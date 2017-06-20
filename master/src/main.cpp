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
#include <XBee.h>

XBee xbee;
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
Timer lastSeenGoalTimer = Timer(LAST_SEEN_GOAL_TIME);

double compassPreviousAngle = 0;
long compassPreviousTime;
double compassDiff = 0;

double facingDirection = 0;
double orbitAngleRelative = 0;

bool xbeeConnected = false;
bool ledOn;

int count = 0;

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

    // XBee
    xbee.init();

    // IMU
    imu.init();
    imu.calibrate();
    compassPreviousTime = micros();

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
    delay(100);
    debug.toggleAllLEDs(false);
}

int calculateRotationCorrection() {
    double multiplierD = goalData.status != GoalStatus::invisible || !lastSeenGoalTimer.timeHasPassedNoUpdate() ? CORRECTION_ROTATION_MULTIPLIER_D_GOAL : CORRECTION_ROTATION_MULTIPLIER_D;
    double multiplierP = goalData.status != GoalStatus::invisible || !lastSeenGoalTimer.timeHasPassedNoUpdate() ? CORRECTION_ROTATION_MULTIPLIER_P_GOAL : CORRECTION_ROTATION_MULTIPLIER_P;

    int correctionRotation;
    int rotation = ((mod(imu.heading - facingDirection, 360) > 180 ? 360 : 0) - mod(imu.heading - facingDirection, 360)) * multiplierP + compassDiff * multiplierD;

    if (abs(rotation) < CORRECTION_ROTATION_MINIMUM) {
        correctionRotation = 0;
    } else if (abs(rotation) < CORRECTION_ROTATION_MAXIMUM) {
        correctionRotation = rotation;
    } else {
        correctionRotation = (rotation > 0 ? CORRECTION_ROTATION_MAXIMUM : -CORRECTION_ROTATION_MAXIMUM);
    }
    return correctionRotation;
}

MoveData calculateLineAvoid(RobotPosition position, MoveData movement) {
    // Direction is the angle the robot would be moving at if it was moving directly towards a line on the field in such a way that the specified RobotPosition was found.
    RobotPositionSize size = getRobotPositionSize(position);
    bool isCorner = getRobotPositionIsCorner(position);
    int direction = getRobotPositionDirection(position);
    int orbitAngle = movement.angle;

    if (isCorner) {
        switch (size) {
            case RobotPositionSize::small:
                if (angleIsInside(mod(direction - 135 - LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), mod(direction + 135 + LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), orbitAngle)) {
                    // movement.angle = mod(direction + 180 - imu.heading, 360);
                    // if (!angleIsInside(mod(direction - 135 - LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), mod(direction + 135 + LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), slaveData.tsopAngle)) {
                    //     movement.angle =
                    // } else {
                        movement.speed = 0;
                    // }
                }

                break;

            case RobotPositionSize::big:
                if (angleIsInside(mod(direction - 135 - LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), mod(direction + 135 + LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), orbitAngle)) {
                    movement.angle = mod(direction + 180 - imu.heading, 360);
                    movement.speed = BIG_LINE_SPEED;
                }

                break;

            case RobotPositionSize::over:
                movement.angle = mod(direction + 180 - imu.heading, 360);
                movement.speed = OVER_LINE_SPEED;
                break;
        }
    } else {
        switch (size) {
            case RobotPositionSize::small:
                if (angleIsInside(mod(direction - 90 - LS_MOVEMENT_ANGLE_BUFFER, 360), mod(direction + 90 + LS_MOVEMENT_ANGLE_BUFFER, 360), orbitAngle)) {
                    // movement.angle = mod(direction + 180 - imu.heading, 360);
                    movement.speed = 0;
                }

                break;

            case RobotPositionSize::big:
                if (angleIsInside(mod(direction - 90 - LS_MOVEMENT_ANGLE_BUFFER, 360), mod(direction + 90 + LS_MOVEMENT_ANGLE_BUFFER, 360), orbitAngle)) {
                    movement.angle = mod(direction + 180 - imu.heading, 360);
                    movement.speed = BIG_LINE_SPEED;
                }

                break;

            case RobotPositionSize::over:
                movement.angle = mod(direction + 180 - imu.heading, 360);
                movement.speed = OVER_LINE_SPEED;
                break;
        }
    }

    return movement;
}

