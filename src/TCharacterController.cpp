//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                   T C h a r a c t e r C o n t r o l l e r
    //-----------------------------------------------------------------------
    TCharacterController::TCharacterController(const TString& controllerName,
        ICameraSceneNode* camera,
        TCharacterControllerMode mode,
        ISceneNode* playerNode) : TController(controllerName, 0, playerNode)
    {
        m_mode = mode;
        m_controllerTarget = CT_BOTH;
        m_camera = camera;
        m_rotating = false;
        m_pitching = false;
        m_translating = false;
        m_fDamping = 
        m_bDamping = false;
        m_mouseMoved = false;
        m_zoomed = false;
        m_movementEnabled = true;
        m_mouseMovementEnabled = true;
        m_translate = TVector3_ZERO;
        m_pitch = 0.0f;
        m_rotate = 0.0f;
        m_shift = 1.0f;
        m_inverted = -1.0f;
        m_fDampDir = 0;
        m_bDampDir = 0;
        m_fDampTime =
        m_bDampTime = 0.f;
        memset(m_actions,0,sizeof(m_actions));
        m_ghostWalkDirection.setZero();

        TConfig* config = getApplication()->getConfig();
        m_orgVelocity =
        m_velocity = config->getFloat("options.velocity",3.0);
        m_velDamp = config->getFloat("options.velocitydamp",1.0);
        m_angularVelocity = config->getFloat("options.angularvelocity",3.0);
        m_maxVertAngle = config->getFloat("options.maxvertangle",88.0);

        m_characterWidth = config->getFloat("physics.characterWidth", 1.f) / 2.f;
        m_characterHeight = config->getFloat("physics.characterHeight", 2.f) / 2.f;
        m_characterStepHeight = config->getFloat("physics.characterStepHeight", 0.35f);
        m_characterJumpSpeed = config->getFloat("physics.characterJumpSpeed", 0.3f);

        m_mouseMoveDelegate = EVENT_DELEGATE(TCharacterController::procMouseMove);
        TApplication* app = getApplication();

        app->acceptEvent("input.mouse.move", m_mouseMoveDelegate);

        m_cmdDelegate = EVENT_DELEGATE(TCharacterController::procCmd);

        m_frwdID = app->acceptEvent("frwd",m_cmdDelegate,(void*)A_FRWD);
        m_backID = app->acceptEvent("back",m_cmdDelegate,(void*)A_BACK);
        m_leftID = app->acceptEvent("left",m_cmdDelegate,(void*)A_LEFT);
        m_rghtID = app->acceptEvent("rght",m_cmdDelegate,(void*)A_RGHT);
        m_rotlID = app->acceptEvent("rotl",m_cmdDelegate,(void*)A_ROTL);
        m_rotrID = app->acceptEvent("rotr",m_cmdDelegate,(void*)A_ROTR);
        m_mvupID = app->acceptEvent("mvup",m_cmdDelegate,(void*)A_MVUP);
        m_mvdnID = app->acceptEvent("mvdn",m_cmdDelegate,(void*)A_MVDN);
        m_rotfID = app->acceptEvent("rotf",m_cmdDelegate,(void*)A_ROTF);
        m_rotbID = app->acceptEvent("rotb",m_cmdDelegate,(void*)A_ROTB);
        m_avelID = app->acceptEvent("avel",m_cmdDelegate,(void*)A_AVEL);
        m_jumpID = app->acceptEvent("jump",m_cmdDelegate,(void*)A_JUMP);

        m_cmdDelegate2 = EVENT_DELEGATE(TCharacterController::procCmd2);
        m_invertMouseID = app->acceptEvent("invert-mouse",m_cmdDelegate2);
        m_toggleMouseID = app->acceptEvent("toggle-mouse",m_cmdDelegate2);
        m_zoomedInID = app->acceptEvent("zoomed.in",m_cmdDelegate2);
        m_zoomedOutID = app->acceptEvent("zoomed.out",m_cmdDelegate2);
        
        // bullet character controller setup
        m_ghostObject= new btPairCachingGhostObject();
        btCapsuleShape* characterShape = new btCapsuleShape(m_characterWidth,m_characterHeight);
        btTransform trans;
        trans.setIdentity();
        TVector3 pos = m_camera->getAbsolutePosition();
        trans.setOrigin(btVector3(pos.X, pos.Y, pos.Z));
        m_ghostObject->setWorldTransform(trans);
        m_ghostObject->setCollisionShape(characterShape);
	    m_ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

        int upAxis = 1;

        m_character = new TKinematicCharacter(m_ghostObject, characterShape, m_characterStepHeight, upAxis);

        m_updater = &TCharacterController::updateFPS;

        m_inputHandler = getApplication()->getInputManager()->getHandler();

        m_irrlichtCollision = getApplication()->getPhysicsManager()->getCollisionSystemType() == cstIrrlicht;
    }

    //-----------------------------------------------------------------------
    //                  ~ T C h a r a c t e r C o n t r o l l e r
    //-----------------------------------------------------------------------
    TCharacterController::~TCharacterController()
    {
        if(m_character)
        {
            btDiscreteDynamicsWorld* world = getApplication()->getPhysicsManager()->getBulletWorld();
            if(world)
                world->removeAction(m_character);
            delete m_character;
        }
    }

    //-----------------------------------------------------------------------
    //                         s e t C a m e r a
    //-----------------------------------------------------------------------
    ICameraSceneNode* TCharacterController::setCamera(ICameraSceneNode* camera)
    {
        ICameraSceneNode* oldCamera = m_camera;
        m_camera = camera;
        TVector3 pos = m_camera->getPosition();
        m_character->warp(btVector3(pos.X, pos.Y, pos.Z));
        return oldCamera;
    }

    //-----------------------------------------------------------------------
    //                            s e t M o d e
    //-----------------------------------------------------------------------
    void TCharacterController::setMode(TCharacterControllerMode value)
    {
        // if switching from God mode, update the bullet ghost object.        
        if(m_mode == ccmGod)
        {
            TVector3 pos = m_camera->getPosition();
            m_character->warp(btVector3(pos.X, pos.Y, pos.Z));
        }
        m_mode = value;
    }

    //-----------------------------------------------------------------------
    //                 s e t C o n t r o l l e r T a r g e t
    //-----------------------------------------------------------------------
    void TCharacterController::setControllerTarget(TControllerTarget value) 
    {
        static bool first=true;

        m_controllerTarget = value;
        if(m_mode == ccmGod)
        {
            switch(value)
            {
                case CT_CAMERA:
                    if(first)
                        break;
                    m_camera->setTarget(m_oldTarget);
                    m_camera->setRotation(m_oldRotation);
                    break;
                case CT_CHARACTER:
                    m_oldTarget = m_camera->getTarget();
                    m_oldRotation = m_camera->getRotation();
                    break;
                default:
                    first = true;
                    break;
            }
            first = false;
        }
    }
    //-----------------------------------------------------------------------
    //                         s e t P o s i t i o n
    //-----------------------------------------------------------------------
    void TCharacterController::setPosition(TVector3 value)
    {
        m_camera->setPosition(value);
        m_character->warp(btVector3(value.X, value.Y, value.Z));
    }

    //-----------------------------------------------------------------------
    //                       e n a b l e M o v e m e n t
    //-----------------------------------------------------------------------
    void TCharacterController::enableMovement(bool value)
    {
        m_movementEnabled = value;
    }

    //-----------------------------------------------------------------------
    //                   e n a b l e M o u s e M o v e m e n t
    //-----------------------------------------------------------------------
    void TCharacterController::enableMouseMovement(bool value)
    {
        m_mouseMovementEnabled = value;
    }

    //-----------------------------------------------------------------------
    //                         p r o c M o u s e M o v e
    //-----------------------------------------------------------------------
    int TCharacterController::procMouseMove(TEvent* event)
    {

        if(!m_mouseMovementEnabled)
            return 1;
        
        const irr::core::vector2di* pme;
        float zcoeff=1.0f;
        if(m_zoomed)
            zcoeff = 0.1f;

        if(m_inputHandler->isKeyDown(irr::KEY_LCONTROL))
            zcoeff *= 0.1f;

        //
        // parm(1) -> SEvent pointer
        // parm(2) -> relative movment vector
        //
        pme = (const irr::core::vector2di*) event->getParameter(1)->getPointerValue();
        m_mouseX = (f32)(-pme->X * 0.13 * zcoeff);
        m_mouseY = (f32) (m_inverted * pme->Y * 0.13 * zcoeff);
        m_mouseMoved = true;
        
        return 1;
    }

    //-----------------------------------------------------------------------
    //                            p r o c C m d
    //-----------------------------------------------------------------------
    int TCharacterController::procCmd(TEvent* event)
    {
        bool start = false;
        float famount = 0.0f;

        if(event->getNumParameters() > 0)
        {
            TEventParameter* ep = event->getParameter(0);

            if(ep->isInt())
                start = ep->getIntValue() ? true : false;
            else if (ep->isDouble())
                famount = (float) ep->getDoubleValue();
        }
        size_t eid = event->getID();

        m_rotating = m_pitching = m_translating = false;

        intptr_t pidx = (intptr_t)event->getUserData();
        int idx = (int)pidx;
        m_actions[idx] = start;

        if(eid == m_frwdID)
        {
            m_fDampDir = start;
            if(!m_fDamping && (m_velDamp != 0.f))
            {
                m_fDampTime = 0.f;
                m_fDamping = true;
            }
        }
        else if(eid == m_backID)
        {
            m_bDampDir = start;
            if(!m_bDamping && (m_velDamp != 0.f))
            {
                m_bDampTime = 0.f;
                m_bDamping = true;
            }
        }
        else if(eid == m_avelID)
        {
            m_velocity = m_orgVelocity * famount;
        }

        return 1;
    }

    //-----------------------------------------------------------------------
    //                            p r o c C m d 2
    //-----------------------------------------------------------------------
    int TCharacterController::procCmd2(TEvent* event)
    {
        float famount = 0.0f;

        size_t eid = event->getID();

        if(event->getNumParameters() > 0)
        {
            TEventParameter* ep = event->getParameter(0);
            if (ep->isDouble())
                famount = (float) ep->getDoubleValue();
        }

        if(eid == m_invertMouseID)
        {
            if(m_inverted < 0)
                m_inverted = 1.0f;
            else m_inverted = -1.0f;
        }
        else if(eid == m_toggleMouseID)
        {
            m_mouseMovementEnabled = m_mouseMovementEnabled ? false : true;
        }
        else if(eid == m_zoomedInID)
        {
            m_zoomed = true;
        }
        else if(eid == m_zoomedOutID)
        {
            m_zoomed = false;
        }

        return 1;
    }


    //-----------------------------------------------------------------------
    //                          u p d a t e F P S
    //-----------------------------------------------------------------------
    void TCharacterController::updateFPS(f32 deltaFrameTime)
    {
        TVector3 target(0,0,1);
        TVector3 pos = m_camera->getPosition();
        TVector3 oldpos = pos;
        TVector3 rotation = m_camera->getRotation();
        TVector3 upVector = m_camera->getUpVector();
        f32 gPlayerForwardBackward=0.f, gPlayerSideways=0.f;

        rotation.X *= -1.0f;
        rotation.Y *= -1.0f;

        if(m_mouseMoved)
        {
            rotation.Y += m_mouseX;

            rotation.X += m_mouseY;
            rotation.X = clamp(rotation.X,
                -m_maxVertAngle, +m_maxVertAngle);
            m_mouseX = 0;
            m_mouseY = 0;
            m_mouseMoved = false;
        }

        if(m_movementEnabled)
        {
            if(m_actions[A_ROTR])
            {
                rotation.Y -= (deltaFrameTime * m_angularVelocity);
            }

            if(m_actions[A_ROTL])
            {
                rotation.Y += (deltaFrameTime * m_angularVelocity);
            }

            if(m_actions[A_ROTF])
            {
                rotation.X -= (deltaFrameTime * m_angularVelocity);
                rotation.X = clamp(rotation.X,
                    -m_maxVertAngle, +m_maxVertAngle);
            }

            if(m_actions[A_ROTB])
            {
                rotation.X += (deltaFrameTime * m_angularVelocity);
                rotation.X = clamp(rotation.X,
                    -m_maxVertAngle, +m_maxVertAngle);
            }

            rotation.X *= -1.0f;
            rotation.Y *= -1.0f;

            m_camera->setRotation(rotation);

            matrix4 mat;
            mat.setRotationDegrees(core::vector3df( rotation.X, rotation.Y, 0));
            mat.transformVect(target);

            vector3df movedir = target.normalize();

            if(m_actions[A_FRWD] || m_fDamping)
            {
                f32 damp = 1.f, velocity;
                if(m_fDamping)
                {
                    m_fDampTime += deltaFrameTime;
                    damp = m_fDampTime / m_velDamp;
                    if(m_fDampDir)
                    {
                        if(damp >= 1.f)                
                            m_fDamping = false;
                    }
                    else 
                    {
                        damp = 1.f - damp;
                        if(damp <= 0.f)                    
                            m_fDamping = false;
                    }
                }
                velocity = m_velocity * damp;
                pos += movedir * deltaFrameTime * velocity;
                gPlayerForwardBackward += (velocity * deltaFrameTime);
            }
            if(m_actions[A_BACK] || m_bDamping)
            {
                f32 damp = 1.f, velocity;
                if(m_bDamping)
                {
                    m_bDampTime += deltaFrameTime;
                    damp = m_bDampTime / m_velDamp;
                    if(m_bDampDir)
                    {
                        if(damp >= 1.f)                
                            m_bDamping = false;
                    }
                    else 
                    {
                        damp = 1.f - damp;
                        if(damp <= 0.f)                    
                            m_bDamping = false;
                    }
                }
                velocity = m_velocity * damp;
                pos -= movedir * deltaFrameTime * velocity;
                gPlayerForwardBackward -= (velocity * deltaFrameTime);
            }

            TVector3 strafeVector = target;
            strafeVector = strafeVector.crossProduct(upVector).normalize();
            if(m_actions[A_LEFT])
            {
                pos += strafeVector * deltaFrameTime * m_velocity;
                gPlayerSideways -= m_velocity * deltaFrameTime;
            }

            if(m_actions[A_RGHT])
            {
                pos -= strafeVector * deltaFrameTime * m_velocity;
                gPlayerSideways += m_velocity * deltaFrameTime;
            }

            if(m_actions[A_MVUP] && m_mode == ccmGod)
            {
                pos += TVector3_UNIT_Y * deltaFrameTime * m_velocity;
            }

            if(m_actions[A_MVDN] && m_mode == ccmGod)
            {
                pos -= TVector3_UNIT_Y * deltaFrameTime * m_velocity;
            }
        }

        m_targetVector = target;

        // Update the character controller when not in God mode
        // This allows viewing the controller debug movement.
        if((m_mode != ccmGod) || (m_controllerTarget > CT_CAMERA))
        {
            core::matrix4 mat;
            mat.setRotationDegrees(rotation);

            btMatrix3x3 orn(btQuaternion (btQuaternion(btVector3(0,1,0),rotation.Y*irr::core::DEGTORAD)));
			m_ghostObject->getWorldTransform ().setBasis(orn);

            if (gPlayerForwardBackward)
            {            
                btVector3 forwardDir(mat[8],mat[9],mat[10]);
                m_ghostWalkDirection += forwardDir*gPlayerForwardBackward;
            }
            if (gPlayerSideways)
            {
                btVector3 sideWays(mat[0],mat[1],mat[2]);
                m_ghostWalkDirection += sideWays*gPlayerSideways;
            }   
            // setWalkDirection does normalization
            m_character->setWalkDirection(m_ghostWalkDirection);

            // 
            if(m_actions[A_JUMP])
            {
                // hack to get at irrlicht animator...
                getApplication()->getPhysicsManager()->jumpCharacter();
                m_actions[A_JUMP] = 0;
            }
        }

        if(m_irrlichtCollision || ((m_mode == ccmGod) && (m_controllerTarget == CT_CAMERA) ))
        {
            m_camera->setPosition(pos);
            m_camera->setTarget(m_targetVector+pos);
            m_camera->updateAbsolutePosition();
        }
    }

    //-----------------------------------------------------------------------
    //                           u p d a t e U R
    //-----------------------------------------------------------------------
    void TCharacterController::updateUR(f32 deltaFrameTime)
    {
    }

    //-----------------------------------------------------------------------
    //                u p d a t e P l a y e r F r o m G h o s t
    //-----------------------------------------------------------------------
    void TCharacterController::updatePlayerFromGhost()
    {
        m_ghostWalkDirection.setZero();
        if(m_mode == ccmGod)
            return;

        btVector3 c = m_character->getGhostObject()->getWorldTransform().getOrigin();
        core::vector3df pos (c.getX(),c.getY()+m_characterHeight,c.getZ());
        m_camera->setPosition(pos);
        m_camera->setTarget(m_targetVector+pos);
        m_camera->updateAbsolutePosition();
    }

    //-----------------------------------------------------------------------
    //                            u p d a t e
    //-----------------------------------------------------------------------
    void TCharacterController::update(float deltaFrameTime)
    {
        (this->*m_updater)(deltaFrameTime);
    }

}

