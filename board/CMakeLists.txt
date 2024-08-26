target_sources(chess PRIVATE board.cpp board.tpp)

target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})