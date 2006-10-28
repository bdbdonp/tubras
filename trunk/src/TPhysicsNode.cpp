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

#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T P h y s i c s N o d e
    //-----------------------------------------------------------------------
    TPhysicsNode::TPhysicsNode (string name, TSceneNode *parent, TColliderShape* shape,float mass) : TSceneNode(name,parent)
    {
        btTransform startTransform;
        btMatrix3x3 bmat3;
        btVector3   borg;

        TMatrix3 mat3;
        TMatrix4 mat4;
        TVector3 trans;

        m_mass = mass;

        parent->getTransform(&mat4);
        trans = mat4.getTrans();
        mat4.extract3x3Matrix(mat3);

        bmat3.setValue(mat3[0][0],mat3[0][1],mat3[0][2],
                       mat3[1][0],mat3[1][1],mat3[1][2],
                       mat3[2][0],mat3[2][1],mat3[2][2]);
        borg.setValue(trans.x,trans.y,trans.z);

        startTransform.setBasis(bmat3);
        startTransform.setOrigin(borg);


        m_body = new TRigidBody(mass,startTransform,shape,this);

    }

    //-----------------------------------------------------------------------
    //                       ~ T P h y s i c s N o d e
    //-----------------------------------------------------------------------
    TPhysicsNode::~TPhysicsNode()
    {
    }



}