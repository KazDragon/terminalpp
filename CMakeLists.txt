project(terminalpp)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
include(cotire OPTIONAL)

find_package(CppUnit)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

add_library(terminalpp
    src/ansi/charset.cpp
    src/ansi/functions.cpp
    src/attribute.cpp
    src/detail/terminal_control.cpp
    src/detail/terminal_cursor_control.cpp
    src/detail/element_difference.cpp
    src/element.cpp
    src/encoder.cpp
    src/glyph.cpp
    src/point.cpp
    src/string.cpp
    src/string_io.cpp
    src/terminal.cpp
)

target_include_directories(terminalpp
    PUBLIC "${CMAKE_SOURCE_DIR}/include"
)

target_compile_features(terminalpp
    PUBLIC
        cxx_strong_enums
        cxx_relaxed_constexpr
)

if (COMMAND cotire)
    cotire(terminalpp)
endif()

enable_testing()

add_executable(terminalpp_tester
    test/ansi_functions_test.cpp
    test/encoder_test.cpp
    test/expect_sequence.cpp
    test/terminal_cursor_test.cpp
    test/terminal_init_test.cpp
    test/terminal_string_test.cpp
    test/main.cpp
)

target_compile_features(terminalpp_tester
    PUBLIC
        cxx_strong_enums
        cxx_relaxed_constexpr)

target_link_libraries(terminalpp_tester terminalpp cppunit)

if (COMMAND cotire)
    cotire(terminalpp_tester)
endif()

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
