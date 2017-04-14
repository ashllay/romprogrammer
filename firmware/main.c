#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "flash.h"
#include "uart.h"
#include "../common/protocol.h"
#include "commands.h"


void init_hw(void) {
  // Disable all pull-ups
  MCUCR = PUD;

  DDRB = 0x3C;
  DDRC = 0x06;
  DDRD = 0x02;

  PORTB = 0x00;
  PORTC = 0x06;
  PORTD = 0x00;
}


void read_and_exec_command(void) {
  uint8_t buffer[140];

  uint8_t err = protocol_read_packet(sizeof(buffer), buffer);
  if(err != ERROR_NONE) {
    command_generate_error_reply(err);
  } else {
    command_execute(buffer);
  }
}


int main(void) {
  init_hw();
  uart_init();

  flash_set_write_enable(0);
  flash_set_output_enable(0);

  flash_set_write_mode();
  for(;;) {
    read_and_exec_command();
  }
}
