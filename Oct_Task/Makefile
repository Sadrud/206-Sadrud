CC = g++ -Wall -Wextra -Werror
SOURCES = Limits.hpp GCD_LCM.hpp main.cpp GCD_LCM.cpp Exception.hpp
EXECUTABLE = MyProject
CFLAGS = -c
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
	$(CC) $(CFLAGS) $< -o $@
	~                                       
