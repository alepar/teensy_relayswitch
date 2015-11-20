#ifndef __Selection_h_
#define __Selection_h_

#include "WProgram.h"

class Selection {
private:
	uint8_t size, cur;
	uint64_t lastEvent;

public:
	Selection(uint8_t);
	void next();
	void keep();
	uint8_t selected();
};

#endif