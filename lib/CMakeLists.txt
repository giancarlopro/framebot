cmake_minimum_required (VERSION 3.7)
project(TelebotLibrary)

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
message("OPENMP FOUND")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories (${PROJECT_SOURCE_DIR}/../include)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
	add_library(libtelebot_ SHARED telebot.c memory.c objects.c json.c network.c format.c util.c)
	target_link_libraries(libtelebot_ jansson libcurl.so)

	add_library(libtelebot STATIC telebot.c memory.c objects.c json.c network.c format.c util.c)
	target_link_libraries(libtelebot jansson libcurl.so)

	if(DEBUG EQUAL 1)
		add_definitions("-g")
		add_definitions("-Wall")
	endif()
endif()

if(WIN32)
	add_library(libtelebot telebot.c memory.c objects.c json.c network.c format.c util.c)
	target_link_libraries(libtelebot jansson libcurl.so)
endif()
