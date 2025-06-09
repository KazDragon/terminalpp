project (POSITIONED_SMILEY)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

find_package(terminalpp 3.0.0 REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(positioned_smiley src/positioned_smiley.cpp)
target_link_libraries(positioned_smiley PRIVATE KazDragon::terminalpp)
