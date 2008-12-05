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

#ifndef _TRENDERENGINE_H_
#define _TRENDERENGINE_H_

#define TEntity Ogre::Entity
#define TSceneManager Ogre::SceneManager
#define TColor Ogre::ColourValue


namespace Tubras
{

    class TCamera;

    typedef map< string,TCamera *> MAP_CAMERAS;
    typedef MAP_CAMERAS::iterator MAP_CAMERAS_ITR;

    typedef map< string, TViewPort*> MAP_VIEWPORTS;
    typedef MAP_VIEWPORTS::iterator MAP_VIEWPORTS_ITR;

    typedef map< string,TSceneNode *> MAP_SCENENODES;
    typedef MAP_SCENENODES::iterator MAP_SCENENODES_ITR;

    typedef map< string,TEntity *> MAP_ENTITIES;
    typedef MAP_ENTITIES::iterator MAP_ENTITIES_ITR;

    typedef Ogre::RenderTarget::FrameStats& TRenderStats;


    class TApplication;


    class TRenderEngine : public Tubras::TSingleton<Tubras::TRenderEngine>,
        public Ogre::WindowEventListener
    {
    private:

        int                     m_WindowHandle;
        Ogre::Root*				m_pOgreRoot;
        Ogre::RenderWindow*		m_pRenderWindow;
        Ogre::RenderSystem*		m_pRenderSystem;
        TSceneManager*		    m_sceneManager;
        Ogre::Viewport*			m_pViewPort;
        TSceneNode*             m_pRootSceneNode;

        TApplication*           m_pApplication;
        TConfigFile*	        m_pConfigFile;

        TCamera*                m_camera;

        MAP_CAMERAS             m_cameras;
        MAP_VIEWPORTS			m_viewports;

        MAP_SCENENODES          m_SceneNodes;
        MAP_ENTITIES            m_Entities;

    private:
        static TRenderEngine& getSingleton(void);
        static TRenderEngine* getSingletonPtr(void);
    public:
        TRenderEngine(TConfigFile* pConfigFile);
        virtual ~TRenderEngine();

        int setBackgroundColor(TColor color);
        int setAmbientLight(TColor color);

        TSceneManager* getSceneManager() {return m_sceneManager;};

        TSceneNode* getRootSceneNode();
        TSceneNode* createSceneNode(const char *name,TSceneNode* parent);

        TEntity* createEntity(const char* entityName, const char* meshName);

        void addCamera(TCamera* camera);
        void removeCamera(string name);
        TCamera* getCamera(string cameraName);

        void addViewPort(TViewPort* viewport);
        void removeViewPort(string name);
        TViewPort* getViewPort(string viewPortName);

        int initialize();
        int getWindowHandle() {return m_WindowHandle;};

        TRenderStats getRenderStats() {return (TRenderStats) m_pRenderWindow->getStatistics();};
        Ogre::RenderWindow* getRenderWindow() {return m_pRenderWindow;};
        Ogre::Root* getRoot() {return m_pOgreRoot;};

        virtual void windowMoved(Ogre::RenderWindow* rw);
        virtual void windowResized(Ogre::RenderWindow* rw);
        virtual void windowFocusChange(Ogre::RenderWindow* rw);

        int renderFrame();

    };
}
#endif