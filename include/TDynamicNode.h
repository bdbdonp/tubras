//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TDYNAMICNODE_H_
#define _TDYNAMICNODE_H_

namespace Tubras
{
    class TColliderShape;
    class TRigidBody;
    enum  TBodyType;

    class TDynamicNode
    {
        ISceneNode*             m_sceneNode;
        TRigidBody*             m_body;
        TColliderShape*         m_shape;
        float                   m_mass;
        bool                    m_isDynamic;

    public:
        TDynamicNode (const TString& name, ISceneNode* sceneNode,TColliderShape* shape,float mass=0.0f,
            TBodyType bodyType=btDynamic,TVector3 colliderOffset=TVector3::ZERO);
        virtual ~TDynamicNode();
        TRigidBody* getRigidBody() {return m_body;};
        TColliderShape* getColliderShape() {return m_shape;};
        virtual bool isDynamic();
        virtual void synchronizeMotionState();
        virtual void allowDeactivation(bool value);
        virtual void setActivationState(int newState);
        virtual void applyImpulse(const TVector3& impulse, const TVector3& rel_pos);
        virtual TVector3 getCenterOfMassPosition();
        virtual void setRestitution(TReal value);
        virtual void setFriction(TReal value);
        virtual void setDamping(TReal linearDamping, TReal angularDamping);
        virtual void setLinearVelocity(const TVector3& value);
        TString getName() {return m_sceneNode->getName();}

    };


}
#endif

