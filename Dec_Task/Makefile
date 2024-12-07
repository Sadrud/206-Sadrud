CC = g++ -Wall -Werror -Wextra
SOURCES = main.cpp Tree.hpp Tree.cpp
EXECUTABLE = MyProject
CFLAGS = -c 
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
	$(CC) $(CFLAGS) $< -o $@
