cmake_minimum_required(VERSION 2.8.9)
project (hello)

add_executable(hello main.cpp)
target_link_libraries(hello ${GLFK_LIBS})
