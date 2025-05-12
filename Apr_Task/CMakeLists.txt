cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SERVER 
	server/server.cpp
	)
set(CLIENT
	client/client.cpp
	tests/
	)

set (CMAKE_CXX_FLAGS "-lpthread ${CMAKE_CXX_FLAGS}")

#add_custom_target(clean_inputs
#	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/build/input"
#	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_SOURCE_DIR}/build/output"
#	)

add_custom_target(clean_all
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/*
	COMMENT "Очистка папки Build"
	)

include_directories (methods)

#add_executable(my_project ${SOURCES})
add_executable(server ${SERVER})
add_executable(client ${CLIENT})
