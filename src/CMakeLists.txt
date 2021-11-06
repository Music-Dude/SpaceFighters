cmake_minimum_required(VERSION 3.10.0)

# compile source files
add_executable(${PROJECT_NAME}
    item.cpp
    main.cpp
    entity.cpp
)

# output to build dir
set_target_properties(${PROJECT_NAME}
    PROPERTIES
       RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# link SFML in executable
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
