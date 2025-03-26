CC = g++
SOURCES = main.cpp Methods.cpp ../include/Data_Structures/Node.cpp ../include/Geometry/Axis_Parallel_Edge.cpp 
EXECUTABLE = MyProject
CFLAGS = -c 
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
		$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
		$(CC) $(CFLAGS) $< -o $@

run: Myproject
		./$(EXECUTABLE)
		python3 visual.py
