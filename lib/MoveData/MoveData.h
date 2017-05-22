#ifndef MOVE_DATA_H
#define MOVE_DATA_H

typedef struct MoveData {
    int angle = 0, speed = 0, rotation = 0;

    MoveData() {}
    MoveData(int moveAngle, int moveSpeed, int moveRotation) {
        angle = moveAngle;
        speed = moveSpeed;
        rotation = moveRotation;
    }
} MoveData;

#endif // MOVE_DATA_H
