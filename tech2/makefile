# AVR-GCC Makefile
PROJECT=tech2
SOURCES=tech2.c led.c serial.c sensors.c pwm.c
CC=avr-gcc
OBJCOPY=avr-objcopy
MMCU=atmega8

CFLAGS=-mmcu=$(MMCU) -Wall -O

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES) 
	$(CC) $(CFLAGS) -I./ -o $(PROJECT).out $(SOURCES)
#	$(CC) $(CFLAGS) -I./ -o $(PROJECT).out $(SOURCES)

program: $(PROJECT).hex
	avrdude -p m8 -c avrusb500 -e -U flash:w:$(PROJECT).hex:a

flash: $(PROJECT).hex
	avrdude -p m8 -c avrisp -P /dev/ttyUSB0 -b 19200 -U flash:w:$(PROJECT).hex:a

clean:
	rm -f $(PROJECT).o
	rm -f $(PROJECT).out
	rm -f $(PROJECT).map
	rm -f $(PROJECT).hex

serial:
	$(CC) $(CFLAGS) -I./ -o justserial.out justserial.c led.c
	$(OBJCOPY) -j .text -O ihex justserial.out justserial.hex
	avrdude -p m8 -c avrisp -P COM4 -b 19200 -U flash:w:justserial.hex:a

win: $(PROJECT).hex
	avrdude -p m8 -c avrisp -P COM4 -b 19200 -U flash:w:$(PROJECT).hex:a