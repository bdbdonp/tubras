//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TCOLLIDERMESH_H_
#define __TCOLLIDERMESH_H_

namespace Tubras
{

    class TColliderMesh : public TColliderShape
    {
    private:
        btTriangleMesh* m_triMesh;

    protected:
        void extractTriangles(IMesh* mesh);

    public:
        TColliderMesh(IMesh* mesh,bool optimize=false);
        virtual ~TColliderMesh();

    };

}


#endif