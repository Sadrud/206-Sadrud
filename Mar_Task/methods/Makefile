CC = g++ -Wall -Werror -Wextra
SOURCES = main.cpp ../include/Data_Structures/Dictionary.hpp ../include/Data_Structures/RandomizedNode.hpp ../include/Data_Structures/BraidedNode.hpp ../include/Data_Structures/TreeNode.hpp ../include/Data_Structures/Node.hpp
EXECUTABLE = MyProject
CFLAGS = -c 
OBJECTS = $(SOURCES:.cpp = .o)

Myproject : $(SOURCES)
		$(CC) $(OBJECTS) -o $(EXECUTABLE)

cpp.o : .o
		$(CC) $(CFLAGS) $< -o $@
