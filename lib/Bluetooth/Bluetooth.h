#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <BluetoothData.h>

class Bluetooth {
public:
    static void init() {
        Serial1.begin(9600);
        Serial1.setTimeout(50);
    }

    static void send(String data, int dataCode = BluetoothDataType::info) {
        String msg = String(dataCode) + ";" + data;
        Serial.println(msg);
    }

    static BluetoothData receive() {
        if (Serial1.available()) {
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
