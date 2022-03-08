#include "Application.h"

int main()
{
    auto app = std::make_unique<Application>();
    app->OnInitialize();
    
    while (app->IsRunning())
    {
        app->OnUpdate(GetFrameTime());
        app->OnRender();
    }
    return 0;
}

