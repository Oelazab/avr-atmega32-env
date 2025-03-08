MCU = atmega32
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -Wall -Os

TARGET = debug/main

SRC = main.cpp \
    MCAL/UART/src/UART_program.cpp

INC = -I. \
    -IMCAL/UART/inc \
    -IUTILES_LIB


all: create_debug  $(TARGET).hex

create_debug:
	@if not exist debug mkdir debug

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

flash: $(TARGET).hex
	avrdude -c usbasp -p m32 -U flash:w:$(TARGET).hex:i

clean:
	@if exist debug rd /s /q debug