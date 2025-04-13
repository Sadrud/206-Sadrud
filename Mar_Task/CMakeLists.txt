cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python REQUIRED COMPONENTS Interpreter)

execute_process(
	COMMAND ${Python_EXECUTABLE} -c "import matplotlib.pyplot as plt, numpy as np, os, glob, pathlib"
	RESULT_VARIABLE python_test_result
	OUTPUT_QUIET ERROR_QUIET
	)

if(NOT python_test_result EQUAL 0)
	message(FATAL_ERROR "Требуемые Python-модули не установлены")
endif()

set(SOURCES
	methods/main.cpp
	methods/Methods.cpp
	include/Geometry/Axis_Parallel_Edge.cpp
	include/Data_Structures/Node.cpp
	)

set(SERVER 
	Server/server.cpp
	include/Data_Structures/Node.cpp 
	methods/Methods.cpp 
	include/Geometry/Axis_Parallel_Edge.cpp
	)
set(CLIENT Client/client.cpp )

add_custom_target(clean_inputs
	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/build/input1"
	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/build/input2"
	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/build/input3"
	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/build/output1"
	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/build/output2"
	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/build/output3"
	COMMENT "Удаление папок input1, input2, input3, output1, output2, output3"
	)

include_directories (include, methods)

add_executable(my_project ${SOURCES})
add_executable(server ${SERVER})
add_executable(client ${CLIENT})

add_custom_command(
	TARGET client
	POST_BUILD
	COMMAND client 127.0.0.1 3
	)

add_custom_target(run_analysis
	COMMAND ${Python_EXECUTABLE} 
	${CMAKE_SOURCE_DIR}/Client/visual.py
	--build-dir ${CMAKE_BINARY_DIR}
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Запуск анализатора данных"
	)
