//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                        T C o n t r o l l e r
    //-----------------------------------------------------------------------
    TController::TController(const TString& controllerName, 
        TControllerFunction* function, ISceneNode* node, 
        const TString& startedEvent, const TString& stoppedEvent) : TDelegate()
    {
        m_name = controllerName;        
        m_startedEvent = startedEvent;
        m_stoppedEvent = stoppedEvent;
        m_node = node;
        m_function = function;
        m_startTime = 0;
        m_lastTime = 0;
        m_manager = getApplication()->getControllerManager();
        if(!m_function)
            m_function = new TPassThroughControllerFunction();
        m_active = false;
        m_manager->registerController(this);
    }

    //-----------------------------------------------------------------------
    //                       ~ T C o n t r o l l e r
    //-----------------------------------------------------------------------
    TController::~TController()
    {
        if(m_function)
            delete m_function;
    }

    //-----------------------------------------------------------------------
    //                           s e t N o d e
    //-----------------------------------------------------------------------
    void TController::setNode(ISceneNode* node)
    {
        m_node = node;
    }

    //-----------------------------------------------------------------------
    //                             s t a r t
    //-----------------------------------------------------------------------
    ISceneNode* TController::getNode() 
    {
        return m_node;
    }

    //-----------------------------------------------------------------------
    //                             s t a r t
    //-----------------------------------------------------------------------
    void TController::start()
    {
        if(m_active)
            return;
        m_active = true;
        m_manager->start(this);
        if(m_startedEvent.size())
        {
            TEvent event(m_startedEvent);
            getApplication()->getEventManager()->send(&event);
        }
    }

    //-----------------------------------------------------------------------
    //                              s t o p
    //-----------------------------------------------------------------------
    void TController::stop()
    {
        if(!m_active)
            return;
        m_active = false;
        m_manager->stop(this);
        if(m_stoppedEvent.size())
        {
            TEvent event(m_stoppedEvent);
            getApplication()->getEventManager()->send(&event);
        }
    }
}
