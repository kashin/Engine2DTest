#ifndef ANIMATOR2D_H
#define ANIMATOR2D_H

class GraphicBlock;

//! base class for all 2D animations in this test application
class Animator2D
{
public:
    enum AnimationType {
        MoveToAnimation = 0,
        FireToAnimation,
        BulletAnimation,
        ExplosionAnimation,

        // add new Animation types above this line
        AllAnimations
    };

    explicit Animator2D(AnimationType type);
    virtual ~Animator2D();

    AnimationType type() const { return mType; }

    virtual void runAnimation(GraphicBlock* graphicBlock) = 0;
    virtual bool animationFinished() = 0;

private:
    AnimationType mType;
};

#endif // ANIMATOR2D_H
