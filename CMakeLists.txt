cmake_minimum_required(VERSION 3.14)
project(${CMAKE_PROJECT_NAME} VERSION 1.0)
add_compile_definitions(${CMAKE_BUILD_TYPE})
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "COMPILE DEFINITION: ${CMAKE_BUILD_TYPE}")

include(cmake/directoryManager.cmake)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows") 
	include(cmake/windows.cmake)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	include(cmake/android.cmake)
endif()

include(cmake/common.cmake)

