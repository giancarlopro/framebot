cmake_minimum_required (VERSION 3.7)
project(FramebotFramework)

find_package(OpenSSL REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

install(DIRECTORY include/ DESTINATION include)

#include(CPack) # Create installation package