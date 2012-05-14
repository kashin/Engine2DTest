#ifndef MOVETOANIMATOR2D_H
#define MOVETOANIMATOR2D_H

#include "animator2d.h"
#include <irrlicht/vector2d.h>


class MoveToAnimator2D: public Animator2D
{
public:
    explicit MoveToAnimator2D(Animator2D::AnimationType type,
                              irr::core::vector2d<irr::s32> startPosition,
                              irr::core::vector2d<irr::s32> moveToPosition,
                              irr::s32 animationSpeed);

    virtual void runAnimation(GraphicBlock* character);

    virtual bool animationFinished();

private:
    bool mFinished;
    irr::s32 mSkipFrames; // FIXME: remove this stupid hack as soon as right algorithm is done for Speed Vector.
    irr::s32 mAnimationSpeed; // FIXME: remove this stupid hack as soon as right algorithm is done for Speed Vector.
    irr::core::vector2d<irr::s32> mSpeedVector;
    irr::core::vector2d<irr::s32> mEndPostion;
};

#endif // MOVETOANIMATOR2D_H
