cmake_minimum_required(VERSION 2.6)

# GLFW --------------------------------------
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.2)
find_package(OpenGL REQUIRED)

# add libs and includes
list(APPEND GLFK_DEP_LIBS glfw ${OPENGL_LIBRARIES})
list(APPEND GLFK_DEP_INCLUDES ${OPENGL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.2/include)
list(APPEND GLFK_DEP_DEFINES GLFK_HAS_GLFW)

# GLM ----------------------------------------

list(APPEND GLFK_DEP_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/glm-0.9.7)
list(APPEND GLFK_DEP_DEFINES GLFK_HAS_GLM)

# GLAD ---------------------------------------

add_subdirectory(glad)
list(APPEND GLFK_DEP_LIBS glad)
list(APPEND GLFK_DEP_INCLUDES ${GLAD_INCLUDES})

# --------------------------------------------
# propagate to parent
set(GLFK_DEP_LIBS ${GLFK_DEP_LIBS} PARENT_SCOPE)
set(GLFK_DEP_INCLUDES ${GLFK_DEP_INCLUDES} PARENT_SCOPE)
set(GLFK_DEP_DEFINES ${GLFK_DEP_DEFINES} PARENT_SCOPE)
