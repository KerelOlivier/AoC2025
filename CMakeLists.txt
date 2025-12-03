cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DAY "Day" 1)


message("---Day: ${Day}---")
project("project")

if(${Day} EQUAL 1) 
	add_executable("day1.out" src/day1.cpp)
elseif(${Day} EQUAL 2)
	add_executable("day2.out" src/day2.cpp)
elseif(${Day} EQUAL 3)
	add_executable("day3.out" src/day3.cpp)
else()
	message("ERROR: Invalid day")
endif()

