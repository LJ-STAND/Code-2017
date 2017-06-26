#ifndef LINE_DATA_H
#define LINE_DATA_H

typedef struct LineData {
    double angle;
    double size;
    bool onField;

    LineData() {}
    LineData(double a, double s, bool o) : angle(a), size(s), onField(o) {}
} LineData;

#endif // LINE_DATA_H
