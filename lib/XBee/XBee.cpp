#include "XBee.h"

void XBee::init() {
    XBeeSerial.begin(9600);
}

void XBee::update(int ballAngle, int ballStrength) {
    thisBallAngle = ballAngle;
    thisBallStrength = ballStrength;

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
        }
    }
}

void XBee::tx(uint8_t data) {
    XBeeSerial.write(data);
}

int XBee::rx() {
    return XBeeSerial.read();
}

void XBee::send(XBeeCommands command, uint16_t data) {
    tx(xbeeStart);
    tx(command);
    tx(data >> 8);
    tx(data & 0xff);
    tx(xbeeEnd);
}

void XBee::sendNext() {
    XBeeCommands toSendCommmand = toSend[mod(lastSentIndex + 1, NUM_SEND - 1)];
    lastSentIndex += 1;

    switch (toSendCommmand) {
        case XBeeCommands::ballAngle:
            send(toSendCommmand, thisBallAngle);
            break;

        case XBeeCommands::ballStrength:
            send(toSendCommmand, thisBallStrength);
            break;
    }
}

XBeeData XBee::receive() {
    XBeeData nothingRecieved = (XBeeData) {XBeeCommands::xbeeEnd, 0, false};

    if (XBeeSerial.available() > XBEE_TRANSACTION_LENGTH) {
        int start = rx();
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
