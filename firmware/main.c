#include <avr/io.h>

int main(void) {
  // Disable all pull-ups
  MCUCR = PUD;
}
