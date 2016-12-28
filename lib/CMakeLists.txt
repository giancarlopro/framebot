cmake_minimum_required (VERSION 3.7)
project(TelebotLibrary)

include_directories (${PROJECT_SOURCE_DIR}/../include)
add_library(telebotlibrary telebot.c telebot_memory.c telebot_objects.c telebot_json.c telebot_network.c telebot_memory.c)
target_link_libraries(telebotlibrary jansson)
