/* Library for interfacing with TSOP array
 */
#include "TSOPArray.h"

void TSOPArray::init() {
    // Set the correct pinmodes for all the TSOP pins
    pinMode(TSOP_PWR_1, OUTPUT);
    pinMode(TSOP_PWR_2, OUTPUT);
    pinMode(TSOP_PWR_3, OUTPUT);
    pinMode(TSOP_PWR_4, OUTPUT);

    for (int i = 0; i < TSOP_NUM; i++) {
        pinMode(TSOPPins[i], INPUT);
    }

    // Set up scaled sin/cos tables

    // double temp;
    // double temp_angle;
    //
    // for (int i = 0; i < TSOP_NUM; i++){
    //     // remember, angle = -bearing + 90 = -bearing + PI/2
    //     // angle = i * 2 * PI / TSOP_COUNT
    //     temp_angle = 1.5707963f - 6.283185307f * i / TSOP_NUM;
    //
    //     temp = cos(temp_angle) * 4095.0f;
    //     scaledCos[i] = temp;
    //
    //     temp = sin(temp_angle) * 4095.0f;
    //     scaledSin[i] = temp;
    // }

    on();
}

void TSOPArray::updateOnce() {
    // Read each TSOP once
    for (int i = 0; i < TSOP_NUM; i++) {
        tempValues[i] += digitalRead(TSOPPins[i]) ^ 1;
    }

    tsopCounter++;
}
void TSOPArray::on() {
    // Turn the TSOPs on
    digitalWrite(TSOP_PWR_1, HIGH);
    digitalWrite(TSOP_PWR_2, HIGH);
    digitalWrite(TSOP_PWR_3, HIGH);
    digitalWrite(TSOP_PWR_4, HIGH);
}

void TSOPArray::off() {
    // Turn the TSOPs off
    digitalWrite(TSOP_PWR_1, LOW);
    digitalWrite(TSOP_PWR_2, LOW);
    digitalWrite(TSOP_PWR_3, LOW);
    digitalWrite(TSOP_PWR_4, LOW);
}

void TSOPArray::unlock() {
    // TSOPs become overly sensitive ("locked") if not turned off and on often
    off();
    delay(TSOP_UNLOCK_DELAY);
    on();
}

void TSOPArray::finishRead() {
    // Complete a reading of the TSOPs after a certain amount of individual readings, TSOP values are now stored in the values array until the next complete read
    tsopCounter = 0;
    for (int i = 0; i < TSOP_NUM; i++) {
        #if DEBUG_TSOP
            Serial.print(tempValues[i]);
            if (i != TSOP_NUM - 1) {
                Serial.print(", ");
            } else {
                Serial.println();
            }
        #endif

        values[i] = tempValues[i];
        tempValues[i] = 0;
        filteredValues[i] = 0;
        sortedFilteredValues[i] = 0;
        indexes[i] = 0;
    }

    sortFilterValues();
    calculateAngleSimple();
    calculateAngle(TSOP_BEST_TSOP_NO_ANGLE);
    calculateStrengthSimple();
    calculateStrength(TSOP_BEST_TSOP_NO_STRENGTH);
}

void TSOPArray::sortFilterValues() {
    // Remove noise
    for (int i = 0; i < TSOP_NUM; i++) {
        #if TSOP_FILTER_NOISE
            if (values[i] < TSOP_MIN_IGNORE || values[i] > TSOP_MAX_IGNORE) {
                tempFilteredValues[i] = 0;
            } else {
                tempFilteredValues[i] = values[i];
            }
        #else
            tempFilteredValues[i] = values[i];
        #endif
    }

    // A rather efficient way to filter data by scoring each data by the TSOP by it's adjacent TSOPs
    for (int i = 0; i < TSOP_NUM; i++) {
        #if TSOP_FILTER_SURROUNDING
            int temp = TSOP_K1 * tempFilteredValues[i] + TSOP_K2 * (tempFilteredValues[mod(i + 1, TSOP_NUM)] + tempFilteredValues[mod(i - 1, TSOP_NUM)]) + TSOP_K3 * (tempFilteredValues[mod(i + 2, TSOP_NUM)] + tempFilteredValues[mod(i - 2, TSOP_NUM)]);
        #else
            int temp = tempFilteredValues[i] << 4;
        #endif

        // TSOP_K1 + 2 * TSOP_K2 + 2 * TSOP_K3 = 16 so we must divide the value by 16
        filteredValues[i] = temp >> 4;
    }

    /* Sort the TSOP values from greatest to least in sortedFilteredValues
     * and sort the TSOP indexes from greatest to least strength in indexes
     */
    for (int i = 0; i < TSOP_NUM; i++) {
        for (int j = 0; j < TSOP_NUM; j++) {
            if (filteredValues[i] > sortedFilteredValues[j]) {
                // We've found our place!
                // Shift elements from index j down
                if (j <= i) {
                    // Make sure we only shift what is needed
                    ARRAYSHIFTDOWN(sortedFilteredValues, j, i);
                    ARRAYSHIFTDOWN(indexes, j, i);
                }

                sortedFilteredValues[j] = filteredValues[i];
                indexes[j] = i;
                break;
            }
        }
    }
}

