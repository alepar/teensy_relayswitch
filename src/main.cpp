#include "WProgram.h"

#include "Time.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
Adafruit_SSD1306 display(/*OLED_DC*/ 6, /*OLED_RESET*/ 8, /*OLED_CS*/ 7);

#include "Button.h"
Button btn1(20), btn2(21);

#include "Selection.h"
#include "TextControls.h"

bool lessOrEqual(uint8_t lh, uint8_t lm, uint8_t ls, uint8_t rh, uint8_t rm, uint8_t rs) {
	if (lh < rh) {
		return 1;
	} else if (lh > rh) {
		return 0;
	} else if (lm < rm) {
		return 1;
	} else if (lm > rm) {
		return 0;
	} else if (ls > rs) {
		return 0;
	} else {
		return 1;
	}
}

extern "C" int main(void) {
	setTime(0, 0, 0, 21, 11, 2015);

	pinMode(13, OUTPUT);

	pinMode(3, OUTPUT);  //led1
	pinMode(4, OUTPUT);  //led2

	SPI.setSCK(14);
	display.begin(SSD1306_SWITCHCAPVCC);

	display.setTextSize(1);
	display.setTextColor(WHITE);

	StaticTextControl spaceTxt(&display, " ");
	StaticTextControl dotsLine(&display, "---------------------");
	StaticTextControl dashTxt(&display, " - ");

    SystemDateTimeTextControl systemDateTime(&display);

    SwitchTextControl relaySwitches[] = {
    	SwitchTextControl(&display, "1"),
    	SwitchTextControl(&display, "2"),
    	SwitchTextControl(&display, "3"),
    	SwitchTextControl(&display, "4")
    };

    TimeTextControl relayStarts[] = {
		TimeTextControl(&display),
		TimeTextControl(&display),
		TimeTextControl(&display),
		TimeTextControl(&display)
    };

    TimeTextControl relayEnds[] = {
		TimeTextControl(&display),
		TimeTextControl(&display),
		TimeTextControl(&display),
		TimeTextControl(&display)
    };

	TextControl *controlsArray[] = { 
		&spaceTxt, &systemDateTime, &spaceTxt,
		&dotsLine,
		&relaySwitches[0], &spaceTxt, &relayStarts[0], &dashTxt, &relayEnds[0],
		&relaySwitches[1], &spaceTxt, &relayStarts[1], &dashTxt, &relayEnds[1],
		&relaySwitches[2], &spaceTxt, &relayStarts[2], &dashTxt, &relayEnds[2],
		&relaySwitches[3], &spaceTxt, &relayStarts[3], &dashTxt, &relayEnds[3]
	};

	CompositeTextControl screenCtrl(&display, controlsArray,  sizeof(controlsArray)/sizeof(controlsArray[0]));
	Selection selection(screenCtrl.getSelectableCount());

	uint64_t lastEvent = millis(), curMillis = lastEvent;

	uint8_t lastStates[4] = {0};

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
			if (selected >= 0) {
				selection.keep();
				screenCtrl.adjust(screenCtrl.selectableToElement(selected), 1);
			}
		}

		display.clearDisplay();
		if (curMillis-lastEvent < 15000) {
			display.setCursor(0, 0);
			for(uint8_t i=0; i<screenCtrl.getElementCount(); i++) {
				screenCtrl.print(i, showSelection || i != screenCtrl.selectableToElement(selected));
			}
		}		

		uint8_t _hour = hour();
		uint8_t _minute = minute();
		uint8_t _second = second();

		for (uint8_t i=0; i<2; i++) {
			uint8_t se, sc, ce, on;
			se = !lessOrEqual(relayEnds[i].hour(), relayEnds[i].minute(), relayEnds[i].second(), relayStarts[i].hour(), relayStarts[i].minute(), relayStarts[i].second());
			sc = lessOrEqual(relayStarts[i].hour(), relayStarts[i].minute(), relayStarts[i].second(), _hour, _minute, _second);
			ce = lessOrEqual(_hour, _minute, _second, relayEnds[i].hour(), relayEnds[i].minute(), relayEnds[i].second());
			if(se) {
				on = sc && ce;
			} else {
				on = sc || ce;
			}

			if(lastStates[i] != on) {
				relaySwitches[i].set(on);
			}
			lastStates[i] = on;
			digitalWrite(i+3, relaySwitches[i].get() ? HIGH : LOW);
		}

		display.display();
	}
}

