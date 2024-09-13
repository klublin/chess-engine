cmake_minimum_required(VERSION 3.13)
project(chess_engine)

add_compile_options(-Wall -Werror -g -fstack-protector-all -fsanitize=address)
add_link_options(-fsanitize=address)
add_executable(kevbot main.cpp)

add_subdirectory(board)
add_subdirectory(evaluation)
add_subdirectory(move_generation)
add_subdirectory(search)
add_subdirectory(src)

target_include_directories(kevbot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
