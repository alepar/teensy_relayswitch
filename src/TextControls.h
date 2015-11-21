#ifndef _TEXT_CONTROLS__H_
#define _TEXT_CONTROLS__H_

#include "WProgram.h"
#include "Adafruit_SSD1306.h"
#include "Time.h"

class TextControl {
public:
	virtual uint8_t getElementCount() = 0;
	virtual uint8_t getSelectableCount() = 0;
	virtual uint8_t selectableToElement(uint8_t s) = 0;

	virtual bool isSelectable(uint8_t idx) = 0;
	virtual void print(uint8_t idx, bool visible) = 0;
	virtual void adjust(uint8_t idx, int16_t adjValue) = 0;
};

class DateTimeTextControl : TextControl {
private:
	Adafruit_GFX* gfx;
public:
	DateTimeTextControl(Adafruit_GFX* _gfx);

	uint8_t getElementCount();
	uint8_t getSelectableCount();
	uint8_t selectableToElement(uint8_t s);

	bool isSelectable(uint8_t idx);
	void print(uint8_t idx, bool visible);
	void adjust(uint8_t idx, int16_t adjValue);
};

#endif