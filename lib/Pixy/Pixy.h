//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This file is for defining the SPI-related classes.  It's called Pixy.h instead
// of Pixy_SPI.h because it's the default/recommended communication method
// with Arduino.  This class assumes you are using the ICSP connector to talk to
// Pixy from your Arduino.  For more information go to:
//
//http://cmucam.org/projects/cmucam5/wiki/Hooking_up_Pixy_to_a_Microcontroller_(like_an_Arduino)
//

#ifndef PIXY_H
#define PIXY_H

#include "TPixy.h"


#define PIXY_SYNC_BYTE              0x5a
#define PIXY_SYNC_BYTE_DATA         0x5b
#define PIXY_BUF_SIZE               16

template <class BufType> struct CircularQ
{
    CircularQ()
    {
        len = 0;
        writeIndex = 0;
        readIndex = 0;
    }

    bool read(BufType *c)
    {
        if (len)
        {
            *c = buf[readIndex++];
            len--;
            if (readIndex==PIXY_BUF_SIZE)
            readIndex = 0;
            return true;
        }
        else
        return false;
    }

    uint8_t freeLen()
    {
        return PIXY_BUF_SIZE-len;
    }

    bool write(BufType c)
    {
        if (freeLen()==0)
        return false;

        buf[writeIndex++] = c;
        len++;
        if (writeIndex==PIXY_BUF_SIZE)
        writeIndex = 0;
        return true;
    }

    BufType buf[PIXY_BUF_SIZE];
    uint8_t len;
    uint8_t writeIndex;
    uint8_t readIndex;
};

class LinkSPI
{
    volatile uint16_t dataIn[1];
    volatile uint16_t dataOut[1];

public:
    void init()
    {
    }

    uint16_t getWord()
    {
        // ordering is different (big endian) because Pixy is sending 16 bits through SPI
        // instead of 2 bytes in a 16-bit word as with I2C
        uint16_t w;

        if (inQ.read(&w))
        return w;

        return getWordHw();
    }

    uint8_t getByte()
    {
        dataOut[0] = 0x00;
        spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_PIXY);
        return dataIn[0];
    }

    int8_t send(uint8_t *data, uint8_t len)
    {
        int i;

        // check to see if we have enough space in our circular queue
        if (outQ.freeLen()<len)
        return -1;

        for (i=0; i<len; i++)
        outQ.write(data[i]);
        flushSend();
        return len;
    }

    void setArg(uint16_t arg)
    {
    }

private:
    uint16_t getWordHw()
    {
        // ordering is different (big endian) because Pixy is sending 16 bits through SPI
        // instead of 2 bytes in a 16-bit word as with I2C
        uint16_t w;
        uint8_t c, cout = 0;

        if (outQ.read(&cout)) {
            dataOut[0] = PIXY_SYNC_BYTE_DATA;
            spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_PIXY);
            w = dataIn[0];
        } else {
            dataOut[0] = PIXY_SYNC_BYTE;
            spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_PIXY);
            w = dataIn[0];
        }

        w <<= 8;
        dataOut[0] = cout;
        spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_PIXY);
        c = dataIn[0];
        w |= c;

        return w;
    }

    void flushSend()
    {
        uint16_t w;
        while(outQ.len)
        {
            w = getWordHw();
            inQ.write(w);
        }
    }

    // we need a little circular queues for both directions
    CircularQ<uint8_t> outQ;
    CircularQ<uint16_t> inQ;
};


typedef TPixy<LinkSPI> Pixy;

#endif
