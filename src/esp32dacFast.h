#ifndef esp32dacFast_h
#define esp32dacFast_h
#include "esp32-hal.h"
#include "driver/gpio.h"



void dacAttachPin(uint8_t pin);
void dacFastWrite25(uint8_t value);
void dacFastWrite26(uint8_t value);
#endif
