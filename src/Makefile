# Compiler settings
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Werror -I/Users/daniel/documents/libraries/c++/sfml/include

# Linker settings
LDFLAGS = -L/Users/daniel/documents/libraries/c++/sfml/build/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,/Users/daniel/documents/libraries/c++/sfml/build/lib

# Source files and object files
SRCS = main.cpp imps/game.cpp imps/piece.cpp imps/cell.cpp
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = tetris

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean