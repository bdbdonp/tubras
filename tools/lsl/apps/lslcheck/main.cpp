//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#include "CLSL.h"
#include "getopt.h"
#include <errno.h>

static irr::core::stringc m_scriptName="";

//-----------------------------------------------------------------------------
//                               s h o w U s a g e
//-----------------------------------------------------------------------------
void showUsage()
{
    printf("usage: lslcheck <options> -i[input file] \n\n");
    printf("       <options> - LSL Syntax Checker options:\n");
    printf("                     -s : dump symbol table\n");
    printf("                     -o : dump object info\n");
    printf("\n");
    printf("    [input file] - LSL file.\n\n");
}

//-----------------------------------------------------------------------------
//                                   m a i n
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{

    bool oDumpST=false;
    bool oDumpOI=false;

    printf("lslcheck 0.1 Copyright(C) 2008 Tubras Software, Ltd\n\n");

    if(argc < 2)
    {
        showUsage();
        return 1;
    }

    int c;
    while ((c = getopt(argc, argv, "soi:")) != EOF)
    {
        switch (c)
        {
        case 's':
            oDumpST = true;
            break;
        case 'o':
            oDumpOI = true;
            break;
        case 'i':
            m_scriptName = optarg;
            break;
        };
            
    }

    if(!m_scriptName.size())
    {
        if(optind >= argc)
        {
            showUsage();
            return 1;
        }
        m_scriptName = argv[optind++];
    }

    printf(" Input Script: %s\n",m_scriptName.c_str());

    lsl::CLSL*   lsl = new lsl::CLSL();

    lsl::CLSLStatus status = lsl->loadScript(m_scriptName,
        oDumpST, oDumpOI);
    if(status != lsl::E_OK)
    {
        fprintf(stderr, "Check Errors\n");
    }

    // testing
    irr::core::stringc stemp = lsl->getString("options.floorTexture");
    int     itemp = lsl->getInteger("floor.type");
    irr::f32     ftemp = lsl->getFloat("options.moveSpeed");
    bool    btemp = lsl->getBool("options.showCursor");
    irr::video::SColor  ctemp = lsl->getColor("video.bgcolor");
    ctemp = lsl->getColor("video.testcolor");
    ctemp = lsl->getColor("video.testcolor2");


    delete lsl;
}