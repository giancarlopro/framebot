cmake_minimum_required (VERSION 3.7)
project(FramebotFramework)

find_package(OpenSSL REQUIRED)

set(curl /usr/local/lib/libcurl.so)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)

install(DIRECTORY include/ DESTINATION include)

#include(CPack) # Create installation package