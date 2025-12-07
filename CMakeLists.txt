cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DAY "Day" 1)


message("---Day: ${Day}---")
project("project")

include_directories(include)

if(${Day} EQUAL 1) 
	add_executable("day1.out" src/day1.cpp)
elseif(${Day} EQUAL 2)
	add_executable("day2.out" src/day2.cpp)
elseif(${Day} EQUAL 3)
	add_executable("day3.out" src/day3.cpp)
elseif(${Day} EQUAL 4)
	add_executable("day4.out" src/day4.cpp)
elseif(${Day} EQUAL 5)
	add_executable("day5.out" src/day5.cpp)
elseif(${Day} EQUAL 6)
	add_executable("day6.out" src/day6.cpp)
elseif(${Day} EQUAL 7)
	add_executable("day7.out" src/day7.cpp)
else()
	message("ERROR: Invalid day")
endif()

