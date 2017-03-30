CC = avr-gcc
CFLAGS = -mmcu=atmega328

all: programmer.hex

clean:
	rm -f *.o *.hex *.elf

programmer.elf: main.o
	$(CC) $(CFLAGS) -o $@ $^

programmer.hex: programmer.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
