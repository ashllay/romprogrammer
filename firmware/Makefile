CC = avr-gcc
CFLAGS = -mmcu=atmega328p -std=c99 -O1
LDFLAGS = -mmcu=atmega328p

all: programmer.hex

clean:
	rm -f *.o *.hex *.elf

programmer.elf: main.o flash.o shift_register.o ../common/protocol.o uart.o commands.o
	$(CC) $(CFLAGS) -o $@ $^

programmer.hex: programmer.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

flash: programmer.hex
	avrdude -p m328p -c avrisp2 -U flash:w:programmer.hex:i
