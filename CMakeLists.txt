project(terminalpp)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")

# Boost is required as we used Boost.Variant, Boost.Optional, and
# Boost.Format.  All of these are header-only libraries, so no subcomponents
# are required.
include(FindBoost)
find_package(Boost 1.29.0 REQUIRED)

# Optionally, the built-in tests use CppUnit.  If that is available, the tests
# will be built as part of the normal compilation.
find_package(CppUnit)

add_library(terminalpp
    src/ansi/charset.cpp
    src/attribute.cpp
    src/canvas.cpp
    src/detail/terminal_charset_control.cpp
    src/detail/terminal_control.cpp
    src/detail/terminal_cursor_control.cpp
    src/detail/element_difference.cpp
    src/element.cpp
    src/encoder.cpp
    src/extent.cpp
    src/glyph.cpp
    src/point.cpp
    src/screen.cpp
    src/string.cpp
    src/string_io.cpp
    src/terminal.cpp
)

target_include_directories(terminalpp
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
)

target_compile_features(terminalpp
    PUBLIC
        cxx_strong_enums
        cxx_relaxed_constexpr
)

if (CPPUNIT_FOUND)
    enable_testing()

    add_executable(terminalpp_tester
        test/canvas_test.cpp
        test/encoder_test.cpp
        test/expect_sequence.cpp
        test/screen_test.cpp
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

    add_test(terminalpp_test terminalpp_tester)
endif()

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
