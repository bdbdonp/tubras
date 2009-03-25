/** \file
 *  This C header file was generated by $ANTLR version 3.1.1
 *
 *     -  From the grammar source file : C:\\gdev\\itubras\\tools\\isl\\grammar\\isl.g
 *     -                            On : 2008-11-03 14:26:32
 *     -                 for the lexer : islLexerLexer *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer islLexer has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 * 
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pislLexer, which is returned from a call to islLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 * * The methods in pislLexer are  as follows:
 *
 *  -  void      pislLexer->CNFDEF(pislLexer)
 *  -  void      pislLexer->MATDEF(pislLexer)
 *  -  void      pislLexer->LAYDEF(pislLexer)
 *  -  void      pislLexer->MTXDEF(pislLexer)
 *  -  void      pislLexer->GELDEF(pislLexer)
 *  -  void      pislLexer->PRTDEF(pislLexer)
 *  -  void      pislLexer->BOOLLITERAL(pislLexer)
 *  -  void      pislLexer->STRING(pislLexer)
 *  -  void      pislLexer->NAME(pislLexer)
 *  -  void      pislLexer->INTEGER(pislLexer)
 *  -  void      pislLexer->FLOAT(pislLexer)
 *  -  void      pislLexer->HEX(pislLexer)
 *  -  void      pislLexer->ASSIGN(pislLexer)
 *  -  void      pislLexer->ADD(pislLexer)
 *  -  void      pislLexer->SUB(pislLexer)
 *  -  void      pislLexer->MUL(pislLexer)
 *  -  void      pislLexer->DIV(pislLexer)
 *  -  void      pislLexer->DOT(pislLexer)
 *  -  void      pislLexer->COLON(pislLexer)
 *  -  void      pislLexer->SCOLON(pislLexer)
 *  -  void      pislLexer->COMMA(pislLexer)
 *  -  void      pislLexer->LPAREN(pislLexer)
 *  -  void      pislLexer->RPAREN(pislLexer)
 *  -  void      pislLexer->SDEF(pislLexer)
 *  -  void      pislLexer->EDEF(pislLexer)
 *  -  void      pislLexer->EscapeSequence(pislLexer)
 *  -  void      pislLexer->OctalEscape(pislLexer)
 *  -  void      pislLexer->UnicodeEscape(pislLexer)
 *  -  void      pislLexer->HexDigit(pislLexer)
 *  -  void      pislLexer->WS(pislLexer)
 *  -  void      pislLexer->COMMENT(pislLexer)
 *  -  void      pislLexer->LINE_COMMENT(pislLexer)
 *  -  void      pislLexer->LINE_COMMAND(pislLexer)
 *  -  void      pislLexer->Tokens(pislLexer)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
#ifndef	_islLexer_H
#define _islLexer_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */
 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct islLexer_Ctx_struct islLexer, * pislLexer;




void* doInclude(void* plexer, char *filename);


#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule 
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#endif


/** Context tracking structure for islLexer
 */
struct islLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;


     void (*mCNFDEF)	(struct islLexer_Ctx_struct * ctx);
     void (*mMATDEF)	(struct islLexer_Ctx_struct * ctx);
     void (*mLAYDEF)	(struct islLexer_Ctx_struct * ctx);
     void (*mMTXDEF)	(struct islLexer_Ctx_struct * ctx);
     void (*mGELDEF)	(struct islLexer_Ctx_struct * ctx);
     void (*mPRTDEF)	(struct islLexer_Ctx_struct * ctx);
     void (*mBOOLLITERAL)	(struct islLexer_Ctx_struct * ctx);
     void (*mSTRING)	(struct islLexer_Ctx_struct * ctx);
     void (*mNAME)	(struct islLexer_Ctx_struct * ctx);
     void (*mINTEGER)	(struct islLexer_Ctx_struct * ctx);
     void (*mFLOAT)	(struct islLexer_Ctx_struct * ctx);
     void (*mHEX)	(struct islLexer_Ctx_struct * ctx);
     void (*mASSIGN)	(struct islLexer_Ctx_struct * ctx);
     void (*mADD)	(struct islLexer_Ctx_struct * ctx);
     void (*mSUB)	(struct islLexer_Ctx_struct * ctx);
     void (*mMUL)	(struct islLexer_Ctx_struct * ctx);
     void (*mDIV)	(struct islLexer_Ctx_struct * ctx);
     void (*mDOT)	(struct islLexer_Ctx_struct * ctx);
     void (*mCOLON)	(struct islLexer_Ctx_struct * ctx);
     void (*mSCOLON)	(struct islLexer_Ctx_struct * ctx);
     void (*mCOMMA)	(struct islLexer_Ctx_struct * ctx);
     void (*mLPAREN)	(struct islLexer_Ctx_struct * ctx);
     void (*mRPAREN)	(struct islLexer_Ctx_struct * ctx);
     void (*mSDEF)	(struct islLexer_Ctx_struct * ctx);
     void (*mEDEF)	(struct islLexer_Ctx_struct * ctx);
     void (*mEscapeSequence)	(struct islLexer_Ctx_struct * ctx);
     void (*mOctalEscape)	(struct islLexer_Ctx_struct * ctx);
     void (*mUnicodeEscape)	(struct islLexer_Ctx_struct * ctx);
     void (*mHexDigit)	(struct islLexer_Ctx_struct * ctx);
     void (*mWS)	(struct islLexer_Ctx_struct * ctx);
     void (*mCOMMENT)	(struct islLexer_Ctx_struct * ctx);
     void (*mLINE_COMMENT)	(struct islLexer_Ctx_struct * ctx);
     void (*mLINE_COMMAND)	(struct islLexer_Ctx_struct * ctx);
     void (*mTokens)	(struct islLexer_Ctx_struct * ctx);    const char * (*getGrammarFileName)();
    void	    (*free)   (struct islLexer_Ctx_struct * ctx);
        
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pislLexer islLexerNew         (pANTLR3_INPUT_STREAM instream);
ANTLR3_API pislLexer islLexerNewSSD      (pANTLR3_INPUT_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the lexer will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif 
#define INTEGER      22
#define UNARYOP      7
#define MATDEF      10
#define LAYDEF      12
#define LINE_COMMENT      38
#define INHERIT      6
#define SDEF      8
#define PRTDEF      15
#define BOOLLITERAL      25
#define SUB      18
#define FLOAT      21
#define EOF      -1
#define HexDigit      35
#define MUL      19
#define LPAREN      26
#define COLON      31
#define TUPLE      5
#define RPAREN      28
#define NAME      29
#define WS      36
#define CNFDEF      11
#define HEX      23
#define COMMA      27
#define UnicodeEscape      33
#define LINE_COMMAND      39
#define ASSIGN      4
#define EDEF      9
#define DIV      20
#define DOT      30
#define COMMENT      37
#define GELDEF      14
#define EscapeSequence      32
#define OctalEscape      34
#define STRING      24
#define ADD      17
#define SCOLON      16
#define MTXDEF      13
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for islLexer
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */