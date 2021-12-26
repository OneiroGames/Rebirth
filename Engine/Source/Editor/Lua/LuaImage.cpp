//
// Created by Dezlow on 29.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#include "LuaImage.h"

extern const char* vertexShaderSrc;
extern const char* fragmentShaderSrc;

#include "Runtime/Core/Core.h"
extern std::vector<VNStatementInfo> StatementsList;

void LuaImage::show()
{
    mIsSprite = true;
    StatementsList.push_back({VNStatements::SHOWSPRITE, {}, this});
}

void LuaImage::hide()
{
    mIsSprite = true;
    StatementsList.push_back({VNStatements::HIDESPRITE, {}, this});
}

void LuaImage::Load()
{
    mImageLoaded = true;
    mImageShader.LoadFromSource(vertexShaderSrc, fragmentShaderSrc);
    mImageTexture.Load(mImagePath);

    mImageShader.use();
    mImageShader.SetUniform("uTextureWidth", mImageTexture.GetWidth());
    mImageShader.SetUniform("uTextureHeight", mImageTexture.GetHeight());
}

void LuaImage::UnLoad()
{
    mImageLoaded = false;
    mImageShader.UnLoad();
    mImageTexture.UnLoad();
}
