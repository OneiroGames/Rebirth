//
// Created by dezlow on 25.09.2021.
//

#ifndef REBIRTH_APPLICATION_H
#define REBIRTH_APPLICATION_H

#ifdef __MINGW64__
#include "Engine/Platform/Windows/WindowsWindow.h"
#elif __linux__
#include "Runtime/Platform/Linux/LinuxWindow.h"
#endif


#include "Runtime/OpenGL/Shader.h"
#include "Runtime/OpenGL/VertexArray.h"
#include "Runtime/OpenGL/VertexBuffer.h"
#include "Runtime/OpenGL/VertexBufferLayout.h"
#include "Runtime/OpenGL/IndexBuffer.h"
#include "Runtime/OpenGL/Texture.h"
#include "Runtime/OpenGL/Text.h"

#include "Editor/Lua/LuaTextBox.h"
#include "Editor/Lua/LuaConfig.h"
#include "Editor/Lua/LuaImage.h"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "stb/stb_image.h"

class Application
{
public:
    Application();
    ~Application();

    void Init();
    void Run();
private:
    bool UpdateImage(LuaImage* img, uint32_t& it, glm::mat4& MVP);

    sol::state lua;
    VertexArray mVAO;
    VertexBuffer mVBO;
    IndexBuffer mEBO;
    WindowProperties mWindowProps{};

    uint32_t NewBGId{};

    void NextStatement();

    Text mTextRender;
    Text mTextNameRender;
    LuaConfig mConfigs;

    LuaTextBox mTextBox;

    uint16_t mCurrentIterator{};
};


#endif //REBIRTH_APPLICATION_H
