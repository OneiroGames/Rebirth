//
// Created by dezlow on 05.10.2021.
//

#include <vector>
#include "LuaCore.h"
#include "Runtime/Core/Core.h"
#include "Editor/Lua/LuaScene.h"
#include "Editor/Lua/LuaSprite.h"

extern std::vector<VNStatementInfo> StatementsList;

void text(const std::string& text)
{
    StatementsList.push_back({VNStatements::TEXT, text, nullptr, nullptr});
}

void scene(LuaScene* scene)
{
    StatementsList.push_back({VNStatements::SCENE, {}, scene, nullptr});
}

void LuaCore::Run(sol::state& lua)
{
    auto rebirth = lua.create_named_table("rebirth");
    rebirth.set_function("DisplayText", text);
    lua.set_function("scene", scene);
    lua.new_usertype<LuaScene>("Scene", sol::call_constructor,
                               sol::factories([](const char* path) {
                                   return std::make_shared<LuaScene>(path);
                               }));

    lua.new_usertype<LuaSprite>("Sprite", sol::call_constructor,
                               sol::factories([](const char* path) {
                                   return std::make_shared<LuaSprite>(path);
                               }), "show", &LuaSprite::Show, "hide", &LuaSprite::Hide);

    lua.script("function Class()\n"
               "local class = {}\n"
               "\tlocal mClass = {}\n"
               "\n"
               "\tclass.__index = class\n"
               "\n"
               "\tfunction mClass:__call(...)\n"
               "\t\tlocal instance = setmetatable({}, class)\n"
               "\n"
               "\t\tif type(class.init) == 'function' then\n"
               "\t\t\treturn instance, instance:init(...)\n"
               "\t\tend\n"
               "\n"
               "\t\treturn instance\n"
               "\tend\n"
               "\n"
               "\treturn setmetatable(class, mClass)\n"
               "end\n"
               "\n"
               "Character = Class()\n"
               "\n"
               "function Character:init(charname)\n"
               "\tself.charname = charname\n"
               "end\n"
               "\n"
               "function Character:__tostring()\n"
               "\treturn self.charname\n"
               "end\n"
               "\n"
               "function Character:__call(text)\n"
               "    rebirth.DisplayText(self.charname .. \": \" .. text)\n"
               "end");
}

