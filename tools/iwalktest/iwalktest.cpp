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
    m_havePayload(false),
    m_physicsEnabled(false),
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

    if(m_sceneAttributes)
        m_sceneAttributes->drop();

#ifdef TRACK_MEMORY
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
        {
            IMaterialRenderer* mr = getRenderer()->getVideoDriver()->
                getMaterialRenderer(mat.MaterialType);
            if(!mr->isTransparent())
                mat.MaterialType = EMT_SOLID;
            else
                mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
        }
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
    if(!m_physicsEnabled)
        return 1;

    if(getCharacterController()->getMode() == ccmFirstPerson)
    {
        getPhysicsManager()->setCharacterControllerMode(ccmGod);
        getCharacterController()->setControllerTarget(CT_CAMERA);
    }
    else
    {
        getPhysicsManager()->setCharacterControllerMode(ccmFirstPerson);
        getCharacterController()->setControllerTarget(CT_BOTH);
    }
    return 1;
}

//-----------------------------------------------------------------------
//              t o g g l e C o n t r o l l e r T a r g e t
//-----------------------------------------------------------------------
int TWalktest::toggleControllerTarget(const TEvent* event)
{
    TCharacterController* cc = getCharacterController();
    if(cc && (cc->getMode() == ccmGod))
    {
        if(cc->getControllerTarget() == CT_CHARACTER)
            cc->setControllerTarget(CT_CAMERA);
        else
            cc->setControllerTarget(CT_CHARACTER);
    }
    return 1;
}

