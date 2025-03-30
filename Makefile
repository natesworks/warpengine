CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 `sdl2-config --cflags` -ggdb3 -fPIC
LDFLAGS := -lSDL2 -lSDL_ttf -shared
SRC := $(wildcard *.cpp */*.cpp */*/*.cpp)
OBJ := $(SRC:.cpp=.o)

ifeq ($(OS),Windows_NT)
    TARGET := warpengine.dll
else
    TARGET := libwarpengine.so
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

