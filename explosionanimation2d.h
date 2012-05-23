#ifndef EXPLOSIONANIMATION2D_H
#define EXPLOSIONANIMATION2D_H

#include "movetoanimator2d.h"

class ExplosionAnimation2D : public MoveToAnimator2D
{
public:
    ExplosionAnimation2D(Animator2D::AnimationType type,
                         irr::core::vector2d<irr::s32> startPosition,
                         irr::core::vector2d<irr::s32> moveToPosition,
                         irr::s32 animationSpeed);
protected:
    virtual void finishAnimation(GraphicBlock *graphicBlock = 0, bool collided = false);
};

#endif // EXPLOSIONANIMATION2D_H
