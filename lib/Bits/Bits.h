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
} Bits;

union BitsUnion {
    Bits bits;
    uint16_t bit16;
};

#endif // BITS_H
