#ifndef ISCENENODE_H
#define ISCENENODE_H

#include <irrlicht/irrList.h>

namespace irr {
    class SEvent;
}

/*!
 * \brief The ISceneNode interface is a general interface  that nshould be implemented by all
 * Graphical blocks (nodes).
 */

class ISceneNode
{
public:
    ISceneNode(ISceneNode* parent = 0);
    virtual ~ISceneNode();

    /*!
     * \brief draw method called when parents wants to draw this scene node.
     *  calls draw method for all childs.
     */
    virtual void draw();
    /*!
     * \brief handleEvent method that handles device's input.
     *  Passes events to childs if it is not processed.
     * \param event event that should be processed
     *
     * \return @c true if event was processed and @c false otherwise
     */
    virtual bool handleEvent(const irr::SEvent& event);

    /*!
     * \brief getParent returns parent's node
     * \return parent's SceneNode
     */
    ISceneNode* getParent();

    /*!
     * \brief setParent sets parent for this scene node
     * \param parent Node that becomes an owner of the SceneNode.
     *  Removes SceneNode from previous parent.
     */
    void setParent(ISceneNode* parent);

    /*!
     * \brief appendChildNode appends child node to this SceneNode
     * \param node a SceneNode that shoud be appended
     */
    void appendChildNode(ISceneNode* node);

    /*!
     * \brief removeChildNode removes child node for this SceneNode.
     * \param node aSceneNode that should be removed.
     * SceneNode is not deleted auomatically, so you should remove it if you don't need it anymore.
     */
    void removeChildNode(ISceneNode* node);

    /*!
     * \brief getChildCount returns child's count
     * \return child's count
     */
    irr::u32 getChildCount();

private:
    bool isSceneNodeAppended(ISceneNode* node);

private:
    ISceneNode* mParent;
    irr::core::list<ISceneNode*>  mChilds;
};

#endif // ISCENENODE_H
