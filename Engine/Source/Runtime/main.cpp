//
// Created by Dezlow on 17.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#include "Runtime/Core/Application.h"

int main()
{
    auto* app = new Application;

    app->Init();
    app->Run();

    return 0;
}