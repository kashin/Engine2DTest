#ifndef FIELD_H
#define FIELD_H

#include <irrlicht/path.h>
#include <irrlicht/irrTypes.h>
#include <irrlicht/irrList.h>
#include <irrlicht/rect.h>

namespace irr {
namespace video {
    class ITexture;
    class IVideoDriver;
}
    class SEvent;
}

class GraphicBlock;
class IGestureRecognizer;

//! This is a game field class.
/** This class handles some events and moves it to appropriate objects (like characters).
    It is some kind of a Scene manager. It draws all objects on the Game Field
  */
class Field
{
public:
    static Field & instance();
    static Field & createField(irr::video::IVideoDriver* driver);
    static void deleteField();
    virtual ~Field();

    void newEvent(const irr::SEvent& event);
    virtual void draw();

    void setBackground(const irr::io::path& backgroundPath);

    void setCharacterPosition(const irr::s32& xCoord,
                              const irr::s32& yCoord);

    void addWallBlock(const irr::io::path& blocksBackground, const irr::s32& xCoord,
                      const irr::s32& yCoord);
    bool isCollidedWithWall(const irr::core::rect<irr::s32>& objRect) const;

    const GraphicBlock* isCollided(const irr::core::rect<irr::s32>& checkRect) const;

protected:
    irr::video::IVideoDriver* mDriver;

private:
    explicit Field(irr::video::IVideoDriver* driver);
    void init();
    void addFieldNet();

private:
    irr::core::dimension2d<irr::u32> mBlockSizes;
    GraphicBlock* mCharacter;
    irr::io::path mBackgroundTexturePath;
    irr::video::ITexture* mTexture;
    irr::core::list<GraphicBlock*> mGraphicBlocks;
    irr::core::list<GraphicBlock*> mFieldsNetGraphicBlocks;
    irr::core::list<IGestureRecognizer*> mGestureRecognizers;
};

#endif // FIELD_H
