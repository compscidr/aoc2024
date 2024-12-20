add_executable(d5p1 p1.cpp)
add_executable(d5p2 p2.cpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})