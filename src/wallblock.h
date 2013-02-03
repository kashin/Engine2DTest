#ifndef WALLBLOCK_H
#define WALLBLOCK_H

#include "graphicblock.h"

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

class WallBlock: public GraphicBlock
{
public:
    explicit WallBlock(irr::video::IVideoDriver* driver, irr::core::vector2d<irr::s32> position,
                       const CollisionType& type = CanCollideType);
    ~WallBlock();

    /*!
     * ISceneNode interface implementation
    */
    virtual void draw();

private:
};

#endif // WALLBLOCK_H
