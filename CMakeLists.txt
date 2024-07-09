cmake_minimum_required(VERSION 3.13)
project(chess_engine)

add_executable(chess main.cpp)

add_subdirectory(board)
add_subdirectory(evaluation)
add_subdirectory(moving)
add_subdirectory(search)