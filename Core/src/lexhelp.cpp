/**************************************************
* File: lexhelp.cc.
* Desc: Contains helpful functions for the compiler parser.
* Module: AkraLog : JavaKit.
* Rev: 24 avril 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <stdio.h>
#if defined(_WIN32) || defined(__linux__) || defined(__GNUC__)   // MODNT.
#include <string.h>
#endif

#include "jvtypes.h"

#ifndef _cplusplus
#define class	typedef unsigned int 
class JCIdentifier;
class JCDimIdentifier;
class JCPackage;
class JCPackageDeclaration;
class JCMember;
class JCReferencedType;
class JCActionBlock;
class JCHandlingBlock;
class JCAction;
class JCStatement;
class JCExpression;
class JCVariableDeclaration;
class JCType;
class JCPackageName;
class TransitionList;
class JCTransition;

/*** Extension SQL-92. ***/
class SqlStatementList;
class JCSqlStatement;
class JCSqlClause;
class JCSqlExpression;
class JCSqlIdentifier;
class JCSqlIdentList;

#endif


#include "y.tab.h"


extern FILE *yyin;
extern int isInSubset;
extern void ShowCompilerMessage(int, char *, char *);


#if defined(USE_YACC)

extern int yylineno;
extern int yytchar;
extern char *yysptr, yysbuf[];
int input(void);
void unput(char);


#else		// BISON.

#if defined(NeXT) || defined(__linux__) || defined(__APPLE__)
extern int yylineno;
#else
int yylineno= 1;
#endif
#endif

void PasseCommentaire1(void);
void PasseCommentaire2(void);
void yyerror(char *);


#ifndef EOF_CHAR
#define EOF_CHAR	-1
#endif

#if defined(USE_YACC)

/********************************************************
* Fonction: PasseCommentaire1.
* Desc: Prend une suite de commentaire (commencee par '/''*')
*       et ignore tout ce qui suit, jusqu'a '*''/'.
* Args: Aucun.
* Renvoie: Rien.
********************************************************/

void PasseCommentaire1(void)
{
    char lastChar, c;

    while (1) {
	while ((c = input()) != '/') lastChar= c;
	if (lastChar == '*') {
	    return;
	 }
        else if (c == EOF_CHAR) {
//	    sprintf(ErrorMsgBuffer, "While in comment: unexpected EOF.\n");
//	    AddWarning(NULL, ErrorMsgBuffer);
	    return;
	 }
	else lastChar= c;
    }
}


/********************************************************
* Fonction: PasseComentaire2.
* Desc: Prend une suite de commentaire (commencee par '/''/')
*       et ignore tout ce qui suit, jusqu'a la fin de la ligne.
* Args: Aucun.
* Renvoie: Rien.
********************************************************/

void PasseCommentaire2(void)
{
    char c;

    while ((c = input()) != '\n') {
	if (c == EOF_CHAR) {
	    break;
	 }
     }

    if (c == '\n') unput(c);

    return;
}

#endif		/* USE_YACC */

// Temp locations for the file input/output functions.
#if defined(USE_YACC)
int input()	
{

    yytchar= (yysptr>yysbuf) ? (*--yysptr) : getc(yyin);
    if (yytchar =='\n') {
//	fprintf(stdout, "Got line %d.\n", yylineno);
	yylineno++;
     }
    else if (yytchar == EOF_CHAR) yytchar= 0;
    return (int)yytchar;
}


void unput(char c)
{
    unsigned int lineNumber= 0;

    yytchar= (c);
    if (yytchar=='\n') yylineno--;
    *yysptr++=yytchar;
}
#else		// For BISON/FLEX.


#endif

void output(char c)
{
//    printf("Call to 'output'(%c)... Internal error.\n", c);
}


void yyerror(char *msg)
{
    fprintf(stderr, "%s on line %d.\n", msg, yylineno);
}


