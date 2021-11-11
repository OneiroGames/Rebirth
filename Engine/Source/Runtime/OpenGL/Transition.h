//
// Created by dezlow on 15.10.2021.
//

#ifndef REBIRTH_TRANSITION_H
#define REBIRTH_TRANSITION_H

#include <string>

class LuaImage;

enum class TransitionTypes
{
    NONE,
    DISSOLVE,
    REDISSOLVE
};

class Transition
{
public:
    Transition() = default;
    ~Transition() = default;
    void SetImage(LuaImage* image);
    void SetNextImage(LuaImage* image);
    void SetSpeed(const float& speed);
    void SetType(const TransitionTypes& type);
    void UpdateScene(const float& dt);
    void UpdateSprite(const float& dt);
    void UpdateReSprite(const float& dt);
    void UpdateReScene(const float& dt);
    bool isShowed();
    bool ReSceneEnd() { return mReSceneEnd; }

    bool isShowing() { return mTransition; }
    bool isShowingRe() { return mTransitionRe; }

    float* GetCurrentAlpha() { return &mData.currentAlpha; }
private:
    bool mTransition = false;
    bool mTransitionRe = false;
    struct TransitionData
    {
        float speed = 1.0f;
        LuaImage* image;
        LuaImage* nextImage;
        TransitionTypes type = TransitionTypes::DISSOLVE;
        float currentAlpha = 0.0f;
        float currentReAlpha = 1.0f;
    };
    bool mReSceneEnd = false;
    TransitionData mData;
};


#endif //REBIRTH_TRANSITION_H
