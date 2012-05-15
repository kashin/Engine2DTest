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
    : GraphicBlock(driver, type),
      mShowMenu(false)
{
}

Character::~Character()
{
}

void Character::draw()
{
    if (mShowMenu)
    {
        mDriver->draw2DPolygon(position(), max_<s32>(texture()->getSize().Width, texture()->getSize().Height),
                               SColor(255, 120, 255, 255), 30);
        return;
    }
    if (mDriver && texture())
    {
        mDriver->draw2DImage(texture(), position() - (vector2d<s32>(texture()->getSize().Width/2, texture()->getSize().Height/2)));
    }
}

void Character::newEvent(const irr::SEvent &event)
{
    switch(event.EventType)
    {
    case EET_MOUSE_INPUT_EVENT:
    {
        switch(event.MouseInput.Event)
        {
        case EMIE_RMOUSE_PRESSED_DOWN:
            {
                if (getBoundRect().isPointInside(vector2d<s32>(event.MouseInput.X, event.MouseInput.Y)))
                {
                    showMenu();
                }
                else if (mShowMenu)
                {
                    closeMenu();
                }
            }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void Character::showMenu()
{
    if (!mShowMenu)
    {
        mShowMenu = true;
    }
}

void Character::closeMenu()
{
    if (mShowMenu)
    {
        mShowMenu = false;
    }
}
