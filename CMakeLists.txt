cmake_minimum_required(VERSION 3.13)
project(chess_engine)

add_compile_options(-Wall -fstack-protector-all -fsanitize=address -O2 -Werror)
add_link_options(-fsanitize=address)
add_executable(chess main.cpp)

add_subdirectory(board)
add_subdirectory(evaluation)
add_subdirectory(move_generation)
add_subdirectory(search)
add_subdirectory(src)

target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
