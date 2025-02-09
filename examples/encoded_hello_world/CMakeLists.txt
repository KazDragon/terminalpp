project (ENCODED_HELLO_WORLD)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

find_package(terminalpp 3.0.0 REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(encoded_hello_world src/encoded_hello_world.cpp)
target_link_libraries(encoded_hello_world PRIVATE KazDragon::terminalpp)
