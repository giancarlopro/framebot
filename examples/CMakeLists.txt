cmake_minimum_required (VERSION 3.7)
project(ExampleBots)

include_directories (${PROJECT_SOURCE_DIR}/../include)

add_definitions("-g")

set(OS_FREEBSD CMAKE_SYSTEM_NAME STREQUAL FreeBSD)

if(${OS_FREEBSD})
	# Add /usr/local/lib so we can find the libs on FreeBSD
	link_directories(/usr/local/lib /usr/lib /lib)
endif()

add_executable(echo echo.c)
target_link_libraries(echo jansson libcurl.so framebot)

add_executable(inline inline_bot.c)
target_link_libraries(inline jansson libcurl.so framebot)

if(${OS_FREEBSD})
	target_compile_options(echo PUBLIC -I/usr/local/include)
	target_compile_options(inline PUBLIC -I/usr/local/include)
endif()
