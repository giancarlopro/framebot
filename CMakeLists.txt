cmake_minimum_required (VERSION 3.7)
project(Telebot)

add_subdirectory(lib)
add_subdirectory(test)

add_definitions("-g")

if(CONFIG_DEFAULT EQUAL 1)
	#does not read configuration file, uses default configuration
	add_definitions("-D CONFIG_DEFAULT")
endif()