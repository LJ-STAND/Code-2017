#include "XBee.h"

void XBee::init() {
    XBEESERIAL.begin(XBEE_BAUD);
    resetOtherData();
}

void XBee::update(int ballAngle, int ballStrength, int heading, bool ballIsOut, PlayMode playMode, bool isOnField, bool noRecieve) {
    thisBallAngle = ballAngle;
    thisBallStrength = ballStrength;
    thisHeading = heading;
    thisBallIsOut = ballIsOut;
    thisPlayMode = playMode;
    thisIsOnField = isOnField;

    send();

    if (!noRecieve) {
        receive();
    }
}

void XBee::send() {
    XBEESERIAL.write(XBEE_START);
    XBEESERIAL.write(XBEE_START);
    XBEESERIAL.write(thisBallAngle >> 8);
    XBEESERIAL.write(thisBallAngle & 0xFF);
    XBEESERIAL.write(thisBallStrength);
    XBEESERIAL.write(thisHeading >> 8);
    XBEESERIAL.write(thisHeading & 0xFF);
    XBEESERIAL.write(thisBallIsOut);
    XBEESERIAL.write(thisPlayMode);
    XBEESERIAL.write(thisIsOnField);
}

void XBee::receive() {
    bool nothingRecieved = true;

    while (XBEESERIAL.available() >= XBEE_PACKET_SIZE) {
        uint8_t first = XBEESERIAL.read();
        uint8_t second = XBEESERIAL.peek();

        if (first == XBEE_START && second == XBEE_START) {
            XBEESERIAL.read();

            uint8_t dataBuffer[XBEE_PACKET_SIZE - 2];

            for (int i = 0; i < XBEE_PACKET_SIZE - 2; i++) {
                dataBuffer[i] = XBEESERIAL.read();
            }

            otherBallAngle = (dataBuffer[0] << 8) | dataBuffer[1];
            otherBallStrength = dataBuffer[2];
            otherHeading = (dataBuffer[3] << 8) | dataBuffer[4];
            otherBallIsOut = (bool) dataBuffer[5];
            otherPlayMode = static_cast<PlayMode>(dataBuffer[6]);
            otherIsOnField = (bool) dataBuffer[7];

            nothingRecieved = false;
            connectedTimer.update();
        }
    }

    isConnected = !nothingRecieved || !connectedTimer.timeHasPassedNoUpdate();

    if (!isConnected) {
        resetOtherData();
    }
}

void XBee::resetOtherData() {
    otherBallAngle = TSOP_NO_BALL;
    otherBallStrength = 0;
    otherPlayMode = PlayMode::undecided;
    otherBallIsOut = false;
    otherHeading = 0;
    otherIsOnField = true;
}
