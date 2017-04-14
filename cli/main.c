#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "serial.h"
#include "../common/protocol.h"
#include "commands.h"


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
#elif 0
  uint8_t cmd[] = {1};
  uint8_t buf[256];
  protocol_write_packet(sizeof(cmd), cmd);
  printf("CMD1 sent\n");
  memset(buf, 0, sizeof(buf));
  protocol_read_packet(sizeof(buf), buf);
  for(int i = 0; i < 256; ++i) {
    printf("%02x ", buf[i]);
  }
  printf("\n");
#else
  ReplyPing ping = command_ping();
  printf("Ping:\n");
  printf("  err:              %4d\n", ping.error_code);
  printf("  version_major:    %4d\n", ping.firmware_version_major);
  printf("  version_minor:    %4d\n", ping.firmware_version_minor);
  printf("  address_bits:     %4d\n", ping.address_bits);
  printf("  max_write_length: %4d\n", ping.max_write_length);

  ReplyIdentify ident = command_identify();
  printf("Identify:\n");
  printf("  err:              %4d\n", ident.error_code);
  printf("  manufacturer_id:     %02Xh\n", ident.manufacturer_id);
  printf("  device_id:           %02Xh\n", ident.device_id);

  uint8_t data[128];
  memset(data, 0, 128);
  uint8_t err2 = command_read(0, 128, data);
  printf("Read:\n");
  printf("  err: %d\n", err2);
  printf("  data: ");
  for(int i = 0; i < sizeof(data); ++i) {
    if(i % 16 == 0) {
      printf("\n    ");
    }
    printf("%02x ", data[i]);
  }
  printf("\n");

  ReplyCRC crc;
  err2 = command_crc(0, 15, &crc);
  printf("CRC:\n");
  printf("  err: %4d\n", err2);
  printf("  crc: %02X\n", crc.crc);
#endif

  close_serial();
}
