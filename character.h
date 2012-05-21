#ifndef CHARACTER_H
#define CHARACTER_H

#include "graphicblock.h"

class ActionGraphicItem;

//! This class representing a character(for example a tank) on the field.
class Character: public GraphicBlock
{
public:
    explicit Character(irr::video::IVideoDriver* driver, const CollisionType& type = CanCollideType);
    ~Character();

    virtual void draw();

    virtual void newKeyEvent(const irr::SEvent& event);
    virtual void newMouseEvent(const irr::SEvent& event);

    irr::s32 actionsCount() const { return mMenuActionsCount; }

    //! Sets FPS for character (number of pictures in the sprite)
    //! @param fps should an fps value for the character >= 1
    void setFPS(const unsigned int fps);
    unsigned int getFPS() const { return mAnimationFPS; }

private:
    void drawMenu();
    void addMenuAction(const irr::core::vector2d<irr::s32>& pos);
    void clearMenuActions();
    void showMenu();
    void closeMenu();

private:
    bool mShowMenu;
    irr::u32 mMenuActionsCount;
    irr::core::list<ActionGraphicItem*> mActionItems;
    unsigned int mAnimationFPS; //! if  mAnimationFPS = 1 than it means a static picture
    unsigned int mCurrentAnimationFrame;
};

#endif // CHARACTER_H
