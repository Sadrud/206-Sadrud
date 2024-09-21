CC = g++ -Wall -Wextra -Werror
SOURCES = Plane.hpp main.cpp Plane.cpp Exception.hpp
EXECUTABLE = MyProject
CFLAGS = -c
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
	$(CC) $(CFLAGS) $< -o $@