MoveData calculateOrbit() {
    MoveData orbitMovement;

    int tsopAngle = slaveData.tsopAngle;
    int tsopStrength = slaveData.tsopStrength;

    if (tsopAngle < ORBIT_SMALL_ANGLE || tsopAngle > 360 - ORBIT_SMALL_ANGLE) {
        orbitMovement.angle = (int)round(tsopAngle < 180 ? (tsopAngle * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER) : (360 - (360 - tsopAngle) * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER));
    } else if (tsopAngle < ORBIT_BIG_ANGLE || tsopAngle > 360 - ORBIT_BIG_ANGLE) {
        if (tsopAngle < 180) {
            double nearFactor = (double)(tsopAngle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            orbitMovement.angle = (int)round(90 * nearFactor + tsopAngle * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER + tsopAngle * (1 - ORBIT_BALL_FORWARD_ANGLE_TIGHTENER) * nearFactor);
        } else {
            double nearFactor = (double)(360 - tsopAngle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            orbitMovement.angle = (int)round(360 - (90 * nearFactor + (360 - tsopAngle)* ORBIT_BALL_FORWARD_ANGLE_TIGHTENER + (360 - tsopAngle) * (1 - ORBIT_BALL_FORWARD_ANGLE_TIGHTENER) * nearFactor));
        }
    } else {
        if (tsopStrength > ORBIT_SHORT_STRENGTH) {
            orbitMovement.angle =  tsopAngle + (tsopAngle < 180 ? 90 : -90);
        } else if (tsopStrength > ORBIT_BIG_STRENGTH) {
            double strengthFactor = (double)(tsopStrength - ORBIT_BIG_STRENGTH) / (double)(ORBIT_SHORT_STRENGTH - ORBIT_BIG_STRENGTH);
            double angleFactor = strengthFactor * 90;
            orbitMovement.angle = tsopAngle + (tsopAngle < 180 ? angleFactor : -angleFactor);
        } else {
            orbitMovement.angle = tsopAngle;
        }
    }

    orbitMovement.angle = mod(orbitMovement.angle + orbitAngleRelative, 360);

    orbitMovement.speed = MAX_ORBIT_SPEED;

    if (tsopAngle == TSOP_NO_BALL) {
        // No Ball -> Don't move except rotating
        orbitMovement.angle = 0;
        orbitMovement.speed = 0;
    }

    #if DEBUG_APP_TSOPS
        debug.appSendOrbitAngle(orbitMovement.angle);
    #endif

    return orbitMovement;
}

void calculateGoalTracking() {
    if (slaveData.tsopStrength > FACE_GOAL_SHORT_STRENGTH || slaveData.tsopAngle < ORBIT_SMALL_ANGLE || slaveData.tsopAngle > 360 - ORBIT_SMALL_ANGLE) {
        orbitAngleRelative = 0;
        debug.setGreenBrightness(255);
    } else if (slaveData.tsopStrength > FACE_GOAL_BIG_STRENGTH) {
        double strengthFactor = (double)(slaveData.tsopStrength - FACE_GOAL_BIG_STRENGTH) / (double)(FACE_GOAL_SHORT_STRENGTH - FACE_GOAL_BIG_STRENGTH);
        double scaledHeading = doubleMod(imu.heading + 180, 360) - 180;

        orbitAngleRelative = -scaledHeading * (1 - strengthFactor);
        debug.setGreenBrightness((int)((double)strengthFactor * 255));
    } else {
        orbitAngleRelative = (360 - imu.heading);
        debug.setGreenBrightness(0);
    }

    orbitAngleRelative = doubleMod(orbitAngleRelative, 360.0);

    if (goalData.status != GoalStatus::invisible || !lastSeenGoalTimer.timeHasPassedNoUpdate()) {
        facingDirection = mod(imu.heading + goalData.angle, 360);
    } else {
        facingDirection = 0;
    }

    // Serial.println(String(goalData.angle) + ", " + String(facingDirection));
}

MoveData calculateMovement() {
    MoveData movement = calculateOrbit();

    if (position != RobotPosition::field && AVOID_LINE) {
        movement = calculateLineAvoid(position, movement);
    }

    movement.rotation = calculateRotationCorrection();

    return movement;
}

void updatePixy() {
    if (pixyTimer.timeHasPassed()) {
        uint16_t blocks = pixy.getBlocks();

        Block goalBlock;
        int foundBlocks = 0;

        for (int i = 0; i < blocks; i++) {
            if (pixy.blocks[i].height * pixy.blocks[i].width > GOAL_MIN_AREA) {
                goalBlock = pixy.blocks[i];
                foundBlocks += 1;
            }
        }

        if (foundBlocks > 1) {
            goalData.status = GoalStatus::blocked;
        } else if (foundBlocks > 0) {
            goalData.status = GoalStatus::visible;
        } else {
            goalData.status = GoalStatus::invisible;
        }

        if (goalData.status != GoalStatus::invisible) {
            lastSeenGoalTimer.update();

            debug.toggleRed(true);
            double height = goalBlock.height;
            goalData.distance = (int)((height / (double)(GOAL_HEIGHT_SHORT - GOAL_HEIGHT_LONG)) * GOAL_DISTANCE_MULTIPLIER);

            #if DEBUG_APP_PIXY
                double width = goalBlock.width;
                double x = goalBlock.x;
                double y = goalBlock.y;

                debug.appSendPixy(x, y, width, height);
            #endif

            double middleGoalPoint = (double)goalBlock.x;
            double goalDiffMiddleFOV = middleGoalPoint - 160;

            goalData.angle = (int)(((double)goalDiffMiddleFOV / 160.0) * 75);
        } else {
            debug.toggleRed(false);

            if (lastSeenGoalTimer.timeHasPassedNoUpdate()) {
                goalData.angle = 0;
                goalData.distance = 0;
            }
        }
    }
}

void updateCompass() {
    imu.update();
    long currentTime = micros();
    compassDiff = (imu.heading - compassPreviousAngle) / (currentTime - compassPreviousTime);

    if (compassDiff > 180) {
        compassDiff -= 360;
    } else if (compassDiff < -180) {
        compassDiff += 360;
    }

    compassPreviousAngle = imu.heading;
    compassPreviousTime = currentTime;
}

void loop() {
    // -- Bluetooth -- //
    // BluetoothData data = Bluetooth::receive();
    // if (data.type == BluetoothDataType::settings && data.value == 9) {
    //     Bluetooth::send(String(DEBUG_APP_IMU) + String(DEBUG_APP_LIGHTSENSORS) + String(false /*DEBUG_APP_TSOPS*/),BluetoothDataType::settings);
    // }

    // -- Slaves -- //
    // Light Slave
    // LinePosition linePosition = slaveLightSensor.getLinePosition();
    // uint16_t first16Bit = slaveLightSensor.getFirst16Bit();
    // uint16_t second16Bit = slaveLightSensor.getSecond16Bit();

    // TSOP Slave
    int tsopAngle = slaveTSOP.getTSOPAngle();
    int tsopStrength = slaveTSOP.getTSOPStrength();

    slaveData = SlaveData(LinePosition::none, tsopAngle, tsopStrength);

    Serial.println(slaveData.tsopStrength);

    // -- XBee -- //
    // xbee.update(slaveData.tsopAngle, slaveData.tsopStrength);

    // Serial.println(String(xbee.otherBallAngle) + ", " + String(xbee.otherBallStrength));

    // -- Sensors -- //
    // IMU
    updateCompass();

    #if LINE_SENSOR_ROTATION
        slaveLightSensor.sendHeading(imu.heading);
    #endif

    position = calculateRobotPosition(slaveData.linePosition, previousPosition);

    if (position != previousPosition) {
        #if DEBUG_APP_LIGHTSENSORS
            // Serial.println(linePositionString(slaveData.linePosition) + ", " + robotPositionString(position));
            Bluetooth::send(position, BluetoothDataType::btRobotPosition);
        #endif

        previousPosition = position;
    }

    // Pixy
    #if PIXY_ENABLED
        updatePixy();
        calculateGoalTracking();
    #endif

    // -- Debug -- //
    // IMU
    #if DEBUG_APP_IMU
        debug.appSendIMU(imu.heading);
    #endif

    // Light Sensors
    #if DEBUG_APP_LIGHTSENSORS
        // debug.appSendLightSensors(first16Bit, second16Bit);
    #endif

    #if DEBUG_APP_TSOPS
        debug.appSendTSOPs(slaveData.tsopAngle);
    #endif

    // LED
    if (ledTimer.timeHasPassed()) {
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }

    // -- Movement -- //

    MoveData movement = calculateMovement();
    motors.move(movement);
}
