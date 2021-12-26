//
// Created by Dezlow on 28.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#include "LuaConfig.h"

void LuaConfig::Run(sol::state& lua, const std::string& cfgFile)
{
    mConfigs = lua.create_named_table("config");
    mWindowConfigs = mConfigs.create_named("window");

    mWindowConfigs["title"] = "Visual Novel";
    mWindowConfigs["width"] = 1280;
    mWindowConfigs["height"] = 720;

    lua.do_file(cfgFile);
}
