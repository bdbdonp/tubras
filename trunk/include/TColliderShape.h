//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#ifndef __TCOLLIDERSHAPE_H_
#define __TCOLLIDERSHAPE_H_

namespace Tubras
{

    class TColliderShape 
    {
    protected:
        btCollisionShape*       m_shape;
        btRigidBody*            m_body;
    public:
        TColliderShape();
        virtual ~TColliderShape();
        virtual void setShape(btCollisionShape* shape) {m_shape = shape;};
        virtual btCollisionShape* getShape() {return m_shape;};
        virtual btRigidBody* getRigidBody() {return m_body;};
        btRigidBody* createRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape);

    };

}


#endif
