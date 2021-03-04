if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
    project(TERMINALPP VERSION 1.4.2)
else()
    project(TERMINALPP)
endif()

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

if (POLICY CMP0063)
    cmake_policy(SET CMP0063 OLD) # Do not allow hidden visibility for static libs
endif()

option(TERMINALPP_COVERAGE  "Build with code coverage options")
option(TERMINALPP_SANITIZE "Build using sanitizers" "")
option(TERMINALPP_WITH_TESTS "Build with tests" True)
option(TERMINALPP_DOC_ONLY "Build only documentation" False)

message("Building Terminal++ with config: ${CMAKE_BUILD_TYPE}")
message("Building Terminal++ with code coverage: ${TERMINALPP_COVERAGE}")
message("Building Terminal++ with sanitizers: ${TERMINALPP_SANITIZE}")
message("Building Terminal++ with tests: ${TERMINALPP_WITH_TESTS}")
message("Building Terminal++ with only documentation: ${TERMINALPP_DOC_ONLY}")

# For producing automatically-generated documentation, we use Doxygen.
find_package(Doxygen)

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

if (TERMINALPP_DOC_ONLY)
    return()
endif()

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message("Using Conan due to conanbuildinfo.cmake")
    set(TERMINALPP_USE_CONAN ON)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
endif()

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The required C++ Standard for Terminal++ is C++14.
set(CMAKE_CXX_STANDARD 14)

if (TERMINALPP_USE_CONAN)
    set(TERMINALPP_PUBLIC_LIBRARIES
        CONAN_PKG::boost
        CONAN_PKG::gsl-lite
    )

    set(TERMINALPP_PRIVATE_LIBRARIES
        CONAN_PKG::fmt)

    if (${TERMINALPP_WITH_TESTS})
        set(TERMINALPP_TEST_LIBRARIES
            terminalpp
            CONAN_PKG::fmt
            CONAN_PKG::gtest
        )
    endif()
else()
    # Terminal++ requires at least Boost 1.69
    find_package(Boost 1.69.0 REQUIRED)

    # Terminal++ requires exactly version 0.34 of gsl-lite
    find_package(gsl-lite 0.34.0 REQUIRED)

    # Terminal++ requires libfmt
    find_package(fmt 5.3 REQUIRED)

    # If we are building with tests, then we require the GTest library
    if (${TERMINALPP_WITH_TESTS})
        find_package(GTest REQUIRED)
    endif()

    set(TERMINALPP_PUBLIC_LIBRARIES
        Boost::boost
    )

    set(TERMINALPP_PRIVATE_LIBRARIES
        fmt::fmt
    )

    if (${TERMINALPP_WITH_TESTS})
        set(TERMINALPP_TEST_LIBRARIES
            terminalpp
            fmt::fmt
            GTest::GTest
            GTest::Main
        )
    endif()    
endif()

# When building shared objects, etc., we only want to export certain
# symbols.  Therefore, we need to generate a header suitable for declaring
# which symbols should be included.
include (GenerateExportHeader)

# Increase warning level for GNU or Clang compilers.
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
        include/terminalpp/algorithm/for_each_in_region.hpp
        include/terminalpp/ansi/charset.hpp
        include/terminalpp/ansi/control_characters.hpp
        include/terminalpp/ansi/csi.hpp
        include/terminalpp/ansi/dec_private_mode.hpp
        include/terminalpp/ansi/graphics.hpp
        include/terminalpp/ansi/mouse.hpp
        include/terminalpp/ansi/osc.hpp
        include/terminalpp/ansi/protocol.hpp
#        include/terminalpp/ansi/ss3.hpp
        include/terminalpp/detail/ascii.hpp
        include/terminalpp/detail/element_difference.hpp
#        include/terminalpp/detail/export.hpp
#        include/terminalpp/detail/lambda_visitor.hpp
#        include/terminalpp/detail/parser.hpp
#        include/terminalpp/detail/terminal_charset_control.hpp
#        include/terminalpp/detail/terminal_control.hpp
#        include/terminalpp/detail/terminal_cursor_control.hpp
#        include/terminalpp/detail/well_known_virtual_key.hpp
        include/terminalpp/attribute.hpp
        include/terminalpp/behaviour.hpp
        include/terminalpp/character_set.hpp
        include/terminalpp/colour.hpp
        include/terminalpp/canvas.hpp
        include/terminalpp/control_sequence.hpp
        include/terminalpp/core.hpp
        include/terminalpp/effect.hpp
        include/terminalpp/element.hpp
        include/terminalpp/encoder.hpp
        include/terminalpp/extent.hpp
        include/terminalpp/glyph.hpp
        include/terminalpp/graphics.hpp
        include/terminalpp/mouse.hpp
        include/terminalpp/palette.hpp
        include/terminalpp/point.hpp
        include/terminalpp/rectangle.hpp
        include/terminalpp/screen.hpp
        include/terminalpp/string.hpp
        include/terminalpp/terminal.hpp
