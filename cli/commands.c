#include <string.h>
#include "../common/commands.h"
#include "../common/protocol.h"
#include "commands.h"


ReplyPing command_ping() {
  uint8_t cmd = CMD_ping;
  protocol_write_packet(sizeof(cmd), &cmd);
  uint8_t buffer[sizeof(ReplyPing) + 3];
  protocol_read_packet(sizeof(buffer), buffer);
  return *(ReplyPing const*)(buffer+1);
}


ReplyIdentify command_identify() {
  uint8_t cmd = CMD_identify;
  protocol_write_packet(sizeof(cmd), &cmd);
  uint8_t buffer[sizeof(ReplyIdentify) + 3];
  protocol_read_packet(sizeof(buffer), buffer);
  return *(ReplyIdentify const*)(buffer+1);
}


uint8_t command_read(uint32_t start_address, uint8_t len, uint8_t *buffer) {
  struct {
    uint8_t cmd_id;
    CommandRead data;
  } cmd = {
    .cmd_id = CMD_read,
    .data = {
      .read_addr = start_address,
      .read_len  = len
    }
  };
  protocol_write_packet(sizeof(cmd), (uint8_t const*)&cmd);
  uint8_t reply[len + 4];
  int err = protocol_read_packet(sizeof(reply), reply);
  if(err != ERROR_NONE) {
    return err;
  }

  if(reply[1] != ERROR_NONE) {
    return reply[1];
  }

  memcpy(buffer, reply+2, len);

  return ERROR_NONE;
}


uint8_t command_crc(uint32_t start_address, uint32_t end_address, ReplyCRC *crc) {
  struct {
    uint8_t cmd_id;
    CommandCRC data;
  } cmd = {
    .cmd_id = CMD_crc,
    .data = {
      .start_addr = start_address,
      .end_addr   = end_address
    }
  };

  protocol_write_packet(sizeof(cmd), (uint8_t const*)&cmd);

  struct {
    uint8_t len;
    ReplyCRC crc;
    uint16_t pkt_crc;
  } reply;

  int err = protocol_read_packet(sizeof(reply), (uint8_t*)&reply);
  if(err != ERROR_NONE) {
    return err;
  }

  if(reply.crc.error_code != ERROR_NONE) {
    return reply.crc.error_code;
  }

  *crc = reply.crc;

  return ERROR_NONE;
}


uint8_t command_write(uint32_t start_address, uint8_t len, uint8_t const* buffer) {
}


uint8_t command_erase_sector(uint32_t start_address, uint32_t end_address) {
}


uint8_t command_erase_chip() {
}
