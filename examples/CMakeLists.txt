cmake_minimum_required (VERSION 3.7)
project(ExampleBots)

include_directories (${PROJECT_SOURCE_DIR}/../include)

add_definitions("-g")

if(UNIX)
	if(NOT CMAKE_SYSTEM_NAME STREQUAL Linux AND NOT CMAKE_SYSTEM_NAME STREQUAL FreeBSD)
		# This is probably an unsupported BSD or OSX.
		# Show an error, but try to proceed.
		message(SEND_ERROR "Only Linux, FreeBSD and Windows are supported at this time.")
	endif()

	# Search for the required libraries, erroring out if they aren't found
	find_library(JANSSON_LIB NAMES jansson)
	find_package(CURL REQUIRED)
	# Add the include directories for the libraries
	include_directories(${CURL_INCLUDE_DIRS})
endif()

add_executable(echo echo.c)
target_link_libraries(echo ${JANSSON_LIB} ${CURL_LIBRARIES} framebot)

add_executable(inline inline_bot.c)
target_link_libraries(inline ${JANSSON_LIB} ${CURL_LIBRARIES} framebot)
