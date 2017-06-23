#ifndef BALL_DATA_H
#define BALL_DATA_H

typedef struct BallData {
    int angle;
    int strength;

    BallData() {}
    BallData(int a, int s) : angle(a), strength(s) {} 
} BallData;

#endif // BALL_DATA_H
