cmake_minimum_required(VERSION 3.20)

project(Rebirth)

set(CMAKE_CXX_STANDARD 17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#set(CMAKE_EXE_LINKER_FLAGS "-v -lfreetype")

include_directories(Engine/Source/ThirdParty/)
include_directories(Engine/Source/)

find_package(OpenGL REQUIRED)
find_package(Lua51 REQUIRED)
find_package(Freetype REQUIRED)
find_package(SFML 2.5 COMPONENTS audio REQUIRED)

include_directories(${FREETYPE_INCLUDE_DIRS})

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
        )

add_subdirectory(Engine/Source/ThirdParty/glfw)
add_subdirectory(Engine/Source/ThirdParty/glad)
add_subdirectory(Engine/Source/ThirdParty/glm)
target_link_libraries(${CMAKE_PROJECT_NAME}
        glfw
        glad
        glm
        ${CMAKE_DL_LIBS}
        ${LUA_LIBRARIES}
        ${FREETYPE_LIBRARY}
        OpenGL::GL
        #OpenGL::GLU
        #sfml-audio
        )
