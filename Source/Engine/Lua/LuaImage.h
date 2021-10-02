//
// Created by dezlow on 29.09.2021.
//

#ifndef REBIRTH_LUAIMAGE_H
#define REBIRTH_LUAIMAGE_H


#include "Engine/OpenGL/Shader.h"
#include "Engine/OpenGL/Texture.h"

class LuaImage
{
public:
    LuaImage();

    explicit LuaImage(const char* path);

    void show();
    void hide();

    void Load();
    void UnLoad();

    [[nodiscard]] Shader GetShader() const { return mImageShader; }
    [[nodiscard]] Texture GetTexture() const { return mImageTexture; }
private:
    Shader mImageShader;
    Texture mImageTexture;

    const char* mImagePath;
};


#endif //REBIRTH_LUAIMAGE_H
