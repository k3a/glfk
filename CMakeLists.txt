cmake_minimum_required(VERSION 2.6)
project (glfk)
	 
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
	 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

option(GLFK_BUILD_EXAMPLES "Build GLFK examples" ON)
option(GLFK_DEBUG "Enable debug build" ON)
option(GLFK_ENSURE_UNBIND "Ensure unbinding every object which was automatically-binded" OFF)

if (GLFK_DEBUG)
	list(APPEND GLFK_DEFINES DEBUG=1)
endif()
if (GLFK_ENSURE_UNBIND)
	list(APPEND GLFK_DEFINES GLFK_ENSURE_UNBIND=1)
endif()

include_directories("${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/deps")

file(GLOB CORE_FILES
		"src/core/*"
	)
source_group("Core" FILES ${CORE_FILES})

file(GLOB EXT_FILES
		"src/extra/*"
	)
source_group("Extra" FILES ${EXT_FILES})


# make sure we have dependencies
add_subdirectory(deps)
message("Dependency includes: ${GLFK_DEP_INCLUDES}")
message("Dependency libraries: ${GLFK_DEP_LIBS}")

# make our library
include_directories(${GLFK_DEP_INCLUDES})
add_library(glfk STATIC ${CORE_FILES} ${EXT_FILES})
target_compile_definitions(glfk PUBLIC ${GLFK_DEP_DEFINES} ${GLFK_DEFINES})
list(APPEND GLFK_LIBS glfk ${GLFK_DEP_LIBS})

# make examples
add_subdirectory(examples)
