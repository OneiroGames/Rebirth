//
// Created by dezlow on 17.09.2021.
//

#include "Engine/Core/Application.h"

int main()
{
    auto* app = new Application;

    app->Init();
    app->Run();

    return 0;
}