#ifndef DEBUG_CONTROLLER_H
#define DEBUG_CONTROLLER_H

#include <Pins.h>
#include <Arduino.h>
#include <Bluetooth.h>
#include <Bits.h>
#include <Config.h>
#include <Timer.h>
#include <BluetoothData.h>

class DebugController {
public:
    DebugController() {}
    void init();

    void setLEDBrightness(int orange, int white, int yellow, int blue, int green, int red);
    void toggleLEDs(bool orange, bool white, bool yellow, bool blue, bool green, bool red);
    void setAllLEDBrightness(int brightness);
    void toggleAllLEDs(bool on);

    void setOrangeBrightness(int brightness);
    void toggleOrange(bool on);
    void setWhiteBrightness(int brightness);
    void toggleWhite(bool on);
    void setYellowBrightness(int brightness);
    void toggleYellow(bool on);
    void setBlueBrightness(int brightness);
    void toggleBlue(bool on);
    void setGreenBrightness(int brightness);
    void toggleGreen(bool on);
    void setRedBrightness(int brightness);
    void toggleRed(bool on);

    void rgb(int r, int g, int b);
    void BBC();
    void flashAllLEDs(int n, int delayTime);

    void appSendTSOPs(int tsop, int strength);
    void appSendIMU(double angle);
    void appSendTSOPs(double angle);
    void appSendOrbitAngle(double angle);
    void appSendString(String string);
    void appSendLightSensors(uint16_t first16Bit, uint16_t second16Bit);
    void appSendPixy(double x, double y, double width, double height);
};

#endif
