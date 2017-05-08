/*
 * Header file to define pin values within the whole project
 * (e.g. TSOP_6)
 */

#include <Arduino.h>
#include <t3spi.h>

#ifndef PINS_H
#define PINS_H

// Light Sensors

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

// Light Gate

#define LIGHT_GATE A20

// Motors

#define MOTOR_RIGHT_IN1 0
#define MOTOR_RIGHT_IN2 1
#define MOTOR_RIGHT_PWM 2
#define MOTOR_RIGHT_SB 3
#define MOTOR_RIGHT_ANGLE 55
#define MOTOR_RIGHT_REVERSED true

#define MOTOR_LEFT_IN1 4
#define MOTOR_LEFT_IN2 5
#define MOTOR_LEFT_PWM 6
#define MOTOR_LEFT_SB 7
#define MOTOR_LEFT_ANGLE 305
#define MOTOR_LEFT_REVERSED true

#define MOTOR_BACK_RIGHT_IN1 8
#define MOTOR_BACK_RIGHT_IN2 16
#define MOTOR_BACK_RIGHT_PWM 20
#define MOTOR_BACK_RIGHT_SB 17
#define MOTOR_BACK_RIGHT_ANGLE 130
#define MOTOR_BACK_RIGHT_REVERSED true

#define MOTOR_BACK_LEFT_IN1 21
#define MOTOR_BACK_LEFT_IN2 22
#define MOTOR_BACK_LEFT_PWM 23
#define MOTOR_BACK_LEFT_SB 24
#define MOTOR_BACK_LEFT_ANGLE 230
#define MOTOR_BACK_LEF_REVERSED true

// Communication

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

// LEDs

#define LED_ORANGE 30
#define LED_WHITE 29
#define LED_YELLOW 35
#define LED_BLUE 36
#define LED_GREEN 37
#define LED_RED 38

// TSOPs

#define TSOP_0 0
#define TSOP_1 1
#define TSOP_2 2
#define TSOP_3 3
#define TSOP_4 4
#define TSOP_5 5
#define TSOP_6 6
#define TSOP_7 7
#define TSOP_8 8
#define TSOP_9 9
#define TSOP_10 15
#define TSOP_11 16
#define TSOP_12 17
#define TSOP_13 18
#define TSOP_14 19
#define TSOP_15 20
#define TSOP_16 21
#define TSOP_17 22
#define TSOP_18 23
#define TSOP_19 24
#define TSOP_20 25
#define TSOP_21 26
#define TSOP_22 27
#define TSOP_23 28

#endif // PINS_H
