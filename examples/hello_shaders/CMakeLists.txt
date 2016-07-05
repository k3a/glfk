cmake_minimum_required(VERSION 2.8.9)
project (hello_shaders)

add_executable(hello_shaders main.cpp)
target_link_libraries(hello_shaders ${GLFK_LIBS})
