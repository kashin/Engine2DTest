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

//! This class representing a character(for example a tank) on the field.
class Character: public GraphicBlock
{
public:
    Character(irr::video::IVideoDriver* driver, const CollisionType& type = CanCollideType);
    ~Character();

    virtual void draw();

    virtual void newKeyEvent(const irr::SEvent& event);
    virtual void newMouseEvent(const irr::SEvent& event);

    irr::s32 actionsCount() const { return mMenuActionsCount; }

private:
    void drawMenu();
    void drawMenuAction(const irr::core::vector2d<irr::s32>& pos);
    void showMenu();
    void closeMenu();

private:
    bool mShowMenu;
    irr::s32 mMenuActionsCount;
    irr::video::ITexture* mMenuCircleTexture;
};

#endif // CHARACTER_H
