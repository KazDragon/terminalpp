project (HELLO_WORLD)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hello_world src/hello_world.cpp)
target_link_libraries(hello_world PRIVATE CONAN_PKG::terminalpp)