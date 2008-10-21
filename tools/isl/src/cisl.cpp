#include "CISL.h"
#include <errno.h>
namespace CISL
{
    static char* MATVARS[] =
    { "type",
      "ambient",
      "diffuse",
      "emissive",
      "specular",
      "shininess",
      "parm1",
      "parm2",
      "thickness",
      "gouraud",
      "lighting",
      "zwriteenable",
      "backfaceculling",
      "frontfaceculling",
      "fogenable",
      "normalizenormals",
      "zbuffer",
      0
    };

    void islRecognitionError	    (pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8 * tokenNames);

    //-------------------------------------------------------------------------
    //                                  C I S L
    //-------------------------------------------------------------------------
    CISL::CISL() : m_fileName(0),
        m_inputStream(0),
        m_lexer(0),
        m_tokenStream(0),
        m_parser(0),
        m_treeNodes(0),
        m_st(0)
    {
    }

    //-------------------------------------------------------------------------
    //                                 ~ C I S L
    //-------------------------------------------------------------------------
    CISL::~CISL()
    {
        _freeResources();
    }

    //-------------------------------------------------------------------------
    //                          _ f r e e R e s o u r c e s
    //-------------------------------------------------------------------------
    void CISL::_freeResources()
    {
        if(m_st)
        {
            delete m_st;
            m_st = 0;
        }

        if(m_treeNodes)
        {
            m_treeNodes->free(m_treeNodes);
            m_treeNodes = 0;
        }

        if(m_parser)
        {
            m_parser->free(m_parser);      
            m_parser = 0;
        }

        if(m_tokenStream)
        {
            m_tokenStream ->free  (m_tokenStream);  
            m_tokenStream = 0;
        }
        if(m_lexer)
        {
            m_lexer->free(m_lexer);      
            m_lexer = 0;
        }
        if(m_inputStream)
        {
            m_inputStream->close (m_inputStream);    
            m_inputStream = 0;
        }
    }

    //-------------------------------------------------------------------------
    //                         f i l e E x i s t s
    //-------------------------------------------------------------------------
    bool fileExists(const irr::core::stringc fileName)
    {
        struct stat buf;
        if(stat(fileName.c_str(),&buf) != 0)
        {
            if(errno == ENOENT)
            {
                return false;
            }
        }
        return true;
    }

    //-------------------------------------------------------------------------
    //                             d o I n c l u d e
    //-------------------------------------------------------------------------
    void* CISL::doInclude(char* filename)
    {
        irr::core::stringc fname = _extractString(filename);
        // need to track these to free them later...
        if(fileExists(fname))
        {

            return antlr3AsciiFileStreamNew((pANTLR3_UINT8)fname.c_str());
        }

        irr::core::stringc afilename="";
        for(irr::u32 i=0; i<m_incDirs.size(); i++)
        {
            afilename = m_incDirs[i] + fname;
            if(fileExists(afilename))
                return antlr3AsciiFileStreamNew((pANTLR3_UINT8)afilename.c_str());
        }



        return 0;
    }

    //-------------------------------------------------------------------------
    //                       a p p e n d I n c l u d e D i r s
    //-------------------------------------------------------------------------
    void CISL::appendIncludeDirs(irr::core::stringc dirs, char sep)
    {
        int idx,s=0,e,end=dirs.size();
        irr::core::stringc dir="";

        for(idx=0;idx<end;idx++)
        {
            if(dirs[idx] == sep)
            {
                dir = dirs.subString(s,idx);
                m_incDirs.push_back(dir);
                s = idx;
            }
        }
        dir = dirs.subString(s,end);
        m_incDirs.push_back(dir);
    }

