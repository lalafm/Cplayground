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

# Add your Source files to this variable
LIBS = ./libs/lifo_buffer.c

SOURCES = $(LIBS) \
	./src/main.c

TESTSOURCES = $(LIBS) \
	$(UNITY_ROOT)/src/unity.c \
  	$(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  	tests/TestProductionCode2.c \
	tests/test_runners/TestProductionCode2_Runner.c \
 	tests/test_runners/all_tests.c

# Add your include paths to this variable
INCLUDES = -I ./libs

TESTINCLUDES = -I ./libs \
	-I$(UNITY_ROOT)/src \
	-I$(UNITY_ROOT)/extras/fixture/src \
	-I$(UNITY_ROOT)/extras/memory/src

# Add path where Unity framework files are located
UNITY_ROOT = ../Unity-master
