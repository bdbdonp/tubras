//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TINPUTBINDER_H_
#define _TINPUTBINDER_H_

namespace Tubras
{
    typedef TMap<TString,TEvent *>  TBindingMap;

    /**
    TInputBinder Class.
    @remarks
    Binds simple input to logic commands.
    */
    class TInputBinder 
    {
        friend class TInputHandler;
    protected:
        TBindingMap         m_commands;
        TApplication*       m_app;
        TInputBinder();
    public:
        virtual ~TInputBinder();
        int initialize();

        TParamType getParamType(const TString& parm);
        TEvent* parseCommand(const TString& keyEvent, const TString& command);

        void processKey(const TString& key);

    };
}

#endif
