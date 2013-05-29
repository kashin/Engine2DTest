#include "engineapplication.h"

int main()
{
    int result = EngineApplication::instance().start();
    return result;
}
