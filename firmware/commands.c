#include "commands.h"
#include "flash.h"
#include "protocol.h"


void command_identify(uint8_t const* buffer) {
  (void)buffer;

  flash_enter_software_id();
  uint8_t reply[2] = {
    flash_read_manufacturer_id(),
    flash_read_device_id()
  };
  flash_leave_software_id();
}


Command known_commands[] = {
  command_identify
};
#define MAX_COMMAND (sizeof(known_commands) / sizeof(known_commands[0]))



void command_execute(uint8_t const *buffer) {
  if(buffer[1] >= MAX_COMMAND) {
    protocol_generate_error_reply(ERROR_COMMAND);
  }

}


