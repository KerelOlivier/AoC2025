cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DAY "Day" 1)


message("---Day: ${Day}---")
project("project")

if(${Day} EQUAL 1) 
	add_executable("day_1.out" src/day_1.cpp)
else()
	message("ERROR: Invalid day")
endif()

