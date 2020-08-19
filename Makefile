# Project Name
TARGET = Daikrispator

# Sources
CPP_SOURCES = Daikrispator.cpp
CPP_SOURCES += \
adsr.cpp \
blepvco.cpp \
chorusFD.cpp \
delay.cpp \
drifter.cpp \
math_tools.cpp \
minblep_tables.cpp \
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
LIBDAISY_DIR = ../../libdaisy
DAISYSP_DIR = ../../DaisySP

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

