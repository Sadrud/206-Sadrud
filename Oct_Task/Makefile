CC = g++ -Wall
SOURCES = main.cpp GCD_LCM.hpp GCD_LCM.cpp
EXECUTABLE = MyProject
CFLAGS = -c -Wall
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
	$(CC) $(CFLAGS) $< -o $@
