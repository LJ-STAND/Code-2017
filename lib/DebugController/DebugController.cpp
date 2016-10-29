#include "DebugController.h"

void DebugController::init() {
    pinMode(LED_1_GREEN, OUTPUT);
    pinMode(LED_2_ORANGE, OUTPUT);
    pinMode(LED_3_PINK, OUTPUT);
    pinMode(LED_4_RED, OUTPUT);
    pinMode(LED_5_WHITE, OUTPUT);
    pinMode(LED_6_YELLOW, OUTPUT);
}

void DebugController::setLEDBrightness(int green, int orange, int pink, int red, int white, int yellow) {
    setGreenBrightness(green);
    setOrangeBrightness(orange);
    setPinkBrightness(pink);
    setRedBrightness(red);
    setWhiteBrightness(white);
    setYellowBrightness(yellow);
}

void DebugController::toggleLEDs(bool green, bool orange, bool pink, bool red, bool white, bool yellow) {
    toggleGreen(green);
    toggleOrange(orange);
    togglePink(pink);
    toggleRed(red);
    toggleWhite(white);
    toggleYellow(yellow);
}

void DebugController::setAllLEDBrightness(int brightness) {
    setGreenBrightness(brightness);
    setOrangeBrightness(brightness);
    setPinkBrightness(brightness);
    setRedBrightness(brightness);
    setWhiteBrightness(brightness);
    setYellowBrightness(brightness);
}

void DebugController::toggleAllLEDs(bool on) {
    toggleGreen(on);
    toggleOrange(on);
    togglePink(on);
    toggleRed(on);
    toggleWhite(on);
    toggleYellow(on);
}

void DebugController::setGreenBrightness(int brightness) {
    analogWrite(LED_1_GREEN, constrain(brightness, 0, 255));
}

void DebugController::toggleGreen(bool on) {
    digitalWrite(LED_1_GREEN, on);
}

void DebugController::setOrangeBrightness(int brightness) {
    analogWrite(LED_2_ORANGE, constrain(brightness, 0, 255));
}

void DebugController::toggleOrange(bool on) {
    digitalWrite(LED_2_ORANGE, on);
}

void DebugController::setPinkBrightness(int brightness) {
    analogWrite(LED_3_PINK, constrain(brighness, 0, 255));
}

void DebugController::togglePink(bool on) {
    digitalWrite(LED_3_PINK, on);
}

void DebugController::setRedBrightness(int brightness) {
    analogWrite(LED_4_RED, constrain(brightnes, 0, 255));
}

void DebugController::toggleRed(bool on) {
    digitalWrite(LED_4_RED, on);
}

void DebugController::setWhiteBrightness(int brightness) {
    analogWrite(LED_5_WHITE, constrain(brightness, 0, 255));
}

void DebugController::toggleWhite(bool on) {
    digitalWrite(LED_5_WHITE, on);
}

void DebugController::setYellowBrightness(int brightness) {
    analogWrite(LED_6_YELLOW, constrain(brightness, 0, 255));
}

void DebugController::toggleYellow(bool on) {
    digitalWrite(LED_6_YELLOW, on);
}
