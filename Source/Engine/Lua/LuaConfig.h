//
// Created by dezlow on 28.09.2021.
//

#ifndef REBIRTH_LUACONFIG_H
#define REBIRTH_LUACONFIG_H

#include "sol/sol.hpp"

class LuaConfig
{
public:
    LuaConfig() = default;
public:
    void Run(sol::state& lua, const std::string& cfgFile);

    [[nodiscard]] unsigned int GetWindowWidth() const
    {
        return mWindowConfigs["width"].get<unsigned int>();
    }

    [[nodiscard]] unsigned int GetWindowHeight() const
    {
        return mWindowConfigs["height"].get<unsigned int>();
    }

    [[nodiscard]] std::string GetWindowTitle() const
    {
        return mWindowConfigs["title"].get<std::string>();
    }
private:
    sol::table mConfigs;
    sol::table mWindowConfigs;
};


#endif //REBIRTH_LUACONFIG_H
