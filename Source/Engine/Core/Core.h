//
// Created by dezlow on 29.09.2021.
//

#ifndef REBIRTH_CORE_H
#define REBIRTH_CORE_H

#include <iostream>
#include <vector>
#include <deque>

#include "Engine/Lua/LuaImage.h"

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
    const char* content;
    const LuaImage* image;
};

#endif //REBIRTH_CORE_H
