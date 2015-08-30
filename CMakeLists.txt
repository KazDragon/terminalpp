project(terminalpp)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(CppUnit)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

add_library(terminalpp
    src/ansi/charset.cpp
    src/ansi/functions.cpp
    src/attribute.cpp
    src/detail/element_difference.cpp
    src/detail/string_to_elements.cpp
    src/element.cpp
    src/glyph.cpp
    src/string.cpp
)

target_include_directories(terminalpp
    PUBLIC "${CMAKE_SOURCE_DIR}/include"
)

target_compile_features(terminalpp
    PUBLIC
        cxx_strong_enums
        cxx_relaxed_constexpr
)

enable_testing()

add_executable(terminalpp_tester
    test/ansi_functions_test.cpp
    test/main.cpp
    test/string_test.cpp
)

target_link_libraries(terminalpp_tester terminalpp cppunit)
add_test(terminalpp_test terminalpp_tester)

install(
    TARGETS
        terminalpp
    ARCHIVE DESTINATION
        lib
)

install(
    DIRECTORY
        include/
    DESTINATION
        include
)