//-----------------------------------------------------------------------
//                         c y c l e C a m e r a
//-----------------------------------------------------------------------
int TWalktest::cycleCamera(const TEvent* event)
{
    u32  tcams = m_cameras.size();
    TCharacterController* cc = getCharacterController();
    void *ccam=getActiveCamera();

    if((cc->getMode() != ccmGod) || !m_physicsEnabled)
    {
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
    }

    if(cc->getControllerTarget() == CT_CHARACTER)
        cc->setControllerTarget(CT_CAMERA);
    else
        cc->setControllerTarget(CT_CHARACTER);

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
//                       h a n d l e S e n s o r
//-----------------------------------------------------------------------
int TWalktest::handleSensor(const TEvent* event)
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

    m_guiDebug->updateValue(m_dbgSensorIndex, tdata, color);
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
//                      b u i l d N o d e L i s t s
//-----------------------------------------------------------------------
void TWalktest::buildNodeLists(ISceneNode* sceneNode)
{
    ESCENE_NODE_TYPE type = sceneNode->getType();
    E_MATERIAL_TYPE EMT_LM_ALPHA = getRenderer()->getCustomMaterialType("tlm_alpha");

    if( (type==ESNT_MESH || type==ESNT_OCTREE) )
    {
        IMeshSceneNode* node = (IMeshSceneNode*) sceneNode;

        for(u32 i=0; i<node->getMaterialCount(); i++)
        {
            SMaterial& mat = node->getMaterial(0);
            if((mat.MaterialType >= EMT_LIGHTMAP) && 
               (mat.MaterialType <= EMT_LIGHTMAP_LIGHTING_M4) ||
               (mat.MaterialType == EMT_LM_ALPHA))
            {
                PLMInfo p = new LMInfo;
                p->node = node;
                p->orgType = mat.MaterialType;
                p->idx = i;
                m_lightMaps.push_back(p);
            }
        }
    }
    else if (type == ESNT_ANIMATED_MESH)
    {
        IAnimatedMeshSceneNode* node = (IAnimatedMeshSceneNode*) sceneNode;
        m_animatedNodes.push_back(node);
    }
    else if(type==ESNT_LIGHT)
    {
        ILightSceneNode* node = (ILightSceneNode*) sceneNode;
        
        SLight& ldata = node->getLightData();

        IBillboardSceneNode* bnode = getSceneManager()->addBillboardSceneNode(node->getParent());
        bnode->setColor(ldata.DiffuseColor.toSColor());
        bnode->setSize(core::dimension2d<f32>(1, 1));
        bnode->setPosition(node->getPosition());
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
        node->OnRegisterSceneNode();

        TLineNode* dline;
        if(ldata.Type != ELT_POINT)
        {
            // direction is already normalized.
            TVector3 dir = ldata.Direction * ldata.Radius;
            TColor dcolor = ldata.DiffuseColor.toSColor();
            // create direction line
            TLineNode* dline =  new TLineNode(bnode,-1,TVector3_ZERO,dir,dcolor);
            dline->setVisible(true);
        }
        // pole - vertical line to the ground (y=0)
        TVector3 pos = bnode->getPosition();
        dline = new TLineNode(bnode,-1, TVector3(), TVector3(pos.X, 0, pos.Z) - pos, TColor(128, 128, 128));
        dline->setVisible(true);
    }

    list<ISceneNode*> children = sceneNode->getChildren();
    list<ISceneNode*>::Iterator itr = children.begin();
    while(itr != children.end())
    {
        ISceneNode* child = *itr;
        buildNodeLists(child);
        itr++;
    }
}

//-----------------------------------------------------------------------
//                    c r e a t e P h y s i c s O b j e c t
//-----------------------------------------------------------------------
void TWalktest::createPhysicsObject(IMeshSceneNode* mnode, io::IAttributes* userData)
{
    TPhysicsBodyShape bodyShape=stConcaveMesh;

    stringc sBodyType = userData->getAttributeAsString("Physics.BodyType");
    if(sBodyType == "none")
        return;

    stringc sBodyShape = userData->getAttributeAsString("Physics.BodyShape");
    bool isVisible = true;
    if(userData->existsAttribute("Physics.Visible"))
        isVisible = userData->getAttributeAsBool("Physics.Visible");

    bool isGhost = userData->getAttributeAsBool("Physics.Ghost");  // collision without restitution
    bool isSensor = false;

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

    if(sBodyType.equals_ignore_case("sensor"))
        isSensor = true;

    getPhysicsManager()->createObject(mnode, bodyShape, mass, radius, isVisible, isGhost, 
        isSensor, friction, restitution);

    if(userData->existsAttribute("Physics.Constraints"))
    {
        int count = userData->getAttributeAsInt("Physics.Constraints");

        for(int i=1; i<=count; i++)
        {
            SRBConstraint* pc = new SRBConstraint();
            char buf[100];
            sprintf(buf,"Constraint%d.",i);
            stringc prefix = buf;

            stringc varname = prefix + "Name";
            pc->Name = userData->getAttributeAsString(varname.c_str());

            pc->Node = mnode;

            varname = prefix + "Type";
            stringc temp = userData->getAttributeAsString(varname.c_str());
            pc->Type = ctHinge;
            if(temp.equals_ignore_case("ball"))
                pc->Type = ctBall;
            else if(temp.equals_ignore_case("cone_twist"))
                pc->Type = ctConeTwist;
            else if(temp.equals_ignore_case("generic_6_dof"))
                pc->Type = ct6DOF;
            
            varname = prefix + "Target";
            pc->Target = userData->getAttributeAsString(varname.c_str());
            
            varname = prefix + "Child";
            pc->Child = userData->getAttributeAsString(varname.c_str());
            
            varname = prefix + "Pivot";
            vector3df vtemp = userData->getAttributeAsVector3d(varname.c_str());
            pc->Pivot.setZero();
            pc->Pivot.setX(vtemp.X);
            pc->Pivot.setY(vtemp.Y);
            pc->Pivot.setZ(vtemp.Z);
            
            varname = prefix + "Axis";
            vtemp = userData->getAttributeAsVector3d(varname.c_str());
            pc->Axis.setZero();
            pc->Axis.setX(vtemp.X);
            pc->Axis.setY(vtemp.Y);
            pc->Axis.setZ(vtemp.Z);

            varname = prefix + "Limits";
            if(userData->existsAttribute(varname.c_str()))
            {
                // LimitFlags: 0XXX0XXX 
                //              zyx ZYX wheire zyx=angular 
                vector3df tvec;
                pc->LimitFlags = userData->getAttributeAsInt(varname.c_str());

                if(pc->LimitFlags & 0x07)
                {
                    varname = prefix+"LimitsMin";
                    tvec = userData->getAttributeAsVector3d(varname.c_str());
                    pc->LimitMin.setValue(tvec.X, tvec.Y, tvec.Z);
                    varname = prefix+"LimitsMax";
                    tvec = userData->getAttributeAsVector3d(varname.c_str());
                    pc->LimitMax.setValue(tvec.X, tvec.Y, tvec.Z);
                }

                // angular limits?
                if(pc->LimitFlags > 4)
                {
                    varname = prefix+"LimitsAngularMin";
                    tvec = userData->getAttributeAsVector3d(varname.c_str());
                    pc->LimitAngularMin.setValue(tvec.X, tvec.Y, tvec.Z);
                    varname = prefix+"LimitsAngularMax";
                    tvec = userData->getAttributeAsVector3d(varname.c_str());
                    pc->LimitAngularMax.setValue(tvec.X, tvec.Y, tvec.Z);
                }
            }

            m_constraints.push_back(pc);
        }
    }
}

//-----------------------------------------------------------------------
//                      o n C o n s o l e C o m m a n d
//-----------------------------------------------------------------------
int TWalktest::onConsoleCommand(const TEvent* event)
{
    TApplication::onConsoleCommand(event);

    procCommand(this, (TEvent*) event);

    return 0;
}

//-----------------------------------------------------------------------
//                      O n R e a d U s e r D a t a
//-----------------------------------------------------------------------
void TWalktest::OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData)
{
    stringc sname = forSceneNode->getName();
    static bool checkPhysicsAttributes = false;

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

        m_physicsEnabled = m_sceneAttributes->getAttributeAsBool("Physics.Enabled");
        //
        // turn gravity on
        //
        if(m_physicsEnabled)
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

        if(m_physicsEnabled)
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
//                 g e t S c e n e F r o m M a n i f e s t
//-----------------------------------------------------------------------
stringc TWalktest::getSceneFromManifest(stringc fileName)
{
    stringc result="";
    IXMLReaderUTF8* xml=0;

    xml = getFileSystem()->createXMLReaderUTF8(fileName.c_str());

    while(xml && xml->read())
    {
        if(xml->getNodeType() == EXN_ELEMENT)
        {
            const irr::c8* name = xml->getNodeName();
            if (!strcmp(name, "Scene-File"))
            {
                result = xml->getAttributeValue("value");
                break;
            }
        }
    }

    xml->drop();
    return result;
}

//-----------------------------------------------------------------------
//                          i n i t C o n f i g
//-----------------------------------------------------------------------
int TWalktest::initConfig()
{
    int size;
    struct SigStruct sig;
    struct DatStruct dat;
    IReadFile*  file;

    // look for embedded configuration (tsl) file

    // we don't have a file system yet, so use the one on the null device
    file = m_nullDevice->getFileSystem()->createAndOpenFile(m_appExecutable);
    if(!file)
    {
        logMessage(LOG_INFO, "Payload data not found - Unable to open: %s", 
            m_appExecutable.c_str());
        return TApplication::initConfig();
    }

    size = file->getSize();
    file->seek(size-sizeof(sig));
    file->read(&sig, sizeof(sig));

    if((sig.sig1 != 0x62726142) || (sig.sig2 != 0x62727269))
    {
        file->drop();
        logMessage(LOG_INFO, "Payload data not found.");
        return TApplication::initConfig();
    }

    m_havePayload = true;

    file->seek(sig.offset);
    file->read(&dat, sizeof(dat));
    u32 pcount=0;
    while((dat.sig == 0x62726142) && (pcount < sig.count))
    {
        // only processing archives here
        if(dat.type == RT_CONFIG)
        {
            void* memdata = malloc(dat.length);
            if((u32)file->read(memdata, dat.length) == dat.length)
            {
                logMessage(LOG_INFO, "Using payload config \"%s\".", dat.id);

                m_configScript = new TConfig();
                if(m_configScript->loadScript((const char *)memdata, dat.length, "default.cfg", 
                    false, false, this) == E_OK)
                {
                    file->drop();
                    m_configScript->setOverrideAttributes(this->m_configOverride);
                    return 0;
                }
                else
                {
                    file->drop();
                    return TApplication::initConfig();
                }
            }
            else
            {
                file->drop();
                return TApplication::initConfig();
            }
        }
        else
        {
            file->seek(dat.length, true);            
        }
        ++pcount;
        file->read(&dat, sizeof(dat));
    }

    file->drop();
    return TApplication::initConfig();
}

//-----------------------------------------------------------------------
//                      o n D e v i c e C r e a t e d
//-----------------------------------------------------------------------
int TWalktest::onDeviceCreated()
{
    int size;
    struct SigStruct sig;
    struct DatStruct dat;
    IReadFile*  file;
    IReadFile*  mfile;

    if(TApplication::onDeviceCreated())
        return 1;

    if(!m_havePayload)
        return 0;

    m_dataRoot = "data/";

    file = getFileSystem()->createAndOpenFile(this->m_appExecutable);

    if(!file)
    {
        logMessage(LOG_INFO, "Payload data not found - Unable to open: %s", 
            m_appExecutable.c_str());
        return 0;
    }

    size = file->getSize();
    file->seek(size-sizeof(sig));
    file->read(&sig, sizeof(sig));

    if((sig.sig1 != 0x62726142) || (sig.sig2 != 0x62727269))
    {
        file->drop();
        logMessage(LOG_INFO, "Payload data not found.");
        return 0;
    }
    logMessage(LOG_INFO, "Payload found.");

    file->seek(sig.offset);
    file->read(&dat, sizeof(dat));
    u32 pcount=0;
    while((dat.sig == 0x62726142) && (pcount < sig.count))
    {
        // only processing archives here
        if(dat.type == RT_ARCHIVE)
        {
            void* memdata = new c8[dat.length];
            if((u32)file->read(memdata, dat.length) == dat.length)
            {
                logMessage(LOG_INFO, "Adding payload archive \"%s\".", dat.id);
                mfile = getFileSystem()->createMemoryReadFile(memdata, dat.length, dat.id, true);
                getFileSystem()->addFileArchive(mfile, false, true);
            }
            else
            {
                file->drop();
                return 0;
            }
        }
        else
        {
            file->seek(dat.length, true);            
        }
        ++pcount;
        file->read(&dat, sizeof(dat));
    }

    file->drop();
    return 1;
}

//-----------------------------------------------------------------------
//                             i P r i n t f
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WINDOWS
HANDLE hStdOut=0;
HANDLE hStdIn=0;
void iPrintf(const char *msg)
{
    DWORD dwLen;
    WriteConsoleA(hStdOut,msg,strlen(msg),&dwLen,0);
}
#else
void iPrintf(const char *msg)
{
    fputs(msg, stdout);
}
#endif

//-----------------------------------------------------------------------
//                             u s a g e
//-----------------------------------------------------------------------
void usage()
{
#ifdef TUBRAS_PLATFORM_WINDOWS
    AttachConsole(ATTACH_PARENT_PROCESS);
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    hStdIn = GetStdHandle(STD_INPUT_HANDLE);
#endif
    iPrintf("\nUsage: iwalktest [options]\n\n");
    iPrintf("options: -h, -?             This help.\n");
    iPrintf("         -i <scene file>    Input scene (.irr) file name.\n");        
    iPrintf("         -a <scene archive> Scene archive directory.\n");
    iPrintf("         -p <pack file>     Packed archive.\n");
    iPrintf("         -c <config file>   Config file override.\n");
    iPrintf("         -o <config option> Config option override.\n");
    
#ifdef TUBRAS_PLATFORM_WINDOWS
    DWORD dwEvents;
    INPUT_RECORD ir[2];
    ir[0].EventType = KEY_EVENT;
    ir[0].Event.KeyEvent.bKeyDown = TRUE;
    ir[0].Event.KeyEvent.dwControlKeyState = 0;
    ir[0].Event.KeyEvent.uChar.UnicodeChar = '\r';
    ir[0].Event.KeyEvent.wRepeatCount = 1;
    ir[0].Event.KeyEvent.wVirtualKeyCode = 0x0D;
    ir[0].Event.KeyEvent.wVirtualScanCode = MapVirtualKey(0x0D, MAPVK_VK_TO_VSC);
    ir[1].EventType = KEY_EVENT;
    ir[1].Event.KeyEvent.bKeyDown = FALSE;
    ir[1].Event.KeyEvent.dwControlKeyState = 0;
    ir[1].Event.KeyEvent.uChar.UnicodeChar = '\r';
    ir[1].Event.KeyEvent.wRepeatCount = 1;
    ir[1].Event.KeyEvent.wVirtualKeyCode = 0x0D;
    ir[1].Event.KeyEvent.wVirtualScanCode = MapVirtualKey(0x0D, MAPVK_VK_TO_VSC);
    WriteConsoleInputA(hStdIn, ir, 2, &dwEvents);
    FreeConsole();
#endif
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TWalktest::initialize()
{
    TArray<stringc> folderArchives;
    stringc         sceneDirectory="";
    bool            isPacked=false;
    bool            overrideConfig=false;
    stringc         cfgFileName;
    stringc         option;

    //
    // check for scene file name passed as an argument
    //
    int c;
    IAttributes* oattr = getConfigOverride();

    while ((c = getopt(m_argc,m_argv, "?hi:a:p:c:o:")) != EOF)
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
        case 'p':
            isPacked = true;
            m_sceneFileName = optarg;
            break;
        case 'c':
            overrideConfig = true;
            cfgFileName = optarg;
            setConfigFileName(cfgFileName);
            break;
        case 'o':
            {
                option = optarg;
                s32 sep = option.findFirstChar("=:", 2);
                if(sep > 0)
                {
                    stringc opt = option.subString(0, sep);
                    stringc val = option.subString(sep+1, option.size());
                    oattr->addString(opt.c_str(), val.c_str());
                }
            }
            break;
        case 'h':
        case '?':
            usage();
            return 1;
            break;
        }        
    }

    //
    // must call inherited initialize to create and initialize
    // all sub-systems.
    //
    if(TApplication::initialize())
        return 1;

    if(!m_sceneFileName.size())
    {
        if(optind < m_argc)
        {
            m_sceneFileName = m_argv[optind++];
        }
    }

    if(!m_havePayload)
    {
        stringc caption = "iwalktest - ";
        if(m_archBits == 64)
            caption = "iwalktest (x64) - ";
        caption += m_sceneFileName;
        setWindowCaption(caption);
    }
    else
    {
        stringc caption = getFileSystem()->getFileBasename(m_appExecutable, false);
        if(m_archBits == 64)
            caption += " (x64)";

        stringc usercap = getConfig()->getString("options.caption","");
        if(usercap.size())
        {
            caption += " - ";
            caption += usercap;
        }
        setWindowCaption(caption);
    }

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

    logMessage(LOG_INFO, "walktest Scene: (%d), %s", m_sceneFileName.size(), m_sceneFileName.c_str());
    if(m_sceneFileName.size())
    {
        if(!isPacked)
        {
            // add folder archives specified on the command line
            for(u32 i=0;i<folderArchives.size();i++)
            {
                stringc folder = folderArchives[i];
                if(getFileSystem()->existFile(folder))
                    getFileSystem()->addFileArchive(folder.c_str(), false, false, EFAT_FOLDER);
            }

            // set working directory to the location of the scene file because irrb generates
            // .irrmesh & texture file references relative to the scene directory.
            stringc saveDir = getFileSystem()->getWorkingDirectory();
            getFileSystem()->changeWorkingDirectoryTo(sceneDirectory);

            getSceneManager()->loadScene(m_sceneFileName.c_str(), this);

            getFileSystem()->changeWorkingDirectoryTo(saveDir);
        }
        else
        {
            if(getFileSystem()->existFile(m_sceneFileName))
            {
                getFileSystem()->addFileArchive(m_sceneFileName.c_str(), false, false, EFAT_ZIP);
                stringc sceneName = getSceneFromManifest("manifest.xml");
                getSceneManager()->loadScene(sceneName, this);
            }
        }
    }
    else if(m_havePayload)
    {
        stringc sceneName = getSceneFromManifest("manifest.xml");
        getSceneManager()->loadScene(sceneName, this);
    }

    addHelpText("wasd -","Camera movement");
    addHelpText("ec -","Camera elevation");
    addHelpText("arrow -","Camera rotation");
    addHelpText("shift -","Camera velocity+");
    addHelpText("space -","Camera jump");
    addHelpText("I -","Invert mouse");
    addHelpText("L -","Toggle debug lights");
    addHelpText("M -","Toggle light maps");
    addHelpText("prt -","Screen capture");
    addHelpText("tab -","Cycle camera");
    addHelpText("F1 -","Toggle help");
    addHelpText("F2 -","Toggle debug info");
    addHelpText("F3 -","Cycle wire/pts");
    if(m_physicsEnabled)
        addHelpText("F4 -","Toggle Phys dbg");
    addHelpText("F5 -","Cycle dbg data");
    if(m_physicsEnabled)
        addHelpText("F7 -","Toggle God mode");
    addHelpText("F8 -","Toggle console");

    if(getConfig()->getBool("options.showHelpGUI", true))
        TApplication::toggleHelpGUI();

    if(getConfig()->getBool("options.showDebugGUI", true))
        TApplication::toggleDebugGUI();

    // add sensor debug area
    m_dbgSensorIndex = m_guiDebug->addItem("Active Sensor:");
    m_guiDebug->updateValue(m_dbgSensorIndex, "None");

    acceptEvent("help",EVENT_DELEGATE(TWalktest::toggleHelp));
    acceptEvent("idbg",EVENT_DELEGATE(TWalktest::toggleDebug));      
    acceptEvent("ldbg",EVENT_DELEGATE(TWalktest::toggleDebugLights));      
    acceptEvent("mdbg",EVENT_DELEGATE(TWalktest::toggleLightMaps));      
    acceptEvent("wire",EVENT_DELEGATE(TWalktest::toggleWire));  
    if(m_physicsEnabled)
        acceptEvent("pdbg",EVENT_DELEGATE(TWalktest::togglePhysicsDebug));      
    acceptEvent("cdbg",EVENT_DELEGATE(TWalktest::cycleDebug));
    acceptEvent("ccam",EVENT_DELEGATE(TWalktest::cycleCamera));
    acceptEvent("sprt",EVENT_DELEGATE(TWalktest::captureScreen));
    if(m_physicsEnabled)
        acceptEvent("tgod",EVENT_DELEGATE(TWalktest::toggleGod)); 
    acceptEvent("quit",EVENT_DELEGATE(TWalktest::quit));   
    if(m_physicsEnabled)
    {
        acceptEvent("sensor.enter", EVENT_DELEGATE(TWalktest::handleSensor));
        acceptEvent("sensor.exit", EVENT_DELEGATE(TWalktest::handleSensor));
    }

    // build lightmap, light, & animation node lists
    buildNodeLists(getSceneManager()->getRootSceneNode());

    //
    // add physics constraints
    //
    if(m_constraints.size())
        getPhysicsManager()->addConstraints(m_constraints);

    TRecti vp = getRenderer()->getVideoDriver()->getViewPort();
    getActiveCamera()->setAspectRatio((f32)vp.getWidth() / (f32)vp.getHeight());
    getCharacterController()->setCamera(getActiveCamera());
    PCamCharInfo pci = getCamCharInfo(getActiveCamera());
    if(pci)
    {
        getPhysicsManager()->setCharacterAttributes(pci->width, pci->height, 
            pci->stepHeight, pci->jumpSpeed);
    }

    if(m_physicsEnabled)
        getCharacterController()->setMode(ccmFirstPerson);
    else
    {
        getCharacterController()->setMode(ccmGod);
        getCharacterController()->setControllerTarget(CT_CAMERA);
    }

    addHelpText("Esc -","Quit");

    return 0;
}

//-----------------------------------------------------------------------
//                              m a i n
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WINDOWS
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 
#endif
int main(int argc, const char **argv)
{
    TWalktest app;
#ifdef _DEBUG
	//m_breakOnAlloc(168157);
#endif
    app.setArgs(argc,argv);

    if(!app.initialize())
        app.run();

    return 0;
}
