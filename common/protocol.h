#pragma once

#include <stdint.h>


#define ERROR_NONE      0
#define ERROR_STUFFING  1
#define ERROR_CRC       2
#define ERROR_COMMAND   3

uint8_t protocol_read_command(uint8_t *buffer);
void protocol_generate_error_reply(uint8_t err);
void protocol_write_bytestuffed_reply(uint8_t data_len, uint8_t const* data);