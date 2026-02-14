cmake_minimum_required(VERSION 3.15)
project(GameProject C)

set(CMAKE_C_STANDARD 99)

add_executable(game
    src/main.c
    src/board.c
    src/inputs.c
    src/movements.c
    src/bonus.c
    src/pathfinding.c
)

target_include_directories(game PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_directories(game PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(game
    raylib
    opengl32
    gdi32
    winmm
)
