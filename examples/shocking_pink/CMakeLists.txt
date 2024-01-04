project (SHOCKING_PINK)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

find_package(terminalpp 3.0.0 REQUIRED)
find_package(gsl-lite REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(shocking_pink src/shocking_pink.cpp)
target_link_libraries(shocking_pink PRIVATE KazDragon::terminalpp)