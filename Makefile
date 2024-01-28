FLAGS := -Wall -Wextra -std=c++20 -ggdb

LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= main

all: 
	g++ $(CXX_FLAGS) -Iinclude -Llinux/lib src/GGE/**/*.cpp src/GGE/*.cpp src/*.cpp -o linux/bin/$(EXECUTABLE) $(LIBRARIES)
win:
	g++ $(CXX_FLAGS) -Iinclude -Lwin/lib src/GGE/**/*.cpp src/GGE/*.cpp src/*.cpp -o win/bin/$(EXECUTABLE) $(LIBRARIES)
