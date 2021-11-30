//
// Created by dezlow on 15.10.2021.
//

#include "Transition.h"
#include "Editor/Lua/LuaImage.h"
#include "Runtime/Core/Core.h"
extern std::deque<LuaImage*> images;

void Transition::UpdateScene(const float dt)
{
    if (mData.image->IsSprite())
    {
        return;
    }

    if (mData.type == TransitionTypes::NONE && mData.image->GetCurrentAlpha() <= 0.0f)
    {
        mData.image->Load();
        mData.image->SetAlpha(1.0f);
    }

    if (mData.type == TransitionTypes::DISSOLVE && mData.image->GetCurrentAlpha() < 1.0f)
    {
        mTransition = true;
        if (!mData.image->isLoaded())
        {
            mData.image->Load();
        }
        else
        {
            mData.currentAlpha += dt * mData.speed;
            mData.image->SetAlpha(mData.currentAlpha);
        }

        if (mData.currentAlpha >= 1.0f)
        {
            mData.currentAlpha = 0.0f;
            mTransition = false;
        }
    }
}

bool Transition::isShowed()
{
    return mData.image->GetCurrentAlpha() >= 1.0f;
}

void Transition::SetImage(LuaImage* image)
{
    mData.image = image;
}

void Transition::SetType(const TransitionTypes& type)
{
    mData.type = type;
}

void Transition::UpdateSprite(const float dt)
{
    if (!mData.image->IsSprite())
    {
        return;
    }

    if (mData.type == TransitionTypes::NONE && mData.image->GetCurrentAlpha() <= 0.0f)
    {
        mData.image->Load();
        mData.image->SetAlpha(1.0f);
    }

    if (mData.type == TransitionTypes::DISSOLVE && mData.image->GetCurrentAlpha() < 1.0f)
    {
        mTransition = true;
        if (!mData.image->isLoaded())
        {
            mData.image->Load();
        }
        else
        {
            mData.currentAlpha += dt * (mData.speed + 0.5f);
            mData.image->SetAlpha(mData.currentAlpha);
        }

        if (mData.currentAlpha >= 1.0f)
        {
            mData.currentAlpha = 0.0f;
            mTransition = false;
        }
    }
}

void Transition::UpdateReSprite(const float dt)
{
    if (!mData.image->IsSprite())
    {
        return;
    }

    if (mData.type == TransitionTypes::REDISSOLVE && mData.image->GetCurrentAlpha() > 0.0f)
    {
        mData.currentReAlpha -= dt * (mData.speed + 1.0f);
        mData.image->SetAlpha(mData.currentReAlpha);

        mTransition = true;

        if (mData.image->GetCurrentAlpha() < 0.0f)
        {
            mData.image->UnLoad();
            auto it = images.begin();
            for (auto& img : images)
            {
                if (img == mData.image)
                {
                    images.erase(it);
                }
                it++;
            }
            mData.currentReAlpha = 1.0f;
            mData.currentAlpha = 0.0f;
            mTransition = false;
        }
    }
}

void Transition::UpdateReScene(const float dt)
{
    if (mData.image->IsSprite())
    {
        return;
    }

    if (mData.type == TransitionTypes::REDISSOLVE && mData.image->GetCurrentAlpha() > 0.0f)
    {
        mTransition = true;
        mData.currentReAlpha -= dt * mData.speed;
        mData.image->SetAlpha(mData.currentReAlpha);

        if (mData.image->GetCurrentAlpha() < 0.1f)
        {
            mData.image->UnLoad();
            mData.currentReAlpha = 1.0f;
            mReSceneEnd = true;
            mData.currentAlpha = 0.0f;
            images.erase(images.begin());
        }
    }
}
