cmake_minimum_required(VERSION 3.20)

project(Rebirth)

set(CMAKE_CXX_STANDARD 17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
find_package(Lua51 REQUIRED)
find_package(Freetype REQUIRED)

include_directories(ThirdParty/)
include_directories(Source/)
include_directories(${FREETYPE_INCLUDE_DIRS})

file(GLOB RebirthSRC
        "Source/*.h"
        "Source/*.cpp"
        "Source/Engine/Core/*.h"
        "Source/Engine/Core/*.cpp"
        "Source/Engine/Platform/Platform.h"
        "Source/Engine/Platform/*/*.h"
        "Source/Engine/Platform/*/*.cpp"
        "Source/Engine/OpenGL/*.h"
        "Source/Engine/OpenGL/*.cpp"
        "Source/Engine/Application/Application.cpp"
        "Source/Engine/Application/Application.h"
        "Source/Engine/Core/*.cpp"
        "Source/Engine/Core/*.h"
        "Source/Engine/Lua/*.cpp"
        "Source/Engine/Lua/*.h"
        )

add_executable(${CMAKE_PROJECT_NAME}
        Source/main.cpp

        ${RebirthSRC}

        ThirdParty/ImGui/imgui_widgets.cpp
        ThirdParty/ImGui/imgui.cpp
        ThirdParty/ImGui/imgui_draw.cpp
        ThirdParty/ImGui/imgui_tables.cpp
        ThirdParty/ImGui/backends/imgui_impl_glfw.cpp
        ThirdParty/ImGui/backends/imgui_impl_opengl3.cpp
        )

add_subdirectory(ThirdParty/GLFW)
add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/glm)
target_link_libraries(${CMAKE_PROJECT_NAME}
        glfw
        glad
        glm
        ${LUA_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        OpenGL::GL
        )