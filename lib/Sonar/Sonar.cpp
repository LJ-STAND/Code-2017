#include "Sonar.h"

void Sonar::init(uint16_t address) {
    i2cAddress = address;
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
    if (rangeTimer.timeHasPassed()) {
        lastRange = range();
        beginRanging();
    }

    return lastRange;
}

void Sonar::setRange(double newRange) {
    int range = (int)((double)((newRange - 0.043) / 0.043) + 0.5);

    Wire.beginTransmission(i2cAddress);
    Wire.write(0x02);
    Wire.write(range);
    Wire.endTransmission();
}

void Sonar::setAddress(uint16_t newAddress) {
    Wire.beginTransmission(i2cAddress);
    Wire.write(0x00);
    Wire.write(0xA0);
    Wire.endTransmission();

    Wire.beginTransmission(i2cAddress);
    Wire.write(0x00);
    Wire.write(0xAA);
    Wire.endTransmission();

    Wire.beginTransmission(i2cAddress);
    Wire.write(0x00);
    Wire.write(0xA5);
    Wire.endTransmission();

    Wire.beginTransmission(i2cAddress);
    Wire.write(0x00);
    Wire.write(newAddress);
    Wire.endTransmission();

    i2cAddress = newAddress >> 1;

    Wire.beginTransmission(i2cAddress);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(newAddress, 1);
    while (Wire.available() < 1);
    Serial.println(Wire.read());
}
