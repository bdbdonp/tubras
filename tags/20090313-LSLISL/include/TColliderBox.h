//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TCOLLIDERBOX_H_
#define __TCOLLIDERBOX_H_

namespace Tubras
{

    class TColliderBox : public TColliderShape
    {
    protected:

    public:
        TColliderBox(TAABBox box);
        TColliderBox(ISceneNode* node);
        virtual ~TColliderBox();

    };

}


#endif