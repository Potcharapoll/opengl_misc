cmake_minimum_required(VERSION 3.8.2)
project(opengl_misc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/cglm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui)

set(IMGUI_LIBRARIES )
set(IMGUI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/cimgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/imgui/backends/imgui_impl_glfw.cpp
)

include_directories(lib/cimgui/imgui)
if (WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
    add_library(cimgui STATIC ${IMGUI_SOURCES})
    list(APPEND IMGUI_LIBRARIES opengl32)
else(WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\"")
    add_library(cimgui SHARED ${IMGUI_SOURCES})
    list(APPEND IMGUI_LIBRARIES GL)
endif(WIN32)
target_link_libraries(cimgui ${IMGUI_LIBRARIES} glfw)

include_directories(lib/glad/include)
include_directories(lib/cimgui/)
include_directories(lib/cimgui/generator/output)

add_executable(
    ${PROJECT_NAME} 
    lib/glad/src/glad.c
    src/main.c
    src/gfx/vao.c
    src/gfx/vbo.c
    src/gfx/shader.c
    # src/gfx/texture.c
    src/ui/ui.c
    src/ui/menu.c
    src/ui/menu_main.c
    src/ui/menu_triangle.c
    src/ui/menu_rectangle.c
)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DCIMGUI_USE_OPENGL3 -DCIMGUI_USE_GLFW)
target_link_libraries(${PROJECT_NAME} PRIVATE cglm m glfw cimgui)
