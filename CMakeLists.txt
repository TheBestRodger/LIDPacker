set(MCMAKE_VERSION 3.21)
set(MPROJECT_VERSION 1.0.0)

cmake_minimum_required(VERSION ${MCMAKE_VERSION})

#if(NOT "$ENV{VS110COMNTOOLS}" STREQUAL "")
	#set(CMAKE_GENERATOR "Visual Studio 17 2019" CACHE INTERNAL "Name of generator.")
#endif()

project(LIDPacker)
include(settings.cmake)
add_compile_definitions("_CRT_SECURE_NO_WARNINGS")
# Separation of project to subprojects 
add_subdirectory(source/LIDPacker)