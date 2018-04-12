cmake_minimum_required(VERSION 3.3)
project("CS352 School Building IIT Indore")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGL -lGLU -lglut")

set(BUILD_1 main)
set(SOURCE_FILES_1 main.cpp)
add_executable(${BUILD_1} ${SOURCE_FILES_1})