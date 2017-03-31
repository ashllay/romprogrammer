#pragma once

#include <stdint.h>

typedef void (*Command)(uint8_t const*);
void command_execute(uint8_t const* buffer);
