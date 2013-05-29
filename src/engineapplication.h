#ifndef ENGINEAPPLICATION_H
#define ENGINEAPPLICATION_H

class SceneManager;

class EngineApplication
{
public:
    EngineApplication();

    /**
     * @brief start Starts application's event and rendering loops.
     */
    int start();

    /**
     * @brief setSceneManager sets the Applicaiton's SceneManager
     * @param sceneManager SceneManager that should be used by Applicaiton.
     */
    void setSceneManager(SceneManager* sceneManager);
};

#endif // ENGINEAPPLICATION_H
