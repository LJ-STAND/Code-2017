#ifndef DEBUG_CONTROLLER_H
#define DEBUG_CONTROLLER_H

#include <Pins.h>
#include <Arduino.h>
#include <Bluetooth.h>

class DebugController {
public:
    DebugController() {}
    void init();

    void setLEDBrightness(int green, int orange, int pink, int red, int white, int yellow);
    void toggleLEDs(bool green, bool orange, bool pink, bool red, bool white, bool yellow);
    void setAllLEDBrightness(int brightness);
    void toggleAllLEDs(bool on);

    void setGreenBrightness(int brightness);
    void toggleGreen(bool on);
    void setOrangeBrightness(int brightness);
    void toggleOrange(bool on);
    void setPinkBrightness(int brightness);
    void togglePink(bool on);
    void setRedBrightness(int brightness);
    void toggleRed(bool on);
    void setWhiteBrightness(int brightness);
    void toggleWhite(bool on);
    void setYellowBrightness(int brightness);
    void toggleYellow(bool on);

    void appSendTsops(int tsop, int strength);
    void appSendImu(double angle);
};

#endif
