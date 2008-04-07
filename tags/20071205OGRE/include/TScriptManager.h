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

#ifndef _TSCRIPTMANAGER_H_
#define _TSCRIPTMANAGER_H_

namespace Tubras
{
    typedef std::map< TString,TScript *> MAP_SCRIPTS;
	typedef MAP_SCRIPTS::iterator MAP_SCRIPTS_ITR;


    class TScriptManager : public TSingleton<Tubras::TScriptManager>, TObject
    {
    private:
        TString             m_modPath;
        MAP_SCRIPTS         m_scripts;
        TEventDelegate*     m_eventDelegate;
        TFuncIntDelegate*   m_funcIntervalDelegate;
        PyObject*           m_funcIntervalArgs;

    protected:
        void setupRedirect();
        int handleEvent(TSEvent event);
        void functionInterval(double T,void* userData);

    public:
        TScriptManager();
        ~TScriptManager();
        static TScriptManager& getSingleton(void);
        static TScriptManager* getSingletonPtr(void);
        int initialize(TString modPath, TString appEXE);
        TString getModPath() {return m_modPath;}
        TScript* loadScript(TString scriptName);
        int unloadScript(TScript* script);
        int unloadScript(TString scriptName);
        TEventDelegate* getEventDelegate() {return m_eventDelegate;}
        TFuncIntDelegate* getFuncIntervalDelegate() {return m_funcIntervalDelegate;}
    };
}
#endif