//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TBSTATICMESH_H_
#define _TBSTATICMESH_H_

namespace Tubras
{
    class TBStaticMesh : public IBehavior
    {
    protected:
        IAnimatedMeshSceneNode*     m_node;

    public:
        int initialize(TEntity* owner, TProperties& properties);
    };
}

#endif