int GetTokenID(char *aName)
{
#define NBR_KEYWORDS	72
#define NBR_SQL_KEYWORDS 92
    char *tokenTable[255][80];
    char *entryPoint;
    int resultat= -1, tmpCmp;
    unsigned int i;

    char *tokens[NBR_KEYWORDS]= {
	"abstract", "blocking", "boolean", "break", "byte",
	"byvalue", "case", "cast", "catch", "char",
	"class", "const", "consume", "continue", "critical", "declareSql",
	"default", "do", "double", "else", "execSql",
	"extends", "final", "finally", "fire", "float",
	"for", "future", "generic", "goto", "if",
	"immediate", "implements", "implicit", "import", "inner",
	"instanceof", "int", "interface", "long", "native",
	"new", "null", "operator", "outer", "package",
	"parallel", "passby", "pon", "ppop", "ppush",
	"private", "protected", "pstate", "public", "rest",
	"return", "short", "static", "super", "switch",
	"synchronized", "this", "throw", "throws", "transient",
	"transition", "try", "var", "void", "volatile",
	"while"
    };

    int tokensID[NBR_KEYWORDS]= {
	ABSTRACT_KW, BLOCKING_KW, BOOLEAN_KW, BREAK_KW, BYTE_KW,
	BYVALUE_KW, CASE_KW, CAST_KW, CATCH_KW, CHAR_KW,
	CLASS_KW, CONST_KW, CONSUME_KW, CONTINUE_KW, CRITICAL_KW, DECLARESQL_KW,
	DEFAULT_KW, DO_KW, DOUBLE_KW, ELSE_KW, DOSQL_KW,
	EXTENDS_KW, FINAL_KW, FINALLY_KW, FIRE_KW, FLOAT_KW,
	FOR_KW, FUTURE_KW, GENERIC_KW, GOTO_KW, IF_KW,
	IMMEDIATE_KW, IMPLEMENTS_KW, IMPLICIT_KW, IMPORT_KW, INNER_KW,
	INSTANCEOF_KW, INT_KW, INTERFACE_KW, LONG_KW, NATIVE_KW,
	NEW_KW, NULL_KW, OPERATOR_KW, OUTER_KW, PACKAGE_KW,
	PARALLEL_KW, PASSBY_KW, ON_KW, POP_KW, PUSH_KW,
	PRIVATE_KW, PROTECTED_KW, STATE_KW, PUBLIC_KW, REST_KW,
	RETURN_KW, SHORT_KW, STATIC_KW, SUPER_KW, SWITCH_KW,
	SYNCHRONIZED_KW, THIS_KW, THROW_KW, THROWS_KW, TRANSIENT_KW,
	TRANSITION_KW, TRY_KW, VAR_KW, VOID_KW, VOLATILE_KW,
	WHILE_KW
     };

    char *sqlTokens[NBR_SQL_KEYWORDS]= {
	"absolute", "all", "and", "any", "as", "asc", "avg", "between", "bit_length", "both",
	"by", "character_length", "char_length", "close", "collate", "convert", "corresponding", "count",
	"cross", "current", "current_user", "desc", "delete", "distinct", "escape",
	"except", "exists", "extract", "false", "fetch", "first", "for", "from", "full", "group",
	"having", "in", "indicator", "inner", "insert", "intersect", "into", "is", "join", "last",
	"leading", "left", "like", "lower", "match", "max", "min", "module", "natural",
	"next", "not", "null", "octet_length", "of", "on", "open", "or", "order", "outer", "overlaps",
	"partial", "position", "prior", "relative", "right", "select", "session_user", "set",
	"some", "substring", "sum", "system_user", "table", "trailing", "translate", "trim",
	"true", "union", "unique", "unknown", "update", "upper", "user", "using", "value",
	"values", "where"
    };
    int sqlTokensID[NBR_SQL_KEYWORDS]= {
	ABSOLUTE_KW, ALL_KW, AND_KW, ANY_KW, AS_KW, ASC_KW,
	AVG_KW, BETWEEN_KW, BIT_LENGTH_KW, BOTH_KW,
	BY_KW, CHARACTER_LENGTH_KW, CHAR_LENGTH_KW,
	CLOSE_KW, COLLATE_KW, CONVERT_KW, CORRESPONDING_KW, COUNT_KW,
	CROSS_KW, CURRENT_KW, CURRENT_U_KW, DESC_KW,
	DELETE_KW, DISTINCT_KW, ESCAPE_KW, EXCEPT_KW,
	EXISTS_KW, EXTRACT_KW, FALSE_KW, FETCH_KW,
	FIRST_KW, FOR_KW, FROM_KW, FULL_KW, GROUP_KW,
	HAVING_KW, IN_KW, INDICATOR_KW, INNER_KW,
	INSERT_KW, INTERSECT_KW, INTO_KW, IS_KW, JOIN_KW,
	LAST_KW, LEADING_KW, LEFT_KW, LIKE_KW, LOWER_KW,
	MATCH_KW, MAX_KW, MIN_KW, MODULE_KW, NATURAL_KW,
	NEXT_KW, NOT_KW, NULL_KW, OCTET_LENGTH_KW, OF_KW,
	ON_KW, OPEN_KW, OR_KW, ORDER_KW, OUTER_KW, OVERLAPS_KW,
	PARTIAL_KW, POSITION_KW, PRIOR_KW, RELATIVE_KW,
	RIGHT_KW, SELECT_KW, SESSION_U_KW, SET_KW,
	SOME_KW, SUBSTRING_KW, SUM_KW, SYSTEM_U_KW,
	TABLE_KW, TRAILING_KW, TRANSLATE_KW, TRIM_KW,
	TRUE_KW, UNION_KW, UNIQUE_KW, UNKNOWN_KW,
	UPDATE_KW, UPPER_KW, USER_KW, USING_KW, VALUE_KW,
	VALUES_KW, WHERE_KW
    };

    i= 0;
    if (aName[0] == 'a') i= 0;
    else if (aName[0] == 'b') i= 1;
    else if (aName[0] == 'c') i= 6;
    else if (aName[0] == 'd') i= 15;
    else if (aName[0] == 'e') i= 18;
    else if (aName[0] == 'f') i= 21;
    else if (aName[0] == 'g') i= 27;
    else if (aName[0] == 'i') i= 29;
    else if (aName[0] == 'l') i= 38;
    else if (aName[0] == 'n') i= 39;
    else if (aName[0] == 'o') i= 42;
    else if (aName[0] == 'p') i= 44;
    else if (aName[0] == 'r') i= 54;
    else if (aName[0] == 's') i= 56;
    else if (aName[0] == 't') i= 61;
    else if (aName[0] == 'v') i= 67;
    else if (aName[0] == 'w') i= 70;
    else i= NBR_KEYWORDS;

    for (; i < NBR_KEYWORDS; i++) {
	if ((tmpCmp=  strcmp(aName, tokens[i])) == 0) {
	    if ((tokensID[i] == BYVALUE_KW) || (tokensID[i] == CAST_KW) || (tokensID[i] == CONST_KW)
	    	|| (tokensID[i] == FUTURE_KW) || (tokensID[i] == GENERIC_KW) || (tokensID[i] == GOTO_KW)
	    	|| (tokensID[i] == INNER_KW) || (tokensID[i] == OPERATOR_KW) || (tokensID[i] == OUTER_KW)
	    	|| (tokensID[i] == REST_KW) || (tokensID[i] == VAR_KW)) {
		i= NBR_KEYWORDS;
		ShowCompilerMessage(0, "Warning, use of future reserved word '%s'.\n", aName);
	     }
	    break;
	}
	else if (tmpCmp < 0) {
	    i= NBR_KEYWORDS;
	    break;
	}
    }
    if ((isInSubset == 2) && (i == NBR_KEYWORDS)) {
	for (i= 0; i < NBR_SQL_KEYWORDS; i++) {
	    if (strcmp(aName, sqlTokens[i]) == 0) {
		break;
	    }
	}
	if (i < NBR_SQL_KEYWORDS) return sqlTokensID[i];
	else return -1;
    }
    else {
	if (i < NBR_KEYWORDS) return tokensID[i];
	else return -1;
    }

    /* Si un type est detecte, on retourne TYPE_IDENT_KW. */

    if ((aName[0] < 'a') && (aName[0] > 'z')) return resultat;
    entryPoint= tokenTable[0][(unsigned int)aName[0]];
    if (entryPoint != NULL) {
	entryPoint= tokenTable[1][(unsigned int)aName[1]];
	if (entryPoint != NULL) {
	 }
     }
    return resultat;
}


