if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
    project(TERMINALPP VERSION 1.2.5)
else()
    project(TERMINALPP)
endif()

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

if (POLICY CMP0063)
    cmake_policy(SET CMP0063 OLD) # Do not allow hidden visibility for static libs
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")
set(CMAKE_DEBUG_POSTFIX d)

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
# equivalent of the following script before building Terminal++:
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

set (TERMINALPP_VERSION 1.2.5)

set(TERMINALPP_CORE_SOURCE_FILES
    src/ansi/charset.cpp
    src/ansi/control_sequence.cpp
    src/attribute.cpp
    src/canvas.cpp
    src/canvas_view.cpp
    src/colour.cpp
    src/encoder.cpp
    src/glyph.cpp
    src/effect.cpp
    src/extent.cpp
    src/point.cpp
    src/screen.cpp
    src/string.cpp
    src/virtual_key.cpp
)

set(TERMINALPP_CORE_INCLUDE_FILES
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
    include/terminalpp/canvas_view.hpp
    include/terminalpp/core.hpp
    include/terminalpp/effect.hpp
    include/terminalpp/element.hpp
    include/terminalpp/encoder.hpp
    include/terminalpp/extent.hpp
    include/terminalpp/glyph.hpp
    include/terminalpp/point.hpp
    include/terminalpp/screen.hpp
    include/terminalpp/string.hpp
    include/terminalpp/terminal.hpp
    include/terminalpp/terminalpp.hpp
    include/terminalpp/token.hpp
    include/terminalpp/virtual_key.hpp
)

add_library(terminalpp-core
    ${TERMINALPP_CORE_SOURCE_FILES}
    ${TERMINALPP_CORE_INCLUDE_FILES}
)

set_target_properties(terminalpp-core
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VERSION ${TERMINALPP_VERSION}
        SOVERSION ${TERMINALPP_VERSION}
)

target_include_directories(terminalpp-core
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
        "${Boost_INCLUDE_DIRS}"
)

target_compile_features(terminalpp-core
    PUBLIC
        cxx_strong_enums
        cxx_relaxed_constexpr
)

set(TERMINALPP_SOURCE_FILES
    src/detail/terminal_charset_control.cpp
    src/detail/terminal_control.cpp
    src/detail/terminal_cursor_control.cpp
    src/detail/element_difference.cpp
    src/detail/parser.cpp
    src/detail/well_known_virtual_key.cpp
    src/ansi_terminal.cpp
)

set(TERMINALPP_INCLUDE_FILES
    include/terminalpp/detail/ascii.hpp
    include/terminalpp/detail/element_difference.hpp
    include/terminalpp/detail/export.hpp
    include/terminalpp/detail/lambda_visitor.hpp
    include/terminalpp/detail/parser.hpp
    include/terminalpp/detail/terminal_charset_control.hpp
    include/terminalpp/detail/terminal_control.hpp
    include/terminalpp/detail/terminal_cursor_control.hpp
    include/terminalpp/detail/well_known_virtual_key.hpp
    include/terminalpp/ansi_terminal.hpp
)

add_library(terminalpp
    ${TERMINALPP_SOURCE_FILES}
    ${TERMINALPP_INCLUDE_FILES}
)

set_target_properties(terminalpp
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VERSION ${TERMINALPP_VERSION}
        SOVERSION ${TERMINALPP_VERSION}
)

target_link_libraries(terminalpp
    PUBLIC
        terminalpp-core
)

generate_export_header(terminalpp
    EXPORT_FILE_NAME
        "${PROJECT_SOURCE_DIR}/include/terminalpp/detail/export.hpp"
)

configure_file(
    ${PROJECT_SOURCE_DIR}/include/terminalpp/version.hpp.in
    ${PROJECT_SOURCE_DIR}/include/terminalpp/version.hpp
)

install(
    TARGETS
        terminalpp-core
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

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config-version.cmake"
    VERSION
        "${TERMINALPP_VERSION}"
    COMPATIBILITY AnyNewerVersion
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

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config-version.cmake"
    DESTINATION
        lib/terminalpp-${TERMINALPP_VERSION}/cmake
)

if (GTEST_FOUND)
    enable_testing()

    add_executable(terminalpp_tester
        test/io/ansi/control_sequence.cpp
        test/io/ansi/mouse.cpp
        test/io/string.cpp
        test/io/virtual_key.cpp
        test/ansi_terminal_init_test.cpp
        test/ansi_terminal_cursor_test.cpp
        test/ansi_terminal_read_cursor_test.cpp
        test/ansi_terminal_read_fkey_test.cpp
        test/ansi_terminal_read_test.cpp
        test/ansi_terminal_settings_test.cpp
        test/ansi_terminal_string_test.cpp
        test/attribute_test.cpp
        test/canvas_test.cpp
        test/canvas_view_test.cpp
        test/colour_test.cpp
        test/effect_test.cpp
        test/element_test.cpp
        test/encoder_test.cpp
        test/expect_sequence.cpp
        test/expect_tokens.cpp
        test/extent_test.cpp
        test/glyph_test.cpp
        test/point_test.cpp
        test/screen_test.cpp
        test/string_test.cpp
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
