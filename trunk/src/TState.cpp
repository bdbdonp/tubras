//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                            T S t a t e
    //-----------------------------------------------------------------------
    TState::TState(const TString& name) : TDelegate()
    {
        m_name = name;
        m_app = getApplication();
        if(m_app)
            m_app->addState(this);
    }

    //-----------------------------------------------------------------------
    //                            ~T S t a t e
    //-----------------------------------------------------------------------
    TState::~TState()
    {
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TState::initialize()
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //                              E n t e r
    //-----------------------------------------------------------------------
    int TState::Enter()
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //                               E x i t
    //-----------------------------------------------------------------------
    TStateInfo* TState::Exit()
    {
        return &m_info;
    }

    //-----------------------------------------------------------------------
    //                              R e s e t
    //-----------------------------------------------------------------------
    int TState::Reset()
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //                              P a u s e 
    //-----------------------------------------------------------------------
    int TState::Pause()
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //                              R e s u m e
    //-----------------------------------------------------------------------
    int TState::Resume(TStateInfo* prevStateInfo)
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //                       c h a n g e S t a t e
    //-----------------------------------------------------------------------
    int TState::changeState(const TString& stateName)
    {
        return m_app->changeState(stateName);
    }

    //-----------------------------------------------------------------------
    //                         p u s h S t a t e
    //-----------------------------------------------------------------------
    int TState::pushState(const TString& stateName)
    {
        return m_app->pushState(stateName);
    }

    //-----------------------------------------------------------------------
    //                          p o p S t a t e
    //-----------------------------------------------------------------------
    int TState::popState()
    {
        return m_app->popState();
    }


}
