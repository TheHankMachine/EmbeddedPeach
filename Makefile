# Project Name
TARGET = EmbeddedPeach

# Sources
CPP_SOURCES = EmbeddedPeach.cpp 

# CXX = arm-none-eabi-g++ -std=c++20

CPP_STANDARD = -std=gnu++20

# Library Locations
LIBDAISY_DIR = ../libDaisy/
DAISYSP_DIR = ../DaisySP/

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile


# override CXXFLAGS += -std=c++17

# override C_DEFS += -std=c++20
# override CFLAGS += -std=c++20
# override CXXFLAGS += -std=c++20