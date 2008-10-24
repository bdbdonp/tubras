#ifndef _CST_H_
#define _CST_H_

namespace CISL {
    enum SymbolType {stUndefined, stFloat, stInt, stString, stBool, stTuple, stObjectStart,
    stMaterial, stConfig, stMatrix, stLayer};

    class CSymbol;
    struct EvalResult;

    typedef irr::core::map<irr::core::stringc, CSymbol*> SYMMAP;
    typedef irr::core::array<irr::core::stringc> STACK;
    typedef irr::core::array<EvalResult*> TUPLEITEMS;

    struct EvalResult 
    {
        SymbolType  rType;
        long        rInteger;
        irr::f32    rFloat;
        bool        rBool;
        irr::core::stringc rString;
        TUPLEITEMS   rTupleItems;

        EvalResult()
        {
            rType = stUndefined;
            rInteger = 0;
            rFloat = .0;
            rBool = false;
            rString = "";
        }

        EvalResult(EvalResult* other)
        {
            rType = other->rType;
            rInteger = other->rInteger;
            rFloat = other->rFloat;
            rBool = other->rBool;
            rString = other->rString;
            rTupleItems = other->rTupleItems;
        }
    };

    class CSymbol {
    private:
        irr::core::stringc  m_file;
        irr::u32            m_line;
        irr::u32            m_pos;
        irr::core::stringc  m_scope;
        irr::core::stringc  m_scopedID;
        irr::core::stringc  m_id;
        irr::core::stringc  m_iParent;
        EvalResult          m_value;
        SYMMAP              m_children;
        void*               m_userData;

    public:
        CSymbol(irr::core::stringc scope, irr::core::stringc id, SymbolType type=stUndefined, 
            irr::core::stringc iParent="", irr::core::stringc file="", irr::u32 line=0, irr::u32 pos=0);

        irr::core::stringc getScopedID() {return m_scopedID;}
        irr::core::stringc getID() {return m_id;}
        irr::core::stringc getScope() {return m_scope;}
        irr::core::stringc getIParent() {return m_iParent;}
        void setIParent(irr::core::stringc value) {m_iParent = value;}
        SYMMAP& getChildren() {return m_children;}
        irr::u32 getChildCount() {return m_children.size();}
        void addChild(CSymbol* value) {m_children[value->getScopedID()] = value;}
        SymbolType getType() {return m_value.rType;}
        void* getUserData() {return m_userData;}
        void setUserData(void* value) {m_userData = value;}
        EvalResult* getValue() {return &m_value;}
        void setValue(EvalResult* value)
        {
            m_value = value;
        }

    };

    class CST
    {
    private:
        SYMMAP              m_symbols;
        STACK               m_nameSpace;

    protected:
        irr::core::stringc _getScope();
        int _gatherChildren(CSymbol* parent);

    public:
        CST();
        virtual ~CST();
        int reset() {};
        void print();
        int addSymbol(irr::core::stringc id, SymbolType type=stUndefined, irr::core::stringc iparent="",
            irr::core::stringc file="", irr::u32 line=0, irr::u32 pos=0);
        int setValue(irr::core::stringc id, EvalResult* pr);        
        int setIParent(irr::core::stringc id, irr::core::stringc iparent);        
        EvalResult* getValue(irr::core::stringc id);
        CSymbol* getSymbol(irr::core::stringc scopedID);
        bool idExists(irr::core::stringc id);
        irr::core::stringc pushSpace(irr::core::stringc id);
        irr::core::stringc popSpace();       
        int getDefinitions(SymbolType type, SYMMAP& out);
    };
}

#endif