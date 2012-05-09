#ifndef ANIMATOR2D_H
#define ANIMATOR2D_H

class Character;

//! base class for all 2D animations in this test application
class Animator2D
{
public:
    enum AnimationType {
        MoveTo = 0
    };

    explicit Animator2D(AnimationType type);
    virtual bool animationFinished() = 0;

    AnimationType type() const { return mType; }

    virtual void runAnimation(Character* character) = 0;

private:
    AnimationType mType;
};

#endif // ANIMATOR2D_H
