#include "DebugController.h"

void DebugController::init() {
    pinMode(LED_ORANGE, OUTPUT);
    pinMode(LED_WHITE, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
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
    analogWrite(LED_ORANGE, constrain(brightness, 0, 255));
}

void DebugController::toggleOrange(bool on) {
    digitalWrite(LED_ORANGE, on);
}

void DebugController::setWhiteBrightness(int brightness) {
    analogWrite(LED_WHITE, constrain(brightness, 0, 255));
}

void DebugController::toggleWhite(bool on) {
    digitalWrite(LED_WHITE, on);
}

void DebugController::setYellowBrightness(int brightness) {
    analogWrite(LED_YELLOW, constrain(brightness, 0, 255));
}

void DebugController::toggleYellow(bool on) {
    digitalWrite(LED_YELLOW, on);
}

void DebugController::setBlueBrightness(int brightness) {
    analogWrite(LED_BLUE, constrain(brightness, 0, 255));
}

void DebugController::toggleBlue(bool on) {
    digitalWrite(LED_BLUE, on);
}

void DebugController::setGreenBrightness(int brightness) {
    analogWrite(LED_GREEN, constrain(brightness, 0, 255));
}

void DebugController::toggleGreen(bool on) {
    digitalWrite(LED_GREEN, on);
}

void DebugController::setRedBrightness(int brightness) {
    analogWrite(LED_RED, constrain(brightness, 0, 255));
}

void DebugController::toggleRed(bool on) {
    digitalWrite(LED_RED, on);
}
