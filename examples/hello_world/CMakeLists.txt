project (HELLO_WORLD)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

find_package(terminalpp 3.0.0 REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hello_world src/hello_world.cpp)
target_link_libraries(hello_world PRIVATE KazDragon::terminalpp)
