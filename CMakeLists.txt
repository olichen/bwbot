cmake_minimum_required(VERSION 3.8.0)
project(bwbot)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(bwbot ${SOURCES})

#testing
enable_testing()
include_directories(test)
file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(bwbot_test ${TEST_SOURCES})
add_test(NAME run_tests COMMAND bwbot_test)
