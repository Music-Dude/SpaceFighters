cmake_minimum_required(VERSION 3.10.0)

# set the project name and version
project(SpaceThingy VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CXX_WARNINGS "-Wall -Werror -Wextra")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
