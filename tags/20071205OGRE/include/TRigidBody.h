//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
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

#ifndef _TRIGIDBODY_H_
#define _TRIGIDBODY_H_

namespace Tubras
{
    class TColliderShape;

    class TRigidBody 
    {
    protected:
        TColliderShape*         m_shape;
        TBodyType               m_bodyType;
        btRigidBody*            m_body;
        TMotionState*           m_motionState;
        float                   m_mass;
        bool                    m_isDynamic;
        TVector3				m_offset;

    public:
        TRigidBody(float mass,TMatrix4& startTransform,TColliderShape* shape,
            TBodyType bodyType=btDynamic,TVector3 offset=TVector3::ZERO, void* userData=NULL);
        virtual ~TRigidBody();

        btRigidBody* getBulletRigidBody() {return m_body;};
        btDefaultMotionState* getMotionState() {return m_motionState;};
        float getMass() {return m_mass;};
        TColliderShape* getShape() {return m_shape;};
        void allowDeactivation(bool value);
        void setLinearVelocity(TVector3 value);
        void setFriction(TReal value);
        int  getActivationState();
        void setActivationState(int value);
        void setCollisionFlags(int value) {m_body->setCollisionFlags(value);};
        int getCollisionFlags() {return m_body->getCollisionFlags();};
        bool isDynamic() {return m_body->isStaticObject() != true;};
        TVector3 getOffset() {return m_offset;};
        void setOffset(TVector3 offset) {m_offset = offset;};
        void applyImpulse(const TVector3& impulse, const TVector3& rel_pos);
        TVector3 getCenterOfMassPosition();
        void setRestitution(TReal value);
        void setDamping(TReal linearDamping, TReal angularDamping);

    };

}


#endif