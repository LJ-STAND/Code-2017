#ifndef SLAVE_H
#define SLAVE_H

#include <t3spi.h>
#include <Pins.h>
#include <LinePosition.h>

enum SPITransactionType: int {
    start,
    end,
    send,
    receive
};

enum SlaveCommand: int {
    linePosition = 4,
    lightSensorsFirst16Bit,
    lightSensorsSecond16Bit,
    orbitAngle,
    orbitSpeed,
    hasBallTSOP,
    tsopAngle,
    sendCompass
};

enum SPITransactionState: int {
    noTransaction,
    beginning,
    type,
    command,
    data
};

class Slave {
public:
    void init(int csPin);
    uint16_t txrx(uint16_t data=0);
    uint16_t transaction(SlaveCommand command, SPITransactionType transactionType, uint16_t data=0);

private:
    volatile uint16_t dataIn[1];
    volatile uint16_t dataOut[1];
    int cs;
};

class SlaveLightSensor: public Slave {
public:
    void init();
    LinePosition getLinePosition();
    uint16_t getFirst16Bit();
    uint16_t getSecond16Bit();
    void sendHeading(double heading);
};

class SlaveTSOP: public Slave {
public:
    void init();
    int getOrbitAngle();
    int getOrbitSpeed();
    bool getHasBallTSOP();
    int getTSOPAngle();
};

#endif // SLAVE_H
