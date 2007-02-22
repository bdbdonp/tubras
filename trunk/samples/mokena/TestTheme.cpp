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
#include "mokena.h"

//-----------------------------------------------------------------------
//                         T T e s t T h e m e
//-----------------------------------------------------------------------
TTestTheme::TTestTheme(Tubras::TString baseDir) : Tubras::TTheme(baseDir)
{


    m_bgImageName = m_configFile->getSetting("bgimage","images");

}

//-----------------------------------------------------------------------
//                             l o a d
//-----------------------------------------------------------------------
int TTestTheme::load()
{
    if(TTheme::load())
        return 1;

    m_bgMaterial = loadTexture(getName() + "Mat",getName(),m_bgImageName);



    return 0;
}

//-----------------------------------------------------------------------
//                            u n l o a d
//-----------------------------------------------------------------------
int TTestTheme::unload()
{
    if(TTheme::unload())
        return 1;

    unloadMaterial(m_bgMaterial->getName());
    delete m_bgMaterial;
    m_bgMaterial = NULL;

    return 0;
}

