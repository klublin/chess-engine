target_sources(chess PRIVATE board.cpp tables.cpp)

target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})