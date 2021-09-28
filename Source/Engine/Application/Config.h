//
// Created by dezlow on 28.09.2021.
//

#ifndef REBIRTH_CONFIG_H
#define REBIRTH_CONFIG_H

#include "lua5.1/lua.h"

class Config
{
public:
    Config() : mWindowWidth(1280), mWindowHeight(720), mWindowTitle("Visual Novel"), mGameStartFile("script.lua") {}
public:
    void Run(lua_State* L);

    unsigned int GetWindowWidth() const
    {
        return mWindowWidth;
    }

    unsigned int GetWindowHeight() const
    {
        return mWindowHeight;
    }

    const char* GetWindowTitle() const
    {
        return mWindowTitle;
    }

    const char* GetGameStartFile() const
    {
        return mGameStartFile;
    }

private:
    const char* mGameStartFile;
    unsigned int mWindowWidth;
    unsigned int mWindowHeight;
    const char* mWindowTitle;
};


#endif //REBIRTH_CONFIG_H
