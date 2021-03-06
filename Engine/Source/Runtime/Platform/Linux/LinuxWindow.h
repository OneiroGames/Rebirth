//
// Created by Dezlow on 22.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#ifdef __linux

#pragma once

#ifndef REBIRTH_LINUXWINDOW_H
#define REBIRTH_LINUXWINDOW_H

#include "Runtime/Platform/Platform.h"

class WindowHnd
{
public:
    static WindowProperties CreateWindow(const uint32_t& width, const uint32_t& height, const char* title);
};

#endif //REBIRTH_LINUXWINDOW_H

#endif //__linux__