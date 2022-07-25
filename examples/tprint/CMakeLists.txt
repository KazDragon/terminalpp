project (TPRINT)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

    set(TPRINT_PRIVATE_LIBRARIES
        CONAN_PKG::terminalpp
    )
else()
    find_package(terminalpp 3.0.0 REQUIRED)
    find_package(gsl-lite REQUIRED)
    find_package(fmt REQUIRED)
    find_package(Boost REQUIRED)

    set(TPRINT_PRIVATE_LIBRARIES
        KazDragon::terminalpp
    )
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(tprint src/tprint.cpp)
target_link_libraries(tprint PRIVATE ${TPRINT_PRIVATE_LIBRARIES})