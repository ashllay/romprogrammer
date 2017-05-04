# romprogrammer
Open Source Flash/EEPROM programmer

This is an open source programmer for 8 bit-wide parallel Flash/EEPROM chips. So far I've only tested it with (and hardcoded the software for) 2MBit (256Kx8) JEDEC compatible Flash chips (and designed the board layout accordingly).

Larger ROMs would require a redesign of the board, smaller ROMs require an adapter for the pinout.

The board uses an Arduino Nano onto which the firmware is flashed. Then you can read and write your PROMs using the command line tool (which should work on all POSIX systems, but I only tested on Debian Linux).

The board layout is single sided and uses relatively wide clearances and traces - ideal for DIY etching :)

## Schematic and Layout

Schematic and layout were made in [KiCad EDA](http://kicad-pcb.org/). You can use that to export to Gerber or PDF, whatever you prefer for you etching (or what you need for your professional board manufacturing service).

## Building

### Hardware
#### Parts

* Whatever PCB material you want to use
* 3x 74HC595 serial in, parellel out shift registers (Dual Inline Package)
* 1x 32 Pin JEDEC DIL chip socket (ZIF, if you want to make your life easier)
* 2x 15 Pin female pin headers (for the Arduino Nano)
* 1x Arduino Nano
* 1x 100nF ceramic capacitor, through hole
* a few centimeters of insulated jumper wire

The hardware is designed to be easily DIY etched. It only uses a single layer (+ a few jumper wires). The jumper wires are indicated on the front copper layer. You should also add a 100nF ceramic cap between pins 16 and 32 of the ROM socket to stabilize its power supply.

### Software
The software is split into two parts, the firmware for the ATMega328P (the µC on the Arduino Nano) and the Linux command line tool. 

#### Firmware

The firmware requires gcc-avr and [avr-libc](http://www.nongnu.org/avr-libc/). The Makefile also contains a rule for writing the firmware to the Arduino using avrdude. (Using an AVRISPmk2, if you want to use the built-in bootloader of the Arduino, you'll have to adapt the Makefile accordingly).

Just build the software in the firmware directory using make, flash it using make flash.

#### CLI

The Linux command line tool is compiled using CMake, goto the cli directory, create a build directory, cd into it, run cmake, then make:

```
mkdir build
cd build
cmake ..
make
```

### Usage
#### Basic Usage and Tests

The command line interface is relatively easy to use, because it doesn't offer many functions (yet). A first check if building has worked and communication between the host and the programmer is working, can be performed by using the ping command:

```
romprg /dev/ttyUSB0 ping
```

(You'll require read/write access to the USB serial port, usually by adding your user account to the dialout group).

This should tell you some information about the firmware and indicate that communication is working.

Next, you should verify that your PROM chip is detected correctly by using the id command:

```
romprg /dev/ttyUSB0 id
```

This will use the JEDEC identification system to query the vendor and device ID of your ROM chip, like this:

```
EEPROM chip identification: manufacturer=0xBF, device=0xB6
```

These should match the IDs noted in your EEPROM's device datasheet.

#### Erasing

You can erase the whole chip or individual sectors using the erase command:

```
romprg /dev/ttyUSB0 erase chip
```

to erase the whole chip, or 

```
romprg /dev/ttyUSB0 erase <startaddr> <endaddr>
```

to erase individual sectors. Note that the software only supports 4KByte sectors right now (the most common sector size in Flash chips).
endaddr must be the address of the byte _after_ the last byte to be erased. startaddr and endaddr must be sector aligned.

#### Writing

After erasing, you can write data to the chip by using the write command:

```
romprg /dev/ttyUSB0 write <startaddr> <inputfile>
```

At the moment only flat binary files are supported (i.e. the file content will be written verbatim to the flash). startaddr need not be sector aligned. startaddr + the size of inputfile must be smaller than the chip size.

#### Reading

You may also read back data on the chip using the read command:

```
romprg /dev/ttyUSB0 read <startaddr> <endaddr> <outfile>
```

endaddr must be greater than startaddr and indicates the address of the byte after the last one to be read. At the moment only flat binary files are supported, i.e. the ROM content will be copied verbatim into outfile. outfile will also be overwritten without asking you for permission, so make sure you know what you're doing ;-)

#### Verifying

There are two way to verify the contents of the ROM: the verify command, which reads a section of the ROM and compares it to an input file, and the crc command, which returns the CRC16 of a given ROM section.

```
romprg /dev/ttyUSB0 verify <startaddr> <endaddr> <infile>
```

Arguments are the same as for the read command (except the file is read instead of written).

```
romprg /dev/ttyUSB0 crc <startaddr> <endaddr>
```

Here, startaddr and endaddr work the same way as in the other commands.

## License
Copyright (c) 2017 Florian Keßeler

The whole software and hardware is released under the terms of the [GNU General Public License version 2](http://www.gnu.de/documents/gpl-2.0.en.html).

