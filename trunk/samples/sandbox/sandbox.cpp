#include "sandbox.h"

//-----------------------------------------------------------------------
//                           T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::TSandbox(int argc,char **argv) : TApplication(argc,argv,"sandbox")
{
}

//-----------------------------------------------------------------------
//                          ~ T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::~TSandbox()
{
}

//-----------------------------------------------------------------------
//                        t o g g l e H e l p
//-----------------------------------------------------------------------
int TSandbox::toggleHelp(const TEvent* event)
{
    toggleHelpOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e D e b u g
//-----------------------------------------------------------------------
int TSandbox::toggleDebug(const TEvent* event)
{
    toggleDebugOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                      c a p t u r e S c r e e n
//-----------------------------------------------------------------------
int TSandbox::captureScreen(const TEvent* event)
{
    getRenderer()->captureScreen();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e W i r e
//-----------------------------------------------------------------------
int TSandbox::toggleWire(const TEvent* event)
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
int TSandbox::quit(const TEvent* event)
{
    TApplication::stopRunning();
    return 1;
}

//-----------------------------------------------------------------------
//                       t e s t I n t e r v a l
//-----------------------------------------------------------------------
void TSandbox::testInterval(double T, void* userData)
{
    char buf[100];
    sprintf(buf,"testIntervale T: %.3f",T);
    logMessage(buf);
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TSandbox::initialize()
{
    if(TApplication::initialize())
        return 1;

    
    addHelpText("wasd - Camera movement");
    addHelpText("   i - Invert mouse");
    addHelpText(" prt - Screen capture");
    addHelpText("  F1 - Toggle help");
    addHelpText("  F2 - Toggle debug");
    addHelpText("  F3 - Cycle wire/pts");

    acceptEvent("key.down.f1",EVENT_DELEGATE(TSandbox::toggleHelp));
    acceptEvent("key.down.f2",EVENT_DELEGATE(TSandbox::toggleDebug));      
    acceptEvent("key.down.f3",EVENT_DELEGATE(TSandbox::toggleWire));  
    acceptEvent("key.down.prtscr",EVENT_DELEGATE(TSandbox::captureScreen));
    acceptEvent("key.down.esc",EVENT_DELEGATE(TSandbox::quit));    
    

    /*
    TEmptyNode* enode = (TEmptyNode *)addSceneNode("TEmptyNode",getRootSceneNode());  

    TPlaneNode* pnode = (TPlaneNode*)addSceneNode("TPlaneNode",getRootSceneNode());


    pnode->initialize(300.0,TVector3::UNIT_Y);
    pnode->setPosition(TVector3(0,-5,0));
    SMaterial& mat = pnode->getMaterial(0);
    ITexture* tex = getTexture("data/tex/grid.tga");
    mat.setTexture(0,tex);    
    mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
    mat.setFlag(EMF_LIGHTING,false);
    mat.getTextureMatrix(0).setTextureScale(20.0,20.0);

    
    
    ISceneNode* node = getSceneManager()->addCubeSceneNode(10);
	node->setPosition(TVector3(0,-15,-25));
    SMaterial& mat2 = node->getMaterial(0);
    mat2.setFlag(EMF_LIGHTING,false);
    mat2.AmbientColor = TColour(255,0,0);
    mat2.DiffuseColor = TColour(255,0,0);
    new TRotateController("testRot",node,180.0);
    new TOscillateController("testOsc",node,1.0,20.0);
    
    IAnimatedMesh* mesh = getSceneManager()->addArrowMesh("testArrow",
        SColor(255,255,0,0), SColor(255,255,255,0),16,256,10,8,1,3);
    node = getSceneManager()->addMeshSceneNode(mesh->getMesh(0));
    node->getMaterial(0).setFlag(EMF_LIGHTING,false);
    node->getMaterial(1).setFlag(EMF_LIGHTING,false);

    new TRotateController("testRot2",node,250.0,TVector3::UNIT_Z);
    new TOscillateController("testOsc2",node,1.0,10.0,TVector3::UNIT_Z);    
    
    TSound* sound = loadSound("data/snd/ambient.ogg");
    sound->setLoop(true);
    //sound->play();
    */

    //
    // interval 0.0-1.0 for a period of 4 seconds, ease in blending.
    //
    TInterval* interval = new TInterval("testInterval",0.f,1.f,4.0f,INTERVAL_DELEGATE(TSandbox::testInterval),0,btEaseIn);

    return 0;
}

//-----------------------------------------------------------------------
//                              m a i n
//-----------------------------------------------------------------------
#ifdef WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    char    **argv=__argv;
    int     argc=__argc;
#else
extern "C" {
    int main(int argc, char **argv)
    {
#endif
        TSandbox app(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;
    }