#ifndef XBEE_H
#define XBEE_H

#include <Config.h>
#include <Arduino.h>
#include <Timer.h>
#include <LJSTANDCommon.h>
#include <PlayMode.h>

enum XBeeCommands: int {
    xbeeStart,
    xbeeEnd,
    ballAngle,
    ballStrength,
    playMode
};

typedef struct XBeeData {
    XBeeCommands command;
    int data;
    bool received;
} XBeeData;

class XBee {
public:
    int otherBallAngle;
    int otherBallStrength;
    PlayMode otherPlayMode;
    bool isConnected;

    void init();
    void update(int ballAngle, int ballStrength, PlayMode playMode);

private:
    int thisBallAngle;
    int thisBallStrength;
    PlayMode thisPlayMode;

    XBeeCommands toSend[NUM_SEND] = {XBeeCommands::ballAngle, XBeeCommands::ballStrength, XBeeCommands::playMode};
    int sendIndex = 0;

    Timer connectedTimer = Timer(XBEE_LOST_COMMUNICATION_TIME);

    void tx(uint8_t data);
    int rx();
    void send(XBeeCommands command, uint16_t data);
    void sendNext();
    XBeeData receive();
};

#endif // XBEE_H
