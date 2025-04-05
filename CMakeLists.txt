cmake_minimum_required(VERSION 3.10)

project(WarpEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -ggdb3 -fPIC")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB_RECURSE SRC
    "Components/**/*.cpp"
    "Core/**/*.cpp"
    "Rendering/**/*.cpp"
    "Types/**/*.cpp"
)

add_library(warpengine SHARED ${SRC})

target_link_libraries(warpengine SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image)
