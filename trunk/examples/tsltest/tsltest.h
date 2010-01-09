//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TSLTEST_H_
#define _TSLTEST_H_
#include "tubras.h"

using namespace Tubras;

class TSLTest : public TApplication
{
protected:
    TSL*            m_tsl;
protected:
    void _createScene();
    int quit(const TEvent* event);
    int toggleWire(const TEvent* event);

public:
    TSLTest();
    ~TSLTest();
    int initialize();
    int handleScriptError(stringc fileName, int line, int code, 
        stringc errMessage);
};

#endif