#        include/terminalpp/terminal_manip.hpp
#        include/terminalpp/terminalpp.hpp
#        include/terminalpp/token.hpp
        include/terminalpp/version.hpp
        include/terminalpp/virtual_key.hpp

#        src/ansi/charset.cpp
#        src/ansi/mouse.cpp
        src/attribute.cpp
        src/canvas.cpp
        src/character_set.cpp
        src/colour.cpp
        src/control_sequence.cpp
#        src/detail/terminal_charset_control.cpp
#        src/detail/terminal_control.cpp
#        src/detail/terminal_cursor_control.cpp
#        src/detail/parser.cpp
#        src/detail/well_known_virtual_key.cpp
        src/encoder.cpp
        src/glyph.cpp
        src/effect.cpp
        src/element.cpp
        src/extent.cpp
#        src/manip/terminal_streamer.cpp
        src/mouse.cpp
        src/point.cpp
        src/rectangle.cpp
        src/screen.cpp
        src/string.cpp
        src/terminal.cpp
        src/virtual_key.cpp
)

target_link_libraries(terminalpp
    PUBLIC
        ${TERMINALPP_PUBLIC_LIBRARIES}
    PRIVATE
        ${TERMINALPP_PRIVATE_LIBRARIES}
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

target_compile_options(terminalpp
    PRIVATE
        # Do not generate warning C4251 (member needs dll linkage) on MSVC
        $<$<CXX_COMPILER_ID:MSVC>:/wd4251>
        # Do not generate warning C4275 (type needs dll linkage) on MSVC
        $<$<CXX_COMPILER_ID:MSVC>:/wd4275>
        # Any warning on MSVC is an error
        $<$<CXX_COMPILER_ID:MSVC>:/WX>

        # Add warnings on g++ and Clang
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic -Wsign-conversion -Werror>
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

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/terminalpp-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/terminalpp
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config-version.cmake"
    VERSION
        "${TERMINALPP_VERSION}"
    COMPATIBILITY AnyNewerVersion
)

export(
    TARGETS 
        terminalpp
    FILE ${PROJECT_BINARY_DIR}/terminalpp-targets.cmake
)

install(
    TARGETS
        terminalpp
    EXPORT
        terminalpp-targets
    LIBRARY DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/terminalpp-${TERMINALPP_VERSION}
    ARCHIVE DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/terminalpp-${TERMINALPP_VERSION}
    RUNTIME DESTINATION
        ${CMAKE_INSTALL_BINDIR}/terminalpp-${TERMINALPP_VERSION}
)

install(
    EXPORT
        terminalpp-targets
    DESTINATION
        ${CMAKE_INSTALL_DATADIR}/terminalpp-${TERMINALPP_VERSION}
)

install(
    DIRECTORY
        include/
    DESTINATION
        include/terminalpp-${TERMINALPP_VERSION}
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/terminalpp-config-version.cmake"
    DESTINATION
        ${CMAKE_INSTALL_DATADIR}/terminalpp-${TERMINALPP_VERSION}
)

if (TERMINALPP_WITH_TESTS)
enable_testing()

add_executable(terminalpp_tester)

target_sources(terminalpp_tester
    PRIVATE
#        test/expect_tokens.hpp
#        test/terminal_test.hpp

#        test/ansi_charset_test.cpp
        test/attribute_test.cpp
        test/canvas_test.cpp
        test/character_set_test.cpp
        test/colour_test.cpp
        test/control_sequence_test.cpp
        test/effect_test.cpp
        test/element_test.cpp
        test/encoder_test.cpp
        test/expect_sequence.hpp
        test/expect_sequence.cpp
#        test/expect_tokens.cpp
        test/extent_test.cpp
        test/glyph_test.cpp
#        test/manip_test.cpp
        test/mouse_test.cpp
        test/palette_test.cpp
        test/point_test.cpp
        test/rectangle_test.cpp
        test/screen_test.cpp
        test/string_test.cpp
        test/string_manip_test.cpp
        test/terminal_init_test.cpp
        test/terminal_cursor_test.cpp
        test/terminal_erase_test.cpp
#        test/terminal_read_cursor_test.cpp
#        test/terminal_read_fkey_test.cpp
#        test/terminal_read_test.cpp
        test/terminal_settings_test.cpp
        test/terminal_string_test.cpp
        test/virtual_key_test.cpp
)

target_compile_options(terminalpp_tester
    PRIVATE
        # Do not generate warning C4251 (member needs dll linkage) on MSVC
        $<$<CXX_COMPILER_ID:MSVC>:/wd4251>
        # Do not generate warning C4275 (type needs dll linkage) on MSVC
        $<$<CXX_COMPILER_ID:MSVC>:/wd4275>
        # Any warning on MSVC is an error
        $<$<CXX_COMPILER_ID:MSVC>:/WX>
)

target_link_libraries(terminalpp_tester ${TERMINALPP_TEST_LIBRARIES})
add_test(terminalpp_test terminalpp_tester)

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
