#include <avr/io.h>
#include <IRLib.h>

#ifdef PANA  // PANASONIC

#define HEADER_MARK 3500
#define HEADER_SPACE 1750
#define ONE_MARK 435
#define ZERO_MARK 435
#define ONE_SPACE 1300
#define ZERO_SPACE 435
#define TRAILER_MARK 435

#else        // CARRIER

#define HEADER_MARK 4400
#define HEADER_SPACE 4400
#define ONE_MARK 543
#define ZERO_MARK 543
#define ONE_SPACE 1623
#define ZERO_SPACE 543
#define TRAILER_MARK 543

#endif

#define txPinIR   3   //IR carrier output, must be on PORTD

void sendHex(unsigned char *sigArray, unsigned int sizeArray, unsigned char kHz);
void initSoftPWM(unsigned char carrierFreq);
void mark(unsigned int mLen);
void space(unsigned int sLen);
void delay_ms(uint8_t ms);
