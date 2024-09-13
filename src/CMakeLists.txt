target_sources(kevbot PRIVATE perft.cpp tables.cpp uci.cpp)

target_include_directories(kevbot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})