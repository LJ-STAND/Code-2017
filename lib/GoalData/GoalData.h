#ifndef GOALDATA_H
#define GOALDATA_H

enum GoalStatus: int {
    invisible,
    visible,
    blocked
};

typedef struct GoalData {
    double distance;
    int angle;
    GoalStatus status;
} GoalData;

#endif // GOALDATA_H
