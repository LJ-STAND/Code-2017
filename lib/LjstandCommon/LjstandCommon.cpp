#include "LJSTANDCommon.h"

// int len(int array[]){
//     return ARRAYLENGTH(array);
// }

// template <typename T,unsigned S>
// inline unsigned len(const T (&v)[S]) { return S; }

int mod(int x, int m) {
    int r = x % m;
    return r < 0 ? r + m : r;
}

double doubleMod(double x, double m) {
    double r = fmod(x, m);
    return r < 0 ? r + m : r;
}

bool angleIsInside(double angleBoundCounterClockwise, double angleBoundClockwise, double angleCheck) {
    if (angleBoundCounterClockwise < angleBoundClockwise) {
        return (angleBoundCounterClockwise < angleCheck && angleCheck < angleBoundClockwise);
    } else {
        return (angleBoundCounterClockwise < angleCheck || angleCheck < angleBoundClockwise);
    }
}

// int maxInt(int array[]) {
//     int bestvalue = array[0];
//     for (int i = 1; i < ARRAYLENGTH(array); i++) {
//         if (array[i] > bestvalue) bestvalue = array[i];
//     }
//     return bestvalue;
// }

// int sum(int array[]) {
//     int total = 0;
//     for (int i = 0; i < ARRAYLENGTH(array); i++) total += array[i];
//     return total;
// }
//
// int count(int el, int array[]) {
//     int count = 0;
//     for (int i = 0; i < ARRAYLENGTH(array); i++) {
//         if (array[i] == el) count+= 1;
//     }
//     return count;
// }
//
// int find(int el, int array[]) {
//     for (int i = 0; i < ARRAYLENGTH(array); i++) {
//         if (array[i] == el) return i;
//     }
//     return -1;
// }
//
// int maxIndex(int array[]) {
//     int maxval = maxInt(array);
//     int maxvalindex = find(maxval, array);
//     return maxvalindex;
// }
//
// void copyArray(int *toSet, int *row) {
//     for (int i=0; i < ARRAYLENGTH(row); i++) toSet[i] = row[i];
// }

// int abs(int value) {
//     return value * sign(value);
// }

int sign(int value) {
    return value >= 0 ? 1 : -1;
}

int sign(double value) {
    return value >= 0 ? 1 : -1;
}

double degreesToRadians(double degrees) {
    return degrees * TO_RADIANS;
}

double doubleAbs(double value) {
    return value * sign(value);
}
