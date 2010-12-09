//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TKINEMATICCHARACTER_H_
#define _TKINEMATICCHARACTER_H_

namespace Tubras
{

    class TKinematicCharacter : public btCharacterControllerInterface
    {
    protected:

        btScalar m_halfHeight;

        btPairCachingGhostObject* m_ghostObject;
        btConvexShape*	m_convexShape;//is also in m_ghostObject, but it needs to be convex, so we store it here to avoid upcast

        btScalar m_verticalVelocity;
        btScalar m_verticalOffset;
        btScalar m_fallSpeed;
        btScalar m_jumpSpeed;
        btScalar m_maxJumpHeight;
        btScalar m_maxSlopeRadians; // Slope angle that is set (used for returning the exact value)
        btScalar m_maxSlopeCosine;  // Cosine equivalent of m_maxSlopeRadians (calculated once when set, for optimization)
        btScalar m_gravity;

        btScalar m_turnAngle;

        btScalar m_stepHeight;

        btScalar	m_addedMargin;//@todo: remove this and fix the code

        ///this is the desired walk direction, set by the user
        btVector3	m_walkDirection;
        btVector3	m_normalizedDirection;

        //some internal variables
        btVector3 m_currentPosition;
        btScalar  m_currentStepOffset;
        btVector3 m_targetPosition;
        btAlignedObjectArray<btCollisionObject*>    m_sensorContacts;

        ///keep track of the contact manifolds
        btManifoldArray	m_manifoldArray;

        bool m_touchingContact;
        btVector3 m_touchingNormal;

        bool  m_wasOnGround;
        bool  m_wasJumping;
        bool	m_useGhostObjectSweepTest;
        bool	m_useWalkDirection;
        btScalar	m_velocityTimeInterval;
        int m_upAxis;

        static btVector3* getUpAxisDirections();

        btVector3 computeReflectionDirection (const btVector3& direction, const btVector3& normal);
        btVector3 parallelComponent (const btVector3& direction, const btVector3& normal);
        btVector3 perpindicularComponent (const btVector3& direction, const btVector3& normal);

        bool recoverFromPenetration ( btCollisionWorld* collisionWorld);
        void stepUp (btCollisionWorld* collisionWorld);
        void updateTargetPositionBasedOnCollision (const btVector3& hit_normal, btScalar tangentMag = btScalar(0.0), btScalar normalMag = btScalar(1.0));
        void stepForwardAndStrafe (btCollisionWorld* collisionWorld, const btVector3& walkMove);
        void stepDown (btCollisionWorld* collisionWorld, btScalar dt);
    public:
        TKinematicCharacter (btPairCachingGhostObject* ghostObject,btConvexShape* convexShape,btScalar stepHeight, int upAxis = 1);
        ~TKinematicCharacter ();


        ///btActionInterface interface
        virtual void updateAction( btCollisionWorld* collisionWorld,btScalar deltaTime)
        {
            preStep ( collisionWorld);
            playerStep (collisionWorld, deltaTime);
        }

        ///btActionInterface interface
        void	debugDraw(btIDebugDraw* debugDrawer);

        void setUpAxis (int axis)
        {
            if (axis < 0)
                axis = 0;
            if (axis > 2)
                axis = 2;
            m_upAxis = axis;
        }

        /// This should probably be called setPositionIncrementPerSimulatorStep.
        /// This is neither a direction nor a velocity, but the amount to
        ///	increment the position each simulation iteration, regardless
        ///	of dt.
        /// This call will reset any velocity set by setVelocityForTimeInterval().
        virtual void	setWalkDirection(const btVector3& walkDirection);

        /// Caller provides a velocity with which the character should move for
        ///	the given time period.  After the time period, velocity is reset
        ///	to zero.
        /// This call will reset any walk direction set by setWalkDirection().
        /// Negative time intervals will result in no motion.
        virtual void setVelocityForTimeInterval(const btVector3& velocity,
            btScalar timeInterval);

        void reset ();
        void warp (const btVector3& origin);

        void preStep (  btCollisionWorld* collisionWorld);
        void playerStep ( btCollisionWorld* collisionWorld, btScalar dt);

        void setFallSpeed (btScalar fallSpeed);
        void setJumpSpeed (btScalar jumpSpeed);
        void setMaxJumpHeight (btScalar maxJumpHeight);
        bool canJump () const;

        void jump ();

        void setGravity(btScalar gravity);
        btScalar getGravity() const;

        /// The max slope determines the maximum angle that the controller can walk up.
        /// The slope angle is measured in radians.
        void setMaxSlope(btScalar slopeRadians);
        btScalar getMaxSlope() const;

        const btAlignedObjectArray<btCollisionObject*>& getSensorContacts() {return m_sensorContacts;}

        btPairCachingGhostObject* getGhostObject();
        void	setUseGhostSweepTest(bool useGhostObjectSweepTest)
        {
            m_useGhostObjectSweepTest = useGhostObjectSweepTest;
        }

        bool onGround () const;
    };

}

#endif

