//
// Created by dezlow on 17.09.2021.
//

#ifndef REBIRTH_PLATFORM_H
#define REBIRTH_PLATFORM_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "OpenGL/ogl4.5.hpp"


struct WindowProperties
{
    GLFWwindow* window;
    int width;
    int height;
    const char* title;
};

#endif //REBIRTH_PLATFORM_H
