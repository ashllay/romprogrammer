CC = avr-gcc
CFLAGS = -mmcu=atmega328 -std=c99
LDFLAGS = -mmcu=atmega328

all: programmer.hex

clean:
	rm -f *.o *.hex *.elf

programmer.elf: main.o flash.o shift_register.o protocol.o uart.o commands.o
	$(CC) $(CFLAGS) -o $@ $^

programmer.hex: programmer.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
