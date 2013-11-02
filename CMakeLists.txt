cmake_minimum_required (VERSION 2.6.4)

set (PROJECT difsim)

project (${PROJECT})

include_directories (.)
include_directories (./gauss)
include_directories (./math)
include_directories (./2d/hpolarization)
include_directories (./2d/curves)

add_subdirectory(gauss)

if(CMAKE_COMPILER_IS_GNUCC)
add_definitions (-Wall -pedantic -std=gnu++11 -O2)
endif()

set (HEADERS 

)
set (SOURCES 
    ./main.cpp

)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

if(CMAKE_COMPILER_IS_GNUCC)
  target_link_libraries(${PROJECT} pthread)
endif()

