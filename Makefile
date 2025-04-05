CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 `sdl2-config --cflags` -ggdb3 -fPIC
LDFLAGS := -lSDL2 -lSDL2_ttf -lSDL2_image
SRC := $(shell find . -name "*.cpp")
OBJ := $(SRC:.cpp=.o)

TARGET := libwarpengine.so

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -shared $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
