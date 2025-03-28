CC = gcc -Wall -Werror -Wextra
SOURCES = server.cpp erprog.cpp
SOURCES2 = client.cpp erprog.cpp
EXECUTABLE = server
EXECUTABLE2 = client
CFLAGS = -c 
OBJECTS = $(SOURCES:.cpp = .o)
OBJECTS2 = $(SOURCES2:.cpp = .o)

server : $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

client : $(SOURCES2)
	$(CC) $(OBJECTS2) -o $(EXECUTABLE2)

cpp.o : .o
	$(CC) $(CFLAGS) $< -o $@
