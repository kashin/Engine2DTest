#ifndef LINEARGESTURERECOGNIZER_H
#define LINEARGESTURERECOGNIZER_H

#include "igesturerecognizer.h"

class Event;

class LinearGestureRecognizer : public IGestureRecognizer
{
public:
    LinearGestureRecognizer();
    ~LinearGestureRecognizer();

    /**
     * IGestureRecognizer implementation
     */
    virtual Event* handleScreenEvent(const irr::SEvent & event);

protected:
    virtual bool isGestureRecognized();
};
#endif // LINEARGESTURERECOGNIZER_H
