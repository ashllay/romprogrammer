#include <avr/io.h>
#include "uart.h"

#define F_CPU 16000000
#define BAUD  115200
#define UBRR F_CPU/16/BAUD-1


void uart_init(void) {
  UBRR0H = (uint8_t)(UBRR >> 8);
  UBRR0L = (uint8_t)UBRR;
  UCSR0B = 0x18; // Enable TX, RX
  UCSR0C = 0x06; // 8N1
}


uint8_t uart_read_byte(void) {
  while(UCSR0A & 0x80 == 0) { }
  return UDR0;
}


void uart_write_byte(uint8_t byte) {
  while(UCSR0A & 0x20 == 0) {}
  UDR0 = byte;
}
