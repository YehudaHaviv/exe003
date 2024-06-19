# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Source files (including main.cpp)
SRCS = player.cpp vertex.cpp edge.cpp tile.cpp board.cpp catan.cpp 

# Object files (replace .cpp with .o in SRCS)
OBJS = $(SRCS:.cpp=.o)

# Header files (for dependencies)
HDRS = player.hpp vertex.hpp edge.hpp tile.hpp board.hpp catan.hpp 

# Executable name
EXEC = playCatan

# Default rule to build the executable
all: $(EXEC)

# Rule to link object files and create the executable
$(EXEC): $(OBJS) game.cpp
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) game.cpp

# Rule to compile .cpp files into .o files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
