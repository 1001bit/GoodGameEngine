FLAGS := -Wall -Wextra -std=c++20 -ggdb

LDFLAGS 	:= '-Wl,-rpath,$$ORIGIN/lib'
LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= main

all: 
	rm linux/bin/$(EXECUTABLE)
	g++ $(CXX_FLAGS) -Iinclude $(LDFLAGS) -Llinux/lib src/*.cpp -o linux/bin/$(EXECUTABLE) $(LIBRARIES)
win:
	rm win/bin/$(EXECUTABLE)
	g++ $(CXX_FLAGS) -Iinclude -Lwin/lib src/*.cpp -o win/bin/$(EXECUTABLE) $(LIBRARIES)
