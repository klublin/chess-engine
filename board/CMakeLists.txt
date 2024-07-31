target_sources(chess PRIVATE board.cpp board.hpp tables.cpp tables.hpp)

target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})