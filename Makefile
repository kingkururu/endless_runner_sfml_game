# Compiler and linker flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -w -I./game -I./assets/sprites -I./assets/fonts -I./assets/sound -I.
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files and target
SRC = main.cpp \
      game/game.cpp \
      game/global.cpp \
      assets/sprites/sprites.cpp \
      assets/fonts/fonts.cpp \
      assets/sound/sound.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Target executable
TARGET = ASAtut

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJ)
