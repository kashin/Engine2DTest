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

class Character;
class WallBlock;

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
    ~Field();

    void newEvent(const irr::SEvent& event);
    virtual void draw();

    void setBackground(const irr::io::path& backgroundPath);

    void setCharacterPosition(const irr::s32& xCoord,
                              const irr::s32& yCoord);

    void addWallBlock(const irr::io::path& blocksBackground, const irr::s32& xCoord,
                      const irr::s32& yCoord);
    bool isCollided(const irr::core::rect<irr::s32>& objRect) const ;

protected:
    irr::video::IVideoDriver* mDriver;

private:
    explicit Field(irr::video::IVideoDriver* driver);
    void init();

private:
    Character* mCharacter;
    irr::io::path mBackgroundTexturePath;
    irr::video::ITexture* mTexture;
    irr::core::list<WallBlock*> mWallBlocks;
};

#endif // FIELD_H
