cmake_minimum_required(VERSION 3.20)

project(Rebirth)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_BINARY_DIR "../bin/${CMAKE_SYSTEM_NAME}/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR}/")
file(COPY examples/simplenovel/ DESTINATION ${CMAKE_BINARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

include_directories(Engine/Source/ThirdParty/)
include_directories(Engine/Source/ThirdParty/sol2/include/)
include_directories(Engine/Source/ThirdParty/freetype/include/)
include_directories(Engine/Source/ThirdParty/lua51/src)
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
add_subdirectory(Engine/Source/ThirdParty/glm)
add_subdirectory(Engine/Source/ThirdParty/freetype)
add_subdirectory(Engine/Source/ThirdParty/lua51)
target_link_libraries(${CMAKE_PROJECT_NAME}
        glfw
        glm
        freetype
        OpenGL::GL
        lua_static
        #OpenGL::GLU
        )
