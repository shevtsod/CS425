# compiler
CXX := g++
# compiler flags
CXXLAGS := \
  -I \
  -g \
  -O2 \
  -pedantic-errors \
  -Wall \
  -Wextra \
  -Werror \
# sources (c++ files)
SRC := $(wildcard src/*.cpp)
# build directory
BUILD := ./build
# executable name
TARGET := out

.PHONY: all build clean

all: $(TARGET)

$(TARGET): $(BUILD)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BUILD)/$(TARGET)

build:
	@mkdir -p $(BUILD)

clean:
	rm -rvf $(BUILD)
