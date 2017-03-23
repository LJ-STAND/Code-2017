#ifndef BITS_H
#define BITS_H

typedef struct Bits {
    unsigned b0:1;
    unsigned b1:1;
    unsigned b2:1;
    unsigned b3:1;
    unsigned b4:1;
    unsigned b5:1;
    unsigned b6:1;
    unsigned b7:1;
    unsigned b8:1;
    unsigned b9:1;
    unsigned b10:1;
    unsigned b11:1;
    unsigned b12:1;
    unsigned b13:1;
    unsigned b14:1;
    unsigned b15:1;

    void boolArray(bool* array) {
        array[0] = (bool)b0;
        array[1] = (bool)b1;
        array[2] = (bool)b2;
        array[3] = (bool)b3;
        array[4] = (bool)b4;
        array[5] = (bool)b5;
        array[6] = (bool)b6;
        array[7] = (bool)b7;
        array[8] = (bool)b8;
        array[9] = (bool)b9;
        array[10] = (bool)b10;
        array[11] = (bool)b11;
        array[12] = (bool)b12;
        array[13] = (bool)b13;
        array[14] = (bool)b14;
        array[15] = (bool)b15;
    }
} Bits;

union BitsUnion {
    Bits bits;
    uint16_t bit16;
};

#endif // BITS_H
