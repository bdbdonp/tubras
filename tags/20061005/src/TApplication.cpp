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
#include "direct.h"
#include <CEGUI/CEGUISystem.h>

static Tubras::TApplication *theApp;
using namespace Ogre;

namespace Tubras
{

    TApplication *getApplication() {
        return theApp;
    }

    //-----------------------------------------------------------------------
    //                       T A p p l i c a t i o n
    //-----------------------------------------------------------------------
    TApplication::TApplication(int argc,char** argv,string appName) : TEventHandler()
    {
        theApp = this;
        m_argc = argc;
        m_argv = argv;
        m_lastError = 0;
        m_currentState = NULL;
        m_appName = appName;
        m_initialState = "";
        m_GUISchemeName = "";
        m_themeDirectory = "";
        m_physicsManager = NULL;
        m_GUIManager = NULL;
        m_themeManager = NULL;
        m_intervalManager = NULL;
        m_taskManager = NULL;
        m_soundManager = NULL;
        m_inputManager = NULL;
        m_eventManager = NULL;
        m_renderEngine = NULL;
        m_configFile = NULL;
        m_random = NULL;
        m_debugOverlay = NULL;


    }

    //-----------------------------------------------------------------------
    //                      ~ T A p p l i c a t i o n
    //-----------------------------------------------------------------------
    TApplication::~TApplication()
    {
        //
        // clean up states
        //
        while(!m_stateStack.empty())
        {
            TState* state = m_stateStack.front();
            state->Exit();
            m_stateStack.pop_front();
        }

        TStateMapItr sit;
        for(sit = m_states.begin();sit != m_states.end();++sit)
        {
            TState* state = sit->second;
            delete state;
        }

        if(m_debugOverlay)
            delete m_debugOverlay;

        if(m_physicsManager)
            delete m_physicsManager;

        if(m_GUIManager)
            delete m_GUIManager;

        if(m_themeManager)
            delete m_themeManager;

        if(m_intervalManager)
            delete m_intervalManager;

        if(m_taskManager)
            delete m_taskManager;

        if(m_soundManager)
        {
            m_soundManager->clearCache();
            delete m_soundManager;
        }

        if(m_inputManager)
            delete m_inputManager;

        if(m_eventManager)
            delete m_eventManager;

        if(m_renderEngine)
            delete m_renderEngine;

        if(m_configFile)
            delete m_configFile;

        if(m_random)
            delete m_random;

    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TApplication* TSingleton<TApplication>::ms_Singleton = 0;

    TApplication* TApplication::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TApplication& TApplication::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                       c r e a t e T i m e r
    //-----------------------------------------------------------------------
    TTimer* TApplication::createTimer()
    {
        TTimer* pTimer;
        pTimer = new TTimer();
        pTimer->reset();
        return pTimer;
    }

    //-----------------------------------------------------------------------
    //                       c h a n g e F i l e E x t
    //-----------------------------------------------------------------------
    string TApplication::changeFileExt(string filename,string newext) {
        string      res;
        char        path[_MAX_PATH];
        char        drive[_MAX_DRIVE];
        char        dir[_MAX_DIR];
        char        file[_MAX_FNAME];
        char        ext[_MAX_EXT];

        _splitpath(filename.c_str(),drive,dir,file,ext);

        _makepath(path,drive,dir,file,newext.c_str());

        res = path;

        return res;
    }

    //-----------------------------------------------------------------------
    //                    c r e a t e S c e n e M a n a g e r
    //-----------------------------------------------------------------------
    TSceneManager* TApplication::createSceneManager(Ogre::Root* root)
    {
        return root->createSceneManager(ST_GENERIC,"TubrasSceneManager");
    }

    //-----------------------------------------------------------------------
    //                       s e t G U I S c h e m e
    //-----------------------------------------------------------------------
    void TApplication::setGUIScheme(string schemeName,string lookName)
    {
        m_GUISchemeName = schemeName;
        m_GUILookName = lookName;
    }

    //-----------------------------------------------------------------------
    //                   s e t T h e m e D i r e c t o r y
    //-----------------------------------------------------------------------
    void TApplication::setThemeDirectory(string themeDirectory)
    {
        m_themeDirectory = themeDirectory;
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TApplication::initialize()
    {
        if(TEventHandler::initialize())
            return 1;

        //
        // random number generator
        //
        m_random = new TRandom();
        m_random->randomize();

        //
        // configuration system
        //
        char* pdir = (char*)malloc(512);
        _getcwd(pdir,512);
        m_currentDirectory = pdir;
        free(pdir);

        m_appExecutable = m_argv[0];
        m_configName = changeFileExt(m_appExecutable,".cfg");
        m_logName = changeFileExt(m_appExecutable,".log");

        if(initConfig())
            return 1;

        //
        // event manager
        //
        m_eventManager = new TEventManager();
        if(m_eventManager->initialize())
            return 1;

        //
        // interval manager
        //
        m_intervalManager = new TIntervalManager();
        if(m_intervalManager->initialize())
            return 1;

        //
        // task manager
        //
        m_taskManager = new TTaskManager();
        if(m_taskManager->initialize())
            return 1;

        //
        // render engine
        //
        if(initRenderEngine())
            return 1;

        m_windowHandle = m_renderEngine->getWindowHandle();
        m_globalClock = m_renderEngine->getRoot()->getTimer();
        m_taskManager->setGlobalClock(m_globalClock);

        //
        // input system
        //
        if(initInputSystem())
            return 1;

        //
        // collision/physics system
        //
        m_physicsManager = new TPhysicsManager();
        if(m_physicsManager->initialize())
            return 1;

        //
        // sound system
        //
        if(initSoundSystem())
            return 1;

        //
        // GUI System
        //

        m_GUIManager = new TGUIManager();
        if(m_GUIManager->initialize(m_GUISchemeName, m_GUILookName))
            return 1;

        m_GUISheet = new TWindow(NULL,"application-sheet");
        m_GUIManager->getSystem()->setGUISheet(m_GUISheet->getWidget());

        m_console = new TConsole(m_GUISheet,"CommandConsole");
        m_console->setVisible(false);


        logMessage(" ");
        logMessage("*** Tubras Core Initialized ***");
        logMessage(" ");

        //
        // create and initialize the theme manager
        //
        m_themeManager = new TThemeManager();
        if(!m_themeDirectory.empty())
            m_themeManager->initialize(m_themeDirectory);

        //
        // create and initialize the application/game states
        //
        if(createStates())
            return 1;

        TStateMapItr sit;

        for(sit = m_states.begin();sit != m_states.end();++sit)
        {
            TState* state = sit->second;
            if(state->initialize())
                return 1;
        }

        //
        // receive notifications when the main window is resized
        //
        acceptEvent("window-resized",EVENT_DELEGATE(TApplication::windowResized));
        acceptEvent("console.command",EVENT_DELEGATE(TApplication::procConsoleCommand));

        return 0;
    }

    //-----------------------------------------------------------------------
    //                 p r o c C o n s o l e C o m m a n d
    //-----------------------------------------------------------------------
    int TApplication::procConsoleCommand(Tubras::TSEvent event)
    {
        int result = 1;
        string cmd;
        TSEventParameter ep = event->getParameter(0);
        cmd = ep->getStringValue();

        if(!cmd.compare("help"))
        {
            m_console->addText(" bbox - toggle bounding boxes");
            m_console->addText("cwire - toggle collider wireframe view");
            m_console->addText("  dbg - toggle engine debug display");
            m_console->addText(" vert - toggle vertices only view");
            m_console->addText(" wire - toggle mesh wireframe view");            
        }
        else if(!cmd.compare("wire"))
        {
            if(m_renderEngine->getCamera("Default")->getPolygonMode() == Ogre::PM_SOLID)
                m_renderEngine->getCamera("Default")->setPolygonMode(Ogre::PM_WIREFRAME);
            else m_renderEngine->getCamera("Default")->setPolygonMode(Ogre::PM_SOLID);
        }
        else if(!cmd.compare("vert"))
        {
            if(m_renderEngine->getCamera("Default")->getPolygonMode() != Ogre::PM_POINTS)
                m_renderEngine->getCamera("Default")->setPolygonMode(Ogre::PM_POINTS);
            else m_renderEngine->getCamera("Default")->setPolygonMode(Ogre::PM_SOLID);
        }
        else if(!cmd.compare("bbox"))
        {
            if(m_renderEngine->getSceneManager()->getShowBoundingBoxes())
                m_renderEngine->getSceneManager()->showBoundingBoxes(false);
            else
                m_renderEngine->getSceneManager()->showBoundingBoxes(true);
        }
        else if(!cmd.compare("dbg"))
        {
            if(!m_debugOverlay)
            {
                m_debugOverlay = new Tubras::TOverlay("test",Ogre::FloatRect(0.2,0.005,0.8,0.03),
                    Ogre::ColourValue(0.8,0.8,0.8),0.75);
                m_debugOverlay->setVisible(true);
                m_debugTask = new TTask("debugTask",TASK_DELEGATE(TApplication::showDebugInfo),0,0,NULL,"testTaskDone");
                m_debugTask->start();
            }
            else
            {
                if(m_debugOverlay->getVisible())
                {
                    m_debugOverlay->setVisible(false);
                    m_debugTask->stop();
                }
                else 
                {
                    m_debugOverlay->setVisible(true);
                    m_debugTask->start();
                }
            }

        }
        else
        {
            m_console->addText("Unknown Command");
            result = 0;
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                       s h o w D e b u g I n f o
    //-----------------------------------------------------------------------
    int TApplication::showDebugInfo(TTask* task)
    {

        if(task->m_elapsedTime >= 500)
        {
            //
            // update and reset time
            //
            task->m_elapsedTime = 0;

        }

        return TTask::cont;
    }


    //-----------------------------------------------------------------------
    //                     w i n d o w R e s i z e d
    //-----------------------------------------------------------------------
    int TApplication::windowResized(Tubras::TSEvent event)
    {

        int width  = event->getParameter(0)->getIntValue();
        int height = event->getParameter(1)->getIntValue();

        m_GUIManager->getRenderer()->setDisplaySize(CEGUI::Size(width,height));
        return 0;
    }

    //-----------------------------------------------------------------------
    //                   c r e a t T h e m e C l a s s 
    //-----------------------------------------------------------------------
    TTheme* TApplication::createThemeClass(string baseDir)
    {
        return new TTheme(baseDir);
    }


    //-----------------------------------------------------------------------
    //                    i n i t S o u n d S y s t e m
    //-----------------------------------------------------------------------
    int TApplication::initSoundSystem()
    {
        m_soundManager = NULL;        
        string temp = m_configFile->getSetting("System","Sound");
        if((temp == "NULL") || (temp.empty()))
            m_soundManager = new TNullSoundManager();

        else if(temp == "FMOD")
        {
#ifdef USE_FMOD_SOUND
            try
            {
                m_soundManager = new TFMSoundManager();
            }
            catch(...)
            {
                m_soundManager = new TNullSoundManager();
            }
#endif
        }

        if(!m_soundManager)
            m_soundManager = new TNullSoundManager();


        if(m_soundManager->initialize())
            return 1;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t I n p u t S y s t e m
    //-----------------------------------------------------------------------
    int TApplication::initInputSystem()
    {
        string	msg;

        //
        // Initialize the Input System (OIS)
        //
        msg = "Initializing Input System";
        logMessage(msg.c_str());

        m_inputManager = new TInputManager(m_windowHandle);
        if(m_inputManager->initialize())
            return 1;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t R e n d e r E n g i n e
    //-----------------------------------------------------------------------
    int TApplication::initRenderEngine()
    {
        m_renderEngine = new TRenderEngine(m_configFile);
        if(m_renderEngine->initialize())
            return 1;
        return 0;
    }

    //-----------------------------------------------------------------------
    //                        i n i t C o n f i g 
    //-----------------------------------------------------------------------
    int TApplication::initConfig()
    {
        m_configFile = new TConfigFile();
        m_configFile->load(m_configName.c_str());

        string temp = m_configFile->getSetting("Console","Options");
        if(temp == "true")
            m_bConsole = true;
        else m_bConsole = false;

        temp = m_configFile->getSetting("Debug","Options");
        if(temp == "true")
            m_bDebug = true;
        else m_bDebug = false;

        //
        // create a console window
        //
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        {
            if(m_bConsole)
            {
                AllocConsole();
                m_hConsole = (int)GetStdHandle( STD_OUTPUT_HANDLE );
                freopen("CONOUT$", "a", stdout);
            }
            else m_hConsole = 0;
        }
#else   
        m_hConsole = 0;
#endif

        return 0;
    }

    //-----------------------------------------------------------------------
    //                          a d d S t a t e
    //-----------------------------------------------------------------------
    int TApplication::addState(TState *state)
    {
        m_states[state->getName()]  = state;
        return 0;
    }

    //-----------------------------------------------------------------------
    //                       c h a n g e S t a t e
    //-----------------------------------------------------------------------
    int TApplication::changeState(string stateName)
    {
        TState *state;
        bool GUIEnabled=false;

        if(!m_stateStack.empty())
        {
            state = m_stateStack.front();
            state->Pause();
        }

        state = m_states[stateName];
        if(state)
        {
            m_stateStack.push_front(state);
            state->Enter();
            m_currentState = state;
        }
        else
        {
            TStrStream msg;
            msg << "Invalid State: " << stateName << " (Not Found)";
            logMessage(msg.str().c_str());
            m_currentState = NULL;
        }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                         p u s h S t a t e
    //-----------------------------------------------------------------------
    int TApplication::pushState(string stateName)
    {
        TState *state;

        if(!m_stateStack.empty())
        {
            state = m_stateStack.front();
            state->Pause();
        }

        state = m_states[stateName];
        m_stateStack.push_front(state);
        state->Enter();
        m_currentState = state;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                          p o p S t a t e
    //-----------------------------------------------------------------------
    int TApplication::popState()
    {
        TState *state;
        TStateInfo* prevInfo=NULL;

        m_currentState = NULL;
        if(!m_stateStack.empty())
        {
            state = m_stateStack.front();
            prevInfo = state->Exit();
            m_stateStack.pop_front();
        }

        if(!m_stateStack.empty())
        {
            state = m_stateStack.front();
            state->Resume(prevInfo);
            m_currentState = state;
        }
        else
        {
            //
            // the last state was popped
            //
            m_currentState = NULL;
        }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                 c r e a t e D e f a u l t C a m e r a 
    //-----------------------------------------------------------------------
    TCamera* TApplication::createDefaultCamera()
    {
        T1PCamera* camera = new T1PCamera("Default");
        // Position it at 500 in Z direction
        camera->setPosition(Vector3(0,3,12));
        // Look back along -Z
        camera->lookAt(Vector3(0,0,0));
        camera->setNearClipDistance(0.01);

        return camera;
    }

    //-----------------------------------------------------------------------
    //              c r e a t e D e f a u l t V i e w P o r t
    //-----------------------------------------------------------------------
    TViewPort* TApplication::createDefaultViewport()
    {
        // Create one viewport, entire window
        TCamera* camera = m_renderEngine->getCamera("Default");

        TViewPort* viewport = new TViewPort("Default", camera,
            m_renderEngine->getRenderWindow(),
            0.0,0.0,1.0,1.0,0);

        viewport->setBackgroundColour(ColourValue(0,0,0));

        // Alter the camera aspect ratio to match the viewport
        if(camera)
            camera->setAspectRatio(Real(viewport->getActualWidth()) / 
            Real(viewport->getActualHeight()));

        return viewport;
    }

    //-----------------------------------------------------------------------
    //                       t o g g l e C o n s o l e
    //-----------------------------------------------------------------------
    void TApplication::toggleConsole()
    {
        m_console->toggle();
    }

    //-----------------------------------------------------------------------
    //                      c a p t u r e S c r e e n 
    //-----------------------------------------------------------------------
    void TApplication::captureScreen(string fileName)
    {
        m_renderEngine->getRenderWindow()->writeContentsToFile(fileName);
    }

    //-----------------------------------------------------------------------
    //                      c a p t u r e S c r e e n 
    //-----------------------------------------------------------------------
    void TApplication::captureScreen()
    {
        m_renderEngine->getRenderWindow()->writeContentsToTimestampedFile("cap",
            getConfigFile()->getSetting("ScreenCapExt","Options"));
    }

    //-----------------------------------------------------------------------
    //                         l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TApplication::logMessage(const char* msg)
    {
        Ogre::LogManager *lp = Ogre::LogManager::getSingletonPtr();
        if(lp)
            lp->logMessage(msg);
        if(m_hConsole)
        {
            printf(msg);
            printf("\n");
        }

        return;
    }

    //-----------------------------------------------------------------------
    //                        f i n d A r c h i v e
    //-----------------------------------------------------------------------
    Ogre::Archive* TApplication::findArchive(string &filename)
    {
        Ogre::ResourceGroupManager *grp = Ogre::ResourceGroupManager::getSingletonPtr();
        grp->resourceExists("General",filename);

        return NULL;
    }

    //-----------------------------------------------------------------------
    //                              r u n 
    //-----------------------------------------------------------------------
    void TApplication::run()
    {

        string msg; 

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        HWND hWnd;
        hWnd = (HWND)((void *)m_renderEngine->getWindowHandle());
#endif
        //
        // using state management?
        //
        if(m_initialState != "")
        {
            pushState(m_initialState);
        }
        else m_currentState = (TState *) this;

        m_running = true;
        m_lastTime = m_globalClock->getMilliseconds();

        while(m_running)
        {

            Ogre::WindowEventUtilities::messagePump();

            //
            // calculate time since last update (milliseconds)
            //
            m_currentTime = m_globalClock->getMilliseconds();

            m_deltaTime = (m_currentTime - m_lastTime);

            m_lastTime = m_currentTime;

            //
            // process queued events
            //
            m_eventManager->step();

            //
            // process input
            //
            m_inputManager->capture();

            //
            // update the GUI system
            //
            if(m_currentState && m_currentState->getGUIEnabled())
                m_GUIManager->injectTimePulse(m_deltaTime);

            //
            // update physics & collision detection
            //
            m_physicsManager->step(m_deltaTime);

            //
            // step the sound system
            //
            m_soundManager->step();

            //
            // run tasks
            //
            m_taskManager->step();

            //
            // run intervals
            //
            m_intervalManager->step();

            //
            // render frame
            //
            if(!m_renderEngine->renderFrame())
                break;

            ++m_frames;
        }

    }

}