# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sadrudin/206-Sadrud/Mar_Task

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sadrudin/206-Sadrud/Mar_Task/build

# Include any dependencies generated for this target.
include CMakeFiles/my_algorithm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/my_algorithm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/my_algorithm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_algorithm.dir/flags.make

CMakeFiles/my_algorithm.dir/methods/main.cpp.o: CMakeFiles/my_algorithm.dir/flags.make
CMakeFiles/my_algorithm.dir/methods/main.cpp.o: ../methods/main.cpp
CMakeFiles/my_algorithm.dir/methods/main.cpp.o: CMakeFiles/my_algorithm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sadrudin/206-Sadrud/Mar_Task/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_algorithm.dir/methods/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_algorithm.dir/methods/main.cpp.o -MF CMakeFiles/my_algorithm.dir/methods/main.cpp.o.d -o CMakeFiles/my_algorithm.dir/methods/main.cpp.o -c /home/sadrudin/206-Sadrud/Mar_Task/methods/main.cpp

CMakeFiles/my_algorithm.dir/methods/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_algorithm.dir/methods/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sadrudin/206-Sadrud/Mar_Task/methods/main.cpp > CMakeFiles/my_algorithm.dir/methods/main.cpp.i

CMakeFiles/my_algorithm.dir/methods/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_algorithm.dir/methods/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sadrudin/206-Sadrud/Mar_Task/methods/main.cpp -o CMakeFiles/my_algorithm.dir/methods/main.cpp.s

CMakeFiles/my_algorithm.dir/methods/Methods.cpp.o: CMakeFiles/my_algorithm.dir/flags.make
CMakeFiles/my_algorithm.dir/methods/Methods.cpp.o: ../methods/Methods.cpp
CMakeFiles/my_algorithm.dir/methods/Methods.cpp.o: CMakeFiles/my_algorithm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sadrudin/206-Sadrud/Mar_Task/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_algorithm.dir/methods/Methods.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_algorithm.dir/methods/Methods.cpp.o -MF CMakeFiles/my_algorithm.dir/methods/Methods.cpp.o.d -o CMakeFiles/my_algorithm.dir/methods/Methods.cpp.o -c /home/sadrudin/206-Sadrud/Mar_Task/methods/Methods.cpp

CMakeFiles/my_algorithm.dir/methods/Methods.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_algorithm.dir/methods/Methods.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sadrudin/206-Sadrud/Mar_Task/methods/Methods.cpp > CMakeFiles/my_algorithm.dir/methods/Methods.cpp.i

CMakeFiles/my_algorithm.dir/methods/Methods.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_algorithm.dir/methods/Methods.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sadrudin/206-Sadrud/Mar_Task/methods/Methods.cpp -o CMakeFiles/my_algorithm.dir/methods/Methods.cpp.s

CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.o: CMakeFiles/my_algorithm.dir/flags.make
CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.o: ../include/Geometry/Axis_Parallel_Edge.cpp
CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.o: CMakeFiles/my_algorithm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sadrudin/206-Sadrud/Mar_Task/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.o -MF CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.o.d -o CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.o -c /home/sadrudin/206-Sadrud/Mar_Task/include/Geometry/Axis_Parallel_Edge.cpp

CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sadrudin/206-Sadrud/Mar_Task/include/Geometry/Axis_Parallel_Edge.cpp > CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.i

CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sadrudin/206-Sadrud/Mar_Task/include/Geometry/Axis_Parallel_Edge.cpp -o CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.s

CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.o: CMakeFiles/my_algorithm.dir/flags.make
CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.o: ../include/Data_Structures/Node.cpp
CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.o: CMakeFiles/my_algorithm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sadrudin/206-Sadrud/Mar_Task/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.o -MF CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.o.d -o CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.o -c /home/sadrudin/206-Sadrud/Mar_Task/include/Data_Structures/Node.cpp

CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sadrudin/206-Sadrud/Mar_Task/include/Data_Structures/Node.cpp > CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.i

CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sadrudin/206-Sadrud/Mar_Task/include/Data_Structures/Node.cpp -o CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.s

# Object files for target my_algorithm
my_algorithm_OBJECTS = \
"CMakeFiles/my_algorithm.dir/methods/main.cpp.o" \
"CMakeFiles/my_algorithm.dir/methods/Methods.cpp.o" \
"CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.o" \
"CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.o"

# External object files for target my_algorithm
my_algorithm_EXTERNAL_OBJECTS =

libmy_algorithm.so: CMakeFiles/my_algorithm.dir/methods/main.cpp.o
libmy_algorithm.so: CMakeFiles/my_algorithm.dir/methods/Methods.cpp.o
libmy_algorithm.so: CMakeFiles/my_algorithm.dir/include/Geometry/Axis_Parallel_Edge.cpp.o
libmy_algorithm.so: CMakeFiles/my_algorithm.dir/include/Data_Structures/Node.cpp.o
libmy_algorithm.so: CMakeFiles/my_algorithm.dir/build.make
libmy_algorithm.so: CMakeFiles/my_algorithm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sadrudin/206-Sadrud/Mar_Task/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libmy_algorithm.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_algorithm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_algorithm.dir/build: libmy_algorithm.so
.PHONY : CMakeFiles/my_algorithm.dir/build

CMakeFiles/my_algorithm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_algorithm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_algorithm.dir/clean

CMakeFiles/my_algorithm.dir/depend:
	cd /home/sadrudin/206-Sadrud/Mar_Task/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sadrudin/206-Sadrud/Mar_Task /home/sadrudin/206-Sadrud/Mar_Task /home/sadrudin/206-Sadrud/Mar_Task/build /home/sadrudin/206-Sadrud/Mar_Task/build /home/sadrudin/206-Sadrud/Mar_Task/build/CMakeFiles/my_algorithm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_algorithm.dir/depend

