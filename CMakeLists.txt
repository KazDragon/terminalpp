project(terminalpp)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(CppUnit)

add_library(terminalpp 
    src/attribute.cpp
    src/element.cpp
    src/glyph.cpp)

target_include_directories(terminalpp
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)

target_compile_features(terminalpp
    PUBLIC
        cxx_strong_enums
        cxx_constexpr
)