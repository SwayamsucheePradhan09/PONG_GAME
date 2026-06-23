SFML_PATH = /Users/swayamsucheepradhan/Downloads/SFML/SFML-2.6.2

CXX = clang++
CXXFLAGS = -std=c++17 -I$(SFML_PATH)/include
LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,$(SFML_PATH)/lib

SRCS = pong.cpp ball.cpp bat.cpp
TARGET = pong_game

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
