cmake_minimum_required(VERSION 3.10)
project(MyAlgorithmLibrary)

# Указываем стандарт C++ (например, C++17)
set(CMAKE_CXX_STANDARD 17)

# Добавляем исходные файлы
set(SOURCES
	methods/main.cpp
	methods/Methods.cpp
	include/Geometry/Axis_Parallel_Edge.cpp
	include/Data_Structures/Node.cpp
	)

# Добавляем заголовочные файлы
include_directories(include/Data_Srtuctures include/Geometry)

# Создаем библиотеку
add_library(my_algorithm SHARED ${SOURCES})

# Указываем, что main.cpp не должен быть частью библиотеки
set_source_files_properties(methods/main.cpp PROPERTIES EXCLUDE_FROM_ALL TRUE)
