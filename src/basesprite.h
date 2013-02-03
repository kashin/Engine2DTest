#ifndef BASESPRITE_H
#define BASESPRITE_H

#include <vector2d.h>
#include <irrTypes.h>
#include <irrList.h>
#include <rect.h>
#include <path.h>

namespace irr {
    namespace video {
        class ITexture;
        class IVideoDriver;
    }
}

class BaseSprite
{
public:
    BaseSprite(irr::video::IVideoDriver* driver,
               irr::core::vector2d<irr::s32> position,
               const irr::io::path& spriteTexturePath,
               irr::u32 frameWidth,
               irr::u32 frameHeight,
               bool replay = false);
    ~BaseSprite();

    virtual void draw();

    void setTextureName(const irr::io::path &textureName);

    void setReplay(bool replay);
    bool replay() const { return mReplay; }

    bool stopped() const { return mStopped; }

private:
//    irr::core::vector2d<irr::s32> mPosition;
    irr::u32 mCurrentAnimationFrame;
    irr::u32 mFrameWidth;
    irr::u32 mFrameHeight;
    irr::core::rect<irr::s32> mDestRect;
    irr::core::list<irr::core::rect<irr::s32> > mSpriteFrameRectangles;
    bool mReplay;
    bool mStopped;
    irr::video::ITexture* mTexture;
    irr::video::IVideoDriver* mDriver;
};

#endif // BASESPRITE_H
