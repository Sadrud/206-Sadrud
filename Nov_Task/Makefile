CC = g++ -Wall -Werror -Wextra
SOURCES = main.cpp List.hpp List.cpp
EXECUTABLE = MyProject
CFLAGS = -c 
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
	$(CC) $(CFLAGS) $< -o $@
