//
// Created by dezlow on 15.11.2021.
//

#include "LuaSprite.h"
#include "Runtime/Core/Core.h"

extern const char* vertexShaderSrc;
extern const char* fragmentShaderSrc;
extern std::vector<VNStatementInfo> StatementsList;

void LuaSprite::Show()
{
    StatementsList.push_back({VNStatements::SHOWSPRITE, {}, nullptr, this});
}

void LuaSprite::Hide()
{
    StatementsList.push_back({VNStatements::HIDESPRITE, {}, nullptr, this});
}

void LuaSprite::Load()
{
    mSpriteLoaded = true;
    mSpriteShader.LoadFromSource(vertexShaderSrc, fragmentShaderSrc);
    mSpriteTexture.Load(mSpritePath);

    mSpriteShader.use();
    mSpriteShader.SetUniform<int>("uTextureWidth", mSpriteTexture.width);
    mSpriteShader.SetUniform<int>("uTextureHeight", mSpriteTexture.height);
}

void LuaSprite::UnLoad()
{
    mSpriteLoaded = false;
    mSpriteShader.UnLoad();
    mSpriteTexture.UnLoad();
}
