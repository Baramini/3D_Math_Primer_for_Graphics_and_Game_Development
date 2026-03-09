cmake_minimum_required(VERSION 3.20)
project(GameMath VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# When you add src files, you should include the file name.
add_executable(GameMath
    src/main.cpp
)

target_include_directories(GameMath PRIVATE src)