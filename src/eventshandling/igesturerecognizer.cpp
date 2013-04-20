#include "igesturerecognizer.h"

IGestureRecognizer::IGestureRecognizer()
{
}

IGestureRecognizer::~IGestureRecognizer()
{
    if (!mEventsList.empty()) {
        irr::core::list<irr::SEvent*>::ConstIterator it = mEventsList.begin();
        irr::core::list<irr::SEvent*>::ConstIterator end = mEventsList.end();
        while (it != end)
        {
            delete (*it);
            ++it;
        }
        mEventsList.clear();
    }
}
