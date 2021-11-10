//
// Created by dezlow on 29.09.2021.
//

#ifndef REBIRTH_CORE_H
#define REBIRTH_CORE_H

#include <iostream>
#include <vector>
#include <deque>

#include "Editor/Lua/LuaSprite.h"
#include "Editor/Lua/LuaScene.h"

enum class VNStatements
{
    TEXT,
    SCENE,
    SHOWSPRITE,
    HIDESPRITE
};

struct VNStatementInfo
{
    const VNStatements command;
    std::string content;
    LuaScene* scene;
    LuaSprite* sprite;
};

#endif //REBIRTH_CORE_H
