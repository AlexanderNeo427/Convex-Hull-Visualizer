#include "Application.h"

int main( void )
{
    auto app = std::make_unique<Application>();

    app->OnInitialize();
    while (app->IsRunning())
    {
        app->OnUpdate(GetFrameTime());
        app->OnRender();
    }
    app->OnExit();

    return EXIT_SUCCESS;
}

