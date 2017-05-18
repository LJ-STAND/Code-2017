#include "XBee.h"

void XBee::init() {
    Serial.begin(9600);
}

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
        int start = rx();
        int command = rx();
        int high = rx();
        int low = rx();
        int data = (high << 8) | low;

        return (XBeeData) {static_cast<XBeeCommands>(command), data, true};
    } else {
        return (XBeeData) {XBeeCommands::xbeeEnd, 0, false};
    }
}
