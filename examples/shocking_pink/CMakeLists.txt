project (SHOCKING_PINK)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(shocking_pink src/shocking_pink.cpp)
target_link_libraries(shocking_pink PRIVATE CONAN_PKG::terminalpp)