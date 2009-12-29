#include "main.h"

#ifdef USE_IRR
static ISceneCollisionManager* m_collisionManager=0;
static IMetaTriangleSelector* m_world=0;
static IMetaTriangleSelector* m_triggers=0;
static ISceneNodeAnimatorCollisionResponse* m_character=0;

extern IrrlichtDevice*      m_device;
extern IVideoDriver*        m_videoDriver;
extern ISceneManager*       m_sceneManager;
extern IFileSystem*         m_fileSystem;
extern IEventReceiver*      m_eventReceiver;
extern IGUIEnvironment*     m_gui;
extern ICameraSceneNode*    m_camera;
extern ISceneNodeAnimatorCameraFPS* m_fpsAnimator;


//-----------------------------------------------------------------------------
//                       _ i n i t P h y s i c s L i b r a r y
//-----------------------------------------------------------------------------
int _initPhysicsLibrary()
{
    vector3df ellipsoid(2,5,2);
    vector3df gravity(0,-0.1f, 0);

    m_collisionManager = m_sceneManager->getSceneCollisionManager();
    m_world = m_sceneManager->createMetaTriangleSelector();
    m_character =  m_sceneManager->createCollisionResponseAnimator(m_world, m_camera, ellipsoid, gravity);
    m_camera->addAnimator(m_character);

    // later we will test for collisions against all geometry added to m_triggers.
    m_triggers = m_sceneManager->createMetaTriangleSelector();


    // set default "character" (response animator) size
    m_character->setEllipsoidRadius(vector3df(1.f, 2.f, 1.f));
    m_character->setGravity(vector3df(0.f, -9.8f, 0.f));
    return 0;
}

//-----------------------------------------------------------------------------
//                       _ a d d P h y s i c s O b j e c t
//-----------------------------------------------------------------------------
void _addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData)
{
    struct PhysicsAttributes attr;
    scene::IMesh* mesh=0;

    switch(node->getType())
    {
    case scene::ESNT_ANIMATED_MESH:
        mesh =  static_cast<scene::IAnimatedMeshSceneNode*>(node)->getMesh();
        break;
    case scene::ESNT_MESH:
        mesh =  static_cast<scene::IMeshSceneNode*>(node)->getMesh();
        break;
    } 
    if(!mesh)
    {
        printf("Error creating physics object - Mesh is NULL for %s\n", node->getName());
        return;
    }

    _setPhysicsAttributes(userData, attr);

    irr::scene::ITriangleSelector* selector = m_sceneManager->createTriangleSelector(mesh, node);
    if(!attr.trigger)
        m_world->addTriangleSelector(selector);
    else
        m_triggers->addTriangleSelector(selector);

    // collision only ?
    if(!attr.visible)
    {
        // turn off visibility
        node->setVisible(false);
    }
}

//-----------------------------------------------------------------------------
//                   _ d i s p l a y P h y s i c s D e b u g
//-----------------------------------------------------------------------------
void _displayPhysicsDebug()
{
    irr::core::triangle3df* tris, *tri;
    video::IVideoDriver* driver = m_sceneManager->getVideoDriver();
    s32 outCount;
    s32 tcount  = m_world->getTriangleCount();

    // collision (green)
    if(tcount)
    {
        tri = 
        tris = (irr::core::triangle3df*) malloc(sizeof(irr::core::triangle3df) * tcount);
        m_world->getTriangles(tris, tcount, outCount);
        video::SColor color(255, 0, 255, 0);

        for(int i=0; i<outCount; i++)
        {            
            driver->draw3DLine(tri->pointA, tri->pointB, color);
            driver->draw3DLine(tri->pointB, tri->pointC, color);
            driver->draw3DLine(tri->pointA, tri->pointC, color);
            ++tri;
        }
        free(tris);
    }

    // triggers (yellow)
    tcount  = m_triggers->getTriangleCount();
    if(!tcount)
        return;

    tri = 
    tris = (irr::core::triangle3df*) malloc(sizeof(irr::core::triangle3df) * tcount);
    m_triggers->getTriangles(tris, tcount, outCount);
    video::SColor color(255, 255, 255, 0);

    for(int i=0; i<outCount; i++)
    {
        driver->draw3DLine(tri->pointA, tri->pointB, color);
        driver->draw3DLine(tri->pointB, tri->pointC, color);
        driver->draw3DLine(tri->pointA, tri->pointC, color);
        ++tri;
    }
    free(tris);
}

//-----------------------------------------------------------------------------
//                        _ s t e p S i m u l a t i o n
//-----------------------------------------------------------------------------
void _stepSimulation(irr::u32 deltaMS)
{
    static bool firstUpdate=true;
    static core::vector3df lastPosition;
    static scene::ISceneNode* activeTrigger=0;

    // check for collision against "trigger" geometry
    const scene::ISceneNode* node=0;
    core::vector3df directionAndSpeed;
    core::triangle3df triout;
    core::vector3df hitPosition;
    bool falling;
    core::vector3df currentPosition = m_sceneManager->getActiveCamera()->getAbsolutePosition();
    if(firstUpdate)
    {
        lastPosition = currentPosition;
        firstUpdate = false;
    }

    directionAndSpeed.set(0.1f, 0.1f, 0.f); // ...
    lastPosition  = currentPosition;

    m_collisionManager->getCollisionResultPosition(
        m_triggers, 
        currentPosition,
        m_character->getEllipsoidRadius(),
        directionAndSpeed,
        triout,
        hitPosition,
        falling,
        node);

    // hit?
    if(node)
    {
        if(node != activeTrigger)
        {
            // enter event
            SEvent event;
            event.UserEvent.UserData1 = TRIGGER_ENTER;
            event.UserEvent.UserData2 = (s32)node;
            m_sceneManager->postEventFromUser(event);
            activeTrigger = (scene::ISceneNode*) node;
        }
    }
    else if(activeTrigger)  // no collisions and previous = exit
    {
        // exit event
        SEvent event;
        event.UserEvent.UserData1 = TRIGGER_EXIT;
        event.UserEvent.UserData2 = (s32)activeTrigger;
        m_sceneManager->postEventFromUser(event);
        activeTrigger = 0;
    }

}
#endif