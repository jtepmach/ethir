#include "ir.h"

#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

//#if defined(IR_RECV_TIMER1)  // defines for timer1 (16 bits)
#define SYSCLOCK F_CPU
#define USECPERTICK 50

// hardware PWM stuff
#define IR_RECV_ENABLE_INTR    (TIMSK1 = _BV(OCIE1A))
#define IR_RECV_DISABLE_INTR   (TIMSK1 = 0)
#define IR_RECV_INTR_NAME      TIMER1_COMPA_vect
#define IR_RECV_CONFIG_TICKS() ({ \
		TCCR1A = 0;   TCCR1B = _BV(WGM12) | _BV(CS10); \
		OCR1A = SYSCLOCK * USECPERTICK / 1000000;   TCNT1 = 0; })

unsigned char carrierFreq;
unsigned char periodHigh;
unsigned char periodLow;
unsigned long sigTime = 0;


void sendHex(unsigned char *sigArray, unsigned int sizeArray, unsigned char kHz) {
  if (carrierFreq != kHz) // freq. changed
    initSoftPWM(kHz);

  sigTime = micros();

  mark(HEADER_MARK);
  space(HEADER_SPACE);

  for (unsigned int i = 0; i < sizeArray; i++) {
    register unsigned char bitMask =  0x80;
    while (bitMask) {               // until bitMask bit has been shifted off rhs
      if (bitMask & sigArray[i]) {  // 1
        mark(ONE_MARK);
        space(ONE_SPACE);
      } else {                      // 0
        mark(ZERO_MARK);
        space(ZERO_SPACE);
      }
      bitMask = (unsigned char) bitMask >> 1; // shift right
    }
  }

  mark(TRAILER_MARK);
}


void initSoftPWM(unsigned char carrierFreq) {
  // 38khz, 30% duty cycle, at 16mhz
  periodHigh = 8;
  periodLow = 15;

	IR_RECV_CONFIG_TICKS();
  
  // 38khz, 30% duty cycle, at 8mhz
  //periodHigh = 8;
  //periodLow = 9;  // processing overhead adds to the low time
}


void mark(unsigned int duration) {
  sigTime += duration;

  while (micros() < sigTime); return;

  while (micros() < sigTime) {
    output_high(PORTD, txPinIR); if (periodHigh) delayMicroseconds(periodHigh);

    output_low(PORTD, txPinIR); if (periodLow) delayMicroseconds(periodLow);
  }
}

void space(unsigned int duration) {
  sigTime += duration;

  while (micros() < sigTime);
}
