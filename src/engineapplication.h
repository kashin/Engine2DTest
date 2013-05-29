#ifndef ENGINEAPPLICATION_H
#define ENGINEAPPLICATION_H

#include <irrlicht/irrList.h>

namespace irr {
    class SEvent;
}

class SceneManager;
class IGestureRecognizer;

/**
  * Starting point of the application.
  */
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
     * If application had set SceneManager, then previous SceneManager is deleted.
     * @c EngineApplication become owns the SceneManager.
     * @param sceneManager SceneManager that should be used by Applicaiton.
     */
    void setSceneManager(SceneManager* sceneManager);

    /**
      * Adds gesture recognizer for events in Application.
      */
    void addGestureRecognizer(IGestureRecognizer* recognizer);

    /**
      * @brief handleEvent handles Irrlichts events and passes our own Events
      * to SceneManager.
      */
    virtual bool handleEvent(const irr::SEvent& event);

    /**
      * Called when it is time to draw all our content.
      */
    void draw();

    static EngineApplication & instance();

protected:
    virtual ~EngineApplication();

private:
    SceneManager* mSceneManager;
    irr::core::list<IGestureRecognizer*> mGestureRecognizers;
};

#endif // ENGINEAPPLICATION_H
