#include "TextControls.h"

// =======================================================
// ============== SystemDateTimeTextControl ==============
// =======================================================
SystemDateTimeTextControl::SystemDateTimeTextControl(Adafruit_GFX* _gfx) {
	gfx = _gfx;
}

uint8_t SystemDateTimeTextControl::getElementCount() {
	return 11;
}

uint8_t SystemDateTimeTextControl::getSelectableCount() {
	return 6;
}

uint8_t SystemDateTimeTextControl::selectableToElement(uint8_t s) {
	return s*2;
}

bool SystemDateTimeTextControl::isSelectable(uint8_t idx) {
	return (idx % 2) == 0;
}

void SystemDateTimeTextControl::print(uint8_t idx, bool visible) {
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

void SystemDateTimeTextControl::adjust(uint8_t idx, int16_t adjValue) {
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


// =======================================================
// ================== TimeTextControl ====================
// =======================================================
TimeTextControl::TimeTextControl(Adafruit_GFX* _gfx) {
	gfx = _gfx;
	_hour = _minute = _second = 0;
}

uint8_t TimeTextControl::getElementCount() {
	return 5;
}

uint8_t TimeTextControl::getSelectableCount() {
	return 3;
}

uint8_t TimeTextControl::selectableToElement(uint8_t s) {
	return s*2;
}

bool TimeTextControl::isSelectable(uint8_t idx) {
	return (idx % 2) == 0;
}

void TimeTextControl::print(uint8_t idx, bool visible) {
	if(visible) {
		gfx->setTextColor(WHITE);
	} else {
		gfx->setTextColor(BLACK);
	}

	switch(idx) {
		case 1:
		case 3:
			gfx->print(":");
			break;
		case 0:
			gfx->printf("%02u", _hour);
			break;
		case 2:
			gfx->printf("%02u", _minute);
			break;
		case 4:
			gfx->printf("%02u", _second);
			break;
	}
}

void TimeTextControl::adjust(uint8_t idx, int16_t adjValue) {
	switch (idx) {
		case 0:
			_hour++;
			break;
		case 2:
			_minute++;
			break;
		case 4:
			_second++;
			break;
	}
	
	if (_second == 60) {
		_second = 0;
		_minute++;
	}

	if (_minute == 60) {
		_minute = 0;
		_hour++;
	}

	if (_hour == 24) {
		_hour = 0;
	}
}

uint8_t TimeTextControl::hour() {
	return _hour;
}

uint8_t TimeTextControl::minute() {
	return _minute;
}

uint8_t TimeTextControl::second() {
	return _second;
}

// =======================================================
// ================= StaticTextControl ===================
// =======================================================
StaticTextControl::StaticTextControl(Adafruit_GFX* _gfx, const char* _text) {
	gfx = _gfx;
	text = _text;
}

uint8_t StaticTextControl::getElementCount() {
	return 1;
}

uint8_t StaticTextControl::getSelectableCount() {
	return 0;
}

uint8_t StaticTextControl::selectableToElement(uint8_t s) {
	return 0;
}


bool StaticTextControl::isSelectable(uint8_t idx) {
	return 0;
}

void StaticTextControl::print(uint8_t idx, bool visible) {
	if (visible) {
		gfx->setTextColor(WHITE);
	} else {
		gfx->setTextColor(BLACK);
	}
	gfx->print(text);
}

void StaticTextControl::adjust(uint8_t idx, int16_t adjValue) { }

// =======================================================
// ================= SwitchTextControl ===================
// =======================================================
SwitchTextControl::SwitchTextControl(Adafruit_GFX* _gfx, const char* _text) {
	gfx = _gfx;
	text = _text;
	state = 0;
}

uint8_t SwitchTextControl::getElementCount() {
	return 1;
}

uint8_t SwitchTextControl::getSelectableCount() {
	return 1;
}

uint8_t SwitchTextControl::selectableToElement(uint8_t s) {
	return 0;
}


bool SwitchTextControl::isSelectable(uint8_t idx) {
	return 1;
}

void SwitchTextControl::print(uint8_t idx, bool visible) {
	if (visible) {
		if (state) {
			gfx->setTextColor(BLACK, WHITE);
		} else {
			gfx->setTextColor(WHITE);
		}
	} else {
		gfx->setTextColor(BLACK);
	}
	gfx->print(text);
}

void SwitchTextControl::adjust(uint8_t idx, int16_t adjValue) {
	state = !state;
}

void SwitchTextControl::set(uint8_t val) {
	state = val;
}

uint8_t SwitchTextControl::get() {
	return state;
}

// =======================================================
// =============== CompositeTextControl ==================
// =======================================================
CompositeTextControl::CompositeTextControl(Adafruit_GFX* _gfx, TextControl *_controls[], uint8_t _controlsLength) {
	gfx = _gfx;
	controls = _controls;
	controlsLength = _controlsLength;

	totalElements = totalSelectable = 0;
	for(uint8_t i=0; i<controlsLength; i++) {
		totalElements += controls[i]->getElementCount();
		totalSelectable += controls[i]->getSelectableCount();
	}
}

uint8_t CompositeTextControl::getElementCount() {
	return totalElements;	
}

uint8_t CompositeTextControl::getSelectableCount() {
	return totalSelectable;
}

uint8_t CompositeTextControl::selectableToElement(uint8_t s) {
	uint8_t result = 0;
	for(uint8_t i=0; i<controlsLength; i++) {
		uint8_t curSelectable = controls[i]->getSelectableCount();
		uint8_t curElements = controls[i]->getElementCount();

		if (s >= curSelectable) {
			s -= curSelectable;
			result += curElements;
		} else {
			result += controls[i]->selectableToElement(s);
			break;
		}
	}

	return result;
}

bool CompositeTextControl::isSelectable(uint8_t idx) {
	for(uint8_t i=0; i<controlsLength; i++) {
		uint8_t curElements = controls[i]->getElementCount();

		if (idx >= curElements) {
			idx -= curElements;
		} else {
			return controls[i]->isSelectable(idx);
		}
	}

	return 0;
}

void CompositeTextControl::print(uint8_t idx, bool visible) {
	for(uint8_t i=0; i<controlsLength; i++) {
		uint8_t curElements = controls[i]->getElementCount();

		if (idx >= curElements) {
			idx -= curElements;
		} else {
			controls[i]->print(idx, visible);
			break;
		}
	}
}

void CompositeTextControl::adjust(uint8_t idx, int16_t adjValue) {
	for(uint8_t i=0; i<controlsLength; i++) {
		uint8_t curElements = controls[i]->getElementCount();

		if (idx >= curElements) {
			idx -= curElements;
		} else {
			controls[i]->adjust(idx, adjValue);
			break;
		}
	}
}
