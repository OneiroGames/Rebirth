//
// Created by Dezlow on 29.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef REBIRTH_CORE_H
#define REBIRTH_CORE_H

#include <string>
#include <vector>
#include <deque>

#include "Editor/Lua/LuaImage.h"

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
    LuaImage* image;
};

#endif //REBIRTH_CORE_H
