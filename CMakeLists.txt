cmake_minimum_required(VERSION 3.13)
project(SDL)

include_directories(D:\\Documents\\SDL\\x86_64-w64-mingw32\\include)
link_directories(D:\\Documents\\SDL\\x86_64-w64-mingw32\\lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDL main.cpp)

target_link_libraries(SDL mingw32 SDL2main SDL2)