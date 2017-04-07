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
#include <Slave.h>
#include <Timer.h>
#include <EEPROM.h>
#include <SparkFunMPU9250-DMP.h>

T3SPI spi;
DebugController debug;
MotorArray motors;
IMU imu;
LightGate lightGate;
PixyI2C pixy;
Sonar sonarFront;
Sonar sonarRight;
Sonar sonarBack;
Sonar sonarLeft;

SlaveLightSensor slaveLightSensor;
SlaveTSOP slaveTSOP;
SlaveData slaveData;

RobotPosition position;
RobotPosition previousPosition = RobotPosition::field;
GoalData goalData;

Timer pixyTimer = Timer(PIXY_UPDATE_TIME);
Timer ledTimer = Timer(LED_BLINK_TIME_MASTER);

bool ledOn;

int facingDirection = 0;

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

    slaveLightSensor.init();
    slaveTSOP.init();

    debug.toggleYellow(true);

    // IMU
    imu.init();
    imu.calibrate();

    // imu.begin();
    // imu.setSensors(INV_XYZ_GYRO);
    // imu.setGyroFSR(2000);
    // imu.dmpBegin(DMP_FEATURE_GYRO_CAL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_6X_LP_QUAT);

    debug.toggleBlue(true);

    // Light Gate
    lightGate.init();

    debug.toggleGreen(true);

    // Pixy
    pixy.init();

    // Sonars
    sonarFront.init(SONAR_FRONT_ADDRESS);
    sonarRight.init(SONAR_RIGHT_ADDRESS);
    sonarBack.init(SONAR_BACK_ADDRESS);
    sonarLeft.init(SONAR_LEFT_ADDRESS);

    debug.toggleAllLEDs(true);
    delay(500);
    debug.flashAllLEDs(3, 200);
}

