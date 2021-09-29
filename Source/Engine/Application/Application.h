//
// Created by dezlow on 25.09.2021.
//

#ifndef REBIRTH_APPLICATION_H
#define REBIRTH_APPLICATION_H


#ifdef __MINGW64__
#include "Engine/Platform/Windows/WindowsWindow.h"
#elif __linux__
#include "Engine/Platform/Linux/LinuxWindow.h"
#endif

#include <deque>

#include "Engine/OpenGL/Shader.h"
#include "Engine/OpenGL/VertexArray.h"
#include "Engine/OpenGL/VertexBuffer.h"
#include "Engine/OpenGL/VertexBufferLayout.h"
#include "Engine/OpenGL/IndexBuffer.h"
#include "Engine/OpenGL/Texture.h"
#include "Config.h"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "stb/stb_image.h"

#include "lua5.1/lua.h"
#include "lua5.1/lauxlib.h"
#include "lua5.1/lualib.h"
#include "LuaBridge/LuaBridge.h"

namespace lb = luabridge;

class Application
{
public:
    Application();
    ~Application();

    void Run();
private:
    VertexArray mVAO;
    VertexBuffer mVBO;
    IndexBuffer mEBO;
    WindowProperties mWindowProps{};

    Config mConfigs;

    unsigned short int mCurrentIterator;
};


#endif //REBIRTH_APPLICATION_H
