CXX = g++
# Оптимизация для Intel Core 2 Quad Q9000 (архитектура Penryn, 45 нм)
# Поддерживает SSE4.1, но не поддерживает AVX
CXXFLAGS = -Wall -Wextra -Wpedantic -O3 -std=c++17 -march=core2 -msse4.1 -ffast-math -pthread
CXXFLAGS += -MMD -MP
LDFLAGS = -lm -pthread

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
TARGET = $(BIN_DIR)/dyno_stand

.PHONY: all clean run debug release

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

debug: CXXFLAGS += -g -DDEBUG -O0
debug: clean all

release: CXXFLAGS += -DNDEBUG
release: clean all
