//
// Created by dezlow on 28.09.2021.
//

#ifndef REBIRTH_LUACONFIG_H
#define REBIRTH_LUACONFIG_H

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

class LuaConfig
{
public:
    LuaConfig() = default;
public:
    void Run(sol::state& lua, const std::string& cfgFile);

    [[nodiscard]] uint32_t GetWindowWidth() const
    {
        return mWindowConfigs["width"].get<uint32_t>();
    }

    [[nodiscard]] uint32_t GetWindowHeight() const
    {
        return mWindowConfigs["height"].get<uint32_t>();
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