int calculateRotationCorrection() {
    int correctionRotation;
    int rotation = (mod(imu.heading - facingDirection, 360) > 180 ? 360 : 0) - mod(imu.heading - facingDirection, 360);

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

MoveData calculateLineAvoid(MoveData movement) {
    if (position != RobotPosition::field && slaveData.orbitAngle != TSOP_NO_BALL && AVOID_LINE) {
        int orbitAngle = slaveData.orbitAngle;

        // Front
        if (position == RobotPosition::smallOnFrontLine) {
            if (270 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER) {
                movement.speed = 0;
            }
        }

        if (position == RobotPosition::bigOnFrontLine) {
            if (270 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER) {
                // if (orbitAngle > 0) {
                //     movement.angle = 120;
                // } else {
                //     movement.angle = 240;
                // }
                movement.angle = 180;
            }
        }

        if (position == RobotPosition::overFrontLine) {
            movement.angle = 180;
        }

        // Right
        if (position == RobotPosition::smallOnRightLine) {
            if (mod(0 - LS_MOVEMENT_ANGLE_BUFFER, 360) < orbitAngle || orbitAngle < 180 + LS_MOVEMENT_ANGLE_BUFFER) {
                movement.speed = 0;
            }
        }

        if (position == RobotPosition::bigOnRightLine) {
            if (mod(0 - LS_MOVEMENT_ANGLE_BUFFER, 360) < orbitAngle || orbitAngle < 180 + LS_MOVEMENT_ANGLE_BUFFER) {
                // if (orbitAngle > 90) {
                //     movement.angle = 210;
                // } else {
                //     movement.angle = 330;
                // }
                movement.angle = 270;
            }
        }

        if (position == RobotPosition::overRightLine) {
            movement.angle = 270;
        }

        // Back
        if (position == RobotPosition::smallOnBackLine) {
            if (90 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle && orbitAngle < 270 + LS_MOVEMENT_ANGLE_BUFFER) {
                movement.speed = 0;
            }
        }

        if (position == RobotPosition::bigOnBackLine) {
            if (90 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle && orbitAngle < 270 + LS_MOVEMENT_ANGLE_BUFFER) {
                // if (orbitAngle > 180) {
                //     movement.angle = 300;
                // } else {
                //     movement.angle = 60;
                // }
                movement.angle = 0;
            }
        }

        if (position == RobotPosition::overBackLine) {
            movement.angle = 0;
        }

        // Left
        if (position == RobotPosition::smallOnLeftLine) {
            if (180 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < LS_MOVEMENT_ANGLE_BUFFER) {
                movement.speed = 0;
            }
        }

        if (position == RobotPosition::bigOnLeftLine) {
            if (180 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < LS_MOVEMENT_ANGLE_BUFFER) {
                // if (orbitAngle > 270 || orbitAngle < LS_MOVEMENT_ANGLE_BUFFER) {
                //     movement.angle = 30;
                // } else {
                //     movement.angle = 150;
                // }
                movement.angle = 90;
            }
        }

        if (position == RobotPosition::overLeftLine) {
            movement.angle = 90;
        }

        // Front right corner
        if (position == RobotPosition::smallOnCornerFrontRight) {
            if (270 - LS_MOVEMENT_ANGLE_BUFFER_CORNER < orbitAngle || orbitAngle < 180 + LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                movement.speed = 0;
            }
        }

        if (position == RobotPosition::bigOnCornerFrontRight) {
            if (270 - LS_MOVEMENT_ANGLE_BUFFER_CORNER < orbitAngle || orbitAngle < 180 + LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                // if (orbitAngle > 45) {
                //     movement.angle = 210;
                // } else {
                //     movement.angle = 240;
                // }
                movement.angle = 225;
            }
        }

        if (position == RobotPosition::overCornerFrontRight) {
            movement.angle = 225;
        }

        // Back right corner
        if (position == RobotPosition::smallOnCornerBackRight) {
            if (mod(0 - LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360) < orbitAngle || orbitAngle < 270 + LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                movement.speed = 0;
            }
        }

        if (position == RobotPosition::bigOnCornerBackRight) {
            if (mod(0 - LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360) < orbitAngle || orbitAngle < 270 + LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                // if (orbitAngle > 135) {
                //     movement.angle = 300;
                // } else {
                //     movement.angle = 330;
                // }
                movement.angle = 315;
            }
        }

        if (position == RobotPosition::overCornerBackRight) {
            movement.angle = 315;
        }

        // Back left corner
        if (position == RobotPosition::smallOnCornerBackLeft) {
            if (90 - LS_MOVEMENT_ANGLE_BUFFER_CORNER < orbitAngle || orbitAngle <  LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                movement.speed = 0;
            }
        }

        if (position == RobotPosition::bigOnCornerBackLeft) {
            if (90 - LS_MOVEMENT_ANGLE_BUFFER_CORNER < orbitAngle || orbitAngle < LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                // if (orbitAngle > 225 || orbitAngle < LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                //     movement.angle = 30;
                // } else {
                //     movement.angle = 60;
                // }
                movement.angle = 45;
            }
        }

        if (position == RobotPosition::overCornerBackLeft) {
            movement.angle = 45;
        }

        // Front left corner
        if (position == RobotPosition::smallOnCornerFrontLeft) {
            if (180 - LS_MOVEMENT_ANGLE_BUFFER_CORNER < orbitAngle || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                movement.speed = 0;
            }
        }

        if (position == RobotPosition::bigOnCornerFrontLeft) {
            if (180 - LS_MOVEMENT_ANGLE_BUFFER_CORNER < orbitAngle || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                // if (orbitAngle > 315 || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER_CORNER) {
                //     movement.angle = 120;
                // } else {
                //     movement.angle = 150;
                // }
                movement.angle = 135;
            }
        }

        if (position == RobotPosition::overCornerFrontLeft) {
            movement.angle = 135;
        }

    }

    return movement;
}

MoveData calculateMovement() {
    MoveData movement;
    movement.angle = slaveData.orbitAngle != TSOP_NO_BALL ? slaveData.orbitAngle : 0;
    movement.speed = slaveData.orbitAngle != TSOP_NO_BALL ? slaveData.orbitSpeed : 0;

    if (goalData.status != GoalStatus::invisible && FACE_GOAL && slaveData.hasBallTSOP) {
        // We have the ball and we can see the goal
        // facingDirection = mod(imu.heading + (int)((double)goalData.angle * 0.5), 360);
        movement.angle = goalData.angle > 180 ? goalData.angle * 0.5 + 180 : goalData.angle + 0.5;

        // angle = 0;
        //
        // // angle = goalData.angle > 0 ? 270 : 90;
        // rotation += (int)(((double)goalData.angle / 75.0) * GOAL_ROTATION_MULTIPLIER);
        // speed = 255;
        //
        // // Serial.println(String(goalData.angle) + ", " + String(angle) + ", " + String(rotation));
    } else {
        facingDirection = 0;
    }

    movement = calculateLineAvoid(movement);

    movement.rotation = calculateRotationCorrection();

    return movement;
}

void updatePixy() {
    if (pixyTimer.timeHasPassed()) {
        uint16_t blocks = pixy.getBlocks();

        if (blocks > 1) {
            goalData.status = GoalStatus::blocked;
        } else if (blocks > 0) {
            goalData.status = GoalStatus::visible;
        } else {
            goalData.status = GoalStatus::invisible;
        }

        if (goalData.status != GoalStatus::invisible) {
            debug.toggleRed(true);
            double height = pixy.blocks[0].height;
            goalData.distance = (int)((height / (double)(GOAL_HEIGHT_SHORT - GOAL_HEIGHT_LONG)) * GOAL_DISTANCE_MULTIPLIER);

            double middleGoalPoint = (double)pixy.blocks[0].x;
            double goalDiffMiddleFOV = middleGoalPoint - 160;

            goalData.angle = (int)(((double)goalDiffMiddleFOV / 160.0) * 75);
        } else {
            debug.toggleRed(false);
            goalData.distance = 0;
            goalData.angle = 0;
        }
    }
}

// void updateIMU() {
//     if (imu.fifoAvailable()) {
//         if (imu.dmpUpdateFifo() == INV_SUCCESS) {
//             imu.computeEulerAngles();
//
//             Serial.println(imu.yaw);
//         }
//     }
// }

void loop() {
    // // Slaves
    LinePosition linePosition = slaveLightSensor.getLinePosition();
    uint16_t first16Bit = slaveLightSensor.getFirst16Bit();
    uint16_t second16Bit = slaveLightSensor.getSecond16Bit();

    debug.appSendLightSensors(first16Bit, second16Bit);


    int orbitAngle = slaveTSOP.getOrbitAngle();
    int orbitSpeed = slaveTSOP.getOrbitSpeed();
    bool hasBallTSOP = slaveTSOP.getHasBallTSOP();
    slaveData = SlaveData(linePosition, orbitAngle, orbitSpeed, hasBallTSOP);

    // Sensors
    imu.update();
    // updatePixy();

    // Debug
    #if DEBUG_APP_IMU
        debug.appSendIMU(imu.heading);
    #endif

    #if DEBUG_APP_LIGHTSENSORS
        debug.appSendLightSensors(slaveLightSensor.getFirst16Bit(), slaveLightSensor.getSecond16Bit());
    #endif

    // Movement
    position = calculateRobotPosition(slaveData.linePosition, previousPosition);
    MoveData movement = calculateMovement();

    // if (previousPosition != position) {
    //     // debug.appSendString(robotPositionString(position));
    //     previousPosition = position;
    //
    //     // Serial5.println(linePositionString(linePosition) + ", " + robotPositionString(position));
    // }

    debug.toggleGreen(lightGate.hasBall());

    if (ledTimer.timeHasPassed()) {
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }

    motors.move(movement);

    // Bluetooth::send(linePositionString(linePosition));
    // String recieved = Bluetooth::receive().string;
    // Bluetooth::send(Bluetooth::receive().string);
}
