cmake_minimum_required(VERSION 3.20)

project(Rebirth)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(Engine/Source/ThirdParty/)
include_directories(Engine/Source/ThirdParty/sol2/include/)
include_directories(Engine/Source/ThirdParty/freetype/include/)
include_directories(Engine/Source/ThirdParty/Lua/)
include_directories(Engine/Source/)

find_package(OpenGL REQUIRED)

file(GLOB OGLLG_SRC
        "Engine/Source/ThirdParty/OpenGL/ogl4.5.cpp")

file(GLOB RebirthSRC
        "Engine/Source/Runtime/*.h"
        "Engine/Source/Runtime/*.cpp"
        "Engine/Source/Runtime/Core/*.h"
        "Engine/Source/Runtime/Core/*.cpp"
        "Engine/Source/Runtime/Platform/Platform.h"
        "Engine/Source/Runtime/Platform/*/*.h"
        "Engine/Source/Runtime/Platform/*/*.cpp"
        "Engine/Source/Runtime/OpenGL/*.h"
        "Engine/Source/Runtime/OpenGL/*.cpp"
        "Engine/Source/Editor/Lua/*.cpp"
        "Engine/Source/Editor/Lua/*.h"
        )

add_executable(${CMAKE_PROJECT_NAME}
        ${RebirthSRC}
        ${OGLLG_SRC}
        )

add_subdirectory(Engine/Source/ThirdParty/glfw)
#add_subdirectory(Engine/Source/ThirdParty/glad)
add_subdirectory(Engine/Source/ThirdParty/glm)
add_subdirectory(Engine/Source/ThirdParty/freetype)
add_subdirectory(Engine/Source/ThirdParty/lua51)
#add_subdirectory(Engine/Source/ThirdParty/spdlog)
target_link_libraries(${CMAKE_PROJECT_NAME}
        glfw
        #glad
        glm
        freetype
        OpenGL::GL
        lua_static
        #spdlog
        #OpenGL::GLU
        )
