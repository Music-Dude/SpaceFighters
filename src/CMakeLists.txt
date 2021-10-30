cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_BINARY_DIR "..")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME}
    item.cpp
    main.cpp
    entity.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS graphics window system audio)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
