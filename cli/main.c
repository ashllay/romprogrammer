#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>


int open_serial(char const* device) {
  int serport = open(device, O_RDWR | O_NOCTTY);
  if(serport < 0 ) {
    perror(device);
    goto out1;
  }

  struct termios tio;
  memset(&tio, 0, sizeof(tio));

  if(tcgetattr(serport, &tio) < 0) {
    perror(device);
    goto out2;
  }

  if(cfsetispeed(&tio, B57600) < 0) {
    perror(device);
    goto out2;
  }
  
  if(cfsetospeed(&tio, B57600) < 0) {
    perror(device);
    goto out2;
  }


  tio.c_cflag &= ~(CSIZE | CSTOPB | CRTSCTS);
  tio.c_cflag |= CS8 | CLOCAL | CREAD;
  tio.c_iflag &= (IGNBRK | IXON | IXOFF | IXANY);
  tio.c_oflag = 0;
  tio.c_lflag = 0;
  tio.c_cc[VMIN] = 1;

  sleep(2);
  if(tcflush(serport, TCIOFLUSH) < 0) {
    perror(device);
    goto out2;
  }

  if(tcsetattr(serport, TCSANOW, &tio) < 0) {
    perror(device);
    goto out2;
  }

  return serport;

out2:
  close(serport);

out1:
  return -1;
}


int serport;


void uart_write_byte(uint8_t byte) {
  if(write(serport, &byte, 1) < 0) {
    perror("serial comm");
    exit(1);
  }
}


uint8_t uart_read_byte() {
  uint8_t buf;
  if(read(serport, &buf, 1) < 0) {
    perror("serial comm");
    exit(1);
  }

  return buf;
}


int main() {
  serport = open_serial("/dev/ttyUSB0");

  if(serport < 0) {
    return 1;
  }

  uint8_t cmd = 0;
  protocol_write_bytestuffed_reply(1, &cmd);
  uint8_t buf[256];
  memset(buf, 0, sizeof(buf));
  protocol_read_command(buf);
  for(int i = 0; i < 256; ++i) {
    printf("%02x ", buf[i]);
  }
  printf("\n");



  close(serport);
}
