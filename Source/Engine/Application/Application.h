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
#include "Engine/Lua/LuaConfig.h"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "stb/stb_image.h"

#include "Engine/OpenGL/Text.h"

class Application
{
public:
    Application();
    ~Application();

    void Init();
    void Run();
private:
    sol::state lua;
    VertexArray mVAO;
    VertexBuffer mVBO;
    IndexBuffer mEBO;
    WindowProperties mWindowProps{};

    std::vector<uint8_t> mSprIDsRemove;
    std::vector<uint8_t> mSprIDsShow;
    uint8_t mBgIDRemove{};


    Text mTextRender;
    LuaConfig mConfigs;

    unsigned short int mCurrentIterator{};
};


#endif //REBIRTH_APPLICATION_H
