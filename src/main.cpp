#include "WProgram.h"

#include "Time.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
Adafruit_SSD1306 display(/*OLED_DC*/ 6, /*OLED_RESET*/ 8, /*OLED_CS*/ 7);

#include "Button.h"
Button btn1(20), btn2(21);

#include "Selection.h"
#include "TextControls.h"

extern "C" int main(void) {
	setTime(0, 0, 0, 21, 11, 2015);

	pinMode(13, OUTPUT);

	pinMode(3, OUTPUT);  //led1
	pinMode(4, OUTPUT);  //led2

	SPI.setSCK(14);
	display.begin(SSD1306_SWITCHCAPVCC);

	display.setTextSize(1);
	display.setTextColor(WHITE);

	Selection selection(6);
	DateTimeTextControl dateTimeCtrl(&display);

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
				dateTimeCtrl.adjust(dateTimeCtrl.selectableToElement(selected), 1);
			}
		}

		display.clearDisplay();

		if (curMillis-lastEvent<15000) {
			display.setCursor(0, 0);

			display.print(" ");
			/* (selected == 0 && !showSelection) */
			for(uint8_t i=0; i<dateTimeCtrl.getElementCount(); i++) {
				dateTimeCtrl.print(i, showSelection || i != dateTimeCtrl.selectableToElement(selected));
			}
			display.print(" ");


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

