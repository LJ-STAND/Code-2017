#ifndef SLAVE_H
#define SLAVE_H

#include <t3spi.h>
#include <Pins.h>
#include <LinePosition.h>

enum SlaveCommands: int {
    noCommand,
    linePosition,
    lightSensorsFirst16Bit,
    lightSensorsSecond16Bit,
    orbitAngle,
    orbitSpeed,
    hasBallTSOP,
    tsopAngle
};

class Slave {
public:
    void init(int csPin);
    uint16_t txrx(uint16_t command=SlaveCommands::noCommand);

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
