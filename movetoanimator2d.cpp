#include "movetoanimator2d.h"
#include "character.h"

#include <QDebug>

MoveToAnimator2D::MoveToAnimator2D(Animator2D::AnimationType type,
                                   irr::core::vector2d<irr::s32> startPosition,
                                   irr::core::vector2d<irr::s32> moveToPosition,
                                   irr::s32 animationSpeed)
    : Animator2D(type),
      mFinished(false),
      mSkipFrames(animationSpeed),
      mAnimationSpeed(animationSpeed),
      mEndPostion(moveToPosition)
{

    // FIXME:  Argh, how to make appropriate speed vector???
    mSpeedVector = (mEndPostion - startPosition) / 20;
}

void MoveToAnimator2D::runAnimation(Character *character)
{
    irr::core::vector2d<irr::s32> currentPosition = character->getPosition();
    if (currentPosition.equals(mEndPostion))
    {
        mFinished = true;
        return;
    }
    if (mSkipFrames > 0)
    {
        --mSkipFrames;
        return;
    }
    else
    {
        mSkipFrames = mAnimationSpeed;
    }
    if ( ((currentPosition + mSpeedVector) >= mEndPostion &&
          (currentPosition < mEndPostion)) ||
         ((currentPosition + mSpeedVector) <= mEndPostion &&
                   (currentPosition > mEndPostion)))
    {
        character->setPosition(mEndPostion);
    }
    else
    {
        character->setPosition(currentPosition + mSpeedVector);
    }
}

bool MoveToAnimator2D::animationFinished()
{
    return mFinished;
}
