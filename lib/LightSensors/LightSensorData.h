#ifndef LIGHT_SENSOR_DATA_H
#define LIGHT_SENSOR_DATA_H

typedef struct LightSensorData {
    // Front sensor
    bool ls0;

    // First quadrant (front right)
    bool ls1, ls2, ls3, ls4, ls5;

    // Right sensor
    bool ls6;

    // Second quadrant (back right)
    bool ls7, ls8, ls9, ls10, ls11;

    // Back sensor
    bool ls12;

    // Third quadrant (back left)
    bool ls13, ls14, ls15, ls16, ls17;

    // Left sensor
    bool ls18;

    // Fourth quadrant (front left)
    bool ls19, ls20, ls21, ls22, ls23;
} LightSensorData;

#endif // LIGHT_SENSOR_DATA_H
