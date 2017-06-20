#ifndef LIGHT_SENSOR_ARRAY_H
#define LIGHT_SENSOR_ARRAY_H

#include <Arduino.h>
#include <Pins.h>
#include <LightSensorData.h>
#include <LightSensor.h>
#include <LightSensorCluster.h>
#include <LinePosition.h>
#include <Bits.h>
#include <LJSTANDCommon.h>

class LightSensorArray {
public:
    LightSensorArray();

    void init();

    void read();
    void calculatePostion();
    LinePosition getLinePosition();

    void getClusters(LightSensorData lightData, bool doneClusters2);
    void getClusters2();
    void calculatePositionClusters();

    uint16_t getFirst16Bit();
    uint16_t getSecond16Bit();

    void updateHeading(int heading);

    LightSensorData data;
    LinePosition position;
    LightSensor sensors[24];
    LightSensorCluster cluster1, cluster2, cluster3 = LightSensorCluster(0.0, 0);

private:
    int arrayOffset = 0;
};

#endif // LIGHT_SENSOR_ARRAY_H
