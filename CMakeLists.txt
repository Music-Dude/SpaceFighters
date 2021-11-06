cmake_minimum_required(VERSION 3.10.0)

# set the project name and version
project(SpaceThingy VERSION 1.0)

# show compiler warnings
if (MSVC)
        add_compile_options(/W4 /WX)
else()
        add_compile_options(-W -Wall -pedantic -Werror)
endif()

# include FindSFML.cmake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS graphics window system)

# include headers in build
include_directories("${PROJECT_SOURCE_DIR}/include")

# add source dir
add_subdirectory("${PROJECT_SOURCE_DIR}/src")
