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

private:
    void showMenu();
    void closeMenu();

private:
    bool mShowMenu;
};

#endif // CHARACTER_H
