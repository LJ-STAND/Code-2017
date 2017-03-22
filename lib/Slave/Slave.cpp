#include "Slave.h"

void Slave::init(int csPin) {
    cs = csPin;

    spi.enableCS(cs, CS_ActiveLOW);
}

uint16_t Slave::txrx(uint16_t command) {
    dataOut[0] = command;

    // Three transfers to ensure the recieved data is what was requested
    for (int i = 0; i < 3; i++) {
        spi.txrx16(dataOut, dataIn, 1, CTAR_0, cs);
    }

    return dataIn[0];
}

void SlaveLightSensor::init() {
    Slave::init(MASTER_CS_LIGHT);
}

LinePosition SlaveLightSensor::getLinePosition() {
    return static_cast<LinePosition>(txrx(SlaveCommands::linePosition));
}

void SlaveTSOP::init() {
    Slave::init(MASTER_CS_TSOP);
}

int SlaveTSOP::getOrbitAngle() {
    return txrx(SlaveCommands::orbitAngle);
}

int SlaveTSOP::getOrbitSpeed() {
    return txrx(SlaveCommands::orbitSpeed);
}

bool SlaveTSOP::getHasBallTSOP() {
    return (bool)txrx(SlaveCommands::hasBallTSOP);
}
