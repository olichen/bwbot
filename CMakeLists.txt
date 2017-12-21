cmake_minimum_required(VERSION 3.8.0)
project(bwbot)

set(CMAKE_CXX_STANDARD 11)

#compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#compile base files
include_directories(include)
file(GLOB SRC_BASE "src/*.cpp")
LIST(REMOVE_ITEM SRC_BASE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
LIST(REMOVE_ITEM SRC_BASE "${CMAKE_CURRENT_SOURCE_DIR}/src/bwbot.cpp")
add_library(SrcBase ${SRC_BASE})

#cli
add_executable(bwbot src/main.cpp)
target_link_libraries(bwbot SrcBase)
add_executable(bwbot2 src/bwbot.cpp)
target_link_libraries(bwbot2 SrcBase)

#gui
#fill out later

#testing
enable_testing()
include_directories(test)
file(GLOB SRC_TEST "test/*.cpp")
add_executable(bwbot_test ${SRC_TEST})
target_link_libraries(bwbot_test SrcBase)
add_test(NAME run_tests COMMAND bwbot_test)
