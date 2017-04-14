#include "../common/commands.h"
#include "../common/protocol.h"
#include "commands.h"


ReplyPing command_ping() {
  uint8_t cmd = CMD_ping;
  protocol_write_packet(sizeof(cmd), &cmd);
}


ReplyIdentify command_identify() {
}


uint8_t command_read(uint32_t start_address, uint8_t len, uint8_t *buffer) {
}


ReplyCRC command_crc(uint32_t start_address, uint32_t end_address) {
}


uint8_t command_write(uint32_t start_address, uint8_t len, uint8_t const* buffer) {
}


uint8_t command_erase_sector(uint32_t start_address, uint32_t end_address) {
}


uint8_t command_erase_chip() {
}
