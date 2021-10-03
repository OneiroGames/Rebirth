//
// Created by dezlow on 28.09.2021.
//

#include "Config.h"

void Config::Run(sol::state& lua)
{
    mConfigs = lua.create_named_table("config");
    mWindowConfigs = mConfigs.create_named("window");

    mWindowConfigs["title"] = "Visual Novel";
    mWindowConfigs["width"] = 1280;
    mWindowConfigs["height"] = 720;
}
