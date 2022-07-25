project (WAIT_FOR_MOUSE_CLICK)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

    set(WAIT_FOR_MOUSE_CLICK_PRIVATE_LIBRARIES
        CONAN_PKG::terminalpp
        CONAN_PKG::consolepp
        CONAN_PKG::fmt
    )
else()
    find_package(terminalpp 3.0.0 REQUIRED)
    find_package(consolepp REQUIRED)
    find_package(gsl-lite REQUIRED)
    find_package(fmt REQUIRED)
    find_package(Boost REQUIRED)
    find_package(Threads REQUIRED)

    set(WAIT_FOR_MOUSE_CLICK_PRIVATE_LIBRARIES
        KazDragon::terminalpp
        KazDragon::consolepp
        Threads::Threads
    )
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(wait_for_mouse_click src/wait_for_mouse_click.cpp)
target_link_libraries(wait_for_mouse_click PRIVATE ${WAIT_FOR_MOUSE_CLICK_PRIVATE_LIBRARIES})
