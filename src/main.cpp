#include "WProgram.h"

#include "Time.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
Adafruit_SSD1306 display(/*OLED_DC*/ 6, /*OLED_RESET*/ 8, /*OLED_CS*/ 7);

#include "Button.h"
Button btn1(20), btn2(21);

#include "Selection.h"

extern "C" int main(void) {
	setTime(0, 0, 0, 19, 11, 2015);

	pinMode(13, OUTPUT);

	pinMode(3, OUTPUT);  //led1
	pinMode(4, OUTPUT);  //led2

	SPI.setSCK(14);
	display.begin(SSD1306_SWITCHCAPVCC);

	display.setTextSize(1);
	display.setTextColor(WHITE);

	Selection selection(6);

	uint64_t lastEvent = millis(), curMillis = lastEvent;

	while(1) {
		curMillis = millis();

		uint8_t showSelection = (curMillis/125) % 2;
		int8_t selected = selection.selected();

		if (btn1.hadClick()) {
			selection.next();
			lastEvent = curMillis;
		}
		if (btn2.hadClick()) {
			lastEvent = curMillis;
			if (selected >= 0 ) {
				selection.keep();
				int _year = year();
				int _month = month();
				int _day = day();
				int _hour = hour();
				int _minute = minute();
				int _second = second();
				switch (selected) {
					case 0:
						_year++;
						break;
					case 1:
						_month++;
						break;
					case 2:
						_day++;
						break;
					case 3:
						_hour++;
						break;
					case 4:
						_minute++;
						break;
					case 5:
						_second++;
						break;
					default:
						break;
				}
				setTime(_hour, _minute, _second, _day, _month, _year);
			}
		}

		display.clearDisplay();

		if (curMillis-lastEvent<15000) {
			display.setCursor(0, 0);
			display.print(" ");

			if (selected == 0 && !showSelection) {
				display.print("    ");
			} else {
				display.printf("%04u", year());
			}
			display.print("/");
			if (selected == 1 && !showSelection) {
				display.print("  ");
			} else {
				display.printf("%02u", month());
			}
			display.print("/");
			if (selected == 2 && !showSelection) {
				display.print("  ");
			} else {
				display.printf("%02u", day());
			}
			display.print(" ");

			if (selected == 3 && !showSelection) {
				display.print("  ");
			} else {
				display.printf("%02u", hour());
			}
			display.print(":");
			if (selected == 4 && !showSelection) {
				display.print("  ");
			} else {
				display.printf("%02u", minute());
			}
			display.print(":");
			if (selected == 5 && !showSelection) {
				display.print("  ");
			} else {
				display.printf("%02u", second());
			}
			display.println("\n");

			display.setTextColor(BLACK, WHITE);
			display.print("1");
			display.setTextColor(WHITE);
			display.print(" 00:00:00 - 12:00:00");

			display.setTextColor(WHITE);
			display.print("2");
			display.setTextColor(WHITE);
			display.print(" 00:00:00 - 12:00:00");

			display.setTextColor(BLACK, WHITE);
			display.print("3");
			display.setTextColor(WHITE);
			display.print(" 00:00:00 - 12:00:00");

			display.setTextColor(WHITE);
			display.print("4");
			display.setTextColor(WHITE);
			display.print(" 00:00:00 - 12:00:00");
		}
		
		display.display();
	}
}

