CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 `sdl2-config --cflags`
LDFLAGS := `sdl2-config --libs`
SRC := $(wildcard *.cpp */*.cpp */*/*.cpp)
OBJ := $(SRC:.cpp=.o)
TARGET := warpengine-test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
