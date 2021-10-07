//
// Created by dezlow on 05.10.2021.
//

#ifndef REBIRTH_LUACORE_H
#define REBIRTH_LUACORE_H


#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

class LuaCore
{
public:
    static void Run(sol::state& lua);
};


#endif //REBIRTH_LUACORE_H
