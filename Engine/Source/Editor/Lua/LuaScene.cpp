//
// Created by dezlow on 15.11.2021.
//

#include "LuaScene.h"

extern const char* vertexShaderSrc;
extern const char* fragmentShaderSrc;

void LuaScene::Load()
{
    mSceneLoaded = true;
    mSceneShader.LoadFromSource(vertexShaderSrc, fragmentShaderSrc);
    mSceneTexture.Load(mScenePath);

    mSceneShader.use();
    mSceneShader.SetUniform<int>("uTextureWidth", mSceneTexture.width);
    mSceneShader.SetUniform<int>("uTextureHeight", mSceneTexture.height);
}

void LuaScene::UnLoad()
{
    mSceneLoaded = false;
    mSceneShader.UnLoad();
    mSceneShader.UnLoad();
}
