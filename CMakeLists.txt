cmake_minimum_required(VERSION 3.20)

project(Rebirth)

set(CMAKE_CXX_STANDARD 17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(ThirdParty/)

find_package(OpenGL REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
        Source/main.cpp
        )

add_subdirectory(ThirdParty/GLFW)
add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/glm)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw glad glm OpenGL::GL)