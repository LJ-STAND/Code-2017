/*
 * Header file to define configurable values within the whole project
 *(e.g. ORBIT_SPEED)
 */

#ifndef CONFIG_H
#define CONFIG_H

// SPI

#define SPI_DELAY 10

// Light Sensors

#define LS_NUM 24

#define LS_CALIBRATION_COUNT 10
#define LS_CALIBRATION_BUFFER 30

#define LS_MOVEMENT_ANGLE_BUFFER 0
#define LS_MOVEMENT_ANGLE_BUFFER_CORNER 0
#define LS_MOVEMENT_SMALL_MULTIPLIER 0.5

#define AVOID_LINE false

#define LINE_SENSOR_ROTATION true

// Light Gate

#define LIGHT_GATE_CALIBRATION_COUNT 10
#define LIGHT_GATE_CALIBRATION_BUFFER 10

// TSOPS

#define TSOP_NUM 24

#define TSOP_LOOP_COUNT 255

#define TSOP_UNLOCK_DELAY 2

#define TSOP_BEST_TSOP_NO_ANGLE 5
#define TSOP_BEST_TSOP_NO_STRENGTH 2

#define TSOP_K1 10
#define TSOP_K2 2
#define TSOP_K3 1

#define TSOP_MIN_IGNORE 50
#define TSOP_MAX_IGNORE 220

#define TSOP_FIRST_TSOP_WEIGHT 3
#define TSOP_SECOND_TSOP_WEIGHT 2

#define TSOP_FILTER_NOISE true
#define TSOP_FILTER_SURROUNDING true

#define TSOP_NO_BALL 400

#define TSOP_HAS_BALL_STRENGTH 130

// IMU

#define CORRECTION_ROTATION_MINIMUM 2
#define CORRECTION_ROTATION_MAXIMUM 150

#define CORRECTION_ROTATION_MULTIPLIER_P 1.2
#define CORRECTION_ROTATION_MULTIPLIER_D 1.8

#define IMU_CALIBRATION_COUNT 10
#define IMU_CALIBRATION_TIME 100
#define IMU_THRESHOLD 1000

#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

// Orbit

#define ORBIT_SHORT_STRENGTH 120
#define ORBIT_BIG_STRENGTH 105

#define ORBIT_SMALL_ANGLE 10
#define ORBIT_BIG_ANGLE 60

#define ORBIT_BALL_FORWARD_ANGLE_TIGHTENER 0.2

#define MIN_ORBIT_SPEED 200
#define MAX_ORBIT_SPEED 200
#define OVER_LINE_SPEED 255
#define BIG_LINE_SPEED 120

#define BALL_FRONT_BUFFER 10

// Pixy

#define GOAL_MIN_AREA 100

#define GOAL_HEIGHT_SHORT 200
#define GOAL_HEIGHT_LONG 20
#define GOAL_DISTANCE_MULTIPLIER 100
#define GOAL_ROTATION_MULTIPLIER 60

#define PIXY_UPDATE_TIME 30000
#define LAST_SEEN_GOAL_TIME 3000000

#define PIXY_ENABLED false
#define FACE_GOAL false

#define FACE_GOAL_SHORT_STRENGTH 120
#define FACE_GOAL_BIG_STRENGTH 105

// Sonars

#define SONAR_FRONT_ADDRESS 0x70 // 0xE0
#define SONAR_RIGHT_ADDRESS 0x71 // 0xE2
#define SONAR_BACK_ADDRESS 0x72 // 0xE4
#define SONAR_LEFT_ADDRESS 0x73 // 0xE6

#define SONAR_RANGE_TIME 65000

// Debug

#define DEBUG_APP_IMU true
#define DEBUG_APP_LIGHTSENSORS true
#define DEBUG_APP_TSOPS true

#define LED_BLINK_TIME_MASTER 100000
#define LED_BLINK_TIME_SLAVE_TSOP 300000
#define LED_BLINK_TIME_SLAVE_LIGHT 700000

// XBee

#define XBEE_TRANSACTION_LENGTH 5
#define XBEE_LOST_COMMUNICATION_TIME 1000000
#define NUM_SEND 2

#define XBeeSerial Serial4

// Motors

#define MOTOR_ANGLE 40

#endif // CONFIG_H
