CXX = g++
# Оптимизация для Intel Core 2 Quad Q9000 (архитектура Penryn, 45 нм)
# Поддерживает SSE4.1, но не поддерживает AVX
CXXFLAGS = -Wall -Wextra -Wpedantic -O2 -flto -std=c++26 -march=core2 -msse4.1 -pthread
CXXFLAGS += -Isrc -MMD -MP #-fopenmp
LDFLAGS = -lm -pthread #-fopenmp

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Рекурсивный поиск всех .cpp файлов
SOURCES = $(shell find $(SRC_DIR) -name "*.cpp")
# Создание списка объектных файлов с сохранением структуры каталогов
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
TARGET = $(BIN_DIR)/pimp_my_engine

.PHONY: all clean run debug release

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Правило для компиляции с сохранением структуры каталогов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
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
