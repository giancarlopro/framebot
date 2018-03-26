cmake_minimum_required (VERSION 3.7)
project(ExampleBots)

include_directories (${PROJECT_SOURCE_DIR}/../include)

add_executable(echo echo.c)
target_link_libraries(echo jansson ${curl} framebot)

add_executable(inline inline_bot.c)
target_link_libraries(inline jansson ${curl} framebot)