#ifndef CHARACTER_H
#define CHARACTER_H

#include "graphicblock.h"

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

class Animator2D;

class Character: public GraphicBlock
{
public:
    Character(irr::video::IVideoDriver* driver);
    ~Character();

    virtual void addAnimator(Animator2D* animator);

    virtual void draw();

private:
    irr::core::list<Animator2D*> mAnimations;
};

#endif // CHARACTER_H
