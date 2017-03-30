CC = avr-gcc
CFLAGS = -mmcu=atmega328

all: programmer.hex

programmer.elf: main.o
	$(CC) $(CFLAGS) -o $@ $^

programmer.hex: programmer.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
