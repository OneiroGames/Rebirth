//
// Created by dezlow on 29.09.2021.
//

#include "LuaImage.h"
extern const char* vertexShaderSrc;
extern const char* fragmentShaderSrc;
#include "Engine/Core/Core.h"
extern std::vector<VNStatementInfo> StatementsList;

LuaImage::LuaImage(const char* path)
{
    mImagePath = path;
}

void LuaImage::show()
{
    StatementsList.push_back({VNStatements::SHOWSPRITE, nullptr, this});
}

void LuaImage::hide()
{
    StatementsList.push_back({VNStatements::HIDESPRITE, nullptr, this});
}

void LuaImage::Load()
{
    mImageShader.LoadFromSource(vertexShaderSrc, fragmentShaderSrc);
    mImageTexture.Load(mImagePath);
}

void LuaImage::UnLoad()
{
    mImageShader.UnLoad();
    mImageTexture.UnLoad();
}
