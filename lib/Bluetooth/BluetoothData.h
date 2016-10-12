#ifndef BLUETOOTHDATA_H
#define BLUETOOTHDATA_H

#include <Arduino.h>

enum BluetoothDataType: int {
    none,
    info,
    tsop,
    lightSensor
};

typedef struct BluetoothData {
    BluetoothDataType type;
    int value;
} BluetoothData;

#endif
