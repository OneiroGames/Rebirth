//
// Created by Dezlow on 22.10.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef REBIRTH_LUATEXTBOX_H
#define REBIRTH_LUATEXTBOX_H

#include "Editor/Lua/LuaImage.h"
#include "glm/glm.hpp"

class LuaTextBox
{
public:
    LuaTextBox() = default;
    ~LuaTextBox() = default;

    void Init(const std::string& pathToImg);

    LuaImage* GetImage()
    {
        return &mTextBoxImage;
    }

    [[nodiscard]] bool DissolveEnabled() const
    {
        return mDissolve;
    }

    [[nodiscard]] bool ReDissolveEnabled() const
    {
        return mReDissolve;
    }

    [[nodiscard]] bool isShowed() const
    {
        return mTextBoxImage.GetCurrentAlpha() > 1.0f;
    }

    void Update(const float& dt);
    void Draw(const glm::mat4& MVP);

    void SetDissolveEnabled();
    void SetReDissolveEnabled();
private:
    bool mReDissolve = false;
    bool mDissolve = false;
    float mCurrentAlpha = 0.0f;
    float mCurrentReAlpha = 1.0f;

    LuaImage mTextBoxImage;
};


#endif //REBIRTH_LUATEXTBOX_H
