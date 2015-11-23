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

class SystemDateTimeTextControl : public TextControl {
private:
	Adafruit_GFX* gfx;
public:
	SystemDateTimeTextControl(Adafruit_GFX* _gfx);

	uint8_t getElementCount();
	uint8_t getSelectableCount();
	uint8_t selectableToElement(uint8_t s);

	bool isSelectable(uint8_t idx);
	void print(uint8_t idx, bool visible);
	void adjust(uint8_t idx, int16_t adjValue);
};

class TimeTextControl : public TextControl {
private:
	Adafruit_GFX* gfx;
	uint8_t _hour, _minute, _second;
public:
	TimeTextControl(Adafruit_GFX* _gfx);

	uint8_t getElementCount();
	uint8_t getSelectableCount();
	uint8_t selectableToElement(uint8_t s);

	bool isSelectable(uint8_t idx);
	void print(uint8_t idx, bool visible);
	void adjust(uint8_t idx, int16_t adjValue);

	uint8_t hour();
	uint8_t minute();
	uint8_t second();
};

class StaticTextControl : public TextControl {
private:
	const char* text;
	Adafruit_GFX* gfx;
public:
	StaticTextControl(Adafruit_GFX* _gfx, const char* _text);

	uint8_t getElementCount();
	uint8_t getSelectableCount();
	uint8_t selectableToElement(uint8_t s);

	bool isSelectable(uint8_t idx);
	void print(uint8_t idx, bool visible);
	void adjust(uint8_t idx, int16_t adjValue);
};

class SwitchTextControl : public TextControl {
private:
	const char* text;
	Adafruit_GFX* gfx;
	bool state;
public:
	SwitchTextControl(Adafruit_GFX* _gfx, const char* _text);

	uint8_t getElementCount();
	uint8_t getSelectableCount();
	uint8_t selectableToElement(uint8_t s);

	bool isSelectable(uint8_t idx);
	void print(uint8_t idx, bool visible);
	void adjust(uint8_t idx, int16_t adjValue);
};

class CompositeTextControl : public TextControl {
private:
	Adafruit_GFX* gfx;
	TextControl **controls;
	uint8_t controlsLength;

	uint8_t totalElements;
	uint8_t totalSelectable;
public:
	CompositeTextControl(Adafruit_GFX* _gfx, TextControl *_controls[], uint8_t _controlsLength);

	uint8_t getElementCount();
	uint8_t getSelectableCount();
	uint8_t selectableToElement(uint8_t s);

	bool isSelectable(uint8_t idx);
	void print(uint8_t idx, bool visible);
	void adjust(uint8_t idx, int16_t adjValue);
};

#endif