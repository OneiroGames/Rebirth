//
// Created by dezlow on 22.10.2021.
//

#ifndef REBIRTH_LUATEXTBOX_H
#define REBIRTH_LUATEXTBOX_H


#include "Editor/Lua/LuaSprite.h"
#include "glm/glm.hpp"

class LuaTextBox
{
public:
    LuaTextBox() = default;
    ~LuaTextBox() = default;

    void Init(const std::string& pathToImg);

    LuaSprite* GetSprite()
    {
        return &mTextBoxSprite;
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
        return mTextBoxSprite.GetCurrentAlpha() > 1.0f;
    }

    void Update(const float& dt);
    void Draw(glm::mat4& MVP);

    void SetDissolveEnabled();
    void SetReDissolveEnabled();
private:
    bool mReDissolve = false;
    bool mDissolve = false;
    float mCurrentAlpha = 0.0f;
    float mCurrentReAlpha = 1.0f;

    LuaSprite mTextBoxSprite;
};


#endif //REBIRTH_LUATEXTBOX_H
