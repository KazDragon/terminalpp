project (HELLO_WORLD)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

    set(HELLO_WORLD_PRIVATE_LIBRARIES
        CONAN_PKG::terminalpp
    )
else()
    find_package(terminalpp REQUIRED)
    find_package(gsl-lite REQUIRED)
    find_package(fmt REQUIRED)
    find_package(Boost REQUIRED)

    set(HELLO_WORLD_PRIVATE_LIBRARIES
        KazDragon::terminalpp
    )
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hello_world src/hello_world.cpp)
target_link_libraries(hello_world PRIVATE ${HELLO_WORLD_PRIVATE_LIBRARIES})
