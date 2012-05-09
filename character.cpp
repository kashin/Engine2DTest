#include "character.h"
#include "animator2d.h"

#include <irrlicht.h>
#include <QDebug>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

Character::Character(IVideoDriver *driver)
    : mDriver(driver),
      mTexture(0)
{
    setPosition(vector2d<s32>(0,0));
}

Character::~Character()
{
    if (mTexture)
        delete mTexture;
    irr::core::list< Animator2D* >::ConstIterator it = mAnimations.begin();
    irr::core::list< Animator2D* >::ConstIterator end = mAnimations.end();
    while (it != end)
    {
        delete *it;
        ++it;
    }
}

void Character::setTextureName(const path &textureName)
{
    mTextureName = textureName;
    if (mTexture)
    {
        delete mTexture;
        mTexture = 0;
    }
    if (mDriver)
        mTexture = mDriver->getTexture(mTextureName);
}

void Character::setPosition(vector2d<s32> position)
{
    mCurrentPosition = position;
}

void Character::addAnimator(Animator2D *animator)
{
    mAnimations.push_front(animator);
}

void Character::draw()
{
    if (!mAnimations.empty())
    {
        irr::core::list< Animator2D* >::Iterator it = mAnimations.begin();
        irr::core::list< Animator2D* >::Iterator end = mAnimations.end();
        irr::core::list< irr::core::list< Animator2D* >::Iterator> deleteAnimsList;
        while (it != end)
        {
            if ((*it)->animationFinished())
            {
                deleteAnimsList.push_front(it);
                ++it;
                continue;
            }
            (*it)->runAnimation(this);
            ++it;
        }
        irr::core::list< irr::core::list< Animator2D* >::Iterator>::Iterator iter = deleteAnimsList.begin();
        while (iter != deleteAnimsList.end())
        {
            delete *(*iter);
            mAnimations.erase((*iter));
            ++iter;
        }
    }
    if (mTexture && mDriver)
    {
        mDriver->draw2DImage(mTexture, mCurrentPosition - (vector2d<s32>(mTexture->getSize().Width/2, mTexture->getSize().Height/2)));
    }
}
