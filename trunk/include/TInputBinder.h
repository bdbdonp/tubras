//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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
    class TInputBinder : public Tubras::TSingleton<Tubras::TInputBinder>, public TObject
    {
        TBindingMap         m_commands;
    public:
        TInputBinder();
        virtual ~TInputBinder();
        static TInputBinder& getSingleton(void);
        static TInputBinder* getSingletonPtr(void);
        int initialize();

        TParamType getParamType(TString parm);
        TEvent* parseCommand(TString keyEvent, TString command);

        void processKey(TString key);

    };
}

#endif