//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------

#ifndef _TSCRIPT_H_
#define _TSCRIPT_H_

struct lua_State;

namespace Tubras
{
    class TScriptManager;
    enum SReturnType {stNumber, stBool, stString, stStringW, stTableRef};
    class SReturnValue : public IReferenceCounted
    {
    public:
        SReturnType type;
        double      dValue;
        bool        bValue;
        stringc     sValue;
        stringw     swValue;
        int         iTableRef;

        SReturnValue() : IReferenceCounted(), dValue(0.0), bValue(false), sValue(""), swValue(L""), iTableRef(-1) {}
    };

    typedef TMap< TString, void *> MAP_SCRIPTFUNCS;
    typedef void*           TModule;

    typedef MAP_SCRIPTFUNCS::Iterator MAP_SCRIPTFUNCS_ITR;

    class TScript : public IReferenceCounted
    {
        friend class TScriptManager;
    private:
        TScriptManager*     m_manager;
        stringc             m_modPath;
        stringc             m_modName;
        stringc             m_modFile;
        lua_State*          m_lua;
        void*			    m_module;
        void*			    m_application;
        MAP_SCRIPTFUNCS	    m_functions;
        TString             m_initialState;

    protected:
        void printLUAErr();
        int checkError();
        void* classToScriptObject(void *klass, TString type);
        int	unRef(void *pobj);
        TScript(TScriptManager* manager, lua_State* lua);
        virtual ~TScript();
        void logMessage(TString msg) {}

        int getReturnInt();

        int createState();
        int initializeStates(SReturnValue* value);
        TString getInitialState() {return m_initialState;}

    public:
        int initialize(const stringc modPath, const stringc modName);
        bool hasFunction(TString functionName);
        SReturnValue* callFunction(const stringc function, int resultCount, 
            const char *fmt=0, ...);

        TModule getModule() {return m_module;}
        stringc getModuleName() {return m_modName;}
    };

    int testFunc(int v);
}


#endif
