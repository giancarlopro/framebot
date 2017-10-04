cmake_minimum_required (VERSION 3.7)
project(TelebotTest)

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
message("OPENMP FOUND")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories (${PROJECT_SOURCE_DIR}/../include)

add_executable(test_lib test_lib.c)

if (WIN32)
	target_link_libraries(test_lib jansson libcurl_a telebotlibrary)
else (UNIX)
	target_link_libraries(test_lib jansson libcurl.so telebotlibrary)
endif()