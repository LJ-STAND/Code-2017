/*
 * Source file for the master teensy for LJ STAND
 */

#include <Arduino.h>
#include <t3spi.h>
#include <i2c_t3.h>
#include <Bluetooth.h>

#include <LinePosition.h>
#include <RobotPosition.h>
#include <CalculateRobotPostion.h>

T3SPI spi;

volatile uint16_t dataInTsop[DATA_LENGTH_TSOP];
volatile uint16_t dataOutTsop[DATA_LENGTH_TSOP];
volatile uint16_t dataInLight[DATA_LENGTH_LIGHT];
volatile uint16_t dataOutLight[DATA_LENGTH_LIGHT];

SensorData sensorData;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    Bluetooth::init();

    spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, CS0, CS_ActiveLOW);
    spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void getData() {
    spi.txrx16(dataOutTsop, dataInTsop, 1, false, MASTER_CS_TSOP);
    spi.txrx16(dataOutLight, dataInLight, 1, false, MASTER_CS_LIGHT);

    sensorData = SensorData(static_cast<LinePosition>(dataInLight[0]), (int) dataInTsop[0], (int) dataInTsop[1]);
}

void loop() {
    getData();
}
