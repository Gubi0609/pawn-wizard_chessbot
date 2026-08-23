CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -MP
LDFLAGS :=

TARGET := bin/pawn-wizard
BUILD_DIR := build

SOURCES := main.cpp pawnWizard.cpp
OBJECTS := $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
DEPFILES := $(OBJECTS:.o=.d)

.PHONY: all clean run format

all: $(TARGET)

$(TARGET): $(OBJECTS) | bin
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin build:
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

format:
	clang-format -i $(SOURCES) pawnWizard.hpp

clean:
	rm -rf $(BUILD_DIR) bin

-include $(DEPFILES)