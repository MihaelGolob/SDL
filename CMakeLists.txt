cmake_minimum_required(VERSION 3.13)
project(SDL)

include_directories(D:\\Documents\\SDL\\SDL2\\include)
link_directories(D:\\Documents\\SDL\\SDL2\\lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDL main.cpp Window.cpp Window.h Player/Player.cpp Player/Player.h Tree/Tree.cpp Tree/Tree.h Enemy/Enemy.cpp Enemy/Enemy.h global.h Text/Text.cpp Text/Text.h)

target_link_libraries(SDL mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)