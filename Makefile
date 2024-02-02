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
TARGET = final.exe
TARGETTEST = final_tests.exe

# Compiler Flags and Defines
C_COMPILER = gcc
CPPFLAGS = -g -O0 -std=c99
SIZE = arm-none-eabi-size

#CFLAGS = -DHOST 
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition

SYMBOLS = -DUNITY_FIXTURE_NO_EXTRAS

OBJS = $(SOURCES:.c=.o)

%.d: %.c 
	$(C_COMPILER) -E -M $< $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -o $@

%.o: %.c 
	$(C_COMPILER) -c $< $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -o $@

%.i: %.c 
	$(C_COMPILER) -E $< $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -o $@

%.asm: %.c %.o $(TARGET)
	$(C_COMPILER) -S $< $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -o $@
	OBJDUMP -d $(word 2,$^)

$(TARGET): $(OBJS)
	$(C_COMPILER) $(OBJS) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -o $@ 
	SIZE $@ 
	./$(TARGET)

$(TARGETTEST): clean
	$(C_COMPILER) $(CFLAGS) $(CPPFLAGS) $(TESTINCLUDES) $(SYMBOLS) $(TESTSOURCES) -o $(TARGETTEST) 
	./$(TARGETTEST)

.PHONY: build
build: $(TARGET)

.PHONY: tests
tests: $(TARGETTEST)

.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: debug
debug: $(TARGET)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) $(TARGETTEST) *.asm *.i *.o *.d