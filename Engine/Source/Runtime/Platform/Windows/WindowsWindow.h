//
// Created by Dezlow on 17.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#ifdef _WIN32

#pragma once

#ifndef REBIRTH_WINDOWSWINDOW_H
#define REBIRTH_WINDOWSWINDOW_H

#include "Runtime/Platform/Platform.h"

class WindowHnd
{
public:
    static WindowProperties CreateWindow(const uint32_t& width, const uint32_t& height, const char* title);
};

#endif //REBIRTH_WINDOWSWINDOW_H

#endif //_WIN32