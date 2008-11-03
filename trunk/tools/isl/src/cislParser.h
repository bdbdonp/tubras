//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _CISLParser_H_
#define _CISLParser_H_

#include "islLexer.h"
#include "islParser.h"
#include "irrlicht.h"
#include "cst.h"
#include "cisl.h"

namespace CISL {

    class CISLParser;


    typedef irr::core::array<irr::core::stringc>  ARRAY;

    class CISLParser 
    {
        friend struct LexerContext;
    protected:
        SYMMAP                  m_matDefs;
        SYMMAP                  m_cnfDefs;
        SYMMAP                  m_mtxDefs;
        SYMMAP                  m_layDefs;

        ARRAY                   m_incDirs;
        pANTLR3_UINT8           m_fileName;
        pANTLR3_INPUT_STREAM    m_inputStream;
        STACK                   m_nameSpace;

        irr::u32                m_unNamed;

        pislLexer               m_lexer;
        CST*                    m_st;       // symbol table

        irr::scene::CSceneNodeAnimatorMaterialLayer* m_animator;
        irr::scene::ISceneNode* m_emptyNode;

        // The token stream is produced by the ANTLR3 generated lexer. Again it is a structure based
        // API/Object, which you can customise and override methods of as you wish. a Token stream is
        // supplied to the generated parser, and you can write your own token stream and pass this in
        // if you wish.
        //
        pANTLR3_COMMON_TOKEN_STREAM        m_tokenStream;

        // The Lang parser is also generated by ANTLR and accepts a token stream as explained
        // above. The token stream can be any source in fact, so long as it implements the 
        // ANTLR3_TOKEN_SOURCE interface. In this case the parser does not return anything
        // but it can of course specify any kind of return type from the rule you invoke
        // when calling it. This is the ctx (CTX macro) pointer for your parser.
        //
        pislParser                m_parser;

        // The parser produces an AST, which is returned as a member of the return type of
        // the starting rule (any rule can start first of course). This is a generated type
        // based upon the rule we start with.
        //
        islParser_script_return     m_islAST;


        // The tree nodes are managed by a tree adaptor, which doles
        // out the nodes upon request. You can make your own tree types and adaptors
        // and override the built in versions. See runtime source for details and
        // eventually the wiki entry for the C target.
        //
        pANTLR3_COMMON_TREE_NODE_STREAM    m_treeNodes;

    protected:
        virtual void _freeResources();
        void _dumpTree(pANTLR3_BASE_TREE tree);
        int _buildST(pANTLR3_BASE_TREE tree);
        int _interpret(pANTLR3_BASE_TREE tree);
        irr::core::stringc _getSpaceID(irr::core::stringc id);
        irr::core::stringc _pushSpace(irr::core::stringc name);
        irr::core::stringc _popSpace();

        void _dumpObjects();
        int _createMatrices();

        void _printMatrices();

        int _eval(pANTLR3_BASE_TREE tree, pANTLR3_BASE_TREE parent, int cidx, struct EvalResult* pr);
        irr::core::stringc _getIParent(pANTLR3_BASE_TREE tree, pANTLR3_BASE_TREE parent, int cidx);
        int _getOp(pANTLR3_BASE_TREE tree, irr::u32 idx, struct EvalResult* pr);
        irr::core::stringc _extractString(char *str);
        irr::core::stringc _getDottedName(pANTLR3_BASE_TREE tree, irr::u32 startidx=0, irr::u32 endidx=0);
        irr::core::stringc _getScope(pANTLR3_BASE_TREE tree, irr::u32 startidx=0, irr::u32 endidx=0);
        int _startDEFSym(pANTLR3_BASE_TREE tree, SymbolType type);
        int _doMath(struct EvalResult* result, ANTLR3_UINT32 op, struct EvalResult* op1, struct EvalResult* op2);
        EvalResult* _getValueResult(CSymbol* sym, irr::core::stringc val);
        int _getIntValue(EvalResult* er, int defval=0);
        irr::core::stringc _getStringValue(EvalResult*er, irr::core::stringc defval="");
        irr::f32 _getFloatValue(EvalResult* er, irr::f32 defval=0);
        bool _getBoolValue(EvalResult* er, bool defval=false);
        irr::core::matrix4& _getMatrixValue(EvalResult* er);
        irr::u32 _getColorValueFromTuple(const TUPLEITEMS& items, irr::u32 idx);

        irr::core::vector3df& _getVectorValue(EvalResult* er);
        irr::core::vector2df& _getVector2dfValue(EvalResult* er);
        irr::core::vector2di& _getVector2diValue(EvalResult* er);

        const irr::video::SColor& _getColorValue(EvalResult* er);

        bool _getMaterialLayerValue(irr::IrrlichtDevice* device, 
            CSymbol* parent, irr::core::stringc layerid, 
            irr::video::SMaterialLayer& output);

        irr::core::stringc _extractDir(irr::core::stringc filename);
        void* doInclude(char* filename);
        void  appendIncludeDirs(irr::core::stringc dirs, char sep=';');

        irr::video::SMaterial* _getMaterialValue(irr::IrrlichtDevice* device,
            CSymbol* symbol);

        CISLStatus validateScript(const irr::core::stringc fileName, const CISLErrorHandler& errorHandler=CISLErrorHandler());
        void _showObjectWarnings(SYMMAP& objects, char** validVars, char* objDesc);

    public:
        CISLParser();
        virtual ~CISLParser();

        irr::scene::CSceneNodeAnimatorMaterialLayer* getAnimator() {return m_animator;}

        CISLStatus parseScript(const irr::core::stringc fileName, 
            const bool dumpAST=false, const bool dumpST=false, const bool dumpOI=false,
            const CISLErrorHandler& errorHandler=CISLErrorHandler());

        irr::video::SMaterial* getMaterial(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        irr::video::SMaterialLayer* getMaterialLayer(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        const irr::core::matrix4& getMatrix(const irr::core::stringc varName);
        const irr::video::SColor& getColor(const irr::core::stringc varName, irr::video::SColor& defValue = 
            irr::video::SColor());

        irr::core::vector2di getVector2di(const irr::core::stringc varName,
            irr::core::vector2di defValue=irr::core::vector2di());

        irr::f32 getFloat(const irr::core::stringc varName, irr::f32 defValue);
        int getInt(const irr::core::stringc varName, const int defValue);
        irr::core::stringc getString(const irr::core::stringc varName, 
            const irr::core::stringc defValue="");
        const void* getList(const irr::core::stringc varName);

        bool isAnimatedMaterial(irr::core::stringc materialName);

        void addAnimationRef(irr::core::stringc materialName, irr::video::SMaterial& ref);


    };

    struct LexerContext {
        islLexer    orgContext;
        CISLParser*       pisl;
        void* doInclude(char* filename) 
        {
            return pisl->doInclude(filename);
        }
    };
}

#endif
