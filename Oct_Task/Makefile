CC = g++ -Wall -Wextra -Werror
SOURCES = Limits.hpp GCD_HCF.hpp main.cpp GCD_HCF.cpp Exception.hpp
EXECUTABLE = MyProject
CFLAGS = -c
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
	$(CC) $(CFLAGS) $< -o $@
	~                                       
