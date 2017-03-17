#include "Sonar.h"

void Sonar::init(uint16_t address) {
    i2cAddress = address;
    lastRangeTime = millis();
    beginRanging();
}

void Sonar::beginRanging() {
    Wire.beginTransmission(i2cAddress);
    Wire.write(0x00);
    Wire.write(0x51);
    Wire.endTransmission();
}

int Sonar::range() {
    Wire.beginTransmission(i2cAddress);
    Wire.write(0x02);
    Wire.endTransmission();

    Wire.requestFrom(i2cAddress, 2);

    while (Wire.available() < 2);

    uint16_t highByte = Wire.read();
    uint16_t lowByte = Wire.read();

    return (highByte << 8) + lowByte;
}

int Sonar::read() {
    if (millis() - lastRangeTime > SONAR_RANGE_TIME) {
        lastRange = range();
        beginRanging();

        lastRangeTime = millis();
    }

    return lastRange;
}
