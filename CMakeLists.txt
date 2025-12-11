cmake_minimum_required(VERSION 3.16)
project(SFMLEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 3: capitalized components + namespaced targets
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(SFMLEngine main.cpp)

target_link_libraries(SFMLEngine
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)
