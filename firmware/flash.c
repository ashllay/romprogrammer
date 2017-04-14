#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "flash.h"
#include "shift_register.h"
#include "bits.h"

#define FLASH_OEPORT PORTC
#define FLASH_OEBIT  1

#define FLASH_WEPORT PORTC
#define FLASH_WEBIT  2

static uint8_t read_mode = 1;


void flash_set_address(uint32_t addr) {
  // Clocking out in this order:
  //    10, 11, 9, 8, 13, 14, 17, x, x, x, x, 16, 15, 12, 7, x, 6, 5, 4, 3, 2, 1, 0, x
  // See schematic for reason.

  #define ao(bit) ser_out(!!(addr & (1ul<<(bit))))
  #define x() ser_out(0)
  ao(10); ao(11); ao( 9); ao( 8);
  ao(13); ao(14); ao(17); x();
  x();    x();    x();    ao(16);
  ao(15); ao(12); ao( 7); x();
  ao( 6); ao( 5); ao( 4); ao( 3);
  ao( 2); ao( 1); ao( 0); x();
  #undef x
  #undef ao

  ser_latch();
}


void flash_set_direction(uint8_t inout) {
  // Frst two bits of PORTB and all but first two bits of PORTD
  DDRB = (DDRB & (~0x03)) | (0x03 * inout);
  DDRD = (DDRD & (~0xFC)) | (0xFC * inout);
}


void flash_set_data(uint8_t data) {
  // Data bit -> port mapping
  // DATABIT: 7 6 5 4 3 2 1 0
  // PORT   : D D D D D B B D
  // PORTBIT: 2 3 4 5 6 1 0 7

  #define sb(a, b) ((~((!!(data & (1<<(a))))-1)) & (1<<(b)))
  PORTD = (PORTD & (~0xFC))
        | sb(7, 2)
        | sb(6, 3)
        | sb(5, 4)
        | sb(4, 5)
        | sb(3, 6)
        | sb(0, 7);
  #undef sb

  PORTB = (PORTB & (~0x03))
        | ((data & 0x06) >> 1);
}


uint8_t flash_get_data(void) {
  // Data bit -> port mapping
  // DATABIT: 7 6 5 4 3 2 1 0
  // PORT   : D D D D D B B D
  // PORTBIT: 2 3 4 5 6 1 0 7
  uint8_t D = PIND;
  uint8_t B = PINB;

  #define sb(p, a, b) ((~((!!((p) & (1<<(a))))-1)) & (1<<(b)))
  return    sb(D, 2, 7)
          | sb(D, 3, 6)
          | sb(D, 4, 5)
          | sb(D, 5, 4)
          | sb(D, 6, 3)
          | sb(B, 1, 2)
          | sb(B, 0, 1)
          | sb(D, 7, 0);
  #undef sb
}


int flash_set_output_enable(uint8_t enable) {
  if(read_mode != enable) { // Make sure I don't ruin ROM or ATMega
    return 1;
  }

  set(FLASH_OEPORT, FLASH_OEBIT, !enable);
  return 0;
}


void flash_set_write_enable(uint8_t enable) {
  set(FLASH_WEPORT, FLASH_WEBIT, !enable);
}


void flash_trigger_write(void) {
  flash_set_write_enable(1);
  _delay_loop_1(1);
  flash_set_write_enable(0);
}


void flash_set_read_mode(void) {
  // Switch pins to Hi-Z
  flash_set_direction(0);
  flash_set_data(0);
  
  read_mode = 1;
}


void flash_set_write_mode(void) {
  // Force data bus pins on Flash chip to Hi-Z
  flash_set_output_enable(0);

  // Switch pins to output
  flash_set_direction(1);

  read_mode = 0;
}


void flash_load(uint32_t addr, uint8_t data) {
  flash_set_address(addr);
  flash_set_write_mode();
  flash_set_data(data);
  flash_trigger_write();
}


uint8_t flash_read(uint32_t addr) {
  flash_set_address(addr);
  flash_set_read_mode();
  flash_set_output_enable(1);
  uint8_t data = flash_get_data();
  flash_set_output_enable(0);
  return data;
}


void flash_attention(void) {
  flash_load(0x5555, 0xAA);
  flash_load(0x2AAA, 0x55);
}


void flash_exec_function(uint8_t func) {
  flash_set_write_mode();
  flash_set_output_enable(0);
  flash_attention();
  flash_load(0x5555, func);
}


void flash_enter_software_id(void) {
  flash_exec_function(0x90);
}


void flash_leave_software_id(void) {
  flash_exec_function(0xF0);
}


uint8_t flash_read_manufacturer_id(void) {
  return flash_read(0x0000);
}


uint8_t flash_read_device_id(void) {
  return flash_read(0x0001);
}


void flash_wait_dq7(uint8_t addr, uint8_t value) {
  for(;;) {
    if((flash_read(addr) & 0x80) == value) {
      return;
    }
  }
}


void flash_write_byte(uint32_t addr, uint8_t byte) {
  flash_exec_function(0xA0);
  flash_load(addr, byte);
  //flash_wait_dq7(addr, byte & 0x80);
  _delay_us(30);
}


void flash_erase_sector(uint32_t addr) {
  flash_exec_function(0x80);
  flash_attention();
  flash_load(addr, 0x30);
  flash_wait_dq7(addr & ~(0x7FF), 0x80);
}


void flash_erase_chip(void) {
  flash_exec_function(0x80);
  flash_exec_function(0x10);
  flash_wait_dq7(0, 0x80);
}

