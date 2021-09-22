//
// Created by dezlow on 17.09.2021.
//

#ifndef REBIRTH_WINDOWSWINDOW_H
#define REBIRTH_WINDOWSWINDOW_H

#ifdef __MINGW64__

#include "Engine/Core/Platform/Platform.h"

class WindowHnd
{
public:
    static WindowProperties CreateWindow(unsigned int width, unsigned int height, const char* title);
};

#endif

#endif //REBIRTH_WINDOWSWINDOW_H
