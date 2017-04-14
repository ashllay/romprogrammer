#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "serial.h"
#include "../common/protocol.h"


int main() {
  int err = open_serial("/dev/ttyUSB0");

  if(err < 0) {
    return 1;
  }

#if 0
  uint8_t cmd1[] = { 7, 4, 8, 15, 16, 23, 42 };
  uint8_t cmd2[] = { 9 };
  uint8_t cmd3[] = { 11 };
  uint8_t buf[256];
  protocol_write_bytestuffed_reply(sizeof(cmd1), cmd1);
  printf("CMD1 sent\n");
  memset(buf, 0, sizeof(buf));
  protocol_read_command(buf);
  for(int i = 0; i < 256; ++i) {
    printf("%02x ", buf[i]);
  }
  printf("\n");

  protocol_write_bytestuffed_reply(sizeof(cmd2), cmd2);
  printf("CMD2 sent\n");
  memset(buf, 0, sizeof(buf));
  protocol_read_command(buf);
  for(int i = 0; i < 256; ++i) {
    printf("%02x ", buf[i]);
  }
  printf("\n");

  protocol_write_bytestuffed_reply(sizeof(cmd3), cmd3);
  printf("CMD3 sent\n");
  memset(buf, 0, sizeof(buf));
  protocol_read_command(buf);
  for(int i = 0; i < 256; ++i) {
    printf("%02x ", buf[i]);
  }
  printf("\n");
#elif 1
  uint8_t cmd[] = {1};
  uint8_t buf[256];
  protocol_write_bytestuffed_reply(sizeof(cmd), cmd);
  printf("CMD1 sent\n");
  memset(buf, 0, sizeof(buf));
  protocol_read_command(buf);
  for(int i = 0; i < 256; ++i) {
    printf("%02x ", buf[i]);
  }
  printf("\n");
#else
  
#endif

  close_serial();
}
