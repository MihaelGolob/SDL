cmake_minimum_required(VERSION 3.13)
project(SDL)


include_directories(SDL2/include)
link_directories(SDL2/lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDL main.cpp Window.cpp Player/Player.cpp Tree/Tree.cpp Enemy/Enemy.cpp global.h Text/Text.cpp Ally/Ally.cpp Sprite.cpp Managers/LevelManager/LevelManager.cpp Texture/Texture.cpp Texture/Texture.h Managers/SceneManager/SceneManager.cpp Managers/SceneManager/SceneManager.h Managers/SoundManager/SoundManager.cpp Managers/SoundManager/SoundManager.h UI/Button.cpp UI/Button.h Managers/SaveManager/SaveManager.cpp Managers/SaveManager/SaveManager.h)

target_link_libraries(SDL mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
