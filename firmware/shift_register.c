#include <avr/io.h>
#include "shift_register.h"
#include "bits.h"

#define SER_DPORT   PORTB
#define SER_CLKPORT PORTB
#define SER_OPORT   PORTB
#define SER_DBIT    4
#define SER_CLKBIT  2
#define SER_OBIT    3

void ser_clk(void) {
  trigger(SER_CLKPORT, SER_CLKBIT);
}


void ser_latch(void) {
  trigger(SER_OPORT, SER_OBIT);
}


void ser_out(uint8_t bit) {
  set(SER_DPORT, SER_DBIT, bit);
  ser_clk();
}


