//
// Created by dezlow on 15.11.2021.
//

#ifndef REBIRTH_LUASCENE_H
#define REBIRTH_LUASCENE_H

#include "Runtime/OpenGL/Shader.h"
#include "Runtime/OpenGL/Texture.h"
#include "Runtime/OpenGL/Transition.h"

#include <utility>

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

class LuaScene
{
public:
    LuaScene() = default;
    ~LuaScene() {}

    void Destroy() { this->~LuaScene(); }

    explicit LuaScene(std::string path) : mScenePath("game/data/" + std::move(path)) { mSceneTransition.SetScene(this); }

    void Load();
    void UnLoad();

    float GetCurrentAlpha() const { return mCurrentAlpha; }
    void SetAlpha(const float& alpha) { mSceneShader.SetUniform<float>("uTextureAlpha", alpha); mCurrentAlpha = alpha; std::cout << "ssdvdsvsvVv" << std::endl; }

    void ChangeScenePath(const std::string& path) { mScenePath = path; mCurrentAlpha = 0.0f; }
    const std::string& GetPath() { return mScenePath; }

    Shader* GetShader() { return &mSceneShader; }
    Texture* GetTexture() { return &mSceneTexture; }
    Transition* GetTransition() { return &mSceneTransition; }

    bool isLoaded() const { return mSceneLoaded; }
private:
    std::string mScenePath;

    Transition mSceneTransition;

    float mCurrentAlpha = 0.0f;
    Shader mSceneShader;
    Texture mSceneTexture;

    bool mSceneLoaded = false;
};


#endif //REBIRTH_LUASCENE_H
