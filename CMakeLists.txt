cmake_minimum_required(VERSION 3.31.5)

project(TestGame)

# Add your source files here
add_executable(${PROJECT_NAME} game.c)

find_package(raylib REQUIRED)

target_link_libraries(${PROJECT_NAME} raylib)
