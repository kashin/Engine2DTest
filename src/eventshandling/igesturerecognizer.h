#ifndef IGESTURERECOGNIZER_H
#define IGESTURERECOGNIZER_H

#include "event.h"
#include <irrlicht/IEventReceiver.h>

class IGestureRecognizer
{
public:
    IGestureRecognizer();
    virtual ~IGestureRecognizer();

    /*!
     * @brief handleScreenEvent
     * @return NULL if gesture is not recognized or if it is not finished and Event object otherwise.
     */
    virtual Event* handleScreenEvent(const irr::SEvent & event) = 0;

protected:
    /*!
     * @return true if gesture is recognized and false otherwise. Typically should return true if gesture is
     * recognized and we have an event 'mouse key up' as a last handled event.
     */
    virtual bool isGestureRecognized() = 0;

protected:
    irr::core::list<irr::SEvent*> mEventsList;

};

#endif // IGESTURERECOGNIZER_H
