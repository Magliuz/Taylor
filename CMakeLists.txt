cmake_minimum_required(VERSION 4.3)
project(Taylor C)

set(CMAKE_C_STANDARD 11)

set(RAYLIB_DIR "C:/raylib/raylib/src")

add_executable(Taylor main.c tinyexpr.c)

target_include_directories(Taylor PRIVATE ${RAYLIB_DIR})
target_link_directories(Taylor PRIVATE ${RAYLIB_DIR})
target_link_libraries(Taylor PRIVATE raylib opengl32 gdi32 winmm)
