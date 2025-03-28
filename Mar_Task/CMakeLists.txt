cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Указываем стандарт C++ (например, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	methods/main.cpp
	methods/Methods.cpp
	include/Geometry/Axis_Parallel_Edge.cpp
	include/Data_Structures/Node.cpp
	)

include_directories (include)

add_executable(my_project ${SOURCES})
