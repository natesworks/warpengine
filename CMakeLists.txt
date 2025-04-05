cmake_minimum_required(VERSION 3.10)

project(WarpEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -ggdb3 -fPIC")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB_RECURSE SRC
    "src/Components/**/*.cpp"
    "src/Core/*.cpp"
    "src/Rendering/*.cpp"
    "src/Types/*.cpp"
    "src/WarpEngine.h"
)

add_library(warpengine SHARED ${SRC})

target_link_libraries(warpengine SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image)

install(TARGETS warpengine
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY src/
    DESTINATION include/WarpEngine
    FILES_MATCHING PATTERN "*.h"
)
