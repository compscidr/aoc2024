add_executable(d3p1 p1.cpp)
add_executable(d3p2 p2.cpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})