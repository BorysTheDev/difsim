cmake_minimum_required (VERSION 2.6.4)

set (PROJECT difsim)

project (${PROJECT})

include_directories (.)
include_directories (./gauss)
include_directories (./math)
include_directories (./templates)
include_directories (./2d/hpolarization)
include_directories (./2d/epolarization)
include_directories (./2d/curves)
include_directories (./2d/fields)

add_subdirectory(gauss)

if(CMAKE_COMPILER_IS_GNUCC)
add_definitions (-Wall -pedantic -std=gnu++11 -g -O)
endif()

set (HEADERS 
    ./types.h
    ./matrix.h
    ./counter.h

    ./math/hankel.h
    ./math/chebyshev.h
    ./math/simple_math.h
    ./math/point.h
    ./discretization.h

)
set (SOURCES 
    ./main.cpp
    ./discretization.cpp

    ./2d/epolarization/e_core.cpp
    ./2d/epolarization/field_solver.cpp


    ./2d/curves/curve.cpp
    ./2d/curves/discretize_curve.cpp

    ./2d/fields/field.cpp

    ./2d/hpolarization/h_core.cpp


    ./templates/prototype.h

)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

if(CMAKE_COMPILER_IS_GNUCC)
  target_link_libraries(${PROJECT} pthread)
endif()

