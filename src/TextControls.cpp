#include "TextControls.h"

DateTimeTextControl::DateTimeTextControl(Adafruit_GFX* _gfx) {
	gfx = _gfx;
}

uint8_t DateTimeTextControl::getElementCount() {
	return 11;
}

uint8_t DateTimeTextControl::getSelectableCount() {
	return 6;
}

uint8_t DateTimeTextControl::selectableToElement(uint8_t s) {
	return s*2;
}


bool DateTimeTextControl::isSelectable(uint8_t idx) {
	return (idx % 2) == 0;
}

void DateTimeTextControl::print(uint8_t idx, bool visible) {
	if(visible) {
		gfx->setTextColor(WHITE);
	} else {
		gfx->setTextColor(BLACK);
	}

	switch(idx) {
		case 1:
		case 3:
			gfx->print("/");
			break;
		case 0:
			gfx->printf("%04u", year());
			break;
		case 2:
			gfx->printf("%02u", month());
			break;
		case 4:
			gfx->printf("%02u", day());
			break;

		case 5:
			gfx->print(" ");
			break;

		case 7:
		case 9:
			gfx->print(":");
			break;
		case 6:
			gfx->printf("%02u", hour());
			break;
		case 8:
			gfx->printf("%02u", minute());
			break;
		case 10:
			gfx->printf("%02u", second());
			break;
	}
}

void DateTimeTextControl::adjust(uint8_t idx, int16_t adjValue) {
	int _year = year();
	int _month = month();
	int _day = day();
	int _hour = hour();
	int _minute = minute();
	int _second = second();

	switch (idx) {
		case 0:
			_year++;
			break;
		case 2:
			_month++;
			break;
		case 4:
			_day++;
			break;
		case 6:
			_hour++;
			break;
		case 8:
			_minute++;
			break;
		case 10:
			_second++;
			break;
		default:
			break;
	}
	setTime(_hour, _minute, _second, _day, _month, _year);
}
