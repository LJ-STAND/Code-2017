#include "XBee.h"

void XBee::tx(uint8_t data) {
    Serial.write(data);
}

int XBee::rx() {
    return Serial.read();
}

void XBee::send(XBeeCommands command, uint16_t data) {
    tx(xbeeStart);
    tx(command);
    tx(data >> 8);
    tx(data & 0xff);
    tx(xbeeEnd);
}

XBeeData XBee::receive() {
    if (Serial.available() > XBEE_TRANSACTION_LENGTH) {
        start = rx();
        command = rx();
        high = rx();
        low = rx();
        data = (high << 8) | low;

        return (XBeeData) {command, data, true};
    } else {
        return (XBeeData) {0, 0, false};
    }
}
