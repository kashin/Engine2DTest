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
};

#endif // CHARACTER_H
