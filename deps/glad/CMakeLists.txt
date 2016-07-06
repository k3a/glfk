cmake_minimum_required(VERSION 2.6)
project (glad)
	 
file(GLOB SOURCE_FILES
		"*.c"
	)
source_group("Source" FILES ${SOURCE_FILES})

file(GLOB HEADER_FILES
		"*.h*"
	)
source_group("Headers" FILES ${HEADER_FILES})

add_library(glad STATIC ${SOURCE_FILES})
