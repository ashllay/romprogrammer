#include <string.h>
#include <util/crc16.h>
#include "commands.h"
#include "flash.h"
#include "../common/protocol.h"
#include "version.h"
#include <stdbool.h>

#define ERROR_ADDR      4
#define ERROR_LENGTH    5
#define ERROR_TEST_MODE 6

static bool test_mode = false;

#define ASSERT_TEST_MODE(on) if(test_mode != on) { \
  protocol_generate_error_reply(ERROR_TEST_MODE);  \
  return;                                          \
}


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

  ASSERT_TEST_MODE(false);
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
  ASSERT_TEST_MODE(false);

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
  ASSERT_TEST_MODE(false);

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
  ASSERT_TEST_MODE(false);

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
  ASSERT_TEST_MODE(false);

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

  ASSERT_TEST_MODE(false);

  flash_erase_chip();

  protocol_generate_error_reply(ERROR_NONE);
}


void command_test_mode_enter(uint8_t const *buffer) {
  (void) buffer;

  ASSERT_TEST_MODE(false);
  
  static uint8_t const magic[] = {
    4, 8, 15, 16, 23, 42
  };

  if(buffer[0] != sizeof(magic) + 4) {
    protocol_generate_error_reply(20);
    return;
  }

  if(memcmp(buffer+2, magic, sizeof(magic))) {
    protocol_generate_error_reply(21);
    return;
  }

  test_mode = true;
  protocol_generate_error_reply(ERROR_NONE);
}


void command_test_mode_leave(uint8_t const *buffer) {
  (void) buffer;

  ASSERT_TEST_MODE(true);

  test_mode = false;
}


void command_test_mode_set_read_mode(uint8_t const *buffer) {
  (void) buffer;

  ASSERT_TEST_MODE(true);
  
  flash_set_read_mode();
  if(flash_set_output_enable(true)) {
    protocol_generate_error_reply(55);
    return;
  }

  protocol_generate_error_reply(ERROR_NONE);
}


typedef struct {
  uint8_t  packet_length;
  uint8_t  cmd;
  uint32_t addr;
} __attribute__((packed)) TestSetAddrHeader;

void command_test_mode_set_address(uint8_t const *buffer) {
  ASSERT_TEST_MODE(true);

  TestSetAddrHeader const *header = (TestSetAddrHeader const*)buffer;
  if(header->packet_length != sizeof(TestSetAddrHeader) + 2) {
    protocol_generate_error_reply(ERROR_LENGTH);
    return;
  }

  flash_set_address(header->addr);
  
  protocol_generate_error_reply(ERROR_NONE);
}


void command_test_mode_get_data(uint8_t const *buffer) {
  (void) buffer;

  uint8_t reply[2] = {0x00, flash_get_data()};

  protocol_write_bytestuffed_reply(sizeof(reply), reply);
}



static Command const known_commands[] = {
  command_ping,                     //  0
  command_identify,                 //  1
  command_read,                     //  2
  command_crc,                      //  3
  command_write,                    //  4
  command_erase_sector,             //  5
  command_erase_chip,               //  6
  command_test_mode_enter,          //  7
  command_test_mode_leave,          //  8
  command_test_mode_set_read_mode,  //  9
  command_test_mode_set_address,    // 10
  command_test_mode_get_data,       // 11
};
#define MAX_COMMAND (sizeof(known_commands) / sizeof(known_commands[0]))


void command_execute(uint8_t const *buffer) {
  if(buffer[1] >= MAX_COMMAND) {
    protocol_generate_error_reply(ERROR_COMMAND);
  }

  known_commands[buffer[1]](buffer);
}
