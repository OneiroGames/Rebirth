//
// Created by dezlow on 28.09.2021.
//
#pragma once

#ifndef REBIRTH_VNSCRIPT_H
#define REBIRTH_VNSCRIPT_H

#include "sol/sol.hpp"

class VNScript
{
public:
    static void Run(sol::state& lua);

    void CreateImg(const char* path);
};


#endif //REBIRTH_VNSCRIPT_H
