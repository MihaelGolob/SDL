cmake_minimum_required(VERSION 3.13)
project(SDL)

include_directories(D:\\Documents\\SDL\\SDL2\\include)
link_directories(D:\\Documents\\SDL\\SDL2\\lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDL main.cpp Window.cpp Player/Player.cpp Tree/Tree.cpp Enemy/Enemy.cpp global.h Text/Text.cpp Ally/Ally.cpp Sprite.cpp LevelManager.cpp Texture/Texture.cpp Texture/Texture.h)

target_link_libraries(SDL mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)