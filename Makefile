# Compiler and linker flags
CXX = clang++  
CXXFLAGS = -std=c++17 -Wall -I./src -I./src/game/constants -I./src/game -I./src/assets/sprites -I./src/assets/fonts -I./src/assets/sound
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files and target
SRC = src/main.cpp \
      src/game/constants/constants.cpp \
      src/game/game.cpp \
      src/assets/sprites/sprites.cpp \
      src/assets/fonts/fonts.cpp \
      src/assets/sound/sound.cpp 

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
