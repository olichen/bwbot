cmake_minimum_required (VERSION 3.8.0)
project(bwbot)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(bwbot ${SOURCES})
