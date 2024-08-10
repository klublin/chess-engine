cmake_minimum_required(VERSION 3.13)
project(chess_engine)

add_compile_options(-Wall -O2 -Werror)
add_executable(chess main.cpp)

add_subdirectory(board)
add_subdirectory(evaluation)
add_subdirectory(move_generation)
add_subdirectory(search)