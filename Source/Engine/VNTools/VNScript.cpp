//
// Created by dezlow on 28.09.2021.
//

#include <vector>
#include "VNScript.h"
#include "lua5.1/lua.h"
#include "lua5.1/lauxlib.h"
#include "LuaBridge/LuaBridge.h"
#include "Engine/Core/Core.h"
extern std::vector<VNStatementInfo> StatementsList;

namespace lb = luabridge;

#include "Engine/Lua/LuaImage.h"

void text(const char* text)
{
    StatementsList.push_back({VNStatements::TEXT, text});
}

void scene(const LuaImage* image)
{
    StatementsList.push_back({VNStatements::SCENE, nullptr, image});
}

void VNScript::Run(lua_State* L)
{
    lb::getGlobalNamespace(L)
    .addFunction("text", text)
    .addFunction("scene", scene)
    .beginClass<LuaImage>("Image")
            .addConstructor <void (*) (const char*)> ()
    .endClass()
    .beginClass<LuaImage>("Sprite")
            .addConstructor <void (*) (const char*)> ()
            .addFunction("show", &LuaImage::show)
            .addFunction("hide", &LuaImage::hide)
    .endClass();
}
