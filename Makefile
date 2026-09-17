CXX      := g++
CPPFLAGS := -Isrc
LDLIBS   := -lm

CXXFLAGS := -Wall -Wextra -Wpedantic -std=c++26 -march=native -MMD -MP

SRC_DIR := src

ifeq (debug,$(filter debug,$(MAKECMDGOALS)))
  MODE     := debug
  CXXFLAGS += -O0 -g
  LDFLAGS  :=
else
  MODE     := release
  CXXFLAGS += -O2 -flto -DNDEBUG
  LDFLAGS  := -flto -O2 -march=native
endif

BUILD_DIR := build/$(MODE)
BIN_DIR   := bin/$(MODE)

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS    := $(OBJECTS:.o=.d)
TARGET  := $(BIN_DIR)/pimp_my_engine

.PHONY: all debug release run clean

all: $(TARGET)

debug: all
release: all

run: all
	./$(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $@

-include $(DEPS)

clean:
	rm -rf build bin
