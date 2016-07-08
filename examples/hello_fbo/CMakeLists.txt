cmake_minimum_required(VERSION 2.8.9)
project (hello_fbo)

add_executable(hello_fbo main.cpp)
target_link_libraries(hello_fbo ${GLFK_LIBS})
