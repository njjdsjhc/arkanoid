cmake_minimum_required(VERSION 3.16)
project(Arkanoid CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(arkanoid
    src/main.cpp
    src/Game.cpp
    src/Ball.cpp
    src/Paddle.cpp
    src/Block.cpp
    src/Bonus.cpp
)

target_include_directories(arkanoid PRIVATE src)
target_link_libraries(arkanoid sfml-graphics sfml-window sfml-system)
