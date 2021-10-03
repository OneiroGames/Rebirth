//
// Created by dezlow on 28.09.2021.
//

#ifndef REBIRTH_CONFIG_H
#define REBIRTH_CONFIG_H

#include "sol/sol.hpp"

class Config
{
public:
    Config() {}
public:
    void Run(sol::state& lua);

    unsigned int GetWindowWidth() const
    {
        return mWindowConfigs["width"].get<unsigned int>();
    }

    unsigned int GetWindowHeight() const
    {
        return mWindowConfigs["height"].get<unsigned int>();
    }

    const char* GetWindowTitle() const
    {
        return mWindowConfigs["title"].get<const char*>();
    }

    const char* GetGameStartFile() const
    {
        return "script.lua";
    }

private:
    sol::table mConfigs;
    sol::table mWindowConfigs;
};


#endif //REBIRTH_CONFIG_H
