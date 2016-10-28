/*
 * Header file to define pin values within the whole project
 * (e.g. TSOP_6)
 */

#include <Arduino.h>
#include <t3spi.h>

#ifndef PINS_H
#define PINS_H

// Light Sensors
// TODO: Update from schematic

#define LS_0 A1
#define LS_1 A2
#define LS_2 A3
#define LS_3 A4
#define LS_4 A5
#define LS_5 A6
#define LS_6 A7
#define LS_7 A8
#define LS_8 A9
#define LS_9 A10
#define LS_10 A11
#define LS_11 A12
#define LS_12 A13
#define LS_13 A14
#define LS_14 A15
#define LS_15 A16
#define LS_16 A17
#define LS_17 A18
#define LS_18 A19
#define LS_19 A20
#define LS_20 A21
#define LS_21 A22
#define LS_22 A23
#define LS_23 A24

#define TSOP_PWR_1 29
#define TSOP_PWR_2 30
#define TSOP_PWR_3 31
#define TSOP_PWR_4 32

// Motors
// TODO: update from schematic

#define MOTOR_RIGHT_IN1 0
#define MOTOR_RIGHT_IN2 1
#define MOTOR_RIGHT_PWM 2
#define MOTOR_RIGHT_SB 3

#define MOTOR_LEFT_IN1 4
#define MOTOR_LEFT_IN2 5
#define MOTOR_LEFT_PWM 6
#define MOTOR_LEFT_SB 7

#define MOTOR_BACK_RIGHT_IN1 8
#define MOTOR_BACK_RIGHT_IN2 16
#define MOTOR_BACK_RIGHT_PWM 20
#define MOTOR_BACK_RIGHT_SB 17

#define MOTOR_BACK_LEFT_IN1 21
#define MOTOR_BACK_LEFT_IN2 22
#define MOTOR_BACK_LEFT_PWM 23
#define MOTOR_BACK_LEFT_SB 24

// Communication
// TODO: update from schematic

#define MASTER_MOSI MOSI
#define MASTER_MISO MISO
#define MASTER_SCK ALT_SCK
#define MASTER_CS_TSOP CS0
#define MASTER_CS_LIGHT CS1
#define MASTER_CS_PIXY CS2

#define SLAVE_TSOP_MOSI MOSI
#define SLAVE_TSOP_MISO MISO
#define SLAVE_TSOP_SCK ALT_SCK
#define SLAVE_TSOP_CS CS0

#define SLAVE_LIGHT_MOSI MOSI
#define SLAVE_LIGHT_MISO MISO
#define SLAVE_LIGHT_SCK ALT_SCK
#define SLAVE_LIGHT_CS CS0

#endif // PINS_H
