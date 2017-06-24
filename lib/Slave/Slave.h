#ifndef SLAVE_H
#define SLAVE_H

#include <t3spi.h>
#include <Pins.h>
#include <Config.h>
#include <BallData.h>

enum SPITransactionType: int {
    start,
    end,
    commandDelay,
    commandDelay2,
    send,
    receive
};

enum SlaveCommand: int {
    lineAngle = 6,
    lineSize,
    lightSensorsFirst16Bit,
    lightSensorsSecond16Bit,
    tsopAngle,
    tsopStrength
};

enum SPITransactionState: int {
    noTransaction,
    beginning,
    type,
    command,
    cmdDelay,
    cmdDelay2,
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
    uint16_t getFirst16Bit();
    uint16_t getSecond16Bit();
    double getLineAngle();
    double getLineSize();

};

class SlaveTSOP: public Slave {
public:
    void init();
    int getTSOPAngle();
    int getTSOPStrength();
    BallData getBallData();
};

#endif // SLAVE_H
