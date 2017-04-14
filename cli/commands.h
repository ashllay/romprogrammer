#pragma once

#include "../common/replies.h"

uint8_t command_ping(ReplyPing *ping);
uint8_t command_identify(ReplyIdentify *identify);
uint8_t command_read(uint32_t start_address, uint8_t len, uint8_t *buffer);
uint8_t command_crc(uint32_t start_address, uint32_t end_address, ReplyCRC *crc);
uint8_t command_write(uint32_t start_address, uint8_t len, uint8_t const* buffer);
uint8_t command_erase_sector(uint32_t start_address, uint32_t end_address);
uint8_t command_erase_chip();
