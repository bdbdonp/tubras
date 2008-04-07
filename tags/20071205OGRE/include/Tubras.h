//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
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

#ifndef _TUBRAS_H_
#define _TUBRAS_H_

#define TUBRAS_VERSION_MAJOR 0
#define TUBRAS_VERSION_MINOR 1
#define TUBRAS_VERSION_NAME "Abby"

//
// Bullet
//
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btDefaultMotionState.h"
#include "LinearMath/btIDebugDraw.h"

#undef UNICODE
#undef _UNICODE

#include "tconfig.h"

#include "ogre.h"
#include "ogresingleton.h"
#include "ogrescenenode.h"
#include "ogrescenemanager.h"
#include "ogretextareaoverlayelement.h"
//
// python/sip
//
#include "python.h"

//
// particle system api
//
#include "pAPI.h"

//
// OIS
//
#include "ois/ois.h"

//
// tgui
//
#include <tgui.h>

//
// sqlite
//
#include <sqlite3.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include "getopt.h"

typedef std::vector<std::string> TStringVector;
typedef Ogre::StringUtil::StrStreamType TStrStream;
typedef Ogre::Vector2 TVector2;
typedef Ogre::Vector4 TVector4;
typedef Ogre::Timer TTimer;
typedef Ogre::Matrix3 TMatrix3;
typedef Ogre::Real TReal;
typedef Ogre::ColourValue TColour;
typedef Ogre::FloatRect TFloatRect;
typedef Ogre::Radian TRadian;
typedef Ogre::Degree TDegree;
typedef Ogre::AxisAlignedBox TAABox;
typedef Ogre::Entity TEntity;
typedef Ogre::SceneManager TSceneManager;

#ifndef ULONG
typedef unsigned long ULONG;
#endif

namespace Tubras
{
    class TGUIManager;
    class TPhysicsManager;
    class TControllerManager;
    class TThemeManager;
    class TSoundManager;
    class TParticleManager;
    class TDynamicNode;
    class TCameraNode;
    class TCamera;
    class TApplication;
    class TSound;
    class TSceneNode;
    class TModelNode;
    class TActorNode;
    class TParticleAction;
    class TParticleDomain;
    class TParticleNode;
    class TSound;
    class TMaterial;
    class TRenderEngine;
    class TController;
    class TDynamicWorld;
    class TState;
    class TInterval;
    class TQuaternion;
    class TScriptManager;
    class TParticleGroup;
}

#include "tstring.h"
#include "tvector3.h"
#include "tquaternion.h"
#include "tmatrix4.h"
#include "tray.h"
#include "tfile.h"
#include "tdelegate.h"
#include "teventdelegate.h"
#include "ttaskdelegate.h"
#include "tfuncintdelegate.h"
#include "trandom.h"
#include "ttimer.h"
#include "tsingleton.h"
#include "teventparameter.h"
#include "tevent.h"
#include "teventqueue.h"
#include "teventmanager.h"
#include "tobject.h"
#include "tdatabase.h"
#include "tregistry.h"
#include "tdatabasemanager.h"
#include "tcallbacks.h"
#include "tinterval.h"
#include "tfunctioninterval.h"
#include "tlerpinterval.h"
#include "tlerpfunction.h"
#include "tlerpscenenodeinterval.h"
#include "tlerpposinterval.h"
#include "tlerphprinterval.h"
#include "tintervalmanager.h"
#include "tconfigfile.h"
#include "tinputbinder.h"
#include "tinputhandler.h"
#include "tinputmanager.h"
#include "tscenenode.h"
#include "tmodelnode.h"
#include "tcameranode.h"
#include "tactornode.h"
#include "tcardnode.h"
#include "tdynamicnode.h"
#include "tlinenode.h"
#include "taxisnode.h"
#include "tplanenode.h"
#include "tsoundnode.h"
#include "tparticlenode.h"
#include "tviewport.h"
#include "toverlay.h"
#include "ttextoverlay.h"
#include "tmaterial.h"
#include "trenderengine.h"
#include "ttask.h"
#include "ttaskmanager.h"
#include "tguimanager.h"
#include "tcontrollerfunction.h"
#include "tcontroller.h"
#include "trotatecontroller.h"
#include "toscillatecontroller.h"
#include "tplayercontroller.h"
#include "tlinmovcontroller.h"
#include "tcontrollermanager.h"
#include "tcameranode.h"
#include "t1pcamera.h"
#include "t3pcamera.h"
#include "tstate.h"
#include "tsound.h"
#include "tnullsound.h"
#include "tsoundmanager.h"
#include "tfmsound.h"
#include "tfmsoundmanager.h"
#include "tnullsoundmanager.h"
#include "ttheme.h"
#include "tthememanager.h"
#include "tconnection.h"
#include "tconnectionmanager.h"
#include "tcolladadocument.h"
#include "tcolladamanager.h"
#include "tparticle.h"
#include "tparticledomain.h"
#include "tparticleaction.h"
#include "tparticlegroup.h"
#include "tparticlemanager.h"
#include "tapplication.h"
#include "tmotionstate.h"
#include "tobconvert.h"
#include "trigidbody.h"
#include "trayresult.h"
#include "tdynamicworld.h"
#include "tcollidershape.h"
#include "tcolliderbox.h"
#include "tcolliderplane.h"
#include "tcollidersphere.h"
#include "tcollidercylinder.h"
#include "tcollidercone.h"
#include "tcollidermesh.h"
#include "tphysicsmanager.h"
#include "tscript.h"
#include "tscriptmanager.h"

#endif
