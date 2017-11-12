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

add_definitions("-g")

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
	add_library(telebotlibrary telebot.c memory.c objects.c json.c network.c format.c util.c)
	target_link_libraries(telebotlibrary jansson libcurl.so)
endif()

if(WIN32)
	add_library(telebotlibrary telebot.c memory.c objects.c json.c network.c format.c util.c)
	target_link_libraries(telebotlibrary jansson libcurl.so)
endif()
