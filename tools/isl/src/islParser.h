/** \file
 *  This C header file was generated by $ANTLR version 3.1.1
 *
 *     -  From the grammar source file : C:\\gdev\\itubras\\tools\\isl\\grammar\\isl.g
 *     -                            On : 2008-10-14 15:32:11
 *     -                for the parser : islParserParser *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser islParser has the callable functions (rules) shown below,
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
 * a parser context typedef pislParser, which is returned from a call to islParserNew().
 *
 * The methods in pislParser are  as follows:
 *
 *  - islParser_script_return      pislParser->script(pislParser)
 *  - islParser_statements_return      pislParser->statements(pislParser)
 *  - islParser_classdef_return      pislParser->classdef(pislParser)
 *  - islParser_classType_return      pislParser->classType(pislParser)
 *  - islParser_classColor_return      pislParser->classColor(pislParser)
 *  - islParser_classMaterial_return      pislParser->classMaterial(pislParser)
 *  - islParser_classConfig_return      pislParser->classConfig(pislParser)
 *  - islParser_cstatements_return      pislParser->cstatements(pislParser)
 *  - islParser_assignment_return      pislParser->assignment(pislParser)
 *  - islParser_expr_or_def_return      pislParser->expr_or_def(pislParser)
 *  - islParser_addexpr_return      pislParser->addexpr(pislParser)
 *  - islParser_mulexpr_return      pislParser->mulexpr(pislParser)
 *  - islParser_atom_return      pislParser->atom(pislParser)
 *  - islParser_list_return      pislParser->list(pislParser)
 *  - islParser_id_return      pislParser->id(pislParser)
 *  - islParser_idinherit_return      pislParser->idinherit(pislParser)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
#ifndef	_islParser_H
#define _islParser_H
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
typedef struct islParser_Ctx_struct islParser, * pislParser;



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
typedef struct islParser_script_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_script_return;

typedef struct islParser_statements_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_statements_return;

typedef struct islParser_classdef_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_classdef_return;

typedef struct islParser_classType_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_classType_return;

typedef struct islParser_classColor_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_classColor_return;

typedef struct islParser_classMaterial_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_classMaterial_return;

typedef struct islParser_classConfig_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_classConfig_return;

typedef struct islParser_cstatements_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_cstatements_return;

typedef struct islParser_assignment_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_assignment_return;

typedef struct islParser_expr_or_def_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_expr_or_def_return;

typedef struct islParser_addexpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_addexpr_return;

typedef struct islParser_mulexpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_mulexpr_return;

typedef struct islParser_atom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_atom_return;

typedef struct islParser_list_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_list_return;

typedef struct islParser_id_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_id_return;

typedef struct islParser_idinherit_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    islParser_idinherit_return;




/** Context tracking structure for islParser
 */
struct islParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;


     islParser_script_return (*script)	(struct islParser_Ctx_struct * ctx);
     islParser_statements_return (*statements)	(struct islParser_Ctx_struct * ctx);
     islParser_classdef_return (*classdef)	(struct islParser_Ctx_struct * ctx);
     islParser_classType_return (*classType)	(struct islParser_Ctx_struct * ctx);
     islParser_classColor_return (*classColor)	(struct islParser_Ctx_struct * ctx);
     islParser_classMaterial_return (*classMaterial)	(struct islParser_Ctx_struct * ctx);
     islParser_classConfig_return (*classConfig)	(struct islParser_Ctx_struct * ctx);
     islParser_cstatements_return (*cstatements)	(struct islParser_Ctx_struct * ctx);
     islParser_assignment_return (*assignment)	(struct islParser_Ctx_struct * ctx);
     islParser_expr_or_def_return (*expr_or_def)	(struct islParser_Ctx_struct * ctx);
     islParser_addexpr_return (*addexpr)	(struct islParser_Ctx_struct * ctx);
     islParser_mulexpr_return (*mulexpr)	(struct islParser_Ctx_struct * ctx);
     islParser_atom_return (*atom)	(struct islParser_Ctx_struct * ctx);
     islParser_list_return (*list)	(struct islParser_Ctx_struct * ctx);
     islParser_id_return (*id)	(struct islParser_Ctx_struct * ctx);
     islParser_idinherit_return (*idinherit)	(struct islParser_Ctx_struct * ctx);
    // Delegated rules
    const char * (*getGrammarFileName)();
    void	    (*free)   (struct islParser_Ctx_struct * ctx);
    /* @headerFile.members() */
    pANTLR3_BASE_TREE_ADAPTOR	adaptor;
    pANTLR3_VECTOR_FACTORY		vectors;
    /* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pislParser islParserNew         (pANTLR3_COMMON_TOKEN_STREAM instream);
ANTLR3_API pislParser islParserNewSSD      (pANTLR3_COMMON_TOKEN_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the parser will work with.
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
#define INTEGER      18
#define MATDEF      15
#define LINE_COMMENT      35
#define ENDDEF      13
#define INHERIT      7
#define STARTDEF      12
#define BOOLLITERAL      22
#define SUB      9
#define FLOAT      17
#define NSTRING      20
#define LIST      6
#define EOF      -1
#define HexDigit      32
#define MUL      10
#define LPAREN      23
#define COLON      28
#define RPAREN      25
#define NAME      26
#define WS      33
#define COLDEF      14
#define T__36      36
#define OBJECT      4
#define CNFDEF      16
#define COMMA      24
#define HEX      19
#define UnicodeEscape      30
#define ASSIGN      5
#define DIV      11
#define COMMENT      34
#define DOT      27
#define OctalEscape      31
#define EscapeSequence      29
#define STRING      21
#define ADD      8
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for islParser
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
