#include "engineapplication.h"

int main()
{
    EngineApplication* app = new EngineApplication();
    int result = app->start();
    return result;
}
