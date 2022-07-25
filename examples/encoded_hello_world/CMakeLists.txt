project (ENCODED_HELLO_WORLD)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)


if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

    set(ENCODED_HELLO_WORLD_PRIVATE_LIBRARIES
        CONAN_PKG::terminalpp
    )
else()
    find_package(terminalpp 3.0.0 REQUIRED)
    find_package(gsl-lite REQUIRED)
    find_package(fmt REQUIRED)
    find_package(Boost REQUIRED)

    set(ENCODED_HELLO_WORLD_PRIVATE_LIBRARIES
        KazDragon::terminalpp
    )
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(encoded_hello_world src/encoded_hello_world.cpp)
target_link_libraries(encoded_hello_world PRIVATE ${ENCODED_HELLO_WORLD_PRIVATE_LIBRARIES})
