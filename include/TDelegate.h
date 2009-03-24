//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TDELEGATE_H_
#define _TDELEGATE_H_

namespace Tubras
{
    class TDelegate
    {
    protected:
        TDelegate*          m_instance;
        int                 m_priority;

    public:
        TDelegate(TDelegate* instance) : m_instance(instance), m_priority(0) {};
        TDelegate() : m_priority(0) {m_instance = this;};
        virtual ~TDelegate() {}

        int getPriority() {return m_priority;};
        void setPriority(int value) {m_priority = value;};

        TDelegate* getInstance() {return m_instance;};
    };

}
#endif

