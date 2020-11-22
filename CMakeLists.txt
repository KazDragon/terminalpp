if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
    project(TERMINALPP VERSION 1.4.1)
else()
    project(TERMINALPP)
endif()

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

if (POLICY CMP0063)
    cmake_policy(SET CMP0063 OLD) # Do not allow hidden visibility for static libs
endif()

include(cmake/conan.cmake)
conan_cmake_run(REQUIRES
	gtest/1.10.0
	boost/1.69.0
	fmt/5.3.0
        OPTIONS boost:shared=True
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

option(TERMINALPP_COVERAGE  "Build with code coverage options")
option(TERMINALPP_SANITIZE "Build using sanitizers" "")
option(TERMINALPP_WITH_TESTS "Build with tests" True)
message("Building Terminal++ with config: ${CMAKE_BUILD_TYPE}")
message("Building Terminal++ with code coverage: ${TERMINALPP_COVERAGE}")
message("Building Terminal++ with sanitizers: ${TERMINALPP_SANITIZE}")
message("Building Terminal++ with tests: ${TERMINALPP_WITH_TESTS}")

# The required C++ Standard for Terminal++ is C++14.
set(CMAKE_CXX_STANDARD 14)

# When building shared objects, etc., we only want to export certain
# symbols.  Therefore, we need to generate a header suitable for declaring
# which symbols should be included.
include (GenerateExportHeader)

# For producing automatically-generated documentation, we use Doxygen.
find_package(Doxygen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (TERMINALPP_SANITIZE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=${TERMINALPP_SANITIZE}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=${TERMINALPP_SANITIZE}")
endif()

if (TERMINALPP_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_library(terminalpp)

target_sources(terminalpp
    PRIVATE
        include/terminalpp/ansi/charset.hpp
        include/terminalpp/ansi/control_characters.hpp
        include/terminalpp/ansi/control_sequence.hpp
        include/terminalpp/ansi/csi.hpp
        include/terminalpp/ansi/dec_private_mode.hpp
        include/terminalpp/ansi/graphics.hpp
        include/terminalpp/ansi/mouse.hpp
        include/terminalpp/ansi/osc.hpp
        include/terminalpp/ansi/protocol.hpp
        include/terminalpp/ansi/ss3.hpp
        include/terminalpp/attribute.hpp
        include/terminalpp/behaviour.hpp
        include/terminalpp/colour.hpp
        include/terminalpp/canvas.hpp
        include/terminalpp/character_set.hpp
        include/terminalpp/core.hpp
        include/terminalpp/detail/ascii.hpp
        include/terminalpp/detail/element_difference.hpp
        include/terminalpp/detail/export.hpp
        include/terminalpp/detail/lambda_visitor.hpp
        include/terminalpp/detail/parser.hpp
        include/terminalpp/detail/terminal_charset_control.hpp
        include/terminalpp/detail/terminal_control.hpp
        include/terminalpp/detail/terminal_cursor_control.hpp
        include/terminalpp/detail/well_known_virtual_key.hpp
        include/terminalpp/effect.hpp
        include/terminalpp/element.hpp
        include/terminalpp/encoder.hpp
        include/terminalpp/extent.hpp
        include/terminalpp/glyph.hpp
        include/terminalpp/manip/disable_mouse.hpp
        include/terminalpp/manip/enable_mouse.hpp
        include/terminalpp/manip/erase_in_display.hpp
        include/terminalpp/manip/erase_in_line.hpp
        include/terminalpp/manip/hide_cursor.hpp
        include/terminalpp/manip/move_cursor.hpp
        include/terminalpp/manip/restore_cursor.hpp
        include/terminalpp/manip/save_cursor.hpp
        include/terminalpp/manip/set_window_title.hpp
        include/terminalpp/manip/show_cursor.hpp
        include/terminalpp/manip/terminal_streamer.hpp
        include/terminalpp/manip/use_alternate_screen_buffer.hpp
        include/terminalpp/manip/use_normal_screen_buffer.hpp
        include/terminalpp/manip/write_string.hpp
        include/terminalpp/palette.hpp
        include/terminalpp/point.hpp
        include/terminalpp/screen.hpp
        include/terminalpp/string.hpp
        include/terminalpp/terminal.hpp
        include/terminalpp/terminal_manip.hpp
        include/terminalpp/terminalpp.hpp
        include/terminalpp/token.hpp
        include/terminalpp/virtual_key.hpp

        src/ansi/charset.cpp
        src/ansi/control_sequence.cpp
        src/ansi/mouse.cpp
        src/attribute.cpp
        src/canvas.cpp
        src/character_set.cpp
        src/colour.cpp
        src/detail/terminal_charset_control.cpp
        src/detail/terminal_control.cpp
        src/detail/terminal_cursor_control.cpp
        src/detail/element_difference.cpp
        src/detail/parser.cpp
        src/detail/well_known_virtual_key.cpp
        src/encoder.cpp
        src/glyph.cpp
        src/effect.cpp
        src/element.cpp
        src/extent.cpp
        src/manip/terminal_streamer.cpp
        src/point.cpp
        src/rectangle.cpp
        src/screen.cpp
        src/string.cpp
        src/terminal.cpp
        src/virtual_key.cpp
)

target_link_libraries(terminalpp
    PUBLIC
        CONAN_PKG::boost
    PRIVATE
        CONAN_PKG::fmt
)

target_include_directories(terminalpp
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/terminalpp-${TERMINALPP_VERSION}>)

set_target_properties(terminalpp
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VERSION ${TERMINALPP_VERSION}
        SOVERSION ${TERMINALPP_VERSION}
)

generate_export_header(terminalpp
    EXPORT_FILE_NAME
        "${PROJECT_SOURCE_DIR}/include/terminalpp/detail/export.hpp"
)

configure_file(
    ${PROJECT_SOURCE_DIR}/include/terminalpp/version.hpp.in
    ${PROJECT_SOURCE_DIR}/include/terminalpp/version.hpp
    @ONLY
)

install(
    TARGETS
        terminalpp
    EXPORT
        terminalpp-config
    ARCHIVE DESTINATION
        lib/terminalpp-${TERMINALPP_VERSION}
    LIBRARY DESTINATION
        lib/terminalpp-${TERMINALPP_VERSION}
)

install(
    DIRECTORY
        include/
    DESTINATION
        include/terminalpp-${TERMINALPP_VERSION}
)

export(
    EXPORT
        terminalpp-config
    FILE
        "${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config.cmake"
)

install(
    EXPORT
        terminalpp-config
    DESTINATION
        lib/terminalpp-${TERMINALPP_VERSION}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config-version.cmake"
    VERSION
        "${TERMINALPP_VERSION}"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config-version.cmake"
    DESTINATION
        lib/terminalpp-${TERMINALPP_VERSION}
)

if (TERMINALPP_WITH_TESTS)
enable_testing()

add_executable(terminalpp_tester)

target_sources(terminalpp_tester
    PRIVATE
        test/attribute_test.cpp
        test/canvas_test.cpp
        test/character_set_test.cpp
        test/colour_test.cpp
        test/control_sequence_test.cpp
        test/effect_test.cpp
        test/element_test.cpp
        test/encoder_test.cpp
        test/expect_sequence.cpp
        test/expect_tokens.cpp
        test/extent_test.cpp
        test/glyph_test.cpp
        test/manip_test.cpp
        test/mouse_test.cpp
        test/palette_test.cpp
        test/point_test.cpp
        test/rectangle_test.cpp
        test/screen_test.cpp
        test/string_test.cpp
        test/string_manip_test.cpp
        test/terminal_init_test.cpp
        test/terminal_cursor_test.cpp
        test/terminal_read_cursor_test.cpp
        test/terminal_read_fkey_test.cpp
        test/terminal_read_test.cpp
        test/terminal_settings_test.cpp
        test/terminal_string_test.cpp
        test/virtual_key_test.cpp
)

target_link_libraries(terminalpp_tester
    terminalpp
    CONAN_PKG::fmt
    CONAN_PKG::gtest
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

# Add customizations for packaging
set(CPACK_PACKAGE_NAME "Terminal++")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Terminal++")
set(CPACK_PACKAGE_VENDOR "Matthew Chaplain")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR ${TERMINALPP_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${TERMINALPP_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${TERMINALPP_VERSION_PATCH})
include(CPack)
