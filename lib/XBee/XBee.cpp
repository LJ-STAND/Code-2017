#include "XBee.h"

void XBee::tx(uint8_t data) {
    Serial.write(data);
}
