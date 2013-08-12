###############################################################################
# Makefile for the project Temperature_Sensor_w_LCD
###############################################################################

## General Flags
PROJECT = Temperature_Sensor_w_LCD
MCU = atmega8535
TARGET = Temperature_Sensor_w_LCD.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=Temperature_Sensor_w_LCD.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = Temperature_Sensor_w_LCD.o LCDKS0070B.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Temperature_Sensor_w_LCD.hex Temperature_Sensor_w_LCD.eep Temperature_Sensor_w_LCD.lss size

## Compile
Temperature_Sensor_w_LCD.o: ../Temperature_Sensor_w_LCD.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

LCDKS0070B.o: ../LCDKS0070B.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) Temperature_Sensor_w_LCD.elf dep/* Temperature_Sensor_w_LCD.hex Temperature_Sensor_w_LCD.eep Temperature_Sensor_w_LCD.lss Temperature_Sensor_w_LCD.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

