//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "iwalktest.h"

//-----------------------------------------------------------------------
//                           T W a l k t e s t
//-----------------------------------------------------------------------
TWalktest::TWalktest() : TApplication("iwalktest"), m_lightsVisible(false),
    m_lightMapsVisible(true),
    m_useIrrlichtCollision(false),
    m_sceneAttributes(0)
{
}

//-----------------------------------------------------------------------
//                          ~ T W a l k t e s t
//-----------------------------------------------------------------------
TWalktest::~TWalktest()
{
    for(u32 i=0; i<m_lightMaps.size(); i++)
    {
        PLMInfo p = m_lightMaps[i];
        delete p;
    }
    m_lightMaps.clear();

    for(u32 i=0; i<m_cameras.size(); i++)
    {
        PCamCharInfo p = m_cameras[i];
        delete p;
    }
    m_lightMaps.clear();

#ifdef _DEBUG
    m_dumpMemoryReport();
#endif
}

//-----------------------------------------------------------------------
//                        t o g g l e H e l p
//-----------------------------------------------------------------------
int TWalktest::toggleHelp(const TEvent* event)
{
    this->toggleHelpGUI();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e D e b u g
//-----------------------------------------------------------------------
int TWalktest::toggleDebug(const TEvent* event)
{
    toggleDebugGUI();
    return 1;
}

//-----------------------------------------------------------------------
//                    t o g g l e D e b u g L i g h t s 
//-----------------------------------------------------------------------
int TWalktest::toggleDebugLights(const TEvent* event)
{
    m_lightsVisible = m_lightsVisible ? false : true;
    for(u32 i=0; i<m_lights.size(); i++)
    {
        m_lights[i]->setVisible(m_lightsVisible);
    }
    return 1;
}

//-----------------------------------------------------------------------
//                     t o g g l e L i g h t M a p s
//-----------------------------------------------------------------------
int TWalktest::toggleLightMaps(const TEvent* event)
{
    m_lightMapsVisible = m_lightMapsVisible ? false : true;
    for(u32 i=0; i<m_lightMaps.size(); i++)
    {
        SMaterial& mat = m_lightMaps[i]->node->getMaterial(m_lightMaps[i]->idx);

        if(m_lightMapsVisible)
            mat.MaterialType = m_lightMaps[i]->orgType;
        else
            mat.MaterialType = EMT_SOLID;
    }
    return 1;
}

//-----------------------------------------------------------------------
//                         c y c l e D e b u g
//-----------------------------------------------------------------------
int TWalktest::cycleDebug(const TEvent* event)
{
    cycleDebugData();
    return 1;
}

//-----------------------------------------------------------------------
//                         t o g g l e G o d
//-----------------------------------------------------------------------
int TWalktest::toggleGod(const TEvent* event)
{
    if(getCharacterController()->getMode() == ccmFirstPerson)
        getPhysicsManager()->setCharacterControllerMode(ccmGod);
    else
        getPhysicsManager()->setCharacterControllerMode(ccmFirstPerson);
    return 1;
}

//-----------------------------------------------------------------------
//                         c y c l e C a m e r a
//-----------------------------------------------------------------------
int TWalktest::cycleCamera(const TEvent* event)
{
    u32  tcams = m_cameras.size();
    void *ccam=getActiveCamera();
    for(u32 i=0;i<tcams;i++)
    {
        PCamCharInfo pci = m_cameras[i];

        if(ccam == (void*)pci->camera)
        {
            if( (i+1) >= tcams)
                i = 0;
            else ++i;
            pci = m_cameras[i];
            TRecti vp = getRenderer()->getVideoDriver()->getViewPort();
            ICameraSceneNode* cam = (ICameraSceneNode*)pci->camera;
            cam->setAspectRatio((f32)vp.getWidth() / (f32)vp.getHeight());
            getSceneManager()->setActiveCamera(cam);
            getCharacterController()->setCamera(cam);
            return 1;
        }
    }

    return 1;
}

//-----------------------------------------------------------------------
//                      g e t C a m C h a r I n f o
//-----------------------------------------------------------------------
PCamCharInfo TWalktest::getCamCharInfo(ICameraSceneNode* node)
{
    PCamCharInfo result=0;

    for(u32 i=0; i<m_cameras.size(); i++)
    {
        result = m_cameras[i];
        if(result->camera == node)
            return result;
    }

    return 0;
}

//-----------------------------------------------------------------------
//                       h a n d l e T r i g g e r
//-----------------------------------------------------------------------
int TWalktest::handleTrigger(const TEvent* event)
{
    ISceneNode* node = (ISceneNode*)(((TEvent*)event)->getParameter(0)->getPointerValue());
    int enter = ((TEvent*)event)->getParameter(1)->getIntValue();

    TColor color = TColor::White;
    
    Tubras::TString tdata = "None";

    if(enter)
    {
        color = TColor(255, 255, 0);
        tdata = node->getName();        
    }

    m_guiDebug->updateValue(m_dbgTriggerIndex, tdata, color);
    return 1;
}


//-----------------------------------------------------------------------
//                 t o g g l e P h y s i c s D e b u g
//-----------------------------------------------------------------------
int TWalktest::togglePhysicsDebug(const TEvent* event)
{
    TApplication::togglePhysicsDebug();
    return 1;
}

//-----------------------------------------------------------------------
//                      c a p t u r e S c r e e n
//-----------------------------------------------------------------------
int TWalktest::captureScreen(const TEvent* event)
{
    getRenderer()->captureScreen();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e W i r e
//-----------------------------------------------------------------------
int TWalktest::toggleWire(const TEvent* event)
{
    TRenderMode mode = getRenderMode();

    if(mode == rmNormal)
        setRenderMode(rmWire);
    else if(mode == rmWire)
        setRenderMode(rmPointCloud);
    else if(mode == rmPointCloud)
        setRenderMode(rmNormal);

    return 1;
}

//-----------------------------------------------------------------------
//                             q u i t
//-----------------------------------------------------------------------
int TWalktest::quit(const TEvent* event)
{
    TApplication::stopRunning();
    return 1;
}

//-----------------------------------------------------------------------
//                      b u i l d L M L i s t
//-----------------------------------------------------------------------
void TWalktest::buildLMList(ISceneNode* node)
{
    ESCENE_NODE_TYPE type = node->getType();

    if( (type==ESNT_MESH) )
    {
        IMeshSceneNode* lnode = (IMeshSceneNode*) node;

        for(u32 i=0; i<lnode->getMaterialCount(); i++)
        {
            SMaterial& mat = lnode->getMaterial(0);
            if((mat.MaterialType >= EMT_LIGHTMAP) && 
               (mat.MaterialType <= EMT_LIGHTMAP_LIGHTING_M4))
            {
                PLMInfo p = new LMInfo;
                p->node = lnode;
                p->orgType = mat.MaterialType;
                p->idx = i;
                m_lightMaps.push_back(p);
            }
        }
    }

    list<ISceneNode*> children = node->getChildren();
    list<ISceneNode*>::Iterator itr = children.begin();
    while(itr != children.end())
    {
        ISceneNode* child = *itr;
        buildLMList(child);
        itr++;
    }
}

//-----------------------------------------------------------------------
//                     b u i l d L i g h t L i s t
//-----------------------------------------------------------------------
void TWalktest::buildLightList(ISceneNode* node)
{
    ESCENE_NODE_TYPE type = node->getType();

    if( (type==ESNT_LIGHT) )
    {
        ILightSceneNode* lnode = (ILightSceneNode*) node;
        
        SLight& ldata = lnode->getLightData();

        IBillboardSceneNode* bnode = getSceneManager()->addBillboardSceneNode(lnode->getParent());
        bnode->setColor(ldata.DiffuseColor.toSColor());
        bnode->setSize(core::dimension2d<f32>(1, 1));
        bnode->setPosition(lnode->getPosition());
        bnode->setVisible(false);
        SMaterial& mat = bnode->getMaterial(0);
        ITexture* tex = getTexture("tex/lamp.tga");
        mat.setTexture(0,tex);
        mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
        mat.setFlag(EMF_LIGHTING,false);
        m_lights.push_back(bnode);

        // doLightRecalc() is called in the light scene node constructor
        // but the light attributes (light type, direction, etc.) aren't set 
        // until after the light is initially created. invoking 
        // OnRegisterSceneNode here forces a direction recalc.
        lnode->OnRegisterSceneNode();

        TLineNode* dline;
        if(ldata.Type != ELT_POINT)
        {
            // direction is already normalized.
            TVector3 dir = ldata.Direction * ldata.Radius;
            TColor dcolor = ldata.DiffuseColor.toSColor();
            // create direction line
            TLineNode* dline =  new TLineNode(bnode,-1,TVector3::ZERO,dir,dcolor);
            dline->setVisible(true);
        }
        // pole - vertical line to the ground (y=0)
        TVector3 pos = bnode->getPosition();
        dline = new TLineNode(bnode,-1, TVector3(), TVector3(pos.X, 0, pos.Z) - pos, TColor(128, 128, 128));
        dline->setVisible(true);
    }

    list<ISceneNode*> children = node->getChildren();
    list<ISceneNode*>::Iterator itr = children.begin();
    while(itr != children.end())
    {
        ISceneNode* child = *itr;
        buildLightList(child);
        itr++;
    }
}

//-----------------------------------------------------------------------
//                    c r e a t e P h y s i c s O b j e c t
//-----------------------------------------------------------------------
void TWalktest::createPhysicsObject(IMeshSceneNode* mnode, io::IAttributes* userData)
{
    TPhysicsBodyShape bodyShape=stConcaveMesh;
    TPhysicsBodyType bodyType=btStatic;

    stringc sBodyType = userData->getAttributeAsString("Physics.BodyType");
    if(sBodyType == "none")
        return;

    stringc sBodyShape = userData->getAttributeAsString("Physics.BodyShape");
    bool isVisible = true;
    if(userData->existsAttribute("Physics.Visible"))
        isVisible = userData->getAttributeAsBool("Physics.Visible");

    bool isGhost = userData->getAttributeAsBool("Physics.Ghost");  // collision without restitution
    bool isTrigger = false;

    f32 mass = userData->getAttributeAsFloat("Physics.Mass");
    f32 friction = userData->getAttributeAsFloat("Physics.Friction");
    f32 restitution = userData->getAttributeAsFloat("Physics.Restitution");
    f32 radius=0.f;
    if(userData->existsAttribute("Physics.Radius"))
        radius = userData->getAttributeAsFloat("Physics.Radius");

    if(sBodyShape.equals_ignore_case("box"))
    {
        bodyShape = stBox;               
    }
    else if(sBodyShape.equals_ignore_case("sphere"))
    {
        bodyShape = stSphere;
    }
    else if(sBodyShape.equals_ignore_case("cylinder"))
    {
        bodyShape = stCylinder;
    }
    else if(sBodyShape.equals_ignore_case("cone"))
    {
        bodyShape = stCone;
    }
    else if(sBodyShape.equals_ignore_case("convexmesh"))
    {
        bodyShape = stConvexMesh;
    }
    else if(sBodyShape.equals_ignore_case("concavemesh"))
    {
        bodyShape = stConcaveMesh;
    }

    if(sBodyType == "rigid")
        bodyType = btKinematic;
    else if(sBodyType == "dynamic")
        bodyType = btDynamic;

    if(sBodyType.equals_ignore_case("trigger"))
        isTrigger = true;

    getPhysicsManager()->createObject(mnode, bodyType, bodyShape, mass, radius, isVisible, isGhost, 
        isTrigger, friction, restitution);
}

//-----------------------------------------------------------------------
//                      O n R e a d U s e r D a t a
//-----------------------------------------------------------------------
void TWalktest::OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData)
{
    stringc sname = forSceneNode->getName();
    static bool checkPhysicsAttributes = false;
    static bool physicsEnabled = false;

    // save the root (scene) attributes.
    if(sname == "root")
    {
        m_sceneAttributes = userData;
        m_sceneAttributes->grab();
        stringc exporter = m_sceneAttributes->getAttributeAsString("Exporter");
        stringc exporterVersion = m_sceneAttributes->getAttributeAsString("Exporter.Version");
        if(exporter == "irrb")
        {
            checkPhysicsAttributes = true;
        }

        // background color?
        if(m_sceneAttributes->findAttribute("BackgroundColor") >= 0)
        {
            SColor color = m_sceneAttributes->getAttributeAsColor("BackgroundColor");
            this->getRenderer()->setBGColor(color);
        }

        physicsEnabled = m_sceneAttributes->getAttributeAsBool("Physics.Enabled");
        //
        // turn gravity on
        //
        if(physicsEnabled)
        {
            f32 gravity=-9.8f;
            if(m_sceneAttributes->existsAttribute("Gravity"))
                gravity = m_sceneAttributes->getAttributeAsFloat("Gravity");
            getPhysicsManager()->setGravity(TVector3(0.f,gravity,0.f));
        }

        return;
    }

    ESCENE_NODE_TYPE type = forSceneNode->getType();
    if(type == ESNT_MESH)
    {
        IMeshSceneNode* mnode = reinterpret_cast<IMeshSceneNode*>(forSceneNode);

        if(physicsEnabled)
        {
            createPhysicsObject(mnode, userData);
        }

        if(mnode && userData->existsAttribute("HWHint") &&
            !userData->getAttributeAsBool("Physics.Ghost"))
        {
            E_HARDWARE_MAPPING  mapping=EHM_NEVER;
            E_BUFFER_TYPE buffertype=EBT_NONE;

            IMesh* mesh = mnode->getMesh();

            stringc smapping = userData->getAttributeAsString("HWHint");
            if(smapping == "static")
                mapping = EHM_STATIC;
            else if(smapping == "dynamic")
                mapping = EHM_DYNAMIC;
            else if(smapping == "stream")
                mapping = EHM_STREAM;

            stringc sbuffertype = userData->getAttributeAsString("HWType");
            if(sbuffertype == "vertex")
                buffertype = EBT_VERTEX;
            else if(sbuffertype == "index")
                buffertype = EBT_INDEX;
            else if(sbuffertype == "vertexindex")
                buffertype = EBT_VERTEX_AND_INDEX;

            if((mapping != EHM_NEVER) && (buffertype != EBT_NONE))
                mesh->setHardwareMappingHint(mapping, buffertype);
        }
    }
    else if(type == ESNT_CAMERA)
    {
        PCamCharInfo    pci = new CamCharInfo;
        pci->camera = reinterpret_cast<ICameraSceneNode*>(forSceneNode);
        pci->width = getConfig()->getFloat("physics.characterWidth", 1.f);
        pci->height = getConfig()->getFloat("physics.characterHeight", 2.f);
        pci->stepHeight = getConfig()->getFloat("physics.characterStepHeight", 0.35f);
        pci->jumpSpeed = getConfig()->getFloat("physics.characterJumpSpeed", 0.3f);

        if(userData->existsAttribute("Character.Width"))
            pci->width = userData->getAttributeAsFloat("Character.Width");
        if(userData->existsAttribute("Character.Height"))
            pci->height = userData->getAttributeAsFloat("Character.Height");
        if(userData->existsAttribute("Character.JumpSpeed"))
            pci->jumpSpeed = userData->getAttributeAsFloat("Character.JumpSpeed");
        if(userData->existsAttribute("Character.StepHeight"))
            pci->stepHeight = userData->getAttributeAsFloat("Character.StepHeight");
        m_cameras.push_back(pci);

    }
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TWalktest::initialize()
{
    TArray<stringc> folderArchives;
    stringc         sceneDirectory="";

    //
    // must call inherited initialize to create and initialize
    // all sub-systems.
    //
    if(TApplication::initialize())
        return 1;

    //
    // check for scene file name passed as an argument
    //
    int c;
    while ((c = getopt(m_argc,m_argv, "i:a:")) != EOF)
    {
        switch (c)
        {
        case 'i':
            m_sceneFileName = optarg;
            break;
        case 'a':
            sceneDirectory = optarg;
            folderArchives.push_back(optarg);
            break;
        }        
    }

    if(!m_sceneFileName.size())
    {
        if(optind < m_argc)
        {
            m_sceneFileName = m_argv[optind++];
        }
    }

    stringc caption = "iwalktest - ";
    caption += m_sceneFileName;
    setWindowCaption(caption);

    addHelpText("wasd -","Camera movement");
    addHelpText("ec -","Camera elevation");
    addHelpText("arrow -","Camera rotation");
    addHelpText("shift -","Camera velocity+");
    addHelpText("space -","Camera jump");
    addHelpText("I -","Invert mouse");
    addHelpText("L -","Toggle debug lights");
    addHelpText("M -","Toggle light maps");
    addHelpText("tab -","Toggle console");
    addHelpText("prt -","Screen capture");
    addHelpText("F1 -","Toggle help");
    addHelpText("F2 -","Toggle debug info");
    addHelpText("F3 -","Cycle wire/pts");
    addHelpText("F4 -","Toggle Phys dbg");
    addHelpText("F5 -","Cycle dbg data");
    addHelpText("F7 -","Toggle God mode");

    if(!getConfig()->getBool("options.showHelpAtStart", true))
        TApplication::toggleHelpGUI();

    // add trigger debug area
    m_dbgTriggerIndex = m_guiDebug->addItem("Active Trigger:");
    m_guiDebug->updateValue(m_dbgTriggerIndex, "None");

    acceptEvent("help",EVENT_DELEGATE(TWalktest::toggleHelp));
    acceptEvent("idbg",EVENT_DELEGATE(TWalktest::toggleDebug));      
    acceptEvent("ldbg",EVENT_DELEGATE(TWalktest::toggleDebugLights));      
    acceptEvent("mdbg",EVENT_DELEGATE(TWalktest::toggleLightMaps));      
    acceptEvent("wire",EVENT_DELEGATE(TWalktest::toggleWire));  
    acceptEvent("pdbg",EVENT_DELEGATE(TWalktest::togglePhysicsDebug));      
    acceptEvent("cdbg",EVENT_DELEGATE(TWalktest::cycleDebug));
    acceptEvent("sprt",EVENT_DELEGATE(TWalktest::captureScreen));
    // for now, no character controller for Bullet...
    if(getConfig()->getString("physics.library","Irrlicht").equals_ignore_case("irrlicht"))
        acceptEvent("tgod",EVENT_DELEGATE(TWalktest::toggleGod)); 
    acceptEvent("quit",EVENT_DELEGATE(TWalktest::quit));   
    acceptEvent("trigger.enter", EVENT_DELEGATE(TWalktest::handleTrigger));
    acceptEvent("trigger.exit", EVENT_DELEGATE(TWalktest::handleTrigger));

    //
    // set default camera position
    //
    ICameraSceneNode* cam;
    cam = getActiveCamera();
    TVector3 cpos = getConfig()->getVector3df("options.defcampos",cam->getPosition());
    TVector3 ctarget = getConfig()->getVector3df("options.defcamtarget",cam->getTarget());
    cam->setPosition(cpos);
    cam->setTarget(ctarget);

    if(getPhysicsManager()->getCollisionSystemType() == cstIrrlicht)
        m_useIrrlichtCollision = true;

    //
    // if scene file name not passed as a parameter then look in iwalktest.cfg
    //
    if(!m_sceneFileName.size())
        m_sceneFileName = getConfig()->getString("options.loadscene");

    if(m_sceneFileName.size())
    {
        // add folder archives specified on the command line
        for(u32 i=0;i<folderArchives.size();i++)
        {
            stringc folder = folderArchives[i];
            TFile   file(folder.c_str());
            if(file.exists())
                getFileSystem()->addFileArchive(folder.c_str(), false, false, EFAT_FOLDER);
        }

        // set working directory to the location of the scene file because irrb generates
        // .irrmesh & texture file references relative to the scene directory.
        stringc saveDir = getFileSystem()->getWorkingDirectory();
        getFileSystem()->changeWorkingDirectoryTo(sceneDirectory);

        getSceneManager()->loadScene(m_sceneFileName.c_str(), this);

        getFileSystem()->changeWorkingDirectoryTo(saveDir);
    }

    //
    // setup light debugging billboards
    //
    buildLightList(getSceneManager()->getRootSceneNode());

    //
    // setup lightmap toggling
    //
    buildLMList(getSceneManager()->getRootSceneNode());

    //
    // if multiple cameras, then setup cycling
    //
    if(m_cameras.size() > 1)
    {
        char buf[100];
        sprintf(buf,"Cycle cameras[%d]",m_cameras.size());
        addHelpText("F9 -", buf);
        acceptEvent("input.key.down.f9",EVENT_DELEGATE(TWalktest::cycleCamera));
    }

    TRecti vp = getRenderer()->getVideoDriver()->getViewPort();
    getActiveCamera()->setAspectRatio((f32)vp.getWidth() / (f32)vp.getHeight());
    getCharacterController()->setCamera(getActiveCamera());
    PCamCharInfo pci = getCamCharInfo(getActiveCamera());
    if(pci)
    {
        getPhysicsManager()->setCharacterAttributes(pci->width, pci->height, 
            pci->stepHeight, pci->jumpSpeed);
    }
    if(m_sceneAttributes && m_sceneAttributes->getAttributeAsBool("Physics.Enabled")
        && getConfig()->getString("physics.library","Irrlicht").equals_ignore_case("irrlicht"))
        getCharacterController()->setMode(ccmFirstPerson);
    else
        getCharacterController()->setMode(ccmGod);

    addHelpText("Esc -","Quit");

    return 0;
}

//-----------------------------------------------------------------------
//                              m a i n
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WIN32
#pragma comment(lib, "Irrlicht.lib") 
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 
#endif
int main(int argc, const char **argv)
{
    TWalktest app;

    app.setArgs(argc,argv);

    if(!app.initialize())
        app.run();

    return 0;
}
