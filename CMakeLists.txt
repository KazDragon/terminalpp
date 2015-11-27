project(terminalpp)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

if (POLICY CMP0063)
    cmake_policy(SET CMP0063 NEW) # Allow hidden visibility for static libs
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")

# Boost is required as we used Boost.Variant, Boost.Optional, and
# Boost.Format.  All of these are header-only libraries, so no subcomponents
# are required.
include(FindBoost)
find_package(Boost 1.29.0 REQUIRED)

# When building shared objects, etc., we only want to export certain
# symbols.  Therefore, we need to generate a header suitable for declaring
# which symbols should be included.
include (GenerateExportHeader)

# Optionally, the built-in tests use CppUnit.  If that is available, the tests
# will be built as part of the normal compilation.
find_package(CppUnit)

add_library(terminalpp
    src/ansi/charset.cpp
    src/ansi/control_sequence.cpp
    src/ansi/mouse.cpp
    src/attribute.cpp
    src/canvas.cpp
    src/detail/terminal_charset_control.cpp
    src/detail/terminal_control.cpp
    src/detail/terminal_cursor_control.cpp
    src/detail/element_difference.cpp
    src/detail/parse_helper.cpp
    src/detail/well_known_virtual_key.cpp
    src/element.cpp
    src/encoder.cpp
    src/extent.cpp
    src/glyph.cpp
    src/point.cpp
    src/screen.cpp
    src/string.cpp
    src/string_io.cpp
    src/terminal.cpp
    src/virtual_key.cpp
)

set_target_properties(terminalpp
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VERSION 0.1
        SOVERSION 0.1
)

target_include_directories(terminalpp
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
)

target_compile_features(terminalpp
    PUBLIC
        cxx_strong_enums
        cxx_relaxed_constexpr
)

generate_export_header(terminalpp
    EXPORT_FILE_NAME
        "${PROJECT_SOURCE_DIR}/include/terminalpp/detail/export.hpp"
)

if (CPPUNIT_FOUND)
    enable_testing()

    add_executable(terminalpp_tester
        test/canvas_test.cpp
        test/colour_test.cpp
        test/element_test.cpp
        test/encoder_test.cpp
        test/expect_sequence.cpp
        test/expect_tokens.cpp
        test/screen_test.cpp
        test/string_test.cpp
        test/terminal_cursor_test.cpp
        test/terminal_init_test.cpp
        test/terminal_read_cursor_test.cpp
        test/terminal_read_fkey_test.cpp
        test/terminal_read_test.cpp
        test/terminal_settings_test.cpp
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
    LIBRARY DESTINATION
        lib
)

install(
    DIRECTORY
        include/
    DESTINATION
        include
)
