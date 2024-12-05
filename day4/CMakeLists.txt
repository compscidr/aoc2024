add_executable(d4p1 p1.cpp)
add_executable(d4p2 p2.cpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})