cmake_minimum_required(VERSION 2.6)
project (glad)
	 
if(GLFK_DEBUG)
	set(SUB_DIR debug)
else()
	set(SUB_DIR release)
endif()

file(GLOB SOURCE_FILES
		"${SUB_DIR}/*.c"
		"*.cpp"
	)
source_group("Source" FILES ${SOURCE_FILES})

file(GLOB HEADER_FILES
		"${SUB_DIR}/*.h*"
	)
source_group("Headers" FILES ${HEADER_FILES})

add_library(glad STATIC ${SOURCE_FILES})

set(GLAD_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/${SUB_DIR} PARENT_SCOPE)

