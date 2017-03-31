#include <util/crc16.h>
#include "commands.h"
#include "flash.h"
#include "protocol.h"
#include "version.h"

#define ERROR_ADDR      4
#define ERROR_LENGTH    5


void command_ping(uint8_t const* buffer) {
  static uint8_t const reply[] = {
    ERROR_NONE,
    PROGRAMMER_VERSION_MAJOR,
    PROGRAMMER_VERSION_MINOR,
    PROGRAMMER_ROM_SIZE & 0xFF,
    (PROGRAMMER_ROM_SIZE >> 8) & 0xFF,
    (PROGRAMMER_ROM_SIZE >> 16) & 0xFF,
    (PROGRAMMER_ROM_SIZE >> 24) & 0xFF,
    PROGRAMMER_MAX_LEN
  };

  protocol_write_bytestuffed_reply(sizeof(reply), reply);
}


void command_identify(uint8_t const* buffer) {
  (void)buffer;

  flash_enter_software_id();
  uint8_t reply[] = {
    ERROR_NONE,
    flash_read_manufacturer_id(),
    flash_read_device_id()
  };
  flash_leave_software_id();

  protocol_write_bytestuffed_reply(sizeof(reply), reply);
}


typedef struct {
  uint8_t  packet_length;
  uint8_t  cmd;
  uint32_t read_addr;
  uint8_t  read_len;
} __attribute__((packed)) ReadHeader;


void command_read(uint8_t const* buffer) {
  ReadHeader const *header = (ReadHeader const*)buffer;
  if(header->packet_length != sizeof(*header)+2) {
    protocol_generate_error_reply(ERROR_COMMAND);
    return;
  }

  if(header->read_len > PROGRAMMER_MAX_LEN) {
    protocol_generate_error_reply(ERROR_LENGTH);
    return;
  }

  if(header->read_addr + header->read_len > PROGRAMMER_ROM_SIZE) {
    protocol_generate_error_reply(ERROR_ADDR);
    return;
  }

  uint8_t  reply[header->read_len+1];
  reply[0] = ERROR_NONE;
  for(uint8_t idx = 0; idx < header->read_len; ++idx) {
    reply[1+idx] = flash_read(header->read_addr + idx);
  }

  protocol_write_bytestuffed_reply(header->read_len+1, reply);
}


typedef struct {
  uint8_t  packet_length;
  uint8_t  cmd;
  uint32_t start_addr;
  uint32_t end_addr;
} __attribute__((packed)) CRCHeader;


void command_crc(uint8_t const* buffer) {
  CRCHeader const *header = (CRCHeader const*)buffer;
  if(header->packet_length != sizeof(*header)+2) {
    protocol_generate_error_reply(ERROR_COMMAND);
    return;
  }

  if(header->start_addr >= PROGRAMMER_ROM_SIZE
      || header->end_addr > PROGRAMMER_ROM_SIZE
      || header->end_addr <= header->start_addr) {

    protocol_generate_error_reply(ERROR_ADDR);
    return;
  }

  uint8_t reply[3];
  reply[0] = ERROR_NONE;
  uint16_t crc = 0;
  for(uint32_t addr = header->start_addr; addr < header->end_addr; ++addr) {
    _crc_ccitt_update(crc, flash_read(addr));
  }

  *(uint16_t*)(reply+1) = crc;

  protocol_write_bytestuffed_reply(sizeof(reply), reply);
}


typedef struct {
  uint8_t  packet_length;
  uint8_t  cmd;
  uint32_t write_addr;
  uint8_t  data[];
} __attribute__((packed)) WriteHeader;


void command_write(uint8_t const* buffer) {
  WriteHeader const *header = (WriteHeader const*)buffer;
  if(header->packet_length < 8) {
    protocol_generate_error_reply(ERROR_LENGTH);
    return;
  }

  uint8_t write_len = buffer[0] - 7;

  if(header->write_addr + write_len > PROGRAMMER_ROM_SIZE) {
    protocol_generate_error_reply(ERROR_ADDR);
    return;
  }

  for(uint8_t idx = 0; idx < write_len; ++idx) {
    flash_write_byte(header->write_addr + idx, header->data[idx]);
  }

  protocol_generate_error_reply(ERROR_NONE);
}


typedef struct {
  uint8_t  packet_length;
  uint8_t  cmd;
  uint32_t start_addr;
  uint32_t end_addr;
} __attribute__((packed)) EraseHeader;


void command_erase_sector(uint8_t const* buffer) {
  EraseHeader const *header = (EraseHeader const*)buffer;
  if(header->packet_length != sizeof(*header)+2) {
    protocol_generate_error_reply(ERROR_COMMAND);
    return;
  }


  if(header->start_addr >= PROGRAMMER_ROM_SIZE
      || header->end_addr > PROGRAMMER_ROM_SIZE
      || header->end_addr <= header->start_addr) {

    protocol_generate_error_reply(ERROR_ADDR);
    return;
  }


  if((header->start_addr & (PROGRAMMER_ROM_SIZE-1)) != 0
      || (header->end_addr & (PROGRAMMER_ROM_SIZE-1)) != 0) {
    protocol_generate_error_reply(ERROR_ADDR);
    return;
  }

  for(uint32_t addr = header->start_addr; addr < header->end_addr; addr += PROGRAMMER_SECTOR_SIZE) {
    flash_erase_sector(addr);
  }

  protocol_generate_error_reply(ERROR_NONE);
}


void command_erase_chip(uint8_t const* buffer) {
  (void) buffer;

  flash_erase_chip();

  protocol_generate_error_reply(ERROR_NONE);
}


static Command const known_commands[] = {
  command_ping,
  command_identify,
  command_read,
  command_crc,
  command_write,
  command_erase_sector,
  command_erase_chip
};
#define MAX_COMMAND (sizeof(known_commands) / sizeof(known_commands[0]))


void command_execute(uint8_t const *buffer) {
  if(buffer[1] >= MAX_COMMAND) {
    protocol_generate_error_reply(ERROR_COMMAND);
  }

  known_commands[buffer[1]](buffer);
}


