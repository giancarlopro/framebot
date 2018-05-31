cmake_minimum_required (VERSION 3.7)
project(framebotLibrary)

include_directories (${PROJECT_SOURCE_DIR}/../include)

# Search for the required libraries, erroring out if they aren't found
find_library(JANSSON_LIB NAMES jansson)
find_package(CURL REQUIRED)
# Add the include directories for the libraries
include_directories(${CURL_INCLUDE_DIRS})

if(UNIX)
	if(NOT CMAKE_SYSTEM_NAME STREQUAL Linux AND NOT CMAKE_SYSTEM_NAME STREQUAL FreeBSD)
		# This is probably an unsupported BSD or OSX.
		# Show an error, but try to proceed.
		message(SEND_ERROR "Only Linux, FreeBSD and Windows are supported at this time.")
	endif()

	add_library(framebot_ SHARED framebot.c memory.c objects.c json.c network.c format.c util.c payments.c)
	target_link_libraries(framebot_ ${JANSSON_LIB} ${CURL_LIBRARIES})

	add_library(framebot STATIC framebot.c memory.c objects.c json.c network.c format.c util.c payments.c)
	target_link_libraries(framebot ${JANSSON_LIB} ${CURL_LIBRARIES})

	install(TARGETS framebot_ LIBRARY DESTINATION lib)
	install(TARGETS framebot ARCHIVE DESTINATION lib)

	if(DEBUG EQUAL 1)
		add_definitions("-g")
		add_definitions("-Wall")
	endif()
endif()

if(WIN32)
	add_library(framebot framebot.c memory.c objects.c json.c network.c format.c util.c payments.c)
	target_link_libraries(framebot ${JANSSON_LIB} ${CURL_LIBRARIES})
	install(TARGETS framebot ARCHIVE DESTINATION lib)
endif()
