//
// Created by dezlow on 29.09.2021.
//

#include "LuaImage.h"

#include "glm/glm.hpp"

extern const char* vertexShaderSrc;
extern const char* fragmentShaderSrc;
#include "Engine/Core/Core.h"
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
    mImageShader.SetUniform<int>("uTextureWidth", mImageTexture.width);
    mImageShader.SetUniform<int>("uTextureHeight", mImageTexture.height);
}

void LuaImage::UnLoad()
{
    mImageLoaded = false;
    mImageShader.UnLoad();
    mImageTexture.UnLoad();
}
