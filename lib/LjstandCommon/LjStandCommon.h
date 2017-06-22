/* Library of common functions and macros.
 */

#ifndef LJSTANDCOMMON_H
#define LJSTANDCOMMON_H

#include <math.h>

#define TO_RADIANS 0.01745329251994329576923690768489

#define ARRAYLENGTH(array) (sizeof(array) / sizeof(array[0]))

#define ARRAYSHIFTDOWN(a, lower, upper){          \
    if (upper == (sizeof(a)/sizeof(a[0])) - 1){   \
        for (int q = upper - 1; q >= lower; q--){ \
            *(a + q + 1) = *(a + q); }            \
    } else{                                       \
        for (int q = upper; q >= lower; q--){     \
            *(a + q + 1) = *(a + q); }}}

// int len(int array[]);

// template <typename T,unsigned S>
// inline unsigned len(const T (&v)[S])

int mod(int x, int m);

double doubleMod(double x, double max);

bool angleIsInside(double angleBoundCounterClockwise, double angleBoundClockwise, double angleCheck);
double angleBetween(double angleCounterClockwise, double angleClockwise);

// int maxInt(int array[]);

// int sum(int array[]);
//
// int count(int el, int array[]);
//
// int find(int el, int array[]);
//
// int maxIndex(int array[]);

// void copyArray(int *toSet, int *row);

// int abs(int value);

int sign(int value);

int sign(double value);

double degreesToRadians(double degrees);

double doubleAbs(double value);

// void printArray(int *array, int length);

struct Vector2D {
    double x;
    double y;
};

struct Vector3D {
    double x;
    double y;
    double z;
};



#endif  // LJSTANDCOMMON_H
