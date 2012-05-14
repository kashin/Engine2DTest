#ifndef WALLBLOCK_H
#define WALLBLOCK_H

#include <irrlicht/irrString.h>
#include <irrlicht/vector2d.h>
#include <irrlicht/path.h>
#include <irrlicht/irrTypes.h>
#include <irrlicht/irrList.h>

namespace irr {
    namespace video {
        class ITexture;
        class IVideoDriver;
    }
}

//FIXME: add an ancestor for WallBlock and Character
// for position, texture, draw, etc.

class WallBlock
{
public:
    explicit WallBlock(irr::video::IVideoDriver* driver, irr::core::vector2d<irr::s32> position);
    ~WallBlock();

    const irr::io::path textureName() const { return mTextureName; }
    void setTextureName(const irr::io::path& textureName);

    virtual const irr::core::vector2d<irr::s32> getPosition() const { return mCurrentPosition; }
    virtual void setPosition(irr::core::vector2d<irr::s32> position);

    virtual void draw();

protected:
    irr::video::IVideoDriver* mDriver;

private:
    irr::io::path mTextureName;
    irr::core::vector2d<irr::s32> mCurrentPosition;
    irr::video::ITexture* mTexture;
};

#endif // WALLBLOCK_H
