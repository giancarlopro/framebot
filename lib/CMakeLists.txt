cmake_minimum_required (VERSION 3.7)
project(TelebotLibrary)

include_directories (${PROJECT_SOURCE_DIR}/../include)
add_library(telebotlibrary telebot.c memory.c objects.c json.c network.c memory.c param.c)
target_link_libraries(telebotlibrary jansson libcurl_a)
