project (POSITIONED_SMILEY)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(positioned_smiley src/positioned_smiley.cpp)
target_link_libraries(positioned_smiley PRIVATE CONAN_PKG::terminalpp)