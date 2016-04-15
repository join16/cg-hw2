
cmake_minimum_required(VERSION 3.3)

project(cg_hw2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCES src/lib/*.cpp src/lib/*.h)

add_executable(output src/main.cpp ${SOURCES})

IF (APPLE)
    include_directories(/System/Library/Frameworks)
    find_library(GLUT_LIBRARY GLUT)
    find_library(OpenGL_LIBRARY OpenGL)

    set(EXTRA_LIBS ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
ENDIF(APPLE)

target_link_libraries(output ${EXTRA_LIBS})