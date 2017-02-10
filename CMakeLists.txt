project(terminalpp)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

if (POLICY CMP0063)
    cmake_policy(SET CMP0063 OLD) # Do not allow hidden visibility for static libs
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

# Due to the strange requirements for Google Test, it is assumed to have been
# built in the "gtest" directory.  For this, it is required to run the moral
# equivalent of the following script before building Telnet++:
#
#  mkdir gtest
#  cd gtest
#  cmake /usr/src/gtest && make
#  export GTEST_ROOT=$PWD
#  cd ..
find_package(GTest)

# For producing automatically-generated documentation, we use Doxygen.
find_package(Doxygen)

if (GTEST_FOUND)
    # For GTest, it is necessary to link with the appropriate local threading
    # library.
    find_package(Threads)
endif()

if (TERMINALPP_SANITIZE)
    list(APPEND CMAKE_CXX_FLAGS "-fsanitize=${TERMINALPP_SANITIZE}")
    list(APPEND CMAKE_EXE_LINKER_FLAGS "-fsanitize=${TERMINALPP_SANITIZE}")
endif()

if (TERMINALPP_COVERAGE)
    list(APPEND CMAKE_CXX_FLAGS "--coverage -g -O0")
    list(APPEND CMAKE_EXE_LINKER_FLAGS "--coverage")
endif()

set (TERMINALPP_VERSION 1.2)

add_library(terminalpp
    src/ansi/charset.cpp
    src/ansi/control_sequence.cpp
    src/canvas.cpp
    src/canvas_view.cpp
    src/detail/terminal_charset_control.cpp
    src/detail/terminal_control.cpp
    src/detail/terminal_cursor_control.cpp
    src/detail/element_difference.cpp
    src/detail/parser.cpp
    src/detail/well_known_virtual_key.cpp
    src/encoder.cpp
    src/glyph.cpp
    src/screen.cpp
    src/string.cpp
    src/terminal.cpp
    src/virtual_key.cpp
)

set_target_properties(terminalpp
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VERSION ${TERMINALPP_VERSION}
        SOVERSION ${TERMINALPP_VERSION}
)

target_include_directories(terminalpp
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        "${Boost_INCLUDE_DIRS}"
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

install(
    TARGETS
        terminalpp
    EXPORT
        terminalpp-config
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

install(
    EXPORT
        terminalpp-config
    DESTINATION
        lib/terminalpp
)

if (GTEST_FOUND)
    enable_testing()

    add_executable(terminalpp_tester
        test/io/ansi/control_sequence.cpp
        test/io/ansi/mouse.cpp
        test/io/string.cpp
        test/io/virtual_key.cpp
        test/canvas_test.cpp
        test/canvas_view_test.cpp
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
        test/virtual_key_test.cpp
    )

    target_compile_features(terminalpp_tester
        PUBLIC
            cxx_strong_enums
            cxx_relaxed_constexpr)

    target_link_libraries(terminalpp_tester
        terminalpp
        ${GTEST_LIBRARY}
        ${GTEST_MAIN_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
    )

    add_test(terminalpp_test terminalpp_tester)
endif()

# Add a rule for generating documentation
if (DOXYGEN_FOUND)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        @ONLY)

    add_custom_target(terminalpp_doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT
            "Generate API documentation with Doxygen" VERBATIM
    )
endif()
