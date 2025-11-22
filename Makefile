# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Ihpp      # <-- ajout du dossier hpp/

# Dossiers
SRC_DIR = cpp

# Source files (déplacés dans cpp/)
SRC_FILES = $(SRC_DIR)/main.cpp \
            $(SRC_DIR)/game_screen.cpp \
            $(SRC_DIR)/boule.cpp \
            $(SRC_DIR)/bank.cpp \
            $(SRC_DIR)/pin.cpp \
            $(SRC_DIR)/shop_screen.cpp \
            $(SRC_DIR)/lose_screen.cpp

# Executable name
EXECUTABLE = main

# Libraries to link
LIBS = -Llib -lm -lraylib

# Target
all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(EXECUTABLE)
