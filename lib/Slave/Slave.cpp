#include "Slave.h"

void Slave::init(int csPin) {
    cs = csPin;

    spi.enableCS(cs, CS_ActiveLOW);
}

uint16_t Slave::txrx(uint16_t data) {
    dataOut[0] = data;
    spi.txrx16(dataOut, dataIn, 1, CTAR_0, cs);
    delayMicroseconds(SPI_DELAY);
    return dataIn[0];
}

uint16_t Slave::transaction(SlaveCommand command, SPITransactionType transactionType, uint16_t data) {
    txrx(SPITransactionType::start);
    txrx(transactionType);
    txrx(command);

    for (int i = 0; i < 5; i++) {
        // 5 delay commands to ensure correct data is recieved
        txrx(SPITransactionType::commandDelay);
    }

    txrx(SPITransactionType::commandDelay2);

    uint16_t received;

    if (transactionType == SPITransactionType::send) {
        txrx(data);
    } else if (transactionType == SPITransactionType::receive) {
        received = txrx();
    } else {
        txrx();
    }

    txrx(SPITransactionType::end);

    return received;
}

void SlaveLightSensor::init() {
    Slave::init(MASTER_CS_LIGHT);
}

double SlaveLightSensor::getLineAngle() {
    return (double)transaction(SlaveCommand::lineAngle, SPITransactionType::receive) / 100.0;
}

double SlaveLightSensor::getLineSize() {
    return (double)transaction(SlaveCommand::lineSize, SPITransactionType::receive) / 100.0;
}

uint16_t SlaveLightSensor::getFirst16Bit() {
    return transaction(SlaveCommand::lightSensorsFirst16Bit, SPITransactionType::receive);
}

uint16_t SlaveLightSensor::getSecond16Bit() {
    return transaction(SlaveCommand::lightSensorsSecond16Bit, SPITransactionType::receive);
}

void SlaveTSOP::init() {
    Slave::init(MASTER_CS_TSOP);
}

int SlaveTSOP::getTSOPAngle() {
    return transaction(SlaveCommand::tsopAngle, SPITransactionType::receive);
}

int SlaveTSOP::getTSOPStrength() {
    return transaction(SlaveCommand::tsopStrength, SPITransactionType::receive);
}

BallData SlaveTSOP::getBallData() {
    int angle = getTSOPAngle();
    int strength = getTSOPStrength();

    return BallData(angle, strength, angle != TSOP_NO_BALL);
}
