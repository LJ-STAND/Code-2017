#ifndef BLUETOOTHDATA_H
#define BLUETOOTHDATA_H

#include <Arduino.h>

enum BluetoothDataType: int {
    noData,
    info,
    tsop,
    lightSensor,
    compass,
    raw,
    btLinePosition,
    btRobotPosition,
    settings,
    orbitAngle,
    goal
};

typedef struct BluetoothData {
    BluetoothDataType type;
    int value;
    String string;

    BluetoothData() {}
    BluetoothData(BluetoothDataType t, int v, String s) : type(t), value(v), string(s) {}
} BluetoothData;

#endif
