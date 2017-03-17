/*
* MASTER
*
* Source file for the master teensy for LJ STAND 2017
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <t3spi.h>
#include <DebugController.h>
#include <i2c_t3.h>
#include <Config.h>
#include <SlaveData.h>
#include <Bluetooth.h>
#include <MotorArray.h>
#include <IMU.h>
#include <LinePosition.h>
#include <RobotPosition.h>
#include <CalculateRobotPosition.h>
#include <MoveData.h>
#include <Pins.h>
#include <LightGate.h>
#include <PixyI2C.h>
#include <GoalData.h>
#include <Sonar.h>

T3SPI spi;

volatile uint16_t dataInTsop[DATA_LENGTH_TSOP];
volatile uint16_t dataOutTsop[DATA_LENGTH_TSOP];
volatile uint16_t dataInLight[DATA_LENGTH_LIGHT];
volatile uint16_t dataOutLight[DATA_LENGTH_LIGHT];

DebugController debug;
MotorArray motors;
IMU imu;
LightGate lightGate;
PixyI2C pixy;
Sonar sonarFront;

SlaveData slaveData;
RobotPosition position;
RobotPosition previousPosition = RobotPosition::field;
GoalData goalData;

unsigned long lastPixyUpdate;

void setup() {
    // Onboard LED
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    // Debug
    debug.init();

    // I2C
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
    Wire.setDefaultTimeout(200000);

    debug.toggleOrange(true);

    // Serial
    Serial.begin(9600);
    Bluetooth::init();

    debug.toggleWhite(true);

    // SPI
    spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, MASTER_CS_TSOP, CS_ActiveLOW);
    spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);
    spi.enableCS(MASTER_CS_LIGHT, CS_ActiveLOW);
    spi.enableCS(MASTER_CS_PIXY, CS_ActiveLOW);

    debug.toggleYellow(true);

    // IMU
    imu.init();
    imu.calibrate();

    debug.toggleBlue(true);

    // Light Gate
    lightGate.init();

    debug.toggleGreen(true);

    // Pixy
    pixy.init();
    lastPixyUpdate = micros();

    sonarFront.init(0x70);

    debug.toggleAllLEDs(true);
}

int calculateRotationCorrection() {
    int correctionRotation;
    int rotation = (imu.heading > 180 ? 360 : 0) - imu.heading;

    if (abs(rotation) < IMU_THRESHOLD) {
        correctionRotation = 0;
    } else if (abs(rotation) < CORRECTION_ROTATION_MINIMUM) {
        correctionRotation = (rotation > 0 ? CORRECTION_ROTATION_MINIMUM : -CORRECTION_ROTATION_MINIMUM);
    } else if (abs(rotation) < CORRECTION_ROTATION_MAXIMUM) {
        correctionRotation = rotation;
    } else {
        correctionRotation = (rotation > 0 ? CORRECTION_ROTATION_MAXIMUM : -CORRECTION_ROTATION_MAXIMUM);
    }

    return correctionRotation * CORRECTION_ROTATION_MULTIPLIER;
}

MoveData calculateMovement() {
    int angle = slaveData.orbitAngle != TSOP_NO_BALL ? slaveData.orbitAngle : 0;
    int speed = slaveData.orbitAngle != TSOP_NO_BALL ? slaveData.orbitSpeed : 0;
    int rotation = calculateRotationCorrection();

    // Serial.println(goalData.status);
    // if (goalData.status != GoalStatus::invisible && slaveData.hasBallTsop) {
    //     // We have the ball and we can see the goal
    //
    //     // angle = mod(goalData.angle > 0 ? goalData.angle - 45 : mod(goalData.angle, 360) + 45, 360);
    //     angle = 0;
    //
    //     // angle = goalData.angle > 0 ? 270 : 90;
    //     rotation += (int)(((double)goalData.angle / 75.0) * 255);
    //     speed = 255;
    //
    //     Serial.println(String(goalData.angle) + ", " + String(angle) + ", " + String(rotation));
    // }

    if (position != RobotPosition::field && slaveData.orbitAngle != TSOP_NO_BALL){
        int orbitAngle = slaveData.orbitAngle;

        // Front
        if (position == RobotPosition::smallOnFrontLine) {
            if (270 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER) {
                speed =  0;
            }
        }

        if (position == RobotPosition::bigOnFrontLine) {
            if (270 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER) {
                if (orbitAngle < 180) {
                    angle = 120;
                }
                else {
                    angle = 240;
                }
            }
        }

        if (position == RobotPosition::overFrontLine) {
            angle = 180;
        }

        // Right
        if (position == RobotPosition::smallOnRightLine) {
            if (mod(0 - LS_MOVEMENT_ANGLE_BUFFER, 360) < orbitAngle && orbitAngle < 180 + LS_MOVEMENT_ANGLE_BUFFER) {
                speed = 0;
            }
        }

        if (position == RobotPosition::bigOnRightLine) {
            if (mod(0 - LS_MOVEMENT_ANGLE_BUFFER, 360) < orbitAngle && orbitAngle < 180 + LS_MOVEMENT_ANGLE_BUFFER) {
                if (orbitAngle > 90) {
                    angle = 210;
                }
                else {
                    angle = 330;
                }
            }
        }

        if (position == RobotPosition::overRightLine) {
            angle = 270;
        }

        // Back
        if (position == RobotPosition::smallOnBackLine) {
            if (90 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle && orbitAngle < 270 + LS_MOVEMENT_ANGLE_BUFFER) {
                speed = 0;
            }
        }

        if (position == RobotPosition::bigOnBackLine) {
            if (90 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle && orbitAngle < 270 + LS_MOVEMENT_ANGLE_BUFFER) {
                if (orbitAngle > 180) {
                    angle = 300;
                }
                else {
                    angle = 60;
                }
            }
        }

        if (position == RobotPosition::overBackLine) {
            angle = 0;
        }

        // Left
        if (position == RobotPosition::smallOnLeftLine) {
            if (180 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 0 + LS_MOVEMENT_ANGLE_BUFFER) {
                speed = 0;
            }
        }

        if (position == RobotPosition::bigOnLeftLine) {
            if (180 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 0 + LS_MOVEMENT_ANGLE_BUFFER) {
                if (orbitAngle > 270) {
                    angle = 30;
                }
                else {
                    angle = 150;
                }
            }
        }

        if (position == RobotPosition::overLeftLine) {
            angle = 90;
        }
    }

    // NEED TO DO CORNERS
    MoveData data = MoveData(angle, speed, rotation);
    return data;
    // TODO
}

void getSlaveData() {
    // Does three transfers to ensure the recieved data is what is being requested

    dataOutTsop[0] = SPI_TSOP_ANGLE;
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    int orbitAngle = dataInTsop[0];

    dataOutTsop[0] = SPI_TSOP_SPEED;
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    int orbitSpeed = dataInTsop[0];

    dataOutTsop[0] = SPI_TSOP_HASBALL;
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    bool hasBallTsop = (bool)dataInTsop[0];

    spi.txrx16(dataOutLight, dataInLight, DATA_LENGTH_LIGHT, CTAR_0, MASTER_CS_LIGHT);

    Serial.println(String(orbitAngle) + ", " + String(orbitSpeed) + ", " + String(hasBallTsop));

    slaveData = SlaveData(static_cast<LinePosition>((int)dataInLight[0]), orbitAngle, orbitSpeed, hasBallTsop);
}

void updatePixy() {
    if (micros() - lastPixyUpdate > 30000) {
        uint16_t blocks = pixy.getBlocks();

        if (blocks > 1) {
            goalData.status = GoalStatus::blocked;
        } else if (blocks > 0) {
            goalData.status = GoalStatus::visible;
        } else {
            goalData.status = GoalStatus::invisible;
        }

        if (goalData.status != GoalStatus::invisible) {
            double height = pixy.blocks[0].height;
            goalData.distance = (int)((height / (double)(GOAL_HEIGHT_SHORT - GOAL_HEIGHT_LONG)) * GOAL_DISTANCE_MULTIPLIER);

            double middleGoalPoint = (double)pixy.blocks[0].x;
            double goalDiffMiddleFOV = middleGoalPoint - 160;

            goalData.angle = (int)(((double)goalDiffMiddleFOV / 160.0) * 75);
        } else {
            goalData.distance = 0;
            goalData.angle = 0;
        }

        lastPixyUpdate = micros();
    }
}

void loop() {
    // // Sensors
    // getSlaveData();
    // imu.update();
    // updatePixy();
    //
    // // Debug
    // #if DEBUG_APP_IMU
    // debug.appSendIMU(imu.heading);
    // #endif
    //
    // // Movement
    // position = calculateRobotPosition(slaveData.linePosition, previousPosition);
    // MoveData movement = calculateMovement();
    //
    // if (previousPosition != position) {
    //     // debug.appSendString(String(robotPositionString(position)));
    //     previousPosition = position;
    // }
    //
    // // Serial.println(position);
    // // Serial.println(slaveData.linePosition);
    // // Serial.println(movement.angle);
    // // Serial.println();
    // // Serial.println(imu.position.x);
    // // Serial.println(lightGate.hasBall());
    // // Serial.println(slaveData.hasBallTsop);
    //
    // // debug.appSendString(lightGate.hasBall());
    //
    // motors.move(movement.angle, movement.rotation, movement.speed);

    // byte error, address;
    // int nDevices;
    //
    // Serial.println("Scanning...");
    //
    // nDevices = 0;
    // for(address = 1; address < 127; address++ )
    // {
    //     // The i2c_scanner uses the return value of
    //     // the Write.endTransmisstion to see if
    //     // a device did acknowledge to the address.
    //     Wire.beginTransmission(address);
    //     error = Wire.endTransmission();
    //
    //     if (error == 0)
    //     {
    //         Serial.print("I2C device found at address 0x");
    //         if (address<16)
    //         Serial.print("0");
    //         Serial.print(address,HEX);
    //         Serial.println("  !");
    //
    //         nDevices++;
    //     }
    //     else if (error==4)
    //     {
    //         Serial.print("Unknown error at address 0x");
    //         if (address<16)
    //         Serial.print("0");
    //         Serial.println(address,HEX);
    //     }
    // }
    // if (nDevices == 0)
    // Serial.println("No I2C devices found\n");
    // else
    // Serial.println("done\n");
    //
    // delay(1000);

    Serial.println(sonarFront.read());
}
