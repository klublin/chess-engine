target_sources(chess PRIVATE perft.cpp tables.cpp uci.cpp)

target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})