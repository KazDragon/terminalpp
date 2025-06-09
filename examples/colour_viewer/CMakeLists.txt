project (COLOUR_VIEWER)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

find_package(terminalpp 3.0.0 REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(colour_viewer src/colour_viewer.cpp)
target_link_libraries(colour_viewer PRIVATE KazDragon::terminalpp)
