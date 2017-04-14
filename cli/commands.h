#pragma once

#include "../common/replies.h"

ReplyPing command_ping();
ReplyIdentify command_identify();
uint8_t command_read(uint32_t start_address, uint8_t len, uint8_t *buffer);
ReplyCRC command_crc(uint32_t start_address, uint32_t end_address);
uint8_t command_write(uint32_t start_address, uint8_t len, uint8_t const* buffer);
uint8_t command_erase_sector(uint32_t start_address, uint32_t end_address);
uint8_t command_erase_chip();
