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
    virtual Event* handleIrrEvent(const irr::SEvent & event);

protected:
    virtual bool isGestureRecognized();

private:
    void updateEventsList();
};
#endif // LINEARGESTURERECOGNIZER_H
