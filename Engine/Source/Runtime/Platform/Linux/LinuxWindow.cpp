//
// Created by dezlow on 22.09.2021.
//

#ifdef __linux__

#include <stdexcept>
#include "LinuxWindow.h"

WindowProperties WindowHnd::CreateWindow(const uint32_t& width, const uint32_t& height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 2);

    WindowProperties windowProps {
            glfwCreateWindow((int)width, (int)height, title, nullptr, nullptr),
            (int)width, (int)height, title
    };

    if (windowProps.window == nullptr)
        std::runtime_error("Failed to create window!");

    glfwMakeContextCurrent(windowProps.window);
    glfwSwapInterval(1);

    gl::Enable(gl::SAMPLES);

    return windowProps;
}

#endif