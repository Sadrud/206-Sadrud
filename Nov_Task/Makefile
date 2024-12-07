CC = g++ -Wall
SOURCES = main.cpp List.hpp List.cpp
EXECUTABLE = MyProject
CFLAGS = -c 
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
	$(CC) $(CFLAGS) $< -o $@
