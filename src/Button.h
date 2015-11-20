#ifndef __Button_h_
#define __Button_h_

#include "WProgram.h"

#define BTN_RELEASED 0
#define BTN_PRESSED 1
#define BTN_PRESS_PENDING 2
#define BTN_RELEASE_PENDING 3

class Button {
public:
  Button(uint8_t _pin);
  void process();
  uint8_t hadClick();

private:
  uint8_t pin;
  uint8_t state;
  uint64_t pressEvent, releaseEvent;
  uint8_t clickHappened;
};
#endif