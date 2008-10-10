/** \file
 *  This C header file was generated by $ANTLR version 3.1.1
 *
 *     -  From the grammar source file : C:\\gdev\\itubras\\tools\\isl\\grammar\\islWalker.g
 *     -                            On : 2008-10-10 16:50:09
 *     -           for the tree parser : islWalkerTreeParser *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The tree parser islWalker has the callable functions (rules) shown below,
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
 * a parser context typedef pislWalker, which is returned from a call to islWalkerNew().
 *
 * The methods in pislWalker are  as follows:
 *
 *  - void      pislWalker->script(pislWalker)
 *  - void      pislWalker->statements(pislWalker)
 *  - void      pislWalker->classdef(pislWalker)
 *  - void      pislWalker->classType(pislWalker)
 *  - void      pislWalker->classColor(pislWalker)
 *  - void      pislWalker->classMaterial(pislWalker)
 *  - void      pislWalker->classConfig(pislWalker)
 *  - void      pislWalker->cstatements(pislWalker)
 *  - void      pislWalker->assignment(pislWalker)
 *  - void      pislWalker->expr_or_def(pislWalker)
 *  - void      pislWalker->expr(pislWalker)
 *  - void      pislWalker->addsubexpr(pislWalker)
 *  - void      pislWalker->muldivexpr(pislWalker)
 *  - void      pislWalker->atom(pislWalker)
 *  - void      pislWalker->list_or_expr(pislWalker)
 *  - void      pislWalker->id(pislWalker)
 *  - void      pislWalker->idinherit(pislWalker)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
#ifndef	_islWalker_H
#define _islWalker_H
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
typedef struct islWalker_Ctx_struct islWalker, * pislWalker;



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


/** Context tracking structure for islWalker
 */
struct islWalker_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_TREE_PARSER	    pTreeParser;


     void (*script)	(struct islWalker_Ctx_struct * ctx);
     void (*statements)	(struct islWalker_Ctx_struct * ctx);
     void (*classdef)	(struct islWalker_Ctx_struct * ctx);
     void (*classType)	(struct islWalker_Ctx_struct * ctx);
     void (*classColor)	(struct islWalker_Ctx_struct * ctx);
     void (*classMaterial)	(struct islWalker_Ctx_struct * ctx);
     void (*classConfig)	(struct islWalker_Ctx_struct * ctx);
     void (*cstatements)	(struct islWalker_Ctx_struct * ctx);
     void (*assignment)	(struct islWalker_Ctx_struct * ctx);
     void (*expr_or_def)	(struct islWalker_Ctx_struct * ctx);
     void (*expr)	(struct islWalker_Ctx_struct * ctx);
     void (*addsubexpr)	(struct islWalker_Ctx_struct * ctx);
     void (*muldivexpr)	(struct islWalker_Ctx_struct * ctx);
     void (*atom)	(struct islWalker_Ctx_struct * ctx);
     void (*list_or_expr)	(struct islWalker_Ctx_struct * ctx);
     void (*id)	(struct islWalker_Ctx_struct * ctx);
     void (*idinherit)	(struct islWalker_Ctx_struct * ctx);
    // Delegated rules
    const char * (*getGrammarFileName)();
    void	    (*free)   (struct islWalker_Ctx_struct * ctx);
        
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pislWalker islWalkerNew         (pANTLR3_COMMON_TREE_NODE_STREAM instream);
ANTLR3_API pislWalker islWalkerNewSSD      (pANTLR3_COMMON_TREE_NODE_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the tree parser will work with.
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
#define INTEGER      7
#define T__28      28
#define T__27      27
#define T__26      26
#define T__25      25
#define T__24      24
#define T__23      23
#define T__22      22
#define T__21      21
#define T__20      20
#define MCMT      15
#define FLOAT      6
#define EOF      -1
#define LPAREN      9
#define COLON      14
#define T__19      19
#define RPAREN      10
#define NAME      12
#define WS      17
#define T__18      18
#define OBJECT      4
#define COMMA      11
#define ASSIGN      5
#define DOT      13
#define SCMT      16
#define STRING      8
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for islWalker
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
