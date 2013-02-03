#ifndef ACTIONGRAPHICITEM_H
#define ACTIONGRAPHICITEM_H

#include "graphicblock.h"

class ActionGraphicItem : public GraphicBlock
{
public:
    ActionGraphicItem(irr::video::IVideoDriver* driver);
    ~ActionGraphicItem();

    virtual void newMouseEvent(const irr::SEvent& event);

    /*!
     * ISceneNode interface implementation
    */
    virtual void draw();

private:
    bool mHighlighted;

};

#endif // ACTIONGRAPHICITEM_H
