#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <BluetoothData.h>

class Bluetooth {
public:
    static void init() {
        Serial5.begin(9600);
        Serial5.setTimeout(15);
    }

    static void send(String data, int dataCode = BluetoothDataType::info) {
        Serial5.print("-" + String(dataCode) + ";" + data + "-");
    }

    static BluetoothData receive() {
        if (Serial5.available()) {
            String data = Serial5.readString();

            if (data.indexOf(';') != -1) {
                int splitIndex = data.indexOf(';');
                String typeString = data.substring(0, splitIndex);
                String valueString = data.substring(splitIndex + 1);

                int type = typeString.toInt();
                int value = valueString.toInt();

                return (BluetoothData) {static_cast<BluetoothDataType>(type), value, data};
            } else {
                return (BluetoothData) {BluetoothDataType::raw, 0, data};
            }
        }

        return (BluetoothData) {BluetoothDataType::noData, 0, ""};
    }
};

#endif
