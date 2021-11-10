//
// Created by dezlow on 15.10.2021.
//

#include "Transition.h"
#include "Editor/Lua/LuaSprite.h"
#include "Editor/Lua/LuaScene.h"
#include "Runtime/Core/Core.h"

extern std::deque<LuaSprite*> sprites;
extern LuaScene* scene;

void Transition::UpdateScene(const float& dt)
{
    if (!scene)
    {
        return;
    }

    if (mData.type == TransitionTypes::NONE && scene->GetCurrentAlpha() <= 0.0f)
    {
        scene->Load();
        scene->SetAlpha(1.0f);
    }

    if (mData.type == TransitionTypes::DISSOLVE && scene->GetCurrentAlpha() < 1.0f)
    {
        mTransition = true;
        if (!scene->isLoaded())
        {
            scene->Load();
        }
        else
        {
            mData.currentAlpha += dt * mData.speed;
            scene->SetAlpha(mData.currentAlpha);
        }

        if (mData.currentAlpha >= 1.0f)
        {
            mData.currentAlpha = 0.0f;
            mTransition = false;
        }
    }
}

bool Transition::isShowed() const
{
    if (mData.sprite)
    {
        return mData.sprite->GetCurrentAlpha() >= 1.0f;
    }
    else if (mData.scene)
    {
        return mData.scene->GetCurrentAlpha() >= 1.0f;
    }
}

void Transition::SetSpeed(const float& speed)
{
    mData.speed = speed;
}

void Transition::SetType(const TransitionTypes& type)
{
    mData.currentAlpha = 0.0f;
    mData.currentReAlpha = 1.0f;
    mData.type = type;
}

void Transition::UpdateSprite(const float& dt)
{
    if (mData.sprite == nullptr)
    {
        return;
    }

    if (mData.type == TransitionTypes::NONE && mData.sprite->GetCurrentAlpha() <= 0.0f)
    {
        mData.sprite->Load();
        mData.sprite->SetAlpha(1.0f);
    }

    if (mData.type == TransitionTypes::DISSOLVE && mData.sprite->GetCurrentAlpha() < 1.0f)
    {
        mTransition = true;
        if (!mData.sprite->isLoaded())
        {
            mData.sprite->Load();
        }
        else
        {
            mData.currentAlpha += dt * (mData.speed + 0.5f);
            mData.sprite->SetAlpha(mData.currentAlpha);
        }

        if (mData.currentAlpha >= 1.0f)
        {
            mData.currentAlpha = 0.0f;
            mTransition = false;
        }
    }
}

void Transition::UpdateReSprite(const float& dt)
{
    if (!mData.scene)
    {
        return;
    }

    if (mData.type == TransitionTypes::REDISSOLVE && mData.sprite->GetCurrentAlpha() > 0.0f)
    {
        mData.currentReAlpha -= dt * (mData.speed + 1.0f);
        mData.sprite->SetAlpha(mData.currentReAlpha);

        mTransition = true;

        if (mData.sprite->GetCurrentAlpha() < 0.0f)
        {
            mData.sprite->UnLoad();
            auto it = sprites.begin();
            for (auto& img : sprites)
            {
                if (img == mData.sprite)
                {
                    sprites.erase(it);
                }
                it++;
            }
            mData.currentReAlpha = 1.0f;
            mData.currentAlpha = 0.0f;
            mTransition = false;
        }
    }
}

void Transition::UpdateReScene(const float& dt)
{
    if (mData.scene == nullptr)
    {
        return;
    }

    if (mData.type == TransitionTypes::REDISSOLVE && mData.scene->GetCurrentAlpha() > 0.0f)
    {
        mTransition = true;
        mData.currentReAlpha -= dt * mData.speed;
        mData.scene->SetAlpha(mData.currentReAlpha);

        if (mData.scene->GetCurrentAlpha() < 0.1f)
        {
            mData.scene->UnLoad();
            mData.currentReAlpha = 1.0f;
            mReSceneEnd = true;
            mData.currentAlpha = 0.0f;
            mData.scene = nullptr;
        }
    }
}

void Transition::SetSprite(LuaSprite* sprite)
{
    mData.sprite = sprite;
    mData.scene = nullptr;
}

void Transition::SetScene(LuaScene* scene)
{
    mData.sprite = nullptr;
    mData.scene = scene;
}