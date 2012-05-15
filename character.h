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
    class SEvent;
}

class Animator2D;

//! This class representing a character(for example a tank) on the field.
class Character: public GraphicBlock
{
public:
    Character(irr::video::IVideoDriver* driver, const CollisionType& type = CanCollideType);
    ~Character();

    virtual void addAnimator(Animator2D* animator);

    virtual void draw();

    //! Handles new events like Mouse/Key clicked, moved, etc.
    void newEvent(const irr::SEvent& event);

private:
    void showMenu();
    void closeMenu();

private:
    irr::core::list<Animator2D*> mAnimations;
    bool mShowMenu;
};

#endif // CHARACTER_H
