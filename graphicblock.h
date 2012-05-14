#ifndef GRAPHICBLOCK_H
#define GRAPHICBLOCK_H

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

class GraphicBlock
{
public:
    GraphicBlock(irr::video::IVideoDriver* driver);
    ~GraphicBlock();

    const irr::io::path textureName() const { return mTextureName; }
    void setTextureName(const irr::io::path& textureName);

    const irr::core::vector2d<irr::s32> position() const { return mCurrentPosition; }
    void setPosition(irr::core::vector2d<irr::s32> position);

    virtual void draw();

protected:
    const irr::video::ITexture* texture() const { return mTexture; }

protected:
    irr::video::IVideoDriver* mDriver;

private:
    irr::io::path mTextureName;
    irr::core::vector2d<irr::s32> mCurrentPosition;
    irr::video::ITexture* mTexture;
};

#endif // GRAPHICBLOCK_H
