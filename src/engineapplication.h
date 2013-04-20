#ifndef ENGINEAPPLICATION_H
#define ENGINEAPPLICATION_H

class EngineApplication
{
public:
    EngineApplication();

    /**
     * @brief start Starts application's event and rendering loops.
     */
    int start();
};

#endif // ENGINEAPPLICATION_H
