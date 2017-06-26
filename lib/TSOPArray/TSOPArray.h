/* Library for interfacing with TSOP array
 */

#ifndef TSOP_ARRAY_H
#define TSOP_ARRAY_H

#include <Arduino.h>

#include <Common.h>
#include <Config.h>
#include <Pins.h>

class TSOPArray {
public:
    TSOPArray() {}
    void init();
    void updateOnce();
    void on();
    void off();
    void unlock();
    void finishRead();
    void sortFilterValues();
    void calculateAngleSimple();
    void calculateAngle(int n);
    void calculateStrengthSimple();
    void calculateStrength(int n);
    int getAngle();
    int getStrength();
    int getSimpleStrength();

    int values[TSOP_NUM] = {0};
    int filteredValues[TSOP_NUM] = {0};
    int sortedFilteredValues[TSOP_NUM] = {0};
    int indexes[TSOP_NUM] = {0};
    int tsopCounter = 0;

private:
    int angle = 0;
    int simpleAngle = 0;
    int strength = 0;
    int simpleStrength = 0;

    int tempValues[TSOP_NUM] = {0};
    int tempFilteredValues[TSOP_NUM] = {0};
    int TSOPPins[TSOP_NUM] = {TSOP_0, TSOP_1, TSOP_2, TSOP_3, TSOP_4, TSOP_5, TSOP_6, TSOP_7, TSOP_8, TSOP_9, TSOP_10, TSOP_11, TSOP_12, TSOP_13, TSOP_14, TSOP_15, TSOP_16, TSOP_17, TSOP_18, TSOP_19, TSOP_20, TSOP_21, TSOP_22, TSOP_23};
    // int scaledSin[TSOP_NUM] = {0};
    // int scaledCos[TSOP_NUM] = {0};
};

#endif // TSOP_ARRAY_H
