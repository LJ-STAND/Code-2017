#ifndef XBEE_H
#define XBEE_H

#include <Config.h>
#include <Arduino.h>
#include <Timer.h>
#include <Common.h>
#include <PlayMode.h>

class XBee {
public:
    int otherBallAngle;
    int otherBallStrength;
    int otherHeading;
    PlayMode otherPlayMode;

    bool isConnected;

    void init();
    void update(int ballAngle, int ballStrength, int heading, PlayMode playMode, bool noRecieve = false);

private:
    int thisBallAngle;
    int thisBallStrength;
    int thisHeading;
    PlayMode thisPlayMode;

    Timer connectedTimer = Timer(XBEE_LOST_COMMUNICATION_TIME);

    void send();
    void receive();
    void resetOtherData();
};

#endif // XBEE_H
