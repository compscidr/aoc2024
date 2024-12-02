add_executable(d1p1 common.cpp p1.cpp)
add_executable(d2p2 common.cpp p2.cpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})