void TSOPArray::calculateAngleSimple() {
    if (sortedFilteredValues[0] <= TSOP_MIN_IGNORE) {
        simpleAngle = -1;
    } else {
        simpleAngle = indexes[0] * 360 / TSOP_NUM;
    }
}

void TSOPArray::calculateStrengthSimple() {
    simpleStrength = sortedFilteredValues[0];
}

void TSOPArray::calculateAngle(int n) {
    // Cartesian addition of best n TSOPs
    // int x = 0;
    // int y = 0;
    // for (int i = 0; i < n; i++){
    //     // convert vector to cartesian (remember that each bitshift << is *2)
    //     x += sortedFilteredValues[i] * scaledCos[indexes[i]] >> 12;
    //     y += sortedFilteredValues[i] * scaledSin[indexes[i]] >> 12;
    // }
    // if (x == 0 && y == 0){
    //     // When vectors sum to (0, 0), we're in trouble. We've got some dodgy data
    //     angle = 0;
    // }
    // else{
    //     angle = 90 - (57.3 * atan2(y, x));
    // }
    //
    // if (angle < 0){
    //     angle += 360;
    // }
    // if (angle < 0){
    //     angle += 360;
    // }

    /* Averages the indexes of the best n TSOPs. Best TSOP is weighted
     * TSOP_FIRST_TSOP_WEIGHT and second is weighted TSOP_SECOND_TSOP_WEIGHT.
     * Rest are unweighted
     */
    int best = indexes[0];
    int relIndexes[TSOP_NUM] = {0}; // indexes relative to best TSOP

    for (int i = 0; i < TSOP_NUM; i++) {
        relIndexes[i] = indexes[i] - best;
        if (relIndexes[i] < (1 - TSOP_NUM / 2)) {
            relIndexes[i] += TSOP_NUM;
        }

        if (relIndexes[i] > (TSOP_NUM / 2)) {
            relIndexes[i] -= TSOP_NUM;
        }
    }

    int relIndexTotal = TSOP_SECOND_TSOP_WEIGHT * relIndexes[1];
    for (int i = 2; i < n; i++){
        relIndexTotal += relIndexes[i];
    }

    double relIndexAverage = (double) relIndexTotal / (double)(n + TSOP_FIRST_TSOP_WEIGHT + TSOP_SECOND_TSOP_WEIGHT - 2);

    double index = best + relIndexAverage;

    index = doubleMod(index, (double) TSOP_NUM);


    if (sortedFilteredValues[0] <= TSOP_MIN_IGNORE) {
        angle = -1;
    } else {
        angle = index * 360.0 / (double) TSOP_NUM;
    }

}

void TSOPArray::calculateStrength(int n) {
    // Return average of strongest n TSOPs
    // could also have a limit, that is, only TSOPs > limit are averaged (team pi used 50)
    int strengthTotal = 0;
    for (int i = 0; i < n; i++) {
        strengthTotal += sortedFilteredValues[i];
    }

    strength = (double) strengthTotal / n;
}

int TSOPArray::getAngle() {
    return angle == -1 ? TSOP_NO_BALL : angle;
}

int TSOPArray::getStrength() {
    return strength;
}

int TSOPArray::getSimpleStrength() {
    return simpleStrength;
}
