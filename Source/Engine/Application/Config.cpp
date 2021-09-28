//
// Created by dezlow on 28.09.2021.
//

#include "Config.h"

#include "lua5.1/lua.h"
#include "lua5.1/lauxlib.h"
#include "lua5.1/lualib.h"
#include "LuaBridge/LuaBridge.h"

namespace lb = luabridge;

void Config::Run(lua_State* L)
{
    lb::getGlobalNamespace(L)
    .beginNamespace("config")
        .beginNamespace("window")
            .addProperty("width", &mWindowWidth)
            .addProperty("height", &mWindowHeight)
            .addProperty("title", &mWindowTitle)
        .endNamespace()
        .beginNamespace("game")
            .addProperty("start", &mGameStartFile)
        .endNamespace()
    .endNamespace();
}
