#include "DebugController.h"

void DebugController::init() {
    pinMode(LED_1_ORANGE, OUTPUT);
    pinMode(LED_2_WHITE, OUTPUT);
    pinMode(LED_3_YELLOW, OUTPUT);
    pinMode(LED_4_BLUE, OUTPUT);
    pinMode(LED_5_GREEN, OUTPUT);
    pinMode(LED_6_RED, OUTPUT);
}

void DebugController::setLEDBrightness(int orange, int white, int yellow, int blue, int green, int red) {
    setOrangeBrightness(orange);
    setWhiteBrightness(white);
    setYellowBrightness(yellow);
    setBlueBrightness(blue);
    setGreenBrightness(green);
    setRedBrightness(red);
}

void DebugController::toggleLEDs(bool orange, bool white, bool yellow, bool blue, bool green, bool red) {
    toggleOrange(orange);
    toggleWhite(white);
    toggleYellow(yellow);
    toggleBlue(blue);
    toggleGreen(green);
    toggleRed(red);
}

void DebugController::setAllLEDBrightness(int brightness) {
    setOrangeBrightness(brightness);
    setWhiteBrightness(brightness);
    setYellowBrightness(brightness);
    setBlueBrightness(brightness);
    setGreenBrightness(brightness);
    setRedBrightness(brightness);
}

void DebugController::toggleAllLEDs(bool on) {
    toggleOrange(on);
    toggleWhite(on);
    toggleYellow(on);
    toggleBlue(on);
    toggleGreen(on);
    toggleRed(on);
}

void DebugController::setOrangeBrightness(int brightness) {
    analogWrite(LED_1_ORANGE, constrain(brightness, 0, 255));
}

void DebugController::toggleOrange(bool on) {
    digitalWrite(LED_1_ORANGE, on);
}

void DebugController::setWhiteBrightness(int brightness) {
    analogWrite(LED_2_WHITE, constrain(brightness, 0, 255));
}

void DebugController::toggleWhite(bool on) {
    digitalWrite(LED_2_WHITE, on);
}

void DebugController::setYellowBrightness(int brightness) {
    analogWrite(LED_3_YELLOW, constrain(brightness, 0, 255));
}

void DebugController::toggleYellow(bool on) {
    digitalWrite(LED_3_YELLOW, on);
}

void DebugController::setBlueBrightness(int brightness) {
    analogWrite(LED_4_BLUE, constrain(brightness, 0, 255));
}

void DebugController::toggleBlue(bool on) {
    digitalWrite(LED_4_BLUE, on);
}

void DebugController::setGreenBrightness(int brightness) {
    analogWrite(LED_5_GREEN, constrain(brightness, 0, 255));
}

void DebugController::toggleGreen(bool on) {
    digitalWrite(LED_5_GREEN, on);
}

void DebugController::setRedBrightness(int brightness) {
    analogWrite(LED_6_RED, constrain(brightness, 0, 255));
}

void DebugController::toggleRed(bool on) {
    digitalWrite(LED_6_RED, on);
}
