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
#define TUBRAS_VERSION_STRING "0.1"
#define TUBRAS_VERSION_NAME "Abby"

#define _CRT_SECURE_NO_WARNINGS

//
// Bullet
//
//#include "btBulletCollisionCommon.h"
//#include "btBulletDynamicsCommon.h"
//#include "LinearMath/btDefaultMotionState.h"
//#include "LinearMath/btIDebugDraw.h"


#include <fstream>
#include <iomanip>

#if defined(_DEBUG) 
	#define CRTDBG_MAP_ALLOC
	#define _CRTDBG_MAP_ALLOC
	#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
	#include <stdlib.h>
	#include <crtdbg.h>
	#define new DEBUG_CLIENTBLOCK
#endif 

//
// Irrlicht
//
#include <irrlicht.h>
#include <irrXML.h>

using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

#define TMap irr::core::map
#define TMapIterator irr::core::map::iterator
#define TList irr::core::list

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 
#include "windows.h"
#endif

//#include "getopt.h"
#include <time.h>

namespace Tubras
{
    class TObject;
    class TState;
    class TApplication;
    class TXMLConfig;
    class TSceneNode;
    class TEventDelegate;
}

#include "TSingleton.h"
#include "TString.h"
#include "TRandom.h"
#include "TTimer.h"
#include "TDimension.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TAABBox.h"
#include "TMath.h"
#include "TColour.h"
#include "TVertex.h"
#include "TObject.h"
#include "TLogger.h"
#include "TDelegate.h"
#include "TEventDelegate.h"
#include "TEventParameter.h"
#include "TEvent.h"
#include "TEventQueue.h"
#include "TEventManager.h"
#include "TEventDelegate.h"
#include "TControllerFunction.h"
#include "TController.h"
#include "TControllerManager.h"
#include "TInputBinder.h"
#include "TXMLConfig.h"
#include "TSceneNode.h"
#include "TEmptyNode.h"
#include "TPlaneNode.h"
#include "TNodeFactory.h"
#include "TState.h"
#include "TRender.h"
#include "TPlayerController.h"
#include "TApplication.h"

#endif
