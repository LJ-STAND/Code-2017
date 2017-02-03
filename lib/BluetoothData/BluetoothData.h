#ifndef BLUETOOTHDATA_H
#define BLUETOOTHDATA_H

#include <Arduino.h>

enum BluetoothDataType: int {
    noData,
    info,
    tsop,
    lightSensor
};

typedef struct BluetoothData {
    BluetoothDataType type;
    int value;
} BluetoothData;

#endif
