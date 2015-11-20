#include "Selection.h"

Selection::Selection(uint8_t _size) {
	size = _size;
	cur = -1;
	lastEvent = 0;
}

void Selection::next() {
	cur++;
	if (cur == size) {
		cur = -1;
	}
	keep();
}

void Selection::keep() {
	lastEvent = millis();
}

uint8_t Selection::selected() {
	if (millis() - lastEvent > 15000) {
		cur = -1;
	}

	return cur;
}