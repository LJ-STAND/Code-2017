#ifndef XBEE_H
#define XBEE_H

#include <Config.h>
#include <Arduino.h>
#include <Timer.h>
#include <LJSTANDCommon.h>

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
    int otherBallAngle;
    int otherBallStrength;
    bool isConnected;

    void init();
    void update(int ballAngle, int ballStrength);

private:
    int thisBallAngle;
    int thisBallStrength;

    XBeeCommands toSend[NUM_SEND] = {XBeeCommands::ballAngle, XBeeCommands::ballStrength};
    int lastSentIndex = NUM_SEND - 1;

    Timer connectedTimer = Timer(XBEE_LOST_COMMUNICATION_TIME);

    void tx(uint8_t data);
    int rx();
    void send(XBeeCommands command, uint16_t data);
    void sendNext();
    XBeeData receive();
};

#endif // XBEE_H