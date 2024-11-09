CC = g++ 
SOURCES = main.cpp GCD_LCM.hpp GCD_LCM.cpp Limits.hpp
EXECUTABLE = MyProject
CFLAGS = -c
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
	$(CC) $(CFLAGS) $< -o $@
	~                                       
