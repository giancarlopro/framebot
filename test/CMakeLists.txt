cmake_minimum_required (VERSION 3.7)
project(TelebotTest)

include_directories (${PROJECT_SOURCE_DIR}/../include)

add_executable(test_lib test_lib.c)
target_link_libraries(test_lib libcurl_a jansson telebotlibrary)
