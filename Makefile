SOURCEDIR = src
INCLUDE_DIR = include
TARGET = $(SOURCEDIR)/tests.cpp
EXECUTABLE = tests
BUILD_DIR = build

CXX = g++
CXXFLAGS = -std=c++23 -Wconversion -Wall -Werror -Wextra -pedantic -I$(INCLUDE_DIR)
LIBS = -lgtest

$(shell mkdir -p $(BUILD_DIR))

all: debug

release: CXXFLAGS += -O3 -DNDEBUG -fsanitize=address -fsanitize=undefined
release: $(OBJECTS) $(EXECUTABLE)
.PHONY: release

debug: CXXFLAGS += -Og -g3 -fsanitize=address -fsanitize=undefined
debug: $(OBJECTS) $(EXECUTABLE)_debug
.PHONY: debug

clean:
	rm -fv $(EXECUTABLE)* *.obj
	rm -rf build
.PHONY: clean

$(EXECUTABLE):
	$(CXX) $(CXXFLAGS) $(TARGET) -o $(BUILD_DIR)/$(EXECUTABLE) $(OBJECTS) $(LIBS)

$(EXECUTABLE)_debug:
		$(CXX) $(CXXFLAGS) $(TARGET) -o $(BUILD_DIR)/$(EXECUTABLE)_debug $(OBJECTS) $(LIBS)

$(OBJECTS): %.obj: $(SOURCEDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(LIBS)
