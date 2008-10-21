//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    //-----------------------------------------------------------------------
    //                           T E m p t y N o d e
    //-----------------------------------------------------------------------
    TEmptyNode::TEmptyNode(ISceneNode* parent) : TSceneNode(parent)
    {
    }

    //-----------------------------------------------------------------------
    //                          ~ T E m p t y N o d e
    //-----------------------------------------------------------------------
    TEmptyNode::~TEmptyNode()
    {
    }
}
