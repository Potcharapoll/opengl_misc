cmake_minimum_required(VERSION 3.8.2)
project(opengl_misc)
set(CMAKE_C_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/cglm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/glad)

add_executable(
    ${PROJECT_NAME} 
    src/main.c
)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw cglm m glad)
