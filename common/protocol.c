#include "protocol.h"

#ifdef __AVR__
# include <util/crc16.h>
#else
uint16_t
_crc_ccitt_update (uint16_t crc, uint8_t data)
{
  data ^= (crc & 0xff);
  data ^= data << 4;
  return ((((uint16_t)data << 8) | (crc >> 8)) ^ (uint8_t)(data >> 4) ^ ((uint16_t)data << 3));
}
#endif


uint8_t uart_read_byte(void);
void uart_write_byte(uint8_t byte);


#define START_BYTE 0xFF
#define ESCAPE_BYTE 0xFE
#define ESCAPE_ESCAPE 0xFD
#define ESCAPE_START  0xFC


void protocol_write_bytestuffed_byte(uint8_t byte) {
  if(byte == START_BYTE) {
    uart_write_byte(ESCAPE_BYTE);
    uart_write_byte(ESCAPE_START);
  } else if(byte == ESCAPE_BYTE) {
    uart_write_byte(ESCAPE_BYTE);
    uart_write_byte(ESCAPE_ESCAPE);
  } else {
    uart_write_byte(byte);
  }
}


void protocol_write_start_byte() {
  uart_write_byte(START_BYTE);
}


void protocol_write_bytestuffed_reply(uint8_t data_len, uint8_t const* data) {
  protocol_write_start_byte();

  uint16_t crc =_crc_ccitt_update(0, data_len + 3);
  protocol_write_bytestuffed_byte(data_len + 3);

  for(uint16_t index = 0; index < data_len; ++index) {
    protocol_write_bytestuffed_byte(data[index]);
    crc = _crc_ccitt_update(crc, data[index]);
  }

  protocol_write_bytestuffed_byte(crc & 0xFF);
  protocol_write_bytestuffed_byte((crc >> 8) & 0xFF);
}


void protocol_generate_error_reply(uint8_t err) {
  protocol_write_bytestuffed_reply(1, &err);
}


void protocol_wait_for_start_byte(void) {
  while(uart_read_byte() != START_BYTE) {}
}


uint8_t protocol_read_bytestuffed_byte(uint8_t *out) {
  uint8_t byte = uart_read_byte();

  if(byte == START_BYTE) { // Must not appear in data stream
    return ERROR_STUFFING;
  }

  if(byte == ESCAPE_BYTE) {
    byte = uart_read_byte();
    if(byte == ESCAPE_ESCAPE) {
      byte = ESCAPE_BYTE;
    } else if(byte == ESCAPE_START) {
      byte = START_BYTE;
    } else {
      return ERROR_STUFFING;
    }
  }

  *out = byte;
  return ERROR_NONE;
}


uint8_t protocol_read_bytestuffed_command(uint8_t *buffer) {
  uint16_t crc = 0;

  buffer[0] = 1;
  for(uint16_t write_index = 0; write_index < buffer[0]; ++write_index) {
    uint8_t err = protocol_read_bytestuffed_byte(buffer + write_index);
    if(err != ERROR_NONE) {
      return err;
    }

    crc = _crc_ccitt_update(crc, buffer[write_index]);
  }

  if(crc != 0) {
    return ERROR_CRC;
  }

  if(buffer[0] < 4) {
    return ERROR_COMMAND;
  }

  return ERROR_NONE;
}


/*
  Frame format:
  START_BYTE | LEN | ... DATA ... | CRC_LO | CRC_HI
  LEN is length over all fields except START_BYTE
  LEN, DATA and CRC are byte stuffed:
    START_BYTE must not occur in stream and is replaced by ESCAPE_BYTE ESCAPE_START
    ESCAPE_BYTE is encoded as ESCAPE_BYTE ESCAPE_ESCAPE
  CRC is CRC16 CCITT over everything except START_BYTE

  buffer contains everything beginning with LEN and including CRC
*/
uint8_t protocol_read_command(uint8_t *buffer) {
  protocol_wait_for_start_byte();
  return protocol_read_bytestuffed_command(buffer);
}
