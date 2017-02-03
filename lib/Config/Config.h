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

#define TSOP_LOOP_COUNT 200

// SPI

#define DATA_LENGTH_TSOP 2
#define DATA_LENGTH_LIGHT 1

// IMU

#define CORRECTION_ROTATION_MINIMUM 40
#define CORRECTION_ROTATION_MAXIMUM 80

#define IMU_CALIBRATION_TIME 1000
#define IMU_THRESHOLD 5

// Orbit

#define SHORT_STRENGTH 135
#define MEDIUM_STRENGTH 110

#define ORBIT_SMALL_ANGLE 5
#define ORBIT_BIG_ANGLE 20

#endif // CONFIG_H
