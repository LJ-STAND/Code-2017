#include "XBee.h"

void XBee::init() {
    XBEESERIAL.begin(9600);
}

void XBee::update(int ballAngle, int ballStrength, PlayMode playMode) {
    thisBallAngle = ballAngle;
    thisBallStrength = ballStrength;
    thisPlayMode = playMode;

    sendNext();

    XBeeData data = receive();

    isConnected = data.received && !connectedTimer.timeHasPassed();

    if (data.received) {
        connectedTimer.update();

        switch (data.command) {
            case XBeeCommands::ballAngle:
                otherBallAngle = data.data;
                break;

            case XBeeCommands::ballStrength:
                otherBallStrength = data.data;
                break;

            case XBeeCommands::mode:
                otherPlayMode = static_cast<PlayMode>(data.data);
                break;
        }
    }
}

void XBee::tx(uint8_t data) {
    XBEESERIAL.write(data);
}

int XBee::rx() {
    return XBEESERIAL.read();
}

void XBee::send(XBeeCommands command, uint16_t data) {
    tx(xbeeStart);
    tx(command);
    tx(data >> 8);
    tx(data & 0xff);
    tx(xbeeEnd);
}

void XBee::sendNext() {
    XBeeCommands toSendCommmand = toSend[sendIndex];
    sendIndex = mod(sendIndex + 1, NUM_SEND);

    switch (toSendCommmand) {
        case XBeeCommands::ballAngle:
            send(toSendCommmand, thisBallAngle);
            break;

        case XBeeCommands::ballStrength:
            send(toSendCommmand, thisBallStrength);
            break;

        case XBeeCommands::mode:
            send(toSendCommmand, thisPlayMode);
    }
}

XBeeData XBee::receive() {
    XBeeData nothingRecieved = (XBeeData) {XBeeCommands::xbeeEnd, 0, false};

    if (XBEESERIAL.available() > XBEE_TRANSACTION_LENGTH) {
        int start = rx();

        if (start != XBeeCommands::xbeeStart) {
            return nothingRecieved;
        }

        int command = rx();
        int high = rx();
        int low = rx();
        int end = rx();

        int data = (high << 8) | low;

        if (start == XBeeCommands::xbeeStart && end == XBeeCommands::xbeeEnd) {
            return (XBeeData) {static_cast<XBeeCommands>(command), data, true};
        }
    }

    return nothingRecieved;
}
