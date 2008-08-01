// Copyright (C) 2002-2008 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "IrrCompileConfig.h"
#ifdef _IRR_COMPILE_WITH_IRR_MESH_LOADER_

#include "CAnimatedMeshIrr.h"

namespace irr
{
namespace scene
{

    void CAnimatedMeshIrr::animateMesh(f32 frame, f32 blend)
    {
        CSkinnedMesh::animateMesh(frame,blend);
    }

}
}

#endif