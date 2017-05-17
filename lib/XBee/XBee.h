#ifndef XBEE_H
#define XBEE_H

#include <Config.h>

enum XBeeCommands: int {
    xbeeStart,
    xbeeEnd,
    ballAngle,
    ballStrength
};

typedef struct XBeeData {
    XBeeCommands command;
    int data;
    bool received;
} XBeeData;

class XBee {
    void tx(uint8_t data);
    int rx();

    void send(XBeeCommands command, uint16_t data);
    XBeeData receive();
};

#endif // XBEE_H
