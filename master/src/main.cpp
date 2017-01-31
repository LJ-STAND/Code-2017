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
RobotPosition position;

MotorArray motors;
IMU imu;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    Bluetooth::init();

    spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, CS0, CS_ActiveLOW);
    spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    imu.init();
    imu.callibrate();
}

void getData() {
    spi.txrx16(dataOutTsop, dataInTsop, 1, false, MASTER_CS_TSOP);
    spi.txrx16(dataOutLight, dataInLight, 1, false, MASTER_CS_LIGHT);

    sensorData = SensorData(static_cast<LinePosition>(dataInLight[0]), (int) dataInTsop[0], (int) dataInTsop[1]);
}

MoveData orbit() {
    MoveData movement;
    int angle = sensorData.tsopAngle

    if (angle < ORBIT_ORBIT_SMALL_ANGLE || angle > 360 - ORBIT_ORBIT_SMALL_ANGLE) {
         movement.direction = (int) round(angle < 180 ? (angle * 0.5) : (180 + angle * 0.5));
    } else if (angle < ORBIT_BIG_ANGLE || angle > 360 - ORBIT_BIG_ANGLE){
        if (angle < 180) {
            double nearFactor = (double)(angle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            movement.direction = (int) round(90 * nearFactor);
        } else {
            double nearFactor = (double)(360 - angle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            movement.direction =  (int) round(360 - (90 * nearFactor));
        }
    } else {
        if (tsops.strength > SHORT_STRENGTH) {
            movement.direction =  angle + (angle < 180 ? 90 : -90);
        } else if (tsops.strength > MEDIUM_STRENGTH) {
            double strengthFactor = (double)(tsops.strength - MEDIUM_STRENGTH) / (double)(SHORT_STRENGTH - MEDIUM_STRENGTH);
            double angleFactor = strengthFactor * 90;

            movement.direction = mod(angle + (angle < 180 ? angleFactor : -angleFactor), 360);
        } else {
            movement.direction = angle;
        }
    }

    return movement;
}

MoveData lineAvoid(MoveData movement) {

}

void move() {
    int correctionRotation = imu.correctionRotation();

    MoveData movement = calculateOrbit();
    movement = lineAvoid(movement);
    motors.move(movement.direction, movement.rotation, movement.speed);
}

void loop() {
    getData();

    position = calculateRobotPosition(sensorData.linePosition, position);

    move();
}
