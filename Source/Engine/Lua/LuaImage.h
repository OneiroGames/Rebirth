//
// Created by dezlow on 29.09.2021.
//

#ifndef REBIRTH_LUAIMAGE_H
#define REBIRTH_LUAIMAGE_H


#include "Engine/OpenGL/Shader.h"
#include "Engine/OpenGL/Texture.h"
#include "Engine/OpenGL/Transition.h"

#include <utility>

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

class LuaImage
{
public:
    explicit LuaImage(std::string path) : mImagePath(std::move(path)) { mImageTransition.SetImage(this); }

    void show();
    void hide();

    [[nodiscard]] bool IsSprite() const { return mIsSprite; }
    [[nodiscard]] float GetCurrentAlpha() const { return mCurrentAlpha; }

    void SetAlpha(const float& alpha) { mImageShader.SetUniform<float>("uTextureAlpha", alpha); mCurrentAlpha = alpha; }

    void Load();
    void UnLoad();

    [[nodiscard]] Shader* GetShader() { return &mImageShader; }
    [[nodiscard]] Texture* GetTexture() { return &mImageTexture; }
    Transition* GetTransition() { return &mImageTransition; }

    bool isLoaded() { return mImageLoaded; }
private:
    bool mIsSprite = false;

    Transition mImageTransition;

    float mCurrentAlpha = 0.0f;

    std::string mImagePath;
    Shader mImageShader;
    Texture mImageTexture;

    bool mImageLoaded = false;
};


#endif //REBIRTH_LUAIMAGE_H
