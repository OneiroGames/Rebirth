//
// Created by dezlow on 15.11.2021.
//

#ifndef REBIRTH_LUASPRITE_H
#define REBIRTH_LUASPRITE_H

#include "Runtime/OpenGL/Shader.h"
#include "Runtime/OpenGL/Texture.h"
#include "Runtime/OpenGL/Transition.h"

#include <utility>

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

class LuaSprite
{
public:
    LuaSprite() = default;
    explicit LuaSprite(std::string path) : mSpritePath("game/data/" + std::move(path)) { mSpriteTransition.SetSprite(this); }

    void Show();
    void Hide();

    void Load();
    void UnLoad();

    float GetCurrentAlpha() const { return mCurrentAlpha; }

    void SetAlpha(const float& alpha) { mSpriteShader.SetUniform<float>("uTextureAlpha", alpha); mCurrentAlpha = alpha; }

    Shader* GetShader() { return &mSpriteShader; }
    Texture* GetTexture() { return &mSpriteTexture; }
    Transition* GetTransition() { return &mSpriteTransition; }

    bool isLoaded() { return mSpriteLoaded; }
private:
    std::string mSpritePath;

    Transition mSpriteTransition;

    float mCurrentAlpha = 0.0f;
    Shader mSpriteShader;
    Texture mSpriteTexture;

    bool mSpriteLoaded = false;

};


#endif //REBIRTH_LUASPRITE_H
