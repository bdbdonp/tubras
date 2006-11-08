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

#ifndef __TPHYSICSMANAGER_H_
#define __TPHYSICSMANAGER_H_

namespace Tubras
{
    enum TPhysicsMode
    {
        pmNone,
        pmCollisionMode,
        pmDynamicsMode,
    };

    class TPhysicsManager : public TSingleton<Tubras::TPhysicsManager>, public TObject
    {
    protected:
        TDynamicWorld*          m_world;
        TPhysicsMode            m_mode;
        string					m_userDebugString;
        TTextOverlay*           m_debugOverlay;
        TTask*                  m_debugTask;
    protected:
        virtual int showDebugInfo(TTask* task);

    public:
        TPhysicsManager();
        virtual ~TPhysicsManager();

        static TPhysicsManager& getSingleton(void);
        static TPhysicsManager* getSingletonPtr(void);

        int initialize();

        void setUserDebugString(string value);
        void toggleDebugOverlay();

        TDynamicWorld* getWorld() {return m_world;};
        void step(float delta) {m_world->step(delta);};

    };
}


#endif
