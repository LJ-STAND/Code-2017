/*
 * Header file to define configurable values within the whole project
 *(e.g. ORBIT_SPEED)
 */

#ifndef CONFIG_H
#define CONFIG_H

// Light Sensors

#define LS_CALIBRATION_COUNT 15
#define LS_CALIBRATION_BUFFER 30

// TSOPS

#define TSOP_NUM 24

#define TSOP_LOOP_COUNT 200

#define TSOP_UNLOCK_DELAY 2

#define TSOP_BEST_TSOP_NO_ANGLE 4
#define TSOP_BEST_TSOP_NO_STRENGTH 1
#define TSOP_MIN_IGNORE 5

#define TSOP_K1 12
#define TSOP_K2 1
#define TSOP_K3 1

#define READ_NUM 255
#define TSOP_MIN_IGNORE 5
#define TSOP_MAX_IGNORE 200

#define TSOP_FIRST_TSOP_WEIGHT 3
#define TSOP_SECOND_TSOP_WEIGHT 2

#define TSOP_FILTER_NOISE true
#define TSOP_FILTER_SURROUNDING true

// SPI

#define DATA_LENGTH_TSOP 2
#define DATA_LENGTH_LIGHT 1

// IMU

#define CORRECTION_ROTATION_MINIMUM 40
#define CORRECTION_ROTATION_MAXIMUM 80

#define IMU_CALIBRATION_TIME 1000
#define IMU_THRESHOLD 5

// Orbit

#define ORBIT_SHORT_STRENGTH 135
#define ORBIT_BIG_STRENGTH 110

#define ORBIT_SMALL_ANGLE 5
#define ORBIT_BIG_ANGLE 20

#define ORBIT_SPEED 255

#endif // CONFIG_H
