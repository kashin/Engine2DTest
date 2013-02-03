#ifndef FIELD_H
#define FIELD_H

#include <irrlicht/path.h>
#include <irrlicht/irrTypes.h>
#include <irrlicht/irrList.h>
#include <irrlicht/rect.h>

#include "iscenenode.h"

namespace irr {
namespace video {
    class ITexture;
    class IVideoDriver;
}
    class SEvent;
}

class GraphicBlock;
class Scene;

//! This is a game field class.
/** This class handles some events and moves it to appropriate objects (like characters).
    It is some kind of a Scene manager. It draws all objects on the Game Field
  */
class SceneManager: public ISceneNode
{
public:
    static SceneManager & instance();
    static SceneManager & createSceneManager(irr::video::IVideoDriver* driver);
    static void deleteField();
    virtual ~SceneManager();

    virtual void handleEvent(const irr::SEvent& event);
    virtual void draw();

    void setBackground(const irr::io::path& backgroundPath);

    void setCharacterPosition(const irr::s32& xCoord,
                              const irr::s32& yCoord);

    void addWallBlock(const irr::io::path& blocksBackground, const irr::s32& xCoord,
                      const irr::s32& yCoord);
    bool isCollidedWithWall(const irr::core::rect<irr::s32>& objRect) const;

    const GraphicBlock* isCollided(const irr::core::rect<irr::s32>& checkRect) const;

    // If mCurrentScene is not null, then previous scene will be deleted
    void setCurrentScene(Scene* newScene);

protected:
    irr::video::IVideoDriver* mDriver;

private:
    explicit SceneManager(irr::video::IVideoDriver* driver);
    void init();
    void addFieldNet();

private:
    Scene* mCurrentScene;
    irr::core::dimension2d<irr::u32> mBlockSizes;
    GraphicBlock* mCharacter;
    irr::io::path mBackgroundTexturePath;
    irr::video::ITexture* mTexture;
    irr::core::list<GraphicBlock*> mGraphicBlocks;
    irr::core::list<GraphicBlock*> mFieldsNetGraphicBlocks;
};

#endif // FIELD_H
