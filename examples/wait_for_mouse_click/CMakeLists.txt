project (WAIT_FOR_MOUSE_CLICK)

find_package(terminalpp 3.0.0 REQUIRED)
find_package(consolepp 0.1.1 REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(wait_for_mouse_click src/wait_for_mouse_click.cpp)
target_link_libraries(wait_for_mouse_click 
    PRIVATE 
        KazDragon::terminalpp
        KazDragon::consolepp
        Threads::Threads)
