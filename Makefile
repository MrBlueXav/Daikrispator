# Project Name
TARGET = Daikrispator

# Optimisations
OPT = -Os

# Sources
CPP_SOURCES = Daikrispator.cpp
CPP_SOURCES += \
adsr.cpp \
chorusFD.cpp \
delay.cpp \
drifter.cpp \
math_tools.cpp \
notesTables.cpp \
oscillators.cpp \
phaser.cpp \
resonantFilter.cpp \
sequencer.cpp \
sinetable.cpp \
soundGen.cpp \
random.cpp \
MIDI_application.cpp

# Library Locations
LIBDAISY_DIR = ../../libDaisy
DAISYSP_DIR = ../../DaisySP

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

