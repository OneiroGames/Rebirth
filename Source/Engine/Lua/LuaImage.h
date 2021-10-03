//
// Created by dezlow on 29.09.2021.
//

#ifndef REBIRTH_LUAIMAGE_H
#define REBIRTH_LUAIMAGE_H


#include "Engine/OpenGL/Shader.h"
#include "Engine/OpenGL/Texture.h"

#include <iostream>

#include "sol/sol.hpp"

class LuaImage
{
public:
    explicit LuaImage(const char* path) : mImagePath(path) {}

    void show();
    void hide();

    void Load();
    void UnLoad();

    [[nodiscard]] Shader GetShader() const { return mImageShader; }
    [[nodiscard]] Texture GetTexture() const { return mImageTexture; }
    const char* mImagePath;
private:
    Shader mImageShader;
    Texture mImageTexture;
};


#endif //REBIRTH_LUAIMAGE_H
