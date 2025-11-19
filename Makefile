# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17

# Source files and executable name
SRC_FILES = main.cpp game_screen.cpp boule.cpp bank.cpp pin.cpp shop_screen.cpp lose_screen.cpp
EXECUTABLE = main

# Libraries to link
LIBS = -Llib -lm -lraylib

# Target
all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(EXECUTABLE)
