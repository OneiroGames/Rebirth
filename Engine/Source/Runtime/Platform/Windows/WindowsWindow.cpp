//
// Created by dezlow on 17.09.2021.
//

#ifdef _WIN32

#include "WindowsWindow.h"

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
        return WindowProperties{};

    glfwMakeContextCurrent(windowProps.window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return WindowProperties{};

    // FOR MSAA
    glEnable(GL_SAMPLES);

    return windowProps;
}

#endif