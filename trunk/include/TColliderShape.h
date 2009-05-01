//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TCOLLIDERSHAPE_H_
#define __TCOLLIDERSHAPE_H_

namespace Tubras
{
    enum TShapeType
    {
        stBox,
        stPlane,
        stSphere,
        stCone,
        stConvex,
        stCylinder
    };

    class TColliderShape 
    {
    protected:
        btCollisionShape*       m_shape;
    public:
        TColliderShape();
        virtual ~TColliderShape();
        virtual void setShape(btCollisionShape* shape) {m_shape = shape;};
        virtual btCollisionShape* getShape() {return m_shape;};

        virtual void calculateLocalInertia(float mass,btVector3& inertia);
    };
}
#endif
