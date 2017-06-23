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
#include <Bluetooth.h>
#include <MotorArray.h>
#include <IMU.h>
#include <MoveData.h>
#include <Pins.h>
#include <LightGate.h>
#include <PixyI2C.h>
#include <GoalData.h>
#include <Sonar.h>
#include <Slave.h>
#include <Timer.h>
#include <XBee.h>
#include <PlayMode.h>
#include <BallData.h>
#include <LineData.h>

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

LineData lineData;
BallData ballData;
MoveData moveData;
GoalData goalData;

PlayMode playMode = PlayMode::attack;

Timer pixyTimer = Timer(PIXY_UPDATE_TIME);
Timer ledTimer = Timer(LED_BLINK_TIME_MASTER);
Timer lastSeenGoalTimer = Timer(LAST_SEEN_GOAL_TIME);

double compassPreviousAngle = 0;
long compassPreviousTime;
double compassDiff = 0;

double facingDirection = 0;
double orbitAngleRelative = 0;

bool ledOn;

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

    // XBee
    xbee.init();

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

double defaultDirection() {
    return playMode == PlayMode::attack ? 0 : 180;
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

void calculateLineAvoid() {
    if (!lineData.onField) {
        if (lineData.size > 1) {
            moveData.angle = mod(lineData.angle + 180 - imu.heading, 360);
            moveData.speed = lineData.size / 3.0 * 255;
        } else {
            if (mod(lineData.angle, 90) > 30 && mod(lineData.angle, 90) < 60) {
                if (angleIsInside(doubleMod(lineData.angle - 135 - LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), doubleMod(lineData.angle + 135 + LS_MOVEMENT_ANGLE_BUFFER_CORNER, 360), mod(moveData.angle + imu.heading, 360))) {
                    moveData.angle = mod(lineData.angle + 180 - imu.heading, 360);
                    moveData.speed = lineData.size < 0.5 ? 0 : lineData.size / 3.0 * 255;
                }
            } else {
                if (angleIsInside(doubleMod(lineData.angle - 90 - LS_MOVEMENT_ANGLE_BUFFER, 360), doubleMod(lineData.angle + 90 + LS_MOVEMENT_ANGLE_BUFFER, 360), moveData.angle)) {
                    moveData.angle = mod(lineData.angle + 180 - imu.heading, 360);
                    moveData.speed = lineData.size < 0.5 ? 0 : lineData.size / 3.0 * 255;
                }
            }
        }
    }
}

void calculateOrbit() {
    if (ballData.angle < ORBIT_SMALL_ANGLE || ballData.angle > 360 - ORBIT_SMALL_ANGLE) {
        moveData.angle = (int)round(ballData.angle < 180 ? (ballData.angle * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER) : (360 - (360 - ballData.angle) * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER));
    } else if (ballData.angle < ORBIT_BIG_ANGLE || ballData.angle > 360 - ORBIT_BIG_ANGLE) {
        if (ballData.angle < 180) {
            double nearFactor = (double)(ballData.angle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            moveData.angle = (int)round(90 * nearFactor + ballData.angle * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER + ballData.angle * (1 - ORBIT_BALL_FORWARD_ANGLE_TIGHTENER) * nearFactor);
        } else {
            double nearFactor = (double)(360 - ballData.angle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            moveData.angle = (int)round(360 - (90 * nearFactor + (360 - ballData.angle)* ORBIT_BALL_FORWARD_ANGLE_TIGHTENER + (360 - ballData.angle) * (1 - ORBIT_BALL_FORWARD_ANGLE_TIGHTENER) * nearFactor));
        }
    } else {
        if (ballData.strength > ORBIT_SHORT_STRENGTH) {
            moveData.angle =  ballData.angle + (ballData.angle < 180 ? 90 : -90);
        } else if (ballData.strength > ORBIT_BIG_STRENGTH) {
            double strengthFactor = (double)(ballData.strength - ORBIT_BIG_STRENGTH) / (double)(ORBIT_SHORT_STRENGTH - ORBIT_BIG_STRENGTH);
            double angleFactor = strengthFactor * 90;
            moveData.angle = ballData.angle + (ballData.angle < 180 ? angleFactor : -angleFactor);
        } else {
            moveData.angle = ballData.angle;
        }
    }

    moveData.speed = MAX_ORBIT_SPEED;

    if (ballData.angle == TSOP_NO_BALL) {
        // No Ball -> Don't move except rotating
        moveData.angle = 0;
        moveData.speed = 0;
    }
}

void calculateGoalTracking() {
    if (goalData.status != GoalStatus::invisible || !lastSeenGoalTimer.timeHasPassedNoUpdate()) {
        facingDirection = mod(imu.heading + goalData.angle, 360);

        if (ballData.strength > FACE_GOAL_SHORT_STRENGTH || ballData.angle < ORBIT_SMALL_ANGLE || ballData.angle > 360 - ORBIT_SMALL_ANGLE) {
            orbitAngleRelative = 0;
            debug.setGreenBrightness(255);
        } else if (ballData.strength > FACE_GOAL_BIG_STRENGTH) {
            double strengthFactor = (double)(ballData.strength - FACE_GOAL_BIG_STRENGTH) / (double)(FACE_GOAL_SHORT_STRENGTH - FACE_GOAL_BIG_STRENGTH);
            double scaledHeading = doubleMod(imu.heading + 180, 360) - 180;

            orbitAngleRelative = -scaledHeading * (1 - strengthFactor);
            debug.setGreenBrightness((int)((double)strengthFactor * 255));
        } else {
            orbitAngleRelative = -imu.heading;
            debug.setGreenBrightness(0);
        }

        orbitAngleRelative = doubleMod(orbitAngleRelative, 360.0);
    } else {
        facingDirection = defaultDirection();
        orbitAngleRelative = 0;
    }
}

void calculateMovement() {
    calculateOrbit();

    #if AVOID_LINE
        calculateLineAvoid();
    #endif

    moveData.rotation = calculateRotationCorrection();
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
            debug.toggleRed(true);

            lastSeenGoalTimer.update();

            goalData.distance = (int)(((double)goalBlock.height / (double)(GOAL_HEIGHT_SHORT - GOAL_HEIGHT_LONG)) * GOAL_DISTANCE_MULTIPLIER);

            #if DEBUG_APP_PIXY
                debug.appSendPixy(goalBlock.x, goalBlock.y, goalBlock.width, goalBlock.height);
            #endif

            double middleGoalPoint = (double)goalBlock.x;
            double goalDiffMiddleFOV = middleGoalPoint - 160;

            goalData.angle = (int)(((double)goalDiffMiddleFOV / 160.0) * 75);
        } else {
            if (lastSeenGoalTimer.timeHasPassedNoUpdate()) {
                goalData.angle = 0;
                goalData.distance = 0;
            }
        }

        debug.toggleRed(goalData.status != GoalStatus::invisible);
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

void calculatePlayMode() {
    if (xbee.isConnected) {
        if (abs(xbee.otherBallAngle - 180) - abs(ballData.angle - 180) > 90) {
            playMode = PlayMode::attack;
        } else {
            playMode = PlayMode::defend;
        }
    } else {
        playMode = PlayMode::attack;
    }
}

void updateLine(double angle, double size) {
    angle = doubleMod(angle + imu.heading, 360);

    if (lineData.onField) {
        if (size != 3) {
            lineData.angle = angle;
            lineData.size = size;

            lineData.onField = false;
        }
    } else {
        if (lineData.size == 3) {
            if (size != 3) {
                lineData.angle = doubleMod(angle + 180, 360);
                lineData.size = 2 - size;
            }
        } else {
            if (size == 3) {
                if (lineData.size <= 1) {
                    lineData.onField = true;
                    lineData.size = 0;
                    lineData.angle = 0;
                } else {
                    lineData.size = 3;
                }
            } else {
                if (smallestAngleBetween(lineData.angle, angle) <= 90) {
                    lineData.angle = angle;
                    lineData.size = size;
                } else {
                    lineData.angle = doubleMod(angle + 180, 360);
                    lineData.size = 2 - size;
                }
            }
        }
    }
}

void appDebug() {
    #if DEBUG_APP_IMU
        debug.appSendIMU(imu.heading);
    #endif

    #if DEBUG_APP_LIGHTSENSORS
        uint16_t first16Bit = slaveLightSensor.getFirst16Bit();
        uint16_t second16Bit = slaveLightSensor.getSecond16Bit();

        debug.appSendLightSensors(first16Bit, second16Bit);
    #endif

    #if DEBUG_APP_TSOPS
        debug.appSendTSOPs(ballData.angle);
        debug.appSendOrbitAngle(moveData.angle);
    #endif
}

void loop() {
    updateLine(slaveLightSensor.getLineAngle(), slaveLightSensor.getLineSize());

    Serial.println(String(lineData.angle) + ", " + String(lineData.size));

    ballData = BallData(slaveTSOP.getTSOPAngle(), slaveTSOP.getTSOPStrength());

    updateCompass();

    #if PIXY_ENABLED
        updatePixy();
        calculateGoalTracking();
    #endif

    appDebug();

    calculateMovement();

    motors.move(moveData);

    if (ledTimer.timeHasPassed()) {
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }
}
