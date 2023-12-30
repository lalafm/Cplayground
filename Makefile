#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# <Put a Description Here>
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      <FILE>.o - Builds <FILE>.o object file
#	   <FILE>.i - Builds <FILE>.i preprocessed file
#	   <FILE>.asm - Builds <FILE>.asm assemby output and final <FILE>.out output file
#      build - Builds and links all source files
#      compile-all - Build all source files but not link
#      clean - removes all generated files
#
# Platform Overrides:
#      CPU - ARM Cortex Architecture (cortex-m4)
#      ARCH - ARM Architecture (armv7e-m, thumb)
#      SPECS - Specs file to give the linker (nosys.specs)
#
#------------------------------------------------------------------------------
include sources.mk

# Platform Overrides
TARGET = final

# Compiler Flags and Defines
CC = gcc
CFLAGS = -DHOST 
CPPFLAGS = -Wall -Werror -g -O0 -std=c99 $(INCLUDES)
SIZE = arm-none-eabi-size

OBJS = $(SOURCES:.c=.o)

%.d: %.c 
	$(CC) -E -M $< $(CPPFLAGS) $(CFLAGS) -o $@

%.o: %.c 
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@

%.i: %.c 
	$(CC) -E $< $(CPPFLAGS) $(CFLAGS) -o $@

%.asm: %.c %.o $(TARGET).out
	$(CC) -S $< $(CPPFLAGS) $(CFLAGS) -o $@
	OBJDUMP -d $(word 2,$^)

$(TARGET).exe: $(OBJS)
	$(CC) $(OBJS) $(CPPFLAGS) $(CFLAGS) -o $@ 
	SIZE $@ 

.PHONY: build
build: $(TARGET).exe

.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: debug
debug: $(TARGET).exe

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET).exe *.asm *.i *.o *.d