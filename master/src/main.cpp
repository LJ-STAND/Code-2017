/*
* MASTER
*
* Source file for the master teensy for LJ STAND 2017
*/

#include <Arduino.h>
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

MoveData calculateLineAvoid(RobotPositionSize size, bool isCorner, int direction, int orbitAngle, MoveData movement) {
    // Direction is the angle the robot would be moving at if it was moving directly towards a line on the field in such a way that the specified RobotPosition was found.

    if (isCorner) {
        switch (size) {
            case RobotPositionSize::small:
                if (angleIsInside(mod(direction - 135 - LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), mod(direction + 135 + LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), orbitAngle)) {
                    movement.speed = 0;
                }

                break;

            case RobotPositionSize::big:
                if (angleIsInside(mod(direction - 135 - LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), mod(direction + 135 + LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), orbitAngle)) {
                    movement.angle = mod(direction + 180 - imu.heading, 360);
                    movement.speed = BIG_LINE_ORBIT_SPEED;
                }

                break;

            case RobotPositionSize::over:
                movement.angle = mod(direction + 180 - imu.heading, 360);
                movement.speed = OVER_LINE_ORBIT_SPEED;
                break;
        }
    } else {
        switch (size) {
            case RobotPositionSize::small:
                if (angleIsInside(mod(direction - 90 - LS_MOVEMENT_ANGLE_BUFFER, 360), mod(direction + 90 + LS_MOVEMENT_ANGLE_BUFFER, 360), orbitAngle)) {
                    movement.speed = 0;
                }

                break;

            case RobotPositionSize::big:
                if (angleIsInside(mod(direction - 90 - LS_MOVEMENT_ANGLE_BUFFER, 360), mod(direction + 90 + LS_MOVEMENT_ANGLE_BUFFER, 360), orbitAngle)) {
                    movement.angle = mod(direction + 180 - imu.heading, 360);
                    movement.speed = BIG_LINE_ORBIT_SPEED;
                }

                break;

            case RobotPositionSize::over:
                movement.angle = mod(direction + 180 - imu.heading, 360);
                movement.speed = OVER_LINE_ORBIT_SPEED;
                break;
        }
    }

    return movement;

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

    if (position != RobotPosition::field && AVOID_LINE) {
        movement = calculateLineAvoid(getRobotPositionSize(position), getRobotPositionIsCorner(position), getRobotPositionDirection(position), slaveData.orbitAngle, movement);
    }

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

void loop() {
    // -- Slaves -- //
    // Light Slave
    LinePosition linePosition = slaveLightSensor.getLinePosition();
    uint16_t first16Bit = slaveLightSensor.getFirst16Bit();
    uint16_t second16Bit = slaveLightSensor.getSecond16Bit();

    // TSOP Slave
    int orbitAngle = slaveTSOP.getOrbitAngle();
    int orbitSpeed = slaveTSOP.getOrbitSpeed();
    bool hasBallTSOP = slaveTSOP.getHasBallTSOP();

    slaveData = SlaveData(linePosition, orbitAngle, orbitSpeed, hasBallTSOP);

    // -- Sensors -- //
    // IMU
    imu.update();
    slaveLightSensor.sendHeading(imu.heading);

    // Pixy
    #if PIXY_ENABLED
        updatePixy();
    #endif

    // -- Debug -- //
    // IMU
    #if DEBUG_APP_IMU
        debug.appSendIMU(imu.heading);
    #endif

    // Light Sensors
    #if DEBUG_APP_LIGHTSENSORS
        debug.appSendLightSensors(first16Bit, second16Bit);
    #endif

    // LED
    if (ledTimer.timeHasPassed()) {
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }

    // -- Movement -- //
    position = calculateRobotPosition(slaveData.linePosition, previousPosition);
    previousPosition = position;
    Serial.println(robotPositionString(position));

    MoveData movement = calculateMovement();
    motors.move(movement);
}
