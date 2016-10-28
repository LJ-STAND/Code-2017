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

#endif // CONFIG_H
