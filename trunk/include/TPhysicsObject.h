//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TDYNAMICNODE_H_
#define _TDYNAMICNODE_H_

namespace Tubras
{
    class TPhysicsObject : public btDefaultMotionState
    {
        TString                 m_name;
        ISceneNode*             m_sceneNode;
        btRigidBody*            m_rigidBody;
        TBodyType               m_bodyType;
        TColliderShape*         m_shape;
        float                   m_mass;
        bool                    m_isDynamic;
        bool                    m_allowDeactivation;
        TVector3                m_offset;
        short                   m_groupMask;
        short                   m_collisionMask;

    public:
        TPhysicsObject (const TString& name, ISceneNode* sceneNode,TColliderShape* shape,float mass=0.0f,
            TBodyType bodyType=btDynamic, TVector3 colliderOffset=TVector3::ZERO);

        TPhysicsObject (const TString& name, ISceneNode* sceneNode,TColliderShape* shape,
            short groupMask, short collisionMask, float mass=0.0f, TBodyType bodyType=btDynamic, 
            TVector3 colliderOffset=TVector3::ZERO);

        virtual ~TPhysicsObject();

        btRigidBody* getRigidBody() {return m_rigidBody;};
        TBodyType getBodyType() {return m_bodyType;}

        TColliderShape* getColliderShape() {return m_shape;};
        virtual bool isDynamic() {return m_isDynamic;}
        virtual void synchronizeMotionState();
        virtual void setActivationState(int value);
        virtual void applyImpulse(const TVector3& impulse, const TVector3& rel_pos);
        virtual void getCenterOfMassPosition(TVector3& out);
        virtual void setRestitution(TReal value);
        virtual void setFriction(TReal value);
        virtual void setDamping(TReal linearDamping, TReal angularDamping);
        virtual void setLinearVelocity(const TVector3& value);
        
        virtual ISceneNode* getSceneNode() {return m_sceneNode;}
        virtual void setSceneNode(ISceneNode* value) {m_sceneNode = value;}

        const TString getName() {return m_name;}
        float getMass() {return m_mass;}

        void allowDeactivation(bool value);
        void setAllowDeactivation(bool value) {m_allowDeactivation = value;}
        virtual bool deactivationCallback(void*	userPointer) {return m_allowDeactivation;}

        bool isActive() {return m_rigidBody->isActive();}
        void activate() {m_rigidBody->activate();}

        void setCollisionFlags(int value) {m_rigidBody->setCollisionFlags(value);}
        int getCollisionFlags() {return m_rigidBody->getCollisionFlags();}

        short getGroupMask() {return m_groupMask;}
        short getCollisionMask() {return m_collisionMask;}

	    virtual void getWorldTransform(btTransform& centerOfMassWorldTrans ) const;
	    virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans);

        void disable();
        void enable();
    };
}
#endif