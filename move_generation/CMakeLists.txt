target_sources(chess PRIVATE MoveGenerator.cpp Move.cpp)

target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})