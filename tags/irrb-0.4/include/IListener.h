//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _ILISTENER_H_
#define _ILISTENER_H_

namespace Tubras
{
    class IListener : public virtual IReferenceCounted
    {
    public:
        virtual void update(TEvent& event)=0;
    };
}

#endif