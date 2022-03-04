#include "Application.h"

int main()
{
    auto app = std::make_unique<Application>();
    app->Run();

    return 0;
}

