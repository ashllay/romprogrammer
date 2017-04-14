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

#elif 0
  ReplyCRC crc;
  err2 = command_crc(0, 15, &crc);
  printf("CRC:\n");
  printf("  err: %4d\n", err2);
  printf("  crc: %02X\n", crc.crc);
#elif 0
  uint8_t data2[11] = "HALLO,FLO!";
  uint8_t err2 = command_write(2*4096-5, 10, &data2);
  printf("Write:\n");
  printf("  err: %4d\n", err2);
#elif 0
  int err2 = command_erase_chip();
  printf("Erase Chip:\n");
  printf("  err: %4d\n", err2);
#elif 0
  int err2 = command_erase_sector(4096, 2*4096);
  printf("Erase Sector:\n");
  printf("  err: %4d\n", err2);

#else
  uint8_t data[128];
  memset(data, 0, 128);
  uint8_t err2 = command_read(4096*2-10, 128, data);
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


#endif

  close_serial();
}
