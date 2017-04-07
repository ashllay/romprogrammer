#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "flash.h"
#include "uart.h"
#include "protocol.h"
#include "commands.h"


void init_hw(void) {
  // Disable all pull-ups
  MCUCR = PUD;

  DDRB = 0x1C;
  DDRC = 0x03;
  DDRD = 0x02;

  PORTB = 0x00;
  PORTC = 0x03;
  PORTD = 0x00;
}



void read_and_exec_command(void) {
  uint8_t buffer[256];

  uint8_t err = protocol_read_command(buffer);
  if(err != ERROR_NONE) {
    protocol_generate_error_reply(err);
  } else {
    command_execute(buffer);
  }
}


int main(void) {
  init_hw();
  uart_init();

  DDRD |= 0x02;
  DDRB |= 0x20;

  for(;;) {
    read_and_exec_command();
  }
}






