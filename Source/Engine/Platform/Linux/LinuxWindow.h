//
// Created by dezlow on 22.09.2021.
//

#ifndef REBIRTH_LINUXWINDOW_H
#define REBIRTH_LINUXWINDOW_H

#ifdef __linux__

#include "Engine/Platform/Platform.h"

class WindowHnd
{
public:
    static WindowProperties CreateWindow(const uint32_t& width, const uint32_t& height, const char* title);
};

#endif

#endif //REBIRTH_LINUXWINDOW_H
