#include "Button.h"

Button::Button(uint8_t _pin) {
	pin = _pin;
	state = BTN_RELEASED;
	pressEvent = releaseEvent = 0;
	clickHappened = 0;

	pinMode(pin, INPUT_PULLUP);
}

void Button::process() {
    uint8_t curBtn = digitalReadFast(pin);
    uint64_t curMillis = millis();

    switch(state) {
      case BTN_RELEASED: 
        if (curBtn == LOW) {
          state = BTN_PRESS_PENDING;
          pressEvent = curMillis;
        }
        break;

      case BTN_PRESS_PENDING:
        if (curBtn == HIGH) {
          state = BTN_RELEASED;
          pressEvent = 0;
        } else {
          if (curMillis - pressEvent > 50) {
            state = BTN_PRESSED;
          }
        }
        break;

      case BTN_PRESSED:
        if (curBtn == HIGH) {
          state = BTN_RELEASE_PENDING;
          releaseEvent = curMillis;
        }
        break;

      case BTN_RELEASE_PENDING:
        if (curMillis - releaseEvent > 50) {
          state = BTN_RELEASED;
          
          if (releaseEvent - pressEvent < 1000) {
            clickHappened = 1;
          }

          releaseEvent = pressEvent = 0;
        }
        break;
    }
}

uint8_t Button::hadClick() {
    process();
    uint8_t result = clickHappened;
    clickHappened = 0;
    return result;
}
