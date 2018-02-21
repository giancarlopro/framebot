cmake_minimum_required (VERSION 3.7)
project(FramebotFramework)

find_package(OpenSSL REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)

if(CONFIG_DEFAULT EQUAL 1)
	#does not read configuration file, uses default configuration
	add_definitions("-D CONFIG_DEFAULT")
endif()

install(DIRECTORY include/ DESTINATION include)

#include(CPack) # Create installation package