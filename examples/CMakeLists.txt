cmake_minimum_required(VERSION 2.6)

# include all subdirs
FILE(GLOB _ALL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*)
FOREACH(_FILE ${_ALL_FILES})
  IF(IS_DIRECTORY ${_FILE} AND NOT "${_FILE}" STREQUAL "CMakeFiles")
    add_subdirectory(${_FILE})
  ENDIF()
ENDFOREACH()
