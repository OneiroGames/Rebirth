//
// Created by dezlow on 28.09.2021.
//
#pragma once

#ifndef REBIRTH_VNSCRIPT_H
#define REBIRTH_VNSCRIPT_H

#include "lua5.1/lua.h"

class VNScript
{
public:
    static void Run(lua_State* L);
};


#endif //REBIRTH_VNSCRIPT_H
