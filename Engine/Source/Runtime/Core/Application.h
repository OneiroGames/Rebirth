//
// Created by Dezlow on 25.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef REBIRTH_APPLICATION_H
#define REBIRTH_APPLICATION_H

#ifdef __linux__
#include "Runtime/Platform/Linux/LinuxWindow.h"
#elif _WIN32
#include "Runtime/Platform/Windows/WindowsWindow.h"
#else
#error UNKOWN PLATFORM!
#endif

#include "Runtime/OpenGL/Shader.h"
#include "Runtime/OpenGL/VertexArray.h"
#include "Runtime/OpenGL/VertexBuffer.h"
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
    bool UpdateImage(LuaImage* img, uint32_t it, glm::mat4& MVP);
    void NextStatement();

    sol::state lua{};
    VertexArray mVAO{};
    VertexBuffer mVBO{};
    IndexBuffer mEBO{};
    WindowProperties mWindowProps{};
    Text mTextRender{};
    Text mTextNameRender{};
    LuaConfig mConfigs{};
    LuaTextBox mTextBox{};

    uint32_t NewBGId{};
    uint16_t mCurrentIterator{};
};


#endif //REBIRTH_APPLICATION_H
