/* Library for interfacing with tsop array
 */
#include "TsopArray.h"

TsopArray::TsopArray(){
    // empty
}

void TsopArray::tsopArraySetup(){
    // set the correct pinmodes for all the tsop pins
    pinMode(UNLOCK_PIN, OUTPUT);

    for (int i = 0; i < TSOP_NUM; i++){
        pinMode(tsopPins[i], INPUT);
    }

    // set up scaled sin/cos tables

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

void TsopArray::updateOnce(){
    // read each TSOP once
    for (int i = 0; i < TSOP_NUM; i++){
        tempValues[i] += digitalRead(tsopPins[i]) ^ 1;
    }
    tsopCounter++;
}
void TsopArray::on(){
    // turn the TSOPs on
    digitalWrite(UNLOCK_PIN, HIGH);
}

void TsopArray::off(){
    // turn the TSOPs off
    digitalWrite(UNLOCK_PIN, LOW);
}

void TsopArray::unlockTsops(){
    // TSOPs become overly sensitive ("locked") if not turned off and on often
    off();
    delay(UNLOCK_DELAY);
    on();
}

void TsopArray::finishRead(){
    // complete a reading of the tsops after READ_NUM individual readings, TSOP values are now stored in the values array until the next complete read
    tsopCounter = 0;
    for(int i = 0; i < TSOP_NUM; i++){
        values[i] = tempValues[i];
        tempValues[i] = 0;
        filteredValues[i] = 0;
        sortedFilteredValues[i] = 0;
        indexes[i] = 0;
    }

    sortFilterValues();
    getAngleSimple();
    getAngle(BEST_TSOP_NO_ANGLE);
    getStrengthSimple();
    getStrength(BEST_TSOP_NO_STRENGTH);
}

void TsopArray::sortFilterValues(){
    // remove noise
    for(int i = 0; i < TSOP_NUM; i++){
        #if TSOP_FILTER_NOISE
            if(values[i] < MIN_IGNORE_TSOPS || values[i] > MAX_IGNORE_TSOPS){
                tempFilteredValues[i] = 0;
            } else {
                tempFilteredValues[i] = values[i];
            }
        #else
            tempFilteredValues[i] = values[i];
        #endif
    }

    // a rather efficient way to filter data by scoring each data by the tsop by it's adjacent tsops
    for (int i = 0; i < TSOP_NUM; i++){
        #if TSOP_FILTER_SURROUNDING
            int temp = TSOP_K1 *  tempFilteredValues[i] + TSOP_K2 *             (tempFilteredValues[mod(i - 1, TSOP_NUM)] + tempFilteredValues[mod(i - 1, TSOP_NUM)]) + TSOP_K3 * (tempFilteredValues[mod(i - 2, TSOP_NUM)] + tempFilteredValues[mod(i - 2, TSOP_NUM)]);
        #else
            int temp = tempFilteredValues[i] << 4;
        #endif

        // TSOP_K1 + 2 * TSOP_K2 + 2 * TSOP_K3 = 16 so we must divide the value by 16

        filteredValues[i] = temp >> 4;
    }

    // sort the TSOP values from greatest to least in sortedFilteredValues and sort the TSOP indexes from greatest to least strength in indexes
    for (int i = 0; i < TSOP_NUM; i++){
        for (int j = 0; j < TSOP_NUM; j++){
            if (filteredValues[i] > sortedFilteredValues[j]){
                // we've found our place!
                // shift elements from index j down
                if (j <= i){
                    // make sure we only shift what is needed
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

void TsopArray::getAngleSimple(){
    if (sortedFilteredValues[0] <= 5){
        simpleAngle = -1;
    } else {
        simpleAngle = indexes[0] * 360 / TSOP_NUM;
    }
}

void TsopArray::getStrengthSimple(){
    simpleStrength = sortedFilteredValues[0];
}

void TsopArray::getAngle(int n){
    // Cartesian addition of best n tsops
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

    // averages the indexes of the best n TSOPs. Best TSOP is weight FIRST_TSOP_WEIGHT and second is weighted SECOND_TSOP_WEIGHT. Rest are unweighted
    // could weight them by their strength or something like that?
    int best = indexes[0];
    int relIndexes[TSOP_NUM] = {0}; // indexes relative to best tsop

    for (int i = 0; i < TSOP_NUM; i++){
        relIndexes[i] = indexes[i] - best;
        if (relIndexes[i] < -5) {
            relIndexes[i] += 12;
        }
        if (relIndexes[i] > 6) {
            relIndexes[i] -= 12;
        }
    }

    int relIndexTotal = SECOND_TSOP_WEIGHT * relIndexes[1];
    for (int i = 2; i < n; i++){
        relIndexTotal += relIndexes[i];
    }

    double relIndexAv;

    relIndexAv = (double)relIndexTotal / (double)(n + FIRST_TSOP_WEIGHT + SECOND_TSOP_WEIGHT - 2);

    double index = best + relIndexAv;

    index = doubleMod(index, (double)TSOP_NUM);


    if (sortedFilteredValues[0] <= 5){
        angle = -1;
    } else {
        angle = index * 360.0 / (double)TSOP_NUM;
    }

}

void TsopArray::getStrength(int n){
    // return average of strongest n tsops
    // could also have a limit, that is, only tsops > limit are averaged (team pi used 50)
    int strTotal = 0;
    for (int i = 0; i < n; i++){
        strTotal += sortedFilteredValues[i];
    }



    strength = (double)strTotal / n;
}
