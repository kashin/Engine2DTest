#include "character.h"
#include "animator2d.h"

#include <irrlicht/irrlicht.h>
#include <QDebug>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

Character::Character(IVideoDriver *driver, const CollisionType& type)
    : GraphicBlock(driver, type)
{
}

Character::~Character()
{
    irr::core::list< Animator2D* >::ConstIterator it = mAnimations.begin();
    irr::core::list< Animator2D* >::ConstIterator end = mAnimations.end();
    while (it != end)
    {
        delete *it;
        ++it;
    }
}

void Character::addAnimator(Animator2D *animator)
{
    irr::core::list< Animator2D* >::Iterator it = mAnimations.begin();
    irr::core::list< Animator2D* >::Iterator end = mAnimations.end();
    while (it != end)
    {
        if ((*it)->type() == animator->type())
        {
            delete (*it);
            mAnimations.erase(it);
            break;
        }
    }
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
    if (mDriver && texture())
    {
        mDriver->draw2DImage(texture(), position() - (vector2d<s32>(texture()->getSize().Width/2, texture()->getSize().Height/2)));
    }
}
