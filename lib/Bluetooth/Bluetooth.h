#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <BluetoothData.h>

class Bluetooth {
public:
    static void init() {
        Serial5.begin(9600);
        Serial5.setTimeout(50);
    }

    static void send(String data, int dataCode = BluetoothDataType::info) {
        String msg = String(dataCode) + ";" + data;
        Serial5.println(msg);
    }

    static BluetoothData receive() {
        if (Serial5.available()) {
            String data = Serial1.readString();

            int splitIndex = data.indexOf(';');
            String typeString = data.substring(0, splitIndex);
            String valueString = data.substring(splitIndex + 1);

            int type = typeString.toInt();
            int value = valueString.toInt();

            return (BluetoothData) {static_cast<BluetoothDataType>(type), value};
        }

        return (BluetoothData) {BluetoothDataType::none, 0};
    }
};

#endif
