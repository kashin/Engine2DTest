#ifndef EXPLOSIONSPRITE_H
#define EXPLOSIONSPRITE_H

#include "animator2d.h"
#include <vector2d.h>

class BaseSprite;

namespace irr {
    namespace video {
        class IVideoDriver;
    }
}

class ExplosionSpriteAnimator2D: public Animator2D
{
public:
    ExplosionSpriteAnimator2D(irr::core::vector2d<irr::s32> position,
                              irr::video::IVideoDriver* driver);

    virtual void runAnimation(GraphicBlock* graphicBlock);

    virtual bool animationFinished();

private:
    bool mFinished;
    irr::core::vector2d<irr::s32> mPosition;
    BaseSprite* mSprite;
};

#endif // EXPLOSIONSPRITE_H