    //-------------------------------------------------------------------------
    //                          g e t M a t e r i a l
    //-------------------------------------------------------------------------
    const irr::video::SMaterial* CISL::getMaterial(const irr::core::stringc materialName)
    {
        irr::video::SMaterial* result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                             g e t C o l o r
    //-------------------------------------------------------------------------
    const irr::video::SColor* CISL::getColor(const irr::core::stringc colorName)
    {
        irr::video::SColor*  result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                            g e t F l o a t
    //-------------------------------------------------------------------------
    float CISL::getFloat(const irr::core::stringc varName)
    {
        float result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                              g e t I n t
    //-------------------------------------------------------------------------
    int CISL::getInt(const irr::core::stringc varName)
    {
        int result=0;
        return result;
    }

    //-------------------------------------------------------------------------
    //                            g e t S t r i n g
    //-------------------------------------------------------------------------
    const irr::core::stringc CISL::getString(const irr::core::stringc varName)
    {
        irr::core::stringc result="";

        return result;
    }

    //-------------------------------------------------------------------------
    //                             g e t L i s t
    //-------------------------------------------------------------------------
    const void* CISL::getList(const irr::core::stringc varName)
    {
        void* result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                         _ e x t r a c t D i r 
    //-------------------------------------------------------------------------
    irr::core::stringc CISL::_extractDir(irr::core::stringc filename)
    {
        irr::core::stringc result="";
        // find last forward or backslash
        irr::s32 lastSlash = filename.findLast('/');
        const irr::s32 lastBackSlash = filename.findLast('\\');
        lastSlash = lastSlash > lastBackSlash ? lastSlash : lastBackSlash;

        if ((irr::u32)lastSlash < filename.size())
            return filename.subString(0, lastSlash+1);
        else
            return ".";
    }

    //-------------------------------------------------------------------------
    //                            _ d u m p T r e e 
    //-------------------------------------------------------------------------
    void CISL::_dumpTree(pANTLR3_BASE_TREE tree)
    {
        pANTLR3_STRING  string;
        ANTLR3_UINT32   i;
        ANTLR3_UINT32   n;
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        static int level=-1;
        static irr::core::stringc tabs = "";


        token = tree->getToken(tree);
        if(token)
        {
            string = token->getText(token);
            tabs = "";
            for(int i=0;i < level; i++)
                tabs += "\t";

            switch(token->type)
            {
            case ASSIGN:
                printf("%sASSIGN (%s)\n", tabs.c_str(), string->chars );
                break;
            case NAME:
                printf("%sNAME (%s)\n", tabs.c_str(), string->chars);
                break;
            case ADD:
                printf("%sADD (%s)\n", tabs.c_str(), string->chars);
                break;
            case SUB:
                printf("%sSUB (%s)\n", tabs.c_str(), string->chars);
                break;
            case MUL:
                printf("%sMUL (%s)\n", tabs.c_str(), string->chars);
                break;
            case DIV:
                printf("%sDIV (%s)\n", tabs.c_str(), string->chars);
                break;
            case INTEGER:
                printf("%sINTEGER (%s)\n", tabs.c_str(), string->chars);
                break;
            case FLOAT:
                printf("%sFLOAT (%s)\n", tabs.c_str(), string->chars);
                break;
                
            case HEX:
                printf("%sHEX (%s)\n", tabs.c_str(), string->chars);
                break;
             
            case BOOLLITERAL:
                printf("%sBOOL (%s)\n", tabs.c_str(), string->chars);
                break;
                
            case STRING:
                printf("%sSTRING (%s)\n", tabs.c_str(), string->chars);
                break;
            case LIST:
                printf("%sLIST (%s)\n", tabs.c_str(), string->chars);
                break;
            case MATDEF:
                printf("%sMATDEF (%s)\n", tabs.c_str(), string->chars);
                break;
            case CNFDEF:
                printf("%sCNFDEF (%s)\n", tabs.c_str(), string->chars);
                break;
            case INHERIT:
                printf("%sINHERIT (%s)\n", tabs.c_str(), string->chars);
                break;
            case DOT:
                printf("%sDOT (%s)\n", tabs.c_str(), string->chars);
                break;
            case STARTDEF:
                ++level;
                break;
            case ENDDEF:
                --level;
                break;
            default:
                printf("%sUNKNOWN TOKEN: %d (%s)\n", tabs.c_str(), token->type, string->chars);
            };
        }

        if	(tree->children == NULL || tree->children->size(tree->children) == 0)
        {
            return;
        }

        /* Need a new string with nothing at all in it.
        */
        if	(tree->children != NULL)
        {
            n = tree->children->size(tree->children);

            for	(i = 0; i < n; i++)
            {   
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);

                ++level;
                _dumpTree(t);
                --level;
            }
        }
        return;
    }

    //-------------------------------------------------------------------------
    //                         _ d u m p O b j e c t s
    //-------------------------------------------------------------------------
    void CISL::_dumpObjects()
    {
        printf("Object Counts:\n");
        printf("\nMaterials: %d\n", m_matDefs.size());
        for ( SYMMAP::Iterator itr = m_matDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            printf("    ID: %s, child count: %d\n", symbol->getScopedID().c_str(), symbol->getChildren().size());
        }

        printf("\nConfigs: %d\n", m_cnfDefs.size());
        for ( SYMMAP::Iterator itr = m_cnfDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            printf("    ID: %s, child count: %d\n", symbol->getScopedID().c_str(), symbol->getChildren().size());
        }
    }

    //-------------------------------------------------------------------------
    //                         _ s t a r t D E F S y m 
    //-------------------------------------------------------------------------
    int CISL::_startDEFSym(pANTLR3_BASE_TREE tree, SymbolType type)
    {
        pANTLR3_STRING  string,parent;
        pANTLR3_BASE_TREE   t, t2;
        pANTLR3_COMMON_TOKEN token;

        //
        // ignore unnamed definition which will be evaluated later.
        //
        if(!tree->children)
            return 0;

        t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, 0);
        token = t->getToken(t);
        if(token->type == NAME)
        {
            string = token->getText(token);
            m_st->addSymbol(string->chars, type);
            m_st->pushSpace(string->chars);
        }
        else if(token->type == INHERIT)
        {
            if(t->children->count != 2)
            {
                return E_BAD_SYNTAX;
            }
            t2 = (pANTLR3_BASE_TREE) t->children->get(t->children, 0);
            token = t->getToken(t2);
            if(token->type != NAME)
                return E_BAD_SYNTAX;
            string = token->getText(token);

            t2 = (pANTLR3_BASE_TREE) t->children->get(t->children, 1);
            token = t->getToken(t2);
            if(token->type != NAME)
                return E_BAD_SYNTAX;
            parent = token->getText(token);

            m_st->addSymbol(string->chars, type, parent->chars);
            m_st->pushSpace(string->chars);
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                        _ g e t D o t t e d N a m e    
    //-------------------------------------------------------------------------
    irr::core::stringc CISL::_getDottedName(pANTLR3_BASE_TREE tree, irr::u32 startidx,
        irr::u32 endidx)
    {
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        irr::core::stringc result="";

        if(!tree->children)
            return "";

        if(endidx == 0)
            endidx = tree->children->count;
        for(irr::u32 i=startidx;i<endidx;i++)
        {
            t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);
            token = t->getToken(t);
            if(token->type == ASSIGN)
                break;
            if(token->type == INHERIT)
            {
                return _getDottedName(t, 0, t->children->count-1);
            }
            if(i>startidx)
                result += ".";
            result += token->getText(token)->chars;
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                        _ g e t D o t t e d N a m e    
    //-------------------------------------------------------------------------
    irr::core::stringc CISL::_getScope(pANTLR3_BASE_TREE tree, irr::u32 startidx,
        irr::u32 endidx)
    {
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        irr::core::stringc result="";

        if(!tree->children)
            return "";

        if(endidx == 0)
            endidx = tree->children->count;
        for(irr::u32 i=startidx;i<endidx;i++)
        {
            t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);
            token = t->getToken(t);
            if(token->type == ASSIGN)
                break;
            if(token->type == INHERIT)
            {
                return _getDottedName(t, 0, t->children->count-1);
            }
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                              b u i l d S T
    //-------------------------------------------------------------------------
    int CISL::_buildST(pANTLR3_BASE_TREE tree)
    {
        int result = 0;

        pANTLR3_STRING  string;
        ANTLR3_UINT32   i;
        ANTLR3_UINT32   n;
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        static int level=-1;
        static irr::core::stringc tabs = "";

        token = tree->getToken(tree);
        if(token)
        {
            string = token->getText(token);

            switch(token->type)
            {
            case ASSIGN:
                if(!tree->children)
                    return 0;
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, 0);
                token = t->getToken(t);
                if(token->type == NAME)
                {
                    irr::core::stringc dname = _getDottedName(tree);
                        
                    m_st->addSymbol(dname);
                }
                else printf("Add Symbol ASSIGN - unknown token type\n");
                break;
            case INHERIT:
                i = 0;
                break;
            case MATDEF:
                _startDEFSym(tree, stMaterial);
                break;
            case CNFDEF:
                _startDEFSym(tree, stConfig);
                break;
            case ENDDEF:
                m_st->popSpace();
                break;
            };
        }

        if	(tree->children == NULL || tree->children->size(tree->children) == 0)
        {
            return 0;
        }

        if	(tree->children != NULL)
        {
            n = tree->children->size(tree->children);

            for	(i = 0; i < n; i++)
            {   
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);

                ++level;
                _buildST(t);
                --level;
            }
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                       _ e x t r a c t S t r i n g
    //-------------------------------------------------------------------------
    irr::core::stringc CISL::_extractString(char *str)
    {
        irr::core::stringc temp = str;
        if(temp.size() == 2)
            return "";

        return temp.subString(1, temp.size()-2);
    }

    //-------------------------------------------------------------------------
    //                            _ g e t S p a c e I D
    //-------------------------------------------------------------------------
    irr::core::stringc CISL::_getSpaceID(irr::core::stringc id)
    {
        irr::core::stringc result="";
        for(irr::u32 i=0; i<m_nameSpace.size(); i++)
        {
            result += (m_nameSpace[i] + ".");
        }
        result += id;
        return result;
    }

    //-------------------------------------------------------------------------
    //                            _ p u s h S p a c e
    //-------------------------------------------------------------------------
    irr::core::stringc CISL::_pushSpace(irr::core::stringc name)
    {
        irr::core::stringc result="";

        m_nameSpace.push_back(name);
        for(irr::u32 i=0; i<m_nameSpace.size(); i++)
        {
            result += (m_nameSpace[i] + ".");
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                             _ p o p S p a c e
    //-------------------------------------------------------------------------
    irr::core::stringc CISL::_popSpace()
    {
        irr::core::stringc result="";
        irr::u32 idx = m_nameSpace.size();
        if(!idx)
            return result;

        m_nameSpace.erase(idx-1);
        for(irr::u32 i=0; i<m_nameSpace.size(); i++)
        {
            result += (m_nameSpace[i] + ".");
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                             _ g e t O p 
    //-------------------------------------------------------------------------
    int CISL::_getOp(pANTLR3_BASE_TREE tree, irr::u32 idx, struct EvalResult* pr)
    {
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        EvalResult op1,op2;
        EvalResult* cvalue;

        t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, idx);
        token = t->getToken(t);
        switch(token->type)
        {
        case NAME:
            cvalue = m_st->getValue((char *) token->getText(token)->chars);
            if(cvalue)
            {
                if((pr->rType == stUndefined) || (cvalue->rType == pr->rType))
                {
                    pr->rType = cvalue->rType;
                    switch(pr->rType)
                    {
                    case stInt:
                        pr->rInteger = cvalue->rInteger; 
                        break;
                    case stFloat:
                        pr->rFloat = cvalue->rFloat; 
                        break;
                    };
                }
                else
                {
                    // type mis-match...
                }
            }
            else
            {
                // undefined symbol...
            }
            break;
        case INTEGER:
            pr->rType = stInt;
            pr->rInteger = atoi((char *)token->getText(token)->chars);
            break;
        case FLOAT:
            pr->rType = stFloat;
            pr->rFloat = (float)atof((char *)token->getText(token)->chars);
            break;
        case MUL:
        case DIV:
        case SUB:
        case ADD:
            _getOp(t, 0, &op1);
            _getOp(t, 1, &op2);
            _doMath(pr, token->type, &op1, &op2);
            break;
        };

        return 0;
    }

    //-------------------------------------------------------------------------
    //                              _ d o M a t h
    //-------------------------------------------------------------------------
    int CISL::_doMath(struct EvalResult* result, ANTLR3_UINT32 op, struct EvalResult* op1, struct EvalResult* op2)
    {
        if(op1->rType == stInt || op1->rType == stFloat)
        {
            irr::f32 o1=op1->rFloat;
            irr::f32 o2=op2->rFloat;
            irr::f32 res;

            // convert both operands to float
            if(op1->rType == stInt)
                o1 = (irr::f32) op1->rInteger;
            if(op2->rType == stInt)
                o2 = (irr::f32) op2->rInteger;

            // math
            switch(op)
            {
            case ADD:
                res = o1 + o2;
                break;
            case SUB:
                res = o1 - o2;
                break;
            case MUL:
                res = o1 * o2;
                break;
            case DIV:
                res = o1 / o2;
                break;
            };

            // set return type & value
            if(op1->rType == stInt && op2->rType == stInt)
            {
                result->rType = stInt;
                result->rInteger = (int) res;
            }
            else
            {
                result->rType = stFloat;
                result->rFloat = res;
            }
        }
        else if(op1->rType == stString)
        {
            if(op == ADD)
            {
            }
            else
            {
                // invalid string operation.
            }
        }
        else
        {
            // type mis-match - can't perform math on object definitions.
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                                _ e v a l
    //-------------------------------------------------------------------------
    int CISL::_eval(pANTLR3_BASE_TREE tree, pANTLR3_BASE_TREE parent, int cidx, struct EvalResult* pr)
    {
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        EvalResult op1,op2;
        EvalResult* cvalue;
        irr::core::stringc cname="";

        pr->rType = stUndefined;
        pr->rInteger = 0;
        pr->rFloat = 0;
        pr->rBool = "";

        token = tree->getToken(tree);

        switch(token->type)
        {
        case NAME:
            if(cidx == parent->getChildCount(parent)-1)
                cname = (char *) token->getText(token)->chars;
            else cname = _getDottedName(parent, cidx);
            cvalue = m_st->getValue(cname.c_str());
            if(cvalue)
            {
                if((pr->rType == stUndefined) || (cvalue->rType == pr->rType))
                {
                    pr->rType = cvalue->rType;
                    switch(pr->rType)
                    {
                    case stInt:
                        pr->rInteger = cvalue->rInteger; 
                        break;
                    case stFloat:
                        pr->rFloat = cvalue->rFloat; 
                        break;
                    };
                }
                else
                {
                    // type mis-match...
                }
            }
            else
            {
                // undefined symbol...
            }
            break;
        case STRING:
            pr->rType = stString;
            pr->rString = _extractString((char *)token->getText(token)->chars);
            break;
        case INTEGER:
            pr->rType = stInt;
            pr->rInteger = atol((char *)token->getText(token)->chars);
            break;
        case FLOAT:
            pr->rType = stFloat;
            pr->rFloat = (irr::f32) atof((char *)token->getText(token)->chars);
            break;            
        case HEX:
            pr->rType = stInt;
            pr->rInteger = strtol((char *)token->getText(token)->chars + 2, NULL, 16);
            break;            
        case BOOLLITERAL:
            pr->rType = stBool;
            pr->rBool = strcmp((char *)token->getText(token)->chars,"true") ? false : true;
            break;
        case LIST:
            pr->rType = stList;
            for(irr::u32 i=0;i<tree->getChildCount(tree);i++)
            {
                EvalResult* cer = new EvalResult();
                pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild(tree,i);
                _eval(child, tree, 0, cer);
                pr->rListItems.push_back(cer);

            }
            break;
        case MUL:
        case DIV:
        case SUB:
        case ADD:
            _getOp(tree, 0, &op1);
            _getOp(tree, 1, &op2);
            _doMath(pr, token->type, &op1, &op2);
            break;
        };

        return 0;
    }

    //-------------------------------------------------------------------------
    //                            _ i n t e r p r e t
    //-------------------------------------------------------------------------
    int CISL::_interpret(pANTLR3_BASE_TREE tree)
    {
        int result = 0;

        pANTLR3_STRING  string;
        ANTLR3_UINT32   i;
        ANTLR3_UINT32   n;
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        static int level=-1;
        static irr::core::stringc tabs = "";
        irr::core::stringc id;
        struct EvalResult er;


        token = tree->getToken(tree);
        if(token)
        {
            string = token->getText(token);

            switch(token->type)
            {
            case ASSIGN:
                if(!tree->children)
                    return 0;

                id = _getSpaceID(_getDottedName(tree));

                irr::u32 i;
                for(i=0;i<tree->children->count-1;i++)
                {
                    t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);
                    token = t->getToken(t);
                    if(token->type == ASSIGN)
                        break;
                }
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, ++i);
                _eval(t, tree, i, &er);
                m_st->setValue(id, &er);

                break;
            case STARTDEF:
                result = 0;
                break;
            case ENDDEF:
                result = 0;
                _popSpace();
                break;
            case MATDEF:
                id = _getSpaceID(_getDottedName(tree));
                er.rType = stMaterial;
                m_st->setValue(id, &er);                
                _pushSpace(id);
                break;
            case CNFDEF:
                id = _getSpaceID(_getDottedName(tree));
                er.rType = stConfig;
                m_st->setValue(id, &er);                
                _pushSpace(id);
                break;
            };
        }

        if	(tree->children == NULL || tree->children->size(tree->children) == 0)
        {
            return 0;
        }

        if	(tree->children != NULL)
        {
            n = tree->children->size(tree->children);

            for	(i = 0; i < n; i++)
            {   
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);

                ++level;
                _interpret(t);
                --level;
            }
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                        _ g e t V a l u e R e s u l t
    //-------------------------------------------------------------------------
    EvalResult* CISL::_getValueResult(CSymbol* sym, irr::core::stringc val)
    {

        SYMMAP&  vars = sym->getChildren();

        for(SYMMAP::Iterator citr = vars.getIterator(); !citr.atEnd(); citr++)
        {
            CSymbol* child = citr->getValue();
            if(val.equals_ignore_case(child->getID()))
                return child->getValue();
        }
        //
        // inheritence?
        //
        irr::core::stringc iparent = sym->getIParent();
        if(iparent.size())
        {
            return _getValueResult(m_st->getSymbol(iparent), val);
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t I n t V a l u e
    //-------------------------------------------------------------------------
    int CISL::_getIntValue(EvalResult* er, int defval)
    {
        int result=defval;

        switch(er->rType)
        {
        case stBool: 
            result = er->rBool;
            break;
        case stInt:
            result = er->rInteger;
            break;
        case stFloat:
            result = (int) er->rFloat;
            break;
        case stString:
            result = atoi(er->rString.c_str());
            break;
        case stList:
            // pull first item...
            break;
        };

        return result;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t F l o a t V a l u e
    //-------------------------------------------------------------------------
    irr::f32 CISL::_getFloatValue(EvalResult* er, irr::f32 defval)
    {
        irr::f32 result=defval;

        switch(er->rType)
        {
        case stBool: 
            result = er->rBool;
            break;
        case stInt:
            result = (irr::f32) er->rInteger;
            break;
        case stFloat:
            result = er->rFloat;
            break;
        case stString:
            result = (irr::f32) atof(er->rString.c_str());
            break;
        case stList:
            // pull first item...
            break;
        };

        return result;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t B o o l V a l u e
    //-------------------------------------------------------------------------
    bool CISL::_getBoolValue(EvalResult* er, bool defval)
    {
        bool result=defval;

        switch(er->rType)
        {
        case stBool: 
            result = er->rBool;
            break;
        case stInt:
            result = er->rInteger ? true : false;
            break;
        case stFloat:
            result = er->rFloat ? true : false;
            break;
        case stString:
            result = atoi(er->rString.c_str()) ? true : false;
            break;
        case stList:
            // pull first item...
            break;
        };

        return result;
    }


    //-------------------------------------------------------------------------
    //                         _ g e t C o l o r V a l u e
    //-------------------------------------------------------------------------
    const irr::video::SColor& CISL::_getColorValue(EvalResult* er)
    {
        static irr::video::SColor result;

        // default black full alpha
        result.set(255,0,0,0);

        switch(er->rType)
        {
        case stInt:
            result.setRed((er->rInteger & 0xFF000000) >> 24);
            result.setGreen((er->rInteger & 0x00FF0000) >> 16);
            result.setBlue((er->rInteger & 0x0000FF00) >> 8);
            result.setAlpha(er->rInteger & 0x000000FF);
            break;
        case stList:

            break;
        }




        return result;
    }

    //-------------------------------------------------------------------------
    //                      _ c r e a t e M a t e r i a l s
    //-------------------------------------------------------------------------
    int CISL::_createMaterials()
    {
        irr::video::SMaterial* pmat;
        irr::core::stringc cid;
        int idx;
        bool found;

        // print invalid var warnings
        for ( SYMMAP::Iterator itr = m_matDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            SYMMAP&  vars = symbol->getChildren();

            for(SYMMAP::Iterator citr = vars.getIterator(); !citr.atEnd(); citr++)
            {
                CSymbol* csymbol = citr->getValue();
                cid = csymbol->getID();
                found = false;
                idx = 0;
                while(MATVARS[idx])
                {
                    if(cid.equals_ignore_case(MATVARS[idx]))
                    {
                        found = true;
                        break;
                    }
                    ++idx;
                }
                if(!found)
                {
                    printf("Warning - Ignoring Invalid Material Variable: %s.%s\n", csymbol->getScope().c_str(),
                        cid.c_str());
                }
            }
        }

        // create materials
        for ( SYMMAP::Iterator itr = m_matDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            pmat = new irr::video::SMaterial();

            EvalResult* er = _getValueResult(symbol, "type");
            if(er)
                pmat->MaterialType = (irr::video::E_MATERIAL_TYPE) _getIntValue(er, 0);

            er = _getValueResult(symbol, "ambient");
            if(er)
                pmat->AmbientColor = _getColorValue(er);

            er = _getValueResult(symbol, "diffuse");
            if(er)
                pmat->DiffuseColor = _getColorValue(er);

            er = _getValueResult(symbol, "emissive");
            if(er)
                pmat->EmissiveColor = _getColorValue(er);

            er = _getValueResult(symbol, "specular");
            if(er)
                pmat->SpecularColor = _getColorValue(er);

            er = _getValueResult(symbol, "shininess");
            if(er)
                pmat->Shininess = _getFloatValue(er, 20.0);

            er = _getValueResult(symbol, "parm1");
            if(er)
                pmat->MaterialTypeParam = _getFloatValue(er, 0.0);

            er = _getValueResult(symbol, "parm2");
            if(er)
                pmat->MaterialTypeParam2 = _getFloatValue(er, 0.0);

            er = _getValueResult(symbol, "thickness");
            if(er)
                pmat->Thickness = _getFloatValue(er, 1.0);

            er = _getValueResult(symbol, "gouraud");
            if(er)
                pmat->Thickness = _getBoolValue(er, true);

            er = _getValueResult(symbol, "lighting");
            if(er)
                pmat->Lighting = _getBoolValue(er, true);

            er = _getValueResult(symbol, "zwriteenable");
            if(er)
                pmat->ZWriteEnable = _getBoolValue(er, true);

            er = _getValueResult(symbol, "backfaceculling");
            if(er)
                pmat->BackfaceCulling = _getBoolValue(er, true);

            er = _getValueResult(symbol, "frontfaceculling");
            if(er)
                pmat->FrontfaceCulling = _getBoolValue(er, false);

            er = _getValueResult(symbol, "fogenabled");
            if(er)
                pmat->FogEnable = _getBoolValue(er, false);

            er = _getValueResult(symbol, "normalizenormals");
            if(er)
                pmat->NormalizeNormals = _getBoolValue(er, false);

            er = _getValueResult(symbol, "zbuffer");
            if(er)
                pmat->ZBuffer = _getIntValue(er, 1);

            symbol->setUserData(pmat);
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                         v a l i d a t e S c r i p t
    //-------------------------------------------------------------------------
    CISLStatus CISL::validateScript(const irr::core::stringc fileName, 
        const CISLErrorHandler& errorHandler)
    {

        if(!fileExists(fileName))
        {
            ANTLR3_FPRINTF(stderr, "Script file doesn't exists.\n");
            return E_NO_FILE;
        }

        if(m_fileName)
        {
            _freeResources();
        }

        // Create the m_inputStream stream based upon the argument supplied to us on the command line
        // for this example, the m_inputStream will always default to ./m_inputStream if there is no explicit
        // argument.
        //
        m_fileName = (pANTLR3_UINT8)fileName.c_str();

        // Create the m_inputStream stream using the supplied file name
        // (Use antlr3AsciiFileStreamNew for UCS2/16bit m_inputStream).
        //
        m_inputStream  = antlr3AsciiFileStreamNew(m_fileName);

        // The m_inputStream will be created successfully, providing that there is enough
        // memory and the file exists etc
        //
        if ( m_inputStream == NULL )
        {
            ANTLR3_FPRINTF(stderr, "Unable to open file %s \n", (char *)m_fileName);
            return E_BAD_INPUT;
        }

        // Our m_inputStream stream is now open and all set to go, so we can create a new instance of our
        // lexer and set the lexer m_inputStream to our m_inputStream stream:
        //  (file | memory | ?) --> inputstream -> lexer --> tokenstream --> parser ( --> treeparser )?
        //
        m_lexer        = islLexerNew(m_inputStream);      // CLexerNew is generated by ANTLR

        // realloc to include our context data 
        m_lexer = (pislLexer) ANTLR3_REALLOC(m_lexer,sizeof(struct LexerContext));
        m_lexer->pLexer->ctx = m_lexer;
        // Need to check for errors
        //
        if ( m_lexer == NULL )
        {
            ANTLR3_FPRINTF(stderr, "Unable to create the lexer due to malloc() failure1\n");
            return E_OUT_OF_MEMORY;
        }

        ((struct LexerContext*)m_lexer)->pisl = this;

        // Our lexer is in place, so we can create the token stream from it
        // NB: Nothing happens yet other than the file has been read. We are just 
        // connecting all these things together and they will be invoked when we
        // call the parser rule. ANTLR3_SIZE_HINT can be left at the default usually
        // unless you have a very large token stream/m_inputStream. Each generated lexer
        // provides a token source interface, which is the second argument to the
        // token stream creator.
        // Note tha even if you implement your own token structure, it will always
        // contain a standard common token within it and this is the pointer that
        // you pass around to everything else. A common token as a pointer within
        // it that should point to your own outer token structure.
        //
        m_tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(m_lexer));


        if (m_tokenStream == NULL)
        {
            ANTLR3_FPRINTF(stderr, "Out of memory trying to allocate token stream\n");
            return E_OUT_OF_MEMORY;
        }

        // Finally, now that we have our lexer constructed, we can create the parser
        //
        m_parser        = islParserNew(m_tokenStream);  // CParserNew is generated by ANTLR3
        if (m_parser == NULL)
        {
            ANTLR3_FPRINTF(stderr, "Out of memory trying to allocate parser\n");
            return E_OUT_OF_MEMORY;
        }

        // install our own error display & debug functions
        m_parser->pParser->rec->displayRecognitionError = islRecognitionError;
        

        // We are all ready to go. Though that looked complicated at first glance,
        // I am sure, you will see that in fact most of the code above is dealing
        // with errors and there isn;t really that much to do (isn;t this always the
        // case in C? ;-).
        //
        // So, we now invoke the parser. All elements of ANTLR3 generated C components
        // as well as the ANTLR C runtime library itself are pseudo objects. This means
        // that they are represented as pointers to structures, which contain any
        // instance data they need, and a set of pointers to other interfaces or
        // 'methods'. Note that in general, these few pointers we have created here are
        // the only things you will ever explicitly free() as everything else is created
        // via factories, that allocate memory efficiently and free() everything they use
        // automatically when you close the parser/lexer/etc.
        //
        // Note that this means only that the methods are always called via the object
        // pointer and the first argument to any method, is a pointer to the structure itself.
        // It also has the side advantage, if you are using an IDE such as VS2005 that can do it
        // that when you type ->, you will see a list of all the methods the object supports.
        //
        m_islAST = m_parser->script(m_parser);

        // If the parser ran correctly, we will have a tree to parse. In general I recommend
        // keeping your own flags as part of the error trapping, but here is how you can
        // work out if there were errors if you are using the generic error messages
        //
        if(m_parser->pParser->rec->state->errorCount > 0)
        {
            ANTLR3_FPRINTF(stderr, "The parser returned %d errors, tree walking aborted.\n", m_parser->pParser->rec->state->errorCount);
            return E_BAD_SYNTAX;
        }
        else
        {
            m_treeNodes   = antlr3CommonTreeNodeStreamNewTree(m_islAST.tree, ANTLR3_SIZE_HINT); // sIZE HINT WILL SOON BE DEPRECATED!!
            m_treeNodes->reset(m_treeNodes);
        }

        return E_OK;
    }

    //-------------------------------------------------------------------------
    //                         p r o c e s s S c r i p t
    //-------------------------------------------------------------------------
    CISLStatus CISL::processScript(const irr::core::stringc fileName, const CISLErrorHandler& errorHandler)
    {
        CISLStatus result=E_OK;
        pANTLR3_COMMON_TOKEN token;

        appendIncludeDirs(_extractDir(fileName));

        result = validateScript(fileName, errorHandler);

        if(result != E_OK)
            return result;

        //
        // dump formatted AST
        //
        printf("\n-------\n\nAST Tree:\n");
        _dumpTree(m_islAST.tree);

        //
        // first pass - build symbol table for forward references
        //
        m_st = new CST();
        if(_buildST(m_islAST.tree) > 0)
        {
            ANTLR3_FPRINTF(stderr, "Symbol Table build error.\n");
            return E_BAD_SYNTAX;
        }
        printf("Pass (1) ");
        m_st->print();

        //
        // second pass - interpretation
        //
        if(_interpret(m_islAST.tree) > 0)
        {
            ANTLR3_FPRINTF(stderr, "Interpreter error.\n");
            return E_BAD_SYNTAX;
        }
        printf("Pass (2) ");
        m_st->print();

        //
        // now we're ready to generate our object (color, config, & material) definitions.
        //
        m_st->getDefinitions(stMaterial, m_matDefs);
        m_st->getDefinitions(stConfig, m_cnfDefs);
        _dumpObjects();

        _createMaterials();



        return E_OK;
    }
}