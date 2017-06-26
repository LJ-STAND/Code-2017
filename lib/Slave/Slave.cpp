#include "Slave.h"

void Slave::init(int csPin) {
    cs = csPin;

    spi.enableCS(cs, CS_ActiveLOW);
}

uint16_t Slave::transaction(SlaveCommand command) {
    dataOut[0] = (uint16_t)command;

    for (int i = 0; i < 3; i++) {
        spi.txrx16(dataOut, dataIn, 1, CTAR_0, cs);
    }

    return dataIn[0];
}

void SlaveLightSensor::init() {
    Slave::init(MASTER_CS_LIGHT);
}

double SlaveLightSensor::getLineAngle() {
    return (double)transaction(SlaveCommand::lineAngle) / 100.0;
}

double SlaveLightSensor::getLineSize() {
    return (double)transaction(SlaveCommand::lineSize) / 100.0;
}

uint16_t SlaveLightSensor::getFirst16Bit() {
    return transaction(SlaveCommand::lightSensorsFirst16Bit);
}

uint16_t SlaveLightSensor::getSecond16Bit() {
    return transaction(SlaveCommand::lightSensorsSecond16Bit);
}

void SlaveTSOP::init() {
    Slave::init(MASTER_CS_TSOP);
}

int SlaveTSOP::getTSOPAngle() {
    return transaction(SlaveCommand::tsopAngle);
}

int SlaveTSOP::getTSOPStrength() {
    return transaction(SlaveCommand::tsopStrength);
}

BallData SlaveTSOP::getBallData() {
    int angle = getTSOPAngle();
    int strength = getTSOPStrength();

    return BallData(angle, strength, angle != TSOP_NO_BALL);
}
