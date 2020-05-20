
/*  A Bison parser, made from src/extGram.ycc
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	ABSTRACT_KW	257
#define	ANDAND_KW	258
#define	ANDASSIGN_KW	259
#define	BOOLEAN_KW	260
#define	BREAK_KW	261
#define	BYTE_KW	262
#define	BYVALUE_KW	263
#define	CASE_KW	264
#define	CAST_KW	265
#define	CATCH_KW	266
#define	CHAR_KW	267
#define	CLASS_KW	268
#define	CONST_KW	269
#define	CONTINUE_KW	270
#define	DECR_KW	271
#define	DEFAULT_KW	272
#define	DIVIDEASSIGN_KW	273
#define	DOUBLE_KW	274
#define	DO_KW	275
#define	ELSE_KW	276
#define	EQ_KW	277
#define	EXTENDS_KW	278
#define	FINALLY_KW	279
#define	FINAL_KW	280
#define	FLOAT_KW	281
#define	FOR_KW	282
#define	FUTURE_KW	283
#define	GENERIC_KW	284
#define	GE_KW	285
#define	GOTO_KW	286
#define	ICR_KW	287
#define	IF_KW	288
#define	IMPLEMENTS_KW	289
#define	IMPORT_KW	290
#define	IDENTIFIER_KW	291
#define	INNER_KW	292
#define	INSTANCEOF_KW	293
#define	INTERFACE_KW	294
#define	INT_KW	295
#define	LE_KW	296
#define	LITERAL_BOOLEAN	297
#define	LITERAL_CHAR	298
#define	LITERAL_DOUBLE	299
#define	LITERAL_FLOAT	300
#define	LITERAL_INT	301
#define	LITERAL_LONG	302
#define	LITERAL_STRING	303
#define	LONG_KW	304
#define	LSASSIGN_KW	305
#define	LS_KW	306
#define	MINUSASSIGN_KW	307
#define	MODASSIGN_KW	308
#define	NATIVE_KW	309
#define	NEW_KW	310
#define	NE_KW	311
#define	NOTASSIGN_KW	312
#define	NULL_KW	313
#define	OPERATOR_KW	314
#define	ORASSIGN_KW	315
#define	OROR_KW	316
#define	OUTER_KW	317
#define	PACKAGE_KW	318
#define	PLUSASSIGN_KW	319
#define	PRIVATE_KW	320
#define	PROTECTED_KW	321
#define	PUBLIC_KW	322
#define	REST_KW	323
#define	RETURN_KW	324
#define	RSASSIGN_KW	325
#define	RS_KW	326
#define	SHORT_KW	327
#define	STATIC_KW	328
#define	SUPER_KW	329
#define	SWITCH_KW	330
#define	SYNCHRONIZED_KW	331
#define	THIS_KW	332
#define	THROW_KW	333
#define	THROWS_KW	334
#define	TIMEASSIGN_KW	335
#define	TRANSIENT_KW	336
#define	TRY_KW	337
#define	URSASSIGN_KW	338
#define	URS_KW	339
#define	VAR_KW	340
#define	VOID_KW	341
#define	VOLATILE_KW	342
#define	WHILE_KW	343
#define	BLOCKING_KW	344
#define	CONSUME_KW	345
#define	CRITICAL_KW	346
#define	FIRE_KW	347
#define	IMMEDIATE_KW	348
#define	IMPLICIT_KW	349
#define	LITERAL_TIME	350
#define	ON_KW	351
#define	PARALLEL_KW	352
#define	PASSBY_KW	353
#define	POP_KW	354
#define	PUSH_KW	355
#define	STATE_KW	356
#define	TRANSITION_KW	357
#define	DOSQL_KW	358
#define	DECLARESQL_KW	359
#define	ABSOLUTE_KW	360
#define	ALL_KW	361
#define	AND_KW	362
#define	ANY_KW	363
#define	AS_KW	364
#define	ASC_KW	365
#define	AVG_KW	366
#define	BETWEEN_KW	367
#define	BIT_LENGTH_KW	368
#define	BOTH_KW	369
#define	BY_KW	370
#define	CHARACTER_LENGTH_KW	371
#define	CHAR_LENGTH_KW	372
#define	CLOSE_KW	373
#define	COLLATE_KW	374
#define	COMMIT_KW	375
#define	CONVERT_KW	376
#define	CORRESPONDING_KW	377
#define	COUNT_KW	378
#define	CROSS_KW	379
#define	CURRENT_KW	380
#define	CURRENT_U_KW	381
#define	DELETE_KW	382
#define	DESC_KW	383
#define	DISTINCT_KW	384
#define	ESCAPE_KW	385
#define	EXCEPT_KW	386
#define	EXISTS_KW	387
#define	EXTRACT_KW	388
#define	FALSE_KW	389
#define	FETCH_KW	390
#define	FIRST_KW	391
#define	FROM_KW	392
#define	FULL_KW	393
#define	GROUP_KW	394
#define	HAVING_KW	395
#define	IN_KW	396
#define	INDICATOR_KW	397
#define	INSERT_KW	398
#define	INTERSECT_KW	399
#define	INTO_KW	400
#define	IS_KW	401
#define	JOIN_KW	402
#define	LAST_KW	403
#define	LEADING_KW	404
#define	LEFT_KW	405
#define	LIKE_KW	406
#define	LOWER_KW	407
#define	MATCH_KW	408
#define	MAX_KW	409
#define	MIN_KW	410
#define	MODULE_KW	411
#define	NATURAL_KW	412
#define	NEXT_KW	413
#define	NOT_KW	414
#define	OCTET_LENGTH_KW	415
#define	OF_KW	416
#define	OPEN_KW	417
#define	OR_KW	418
#define	ORDER_KW	419
#define	OVERLAPS_KW	420
#define	PARTIAL_KW	421
#define	POSITION_KW	422
#define	PRIOR_KW	423
#define	RELATIVE_KW	424
#define	RIGHT_KW	425
#define	ROLLBACK_KW	426
#define	SELECT_KW	427
#define	SESSION_U_KW	428
#define	SET_KW	429
#define	SOME_KW	430
#define	SUBSTRING_KW	431
#define	SUM_KW	432
#define	SYSTEM_U_KW	433
#define	TABLE_KW	434
#define	TRAILING_KW	435
#define	TRANSLATE_KW	436
#define	TRIM_KW	437
#define	TRUE_KW	438
#define	UNION_KW	439
#define	UNIQUE_KW	440
#define	UNKNOWN_KW	441
#define	UPDATE_KW	442
#define	UPPER_KW	443
#define	USER_KW	444
#define	USING_KW	445
#define	VALUE_KW	446
#define	VALUES_KW	447
#define	WHERE_KW	448
#define	WORK_KW	449

#line 8 "src/extGram.ycc"

/* On met ici les declaration et les fichiers inclus */

extern "C" {
/* MSC-MOD:
    Il faut ajouter dans le code genere par yacc les choses suivantes (a leurs positions respectives):
    extern int yychar;
    extern short yyerrflag;
    YYSTYPE yylval, yyval;

 int yylex();
extern void yyerror(char *);
*/
 }

#include <stdio.h>
#include <stdlib.h>

#include "jvtypes.h"
#include "constants.h"
#include "package.h"
#include "compileObjects.h"
#include "actions.h"
#include "expressions.h"
#include "variables.h"
#include "identifiers.h"
#include "typing.h"
#include "outConstant.h"
#include "lists.h"
#if defined(PLZEN_LEVEL_3)
#include "sqlActions.h"
#include "sqlExpressions.h"
#include "sqlClauses.h"
#include "sqlConstants.h"
#include "sqlIdentifier.h"
#endif
#include "compiler.h"


extern int yylex();
extern void yyerror(char *);

extern JCCompiler *compiler;
JCPackage *thePackage;
int isInSubset= 0;

extern "C" {
// int isInSubset= 0;
}

#define YYDEBUG	1

#if defined (_WIN32)
#include <malloc.h>

extern "C" {
int yychar;
YYSTYPE yylval;
}


#endif


#line 286 "src/extGram.ycc"
typedef union
{
    bool boolValue;
    wchar *string;
    int	 integerNumber;
    unsigned int flag;
    float floatNumber;
    int longNumber[2];
    double doubleNumber;
    JCIdentifier *identifier;
    JCDimIdentifier *dimIdentifier;
    JCPackage *package;
    JCPackageDeclaration *packDecl;
    JCMember *member;
    JCReferencedType *type;
    JCActionBlock *actionBlock;
    JCHandlingBlock *handlerBlock;
    JCAction *action;
    JCStatement *statement;
    JCExpression *expression;
    JCVariableDeclaration *varDecl;
    JCType *typeDecl;
    JCPackageName *packName;
    TransitionList *transitionList;
    JCTransition *transition;

/*** Extension SQL-92. ***/
    SqlStatementList *sqlStatList;
    JCSqlStatement *sql92Statement;
    JCSqlClause *sqlClause;
    JCSqlExpression *sqlExpression;
    JCSqlIdentifier *sqlIdentifier;
    JCSqlIdentList *sqlIdentList;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		992
#define	YYFLAG		-32768
#define	YYNTBASE	224

#define YYTRANSLATE(x) ((unsigned)(x) <= 449 ? yytranslate[x] : 545)

static const short yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,   219,     2,     2,     2,   212,   204,     2,   198,
   199,   210,   208,   200,   209,   213,   211,     2,   221,   222,
     2,     2,     2,     2,     2,     2,     2,   216,   196,   206,
   197,   205,   201,   220,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
   217,     2,   218,   203,     2,     2,   223,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,   214,   202,   215,   207,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
    97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
   107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
   117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
   127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
   137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
   147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
   157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
   167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
   177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,   191,   192,   193,   194,   195
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     3,     5,     8,    10,    12,    14,    18,    20,
    24,    27,    30,    32,    37,    38,    42,    44,    46,    48,
    49,    50,    51,    60,    61,    64,    65,    68,    72,    74,
    77,    78,    80,    82,    85,    87,    89,    90,    95,    98,
   101,   105,   109,   111,   115,   117,   121,   124,   126,   128,
   130,   132,   138,   139,   141,   143,   147,   150,   151,   154,
   156,   160,   162,   164,   168,   169,   175,   176,   178,   184,
   186,   188,   189,   193,   194,   200,   201,   203,   206,   210,
   214,   215,   217,   219,   223,   224,   229,   230,   234,   235,
   237,   239,   242,   244,   246,   249,   250,   255,   257,   259,
   262,   264,   266,   268,   270,   272,   274,   276,   279,   280,
   285,   287,   291,   293,   295,   297,   298,   303,   304,   310,
   311,   316,   318,   320,   322,   324,   326,   328,   330,   331,
   338,   339,   342,   345,   346,   347,   355,   356,   357,   365,
   366,   367,   377,   378,   379,   390,   393,   395,   397,   398,
   400,   402,   406,   410,   414,   415,   420,   421,   426,   427,
   431,   432,   439,   442,   445,   449,   451,   454,   455,   462,
   465,   466,   468,   470,   474,   476,   478,   480,   482,   484,
   488,   492,   494,   496,   498,   500,   502,   506,   508,   510,
   512,   514,   517,   519,   523,   528,   533,   535,   539,   540,
   542,   544,   548,   554,   559,   561,   564,   568,   569,   571,
   574,   578,   580,   582,   584,   587,   590,   592,   594,   597,
   600,   602,   605,   608,   610,   613,   616,   618,   620,   624,
   628,   632,   634,   638,   642,   644,   648,   652,   656,   658,
   662,   666,   670,   674,   679,   681,   685,   689,   691,   695,
   697,   701,   703,   707,   709,   713,   715,   719,   721,   727,
   729,   731,   735,   738,   743,   745,   747,   749,   751,   753,
   755,   757,   759,   761,   763,   765,   767,   768,   770,   772,
   774,   776,   778,   780,   782,   784,   786,   788,   790,   792,
   794,   796,   800,   803,   807,   809,   811,   813,   815,   817,
   819,   821,   823,   826,   828,   830,   832,   834,   837,   839,
   841,   842,   844,   846,   849,   851,   853,   855,   857,   859,
   861,   863,   865,   867,   869,   871,   873,   874,   879,   880,
   887,   889,   890,   896,   897,   902,   903,   907,   909,   912,
   914,   916,   919,   920,   927,   928,   934,   935,   938,   939,
   941,   943,   946,   947,   953,   957,   961,   965,   969,   974,
   976,   978,   980,   981,   983,   985,   986,   988,   990,   993,
   995,   997,   999,  1001,  1003,  1007,  1008,  1013,  1015,  1016,
  1020,  1022,  1025,  1028,  1031,  1033,  1035,  1037,  1039,  1041,
  1043,  1045,  1047,  1049,  1051,  1054,  1060,  1061,  1064,  1066,
  1068,  1070,  1072,  1075,  1078,  1080,  1082,  1084,  1087,  1090,
  1093,  1094,  1096,  1098,  1100,  1102,  1104,  1106,  1114,  1119,
  1124,  1127,  1129,  1132,  1136,  1145,  1151,  1153,  1157,  1161,
  1163,  1165,  1167,  1174,  1176,  1177,  1179,  1181,  1183,  1185,
  1187,  1191,  1193,  1197,  1199,  1202,  1205,  1207,  1211,  1213,
  1217,  1219,  1221,  1223,  1227,  1231,  1233,  1237,  1241,  1244,
  1247,  1249,  1251,  1253,  1255,  1257,  1259,  1261,  1265,  1267,
  1269,  1271,  1273,  1276,  1279,  1281,  1283,  1285,  1287,  1289,
  1291,  1293,  1295,  1297,  1299,  1301,  1303,  1305,  1308,  1311,
  1313,  1316,  1321,  1327,  1329,  1331,  1333,  1335,  1337,  1339,
  1341,  1343,  1349,  1355,  1357,  1363,  1364,  1366,  1368,  1372,
  1374,  1376,  1378,  1383,  1387,  1390,  1392,  1396,  1399,  1401,
  1403,  1405,  1407,  1409,  1411,  1415,  1420,  1426,  1427,  1429,
  1432,  1434,  1436,  1438,  1441,  1443,  1445,  1447,  1449,  1450,
  1452,  1454,  1456,  1459,  1464,  1466,  1469,  1472,  1474,  1477,
  1483,  1489,  1490,  1493,  1495,  1499,  1500,  1502,  1505,  1506,
  1510,  1512,  1516,  1520,  1521,  1523,  1524,  1526,  1528,  1530,
  1531,  1533,  1537,  1539,  1543,  1545,  1548,  1551,  1552,  1554,
  1557,  1559,  1563,  1565,  1569,  1572,  1574,  1576,  1581,  1583,
  1587,  1589,  1591,  1593,  1595,  1597,  1599,  1601,  1603,  1605,
  1607,  1611,  1618,  1623,  1625,  1629,  1631,  1635,  1640,  1647,
  1652,  1657,  1660,  1663,  1668,  1672,  1674,  1676,  1678,  1680,
  1682,  1684,  1687,  1688,  1690,  1691,  1693,  1695,  1697,  1699,
  1701,  1702,  1704,  1706,  1708,  1710,  1712,  1716,  1718,  1720,
  1722,  1724,  1726,  1728,  1732,  1734,  1738,  1739,  1741,  1742,
  1744,  1746,  1752,  1754,  1758,  1760,  1762
};

static const short yyrhs[] = {    -1,
   225,     0,   226,     0,   225,   226,     0,   227,     0,   229,
     0,   232,     0,    64,   228,   196,     0,   367,     0,   228,
   213,   367,     0,    36,   230,     0,   228,   196,     0,   231,
     0,   228,   213,   210,   196,     0,     0,   373,   233,   234,
     0,   234,     0,   235,     0,   269,     0,     0,     0,     0,
    14,   236,   367,   237,   239,   238,   240,   241,     0,     0,
    24,   333,     0,     0,    35,   259,     0,   214,   243,   215,
     0,   246,     0,   242,   246,     0,     0,   244,     0,   245,
     0,   244,   245,     0,   246,     0,   267,     0,     0,   375,
   253,   247,   248,     0,   375,   380,     0,   249,   196,     0,
   254,   258,   260,     0,   261,   258,   262,     0,   250,     0,
   249,   200,   250,     0,   251,     0,   251,   197,   252,     0,
   367,   342,     0,   324,     0,   274,     0,   368,     0,    87,
     0,   367,   198,   255,   199,   342,     0,     0,   256,     0,
   257,     0,   256,   200,   257,     0,   368,   251,     0,     0,
    80,   259,     0,   333,     0,   259,   200,   333,     0,   277,
     0,   196,     0,   198,   255,   199,     0,     0,   214,   263,
   264,   280,   215,     0,     0,   265,     0,   266,   198,   337,
   199,   196,     0,    78,     0,    75,     0,     0,    74,   268,
   277,     0,     0,    40,   367,   270,   271,   273,     0,     0,
   272,     0,    24,   259,     0,   214,   242,   215,     0,   214,
   275,   215,     0,     0,   276,     0,   252,     0,   276,   200,
   252,     0,     0,   214,   278,   281,   215,     0,     0,   214,
   279,   215,     0,     0,   281,     0,   282,     0,   281,   282,
     0,   283,     0,   285,     0,     1,   196,     0,     0,   368,
   284,   249,   196,     0,   290,     0,   291,     0,   295,   196,
     0,   299,     0,   302,     0,   312,     0,   317,     0,   277,
     0,   392,     0,   394,     0,   286,   196,     0,     0,   289,
   409,   287,   288,     0,   411,     0,   214,   410,   215,     0,
   104,     0,   105,     0,   196,     0,     0,   367,   216,   292,
   285,     0,     0,    10,   293,   324,   216,   282,     0,     0,
    18,   294,   216,   282,     0,   363,     0,   348,     0,   349,
     0,   345,     0,   346,     0,   335,     0,   339,     0,     0,
    34,   297,   198,   324,   199,   285,     0,     0,    22,   285,
     0,   296,   298,     0,     0,     0,    76,   300,   198,   324,
   199,   301,   277,     0,     0,     0,    89,   303,   198,   324,
   199,   304,   285,     0,     0,     0,    21,   305,   285,   306,
    89,   198,   324,   199,   196,     0,     0,     0,    28,   198,
   307,   309,   323,   196,   310,   199,   308,   285,     0,   311,
   196,     0,   283,     0,   196,     0,     0,   311,     0,   295,
     0,   311,   200,   295,     0,     7,   366,   196,     0,    16,
   366,   196,     0,     0,    70,   313,   323,   196,     0,     0,
    79,   314,   324,   196,     0,     0,    83,   316,   277,     0,
     0,    77,   318,   198,   324,   199,   285,     0,   315,   322,
     0,   315,   319,     0,   315,   319,   322,     0,   320,     0,
   319,   320,     0,     0,    12,   321,   198,   257,   199,   277,
     0,    25,   277,     0,     0,   324,     0,   362,     0,   329,
   213,   367,     0,   325,     0,   372,     0,   334,     0,   335,
     0,   327,     0,   198,   324,   199,     0,   198,   331,   199,
     0,   326,     0,   339,     0,   331,     0,   328,     0,   367,
     0,   330,   213,   367,     0,   330,     0,    78,     0,    75,
     0,    59,     0,   331,   217,     0,   331,     0,   332,   324,
   218,     0,   326,   217,   324,   218,     0,   336,   198,   337,
   199,     0,   331,     0,   329,   213,   367,     0,     0,   338,
     0,   324,     0,   338,   200,   324,     0,    56,   369,   198,
   337,   199,     0,    56,   369,   340,   342,     0,   341,     0,
   340,   341,     0,   217,   324,   218,     0,     0,   343,     0,
   217,   218,     0,   343,   217,   218,     0,   329,     0,   345,
     0,   346,     0,   329,    33,     0,   329,    17,     0,   348,
     0,   349,     0,   208,   347,     0,   209,   347,     0,   350,
     0,    33,   329,     0,    17,   329,     0,   344,     0,   207,
   347,     0,   219,   347,     0,   364,     0,   347,     0,   351,
   210,   347,     0,   351,   211,   347,     0,   351,   212,   347,
     0,   351,     0,   352,   208,   351,     0,   352,   209,   351,
     0,   352,     0,   353,    52,   352,     0,   353,    72,   352,
     0,   353,    85,   352,     0,   353,     0,   354,   206,   353,
     0,   354,   205,   353,     0,   354,    31,   353,     0,   354,
    42,   353,     0,   354,    39,   333,   342,     0,   354,     0,
   355,    23,   354,     0,   355,    57,   354,     0,   355,     0,
   356,   204,   355,     0,   356,     0,   357,   203,   356,     0,
   357,     0,   358,   202,   357,     0,   358,     0,   359,     4,
   358,     0,   359,     0,   360,    62,   359,     0,   360,     0,
   360,   201,   324,   216,   361,     0,   361,     0,   363,     0,
   347,   365,   362,     0,   327,   350,     0,   198,   370,   199,
   347,     0,   197,     0,    65,     0,    53,     0,    81,     0,
    19,     0,     5,     0,    61,     0,    58,     0,    54,     0,
    51,     0,    71,     0,    84,     0,     0,   367,     0,    37,
     0,   369,     0,   371,     0,   370,     0,   333,     0,     6,
     0,    13,     0,     8,     0,    73,     0,    41,     0,    27,
     0,    20,     0,    50,     0,   370,   217,   218,     0,   332,
   218,     0,   371,   217,   218,     0,    43,     0,    44,     0,
    46,     0,    47,     0,    49,     0,    48,     0,    45,     0,
     0,     0,     0,     0,     0,    67,     0,    66,     0,    68,
     0,   374,     0,   373,   374,     0,     3,     0,   379,     0,
     0,   376,     0,   377,     0,   376,   377,     0,     3,     0,
    55,     0,    77,     0,    82,     0,    88,     0,   378,     0,
    67,     0,    66,     0,    74,     0,   379,     0,    26,     0,
    68,     0,     0,   382,   384,   381,   407,     0,     0,   102,
   383,   367,   198,   255,   199,     0,   385,     0,     0,   214,
   386,   389,   397,   215,     0,     0,   214,   387,   398,   215,
     0,     0,   214,   388,   215,     0,   390,     0,   389,   390,
     0,   283,     0,   391,     0,   285,   407,     0,     0,    92,
   393,   198,   337,   199,   285,     0,     0,    93,   395,   330,
   396,   196,     0,     0,    97,   330,     0,     0,   398,     0,
   399,     0,   398,   399,     0,     0,   404,   103,   400,   401,
   196,     0,   330,   216,   403,     0,   330,   216,   402,     0,
    18,   216,   402,     0,    18,   216,     7,     0,   367,   198,
   337,   199,     0,    99,     0,    91,     0,     7,     0,     0,
   101,     0,   100,     0,     0,   405,     0,   406,     0,   405,
   406,     0,    90,     0,    94,     0,    98,     0,    95,     0,
   331,     0,     0,   200,   331,     0,     0,   220,   217,   408,
   218,     0,    96,     0,     0,   198,   324,   199,     0,   411,
     0,   410,   411,     0,   412,   196,     0,     1,   196,     0,
   413,     0,   414,     0,   415,     0,   416,     0,   421,     0,
   436,     0,   425,     0,   437,     0,   422,     0,   423,     0,
   163,   367,     0,   136,   417,   367,   146,   420,     0,     0,
   418,   138,     0,   159,     0,   169,     0,   137,     0,   149,
     0,   106,   419,     0,   170,   419,     0,   460,     0,   453,
     0,   537,     0,   119,   367,     0,   121,   424,     0,   172,
   424,     0,     0,   195,     0,   426,     0,   427,     0,   428,
     0,   431,     0,   432,     0,   128,   138,   444,   194,   126,
   162,   367,     0,   128,   138,   444,   492,     0,   144,   146,
   444,   429,     0,   430,   464,     0,   464,     0,    18,   193,
     0,   198,   541,   199,     0,   188,   444,   175,   433,   194,
   126,   162,   367,     0,   188,   444,   175,   433,   492,     0,
   434,     0,   433,   200,   434,     0,   367,   197,   435,     0,
   446,     0,   534,     0,   535,     0,   173,   438,   439,   146,
   537,   489,     0,   470,     0,     0,   130,     0,   107,     0,
   210,     0,   440,     0,   441,     0,   440,   200,   441,     0,
   442,     0,   444,   213,   210,     0,   446,     0,   446,   443,
     0,   538,   367,     0,   445,     0,   157,   213,   367,     0,
   367,     0,   445,   213,   367,     0,   447,     0,   542,     0,
   448,     0,   447,   208,   448,     0,   447,   209,   448,     0,
   449,     0,   448,   210,   449,     0,   448,   211,   449,     0,
   208,   450,     0,   209,   450,     0,   450,     0,   451,     0,
   543,     0,   452,     0,   444,     0,   462,     0,   471,     0,
   198,   446,   199,     0,   455,     0,   458,     0,   454,     0,
   457,     0,   208,   456,     0,   209,   456,     0,   456,     0,
   456,     0,   457,     0,    47,     0,    46,     0,    44,     0,
   459,     0,   190,     0,   127,     0,   174,     0,   179,     0,
   192,     0,   460,     0,   460,   461,     0,   216,   324,     0,
   460,     0,   143,   460,     0,   124,   198,   210,   199,     0,
   463,   198,   438,   446,   199,     0,   112,     0,   155,     0,
   156,     0,   178,     0,   124,     0,   465,     0,   477,     0,
   466,     0,   464,   185,   530,   467,   475,     0,   464,   132,
   530,   467,   475,     0,   468,     0,   475,   145,   530,   467,
   476,     0,     0,   540,     0,   469,     0,   198,   465,   199,
     0,   470,     0,   472,     0,   474,     0,   173,   438,   439,
   489,     0,   198,   464,   199,     0,   193,   473,     0,   532,
     0,   473,   200,   532,     0,   180,   444,     0,   466,     0,
   477,     0,   468,     0,   477,     0,   478,     0,   479,     0,
   198,   477,   199,     0,   487,   125,   148,   487,     0,   487,
   480,   148,   487,   483,     0,     0,   158,     0,   158,   481,
     0,   481,     0,    38,     0,   482,     0,   482,    63,     0,
   185,     0,   151,     0,   171,     0,   139,     0,     0,   484,
     0,   485,     0,   486,     0,    97,   507,     0,   191,   198,
   541,   199,     0,   444,     0,   444,   488,     0,   471,   488,
     0,   477,     0,   538,   367,     0,   538,   367,   198,   541,
   199,     0,   490,   492,   500,   494,   505,     0,     0,   138,
   491,     0,   487,     0,   491,   200,   487,     0,     0,   493,
     0,   194,   507,     0,     0,   165,   116,   495,     0,   496,
     0,   495,   200,   496,     0,   367,   497,   498,     0,     0,
   504,     0,     0,   499,     0,   111,     0,   129,     0,     0,
   501,     0,   140,   116,   502,     0,   503,     0,   502,   200,
   503,     0,   444,     0,   444,   504,     0,   120,   445,     0,
     0,   506,     0,   141,   507,     0,   508,     0,   507,   164,
   508,     0,   509,     0,   508,   108,   509,     0,   160,   510,
     0,   510,     0,   511,     0,   511,   147,   539,   531,     0,
   512,     0,   198,   507,   199,     0,   513,     0,   514,     0,
   515,     0,   518,     0,   519,     0,   520,     0,   521,     0,
   522,     0,   523,     0,   524,     0,   532,   525,   532,     0,
   532,   539,   113,   532,   108,   532,     0,   532,   539,   142,
   516,     0,   471,     0,   198,   517,   199,     0,   446,     0,
   517,   200,   446,     0,   544,   539,   152,   544,     0,   544,
   539,   152,   544,   131,   544,     0,   532,   147,   539,    59,
     0,   532,   525,   529,   471,     0,   133,   471,     0,   186,
   471,     0,   532,   154,   526,   471,     0,   532,   166,   532,
     0,   197,     0,    57,     0,   206,     0,   205,     0,    42,
     0,    31,     0,   527,   528,     0,     0,   186,     0,     0,
   167,     0,   139,     0,   107,     0,   176,     0,   109,     0,
     0,   107,     0,   184,     0,   135,     0,   187,     0,   533,
     0,   198,   536,   199,     0,   446,     0,   534,     0,   535,
     0,    59,     0,    18,     0,   533,     0,   536,   200,   533,
     0,   459,     0,   537,   200,   459,     0,     0,   110,     0,
     0,   160,     0,   123,     0,   123,   116,   198,   541,   199,
     0,   367,     0,   541,   200,   367,     0,   221,     0,   222,
     0,   223,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   597,   599,   601,   603,   605,   613,   616,   622,   629,   636,
   645,   649,   656,   670,   683,   689,   699,   705,   712,   722,
   728,   732,   737,   749,   754,   765,   770,   796,   805,   810,
   817,   822,   828,   833,   845,   851,   888,   899,   932,   945,
   966,   972,   986,   991,   997,  1005,  1019,  1035,  1040,  1060,
  1065,  1073,  1100,  1104,  1109,  1114,  1120,  1130,  1135,  1157,
  1162,  1169,  1174,  1200,  1222,  1228,  1268,  1273,  1278,  1302,
  1310,  1321,  1327,  1333,  1338,  1348,  1353,  1359,  1389,  1397,
  1406,  1411,  1416,  1421,  1439,  1446,  1455,  1460,  1467,  1472,
  1474,  1479,  1485,  1490,  1494,  1503,  1508,  1525,  1533,  1537,
  1542,  1546,  1550,  1554,  1558,  1566,  1571,  1577,  1579,  1585,
  1600,  1610,  1625,  1630,  1636,  1643,  1649,  1658,  1662,  1684,
  1688,  1709,  1718,  1726,  1734,  1742,  1750,  1758,  1767,  1772,
  1783,  1788,  1793,  1834,  1838,  1843,  1853,  1858,  1863,  1873,
  1879,  1882,  1892,  1897,  1902,  1917,  1922,  1926,  1933,  1939,
  1944,  1949,  1955,  1972,  1988,  1992,  2001,  2005,  2016,  2022,
  2026,  2031,  2041,  2059,  2069,  2082,  2087,  2093,  2099,  2110,
  2119,  2125,  2131,  2139,  2152,  2159,  2163,  2167,  2171,  2186,
  2199,  2206,  2212,  2218,  2241,  2247,  2252,  2258,  2263,  2270,
  2277,  2285,  2292,  2303,  2318,  2343,  2351,  2360,  2371,  2376,
  2381,  2386,  2394,  2415,  2432,  2437,  2443,  2450,  2454,  2459,
  2464,  2472,  2477,  2481,  2487,  2497,  2507,  2512,  2516,  2524,
  2553,  2558,  2568,  2578,  2583,  2591,  2599,  2605,  2610,  2619,
  2628,  2638,  2643,  2652,  2662,  2667,  2676,  2685,  2695,  2700,
  2709,  2718,  2727,  2736,  2764,  2769,  2778,  2788,  2793,  2803,
  2808,  2818,  2823,  2833,  2838,  2848,  2853,  2864,  2869,  2880,
  2885,  2890,  2902,  2925,  2939,  2944,  2948,  2952,  2956,  2960,
  2964,  2968,  2972,  2976,  2980,  2984,  2990,  2995,  3001,  3013,
  3018,  3024,  3033,  3043,  3048,  3052,  3056,  3060,  3064,  3068,
  3072,  3078,  3090,  3103,  3109,  3117,  3124,  3145,  3166,  3173,
  3195,  3222,  3227,  3234,  3239,  3243,  3249,  3254,  3259,  3264,
  3270,  3275,  3281,  3286,  3292,  3297,  3301,  3305,  3309,  3313,
  3319,  3324,  3328,  3332,  3338,  3343,  3350,  3356,  3363,  3368,
  3392,  3398,  3404,  3415,  3420,  3431,  3436,  3444,  3449,  3455,
  3460,  3466,  3472,  3477,  3489,  3494,  3540,  3545,  3551,  3556,
  3562,  3568,  3575,  3580,  3588,  3613,  3636,  3645,  3656,  3670,
  3675,  3679,  3685,  3690,  3694,  3699,  3704,  3709,  3714,  3719,
  3724,  3728,  3732,  3737,  3742,  3749,  3754,  3759,  3770,  3775,
  3780,  3785,  3792,  3797,  3803,  3805,  3813,  3815,  3816,  3817,
  3818,  3819,  3821,  3828,  3831,  3838,  3845,  3849,  3854,  3859,
  3863,  3867,  3871,  3875,  3881,  3886,  3889,  3893,  3900,  3907,
  3914,  3916,  3919,  3921,  3922,  3923,  3924,  3927,  3935,  3943,
  3951,  3956,  3960,  3966,  3973,  3981,  3989,  3994,  4000,  4007,
  4009,  4010,  4013,  4025,  4032,  4037,  4041,  4047,  4053,  4057,
  4062,  4069,  4074,  4081,  4083,  4088,  4095,  4097,  4104,  4109,
  4123,  4125,  4131,  4133,  4137,  4143,  4145,  4149,  4155,  4160,
  4164,  4167,  4169,  4172,  4174,  4178,  4179,  4183,  4191,  4193,
  4196,  4198,  4200,  4206,  4211,  4214,  4216,  4219,  4224,  4230,
  4242,  4244,  4248,  4252,  4256,  4260,  4266,  4271,  4277,  4284,
  4286,  4292,  4297,  4304,  4309,  4313,  4317,  4321,  4327,  4329,
  4335,  4337,  4341,  4347,  4349,  4355,  4356,  4359,  4361,  4367,
  4369,  4370,  4373,  4386,  4393,  4400,  4405,  4412,  4419,  4423,
  4428,  4432,  4437,  4442,  4446,  4450,  4459,  4466,  4468,  4469,
  4470,  4472,  4474,  4475,  4476,  4478,  4480,  4481,  4483,  4484,
  4487,  4489,  4494,  4498,  4505,  4510,  4515,  4520,  4525,  4530,
  4537,  4545,  4550,  4555,  4560,  4567,  4571,  4574,  4580,  4585,
  4591,  4596,  4603,  4610,  4615,  4618,  4623,  4625,  4630,  4636,
  4641,  4644,  4651,  4656,  4663,  4668,  4674,  4681,  4686,  4688,
  4695,  4697,  4703,  4705,  4711,  4717,  4720,  4722,  4728,  4730,
  4736,  4738,  4739,  4740,  4741,  4742,  4743,  4744,  4745,  4746,
  4749,  4756,  4764,  4771,  4773,  4779,  4784,  4791,  4796,  4803,
  4811,  4818,  4825,  4832,  4839,  4846,  4851,  4855,  4859,  4863,
  4867,  4873,  4879,  4884,  4889,  4894,  4898,  4904,  4909,  4913,
  4919,  4923,  4929,  4934,  4938,  4944,  4946,  4956,  4958,  4959,
  4962,  4969,  4976,  4981,  4988,  4993,  5000,  5002,  5005,  5009,
  5015,  5020,  5026,  5031,  5040,  5046,  5053
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ABSTRACT_KW",
"ANDAND_KW","ANDASSIGN_KW","BOOLEAN_KW","BREAK_KW","BYTE_KW","BYVALUE_KW","CASE_KW",
"CAST_KW","CATCH_KW","CHAR_KW","CLASS_KW","CONST_KW","CONTINUE_KW","DECR_KW",
"DEFAULT_KW","DIVIDEASSIGN_KW","DOUBLE_KW","DO_KW","ELSE_KW","EQ_KW","EXTENDS_KW",
"FINALLY_KW","FINAL_KW","FLOAT_KW","FOR_KW","FUTURE_KW","GENERIC_KW","GE_KW",
"GOTO_KW","ICR_KW","IF_KW","IMPLEMENTS_KW","IMPORT_KW","IDENTIFIER_KW","INNER_KW",
"INSTANCEOF_KW","INTERFACE_KW","INT_KW","LE_KW","LITERAL_BOOLEAN","LITERAL_CHAR",
"LITERAL_DOUBLE","LITERAL_FLOAT","LITERAL_INT","LITERAL_LONG","LITERAL_STRING",
"LONG_KW","LSASSIGN_KW","LS_KW","MINUSASSIGN_KW","MODASSIGN_KW","NATIVE_KW",
"NEW_KW","NE_KW","NOTASSIGN_KW","NULL_KW","OPERATOR_KW","ORASSIGN_KW","OROR_KW",
"OUTER_KW","PACKAGE_KW","PLUSASSIGN_KW","PRIVATE_KW","PROTECTED_KW","PUBLIC_KW",
"REST_KW","RETURN_KW","RSASSIGN_KW","RS_KW","SHORT_KW","STATIC_KW","SUPER_KW",
"SWITCH_KW","SYNCHRONIZED_KW","THIS_KW","THROW_KW","THROWS_KW","TIMEASSIGN_KW",
"TRANSIENT_KW","TRY_KW","URSASSIGN_KW","URS_KW","VAR_KW","VOID_KW","VOLATILE_KW",
"WHILE_KW","BLOCKING_KW","CONSUME_KW","CRITICAL_KW","FIRE_KW","IMMEDIATE_KW",
"IMPLICIT_KW","LITERAL_TIME","ON_KW","PARALLEL_KW","PASSBY_KW","POP_KW","PUSH_KW",
"STATE_KW","TRANSITION_KW","DOSQL_KW","DECLARESQL_KW","ABSOLUTE_KW","ALL_KW",
"AND_KW","ANY_KW","AS_KW","ASC_KW","AVG_KW","BETWEEN_KW","BIT_LENGTH_KW","BOTH_KW",
"BY_KW","CHARACTER_LENGTH_KW","CHAR_LENGTH_KW","CLOSE_KW","COLLATE_KW","COMMIT_KW",
"CONVERT_KW","CORRESPONDING_KW","COUNT_KW","CROSS_KW","CURRENT_KW","CURRENT_U_KW",
"DELETE_KW","DESC_KW","DISTINCT_KW","ESCAPE_KW","EXCEPT_KW","EXISTS_KW","EXTRACT_KW",
"FALSE_KW","FETCH_KW","FIRST_KW","FROM_KW","FULL_KW","GROUP_KW","HAVING_KW",
"IN_KW","INDICATOR_KW","INSERT_KW","INTERSECT_KW","INTO_KW","IS_KW","JOIN_KW",
"LAST_KW","LEADING_KW","LEFT_KW","LIKE_KW","LOWER_KW","MATCH_KW","MAX_KW","MIN_KW",
"MODULE_KW","NATURAL_KW","NEXT_KW","NOT_KW","OCTET_LENGTH_KW","OF_KW","OPEN_KW",
"OR_KW","ORDER_KW","OVERLAPS_KW","PARTIAL_KW","POSITION_KW","PRIOR_KW","RELATIVE_KW",
"RIGHT_KW","ROLLBACK_KW","SELECT_KW","SESSION_U_KW","SET_KW","SOME_KW","SUBSTRING_KW",
"SUM_KW","SYSTEM_U_KW","TABLE_KW","TRAILING_KW","TRANSLATE_KW","TRIM_KW","TRUE_KW",
"UNION_KW","UNIQUE_KW","UNKNOWN_KW","UPDATE_KW","UPPER_KW","USER_KW","USING_KW",
"VALUE_KW","VALUES_KW","WHERE_KW","WORK_KW","';'","'='","'('","')'","','","'?'",
"'|'","'^'","'&'","'>'","'<'","'~'","'+'","'-'","'*'","'/'","'%'","'.'","'{'",
"'}'","':'","'['","']'","'!'","'@'","'1'","'2'","'a'","CompilationUnit","UnitList",
"UnitComponent","PackageStatement","PackageName","ImportStatements","ImportBody",
"TypeImportOnDemandStatement","TypeDeclaration","@1","TypeDeclarationBody","ClassDeclaration",
"@2","@3","@4","SuperClass","Interface","ClassBody","LimitedFieldDeclarations",
"FieldDeclarations.Opt","FieldDeclarations","FieldDeclaration","LimitedFieldDeclaration",
"@5","MethodOrFieldVarDeclaration","VariableDeclarators","VariableDeclarator",
"DeclaratorName","VariableInitializer","ResultType","MethodDeclarator","ParameterList.Opt",
"ParameterList","Parameter","Throws.Opt","TypeNameList","MethodBody","ConstructorDeclarator",
"ConstructorBody","@6","ExplicitConstructorCallStatement.Opt","ExplicitConstructorCallStatement",
"ThisOrSuper","StaticInitializer","@7","InterfaceDeclaration","@8","ExtendsInterface.Opt",
"ExtendsInterface","InterfaceBody","ArrayInitializer","ElementInitializers.Opt",
"ElementInitializers","Block","@9","@10","LocalVariableDeclarationAndStatements.Opt",
"LocalVariableDeclarationAndStatements","LocalVariableDeclarationOrStatement",
"LocalVariableDeclarationStatement","@11","Statement","EmbeddedSqlStatement",
"@12","ActualSqlPart","SqlStatementAction","EmptyStatement","LabeledStatement",
"@13","@14","@15","ExpressionStatement","IfHeadStatement","@16","ElseStatement.Opt",
"SelectionStatement","@17","@18","IterationStatement","@19","@20","@21","@22",
"@23","@24","ForInit","ForIncrOpt","ExpressionStatements","JumpStatement","@25",
"@26","TryHeadStatement","@27","GuardingStatement","@28","Catches","Catch","@29",
"Finally","Expression.Opt","Expression","FieldAccess","ComplexPrimary","ParenthisedName",
"NotJustName","PrimaryExpression","QualifiedName","Name","NameArrayStart","TypeName",
"ArrayAccess","MethodCall","MethodAccess","ArgumentList.Opt","ArgumentList",
"AllocationExpression","DimExpressions","DimExpression","Dims.Opt","Dims","PostfixExpression",
"PostIncrement","PostDecrement","UnaryExpression","PreIncrement","PreDecrement",
"UnaryExpressionNotPlusMinus","MultiplicativeExpression","AdditiveExpression",
"ShiftExpression","RelationalExpression","EqualityExpression","AndExpression",
"ExclusiveOrExpression","InclusiveOrExpression","ConditionalAndExpression","ConditionalOrExpression",
"ConditionalExpression","AssignmentExpression","Assignment","CastExpression",
"AssignmentOperator","IdentifierOpt","Identifier","Type","NonArrayType","PrimitiveType",
"ArrayType","Literal","ClassModifiers","ClassModifier","MethodModifiers.Opt",
"MethodModifiers","MethodModifier","SubCategory2","SubCategory1","StateMember",
"@30","StateDeclarator","@31","StateBody","StateBlock","@32","@33","@34","LocalVarDecAndStateStatements",
"LocalVarDecOrStateStatement","StateStatement","CriticalStatement","@35","FireStatement",
"@36","FireDestination.Opt","StateTransitions.Opt","StateTransitions","StateTransition",
"@37","PureStateTransition","TransitionDestination","TransitionSkip","TransitionModifiers.Opt",
"TransitionModifiers","TransitionModifier","TimeInfo.Opt","TimeValue","Receiver.Opt",
"sql92.ProcedureStatementList","sql92.SingleStatement","sql92.ProcedureStatement",
"sql92.DataStatement","sql92.TransactionStatement","sql92.OpenStatement","sql92.FetchStatement",
"sql92.FetchOrientationOpt","sql92.FetchOrientation","sql92.SimpleValueSpec",
"sql92.FetchTargetList","sql92.CloseStatement","sql92.CommitStatement","sql92.RollbackStatement",
"sql92.Work.Opt","sql92.DataChange","sql92.DeleteStatementPos","sql92.DeleteStatementSearched",
"sql92.InsertStatement","sql92.InsertColsAndSource","sql92.InsertColList","sql92.UpdateStatementPos",
"sql92.UpdateStatementSearched","sql92.SetClauseList","sql92.SetClause","sql92.UpdateSource",
"sql92.SelectStatementSingleRow","sql92.SelectStatementMultipleRow","sql92.SetQuantifier",
"sql92.SelectList","sql92.SelectSubList","sql92.SelectSubListElement","sql92.DerivedColumn",
"sql92.AsClause","sql92.TableName","sql92.QualifiedName","sql92.ValueExpr","sql92.NumericValueExpr",
"sql92.Term","sql92.Factor","sql92.NumericPrimary","sql92.ValueExprPrimary",
"sql92.UnsignedValueSpec","sql92.Literal","sql92.SignedNumericLiteral","sql92.UnsignedLiteral",
"sql92.UnsignedNumericLiteral","sql92.GeneralLiteral","sql92.GeneralValueSpec",
"sql92.VariableSpec","sql92.EmbeddedVarName","sql92.IndicatorVar","sql92.SetFunctionSpec",
"sql92.SetFctType","sql92.QueryExpr","sql92.NonJoinQueryExpr","sql92.NonJoinQueryTerm",
"sql92.CorrespSpecOpt","sql92.NonJoinQueryPrimary","sql92.SimpleTable","sql92.QuerySpec",
"sql92.SubQuery","sql92.TableValueConstr","sql92.TableValueConstrList","sql92.ExplicitTable",
"sql92.QueryTerm","sql92.QueryPrimary","sql92.JoinedTable","sql92.CrossJoin",
"sql92.QualifiedJoin","sql92.NatAndJoinType.Opt","sql92.JoinType","sql92.OuterJoinType",
"sql92.JoinSpec.Opt","sql92.JoinSpec","sql92.JoinCond","sql92.NamedColumnJoin",
"sql92.TableReference","sql92.TableReferenceEndPart","sql92.TableExpression",
"sql92.FromClause","sql92.TableReferenceList","sql92.WhereClauseOpt","sql92.WhereClause",
"sql92.OrderByOpt","sql92.SortList","sql92.SortItem","sql92.CollateClauseOpt",
"sql92.SortDirectionOpt","sql92.SortDirection","sql92.GroupByClauseOpt","sql92.GroupByClause",
"sql92.GroupingColumnRefList","sql92.GroupingColumnRef","sql92.CollateClause",
"sql92.HavingClauseOpt","sql92.HavingClause","sql92.SearchCond","sql92.BooleanTerm",
"sql92.BooleanFactor","sql92.BooleanTest","sql92.BooleanPrimary","sql92.Predicate",
"sql92.ComparePred","sql92.BetweenPred","sql92.InPred","sql92.InPredValue","sql92.InValueList",
"sql92.LikePred","sql92.NullPred","sql92.QuantifiedCompPred","sql92.ExistsPred",
"sql92.UniquePred","sql92.MatchPred","sql92.OverlapsPred","sql92.CompOp","sql92.MatchModeOpt",
"sql92.UniqueOpt","sql92.FullOpt","sql92.Quantifier","sql92.AllOpt","sql92.TruthValue",
"sql92.RowValueConstr","sql92.RowValueConstrEle","sql92.NullSpec","sql92.DefaultSpec",
"sql92.RowValueConstrList","sql92.SelectTargetList","sql92.AsOpt","sql92.NotOpt",
"sql92.CorrespSpec","IdentifierList","sql92.StringValueExpr","sql92.NumericValueFunction",
"sql92.CharValueExpr", NULL
};
#endif

static const short yyr1[] = {     0,
   224,   224,   225,   225,   226,   226,   226,   227,   228,   228,
   229,   230,   230,   231,   233,   232,   232,   234,   234,   236,
   237,   238,   235,   239,   239,   240,   240,   241,   242,   242,
   243,   243,   244,   244,   245,   245,   247,   246,   246,   248,
   248,   248,   249,   249,   250,   250,   251,   252,   252,   253,
   253,   254,   255,   255,   256,   256,   257,   258,   258,   259,
   259,   260,   260,   261,   263,   262,   264,   264,   265,   266,
   266,   268,   267,   270,   269,   271,   271,   272,   273,   274,
   275,   275,   276,   276,   278,   277,   279,   277,   280,   280,
   281,   281,   282,   282,   282,   284,   283,   285,   285,   285,
   285,   285,   285,   285,   285,   285,   285,   285,   287,   286,
   288,   288,   289,   289,   290,   292,   291,   293,   291,   294,
   291,   295,   295,   295,   295,   295,   295,   295,   297,   296,
   298,   298,   299,   300,   301,   299,   303,   304,   302,   305,
   306,   302,   307,   308,   302,   309,   309,   309,   310,   310,
   311,   311,   312,   312,   313,   312,   314,   312,   316,   315,
   318,   317,   317,   317,   317,   319,   319,   321,   320,   322,
   323,   323,   324,   325,   326,   326,   326,   326,   326,   326,
   327,   328,   328,   329,   329,   330,   330,   331,   331,   331,
   331,   332,   333,   334,   334,   335,   336,   336,   337,   337,
   338,   338,   339,   339,   340,   340,   341,   342,   342,   343,
   343,   344,   344,   344,   345,   346,   347,   347,   347,   347,
   347,   348,   349,   350,   350,   350,   350,   351,   351,   351,
   351,   352,   352,   352,   353,   353,   353,   353,   354,   354,
   354,   354,   354,   354,   355,   355,   355,   356,   356,   357,
   357,   358,   358,   359,   359,   360,   360,   361,   361,   362,
   362,   363,   364,   364,   365,   365,   365,   365,   365,   365,
   365,   365,   365,   365,   365,   365,   366,   366,   367,   368,
   368,   369,   369,   370,   370,   370,   370,   370,   370,   370,
   370,   371,   371,   371,   372,   372,   372,   372,   372,   372,
   372,    -1,    -1,    -1,    -1,    -1,   373,   373,   374,   374,
   375,   375,   376,   376,   377,   377,   377,   377,   377,   377,
   378,   378,   378,   378,   379,   379,   381,   380,   383,   382,
   384,   386,   385,   387,   385,   388,   385,   389,   389,   390,
   390,   391,   393,   392,   395,   394,   396,   396,   397,   397,
   398,   398,   400,   399,   401,   401,   401,   401,   402,   403,
   403,   403,    -1,    -1,    -1,   404,   404,   405,   405,   406,
   406,   406,   406,    -1,    -1,   407,   407,   408,   409,   409,
   410,   410,   411,   411,   412,   412,   413,   413,   413,   413,
   413,   413,   414,   414,   415,   416,   417,   417,   418,   418,
   418,   418,   418,   418,   419,   419,   420,   421,   422,   423,
   424,   424,   425,   425,   425,   425,   425,   426,   427,   428,
   429,   429,   429,   430,   431,   432,   433,   433,   434,   435,
   435,   435,   436,   437,   438,   438,   438,   439,   439,   440,
   440,   441,   441,   442,   442,   443,   444,   444,   445,   445,
   446,   446,   447,   447,   447,   448,   448,   448,   449,   449,
   449,   450,   450,   451,   451,   451,   451,   451,   452,   452,
   453,   453,   454,   454,   454,   455,   455,   456,   456,   457,
   458,   458,   458,   458,   458,   458,   459,   459,   460,   461,
   461,   462,   462,   463,   463,   463,   463,   463,   464,   464,
   465,   465,   465,   466,   466,   467,   467,   468,   468,   469,
   469,   469,   470,   471,   472,   473,   473,   474,   475,   475,
   476,   476,   477,   477,   477,   478,   479,   480,   480,   480,
   480,   481,   481,   481,   481,   482,   482,   482,   483,   483,
   484,   484,   485,   486,   487,   487,   487,   487,   488,   488,
   489,   490,   490,   491,   491,   492,   492,   493,   494,   494,
   495,   495,   496,   497,   497,   498,   498,   499,   499,   500,
   500,   501,   502,   502,   503,   503,   504,   505,   505,   506,
   507,   507,   508,   508,   509,   509,   510,   510,   511,   511,
   512,   512,   512,   512,   512,   512,   512,   512,   512,   512,
   513,   514,   515,   516,   516,   517,   517,   518,   518,   519,
   520,   521,   522,   523,   524,   525,   525,   525,   525,   525,
   525,   526,   527,   527,   528,   528,   528,   529,   529,   529,
   530,   530,   531,   531,   531,   532,   532,   533,   533,   533,
   534,   535,   536,   536,   537,   537,   538,   538,   539,   539,
   540,   540,   541,   541,   542,   543,   544
};

static const short yyr2[] = {     0,
     0,     1,     1,     2,     1,     1,     1,     3,     1,     3,
     2,     2,     1,     4,     0,     3,     1,     1,     1,     0,
     0,     0,     8,     0,     2,     0,     2,     3,     1,     2,
     0,     1,     1,     2,     1,     1,     0,     4,     2,     2,
     3,     3,     1,     3,     1,     3,     2,     1,     1,     1,
     1,     5,     0,     1,     1,     3,     2,     0,     2,     1,
     3,     1,     1,     3,     0,     5,     0,     1,     5,     1,
     1,     0,     3,     0,     5,     0,     1,     2,     3,     3,
     0,     1,     1,     3,     0,     4,     0,     3,     0,     1,
     1,     2,     1,     1,     2,     0,     4,     1,     1,     2,
     1,     1,     1,     1,     1,     1,     1,     2,     0,     4,
     1,     3,     1,     1,     1,     0,     4,     0,     5,     0,
     4,     1,     1,     1,     1,     1,     1,     1,     0,     6,
     0,     2,     2,     0,     0,     7,     0,     0,     7,     0,
     0,     9,     0,     0,    10,     2,     1,     1,     0,     1,
     1,     3,     3,     3,     0,     4,     0,     4,     0,     3,
     0,     6,     2,     2,     3,     1,     2,     0,     6,     2,
     0,     1,     1,     3,     1,     1,     1,     1,     1,     3,
     3,     1,     1,     1,     1,     1,     3,     1,     1,     1,
     1,     2,     1,     3,     4,     4,     1,     3,     0,     1,
     1,     3,     5,     4,     1,     2,     3,     0,     1,     2,
     3,     1,     1,     1,     2,     2,     1,     1,     2,     2,
     1,     2,     2,     1,     2,     2,     1,     1,     3,     3,
     3,     1,     3,     3,     1,     3,     3,     3,     1,     3,
     3,     3,     3,     4,     1,     3,     3,     1,     3,     1,
     3,     1,     3,     1,     3,     1,     3,     1,     5,     1,
     1,     3,     2,     4,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     0,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     3,     2,     3,     1,     1,     1,     1,     1,     1,
     1,     1,     2,     1,     1,     1,     1,     2,     1,     1,
     0,     1,     1,     2,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     0,     4,     0,     6,
     1,     0,     5,     0,     4,     0,     3,     1,     2,     1,
     1,     2,     0,     6,     0,     5,     0,     2,     0,     1,
     1,     2,     0,     5,     3,     3,     3,     3,     4,     1,
     1,     1,     0,     1,     1,     0,     1,     1,     2,     1,
     1,     1,     1,     1,     3,     0,     4,     1,     0,     3,
     1,     2,     2,     2,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     2,     5,     0,     2,     1,     1,
     1,     1,     2,     2,     1,     1,     1,     2,     2,     2,
     0,     1,     1,     1,     1,     1,     1,     7,     4,     4,
     2,     1,     2,     3,     8,     5,     1,     3,     3,     1,
     1,     1,     6,     1,     0,     1,     1,     1,     1,     1,
     3,     1,     3,     1,     2,     2,     1,     3,     1,     3,
     1,     1,     1,     3,     3,     1,     3,     3,     2,     2,
     1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
     1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
     2,     4,     5,     1,     1,     1,     1,     1,     1,     1,
     1,     5,     5,     1,     5,     0,     1,     1,     3,     1,
     1,     1,     4,     3,     2,     1,     3,     2,     1,     1,
     1,     1,     1,     1,     3,     4,     5,     0,     1,     2,
     1,     1,     1,     2,     1,     1,     1,     1,     0,     1,
     1,     1,     2,     4,     1,     2,     2,     1,     2,     5,
     5,     0,     2,     1,     3,     0,     1,     2,     0,     3,
     1,     3,     3,     0,     1,     0,     1,     1,     1,     0,
     1,     3,     1,     3,     1,     2,     2,     0,     1,     2,
     1,     3,     1,     3,     2,     1,     1,     4,     1,     3,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     3,     6,     4,     1,     3,     1,     3,     4,     6,     4,
     4,     2,     2,     4,     3,     1,     1,     1,     1,     1,
     1,     2,     0,     1,     0,     1,     1,     1,     1,     1,
     0,     1,     1,     1,     1,     1,     3,     1,     1,     1,
     1,     1,     1,     3,     1,     3,     0,     1,     0,     1,
     1,     5,     1,     3,     1,     1,     1
};

static const short yydefact[] = {     1,
   309,    20,   325,     0,     0,     0,   326,     2,     3,     5,
     6,     7,    17,    18,    19,    15,   307,   310,     0,   279,
     0,    11,    13,     9,    74,     0,     4,     0,   308,    21,
    12,     0,    76,     8,     0,    16,    24,     0,    10,     0,
     0,    77,     0,    22,    14,   191,   190,   189,    78,   188,
   193,    60,   186,   311,    75,    25,    26,     0,     0,   315,
   316,   322,   321,   323,   317,   318,   319,   311,    29,     0,
   312,   313,   320,   324,     0,     0,    61,   187,    79,    30,
   284,   286,   285,   290,   289,   288,   291,   287,    51,   329,
    37,   193,     0,   283,    50,   280,   282,   281,    39,     0,
   314,    27,   311,    23,     0,     0,   192,   293,     0,     0,
   332,   327,   331,   323,     0,   311,    33,    35,    36,     0,
    53,    38,     0,    43,    45,    58,    58,   208,   292,   294,
     0,   366,     0,   376,     0,    28,    34,    53,     0,    54,
    55,     0,    40,     0,     0,     0,     0,     0,    53,     0,
    47,   209,   277,   118,   277,     0,   120,   140,     0,     0,
   129,   295,   296,   301,   297,   298,   300,   299,     0,   155,
   134,   161,   157,   159,   137,   343,   345,   113,   114,   115,
     0,     0,     0,     0,    85,     0,   105,   340,   376,     0,
   379,    98,    99,     0,   131,   101,   102,   103,     0,   104,
   175,   182,   179,   185,   212,   184,     0,   177,   178,     0,
   183,   224,   213,   214,     0,   217,   218,   221,   122,   227,
   186,    96,   176,   349,   338,   341,   106,   107,   370,   371,
   373,   372,   366,   351,     0,   367,   368,   337,     0,   328,
    73,     0,    64,     0,    57,   208,    44,    81,    46,    49,
    48,   184,     0,   178,   183,   213,   214,   228,   217,   218,
   232,   235,   239,   245,   248,   250,   252,   254,   256,   258,
   260,   173,   261,    59,    63,    41,    62,    65,    42,     0,
   210,     0,     0,   278,     0,     0,     0,   179,   223,     0,
     0,   143,   222,     0,     0,   282,   171,     0,     0,     0,
     0,     0,     0,     0,     0,   184,     0,   225,   219,   220,
     0,     0,   226,   342,   108,     0,   109,   100,     0,   133,
   168,     0,   164,   166,   163,     0,   263,   216,   215,     0,
     0,   199,   270,   269,   274,   267,   273,   272,   271,   266,
   275,   268,   276,   265,     0,   116,     0,   339,     0,   350,
   335,   352,   353,   369,     0,   330,    56,    83,     0,    82,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    67,   208,   211,   153,     0,   154,     0,   141,     0,
     0,   199,     0,   208,   205,     0,   172,     0,     0,     0,
   160,     0,   199,   347,   180,   181,     0,     0,     0,    91,
    93,    94,    88,     0,     0,   132,     0,   170,   167,   165,
     0,   174,   194,   201,     0,   200,   262,     0,     0,   333,
     0,   378,     0,    80,     0,   229,   230,   231,   228,   233,
   234,   236,   237,   238,   242,   208,   243,   241,   240,   246,
   247,   249,   251,   253,   255,   257,     0,    71,    70,     0,
    68,     0,    52,     0,   121,     0,   148,   147,   151,   171,
     0,     0,     0,     0,     0,   206,   204,   156,     0,     0,
   158,     0,     0,     0,     0,   264,    95,    86,    92,   380,
     0,     0,   411,     0,   397,     0,     0,   411,   435,     0,
     0,   110,   111,     0,   385,   386,   387,   388,   389,   393,
   394,   391,   413,   414,   415,   416,   417,   390,   392,   434,
     0,   195,   196,     0,   117,    97,     0,     0,     0,   377,
    84,   244,     0,     0,     0,   199,   119,     0,     0,   146,
     0,     0,   203,   207,   135,     0,   138,     0,   348,   346,
   384,   408,   412,   409,     0,     0,   401,   402,   399,   400,
     0,     0,     0,     0,   395,   410,   437,   436,     0,     0,
   449,     0,   447,     0,   381,   383,     0,   202,     0,     0,
   354,   259,    66,     0,     0,   149,   152,   130,     0,   162,
     0,   344,   556,   480,   479,   478,     0,     0,     0,   403,
   406,   471,   475,   472,   405,   404,     0,   398,     0,   494,
     0,   483,   495,   496,   484,   497,   485,   482,   486,     0,
     0,     0,   438,   655,   656,   552,   439,   440,   442,   465,
   444,   451,   453,   456,   461,   462,   464,   469,   476,   477,
   470,   481,   487,   466,     0,   467,   452,   463,     0,     0,
     0,   112,   382,     0,   358,     0,   357,   362,   361,   360,
   356,   355,     0,     0,     0,   150,   136,   139,     0,   419,
   557,   473,   474,   489,     0,     0,   435,     0,     0,     0,
   420,     0,   545,   422,   499,   501,   504,   508,   510,   647,
   511,   512,     0,   548,   523,   524,   528,     0,     0,   465,
     0,     0,   467,   465,   459,   460,     0,     0,   513,   556,
     0,     0,   648,   445,     0,     0,     0,     0,     0,     0,
   490,   488,   435,   448,     0,   556,   427,   450,   169,   199,
    69,     0,   144,   642,   641,     0,     0,     0,     0,     0,
   657,   638,   558,   581,   583,   586,   587,   589,   591,   592,
   593,   594,   595,   596,   597,   598,   599,   600,   649,   636,
   639,   640,   649,   396,   645,   407,   423,     0,   518,     0,
   515,   516,     0,   449,   499,   548,     0,   421,   546,     0,
   631,   631,   547,   631,   532,     0,   538,   536,   529,   537,
   535,     0,   531,   533,     0,   468,   514,     0,   548,   554,
   553,   552,     0,   570,   441,   443,   446,   454,   455,   457,
   458,   491,     0,     0,     0,     0,   426,     0,   142,     0,
     0,     0,   612,   585,   613,     0,   638,     0,   636,     0,
     0,     0,   649,   621,   620,   617,   649,   623,   650,     0,
   616,   619,   618,     0,     0,     0,     0,   552,   643,     0,
   509,   525,   424,     0,   549,   632,   506,   506,   506,     0,
   530,     0,   534,   492,     0,   433,     0,   559,   571,     0,
   429,   430,   431,   432,     0,   428,   359,   145,   418,   590,
   637,     0,   582,   584,     0,     0,   624,     0,   625,   615,
   628,   630,   629,     0,   601,     0,     0,     0,   646,   517,
   654,     0,   651,     0,   507,     0,     0,   526,   539,   555,
     0,     0,   578,   493,     0,   644,   634,   633,   635,   588,
   610,   614,   627,   626,   622,   611,     0,     0,   604,   603,
   608,   653,     0,     0,   519,   503,   548,   502,   521,   505,
   548,     0,     0,   527,   540,   541,   542,   575,   572,   573,
     0,     0,   551,   579,   425,     0,   606,     0,     0,   550,
     0,   543,     0,     0,   576,     0,   564,   560,   561,   580,
   602,   605,     0,   609,     0,     0,   577,   574,   566,   565,
     0,   607,   652,   544,   568,   569,   563,   567,   562,     0,
     0,     0
};

static const short yydefgoto[] = {   990,
     8,     9,    10,    21,    11,    22,    23,    12,    28,    13,
    14,    19,    37,    57,    44,    76,   104,    68,   115,   116,
   117,   118,   106,   122,   123,   124,   125,   249,    91,   126,
   139,   140,   141,   147,    49,   276,   127,   279,   382,   460,
   461,   462,   119,   135,    15,    33,    41,    42,    55,   250,
   359,   360,   187,   311,   312,   534,   409,   410,   411,   347,
   412,   190,   415,   502,   191,   192,   193,   428,   285,   290,
   194,   195,   294,   320,   196,   298,   589,   197,   302,   591,
   291,   466,   390,   820,   470,   665,   471,   198,   297,   300,
   199,   301,   200,   299,   323,   324,   417,   325,   396,   424,
   201,   202,   203,   204,   205,    50,   252,   253,    94,   208,
   254,   210,   425,   426,   255,   394,   395,   151,   152,   212,
   256,   257,   258,   259,   260,   218,   261,   262,   263,   264,
   265,   266,   267,   268,   269,   270,   271,   272,   273,   220,
   345,   283,    53,   222,    96,    97,    98,   223,    16,    17,
    70,    71,    72,    73,    74,    99,   134,   100,   105,   112,
   113,   131,   132,   133,   224,   225,   226,   227,   303,   228,
   304,   485,   349,   233,   234,   431,   529,   657,   662,   235,
   236,   237,   240,   433,   317,   574,   503,   504,   505,   506,
   507,   508,   562,   563,   600,   764,   509,   510,   511,   554,
   512,   513,   514,   515,   681,   682,   516,   517,   726,   727,
   871,   518,   519,   569,   626,   627,   628,   629,   714,   704,
   573,   742,   632,   633,   634,   635,   636,   637,   601,   602,
   638,   639,   640,   641,   642,   643,   722,   644,   645,   702,
   685,   686,   904,   687,   688,   689,   646,   691,   771,   692,
   693,   940,   694,   695,   696,   792,   793,   794,   944,   945,
   946,   947,   697,   779,   709,   710,   801,   670,   671,   913,
   968,   969,   979,   987,   988,   868,   869,   949,   950,   965,
   953,   954,   743,   744,   745,   746,   747,   748,   749,   750,
   751,   930,   958,   752,   753,   754,   755,   756,   757,   758,
   844,   888,   889,   925,   894,   857,   920,   759,   760,   761,
   762,   830,   766,   780,   845,   905,   777,   647,   648,   763
};

static const short yypact[] = {  1233,
-32768,-32768,-32768,    89,    89,    89,-32768,  1233,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   173,-32768,-32768,    89,-32768,
   -22,-32768,-32768,-32768,-32768,   126,-32768,    70,-32768,-32768,
-32768,   -24,   194,-32768,    89,-32768,   312,   -26,-32768,   301,
    63,-32768,   301,-32768,-32768,-32768,-32768,-32768,   142,   184,
-32768,-32768,-32768,  1468,-32768,-32768,   354,   301,    89,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    11,-32768,  1452,
  1468,-32768,-32768,-32768,   301,   190,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   193,   210,-32768,-32768,-32768,   224,   232,-32768,   241,
-32768,   142,   116,-32768,    89,    12,-32768,-32768,   240,   267,
   271,-32768,-32768,   277,   279,   955,-32768,-32768,-32768,   317,
  1726,-32768,   182,-32768,   313,   441,   441,   -51,-32768,-32768,
  1910,   530,   328,   334,   333,-32768,-32768,  1726,   353,   361,
-32768,    89,-32768,    89,   897,   301,    83,   352,  1726,   365,
-32768,   368,    89,-32768,    89,   455,-32768,-32768,   391,   455,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  1726,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  2055,  2820,  2820,  2820,   382,  2820,-32768,-32768,   334,   397,
   409,-32768,-32768,   414,   590,-32768,-32768,-32768,   109,-32768,
-32768,   404,  1096,-32768,     1,   -11,  2731,-32768,   212,   416,
   275,-32768,   378,   460,   548,   468,   493,-32768,-32768,-32768,
   415,-32768,-32768,  1810,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   297,-32768,   535,   530,-32768,-32768,   424,-32768,
-32768,   453,-32768,  1726,-32768,   437,-32768,   897,-32768,-32768,
-32768,    68,  2820,-32768,-32768,-32768,-32768,   548,-32768,-32768,
   207,  -156,    31,    30,    33,   465,   454,   461,   667,   -37,
-32768,-32768,-32768,   142,-32768,-32768,-32768,-32768,-32768,   474,
-32768,   464,   484,-32768,  2820,   490,  2820,-32768,   475,   478,
  2138,-32768,   475,   504,    91,-32768,  2820,   507,   522,  2820,
   333,   532,   541,    89,   529,    84,   534,-32768,-32768,-32768,
  1665,   528,-32768,-32768,-32768,  2820,-32768,-32768,  2138,-32768,
-32768,   333,   109,-32768,-32768,  2820,-32768,-32768,-32768,    89,
   526,  2820,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,  2820,-32768,    89,-32768,   531,   375,
-32768,-32768,-32768,-32768,   659,-32768,-32768,-32768,   542,   556,
  2820,  2820,  2820,  2820,  2820,  2820,  2820,  2820,  2820,   301,
  2820,  2820,  2820,  2820,  2820,  2820,  2820,  2820,  2820,  2820,
  2820,   274,   437,-32768,-32768,   544,-32768,  1665,-32768,  2003,
  2820,  2820,  2820,   546,-32768,   562,-32768,  2820,  2820,   565,
-32768,  2820,  2820,   -59,-32768,-32768,  2820,   569,  1301,-32768,
-32768,-32768,-32768,   568,   467,-32768,   570,-32768,-32768,-32768,
   553,   574,-32768,-32768,   575,   573,-32768,  2138,   237,-32768,
   293,-32768,   557,-32768,   897,-32768,-32768,-32768,-32768,   207,
   207,  -156,  -156,  -156,    31,   437,    31,    31,    31,    30,
    30,    33,   465,   454,   461,   667,   561,-32768,-32768,  1391,
-32768,   581,-32768,  1665,-32768,   691,-32768,-32768,-32768,  2820,
   248,   582,   583,   566,  2784,-32768,-32768,-32768,   584,   586,
-32768,   588,   591,    89,   593,-32768,-32768,-32768,-32768,-32768,
   602,    89,   605,   664,   656,   658,    89,   605,   -10,    -5,
   852,-32768,-32768,   610,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  1726,-32768,-32768,  2820,-32768,-32768,   592,   146,   611,-32768,
-32768,-32768,  2820,   604,  1575,  2820,-32768,   622,   625,-32768,
  2820,  2138,-32768,-32768,-32768,  2138,-32768,  2138,   184,-32768,
-32768,-32768,-32768,-32768,    -5,   111,-32768,-32768,-32768,-32768,
   111,    89,   695,    -5,-32768,-32768,-32768,-32768,  2897,   616,
-32768,   648,   621,   227,-32768,-32768,   639,-32768,    39,    44,
-32768,-32768,-32768,   642,  2820,  2820,-32768,-32768,   333,-32768,
  2138,-32768,   650,-32768,-32768,-32768,   326,   326,  2820,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   696,-32768,   160,-32768,
   657,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  2857,
  3095,  3095,-32768,-32768,-32768,   183,   654,-32768,-32768,   635,
    -1,   226,   253,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,  -101,-32768,   661,-32768,-32768,-32768,    89,    89,
    89,-32768,-32768,   333,-32768,   662,-32768,-32768,-32768,-32768,
-32768,-32768,   666,   668,   670,   663,-32768,-32768,  2238,-32768,
-32768,-32768,-32768,-32768,   649,   671,   -10,    -5,  2626,   286,
-32768,   286,    -1,   -41,-32768,   725,-32768,-32768,-32768,   761,
-32768,-32768,   729,   106,-32768,-32768,   533,   673,  2857,   888,
   677,   -40,    -1,-32768,-32768,-32768,     4,   649,-32768,   687,
  2973,   674,-32768,-32768,    89,  3046,  3046,  3046,  3046,   649,
-32768,-32768,   -10,-32768,   688,   134,-32768,-32768,-32768,  2820,
-32768,   690,-32768,-32768,-32768,   726,   697,  2460,   697,  2121,
-32768,-32768,   730,   785,-32768,-32768,   749,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   685,-32768,
-32768,-32768,   739,-32768,-32768,   701,-32768,  2897,-32768,  1034,
   704,-32768,   286,   337,   706,   -32,   350,   -41,-32768,    89,
   799,   799,-32768,   799,-32768,   762,-32768,-32768,   125,-32768,
-32768,   764,-32768,   850,   716,-32768,-32768,   286,-32768,   255,
   718,   -63,  2404,   776,-32768,-32768,-32768,   253,   253,-32768,
-32768,-32768,  2973,  2699,  2331,    89,-32768,   721,-32768,  2138,
    89,   286,-32768,-32768,-32768,  2121,   677,    25,   357,   369,
  2404,  2404,   739,-32768,-32768,-32768,   739,   735,-32768,  2626,
-32768,-32768,-32768,  2533,   121,   777,   649,   790,-32768,  2626,
-32768,-32768,-32768,    89,   733,-32768,   809,   809,   809,     4,
-32768,     4,-32768,-32768,     4,-32768,   817,   770,-32768,   737,
-32768,-32768,-32768,-32768,   775,-32768,-32768,-32768,-32768,-32768,
-32768,  2699,   785,-32768,    53,   880,-32768,   697,   100,-32768,
-32768,-32768,-32768,   697,-32768,  2626,   751,   727,-32768,-32768,
-32768,    89,   835,   286,-32768,   286,   286,   533,  1080,   255,
    -5,   838,   814,-32768,    89,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   853,  2857,-32768,-32768,
   833,-32768,   427,   767,-32768,   729,   171,   729,-32768,-32768,
   374,  2404,   769,-32768,-32768,-32768,-32768,   854,   778,-32768,
    89,  2404,-32768,-32768,-32768,  2626,-32768,   444,   727,-32768,
    89,   730,    89,    89,-32768,    -5,   854,   779,-32768,   730,
-32768,-32768,  2973,-32768,   449,   462,   621,-32768,   195,-32768,
    89,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   982,
   983,-32768
};

static const short yypgoto[] = {-32768,
-32768,   976,-32768,   979,-32768,-32768,-32768,-32768,-32768,   958,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   874,   162,-32768,-32768,   644,   848,   855,  -232,-32768,-32768,
   176,-32768,  -235,   875,   -15,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,  -128,-32768,-32768,-32768,   543,  -302,  -120,-32768,
   -19,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -361,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   420,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   686,-32768,   689,   538,   782,
-32768,-32768,   327,-32768,   360,  -271,   -13,   665,   -35,-32768,
  -110,-32768,  -386,-32768,   -96,-32768,   617,  -324,-32768,-32768,
    -7,   206,  -119,   289,   331,   811,   332,   196,   264,   325,
   640,   641,   653,   638,   669,-32768,   486,   675,   459,-32768,
-32768,   878,    -4,   -67,   865,    27,-32768,-32768,-32768,  1022,
-32768,-32768,   970,-32768,   385,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   818,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,   820,  -211,-32768,-32768,   471,-32768,-32768,
-32768,   812,   858,-32768,-32768,-32768,  -457,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   496,-32768,-32768,-32768,-32768,   564,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   238,
-32768,-32768,-32768,  -582,   292,-32768,   359,-32768,-32768,   288,
    99,  -222,-32768,    -8,     7,   101,-32768,-32768,-32768,-32768,
-32768,   -16,  -288,-32768,  -628,  -513,-32768,-32768,-32768,  -559,
  -641,  -518,  -121,   158,-32768,  -395,   384,-32768,-32768,-32768,
  -424,-32768,  -175,-32768,-32768,-32768,   283,-32768,-32768,-32768,
-32768,-32768,  -633,  -428,   266,-32768,-32768,  -637,-32768,-32768,
-32768,    94,-32768,-32768,-32768,-32768,-32768,-32768,   110,   117,
-32768,-32768,  -730,   246,   256,   347,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,  -275,-32768,  -675,  -475,   273,
   276,-32768,   381,   463,  -739,-32768,  -815,-32768,-32768,  -830
};


#define	YYLAST		3317


static const short yytable[] = {    24,
    25,    24,    95,   772,    52,   473,   241,    56,   357,   828,
   188,   215,    20,    60,    30,   358,   483,   328,   277,   520,
   209,   352,    77,   846,   380,  -193,    51,    39,   469,    51,
    39,    20,   404,   329,   211,  -647,     3,   484,   775,    52,
    20,   720,   605,   575,    51,   655,   765,   605,    20,   684,
   658,   364,   365,   142,    78,   374,    92,   775,   463,   102,
   369,    51,   308,   309,   310,    61,   313,   931,   370,   477,
   142,   371,   804,   800,   707,    20,    62,    63,     7,   765,
    20,   142,   366,     2,    64,   465,   933,    65,   817,   375,
   781,   781,    66,   885,   768,   828,   567,   886,    67,  -500,
   120,   128,   367,   188,   215,   520,   489,    92,   713,     5,
    52,   189,  -520,   209,   599,   368,   653,   206,    60,   568,
   321,   532,   778,   213,    92,    20,   221,   211,   974,   721,
   274,   775,    51,   322,   659,    92,   847,   246,   352,   246,
   813,     3,   660,   782,   782,   975,   149,   976,   284,   584,
   284,   570,  -500,    59,   594,    51,   595,   596,   797,   528,
   570,   537,   785,   381,   890,   150,   852,   306,   895,    45,
    61,   215,   401,    31,   900,     1,   142,   676,   520,   587,
   209,    62,    63,     7,   775,    38,  -197,   917,   831,   114,
    32,   215,    65,   418,   211,   296,    20,    66,     3,   215,
   209,   798,   531,    67,   189,   107,   812,   307,   209,   121,
   206,   962,   549,   330,   211,    69,   213,    40,   899,   221,
   927,   970,   211,   880,   469,    79,   908,   491,   909,    80,
    92,   910,   489,   896,   372,   373,   918,  -500,   923,   919,
     7,   436,   437,   438,   439,   439,   439,   439,   439,   439,
  -520,   439,   439,   439,   439,   439,   439,   439,   439,   439,
   439,   783,   897,   787,   829,  -197,   924,   604,   215,   468,
   215,   389,   604,   306,   783,   788,    54,   209,   275,   209,
   971,  -197,   406,   213,   107,   577,   221,   486,   392,   215,
  -500,   211,   785,   211,   849,   790,   185,   206,   209,   416,
   107,  -500,  -520,   213,  -500,   985,   221,   393,   215,   791,
   527,   213,   211,   242,   221,  -520,   570,   209,   597,   598,
   707,    34,    20,   986,   280,   422,   599,   815,   708,    20,
   -31,   211,   677,   816,   446,    43,   214,    20,    35,   678,
   215,    58,   246,   818,   215,   492,   631,   493,   458,   209,
   829,   459,   679,   209,   494,  -520,    51,   680,    59,    46,
  -334,   580,   495,   211,  -334,  -334,  -520,   211,  -334,  -520,
   496,   595,   596,  -334,   206,    47,   206,   143,    48,   786,
   213,   144,   213,   221,    18,   935,   229,   935,    75,   497,
   230,   231,    18,   787,   232,   206,    59,   701,   498,   499,
    18,   213,  -528,   103,   221,   788,   916,  -127,   525,   107,
  -127,  -127,   789,   439,   500,   215,   361,   362,   363,   216,
   213,   215,   215,   221,   209,   790,   215,   108,   215,   214,
   209,   209,   526,   716,   717,   209,   144,   209,   211,   791,
   109,   652,   570,   540,   211,   211,   206,   541,   110,   211,
   206,   211,   213,   142,   111,   221,   213,   129,   677,   221,
   667,   217,   718,   719,   229,   678,   215,   491,   230,   231,
  -128,   215,   232,  -128,  -128,   209,   701,  -366,   679,   936,
   209,   938,   288,   773,   130,  -336,   288,   552,   631,   211,
   -72,    20,   565,   136,   211,   571,   214,   162,   163,   164,
   165,   166,   167,   168,   776,  -522,   858,    92,   859,   145,
   169,   351,   216,    46,   138,   289,   214,   827,  -522,   293,
   146,   206,   588,   776,   214,   729,   590,   213,   592,    47,
   221,   799,    48,   213,   213,  -653,  -653,   221,   213,   603,
   213,   221,   238,   221,   603,   631,   185,   827,   853,   854,
   571,   243,   333,   239,   217,  -643,  -643,   607,  -522,   571,
   244,   442,   443,   444,   571,   278,   334,   881,   882,  -522,
   785,   668,  -522,  -125,   656,   656,  -125,  -125,   213,   216,
   672,   673,   281,   213,   282,   492,   221,   493,   292,   219,
   870,   872,   315,   214,   494,   214,   -87,   776,   335,   216,
   336,   337,   495,   827,   571,   338,   316,   216,   339,   318,
   496,   319,   340,   332,   214,   571,   571,   571,   341,   229,
   326,   217,   776,   230,   231,   960,   854,   232,   342,   497,
   346,   343,   445,   214,   447,   448,   449,   353,   498,   499,
   355,   217,   972,   973,   724,   725,   728,   983,   854,   217,
   776,   356,   287,   150,   500,  -126,   377,   786,  -126,  -126,
   984,   854,   378,  -123,   571,   214,  -123,  -123,   376,   214,
   379,   787,   383,   571,   571,   774,   216,   571,   216,   385,
   501,   384,   219,   788,   799,   387,   799,   330,  -124,   799,
   789,  -124,  -124,   388,   571,   440,   441,   216,   450,   451,
   215,   391,   571,   790,   398,   957,   571,   808,   809,   209,
   807,   571,   571,   571,   571,   834,   216,   791,   217,   399,
   217,   705,   706,   211,   810,   811,   835,   405,   937,   402,
   937,   941,   407,   571,    93,   571,   906,   907,   403,   217,
   214,   836,   413,   423,   344,   430,   214,   214,   216,   219,
   982,   214,   216,   214,   432,   435,   434,   478,   217,   464,
   481,   556,   475,   571,   487,   571,   490,   521,   571,   219,
   522,  -198,   524,   523,   530,   855,   533,   219,   536,   538,
   542,   543,   545,   544,   546,    93,   547,   572,   550,   548,
   217,   214,   557,   571,   217,   207,   214,   551,   571,   553,
   878,   555,    93,   564,   558,   576,   581,   579,   571,   571,
   571,   725,   213,    93,   559,   221,   879,   571,   583,   585,
   586,   571,   650,   216,   560,   561,   571,   571,   649,   216,
   216,   837,   608,   651,   216,   571,   216,   654,   838,   571,
   663,   675,   593,   669,   839,   571,   219,   712,   219,   901,
   840,   609,   491,   711,   698,   571,   630,   571,   723,   730,
   571,   731,   541,   767,   599,   217,   732,   219,   733,  -519,
   713,   217,   217,   784,   216,   796,   217,   571,   217,   216,
   803,   841,   795,   806,   814,   819,   219,   821,   207,   842,
   843,   571,   832,   831,   822,   833,   683,   932,   839,   571,
   847,   571,   571,   850,   851,   856,   571,   700,    93,   860,
   955,   862,   863,   156,   864,   867,   217,   865,   219,   877,
   887,   217,   219,   571,  -647,  -545,   251,   707,   898,   160,
   902,   903,   911,    20,   912,   914,   915,   571,   921,   162,
   163,   164,   165,   166,   167,   168,   967,   571,   928,   741,
   934,   571,   169,   951,   952,    46,   932,    60,   932,   571,
   956,   571,   305,   959,   961,   769,   963,   683,   571,   683,
   492,    47,   493,   964,    48,   207,   967,   966,   981,   494,
     3,   991,   992,    27,    26,    36,   700,   495,   331,   137,
   429,   247,   690,   219,   683,   496,   245,   713,   630,   219,
   219,   148,   535,   703,   219,   666,   219,   539,   419,    61,
   476,   420,  -545,   327,   497,   452,   455,   453,   582,   427,
    62,    63,     7,   498,   499,   214,  -545,   700,   114,   251,
   454,    65,   286,   295,   331,  -545,    66,    29,  -545,   500,
   101,   348,    67,   350,   219,  -545,   314,   354,   456,   219,
   661,   734,   207,   876,   207,   630,   606,   700,  -545,   848,
   683,   566,   977,   690,   939,   690,   386,   866,   305,   805,
    20,   861,  -545,   207,   989,   978,   883,   594,   397,   595,
   596,   400,   703,   980,   824,   683,   873,   884,   802,   874,
   690,     0,   735,   715,   181,     0,     0,   414,     0,     0,
     0,     0,     0,   182,   183,   184,     0,   421,   216,   683,
   248,     0,     0,   700,     0,   186,     0,   785,     0,     0,
   823,     0,   825,   703,   207,     0,     0,     0,   207,     0,
     0,     0,    20,     0,     0,     0,     0,     0,   162,   163,
   164,   165,   166,   167,   168,   610,     0,   683,     0,   683,
   217,   169,   683,   703,    46,     0,   690,   611,     0,     0,
   612,     0,   457,     0,     0,     0,     0,     0,     0,   -32,
    47,     0,   472,    48,   474,     0,   942,     0,     0,   479,
   480,   690,     0,   482,     0,    93,     0,     0,   613,   614,
   570,   683,     0,   683,   683,     0,     0,     0,   948,   207,
     0,     0,     0,     0,   786,   690,   677,   615,     0,   703,
     0,   616,   617,   678,     0,   700,   251,     0,   787,     0,
     0,     0,     0,   618,     0,   619,   679,  -528,     0,     0,
   788,   699,     0,     0,     0,     1,     0,   789,     0,     0,
     0,   621,   622,   690,     0,   690,     2,     0,   690,   599,
   790,   397,     0,   948,   624,   625,   474,     0,     3,     0,
     0,     0,     0,     0,   791,     0,     0,     0,     4,     0,
   943,   922,     5,     0,     0,     0,     0,   926,   219,     0,
   929,     0,     0,     0,     0,     0,     0,   690,     0,   690,
   690,     0,     0,   181,     0,     0,     6,     0,     0,     0,
     7,   408,   182,     0,     0,   578,    81,   153,    82,     0,
   154,   703,     0,    83,   186,     0,   155,   156,   157,     0,
    84,   158,     0,     0,     0,     0,     0,    85,   159,     0,
     0,     0,     0,   160,   161,     0,     0,    20,     0,     0,
     0,    86,     0,   162,   163,   164,   165,   166,   167,   168,
    87,     0,     0,     0,     0,     0,   169,     0,     0,    46,
     0,     0,     0,     0,     0,     0,   664,     0,     0,     0,
   170,     0,     0,    88,     0,    47,   171,   172,    48,   173,
   674,     0,     0,   174,     0,     0,     0,     0,     0,   175,
     0,   408,   176,   177,     0,     0,    81,   153,    82,     0,
   154,     0,     0,    83,   178,   179,   155,   156,   157,     0,
    84,   158,     0,     0,     0,     0,     0,    85,   159,     0,
     0,     0,     0,   160,   161,     0,     0,    20,     0,     0,
     0,    86,     0,   162,   163,   164,   165,   166,   167,   168,
    87,     0,     0,     0,     0,     0,   169,     0,     0,    46,
     0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
   170,     0,     0,    88,    83,    47,   171,   172,    48,   173,
    60,    84,     0,   174,     0,     0,     0,     0,    85,   175,
     0,     0,   176,   177,     0,     0,     0,     0,    20,     0,
     0,     0,    86,     3,   178,   179,   180,     0,   181,     0,
     0,    87,     0,     0,     0,     0,     0,   182,   183,   184,
    46,     0,     0,     0,   185,   488,     0,     0,     0,   186,
     0,     0,    61,     0,    88,     0,    47,     0,     0,    48,
     0,     0,     0,    62,    63,     7,     0,     0,    89,     0,
     0,    64,     0,     0,    65,     0,     0,     0,     0,    66,
     0,     0,     0,    90,     0,    67,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   408,     0,     0,     0,     0,
    81,   153,    82,     0,   154,     0,   180,    83,   181,     0,
   155,   156,   157,     0,    84,   158,     0,   182,   183,   184,
     0,    85,   159,     0,   185,   -89,     0,   160,   161,   186,
     0,    20,     0,     0,     0,    86,     0,   162,   163,   164,
   165,   166,   167,   168,    87,     0,     0,     0,     0,     0,
   169,     0,     0,    46,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   170,     0,     0,    88,     0,    47,
   171,   172,    48,   173,     0,     0,     0,   174,     0,     0,
     0,     0,     0,   175,     0,   408,   176,   177,     0,     0,
    81,   153,    82,     0,   154,     0,     0,    83,   178,   179,
   155,   156,   157,     0,    84,   158,     0,     0,     0,     0,
     0,    85,   159,     0,     0,     0,     0,   160,   161,     0,
     0,    20,     0,     0,     0,    86,     0,   162,   163,   164,
   165,   166,   167,   168,    87,     0,     0,     0,     0,     0,
   169,     0,     0,    46,     0,     0,     0,     0,     0,     0,
     0,    81,     0,    82,   170,     0,     0,    88,    83,    47,
   171,   172,    48,   173,     0,    84,     0,   174,     0,     0,
     0,     0,    85,   175,     0,     0,   176,   177,     0,     0,
     0,     0,    20,     0,     0,     0,    86,     0,   178,   179,
   180,     0,   181,     0,     0,    87,     0,     0,     0,     0,
     0,   182,   183,   184,    46,     0,     0,     0,   185,   -90,
     0,     0,     0,   186,     0,     0,     0,     0,    88,     0,
    47,     0,     0,    48,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    81,   153,    82,     0,   154,
     0,     0,    83,     0,     0,   155,   156,   157,     0,    84,
   158,     0,     0,     0,     0,     0,    85,   159,     0,     0,
     0,     0,   160,   161,     0,     0,    20,     0,     0,     0,
    86,     0,   162,   163,   164,   165,   166,   167,   168,    87,
   180,     0,   181,     0,     0,   169,     0,     0,    46,     0,
     0,   182,   183,   184,     0,     0,     0,     0,   185,   170,
     0,     0,    88,   186,    47,   171,   172,    48,   173,     0,
     0,     0,   174,     0,     0,     0,     0,     0,   175,   229,
     0,   176,   177,   230,   231,     0,     0,   232,     0,     0,
     0,     0,  -366,   178,   179,    81,   153,    82,     0,   154,
     0,     0,    83,     0,     0,   155,   156,   157,     0,    84,
   158,     0,     0,     0,     0,     0,    85,   159,     0,     0,
     0,     0,   160,   161,     0,     0,    20,     0,     0,     0,
    86,     0,   162,   163,   164,   165,   166,   167,   168,    87,
     0,     0,     0,     0,     0,   169,     0,     0,    46,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   170,
     0,     0,    88,     0,    47,   171,   172,    48,   173,     0,
     0,     0,   174,     0,     0,     0,     0,     0,   175,     0,
     0,   176,   177,     0,     0,   180,     0,   181,    81,     0,
    82,     0,     0,   178,   179,    83,   182,   183,   184,   156,
     0,     0,    84,   185,     0,     0,     0,     0,   186,    85,
     0,     0,     0,     0,     0,   160,     0,     0,     0,    20,
     0,     0,     0,    86,     0,   162,   163,   164,   165,   166,
   167,   168,    87,     0,     0,     0,     0,     0,   169,     0,
    81,    46,    82,     0,     0,     0,     0,    83,     0,     0,
     0,   156,     0,     0,    84,    88,     0,    47,     0,     0,
    48,    85,     0,     0,     0,     0,     0,   160,     0,     0,
     0,    20,     0,     0,     0,    86,     0,   162,   163,   164,
   165,   166,   167,   168,    87,   180,     0,   181,     0,     0,
   169,     0,     0,    46,     0,     0,   182,   183,   184,     0,
     0,     0,     0,   185,     0,     0,     0,    88,   186,    47,
     0,     0,    48,     0,     0,     0,     0,     0,   734,     0,
     0,     0,     0,     0,   153,     0,     0,   154,     0,     0,
     0,     0,     0,   155,   156,   157,     0,    20,   158,     0,
     0,     0,     0,     0,   594,   159,   595,   596,     0,     0,
   160,   161,     0,     0,    20,     0,     0,     0,     0,   735,
   162,   163,   164,   165,   166,   167,   168,     0,     0,     0,
     0,     0,     0,   169,     0,     0,    46,     0,   467,     0,
   181,     0,     0,     0,     0,     0,     0,   170,     0,   182,
   183,   184,    47,   171,   172,    48,   173,     0,     0,     0,
   174,   186,     0,     0,     0,     0,   175,     0,     0,   176,
   177,     0,   610,     0,     0,     0,     0,     0,     0,     0,
     0,   178,   179,     0,   611,     0,     0,   612,     0,     0,
     0,     0,   181,   737,     0,   734,     0,     0,     0,     0,
     0,   182,   183,   184,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   186,    20,   613,   614,   570,     0,     0,
   738,   594,     0,   595,   596,     0,     0,     0,     0,     0,
     0,     0,     0,   677,   615,     0,   735,     0,   616,   617,
   678,     0,     0,     0,     0,     0,   739,     0,     0,     0,
   618,     0,   619,   679,     0,     0,     0,     0,   826,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   621,   622,
     0,     0,     0,   180,     0,   181,   599,     0,     0,     0,
     0,   624,   625,   741,   182,   183,   184,     0,   734,   610,
     0,   185,     0,     0,     0,     0,   186,     0,     0,     0,
     0,   611,     0,   736,   612,     0,     0,    20,     0,     0,
   737,     0,     0,     0,   594,     0,   595,   596,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   735,
     0,     0,   613,   614,   570,     0,     0,   738,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   615,     0,     0,     0,   616,   617,     0,     0,     0,
     0,   734,     0,   739,     0,     0,     0,   618,     0,   619,
     0,     0,     0,     0,     0,   740,     0,     0,     0,     0,
    20,     0,   610,     0,     0,   621,   622,   594,     0,   595,
   596,     0,     0,   599,   611,     0,   875,   612,   624,   625,
   741,     0,   735,   737,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   734,     0,     0,
     0,     0,     0,     0,     0,   613,   614,   570,     0,     0,
   738,     0,     0,     0,     0,     0,    20,     0,     0,     0,
     0,     0,     0,   594,   615,   595,   596,     0,   616,   617,
     0,     0,     0,     0,     0,   610,   739,     0,   735,     0,
   618,     0,   619,     0,     0,     0,     0,   611,   740,     0,
   612,     0,     0,     0,     0,     0,   737,     0,   621,   622,
     0,     0,     0,     0,     0,     0,   599,     0,     0,     0,
   734,   624,   625,   741,     0,     0,     0,     0,   613,   614,
   570,     0,     0,   738,     0,     0,     0,     0,     0,    20,
     0,   610,     0,     0,     0,     0,   594,   615,   595,   596,
     0,   616,   617,   611,     0,     0,   612,     0,     0,   739,
     0,   735,   737,   618,     0,   619,     0,     0,     0,     0,
     0,   740,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   621,   622,     0,   613,   614,   570,     0,     0,   599,
     0,     0,     0,     0,   624,   625,   741,     0,     0,     0,
     0,     0,     0,   615,     0,     0,     0,   616,   617,   891,
     0,   892,     0,   734,   610,   739,     0,     0,     0,   618,
     0,   619,     0,     0,     0,     0,   611,   740,     0,   612,
     0,     0,    20,     0,     0,     0,     0,   621,   622,   594,
     0,   595,   596,     0,     0,   599,     0,     0,     0,     0,
   624,   625,   741,     0,   735,     0,     0,   613,   614,   570,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   615,     0,   893,     0,
   616,   617,     0,     0,     0,     0,   734,     0,     0,     0,
     0,     0,   618,     0,   619,     0,     0,     0,     0,     0,
   770,     0,     0,     0,     0,    20,     0,   610,     0,     0,
   621,   622,   594,     0,   595,   596,     0,   156,   599,   611,
     0,     0,   612,   624,   625,     0,     0,   735,     0,     0,
     0,     0,     0,   160,     0,     0,     0,    20,     0,     0,
     0,     0,     0,   162,   163,   164,   165,   166,   167,   168,
   613,   614,   570,     0,     0,     0,   169,     0,     0,    46,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   615,
   156,     0,     0,   616,   617,    47,     0,     0,    48,     0,
   610,     0,     0,     0,     0,   618,   160,   619,     0,     0,
    20,     0,   611,   770,     0,   612,   162,   163,   164,   165,
   166,   167,   168,   621,   622,     0,   156,     0,     0,   169,
     0,   599,    46,     0,     0,     0,   624,   625,     0,     0,
     0,     0,   160,   613,   614,   570,    20,     0,    47,     0,
     0,    48,   162,   163,   164,   165,   166,   167,   168,     0,
     0,     0,   615,     0,     0,   169,   616,   617,    46,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   618,     0,
   619,     0,     0,    20,    47,     0,   620,    48,     0,     0,
   594,     0,   595,   596,     0,     0,   621,   622,     0,     0,
     0,     0,     0,     0,   599,     0,     0,     0,     0,   624,
   625,     0,     0,     0,     0,     0,     0,     0,   181,     0,
     0,     0,     0,    20,     0,     0,     0,   182,   183,   184,
   594,     0,   595,   596,     0,     0,     0,     0,   108,   186,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   610,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   611,   181,     0,   612,     0,     0,     0,     0,     0,     0,
   182,   183,   184,     0,     0,     0,     0,     0,     0,     0,
     0,   281,   186,     0,     0,     0,     0,     0,   610,    20,
     0,   613,   614,   570,     0,     0,   594,   181,   595,   596,
   611,     0,     0,   612,     0,     0,   182,   183,   184,   677,
   615,     0,     0,     0,   616,   617,   678,     0,   186,     0,
     0,     0,     0,     0,     0,     0,   618,     0,   619,   679,
     0,   613,   614,   570,   699,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   621,   622,     0,     0,     0,     0,
   615,     0,   599,     0,   616,   617,     0,   624,   625,     0,
     0,     0,    20,     0,   610,     0,   618,     0,   619,   594,
     0,   595,   596,     0,   620,     0,   611,     0,     0,   612,
     0,     0,     0,     0,   621,   622,   623,     0,     0,     0,
     0,     0,   599,     0,     0,     0,     0,   624,   625,     0,
     0,     0,     0,     0,     0,     0,     0,   613,   614,   570,
     0,    20,     0,     0,     0,     0,     0,     0,   594,     0,
   595,   596,     0,     0,     0,     0,   615,     0,     0,     0,
   616,   617,     0,     0,     0,     0,     0,   610,     0,     0,
     0,     0,   618,     0,   619,     0,     0,     0,     0,   611,
   620,     0,   612,     0,     0,     0,     0,     0,     0,     0,
   621,   622,     0,     0,     0,     0,     0,     0,   599,     0,
     0,     0,     0,   624,   625,     0,     0,     0,     0,     0,
   613,   614,   570,     0,     0,     0,   610,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   611,   615,
     0,   612,     0,   616,   617,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   618,     0,   619,     0,     0,
     0,     0,     0,   620,     0,     0,     0,     0,     0,   613,
   614,   570,     0,   621,   622,     0,     0,     0,     0,     0,
     0,   599,     0,     0,     0,     0,     0,   625,   615,     0,
     0,     0,   616,   617,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   618,     0,   619,     0,     0,     0,
     0,     0,   620,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   599,     0,     0,     0,     0,     0,   625
};

static const short yycheck[] = {     4,
     5,     6,    70,   679,    40,   392,   135,    43,   244,   740,
   131,   131,    37,     3,    19,   248,   403,    17,   147,   415,
   131,   233,    58,   763,    62,    37,    40,    32,   390,    43,
    35,    37,   304,    33,   131,    37,    26,    97,   680,    75,
    37,   143,   556,   501,    58,     7,   675,   561,    37,   609,
     7,   208,   209,   121,    59,    23,    70,   699,   383,    75,
    31,    75,   182,   183,   184,    55,   186,   898,    39,   394,
   138,    42,   710,   707,   138,    37,    66,    67,    68,   708,
    37,   149,    52,    14,    74,   388,   902,    77,   726,    57,
   132,   132,    82,   833,   677,   826,   107,   837,    88,   132,
   105,   106,    72,   224,   224,   501,   409,   121,   110,    40,
   146,   131,   145,   224,   216,    85,   574,   131,     3,   130,
    12,   446,   682,   131,   138,    37,   131,   224,   959,   643,
   146,   773,   146,    25,    91,   149,   200,   142,   350,   144,
   723,    26,    99,   185,   185,   961,   198,   963,   153,   536,
   155,   157,   185,   213,    44,   169,    46,    47,   199,   431,
   157,   464,    38,   201,   840,   217,   199,   181,   844,   196,
    55,   291,   301,   196,   850,     3,   244,    18,   574,   541,
   291,    66,    67,    68,   826,   210,   198,   135,   164,    74,
   213,   311,    77,   322,   291,   169,    37,    82,    26,   319,
   311,   198,   435,    88,   224,   217,   720,   181,   319,   198,
   224,   942,   484,   213,   311,    54,   224,    24,   847,   224,
   896,   952,   319,   199,   586,   215,   860,     1,   862,    68,
   244,   865,   535,   113,   205,   206,   184,   132,   139,   187,
    68,   361,   362,   363,   364,   365,   366,   367,   368,   369,
   145,   371,   372,   373,   374,   375,   376,   377,   378,   379,
   380,   690,   142,   139,   740,   198,   167,   556,   388,   390,
   390,   291,   561,   287,   703,   151,   214,   388,   196,   390,
   956,   198,   199,   291,   217,   521,   291,   407,   198,   409,
   185,   388,    38,   390,   770,   171,   214,   311,   409,   319,
   217,   196,   132,   311,   199,   111,   311,   217,   428,   185,
    18,   319,   409,   138,   319,   145,   157,   428,   208,   209,
   138,   196,    37,   129,   149,   330,   216,   194,   146,    37,
   215,   428,   173,   200,   370,    24,   131,    37,   213,   180,
   460,   200,   347,   730,   464,   119,   569,   121,    75,   460,
   826,    78,   193,   464,   128,   185,   370,   198,   213,    59,
    90,   216,   136,   460,    94,    95,   196,   464,    98,   199,
   144,    46,    47,   103,   388,    75,   390,   196,    78,   125,
   388,   200,   390,   388,     0,   904,    90,   906,    35,   163,
    94,    95,     8,   139,    98,   409,   213,   620,   172,   173,
    16,   409,   148,   214,   409,   151,   882,   196,   428,   217,
   199,   200,   158,   533,   188,   535,   210,   211,   212,   131,
   428,   541,   542,   428,   535,   171,   546,   218,   548,   224,
   541,   542,   196,   208,   209,   546,   200,   548,   535,   185,
   217,   215,   157,   196,   541,   542,   460,   200,   217,   546,
   464,   548,   460,   521,   214,   460,   464,   218,   173,   464,
   589,   131,   210,   211,    90,   180,   586,     1,    94,    95,
   196,   591,    98,   199,   200,   586,   699,   103,   193,   904,
   591,   906,   156,   198,   218,   215,   160,   492,   711,   586,
   214,    37,   497,   215,   591,   500,   291,    43,    44,    45,
    46,    47,    48,    49,   680,   132,   782,   521,   784,   197,
    56,   215,   224,    59,   198,   156,   311,   740,   145,   160,
    80,   535,   542,   699,   319,   654,   546,   535,   548,    75,
   535,   707,    78,   541,   542,   199,   200,   542,   546,   556,
   548,   546,   215,   548,   561,   768,   214,   770,   199,   200,
   555,   199,     5,   220,   224,   199,   200,   562,   185,   564,
   200,   366,   367,   368,   569,   214,    19,   199,   200,   196,
    38,   591,   199,   196,   579,   580,   199,   200,   586,   291,
   597,   598,   218,   591,   217,   119,   591,   121,   198,   131,
   813,   814,   196,   388,   128,   390,   215,   773,    51,   311,
    53,    54,   136,   826,   609,    58,   198,   319,    61,   196,
   144,    22,    65,   198,   409,   620,   621,   622,    71,    90,
   217,   291,   798,    94,    95,   199,   200,    98,    81,   163,
   216,    84,   369,   428,   371,   372,   373,   103,   172,   173,
   217,   311,   199,   200,   649,   650,   651,   199,   200,   319,
   826,   199,   198,   217,   188,   196,   203,   125,   199,   200,
   199,   200,   202,   196,   669,   460,   199,   200,   204,   464,
     4,   139,   199,   678,   679,   680,   388,   682,   390,   196,
   214,   218,   224,   151,   860,   196,   862,   213,   196,   865,
   158,   199,   200,   216,   699,   364,   365,   409,   374,   375,
   820,   198,   707,   171,   198,   928,   711,   716,   717,   820,
   715,   716,   717,   718,   719,    31,   428,   185,   388,   198,
   390,   621,   622,   820,   718,   719,    42,   199,   904,   198,
   906,   907,   199,   738,    70,   740,   858,   859,   198,   409,
   535,    57,   215,   218,   197,   215,   541,   542,   460,   291,
   973,   546,   464,   548,    96,   200,   215,   196,   428,   216,
   196,   106,   217,   768,   196,   770,   199,   198,   773,   311,
   218,   198,   200,   199,   218,   780,   216,   319,   198,    89,
   199,   199,   199,   218,   199,   121,   199,   500,   196,   199,
   460,   586,   137,   798,   464,   131,   591,   196,   803,   195,
   820,   138,   138,   146,   149,   196,   196,   216,   813,   814,
   815,   816,   820,   149,   159,   820,   821,   822,   215,   198,
   196,   826,   175,   535,   169,   170,   831,   832,   213,   541,
   542,   147,   138,   213,   546,   840,   548,   199,   154,   844,
   199,   146,   555,   194,   160,   850,   388,   213,   390,   854,
   166,   564,     1,   200,   198,   860,   569,   862,   198,   198,
   865,   196,   200,   193,   216,   535,   199,   409,   199,   145,
   110,   541,   542,   145,   586,   199,   546,   882,   548,   591,
   194,   197,   210,   210,   197,   196,   428,   162,   224,   205,
   206,   896,   108,   164,   198,   147,   609,   902,   160,   904,
   200,   906,   907,   200,   199,   107,   911,   620,   244,   148,
   915,   148,    63,    17,   199,   140,   586,   200,   460,   199,
   186,   591,   464,   928,    37,    38,   145,   138,   152,    33,
   198,   123,   116,    37,   165,   199,   162,   942,    59,    43,
    44,    45,    46,    47,    48,    49,   951,   952,   198,   223,
   116,   956,    56,   116,   141,    59,   961,     3,   963,   964,
   108,   966,   181,   131,   198,   678,   198,   680,   973,   682,
   119,    75,   121,   120,    78,   311,   981,   200,   200,   128,
    26,     0,     0,     8,     6,    28,   699,   136,   207,   116,
   347,   144,   609,   535,   707,   144,   142,   110,   711,   541,
   542,   127,   460,   620,   546,   586,   548,   470,   323,    55,
   394,   323,   125,   203,   163,   376,   379,   377,   533,   345,
    66,    67,    68,   172,   173,   820,   139,   740,    74,   248,
   378,    77,   155,   169,   253,   148,    82,    16,   151,   188,
    71,   224,    88,   224,   586,   158,   189,   236,   380,   591,
   580,    18,   388,   816,   390,   768,   561,   770,   171,   768,
   773,   498,   964,   680,   907,   682,   285,   802,   287,   711,
    37,   789,   185,   409,   981,   966,   831,    44,   297,    46,
    47,   300,   699,   967,   738,   798,   814,   832,   708,   814,
   707,    -1,    59,   631,   198,    -1,    -1,   316,    -1,    -1,
    -1,    -1,    -1,   207,   208,   209,    -1,   326,   820,   822,
   214,    -1,    -1,   826,    -1,   219,    -1,    38,    -1,    -1,
   737,    -1,   739,   740,   460,    -1,    -1,    -1,   464,    -1,
    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    43,    44,
    45,    46,    47,    48,    49,   112,    -1,   860,    -1,   862,
   820,    56,   865,   770,    59,    -1,   773,   124,    -1,    -1,
   127,    -1,   381,    -1,    -1,    -1,    -1,    -1,    -1,   215,
    75,    -1,   391,    78,   393,    -1,    97,    -1,    -1,   398,
   399,   798,    -1,   402,    -1,   521,    -1,    -1,   155,   156,
   157,   904,    -1,   906,   907,    -1,    -1,    -1,   911,   535,
    -1,    -1,    -1,    -1,   125,   822,   173,   174,    -1,   826,
    -1,   178,   179,   180,    -1,   928,   435,    -1,   139,    -1,
    -1,    -1,    -1,   190,    -1,   192,   193,   148,    -1,    -1,
   151,   198,    -1,    -1,    -1,     3,    -1,   158,    -1,    -1,
    -1,   208,   209,   860,    -1,   862,    14,    -1,   865,   216,
   171,   470,    -1,   966,   221,   222,   475,    -1,    26,    -1,
    -1,    -1,    -1,    -1,   185,    -1,    -1,    -1,    36,    -1,
   191,   888,    40,    -1,    -1,    -1,    -1,   894,   820,    -1,
   897,    -1,    -1,    -1,    -1,    -1,    -1,   904,    -1,   906,
   907,    -1,    -1,   198,    -1,    -1,    64,    -1,    -1,    -1,
    68,     1,   207,    -1,    -1,   524,     6,     7,     8,    -1,
    10,   928,    -1,    13,   219,    -1,    16,    17,    18,    -1,
    20,    21,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,
    -1,    -1,    -1,    33,    34,    -1,    -1,    37,    -1,    -1,
    -1,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,
    -1,    -1,    -1,    -1,    -1,    -1,   585,    -1,    -1,    -1,
    70,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
   599,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    89,
    -1,     1,    92,    93,    -1,    -1,     6,     7,     8,    -1,
    10,    -1,    -1,    13,   104,   105,    16,    17,    18,    -1,
    20,    21,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,
    -1,    -1,    -1,    33,    34,    -1,    -1,    37,    -1,    -1,
    -1,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,     8,
    70,    -1,    -1,    73,    13,    75,    76,    77,    78,    79,
     3,    20,    -1,    83,    -1,    -1,    -1,    -1,    27,    89,
    -1,    -1,    92,    93,    -1,    -1,    -1,    -1,    37,    -1,
    -1,    -1,    41,    26,   104,   105,   196,    -1,   198,    -1,
    -1,    50,    -1,    -1,    -1,    -1,    -1,   207,   208,   209,
    59,    -1,    -1,    -1,   214,   215,    -1,    -1,    -1,   219,
    -1,    -1,    55,    -1,    73,    -1,    75,    -1,    -1,    78,
    -1,    -1,    -1,    66,    67,    68,    -1,    -1,    87,    -1,
    -1,    74,    -1,    -1,    77,    -1,    -1,    -1,    -1,    82,
    -1,    -1,    -1,   102,    -1,    88,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
     6,     7,     8,    -1,    10,    -1,   196,    13,   198,    -1,
    16,    17,    18,    -1,    20,    21,    -1,   207,   208,   209,
    -1,    27,    28,    -1,   214,   215,    -1,    33,    34,   219,
    -1,    37,    -1,    -1,    -1,    41,    -1,    43,    44,    45,
    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
    56,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    70,    -1,    -1,    73,    -1,    75,
    76,    77,    78,    79,    -1,    -1,    -1,    83,    -1,    -1,
    -1,    -1,    -1,    89,    -1,     1,    92,    93,    -1,    -1,
     6,     7,     8,    -1,    10,    -1,    -1,    13,   104,   105,
    16,    17,    18,    -1,    20,    21,    -1,    -1,    -1,    -1,
    -1,    27,    28,    -1,    -1,    -1,    -1,    33,    34,    -1,
    -1,    37,    -1,    -1,    -1,    41,    -1,    43,    44,    45,
    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
    56,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,     6,    -1,     8,    70,    -1,    -1,    73,    13,    75,
    76,    77,    78,    79,    -1,    20,    -1,    83,    -1,    -1,
    -1,    -1,    27,    89,    -1,    -1,    92,    93,    -1,    -1,
    -1,    -1,    37,    -1,    -1,    -1,    41,    -1,   104,   105,
   196,    -1,   198,    -1,    -1,    50,    -1,    -1,    -1,    -1,
    -1,   207,   208,   209,    59,    -1,    -1,    -1,   214,   215,
    -1,    -1,    -1,   219,    -1,    -1,    -1,    -1,    73,    -1,
    75,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,     6,     7,     8,    -1,    10,
    -1,    -1,    13,    -1,    -1,    16,    17,    18,    -1,    20,
    21,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,    -1,
    -1,    -1,    33,    34,    -1,    -1,    37,    -1,    -1,    -1,
    41,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
   196,    -1,   198,    -1,    -1,    56,    -1,    -1,    59,    -1,
    -1,   207,   208,   209,    -1,    -1,    -1,    -1,   214,    70,
    -1,    -1,    73,   219,    75,    76,    77,    78,    79,    -1,
    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    89,    90,
    -1,    92,    93,    94,    95,    -1,    -1,    98,    -1,    -1,
    -1,    -1,   103,   104,   105,     6,     7,     8,    -1,    10,
    -1,    -1,    13,    -1,    -1,    16,    17,    18,    -1,    20,
    21,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,    -1,
    -1,    -1,    33,    34,    -1,    -1,    37,    -1,    -1,    -1,
    41,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,    -1,
    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    89,    -1,
    -1,    92,    93,    -1,    -1,   196,    -1,   198,     6,    -1,
     8,    -1,    -1,   104,   105,    13,   207,   208,   209,    17,
    -1,    -1,    20,   214,    -1,    -1,    -1,    -1,   219,    27,
    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    37,
    -1,    -1,    -1,    41,    -1,    43,    44,    45,    46,    47,
    48,    49,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,
     6,    59,     8,    -1,    -1,    -1,    -1,    13,    -1,    -1,
    -1,    17,    -1,    -1,    20,    73,    -1,    75,    -1,    -1,
    78,    27,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,
    -1,    37,    -1,    -1,    -1,    41,    -1,    43,    44,    45,
    46,    47,    48,    49,    50,   196,    -1,   198,    -1,    -1,
    56,    -1,    -1,    59,    -1,    -1,   207,   208,   209,    -1,
    -1,    -1,    -1,   214,    -1,    -1,    -1,    73,   219,    75,
    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    18,    -1,
    -1,    -1,    -1,    -1,     7,    -1,    -1,    10,    -1,    -1,
    -1,    -1,    -1,    16,    17,    18,    -1,    37,    21,    -1,
    -1,    -1,    -1,    -1,    44,    28,    46,    47,    -1,    -1,
    33,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    59,
    43,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
    -1,    -1,    -1,    56,    -1,    -1,    59,    -1,   196,    -1,
   198,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,   207,
   208,   209,    75,    76,    77,    78,    79,    -1,    -1,    -1,
    83,   219,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
    93,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   104,   105,    -1,   124,    -1,    -1,   127,    -1,    -1,
    -1,    -1,   198,   133,    -1,    18,    -1,    -1,    -1,    -1,
    -1,   207,   208,   209,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   219,    37,   155,   156,   157,    -1,    -1,
   160,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   173,   174,    -1,    59,    -1,   178,   179,
   180,    -1,    -1,    -1,    -1,    -1,   186,    -1,    -1,    -1,
   190,    -1,   192,   193,    -1,    -1,    -1,    -1,   198,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
    -1,    -1,    -1,   196,    -1,   198,   216,    -1,    -1,    -1,
    -1,   221,   222,   223,   207,   208,   209,    -1,    18,   112,
    -1,   214,    -1,    -1,    -1,    -1,   219,    -1,    -1,    -1,
    -1,   124,    -1,   126,   127,    -1,    -1,    37,    -1,    -1,
   133,    -1,    -1,    -1,    44,    -1,    46,    47,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
    -1,    -1,   155,   156,   157,    -1,    -1,   160,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   174,    -1,    -1,    -1,   178,   179,    -1,    -1,    -1,
    -1,    18,    -1,   186,    -1,    -1,    -1,   190,    -1,   192,
    -1,    -1,    -1,    -1,    -1,   198,    -1,    -1,    -1,    -1,
    37,    -1,   112,    -1,    -1,   208,   209,    44,    -1,    46,
    47,    -1,    -1,   216,   124,    -1,   126,   127,   221,   222,
   223,    -1,    59,   133,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   155,   156,   157,    -1,    -1,
   160,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
    -1,    -1,    -1,    44,   174,    46,    47,    -1,   178,   179,
    -1,    -1,    -1,    -1,    -1,   112,   186,    -1,    59,    -1,
   190,    -1,   192,    -1,    -1,    -1,    -1,   124,   198,    -1,
   127,    -1,    -1,    -1,    -1,    -1,   133,    -1,   208,   209,
    -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,
    18,   221,   222,   223,    -1,    -1,    -1,    -1,   155,   156,
   157,    -1,    -1,   160,    -1,    -1,    -1,    -1,    -1,    37,
    -1,   112,    -1,    -1,    -1,    -1,    44,   174,    46,    47,
    -1,   178,   179,   124,    -1,    -1,   127,    -1,    -1,   186,
    -1,    59,   133,   190,    -1,   192,    -1,    -1,    -1,    -1,
    -1,   198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   208,   209,    -1,   155,   156,   157,    -1,    -1,   216,
    -1,    -1,    -1,    -1,   221,   222,   223,    -1,    -1,    -1,
    -1,    -1,    -1,   174,    -1,    -1,    -1,   178,   179,   107,
    -1,   109,    -1,    18,   112,   186,    -1,    -1,    -1,   190,
    -1,   192,    -1,    -1,    -1,    -1,   124,   198,    -1,   127,
    -1,    -1,    37,    -1,    -1,    -1,    -1,   208,   209,    44,
    -1,    46,    47,    -1,    -1,   216,    -1,    -1,    -1,    -1,
   221,   222,   223,    -1,    59,    -1,    -1,   155,   156,   157,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   174,    -1,   176,    -1,
   178,   179,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,
    -1,    -1,   190,    -1,   192,    -1,    -1,    -1,    -1,    -1,
   198,    -1,    -1,    -1,    -1,    37,    -1,   112,    -1,    -1,
   208,   209,    44,    -1,    46,    47,    -1,    17,   216,   124,
    -1,    -1,   127,   221,   222,    -1,    -1,    59,    -1,    -1,
    -1,    -1,    -1,    33,    -1,    -1,    -1,    37,    -1,    -1,
    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,    49,
   155,   156,   157,    -1,    -1,    -1,    56,    -1,    -1,    59,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,
    17,    -1,    -1,   178,   179,    75,    -1,    -1,    78,    -1,
   112,    -1,    -1,    -1,    -1,   190,    33,   192,    -1,    -1,
    37,    -1,   124,   198,    -1,   127,    43,    44,    45,    46,
    47,    48,    49,   208,   209,    -1,    17,    -1,    -1,    56,
    -1,   216,    59,    -1,    -1,    -1,   221,   222,    -1,    -1,
    -1,    -1,    33,   155,   156,   157,    37,    -1,    75,    -1,
    -1,    78,    43,    44,    45,    46,    47,    48,    49,    -1,
    -1,    -1,   174,    -1,    -1,    56,   178,   179,    59,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,    -1,
   192,    -1,    -1,    37,    75,    -1,   198,    78,    -1,    -1,
    44,    -1,    46,    47,    -1,    -1,   208,   209,    -1,    -1,
    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,   221,
   222,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,    -1,
    -1,    -1,    -1,    37,    -1,    -1,    -1,   207,   208,   209,
    44,    -1,    46,    47,    -1,    -1,    -1,    -1,   218,   219,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   124,   198,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,
   207,   208,   209,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   218,   219,    -1,    -1,    -1,    -1,    -1,   112,    37,
    -1,   155,   156,   157,    -1,    -1,    44,   198,    46,    47,
   124,    -1,    -1,   127,    -1,    -1,   207,   208,   209,   173,
   174,    -1,    -1,    -1,   178,   179,   180,    -1,   219,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   190,    -1,   192,   193,
    -1,   155,   156,   157,   198,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   208,   209,    -1,    -1,    -1,    -1,
   174,    -1,   216,    -1,   178,   179,    -1,   221,   222,    -1,
    -1,    -1,    37,    -1,   112,    -1,   190,    -1,   192,    44,
    -1,    46,    47,    -1,   198,    -1,   124,    -1,    -1,   127,
    -1,    -1,    -1,    -1,   208,   209,   210,    -1,    -1,    -1,
    -1,    -1,   216,    -1,    -1,    -1,    -1,   221,   222,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,   156,   157,
    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
    46,    47,    -1,    -1,    -1,    -1,   174,    -1,    -1,    -1,
   178,   179,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,
    -1,    -1,   190,    -1,   192,    -1,    -1,    -1,    -1,   124,
   198,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   208,   209,    -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,
    -1,    -1,    -1,   221,   222,    -1,    -1,    -1,    -1,    -1,
   155,   156,   157,    -1,    -1,    -1,   112,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   174,
    -1,   127,    -1,   178,   179,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   190,    -1,   192,    -1,    -1,
    -1,    -1,    -1,   198,    -1,    -1,    -1,    -1,    -1,   155,
   156,   157,    -1,   208,   209,    -1,    -1,    -1,    -1,    -1,
    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,   174,    -1,
    -1,    -1,   178,   179,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   190,    -1,   192,    -1,    -1,    -1,
    -1,    -1,   198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   216,    -1,    -1,    -1,    -1,    -1,   222
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 5:
#line 607 "src/extGram.ycc"
{
	 if (!compiler->defineCurrentPackage(yyvsp[0].packName)) {
	    // ERRMSG: "redefinition of current package."
	    // return mortal error.
	  }
     ;
    break;}
case 6:
#line 614 "src/extGram.ycc"
{
    ;
    break;}
case 7:
#line 617 "src/extGram.ycc"
{
    ;
    break;}
case 8:
#line 624 "src/extGram.ycc"
{
	yyval.packName= yyvsp[-1].packName;
     ;
    break;}
case 9:
#line 631 "src/extGram.ycc"
{
	JCPackageName *packName;
	packName= new JCPackageName(yyvsp[0].identifier);
	yyval.packName= packName;
     ;
    break;}
case 10:
#line 637 "src/extGram.ycc"
{
	yyvsp[-2].packName->addName(yyvsp[0].identifier);
	yyval.packName= yyvsp[-2].packName;
     ;
    break;}
case 12:
#line 651 "src/extGram.ycc"
{
	    // List of identifiers, which can define a package or a type within a package.
	compiler->attachSynonymName(yyvsp[-1].packName);
	yyval.flag= 0;
     ;
    break;}
case 13:
#line 657 "src/extGram.ycc"
{
	    // Make a package to be searched for when a name is not resolved.
	compiler->attachOnDemandPackage(yyvsp[0].packName);
	yyval.flag= 0;
     ;
    break;}
case 14:
#line 672 "src/extGram.ycc"
{
	yyval.packName= yyvsp[-3].packName;
    ;
    break;}
case 15:
#line 685 "src/extGram.ycc"
{
	thePackage->setCurrentModifiers(yyvsp[0].flag);
    ;
    break;}
case 16:
#line 689 "src/extGram.ycc"
{
    	if (yyvsp[0].typeDecl) {
	    if (!(yyvsp[0].typeDecl->setModifiers(yyvsp[-2].flag))) {
		compiler->addError("Incompatible access flag");
//		return non-mortal error.
	     }
	 }
	yyval.typeDecl= yyvsp[0].typeDecl;
	thePackage->setCurrentModifiers(0);
     ;
    break;}
case 17:
#line 700 "src/extGram.ycc"
{
	yyval.typeDecl= yyvsp[0].typeDecl;
     ;
    break;}
case 18:
#line 707 "src/extGram.ycc"
{
	JCClass *tmpDebug;
	tmpDebug= (JCClass *)yyvsp[0].typeDecl;
	yyval.typeDecl= yyvsp[0].typeDecl;
     ;
    break;}
case 19:
#line 713 "src/extGram.ycc"
{
	JCInterface *tmpDebug;
	tmpDebug= (JCInterface *)yyvsp[0].typeDecl;
	yyval.typeDecl= yyvsp[0].typeDecl;
     ;
    break;}
case 20:
#line 724 "src/extGram.ycc"
{
	compiler->pushLineNumber();
    ;
    break;}
case 21:
#line 728 "src/extGram.ycc"
{
	thePackage->startClass(yyvsp[0].identifier);
     ;
    break;}
case 22:
#line 732 "src/extGram.ycc"
{
	JCClass *tmpDebug;
	tmpDebug= (JCClass *)thePackage->getCurrentType();
	tmpDebug->setSuperClass(yyvsp[0].type);
     ;
    break;}
case 23:
#line 738 "src/extGram.ycc"
{
	JCClass *tmpDebug;
	tmpDebug= (JCClass *)thePackage->getCurrentType();
	tmpDebug->setInterfaces(yyvsp[-1].type);
	tmpDebug->setBody(yyvsp[0].member);
	thePackage->endCurrentClass();
	tmpDebug->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.typeDecl= tmpDebug;
     ;
    break;}
case 24:
#line 751 "src/extGram.ycc"
{
	yyval.type= thePackage->getStarClass();
     ;
    break;}
case 25:
#line 755 "src/extGram.ycc"
{
	JCReferencedType *result;

	result= new JCReferencedType;
	result->setKind(TYPE_CLASS);
	result->setTypeName(yyvsp[0].identifier);
	yyval.type= result;
     ;
    break;}
case 26:
#line 767 "src/extGram.ycc"
{
	yyval.type= NULL;
     ;
    break;}
case 27:
#line 771 "src/extGram.ycc"
{
	JCReferencedType *typeList= NULL, *currentPtr, *lastPtr= NULL;
	JCIdentifier *tmpName;

	tmpName= yyvsp[0].identifier;
	while (tmpName) {
	    currentPtr= new JCReferencedType;
	    currentPtr->setKind(TYPE_INTERFACE);
	    currentPtr->setTypeName(tmpName);
	    if (!thePackage->bind(tmpName, currentPtr)) {
		thePackage->addUnknown(currentPtr);
	    }
	    if (lastPtr == NULL) {
		typeList= currentPtr;
	     }
	    else {
		lastPtr->setNext(currentPtr);
	     }
	    lastPtr= currentPtr;
	    tmpName= tmpName->getNext();
	 }
	yyval.type= typeList;
     ;
    break;}
case 28:
#line 798 "src/extGram.ycc"
{
	yyval.member= yyvsp[-1].member;
     ;
    break;}
case 29:
#line 807 "src/extGram.ycc"
{
	yyval.member= yyvsp[0].member;
     ;
    break;}
case 30:
#line 811 "src/extGram.ycc"
{
	yyvsp[-1].member->link(yyvsp[0].member);
	yyval.member= yyvsp[-1].member;
     ;
    break;}
case 31:
#line 819 "src/extGram.ycc"
{
	yyval.member= NULL;
     ;
    break;}
case 32:
#line 823 "src/extGram.ycc"
{
	yyval.member= yyvsp[0].member;
     ;
    break;}
case 33:
#line 830 "src/extGram.ycc"
{
	yyval.member= yyvsp[0].member;
     ;
    break;}
case 34:
#line 834 "src/extGram.ycc"
{
	yyvsp[-1].member->link(yyvsp[0].member);
	yyval.member= yyvsp[-1].member;
     ;
    break;}
case 35:
#line 847 "src/extGram.ycc"
{
	thePackage->setCurrentModifiers(0);	// Reset modifiers.
	yyval.member= yyvsp[0].member;
     ;
    break;}
case 36:
#line 852 "src/extGram.ycc"
{
/*
	JCStaticInitializer *result;

	result= new JCStaticInitializer;
	result->setBlock($1);
*/

	JCMethod *result;
	JCDimIdentifier *methodName;
	JCCteUtf8 *aCteName;
	JCIdentifier *tmpIdent;

	aCteName= JCCteUtf8::getWellKnownName(JCCteUtf8::clinitIdent);
	tmpIdent= new JCIdentifier(aCteName);
	methodName= new JCDimIdentifier;
	methodName->setName(tmpIdent);
	methodName->setNbrDimensions(0);

	result= new JCMethod;
	result->setModifiers(ACC_STATIC);
	result->setName(methodName);
	result->setParameters(NULL);
	result->setConstructor(true);
	result->setBody(yyvsp[0].actionBlock);
	result->setReturnedType(JCReferencedType::getVoidType());

	result->quickExport();
	thePackage->addMemberInType(result);

	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());

	yyval.member= result;
     ;
    break;}
case 37:
#line 894 "src/extGram.ycc"
{
	/* MethodModifiers.Opt sets the package's currentModifiers. */
	compiler->pushLineNumber();
    ;
    break;}
case 38:
#line 899 "src/extGram.ycc"
{
	JCField *tmpFieldPtr;
	yyvsp[0].member->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	if (yyvsp[0].member->memberType() == FIELD_MEMBER) {    // Fields can come in lists.
	    tmpFieldPtr= (JCField *)yyvsp[0].member;
	    while (tmpFieldPtr) {
		if (yyvsp[-2].type->isVoid()) {
		    /* ERRMSG: "Can't declare a field to be of 'VOID' type. */
		    /* return non-mortal error. */
		    /* Destroy the JCField declaration. */
		}
		else {
		    tmpFieldPtr->setModifiers(yyvsp[-3].flag);
		    tmpFieldPtr->setReturnedType(yyvsp[-2].type);
		    thePackage->addMemberInType(tmpFieldPtr);
		}
		tmpFieldPtr= (JCField *)tmpFieldPtr->getNext();
	     }
	 }
	else {
	    if (((JCMethod *)yyvsp[0].member)->isConstructor()) {
		yyvsp[0].member->setReturnedType(JCReferencedType::getVoidType());
		delete yyvsp[-2].type;
	    }
	    else {
		yyvsp[0].member->setReturnedType(yyvsp[-2].type);
	    }
	    ((JCMethod *)yyvsp[0].member)->quickExport();
	    thePackage->addMemberInType(yyvsp[0].member);
	 }
	yyval.member= yyvsp[0].member;
    ;
    break;}
case 39:
#line 933 "src/extGram.ycc"
{
	// ATTN: the 'static'  modifier should be refuse, unless we include
	// static states.
	yyvsp[0].member->setModifiers(yyvsp[-1].flag);
	thePackage->addMemberInType(yyvsp[0].member);
	yyval.member= yyvsp[0].member;
  ;
    break;}
case 40:
#line 947 "src/extGram.ycc"
{
	JCField *currentField, *lastField= NULL, *fieldList;
	JCVariableDeclaration *tmpDecl;

	tmpDecl= yyvsp[-1].varDecl;
	while (tmpDecl) {
	    currentField= new JCField;
	    currentField->setDeclarator(tmpDecl);
	    if (lastField == NULL) {
		fieldList= currentField;
	     }
	    else {
		lastField->setNext(currentField);
	     }
	    lastField= currentField;
	    tmpDecl= tmpDecl->getNext();
	 }
	yyval.member= fieldList;
     ;
    break;}
case 41:
#line 967 "src/extGram.ycc"
{ 
	((JCMethod *)yyvsp[-2].member)->setExceptions(yyvsp[-1].type);
	((JCMethod *)yyvsp[-2].member)->setBody(yyvsp[0].actionBlock);
	yyval.member= yyvsp[-2].member;
     ;
    break;}
case 42:
#line 973 "src/extGram.ycc"
{
	((JCMethod *)yyvsp[-2].member)->setExceptions(yyvsp[-1].type);
	((JCMethod *)yyvsp[-2].member)->setBody(yyvsp[0].actionBlock);
	yyval.member= yyvsp[-2].member;
     ;
    break;}
case 43:
#line 988 "src/extGram.ycc"
{
	yyval.varDecl= yyvsp[0].varDecl;
     ;
    break;}
case 44:
#line 992 "src/extGram.ycc"
{
	yyvsp[-2].varDecl->link(yyvsp[0].varDecl);
	yyval.varDecl= yyvsp[-2].varDecl;
     ;
    break;}
case 45:
#line 999 "src/extGram.ycc"
{
	JCVariableDeclaration *result;
	result= new JCVariableDeclaration;
	result->setName(yyvsp[0].dimIdentifier);
	yyval.varDecl= result;	
     ;
    break;}
case 46:
#line 1006 "src/extGram.ycc"
{
	JCVariableDeclaration *result;
	result= new JCVariableDeclaration;
	result->setName(yyvsp[-2].dimIdentifier);
	result->setInitializator(yyvsp[0].expression);
	yyval.varDecl= result;	
     ;
    break;}
case 47:
#line 1021 "src/extGram.ycc"
{
	JCDimIdentifier *result;
	result= new JCDimIdentifier;
	result->setName(yyvsp[-1].identifier);
	result->setNbrDimensions(yyvsp[0].flag);
	yyval.dimIdentifier= result;
     ;
    break;}
case 48:
#line 1037 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 49:
#line 1041 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 50:
#line 1062 "src/extGram.ycc"
{
	yyval.type= yyvsp[0].type;
     ;
    break;}
case 51:
#line 1066 "src/extGram.ycc"
{
	JCReferencedType *result;
	result= JCReferencedType::getVoidType();
	yyval.type= result;
     ;
    break;}
case 52:
#line 1075 "src/extGram.ycc"
{
	JCMethod *result;
	JCDimIdentifier *methodName;

	methodName= new JCDimIdentifier;
	methodName->setName(yyvsp[-4].identifier);
	methodName->setNbrDimensions(yyvsp[0].flag);

	result= new JCMethod;
	result->setModifiers(thePackage->getCurrentModifiers());
	result->setName(methodName);
	result->setParameters(yyvsp[-2].varDecl);
	yyval.member= result;
     ;
    break;}
case 53:
#line 1101 "src/extGram.ycc"
{
	yyval.varDecl= NULL;
     ;
    break;}
case 54:
#line 1105 "src/extGram.ycc"
{
	yyval.varDecl= yyvsp[0].varDecl;
     ;
    break;}
case 55:
#line 1111 "src/extGram.ycc"
{
	yyval.varDecl= yyvsp[0].varDecl;
     ;
    break;}
case 56:
#line 1115 "src/extGram.ycc"
{
	yyvsp[-2].varDecl->link(yyvsp[0].varDecl);
	yyval.varDecl= yyvsp[-2].varDecl;
     ;
    break;}
case 57:
#line 1122 "src/extGram.ycc"
{
	JCVariableDeclaration *result;
	result= new JCVariableDeclaration;
	result->setName(yyvsp[0].dimIdentifier);
	result->setTyping(yyvsp[-1].type);
	yyval.varDecl= result;
     ;
    break;}
case 58:
#line 1132 "src/extGram.ycc"
{
	yyval.type= NULL;
     ;
    break;}
case 59:
#line 1136 "src/extGram.ycc"
{
	JCReferencedType *typeList= NULL, *currentPtr, *lastPtr= NULL;
	JCIdentifier *tmpName;

	tmpName= yyvsp[0].identifier;
	while (tmpName) {
	    currentPtr= new JCReferencedType;
	    currentPtr->setKind(TYPE_INTERFACE);
	    currentPtr->setTypeName(tmpName);
	    if (lastPtr == NULL) {
		typeList= currentPtr;
	     }
	    else {
		lastPtr->setNext(currentPtr);
	     }
	    lastPtr= currentPtr;
	    tmpName= tmpName->getNext();
	 }
	yyval.type= typeList;
     ;
    break;}
case 60:
#line 1159 "src/extGram.ycc"
{
	yyval.identifier= yyvsp[0].identifier;
     ;
    break;}
case 61:
#line 1163 "src/extGram.ycc"
{
	yyvsp[-2].identifier->link(yyvsp[0].identifier);
	yyval.identifier= yyvsp[-2].identifier;
     ;
    break;}
case 62:
#line 1171 "src/extGram.ycc"
{
	yyval.actionBlock= yyvsp[0].actionBlock;
     ;
    break;}
case 63:
#line 1175 "src/extGram.ycc"
{
	JCActionBlock *result;
	result= new JCActionBlock;
	yyval.actionBlock= result;
     ;
    break;}
case 64:
#line 1202 "src/extGram.ycc"
{
	JCMethod *result;
	JCDimIdentifier *methodName;
	JCCteUtf8 *aCteName;
	JCIdentifier *tmpIdent;

	aCteName= JCCteUtf8::getWellKnownName(JCCteUtf8::initIdent);
	tmpIdent= new JCIdentifier(aCteName);
	methodName= new JCDimIdentifier;
	methodName->setName(tmpIdent);
	methodName->setNbrDimensions(0);

	result= new JCMethod;
	result->setModifiers(thePackage->getCurrentModifiers());
	result->setName(methodName);
	result->setParameters(yyvsp[-1].varDecl);
	result->setConstructor(true);
	yyval.member= result;
      ;
    break;}
case 65:
#line 1224 "src/extGram.ycc"
{
	thePackage->pushNameSpace();
	compiler->pushLineNumber();
     ;
    break;}
case 66:
#line 1229 "src/extGram.ycc"
{
	JCActionBlock *result;
	result= new JCActionBlock;
	if (yyvsp[-2].statement) {
	    yyvsp[-2].statement->link(yyvsp[-1].action);
	    result->setContent(yyvsp[-2].statement);
	 }
	else {
	    JCExprStat *superInit;
	    JCInvokeExpr *invoker;
	    JCImpliedInitialization *impliedInit;
	    JCIdentifier *superIdent;

	    superIdent= new JCIdentifier;
	    superIdent->resolveToSuper();
    
	    invoker= new JCInvokeExpr();
		// This automatically inserts a var access as a sub-expression.
	    invoker->setName(superIdent);
	    invoker->setArguments(NULL);

	    superInit= new JCExprStat();
	    superInit->setSubCategory(INVOKE_EXPRESSION);
	    superInit->setSubExpression(invoker);

	    invoker->bindInLocalSpace(thePackage->getBottomNameSpace());
    
	    impliedInit= new JCImpliedInitialization(thePackage->getCurrentType());
	    impliedInit->link(yyvsp[-1].action);
	    superInit->link(impliedInit);
	    impliedInit->setLineRange(compiler->currentLineNumber(), compiler->currentLineNumber());
	    superInit->setLineRange(compiler->currentLineNumber(), compiler->currentLineNumber());
	    result->setContent(superInit);
	 }
	result->setNameSpace(thePackage->popNameSpace());
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.actionBlock= result;
     ;
    break;}
case 67:
#line 1270 "src/extGram.ycc"
{
	yyval.statement= NULL;
     ;
    break;}
case 68:
#line 1274 "src/extGram.ycc"
{
	yyval.statement= yyvsp[0].statement;
     ;
    break;}
case 69:
#line 1280 "src/extGram.ycc"
{
	JCExprStat *result;
	JCInvokeExpr *tmpExpr;

	tmpExpr= new JCInvokeExpr;
		// This automatically inserts a var access as a sub-expression.
	tmpExpr->setName(yyvsp[-4].identifier);
	tmpExpr->setArguments(yyvsp[-2].expression);
	tmpExpr->bindInLocalSpace(thePackage->getBottomNameSpace());

	result= new JCExprStat;
	result->setSubCategory(INVOKE_EXPRESSION);
	result->setSubExpression(tmpExpr);

	if (yyvsp[-4].identifier->getSpecialName() == JCIdentifier::snSuper) {
	    JCImpliedInitialization *initializer= new JCImpliedInitialization(thePackage->getCurrentType());
	    result->link(initializer);
	}
	yyval.statement= result;
     ;
    break;}
case 70:
#line 1304 "src/extGram.ycc"
{
	JCIdentifier *result;
	result= new JCIdentifier;
	result->resolveToSelf();
	yyval.identifier= result;
     ;
    break;}
case 71:
#line 1311 "src/extGram.ycc"
{
	JCIdentifier *result;
	result= new JCIdentifier;
	result->resolveToSuper();
	yyval.identifier= result;
     ;
    break;}
case 72:
#line 1323 "src/extGram.ycc"
{
	compiler->pushLineNumber();
    ;
    break;}
case 73:
#line 1327 "src/extGram.ycc"
{
	yyval.actionBlock= yyvsp[0].actionBlock;
     ;
    break;}
case 74:
#line 1335 "src/extGram.ycc"
{
	thePackage->startInterface(yyvsp[0].identifier);
     ;
    break;}
case 75:
#line 1339 "src/extGram.ycc"
{
	JCInterface *tmpDebug;
	tmpDebug= (JCInterface *)thePackage->getCurrentType();
	tmpDebug->setTypeName(yyvsp[-3].identifier);
	tmpDebug->setInterfaces(yyvsp[-1].type);
	tmpDebug->setBody(yyvsp[0].member);
	yyval.typeDecl= tmpDebug;
     ;
    break;}
case 76:
#line 1350 "src/extGram.ycc"
{
	yyval.type= NULL;
     ;
    break;}
case 77:
#line 1354 "src/extGram.ycc"
{
	yyval.type= yyvsp[0].type;
     ;
    break;}
case 78:
#line 1361 "src/extGram.ycc"
{
	JCReferencedType *typeList= NULL, *currentPtr, *lastPtr= NULL;
	JCIdentifier *tmpName;

	tmpName= yyvsp[0].identifier;
	while (tmpName) {
	    currentPtr= new JCReferencedType;
	    currentPtr->setKind(TYPE_INTERFACE);
	    currentPtr->setTypeName(tmpName);
	    if (!thePackage->bind(tmpName, currentPtr)) {
		thePackage->addUnknown(currentPtr);
	    }
	    if (lastPtr == NULL) {
		typeList= currentPtr;
	     }
	    else {
		lastPtr->setNext(currentPtr);
	     }
	    lastPtr= currentPtr;
	    tmpName= tmpName->getNext();
	 }
	yyval.type= typeList;
     ;
    break;}
case 79:
#line 1391 "src/extGram.ycc"
{
	yyval.member= yyvsp[-1].member;
     ;
    break;}
case 80:
#line 1399 "src/extGram.ycc"
{
	JCBlockExpr *result;
	result= new JCBlockExpr;
	result->setInternal(yyvsp[-1].expression);
	yyval.expression= result;
     ;
    break;}
case 81:
#line 1408 "src/extGram.ycc"
{
	yyval.expression= NULL;
     ;
    break;}
case 82:
#line 1412 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 83:
#line 1418 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 84:
#line 1422 "src/extGram.ycc"
{
	yyvsp[-2].expression->linkExpression(yyvsp[0].expression);
	yyval.expression= yyvsp[-2].expression;
     ;
    break;}
case 85:
#line 1441 "src/extGram.ycc"
{
	thePackage->pushNameSpace();
	compiler->pushLineNumber();
     ;
    break;}
case 86:
#line 1447 "src/extGram.ycc"
{
	JCActionBlock *result;
	result= new JCActionBlock;
	result->setContent(yyvsp[-1].action);
	result->setNameSpace(thePackage->popNameSpace());
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.actionBlock= result;
     ;
    break;}
case 87:
#line 1456 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 88:
#line 1460 "src/extGram.ycc"
{
	JCActionBlock *result;
	result= new JCActionBlock;
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.actionBlock= result;
     ;
    break;}
case 89:
#line 1469 "src/extGram.ycc"
{
	yyval.action= NULL;
     ;
    break;}
case 91:
#line 1476 "src/extGram.ycc"
{
	yyval.action= yyvsp[0].action;
     ;
    break;}
case 92:
#line 1480 "src/extGram.ycc"
{
	yyvsp[-1].action->link(yyvsp[0].action);	// ATTN: If JCAction is not keeping a lastMember, it is unefficient.
	yyval.action= yyvsp[-1].action;
     ;
    break;}
case 93:
#line 1487 "src/extGram.ycc"
{
	yyval.action= yyvsp[0].action;
     ;
    break;}
case 94:
#line 1491 "src/extGram.ycc"
{
	yyval.action= yyvsp[0].statement;
     ;
    break;}
case 95:
#line 1495 "src/extGram.ycc"
{
	/* TMP: First try to put an error catcher. */
	JCStatement *result;
	result= new JCStatement;
	compiler->popLineNumber();
	yyval.action= result;
    ;
    break;}
case 96:
#line 1505 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 97:
#line 1509 "src/extGram.ycc"
{
	JCVarStat *result;
	JCVariableDeclaration *tmpVarDecl;

	result= new JCVarStat;
	tmpVarDecl= yyvsp[-1].varDecl;
	while (tmpVarDecl) {
	    tmpVarDecl->setTyping(yyvsp[-3].type);
	    tmpVarDecl= tmpVarDecl->getNext();
	 }
	result->setMembers(yyvsp[-1].varDecl);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.action= result;
     ;
    break;}
case 98:
#line 1527 "src/extGram.ycc"
{
	    // TMP: Send an empty statement to simplify 'NULL' testing higher.
	JCStatement *result;
	result= new JCStatement;
	yyval.statement= result;
     ;
    break;}
case 99:
#line 1534 "src/extGram.ycc"
{
	yyval.statement= yyvsp[0].statement;
     ;
    break;}
case 100:
#line 1538 "src/extGram.ycc"
{
	yyvsp[-1].statement->setLineRange(compiler->currentLineNumber(), compiler->currentLineNumber());
	yyval.statement= yyvsp[-1].statement;
     ;
    break;}
case 101:
#line 1543 "src/extGram.ycc"
{
	yyval.statement= yyvsp[0].statement;
     ;
    break;}
case 102:
#line 1547 "src/extGram.ycc"
{
	yyval.statement= yyvsp[0].statement;
     ;
    break;}
case 103:
#line 1551 "src/extGram.ycc"
{
	yyval.statement= yyvsp[0].statement;
     ;
    break;}
case 104:
#line 1555 "src/extGram.ycc"
{
	yyval.statement= yyvsp[0].statement;
     ;
    break;}
case 105:
#line 1559 "src/extGram.ycc"
{
	JCBlockStat *result;
	result= new JCBlockStat;
	result->setSubBlock(yyvsp[0].actionBlock);
	yyval.statement= result;
     ;
    break;}
case 106:
#line 1567 "src/extGram.ycc"
{
	/* Ne doit pas avoir lieu lorsqu'on n'est pas dans un membre etat. */
	yyval.statement= yyvsp[0].statement;	/* TMP */
     ;
    break;}
case 107:
#line 1572 "src/extGram.ycc"
{
	/* Ne doit pas avoir lieu lorsqu'on n'est pas dans un membre etat. */
	yyval.statement= yyvsp[0].statement;	/* TMP */
     ;
    break;}
case 109:
#line 1581 "src/extGram.ycc"
{
	isInSubset= 2;		// TMP: Define SQL reserved words to be active.
    ;
    break;}
case 110:
#line 1585 "src/extGram.ycc"
{
	if (yyvsp[-3].flag == 2) {
	    ((JCMetaSqlStatement *)yyvsp[0].statement)->makeDeclarative();
	    if (yyvsp[-2].expression != NULL) {
		// TODO: Complain, can't make declarative statements and provide a context (yet).
	    }
	}
	else {
	    ((JCMetaSqlStatement *)yyvsp[0].statement)->setPipeContext(yyvsp[-2].expression);
	    ((JCMetaSqlStatement *)yyvsp[0].statement)->bindToPackage(thePackage);
	}
	yyval.statement= yyvsp[0].statement;
    ;
    break;}
case 111:
#line 1602 "src/extGram.ycc"
{
	isInSubset= 0;		// TMP: Define SQL reserved words to be inactive.

	JCStatement *result;

	result= new JCMetaSqlStatement(yyvsp[0].sql92Statement);
	yyval.statement= result;
    ;
    break;}
case 112:
#line 1611 "src/extGram.ycc"
{
	isInSubset= 0;		// TMP: Define SQL reserved words to be inactive.

	JCBlockStat *containerStatement= new JCBlockStat();
	JCActionBlock *block= new JCActionBlock();
	JCStatement *result;

	containerStatement->setSubBlock(block);
	block->setContent(yyvsp[-1].sqlStatList->getFirst());
	result= new JCMetaSqlStatement(containerStatement);
	yyval.statement= result;
    ;
    break;}
case 113:
#line 1627 "src/extGram.ycc"
{
	yyval.flag= 1;
    ;
    break;}
case 114:
#line 1631 "src/extGram.ycc"
{
	yyval.flag= 2;
    ;
    break;}
case 115:
#line 1638 "src/extGram.ycc"
{
	yyval.flag= 0;
     ;
    break;}
case 116:
#line 1645 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 117:
#line 1649 "src/extGram.ycc"
{
	JCLabelStat *result;
	result= new JCLabelStat;
	result->setSubCategory(IDENT_LABELED);
	result->setIdentifier(yyvsp[-3].identifier);
	result->setSubStatement(yyvsp[0].statement);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
     ;
    break;}
case 118:
#line 1659 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 119:
#line 1665 "src/extGram.ycc"
{
	if (thePackage->isInsideSwitch()) {
	    JCLabelStat *result;

	    result= new JCLabelStat;
	    result->setSubCategory(CASE_LABELED);
	    result->setSubExpression(yyvsp[-2].expression);
	    result->setSubStatement(yyvsp[0].action);
	    thePackage->incCaseCount(true);
	    yyval.statement= result;
	}
	else {
	    compiler->addError("Case statement not in switch");

		// TMP: Send an empty statement to simplify 'NULL' testing higher.
	    yyval.statement= new JCStatement;
	}
	yyval.statement->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
     ;
    break;}
case 120:
#line 1685 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 121:
#line 1691 "src/extGram.ycc"
{
	if (thePackage->isInsideSwitch()) {
	    JCLabelStat *result;

	    result= new JCLabelStat;
	    result->setSubCategory(DEFAULT_LABELED);
	    result->setSubStatement(yyvsp[0].action);
	    thePackage->incCaseCount(false);
	    yyval.statement= result;
	}
	else {
	    compiler->addError("Default statement not in switch");
		// TMP: Send an empty statement to simplify 'NULL' testing higher.
	    yyval.statement= new JCStatement;
	}
	yyval.statement->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
     ;
    break;}
case 122:
#line 1711 "src/extGram.ycc"
{
	JCExprStat *result;
	result= new JCExprStat;
	result->setSubCategory(ASSIGN_EXPRESSION);
	result->setSubExpression(yyvsp[0].expression);
	yyval.statement= result;
     ;
    break;}
case 123:
#line 1719 "src/extGram.ycc"
{
	JCExprStat *result;
	result= new JCExprStat;
	result->setSubCategory(PREINCR_EXPRESSION);
	result->setSubExpression(yyvsp[0].expression);
	yyval.statement= result;
     ;
    break;}
case 124:
#line 1727 "src/extGram.ycc"
{
	JCExprStat *result;
	result= new JCExprStat;
	result->setSubCategory(PREDECR_EXPRESSION);
	result->setSubExpression(yyvsp[0].expression);
	yyval.statement= result;
     ;
    break;}
case 125:
#line 1735 "src/extGram.ycc"
{
	JCExprStat *result;
	result= new JCExprStat;
	result->setSubCategory(POSTINCR_EXPRESSION);
	result->setSubExpression(yyvsp[0].expression);
	yyval.statement= result;
     ;
    break;}
case 126:
#line 1743 "src/extGram.ycc"
{
	JCExprStat *result;
	result= new JCExprStat;
	result->setSubCategory(POSTDECR_EXPRESSION);
	result->setSubExpression(yyvsp[0].expression);
	yyval.statement= result;
     ;
    break;}
case 127:
#line 1751 "src/extGram.ycc"
{
	JCExprStat *result;
	result= new JCExprStat;
	result->setSubCategory(INVOKE_EXPRESSION);
	result->setSubExpression(yyvsp[0].expression);
	yyval.statement= result;
     ;
    break;}
case 128:
#line 1759 "src/extGram.ycc"
{
	JCExprStat *result;
	result= new JCExprStat;
	result->setSubCategory(ALLOC_EXPRESSION);
	result->setSubExpression(yyvsp[0].expression);
	yyval.statement= result;
     ;
    break;}
case 129:
#line 1769 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 130:
#line 1773 "src/extGram.ycc"
{
	JCSelectStat *result;
	result= new JCSelectStat;
	result->setSubCategory(IF_SELECTION);
	result->setSubExpression(yyvsp[-2].expression);
	result->setSubStatement(yyvsp[0].statement);
	yyval.statement= result;
     ;
    break;}
case 131:
#line 1785 "src/extGram.ycc"
{
	yyval.statement= NULL;
    ;
    break;}
case 132:
#line 1789 "src/extGram.ycc"
{
	yyval.statement= yyvsp[0].statement;
    ;
    break;}
case 133:
#line 1795 "src/extGram.ycc"
{
	if (yyvsp[0].statement != NULL) {
	    yyvsp[-1].statement->setSubCategory(IFELSE_SELECTION);
	    ((JCSelectStat *)yyvsp[-1].statement)->setFalseStatement(yyvsp[0].statement);
	}
	yyvsp[-1].statement->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
    ;
    break;}
case 134:
#line 1835 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 135:
#line 1839 "src/extGram.ycc"
{
	thePackage->startCaseContext();
    ;
    break;}
case 136:
#line 1843 "src/extGram.ycc"
{
	JCSwitchStat *result;
	result= new JCSwitchStat;
	result->setSubExpression(yyvsp[-3].expression);
	result->setSwitchTable(yyvsp[0].actionBlock, thePackage->endCaseContext());
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
     ;
    break;}
case 137:
#line 1855 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 138:
#line 1859 "src/extGram.ycc"
{
	    thePackage->incLoopLevel();
	;
    break;}
case 139:
#line 1863 "src/extGram.ycc"
{
	    JCIterStat *result;
	    result= new JCIterStat;
	    result->setSubCategory(WHILE_ITERATION);
	    result->setSubExpression(yyvsp[-3].expression);
	    result->setSubStatement(yyvsp[0].statement);
	    result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	    thePackage->decLoopLevel();
	    yyval.statement= result;
	    ;
    break;}
case 140:
#line 1874 "src/extGram.ycc"
{
	    compiler->pushLineNumber();
	    thePackage->incLoopLevel();
	;
    break;}
case 141:
#line 1879 "src/extGram.ycc"
{
	    thePackage->decLoopLevel();
	;
    break;}
case 142:
#line 1883 "src/extGram.ycc"
{
	    JCIterStat *result;
	    result= new JCIterStat;
	    result->setSubCategory(DO_ITERATION);
	    result->setSubExpression(yyvsp[-2].expression);
	    result->setSubStatement(yyvsp[-6].statement);
	    result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	    yyval.statement= result;
	    ;
    break;}
case 143:
#line 1893 "src/extGram.ycc"
{
	    compiler->pushLineNumber();
	    thePackage->pushNameSpace();
	;
    break;}
case 144:
#line 1898 "src/extGram.ycc"
{
	    thePackage->incLoopLevel();
	;
    break;}
case 145:
#line 1902 "src/extGram.ycc"
{
	    JCIterStat *result;
	    result= new JCIterStat;
	    result->setSubCategory(FOR_ITERATION);
	    result->setForInit(yyvsp[-6].action);
	    result->setSubExpression(yyvsp[-5].expression);
	    result->setLoopExpression(yyvsp[-3].action);
	    result->setSubStatement(yyvsp[0].statement);
	    result->setNameSpace(thePackage->popNameSpace());
	    thePackage->decLoopLevel();
	    result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	    yyval.statement= result;
	;
    break;}
case 146:
#line 1919 "src/extGram.ycc"
{
	yyval.action= yyvsp[-1].statement;
     ;
    break;}
case 147:
#line 1923 "src/extGram.ycc"
{
	yyval.action= yyvsp[0].action;
     ;
    break;}
case 148:
#line 1927 "src/extGram.ycc"
{
	JCAction *result= new JCAction;
	yyval.action= result;
     ;
    break;}
case 149:
#line 1935 "src/extGram.ycc"
{
	JCAction *result= new JCAction;
	yyval.action= result;
     ;
    break;}
case 150:
#line 1940 "src/extGram.ycc"
{
	yyval.action= yyvsp[0].statement;
     ;
    break;}
case 151:
#line 1946 "src/extGram.ycc"
{
	yyval.statement= yyvsp[0].statement;
     ;
    break;}
case 152:
#line 1950 "src/extGram.ycc"
{
	yyvsp[-2].statement->link(yyvsp[0].statement);
	yyval.statement= yyvsp[-2].statement;
     ;
    break;}
case 153:
#line 1957 "src/extGram.ycc"
{
	if (thePackage->isInsideSwitch() || (thePackage->getLoopLevel() > 0)) {
	    JCJumpStat *result;
	    result= new JCJumpStat;
	    result->setSubCategory(BREAK_JUMP);
	    result->setIdentifier(yyvsp[-1].identifier);
	    result->setLineRange(compiler->currentLineNumber(), compiler->currentLineNumber());
	    yyval.statement= result;
	}
	else {
	    compiler->addError("break not in switch or iterator statement");
		// TMP: Send an empty statement to simplify 'NULL' testing higher.
	    yyval.statement= new JCStatement;
	}
     ;
    break;}
case 154:
#line 1973 "src/extGram.ycc"
{
	if (thePackage->getLoopLevel() > 0) {
	    JCJumpStat *result;
	    result= new JCJumpStat;
	    result->setSubCategory(CONTINUE_JUMP);
	    result->setIdentifier(yyvsp[-1].identifier);
	    result->setLineRange(compiler->currentLineNumber(), compiler->currentLineNumber());
	    yyval.statement= result;
	}
	else {
	    compiler->addError("continue not in switch or iterator statement");
		// TMP: Send an empty statement to simplify 'NULL' testing higher.
	    yyval.statement= new JCStatement;
	}
     ;
    break;}
case 155:
#line 1989 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 156:
#line 1993 "src/extGram.ycc"
{
	JCJumpStat *result;
	result= new JCJumpStat;
	result->setSubCategory(RETURN_JUMP);
	result->setSubExpression(yyvsp[-1].expression);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
     ;
    break;}
case 157:
#line 2002 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 158:
#line 2006 "src/extGram.ycc"
{
	JCJumpStat *result;
	result= new JCJumpStat;
	result->setSubCategory(THROW_JUMP);
	result->setSubExpression(yyvsp[-1].expression);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
     ;
    break;}
case 159:
#line 2018 "src/extGram.ycc"
{
	compiler->pushLineNumber();
    ;
    break;}
case 160:
#line 2022 "src/extGram.ycc"
{
	yyval.actionBlock= yyvsp[0].actionBlock;
    ;
    break;}
case 161:
#line 2028 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 162:
#line 2032 "src/extGram.ycc"
{
	JCGuardStat *result;
	result= new JCGuardStat;
	result->setSubCategory(SYNCH_GUARD);
	result->setSubExpression(yyvsp[-2].expression);	// ATTN: Must resolve to an object (including array).
	result->setSubStatement(yyvsp[0].statement);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
     ;
    break;}
case 163:
#line 2050 "src/extGram.ycc"
{
	JCGuardStat *result;
	result= new JCGuardStat;
	result->setSubCategory(TRYFINAL_GUARD);
	result->setGuardedBlock(yyvsp[-1].actionBlock);
	result->setMandatoryBlock(yyvsp[0].actionBlock);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
     ;
    break;}
case 164:
#line 2060 "src/extGram.ycc"
{
	JCGuardStat *result;
	result= new JCGuardStat;
	result->setSubCategory(TRYCATCH_GUARD);
	result->setGuardedBlock(yyvsp[-1].actionBlock);
	result->setHandlingBlocks(yyvsp[0].handlerBlock);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
     ;
    break;}
case 165:
#line 2070 "src/extGram.ycc"
{
	JCGuardStat *result;
	result= new JCGuardStat;
	result->setSubCategory(TRYFULL_GUARD);
	result->setGuardedBlock(yyvsp[-2].actionBlock);
	result->setHandlingBlocks(yyvsp[-1].handlerBlock);
	result->setMandatoryBlock(yyvsp[0].actionBlock);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
     ;
    break;}
case 166:
#line 2084 "src/extGram.ycc"
{
	yyval.handlerBlock= yyvsp[0].handlerBlock;
     ;
    break;}
case 167:
#line 2088 "src/extGram.ycc"
{
	yyvsp[-1].handlerBlock->link(yyvsp[0].handlerBlock);
	yyval.handlerBlock= yyvsp[-1].handlerBlock;
     ;
    break;}
case 168:
#line 2096 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 169:
#line 2100 "src/extGram.ycc"
{
	JCHandlingBlock *result;
	result= new JCHandlingBlock;
	result->setTrap(yyvsp[-2].varDecl);
	result->setHandler(yyvsp[0].actionBlock);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.handlerBlock= result;
     ;
    break;}
case 170:
#line 2112 "src/extGram.ycc"
{
	yyval.actionBlock= yyvsp[0].actionBlock;
     ;
    break;}
case 171:
#line 2121 "src/extGram.ycc"
{
	JCExpression *result= new JCExpression;
	yyval.expression= result;
     ;
    break;}
case 172:
#line 2126 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 173:
#line 2134 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 174:
#line 2141 "src/extGram.ycc"
{
	JCFieldAccess *result;
	result= new JCFieldAccess;
	result->setSubExpression(yyvsp[-2].expression);
	result->setName(yyvsp[0].identifier);
	result->bindInLocalSpace(thePackage->getBottomNameSpace());
	yyval.expression= result;
     ;
    break;}
case 175:
#line 2156 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 176:
#line 2160 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;	
     ;
    break;}
case 177:
#line 2164 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;	
     ;
    break;}
case 178:
#line 2168 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;	
     ;
    break;}
case 179:
#line 2172 "src/extGram.ycc"
{
	if (yyvsp[0].identifier->isComposed()) {
	    JCFieldAccess *result= new JCFieldAccess;
	    result->setName(yyvsp[0].identifier);
	    result->bindInLocalSpace(thePackage->getBottomNameSpace());
	    yyval.expression= result;
	  }
	 else {
	    JCVarAccess *result= new JCVarAccess();
	    result->setVarName(yyvsp[0].identifier);
	    result->bindInLocalSpace(thePackage->getBottomNameSpace());
	    yyval.expression= result;
	 }
     ;
    break;}
case 180:
#line 2187 "src/extGram.ycc"
{
/*
MOD-961214 [HD]: Trying to live without blocked expression.
	JCBlockExpr *result;
	result= new JCBlockExpr;
	result->setInternal($2);
	$$= result;
*/
	yyval.expression= yyvsp[-1].expression;
    ;
    break;}
case 181:
#line 2201 "src/extGram.ycc"
{
	yyval.identifier= yyvsp[-1].identifier;
    ;
    break;}
case 182:
#line 2209 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 183:
#line 2213 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 184:
#line 2221 "src/extGram.ycc"
{
	if (yyvsp[0].identifier->isComposed()) {
	    JCFieldAccess *result= new JCFieldAccess;
	    result->setName(yyvsp[0].identifier);
	    result->bindInLocalSpace(thePackage->getBottomNameSpace());
	    yyval.expression= result;
	  }
	 else {
	    if (yyvsp[0].identifier->isReserved() && yyvsp[0].identifier->getSpecialName() == JCIdentifier::snNull) {
		JCCteExpr *result= new JCCteExpr(JCReferencedType::popNullObject);
		yyval.expression= result;
	    }
	    else {
		JCVarAccess *result= new JCVarAccess();
		result->setVarName(yyvsp[0].identifier);
		result->bindInLocalSpace(thePackage->getBottomNameSpace());
		yyval.expression= result;
	    }
	 }
     ;
    break;}
case 185:
#line 2242 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 186:
#line 2249 "src/extGram.ycc"
{
	yyval.identifier= yyvsp[0].identifier;
     ;
    break;}
case 187:
#line 2253 "src/extGram.ycc"
{
	yyvsp[-2].identifier->addComponent(yyvsp[0].identifier);
	yyval.identifier= yyvsp[-2].identifier;
     ;
    break;}
case 188:
#line 2260 "src/extGram.ycc"
{
	yyval.identifier= yyvsp[0].identifier;
     ;
    break;}
case 189:
#line 2264 "src/extGram.ycc"
{
	JCIdentifier *result;
	result= new JCIdentifier;
	result->resolveToSelf();
	yyval.identifier= result;
     ;
    break;}
case 190:
#line 2271 "src/extGram.ycc"
{
	JCIdentifier *result;
	result= new JCIdentifier;
	result->resolveToSuper();
	yyval.identifier= result;
     ;
    break;}
case 191:
#line 2278 "src/extGram.ycc"
{
	JCIdentifier *result;
	result= new JCIdentifier;
	result->resolveToNull();
	yyval.identifier= result;
     ;
    break;}
case 192:
#line 2287 "src/extGram.ycc"
{
	yyval.identifier= yyvsp[-1].identifier;
    ;
    break;}
case 193:
#line 2297 "src/extGram.ycc"
{
	yyval.identifier= yyvsp[0].identifier;
     ;
    break;}
case 194:
#line 2305 "src/extGram.ycc"
{
	JCArrayAccess *result;
	result= new JCArrayAccess;
	if (yyvsp[-2].identifier->isReserved()) {
	    compiler->addError("Can't use this or super in an array access");
	}
	else {
	    result->setName(yyvsp[-2].identifier);
	    result->addDimensionOffset(yyvsp[-1].expression);
	    result->bindInLocalSpace(thePackage->getBottomNameSpace());
	}
	yyval.expression= result;
     ;
    break;}
case 195:
#line 2319 "src/extGram.ycc"
{
	JCArrayAccess *result;

	if (yyvsp[-3].expression->getCategory() == JCExpression::eArray) {
	    if (((JCArrayAccess *)yyvsp[-3].expression)->addDimensionOffset(yyvsp[-1].expression)) {
		compiler->addError("field does not have so many dimensions");
		// RETURN non-fatal error.
	     }
	    result= (JCArrayAccess *)yyvsp[-3].expression;
	 }
	else {
	    result= new JCArrayAccess;
	    result->setSubExpression(yyvsp[-3].expression);
	    result->addDimensionOffset(yyvsp[-1].expression);
	    /* ATTN: Is there any need to do a binding in this case ?
		result->bindInLocalSpace(thePackage->getBottomNameSpace());
	    */
	 }
	yyval.expression= result;
     ;
    break;}
case 196:
#line 2345 "src/extGram.ycc"
{
	((JCInvokeExpr *)yyvsp[-3].expression)->setArguments(yyvsp[-1].expression);
	yyval.expression= yyvsp[-3].expression;
     ;
    break;}
case 197:
#line 2353 "src/extGram.ycc"
{
	JCInvokeExpr *result;
	result= new JCInvokeExpr;
	result->setName(yyvsp[0].identifier);
	result->bindInLocalSpace(thePackage->getBottomNameSpace());
	yyval.expression= result;
     ;
    break;}
case 198:
#line 2361 "src/extGram.ycc"
{
	JCInvokeExpr *result;
	result= new JCInvokeExpr;
	result->setName(yyvsp[0].identifier);
	result->setSubExpression(yyvsp[-2].expression);
	result->bindInLocalSpace(thePackage->getBottomNameSpace());
	yyval.expression= result;
     ;
    break;}
case 199:
#line 2373 "src/extGram.ycc"
{
	yyval.expression= NULL;
     ;
    break;}
case 200:
#line 2377 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 201:
#line 2383 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 202:
#line 2387 "src/extGram.ycc"
{
	yyvsp[-2].expression->linkExpression(yyvsp[0].expression);
	yyval.expression= yyvsp[-2].expression;
     ;
    break;}
case 203:
#line 2396 "src/extGram.ycc"
{
	if (yyvsp[-3].type->isPrimitive()) {
	    JCExpression *result= new JCExpression;    // TMP: Simplify the error management at higher levels.

	    compiler->addError("It is illegal to create a single primitive instance");
	    yyval.expression= result;
	}
	else {
	    JCAllocExpr *result;

	    result= new JCAllocExpr;
	    result->setType(yyvsp[-3].type);
	    if (!thePackage->bind(yyvsp[-3].type->getTypeName(), yyvsp[-3].type)) {
		thePackage->addUnknown(yyvsp[-3].type);
	    }
	    result->setArguments(yyvsp[-1].expression);
	    yyval.expression= result;
	}
     ;
    break;}
case 204:
#line 2416 "src/extGram.ycc"
{
	JCAllocExpr *result;
	JCReferencedType *arrayType;

	result= new JCAllocExpr();

	if (!yyvsp[-2].type->isPrimitive()) {
	    if (!thePackage->bind(yyvsp[-2].type->getTypeName(), yyvsp[-2].type)) {
		thePackage->addUnknown(yyvsp[-2].type);
	    }
	}
	result->setArrayType(yyvsp[-2].type, yyvsp[-1].expression, yyvsp[0].flag);
	yyval.expression= result;
     ;
    break;}
case 205:
#line 2434 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 206:
#line 2438 "src/extGram.ycc"
{
	yyvsp[-1].expression->linkExpression(yyvsp[0].expression);
	yyval.expression= yyvsp[-1].expression;
     ;
    break;}
case 207:
#line 2445 "src/extGram.ycc"
{
	yyval.expression= yyvsp[-1].expression;
     ;
    break;}
case 208:
#line 2451 "src/extGram.ycc"
{
	yyval.flag= 0;
     ;
    break;}
case 209:
#line 2455 "src/extGram.ycc"
{
	yyval.flag= yyvsp[0].flag;
     ;
    break;}
case 210:
#line 2461 "src/extGram.ycc"
{
	yyval.flag= 1;
     ;
    break;}
case 211:
#line 2465 "src/extGram.ycc"
{
	yyval.flag= (yyvsp[-2].flag + 1);
     ;
    break;}
case 212:
#line 2474 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 213:
#line 2478 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 214:
#line 2482 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 215:
#line 2489 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(POSTINCR_OPER);
	result->setRightOperand(yyvsp[-1].expression);
	yyval.expression= result;
     ;
    break;}
case 216:
#line 2499 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(POSTDECR_OPER);
	result->setRightOperand(yyvsp[-1].expression);
	yyval.expression= result;
     ;
    break;}
case 217:
#line 2509 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 218:
#line 2513 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 219:
#line 2517 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(POSATE_OPER);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 220:
#line 2525 "src/extGram.ycc"
{
	if (yyvsp[0].expression->getCategory() == JCExpression::eConstant) {
	    JCCteExpr *tmpExpr= (JCCteExpr *)yyvsp[0].expression;
	    JCReferencedType *cteType= tmpExpr->getFinalType();
	    if (cteType->isArithmetic()) {
		tmpExpr->negate();
		yyval.expression= tmpExpr;
	    }
	    else {
		    // We let the opcode do the conversion.  ATTN: Maybe we have to declare a
		    // type error here ? Or insert a type cast ?
		JCOperExpr *result;
    
		result= new JCOperExpr;
		result->setOperator(NEGATE_OPER);
		result->setRightOperand(yyvsp[0].expression);
		yyval.expression= result;
	    }
	}
	else {
	    JCOperExpr *result;

	    result= new JCOperExpr;
	    result->setOperator(NEGATE_OPER);
	    result->setRightOperand(yyvsp[0].expression);
	    yyval.expression= result;
	}
     ;
    break;}
case 221:
#line 2554 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 222:
#line 2560 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(PREINCR_OPER);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 223:
#line 2570 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(PREDECR_OPER);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 224:
#line 2580 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 225:
#line 2584 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(BITFLIP_OPER);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 226:
#line 2592 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(NOT_OPER);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 227:
#line 2600 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 228:
#line 2607 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 229:
#line 2611 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(MULTIPLY_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 230:
#line 2620 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(DIVIDE_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 231:
#line 2629 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(MODULO_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 232:
#line 2640 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 233:
#line 2644 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(ADD_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 234:
#line 2653 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(SUBST_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 235:
#line 2664 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 236:
#line 2668 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(LS_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 237:
#line 2677 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(RS_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 238:
#line 2686 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(URS_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 239:
#line 2697 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 240:
#line 2701 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(LT_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 241:
#line 2710 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(GT_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 242:
#line 2719 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(GE_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 243:
#line 2728 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(LE_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 244:
#line 2737 "src/extGram.ycc"
{
	JCCastExpr *result;
	JCReferencedType *tmpType;

	tmpType= new JCReferencedType;
	tmpType->setTypeName(yyvsp[-1].identifier);
	tmpType->setKind(TYPE_CLASS);
	if (!thePackage->bind(yyvsp[-1].identifier, tmpType)) {
	    thePackage->addUnknown(tmpType);
	 }
	if (yyvsp[0].flag != 0) {
	    JCReferencedType *arrayType;

	    arrayType= new JCReferencedType;
	    tmpType->setKind(TYPE_ARRAY);
	    arrayType->setOfReferencedType(tmpType);
	    arrayType->setNbrDimensions(yyvsp[0].flag);
	    tmpType= arrayType;
	}
	result= new JCCastExpr;
	result->setOperator(ISA_OPER);
	result->setRightOperand(yyvsp[-3].expression);
	result->setTypeMember(tmpType);

	yyval.expression= result;
     ;
    break;}
case 245:
#line 2766 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 246:
#line 2770 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(EQ_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 247:
#line 2779 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(NE_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 248:
#line 2790 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 249:
#line 2794 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(AND_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 250:
#line 2805 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 251:
#line 2809 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(XOR_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 252:
#line 2820 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 253:
#line 2824 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(OR_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 254:
#line 2835 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 255:
#line 2839 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(ANDAND_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 256:
#line 2850 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 257:
#line 2854 "src/extGram.ycc"
{
	JCOperExpr *result;
	result= new JCOperExpr;
	result->setOperator(OROR_OPER);
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 258:
#line 2866 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 259:
#line 2870 "src/extGram.ycc"
{
	JCCondExpr *result;
	result= new JCCondExpr;
	result->setCondition(yyvsp[-4].expression);
	result->setExprOnTrue(yyvsp[-2].expression);
	result->setExprOnFalse(yyvsp[0].expression);
	yyval.expression= result;
     ;
    break;}
case 260:
#line 2882 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 261:
#line 2886 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
     ;
    break;}
case 262:
#line 2892 "src/extGram.ycc"
{
	JCAssignExpr *result;
	result= new JCAssignExpr;
	result->setLeftOperand(yyvsp[-2].expression);
	result->setRightOperand(yyvsp[0].expression);
	result->setOperator(yyvsp[-1].flag);
	yyval.expression= result;
     ;
    break;}
case 263:
#line 2911 "src/extGram.ycc"
{
	JCCastExpr *result;
	JCReferencedType *tmpType;

	tmpType= new JCReferencedType;
	tmpType->setTypeName(yyvsp[-1].identifier);
	if (!thePackage->bind(yyvsp[-1].identifier, tmpType)) {
	    thePackage->addUnknown(tmpType);
	 }
	result= new JCCastExpr;
	result->setRightOperand(yyvsp[0].expression);
	result->setTypeMember(tmpType);
	yyval.expression= result;
     ;
    break;}
case 264:
#line 2926 "src/extGram.ycc"
{
	JCCastExpr *result;
	JCReferencedType *tmpType;

	tmpType= new JCReferencedType;
	tmpType->setOfPrimitiveType(yyvsp[-2].flag);
	result= new JCCastExpr;
	result->setRightOperand(yyvsp[0].expression);
	result->setTypeMember(tmpType);
	yyval.expression= result;
     ;
    break;}
case 265:
#line 2941 "src/extGram.ycc"
{
	yyval.flag= SIMPLEASS_OPER;
     ;
    break;}
case 266:
#line 2945 "src/extGram.ycc"
{
	yyval.flag= PLUSASS_OPER;
     ;
    break;}
case 267:
#line 2949 "src/extGram.ycc"
{
	yyval.flag= MINUSASS_OPER;
     ;
    break;}
case 268:
#line 2953 "src/extGram.ycc"
{
	yyval.flag= TIMEASS_OPER;
     ;
    break;}
case 269:
#line 2957 "src/extGram.ycc"
{
	yyval.flag= DIVIDEASS_OPER;
     ;
    break;}
case 270:
#line 2961 "src/extGram.ycc"
{
	yyval.flag= ANDASS_OPER;
     ;
    break;}
case 271:
#line 2965 "src/extGram.ycc"
{
	yyval.flag= ORASS_OPER;
     ;
    break;}
case 272:
#line 2969 "src/extGram.ycc"
{
	yyval.flag= NOTASS_OPER;
     ;
    break;}
case 273:
#line 2973 "src/extGram.ycc"
{
	yyval.flag= MODASS_OPER;
     ;
    break;}
case 274:
#line 2977 "src/extGram.ycc"
{
	yyval.flag= LSASS_OPER;
     ;
    break;}
case 275:
#line 2981 "src/extGram.ycc"
{
	yyval.flag= RSASS_OPER;
     ;
    break;}
case 276:
#line 2985 "src/extGram.ycc"
{
	yyval.flag= URSASS_OPER;
     ;
    break;}
case 277:
#line 2992 "src/extGram.ycc"
{
	yyval.identifier= NULL;
     ;
    break;}
case 278:
#line 2996 "src/extGram.ycc"
{
	yyval.identifier= yyvsp[0].identifier;
     ;
    break;}
case 279:
#line 3003 "src/extGram.ycc"
{
	JCIdentifier *result;
	JCCteUtf8 *name;

	name= JCCteUtf8::addUniqueInstance(yyvsp[0].string);
	result= new JCIdentifier(name);
	yyval.identifier= result;
     ;
    break;}
case 280:
#line 3015 "src/extGram.ycc"
{
	yyval.type= yyvsp[0].type;
     ;
    break;}
case 281:
#line 3019 "src/extGram.ycc"
{
	yyval.type= yyvsp[0].type;
     ;
    break;}
case 282:
#line 3026 "src/extGram.ycc"
{
	JCReferencedType *result;
	result= new JCReferencedType;
	result->setKind(TYPE_BASIC);
	result->setOfPrimitiveType(yyvsp[0].flag);
	yyval.type= result;
     ;
    break;}
case 283:
#line 3034 "src/extGram.ycc"
{
	JCReferencedType *result;
	result= new JCReferencedType;
	result->setKind(TYPE_CLASS);
	result->setTypeName(yyvsp[0].identifier);
	yyval.type= result;
     ;
    break;}
case 284:
#line 3045 "src/extGram.ycc"
{
	yyval.flag= JVM_TYPE_BOOLEAN;
     ;
    break;}
case 285:
#line 3049 "src/extGram.ycc"
{
	yyval.flag= JVM_TYPE_CHAR;
     ;
    break;}
case 286:
#line 3053 "src/extGram.ycc"
{
	yyval.flag= JVM_TYPE_SIGNED_BYTE;
     ;
    break;}
case 287:
#line 3057 "src/extGram.ycc"
{
	yyval.flag= JVM_TYPE_UNSIGNED_SHORT;
     ;
    break;}
case 288:
#line 3061 "src/extGram.ycc"
{
	yyval.flag= JVM_TYPE_INTEGER;
     ;
    break;}
case 289:
#line 3065 "src/extGram.ycc"
{
	yyval.flag= JVM_TYPE_FLOAT;
     ;
    break;}
case 290:
#line 3069 "src/extGram.ycc"
{
	yyval.flag= JVM_TYPE_DOUBLE;
     ;
    break;}
case 291:
#line 3073 "src/extGram.ycc"
{
	yyval.flag= JVM_TYPE_LONG;
     ;
    break;}
case 292:
#line 3080 "src/extGram.ycc"
{
	JCReferencedType *result, *tmpType;

	result= new JCReferencedType();
	    // ATTN: Must review the way primitive array types are plugged within array types.
	result->setOfPrimitiveType(yyvsp[-2].flag);
	result->setKind(TYPE_ARRAY);
	result->incrementNbrDimensions();
	yyval.type= result;
     ;
    break;}
case 293:
#line 3091 "src/extGram.ycc"
{
	JCReferencedType *result, *tmpType;
	tmpType= new JCReferencedType;
	tmpType->setKind(TYPE_CLASS);
	tmpType->setTypeName(yyvsp[-1].identifier);

	result= new JCReferencedType;
	result->setKind(TYPE_ARRAY);
	result->setOfReferencedType(tmpType);
	result->incrementNbrDimensions();
	yyval.type= result;
     ;
    break;}
case 294:
#line 3104 "src/extGram.ycc"
{
	yyvsp[-2].type->incrementNbrDimensions();
     ;
    break;}
case 295:
#line 3111 "src/extGram.ycc"
{
	JCCteExpr *constant;
	constant= new JCCteExpr(JCReferencedType::popChar);
	constant->setBoolValue(yyvsp[0].boolValue);
	yyval.expression= (JCExpression *)constant;
     ;
    break;}
case 296:
#line 3118 "src/extGram.ycc"
{
	JCCteExpr *constant;
	constant= new JCCteExpr(JCReferencedType::popChar);
	constant->setCharValue(yyvsp[0].string);
	yyval.expression= (JCExpression *)constant;
     ;
    break;}
case 297:
#line 3125 "src/extGram.ycc"
{
	JCCteExpr *constant;

	constant= new JCCteExpr(JCReferencedType::popFloat);
	if (yyvsp[0].floatNumber == 0.0) {
	    constant->setFloatZero();
	}
/* This never happens at this level.
	else if ($1 == -1.0) {
	    constant->setFloatMinusOne();
	}
*/
	else if (yyvsp[0].floatNumber == 1.0) {
	    constant->setFloatOne();
	}
	else {
	    constant->setFloatValue(yyvsp[0].floatNumber);
	}
	yyval.expression= (JCExpression *)constant;
     ;
    break;}
case 298:
#line 3146 "src/extGram.ycc"
{
	JCCteExpr *constant;

	constant= new JCCteExpr(JCReferencedType::popInteger);
	if (yyvsp[0].integerNumber == 0) {
	    constant->setIntZero();
	}
/* This never happen at this level.
	else if ($1 ==  -1) {
	    constant->setIntMinusOne();
	}
*/
	else if (yyvsp[0].integerNumber == 1) {
	    constant->setIntOne();
	}
	else {
	    constant->setIntValue(yyvsp[0].integerNumber);
	}
	yyval.expression= (JCExpression *)constant;
     ;
    break;}
case 299:
#line 3167 "src/extGram.ycc"
{
	JCCteExpr *constant;
	constant= new JCCteExpr(JCReferencedType::popString);
	constant->setStringValue(yyvsp[0].string);
	yyval.expression= (JCExpression *)constant;
     ;
    break;}
case 300:
#line 3174 "src/extGram.ycc"
{
	JCCteExpr *constant;
	unsigned int *aValue= (unsigned int *)yyvsp[0].longNumber;

	constant= new JCCteExpr(JCReferencedType::popLong);
	if ((aValue[0] == 0) && (aValue[1] == 0)) {
	    constant->setLongZero();
	}
/* This never happen at this level.
	else if ((aValue[0] == 0xFFFFFFFF) && (aValue[1] == 0xFFFFFFFF)) {
	    constant->setLongMinusOne();
	}
*/
	else if ((aValue[1] == 0) && (aValue[0] == 1)) {
	    constant->setLongOne();
	}
	else {
	    constant->setLongValue((unsigned int *)yyvsp[0].longNumber);
	}
	yyval.expression= (JCExpression *)constant;
     ;
    break;}
case 301:
#line 3196 "src/extGram.ycc"
{
	JCCteExpr *constant;

	constant= new JCCteExpr(JCReferencedType::popDouble);
	if (yyvsp[0].doubleNumber == 0.0) {
	    constant->setDoubleZero();
	}
/* This never happen at this level.
	else if ($1 == -1.0) {
	    constant->setDoubleMinusOne();
	}
*/
	else if (yyvsp[0].doubleNumber == 1.0) {
	    constant->setDoubleOne();
	}
	else {
	    constant->setDoubleValue(yyvsp[0].doubleNumber);
	}
	yyval.expression= (JCExpression *)constant;
     ;
    break;}
case 302:
#line 3224 "src/extGram.ycc"
{
	yyval.flag= yyvsp[0].flag;
     ;
    break;}
case 303:
#line 3228 "src/extGram.ycc"
{
	yyval.flag= (yyvsp[-1].flag | yyvsp[0].flag);
     ;
    break;}
case 304:
#line 3236 "src/extGram.ycc"
{
	yyval.flag= ACC_PROTECTED;
     ;
    break;}
case 305:
#line 3240 "src/extGram.ycc"
{
	yyval.flag= ACC_PRIVATE;
     ;
    break;}
case 306:
#line 3244 "src/extGram.ycc"
{
	yyval.flag= ACC_PUBLIC;
     ;
    break;}
case 307:
#line 3251 "src/extGram.ycc"
{
	yyval.flag= yyvsp[0].flag;
     ;
    break;}
case 308:
#line 3255 "src/extGram.ycc"
{
	yyval.flag= (yyvsp[-1].flag | yyvsp[0].flag);
     ;
    break;}
case 309:
#line 3261 "src/extGram.ycc"
{
	yyval.flag= ACC_ABSTRACT;
    ;
    break;}
case 310:
#line 3265 "src/extGram.ycc"
{
	yyval.flag= yyvsp[0].flag;
     ;
    break;}
case 311:
#line 3271 "src/extGram.ycc"
{
	thePackage->setCurrentModifiers(0);
	yyval.flag= 0;
     ;
    break;}
case 312:
#line 3276 "src/extGram.ycc"
{
	thePackage->setCurrentModifiers(yyvsp[0].flag);
	yyval.flag= yyvsp[0].flag;
     ;
    break;}
case 313:
#line 3283 "src/extGram.ycc"
{
	yyval.flag= yyvsp[0].flag;
     ;
    break;}
case 314:
#line 3287 "src/extGram.ycc"
{
	yyval.flag= (yyvsp[-1].flag | yyvsp[0].flag);
     ;
    break;}
case 315:
#line 3294 "src/extGram.ycc"
{
	yyval.flag= ACC_ABSTRACT;
     ;
    break;}
case 316:
#line 3298 "src/extGram.ycc"
{
	yyval.flag= ACC_NATIVE;
     ;
    break;}
case 317:
#line 3302 "src/extGram.ycc"
{
	yyval.flag= ACC_SYNCHRONIZED;
     ;
    break;}
case 318:
#line 3306 "src/extGram.ycc"
{
	yyval.flag= ACC_TRANSIENT;
     ;
    break;}
case 319:
#line 3310 "src/extGram.ycc"
{
	yyval.flag= ACC_VOLATILE;
     ;
    break;}
case 320:
#line 3314 "src/extGram.ycc"
{
	yyval.flag= yyvsp[0].flag;
     ;
    break;}
case 321:
#line 3321 "src/extGram.ycc"
{
	yyval.flag= ACC_PROTECTED;
     ;
    break;}
case 322:
#line 3325 "src/extGram.ycc"
{
	yyval.flag= ACC_PRIVATE;
     ;
    break;}
case 323:
#line 3329 "src/extGram.ycc"
{
	yyval.flag= ACC_STATIC;
     ;
    break;}
case 324:
#line 3333 "src/extGram.ycc"
{
	yyval.flag= yyvsp[0].flag;
     ;
    break;}
case 325:
#line 3340 "src/extGram.ycc"
{
	yyval.flag= ACC_FINAL;
     ;
    break;}
case 326:
#line 3344 "src/extGram.ycc"
{
	yyval.flag= ACC_PUBLIC;
     ;
    break;}
case 327:
#line 3352 "src/extGram.ycc"
{
	((JCState *)yyvsp[-1].member)->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
    ;
    break;}
case 328:
#line 3356 "src/extGram.ycc"
{
	((JCState *)yyvsp[-3].member)->setBody(yyvsp[-2].actionBlock);
	// ATTN: Must take care also of the TimeInfo.
	yyval.member= yyvsp[-3].member;
    ;
    break;}
case 329:
#line 3365 "src/extGram.ycc"
{
	compiler->pushLineNumber();
    ;
    break;}
case 330:
#line 3369 "src/extGram.ycc"
{
	JCState *result;
	JCDimIdentifier *stateName;


	stateName= new JCDimIdentifier;

	if (thePackage->getCurrentType()->getName()->isMatching(yyvsp[-3].identifier)) {
	    JCCteUtf8 *aCteName= JCCteUtf8::getWellKnownName(JCCteUtf8::pinitIdent);
	    JCIdentifier *tmpIdent= new JCIdentifier(aCteName);
	    stateName->setName(tmpIdent);
	}
	else {
	    stateName->setName(yyvsp[-3].identifier);
	}

	result= new JCState;
	result->setName(stateName);
	result->setParameters(yyvsp[-1].varDecl);
	yyval.member= result;
    ;
    break;}
case 331:
#line 3394 "src/extGram.ycc"
{
	yyval.actionBlock= yyvsp[0].actionBlock;
     ;
    break;}
case 332:
#line 3400 "src/extGram.ycc"
{
	compiler->pushLineNumber();
	thePackage->pushNameSpace();
     ;
    break;}
case 333:
#line 3405 "src/extGram.ycc"
{
	JCStateActionBlock *result;
	result= new JCStateActionBlock;

	result->setContent(yyvsp[-2].action);
	result->setTransitions(yyvsp[-1].transitionList);
	result->setNameSpace(thePackage->popNameSpace());
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.actionBlock= result;
     ;
    break;}
case 334:
#line 3416 "src/extGram.ycc"
{
	compiler->pushLineNumber();
	thePackage->pushNameSpace();
     ;
    break;}
case 335:
#line 3421 "src/extGram.ycc"
{
	JCStateActionBlock *result;
	result= new JCStateActionBlock;

	result->setContent(NULL);
	result->setTransitions(yyvsp[-1].transitionList);
	result->setNameSpace(thePackage->popNameSpace());
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.actionBlock= result;
     ;
    break;}
case 336:
#line 3432 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 337:
#line 3436 "src/extGram.ycc"
{
	JCActionBlock *result;
	result= new JCActionBlock;
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.actionBlock= result;
     ;
    break;}
case 338:
#line 3446 "src/extGram.ycc"
{
	yyval.action= yyvsp[0].action;
    ;
    break;}
case 339:
#line 3450 "src/extGram.ycc"
{
	yyvsp[-1].action->link(yyvsp[0].action);
	yyval.action= yyvsp[-1].action;
    ;
    break;}
case 340:
#line 3457 "src/extGram.ycc"
{
	yyval.action= yyvsp[0].action;
    ;
    break;}
case 341:
#line 3461 "src/extGram.ycc"
{
	yyval.action= yyvsp[0].statement;
    ;
    break;}
case 342:
#line 3468 "src/extGram.ycc"
{
	yyval.statement= yyvsp[-1].statement;
    ;
    break;}
case 343:
#line 3474 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 344:
#line 3478 "src/extGram.ycc"
{
	JCGuardStat *result;
	result= new JCGuardStat;
	result->setSubCategory(CRITICAL_GUARD);
	result->setSubExpression(yyvsp[-2].expression);	// ATTN: Must resolve to an object (including array).
	result->setSubStatement(yyvsp[0].statement);
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
    ;
    break;}
case 345:
#line 3491 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 346:
#line 3495 "src/extGram.ycc"
{
	JCFireStat *result;

	result= new JCFireStat();

	if (yyvsp[-2].identifier->isComposed()) {
	    JCFieldAccess *anIdent;

	    anIdent= new JCFieldAccess();
	    anIdent->setName(yyvsp[-2].identifier);
	    anIdent->bindInLocalSpace(thePackage->getBottomNameSpace());
	    result->setEvent(anIdent);
	  }
	 else {
	    JCVarAccess *anIdent;
	    anIdent= new JCVarAccess();
	    anIdent->setVarName(yyvsp[-2].identifier);
	    anIdent->bindInLocalSpace(thePackage->getBottomNameSpace());
	    result->setEvent(anIdent);
	 }

	if (yyvsp[-1].identifier != NULL) {
	    if (yyvsp[-1].identifier->isComposed()) {
		JCFieldAccess *anIdent;
    
		anIdent= new JCFieldAccess();
		anIdent->setName(yyvsp[-1].identifier);
		anIdent->bindInLocalSpace(thePackage->getBottomNameSpace());
		result->setDestination(anIdent);
	    }
	    else {
		JCVarAccess *anIdent;
		anIdent= new JCVarAccess();
		anIdent->setVarName(yyvsp[-1].identifier);
		anIdent->bindInLocalSpace(thePackage->getBottomNameSpace());
		result->setDestination(anIdent);
	    }
	}
	else {
		// TODO: Check if in a static method : illegal.
	}
	result->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyval.statement= result;
    ;
    break;}
case 347:
#line 3542 "src/extGram.ycc"
{
	yyval.identifier= NULL;
    ;
    break;}
case 348:
#line 3546 "src/extGram.ycc"
{
	yyval.identifier= yyvsp[0].identifier;
    ;
    break;}
case 349:
#line 3553 "src/extGram.ycc"
{
	yyval.transitionList= new TransitionList();
    ;
    break;}
case 350:
#line 3557 "src/extGram.ycc"
{
	yyval.transitionList= yyvsp[0].transitionList;
    ;
    break;}
case 351:
#line 3564 "src/extGram.ycc"
{
	yyval.transitionList= new TransitionList();
	yyval.transitionList->addObject(yyvsp[0].transition);
    ;
    break;}
case 352:
#line 3569 "src/extGram.ycc"
{
	yyval.transitionList= yyvsp[-1].transitionList;
	yyval.transitionList->addObject(yyvsp[0].transition);
    ;
    break;}
case 353:
#line 3577 "src/extGram.ycc"
{
	compiler->pushLineNumber();
     ;
    break;}
case 354:
#line 3581 "src/extGram.ycc"
{
	yyvsp[-1].transition->setLineRange(compiler->popLineNumber(), compiler->currentLineNumber());
	yyvsp[-1].transition->setModifiers(yyvsp[-4].integerNumber);
	yyval.transition= yyvsp[-1].transition;
    ;
    break;}
case 355:
#line 3590 "src/extGram.ycc"
{
	JCTransition *result;
	result= new JCTransition();

	if (yyvsp[-2].identifier->isComposed()) {
	    JCFieldAccess *anIdent;

	    anIdent= new JCFieldAccess();
	    anIdent->setName(yyvsp[-2].identifier);
	    anIdent->bindInLocalSpace(thePackage->getBottomNameSpace());
	    result->setTriggers(anIdent);
	  }
	 else {
	    JCVarAccess *anIdent;
	    anIdent= new JCVarAccess();
	    anIdent->setVarName(yyvsp[-2].identifier);
	    anIdent->bindInLocalSpace(thePackage->getBottomNameSpace());
	    result->setTriggers(anIdent);
	 }
	result->setSpecialDestination((JCTransition::DestinationModifiers)yyvsp[0].integerNumber);

	yyval.transition= result;
    ;
    break;}
case 356:
#line 3614 "src/extGram.ycc"
{
	JCTransition *result;
	result= new JCTransition();

	if (yyvsp[-2].identifier->isComposed()) {
	    JCFieldAccess *anIdent;

	    anIdent= new JCFieldAccess();
	    anIdent->setName(yyvsp[-2].identifier);
	    anIdent->bindInLocalSpace(thePackage->getBottomNameSpace());
	    result->setTriggers(anIdent);
	  }
	 else {
	    JCVarAccess *anIdent;
	    anIdent= new JCVarAccess();
	    anIdent->setVarName(yyvsp[-2].identifier);
	    anIdent->bindInLocalSpace(thePackage->getBottomNameSpace());
	    result->setTriggers(anIdent);
	 }
	result->setDestination((JCStateInvokeExpr *)yyvsp[0].expression);
	yyval.transition= result;
    ;
    break;}
case 357:
#line 3637 "src/extGram.ycc"
{
	JCTransition *result;
	result= new JCTransition();

	result->setDestination((JCStateInvokeExpr *)yyvsp[0].expression);
	result->setModifiers(JCTransition::tmDefaulter);
	yyval.transition= result;
    ;
    break;}
case 358:
#line 3646 "src/extGram.ycc"
{
	JCTransition *result;
	result= new JCTransition();

	result->setSpecialDestination(JCTransition::dmBreak);
	result->setModifiers(JCTransition::tmDefaulter);
	yyval.transition= result;
    ;
    break;}
case 359:
#line 3661 "src/extGram.ycc"
{
	JCStateInvokeExpr *result;
	result= new JCStateInvokeExpr;
	result->setName(yyvsp[-3].identifier);
	result->bindInLocalSpace(thePackage->getBottomNameSpace());
	result->setArguments(yyvsp[-1].expression);
	yyval.expression= result;
     ;
    break;}
case 360:
#line 3672 "src/extGram.ycc"
{
	yyval.integerNumber= JCTransition::dmPassby;	/* TMP */
    ;
    break;}
case 361:
#line 3676 "src/extGram.ycc"
{
	yyval.integerNumber= JCTransition::dmConsume;	/* TMP */
    ;
    break;}
case 362:
#line 3680 "src/extGram.ycc"
{
	yyval.integerNumber= JCTransition::dmBreak;	/* TMP */
    ;
    break;}
case 363:
#line 3687 "src/extGram.ycc"
{
	yyval.integerNumber= 0;	/* TMP */
    ;
    break;}
case 364:
#line 3691 "src/extGram.ycc"
{
	yyval.integerNumber= JCTransition::dmPush;	/* TMP */
    ;
    break;}
case 365:
#line 3695 "src/extGram.ycc"
{
	yyval.integerNumber= JCTransition::dmPop;	/* TMP */
    ;
    break;}
case 366:
#line 3701 "src/extGram.ycc"
{
	yyval.integerNumber= 0;
    ;
    break;}
case 367:
#line 3705 "src/extGram.ycc"
{
	yyval.integerNumber= yyvsp[0].integerNumber;
    ;
    break;}
case 368:
#line 3711 "src/extGram.ycc"
{
	yyval.integerNumber= yyvsp[0].integerNumber;
    ;
    break;}
case 369:
#line 3715 "src/extGram.ycc"
{
	yyval.integerNumber= yyvsp[-1].integerNumber | yyvsp[0].integerNumber;
    ;
    break;}
case 370:
#line 3721 "src/extGram.ycc"
{
	yyval.integerNumber= JCTransition::tmBlocking;	/* TMP */
    ;
    break;}
case 371:
#line 3725 "src/extGram.ycc"
{
	yyval.integerNumber= JCTransition::tmImmediate;	/* TMP */
    ;
    break;}
case 372:
#line 3729 "src/extGram.ycc"
{
	yyval.integerNumber= JCTransition::tmParallel;	/* TMP */
    ;
    break;}
case 373:
#line 3733 "src/extGram.ycc"
{
	yyval.integerNumber= JCTransition::tmImplicit;	/* TMP */
    ;
    break;}
case 374:
#line 3739 "src/extGram.ycc"
{
	yyval.identifier= yyvsp[0].identifier;
    ;
    break;}
case 375:
#line 3743 "src/extGram.ycc"
{
	yyvsp[-2].identifier->link(yyvsp[0].identifier);
	yyval.identifier= yyvsp[-2].identifier;
    ;
    break;}
case 376:
#line 3751 "src/extGram.ycc"
{
	yyval.expression= NULL;
    ;
    break;}
case 377:
#line 3755 "src/extGram.ycc"
{
	yyval.expression= yyvsp[-1].expression;
     ;
    break;}
case 378:
#line 3761 "src/extGram.ycc"
{
	JCCteExpr *constant;
	constant= new JCCteExpr(JCReferencedType::popInteger);
	constant->setIntValue(yyvsp[0].integerNumber);
	yyval.expression= (JCExpression *)constant;
    ;
    break;}
case 379:
#line 3772 "src/extGram.ycc"
{
	yyval.expression= NULL;
    ;
    break;}
case 380:
#line 3776 "src/extGram.ycc"
{
	yyval.expression= yyvsp[-1].expression;
    ;
    break;}
case 381:
#line 3782 "src/extGram.ycc"
{
	yyval.sqlStatList= new SqlStatementList(yyvsp[0].sql92Statement);
    ;
    break;}
case 382:
#line 3786 "src/extGram.ycc"
{
	yyvsp[-1].sqlStatList->addStatement(yyvsp[0].sql92Statement);
	yyval.sqlStatList= yyvsp[-1].sqlStatList;
    ;
    break;}
case 383:
#line 3794 "src/extGram.ycc"
{
	yyval.sql92Statement->consolidate();
    ;
    break;}
case 384:
#line 3798 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlStatement;
	yyerrok;
    ;
    break;}
case 395:
#line 3833 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlOpen(yyvsp[0].identifier);
     ;
    break;}
case 396:
#line 3840 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlFetch((JCSqlFetchOrientation *)yyvsp[-3].sqlExpression, new JCSqlIdentifier(yyvsp[-2].identifier), (JCSqlTargetList *)yyvsp[0].sqlClause);
     ;
    break;}
case 397:
#line 3846 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFetchOrientation::getSimpleOrientation(JCSqlConstants::foNatural);
     ;
    break;}
case 398:
#line 3850 "src/extGram.ycc"
{
	yyval.sqlExpression= yyvsp[-1].sqlExpression;
     ;
    break;}
case 399:
#line 3856 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFetchOrientation::getSimpleOrientation(JCSqlConstants::foNext);
     ;
    break;}
case 400:
#line 3860 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFetchOrientation::getSimpleOrientation(JCSqlConstants::foPrior);
     ;
    break;}
case 401:
#line 3864 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFetchOrientation::getSimpleOrientation(JCSqlConstants::foFirst);
     ;
    break;}
case 402:
#line 3868 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFetchOrientation::getSimpleOrientation(JCSqlConstants::foLast);
     ;
    break;}
case 403:
#line 3872 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlFetchOrientation(JCSqlConstants::foAbsolute, yyvsp[0].sqlExpression);
     ;
    break;}
case 404:
#line 3876 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlFetchOrientation(JCSqlConstants::foRelative, yyvsp[0].sqlExpression);
     ;
    break;}
case 405:
#line 3883 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlEmbedded(yyvsp[0].expression);
    ;
    break;}
case 408:
#line 3895 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlClose(yyvsp[0].identifier);
     ;
    break;}
case 409:
#line 3902 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlStatement(JCSqlStatement::cCommit);
     ;
    break;}
case 410:
#line 3909 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlStatement(JCSqlStatement::cRollback);
     ;
    break;}
case 418:
#line 3929 "src/extGram.ycc"
{
	/* TODO. */
	yyval.sql92Statement= new JCSqlDelete();
     ;
    break;}
case 419:
#line 3937 "src/extGram.ycc"
{
	/* TODO. */
	yyval.sql92Statement= new JCSqlDelete();
     ;
    break;}
case 420:
#line 3945 "src/extGram.ycc"
{
	((JCSqlInsert *)yyvsp[0].sql92Statement)->setTableName(yyvsp[-1].sqlIdentifier);
	yyval.sql92Statement= yyvsp[0].sql92Statement;
     ;
    break;}
case 421:
#line 3953 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlInsert(NULL, yyvsp[-1].sqlIdentList, yyvsp[0].sqlExpression);
    ;
    break;}
case 422:
#line 3957 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlInsert(NULL, NULL, yyvsp[0].sqlExpression);
    ;
    break;}
case 423:
#line 3961 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlInsert(NULL, NULL, NULL);
    ;
    break;}
case 424:
#line 3968 "src/extGram.ycc"
{
	yyval.sqlIdentList= yyvsp[-1].sqlIdentList;
    ;
    break;}
case 425:
#line 3975 "src/extGram.ycc"
{
	/* TODO. */
	yyval.sql92Statement= new JCSqlUpdate();
    ;
    break;}
case 426:
#line 3983 "src/extGram.ycc"
{
	/* TODO. */
	yyval.sql92Statement= new JCSqlUpdate();
     ;
    break;}
case 427:
#line 3991 "src/extGram.ycc"
{
	/* TODO. */
     ;
    break;}
case 428:
#line 3995 "src/extGram.ycc"
{
	/* TODO. */
     ;
    break;}
case 429:
#line 4002 "src/extGram.ycc"
{
	/* TODO. */
     ;
    break;}
case 433:
#line 4015 "src/extGram.ycc"
{
	JCSqlSelect *selectExpr;
	selectExpr= new JCSqlSelect((JCSqlSelectList *)yyvsp[-3].sqlClause, (JCSqlTableClause *)yyvsp[0].sqlClause);
	if (yyvsp[-4].flag != JCSqlConstants::noSetQuantifier) {
	    selectExpr->quantifySelection((JCSqlConstants::SetQuantifier)yyvsp[-4].flag);
	}
	yyval.sql92Statement= new JCSqlSelectStat(selectExpr, (JCSqlTargetList *)yyvsp[-1].sqlClause);
    ;
    break;}
case 434:
#line 4027 "src/extGram.ycc"
{
	yyval.sql92Statement= new JCSqlSelectStat((JCSqlSelect *)yyvsp[0].sqlExpression, NULL);
   ;
    break;}
case 435:
#line 4034 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::noSetQuantifier;
     ;
    break;}
case 436:
#line 4038 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::distinctElements;
     ;
    break;}
case 437:
#line 4042 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::allElements;
     ;
    break;}
case 438:
#line 4049 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlSelectList();
	((JCSqlSelectList *)yyval.sqlClause)->setStar();
     ;
    break;}
case 440:
#line 4059 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlSelectList((JCSqlSelectItem *)yyvsp[0].sqlClause);
     ;
    break;}
case 441:
#line 4063 "src/extGram.ycc"
{
	((JCSqlSelectList *)yyvsp[-2].sqlClause)->addElement((JCSqlSelectItem *)yyvsp[0].sqlClause);
	yyval.sqlClause= yyvsp[-2].sqlClause;
     ;
    break;}
case 442:
#line 4071 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlSelectItem(yyvsp[0].sqlExpression);
     ;
    break;}
case 443:
#line 4075 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlSelectItem(yyvsp[-2].sqlIdentifier);
	((JCSqlSelectItem *)yyval.sqlClause)->setStar();
     ;
    break;}
case 445:
#line 4084 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlSynonym(yyvsp[-1].sqlExpression, yyvsp[0].sqlIdentifier);
    ;
    break;}
case 446:
#line 4090 "src/extGram.ycc"
{
	yyval.sqlIdentifier= new JCSqlIdentifier(yyvsp[0].identifier);
    ;
    break;}
case 448:
#line 4098 "src/extGram.ycc"
{
	yyval.sqlIdentifier= new JCSqlIdentifier(yyvsp[0].identifier);
	yyval.sqlIdentifier->setModuleHeader();
    ;
    break;}
case 449:
#line 4106 "src/extGram.ycc"
{
	yyval.sqlIdentifier= new JCSqlIdentifier(yyvsp[0].identifier);
    ;
    break;}
case 450:
#line 4110 "src/extGram.ycc"
{
	yyvsp[-2].sqlIdentifier->addComponent(yyvsp[0].identifier);
	yyval.sqlIdentifier= yyvsp[-2].sqlIdentifier;
    ;
    break;}
case 454:
#line 4134 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::add);
    ;
    break;}
case 455:
#line 4138 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::substract);
    ;
    break;}
case 457:
#line 4146 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::multiply);
    ;
    break;}
case 458:
#line 4150 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::divide);
    ;
    break;}
case 459:
#line 4157 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[0].sqlExpression, NULL, JCSqlOperExpr::posate);
    ;
    break;}
case 460:
#line 4161 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[0].sqlExpression, NULL, JCSqlOperExpr::negate);
    ;
    break;}
case 465:
#line 4175 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlColumnExpr(yyvsp[0].sqlIdentifier);
    ;
    break;}
case 468:
#line 4184 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-1].sqlExpression, NULL, JCSqlOperExpr::parenthesis);
    ;
    break;}
case 473:
#line 4202 "src/extGram.ycc"
{
	((JCSqlNumericCte *)yyvsp[0].sqlExpression)->posate();
	yyval.sqlExpression= yyvsp[0].sqlExpression;
    ;
    break;}
case 474:
#line 4207 "src/extGram.ycc"
{
	((JCSqlNumericCte *)yyvsp[0].sqlExpression)->negate();
	yyval.sqlExpression= yyvsp[0].sqlExpression;
    ;
    break;}
case 478:
#line 4221 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlNumericCte((unsigned int)yyvsp[0].integerNumber);
    ;
    break;}
case 479:
#line 4225 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlNumericCte(yyvsp[0].floatNumber);
    ;
    break;}
case 480:
#line 4232 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlCharCte(yyvsp[0].string);
	delete yyvsp[0].string;
    ;
    break;}
case 482:
#line 4245 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlConstantExpr::getPopularConstant(JCSqlConstantExpr::popUser);
    ;
    break;}
case 483:
#line 4249 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlConstantExpr::getPopularConstant(JCSqlConstantExpr::popCurrent);
    ;
    break;}
case 484:
#line 4253 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlConstantExpr::getPopularConstant(JCSqlConstantExpr::popSession);
    ;
    break;}
case 485:
#line 4257 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlConstantExpr::getPopularConstant(JCSqlConstantExpr::popSystem);
    ;
    break;}
case 486:
#line 4261 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlConstantExpr::getPopularConstant(JCSqlConstantExpr::popValue);
    ;
    break;}
case 487:
#line 4268 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlEmbedded(yyvsp[0].expression);
    ;
    break;}
case 488:
#line 4272 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlEmbedded(yyvsp[-1].expression, yyvsp[0].expression);
    ;
    break;}
case 489:
#line 4279 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
    ;
    break;}
case 491:
#line 4287 "src/extGram.ycc"
{
	yyval.expression= yyvsp[0].expression;
    ;
    break;}
case 492:
#line 4294 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFunction::getBuiltin(JCSqlFunction::countStar);
    ;
    break;}
case 493:
#line 4298 "src/extGram.ycc"
{
	((JCSqlFunction *)yyvsp[-4].sqlExpression)->setQuantifier((JCSqlConstants::SetQuantifier)yyvsp[-2].flag);
	((JCSqlFunction *)yyvsp[-4].sqlExpression)->setOperands(yyvsp[-1].sqlExpression);
    ;
    break;}
case 494:
#line 4306 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFunction::getBuiltin(JCSqlFunction::avg);
    ;
    break;}
case 495:
#line 4310 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFunction::getBuiltin(JCSqlFunction::max);
    ;
    break;}
case 496:
#line 4314 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFunction::getBuiltin(JCSqlFunction::min);
    ;
    break;}
case 497:
#line 4318 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFunction::getBuiltin(JCSqlFunction::sum);
    ;
    break;}
case 498:
#line 4322 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlFunction::getBuiltin(JCSqlFunction::count);
    ;
    break;}
case 500:
#line 4330 "src/extGram.ycc"
{
	// TODO.
  ;
    break;}
case 502:
#line 4338 "src/extGram.ycc"
{
	// TODO.
    ;
    break;}
case 503:
#line 4342 "src/extGram.ycc"
{
	// TODO.
    ;
    break;}
case 505:
#line 4350 "src/extGram.ycc"
{
	// TODO.
    ;
    break;}
case 509:
#line 4362 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-1].sqlExpression, NULL, JCSqlOperExpr::parenthesis);
  ;
    break;}
case 513:
#line 4375 "src/extGram.ycc"
{
	JCSqlSelect *selectExpr;

	selectExpr= new JCSqlSelect((JCSqlSelectList *)yyvsp[-1].sqlClause, (JCSqlTableClause *)yyvsp[0].sqlClause);
	if (yyvsp[-2].flag != JCSqlConstants::noSetQuantifier) {
	    selectExpr->quantifySelection((JCSqlConstants::SetQuantifier)yyvsp[-2].flag);
	}
	yyval.sqlExpression= selectExpr;
    ;
    break;}
case 514:
#line 4388 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-1].sqlExpression, NULL, JCSqlOperExpr::parenthesis);
    ;
    break;}
case 515:
#line 4395 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlContainerExpr(yyvsp[0].sqlClause, JCSqlContainerExpr::values);
    ;
    break;}
case 516:
#line 4402 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlRowValueList(new JCSqlRowValue(yyvsp[0].sqlExpression));
    ;
    break;}
case 517:
#line 4406 "src/extGram.ycc"
{
	((JCSqlRowValueList *)yyvsp[-2].sqlClause)->addElement(new JCSqlRowValue(yyvsp[0].sqlExpression));
	yyval.sqlClause= yyvsp[-2].sqlClause;
    ;
    break;}
case 518:
#line 4414 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlContainerExpr(yyvsp[0].sqlIdentifier, JCSqlContainerExpr::table);
    ;
    break;}
case 519:
#line 4421 "src/extGram.ycc"
{
    ;
    break;}
case 520:
#line 4424 "src/extGram.ycc"
{
    ;
    break;}
case 521:
#line 4430 "src/extGram.ycc"
{
    ;
    break;}
case 522:
#line 4433 "src/extGram.ycc"
{
    ;
    break;}
case 523:
#line 4439 "src/extGram.ycc"
{
	// TODO.
    ;
    break;}
case 524:
#line 4443 "src/extGram.ycc"
{
	// TODO.
    ;
    break;}
case 525:
#line 4447 "src/extGram.ycc"
{ yyval.sqlExpression= NULL; /* TMPFIX. */ ;
    break;}
case 526:
#line 4452 "src/extGram.ycc"
{
	// TODO.
     ;
    break;}
case 527:
#line 4462 "src/extGram.ycc"
{
	// TODO.
     ;
    break;}
case 542:
#line 4490 "src/extGram.ycc"
{
	// TODO.
    ;
    break;}
case 544:
#line 4500 "src/extGram.ycc"
{
	yyval.sqlIdentList= yyvsp[-1].sqlIdentList;
    ;
    break;}
case 545:
#line 4507 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlTableRef(yyvsp[0].sqlIdentifier);
    ;
    break;}
case 546:
#line 4511 "src/extGram.ycc"
{
	((JCSqlTableRef *)yyvsp[0].sqlClause)->setSource(yyvsp[-1].sqlIdentifier);
	yyval.sqlClause= yyvsp[0].sqlClause;
    ;
    break;}
case 547:
#line 4516 "src/extGram.ycc"
{
	((JCSqlTableRef *)yyvsp[0].sqlClause)->setSource(yyvsp[-1].sqlExpression);
	yyval.sqlClause= yyvsp[0].sqlClause;
    ;
    break;}
case 548:
#line 4521 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlTableRef(yyvsp[0].sqlExpression);
    ;
    break;}
case 549:
#line 4527 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlTableRef(yyvsp[0].identifier);
    ;
    break;}
case 550:
#line 4531 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlTableRef(yyvsp[-3].identifier);
	((JCSqlTableRef *)yyval.sqlClause)->setDerivedColumns(yyvsp[-1].sqlIdentList);
    ;
    break;}
case 551:
#line 4540 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlTableClause((JCSqlTableRefList *)yyvsp[-4].sqlClause, yyvsp[-3].sqlExpression, (JCSqlGroupList *)yyvsp[-2].sqlClause, (JCSqlSortList *)yyvsp[-1].sqlClause, yyvsp[0].sqlExpression);
     ;
    break;}
case 552:
#line 4547 "src/extGram.ycc"
{
	yyval.sqlClause= NULL;
    ;
    break;}
case 553:
#line 4551 "src/extGram.ycc"
{
	yyval.sqlClause= yyvsp[0].sqlClause;
    ;
    break;}
case 554:
#line 4557 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlTableRefList((JCSqlTableRef *)yyvsp[0].sqlClause);
    ;
    break;}
case 555:
#line 4561 "src/extGram.ycc"
{
	((JCSqlTableRefList *)yyvsp[-2].sqlClause)->addElement((JCSqlTableRef *)yyvsp[0].sqlClause);
	yyval.sqlClause= yyvsp[-2].sqlClause;
    ;
    break;}
case 556:
#line 4568 "src/extGram.ycc"
{
	yyval.sqlExpression= NULL;
    ;
    break;}
case 558:
#line 4576 "src/extGram.ycc"
{
	yyval.sqlExpression= yyvsp[0].sqlExpression;
    ;
    break;}
case 559:
#line 4582 "src/extGram.ycc"
{
	yyval.sqlClause= NULL;
    ;
    break;}
case 560:
#line 4586 "src/extGram.ycc"
{
	yyval.sqlClause= yyvsp[0].sqlClause;
    ;
    break;}
case 561:
#line 4593 "src/extGram.ycc"
{    
	yyval.sqlClause= new JCSqlSortList((JCSqlSortItem *)yyvsp[0].sqlClause);
    ;
    break;}
case 562:
#line 4597 "src/extGram.ycc"
{    
	((JCSqlSortList *)yyvsp[-2].sqlClause)->addElement((JCSqlSortItem *)yyvsp[0].sqlClause);
	yyval.sqlClause= yyvsp[-2].sqlClause;
    ;
    break;}
case 563:
#line 4605 "src/extGram.ycc"
{    
	yyval.sqlClause= new JCSqlSortItem(new JCSqlIdentifier(yyvsp[-2].identifier), yyvsp[-1].sqlIdentifier, (JCSqlConstants::SortOrder)yyvsp[0].flag);
    ;
    break;}
case 564:
#line 4612 "src/extGram.ycc"
{    
	yyval.sqlIdentifier= NULL;
    ;
    break;}
case 566:
#line 4620 "src/extGram.ycc"
{    
	yyval.flag= 0;
    ;
    break;}
case 568:
#line 4627 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::ascending;
    ;
    break;}
case 569:
#line 4631 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::descending;
    ;
    break;}
case 570:
#line 4638 "src/extGram.ycc"
{
	yyval.sqlClause= NULL;
    ;
    break;}
case 572:
#line 4646 "src/extGram.ycc"
{
	yyval.sqlClause= yyvsp[0].sqlClause;
    ;
    break;}
case 573:
#line 4653 "src/extGram.ycc"
{    
	yyval.sqlClause= new JCSqlGroupList((JCSqlGroupItem *)yyvsp[0].sqlClause);
    ;
    break;}
case 574:
#line 4657 "src/extGram.ycc"
{    
	((JCSqlGroupList *)yyvsp[-2].sqlClause)->addElement((JCSqlGroupItem *)yyvsp[0].sqlClause);
	yyval.sqlClause= yyvsp[-2].sqlClause;
    ;
    break;}
case 575:
#line 4665 "src/extGram.ycc"
{    
	yyval.sqlClause= new JCSqlGroupItem(yyvsp[0].sqlIdentifier);
    ;
    break;}
case 576:
#line 4669 "src/extGram.ycc"
{    
	yyval.sqlClause= new JCSqlGroupItem(yyvsp[-1].sqlIdentifier, yyvsp[0].sqlIdentifier);
    ;
    break;}
case 577:
#line 4676 "src/extGram.ycc"
{    
	yyval.sqlIdentifier= yyvsp[0].sqlIdentifier;
    ;
    break;}
case 578:
#line 4683 "src/extGram.ycc"
{
	yyval.sqlExpression= NULL;
    ;
    break;}
case 580:
#line 4690 "src/extGram.ycc"
{
	yyval.sqlExpression= yyvsp[0].sqlExpression;
    ;
    break;}
case 582:
#line 4698 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::orOp);
    ;
    break;}
case 584:
#line 4706 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::andOp);
    ;
    break;}
case 585:
#line 4714 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[0].sqlExpression, NULL, JCSqlOperExpr::notOp);
    ;
    break;}
case 588:
#line 4723 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-3].sqlExpression, new JCSqlBoolCte((JCSqlConstants::TruthValues)yyvsp[0].flag), ((yyvsp[-1].flag == JCSqlOperExpr::notOp) ? JCSqlOperExpr::isnot : JCSqlOperExpr::is));
    ;
    break;}
case 590:
#line 4731 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-1].sqlExpression, NULL, JCSqlOperExpr::parenthesis);
    ;
    break;}
case 601:
#line 4751 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, (JCSqlOperExpr::Operators)yyvsp[-1].flag);
    ;
    break;}
case 602:
#line 4758 "src/extGram.ycc"
{
	JCSqlOperExpr *rangeExpr= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::andOp);
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-5].sqlExpression, rangeExpr, ((yyvsp[-4].flag == JCSqlOperExpr::notOp) ? JCSqlOperExpr::notBetween : JCSqlOperExpr::between));
    ;
    break;}
case 603:
#line 4766 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-3].sqlExpression, yyvsp[0].sqlExpression, ((yyvsp[-2].flag == JCSqlOperExpr::notOp) ? JCSqlOperExpr::notIn : JCSqlOperExpr::in));
    ;
    break;}
case 605:
#line 4774 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlListExpr((JCSqlValueList *)yyvsp[-1].sqlClause);
    ;
    break;}
case 606:
#line 4781 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlValueList(yyvsp[0].sqlExpression)
    ;
    break;}
case 607:
#line 4785 "src/extGram.ycc"
{
	((JCSqlValueList *)yyvsp[-2].sqlClause)->addElement(yyvsp[0].sqlExpression);
	yyval.sqlClause= yyvsp[-2].sqlClause;
    ;
    break;}
case 608:
#line 4793 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-3].sqlExpression, yyvsp[0].sqlExpression, ((yyvsp[-2].flag == JCSqlOperExpr::notOp) ? JCSqlOperExpr::notLike : JCSqlOperExpr::like));
    ;
    break;}
case 609:
#line 4797 "src/extGram.ycc"
{
	JCSqlOperExpr *escapeExpr= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::escape);
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-5].sqlExpression, escapeExpr, ((yyvsp[-4].flag == JCSqlOperExpr::notOp) ? JCSqlOperExpr::notLike : JCSqlOperExpr::like));
    ;
    break;}
case 610:
#line 4805 "src/extGram.ycc"
{
	JCSqlConstantExpr *nullConstant= JCSqlConstantExpr::getPopularConstant(JCSqlConstantExpr::popNullCte);
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-3].sqlExpression, nullConstant, ((yyvsp[-1].flag == JCSqlOperExpr::notOp) ? JCSqlOperExpr::isnot : JCSqlOperExpr::is));
    ;
    break;}
case 611:
#line 4813 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-3].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::mergeSetOperators((JCSqlOperExpr::Operators)yyvsp[-2].flag, (JCSqlConstants::SetQuantifier)yyvsp[-1].flag));
    ;
    break;}
case 612:
#line 4820 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[0].sqlExpression, NULL, JCSqlOperExpr::exists);
    ;
    break;}
case 613:
#line 4827 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[0].sqlExpression, NULL, JCSqlOperExpr::unique);
    ;
    break;}
case 614:
#line 4834 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-3].sqlExpression, yyvsp[0].sqlExpression, (JCSqlOperExpr::Operators)yyvsp[-1].flag);
    ;
    break;}
case 615:
#line 4841 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlOperExpr(yyvsp[-2].sqlExpression, yyvsp[0].sqlExpression, JCSqlOperExpr::overlaps);
    ;
    break;}
case 616:
#line 4848 "src/extGram.ycc"
{
	yyval.flag= JCSqlOperExpr::equal;
    ;
    break;}
case 617:
#line 4852 "src/extGram.ycc"
{
	yyval.flag= JCSqlOperExpr::notEqual;
    ;
    break;}
case 618:
#line 4856 "src/extGram.ycc"
{
	yyval.flag= JCSqlOperExpr::lt;
    ;
    break;}
case 619:
#line 4860 "src/extGram.ycc"
{
	yyval.flag= JCSqlOperExpr::gt;
    ;
    break;}
case 620:
#line 4864 "src/extGram.ycc"
{
	yyval.flag= JCSqlOperExpr::le;
    ;
    break;}
case 621:
#line 4868 "src/extGram.ycc"
{
	yyval.flag= JCSqlOperExpr::ge;
    ;
    break;}
case 622:
#line 4875 "src/extGram.ycc"
{
	yyval.flag= JCSqlOperExpr::mergeSetOperators((JCSqlOperExpr::Operators)yyvsp[-1].flag, (JCSqlConstants::SetQuantifier)yyvsp[0].flag);
     ;
    break;}
case 623:
#line 4881 "src/extGram.ycc"
{
	yyval.flag=  JCSqlOperExpr::match;
    ;
    break;}
case 624:
#line 4885 "src/extGram.ycc"
{
	yyval.flag=  JCSqlOperExpr::matchUnique;
    ;
    break;}
case 625:
#line 4891 "src/extGram.ycc"
{
	yyval.flag= 0;
    ;
    break;}
case 626:
#line 4895 "src/extGram.ycc"
{
	yyval.flag=  JCSqlOperExpr::matchPartial;
    ;
    break;}
case 627:
#line 4899 "src/extGram.ycc"
{
	yyval.flag=  JCSqlOperExpr::matchFull;
    ;
    break;}
case 628:
#line 4906 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::allElements;
    ;
    break;}
case 629:
#line 4910 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::some;
    ;
    break;}
case 630:
#line 4914 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::any;
    ;
    break;}
case 631:
#line 4920 "src/extGram.ycc"
{
	yyval.flag= 0;
    ;
    break;}
case 632:
#line 4924 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::allElements;
    ;
    break;}
case 633:
#line 4931 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::tvTrue;
    ;
    break;}
case 634:
#line 4935 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::tvFalse;
    ;
    break;}
case 635:
#line 4939 "src/extGram.ycc"
{
	yyval.flag= JCSqlConstants::tvUnknown;
    ;
    break;}
case 637:
#line 4947 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlListExpr(yyvsp[-1].sqlClause);
    ;
    break;}
case 641:
#line 4964 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlConstantExpr::getPopularConstant(JCSqlConstantExpr::popNullCte);
    ;
    break;}
case 642:
#line 4971 "src/extGram.ycc"
{
	yyval.sqlExpression= JCSqlConstantExpr::getPopularConstant(JCSqlConstantExpr::popDefaultCte);
    ;
    break;}
case 643:
#line 4978 "src/extGram.ycc"
{    
	yyval.sqlClause= new JCSqlRVConstrList(new JCSqlRowValue(yyvsp[0].sqlExpression));
    ;
    break;}
case 644:
#line 4982 "src/extGram.ycc"
{    
	((JCSqlRVConstrList *)yyvsp[-2].sqlClause)->addElement(new JCSqlRowValue(yyvsp[0].sqlExpression));
	yyval.sqlClause= yyvsp[-2].sqlClause;
    ;
    break;}
case 645:
#line 4990 "src/extGram.ycc"
{
	yyval.sqlClause= new JCSqlTargetList((JCSqlEmbedded *)yyvsp[0].sqlExpression);
    ;
    break;}
case 646:
#line 4994 "src/extGram.ycc"
{
	((JCSqlTargetList *)yyvsp[-2].sqlClause)->addElement((JCSqlEmbedded *)yyvsp[0].sqlExpression);
	yyval.sqlClause= yyvsp[-2].sqlClause;
    ;
    break;}
case 649:
#line 5006 "src/extGram.ycc"
{
	yyval.flag= 0;
    ;
    break;}
case 650:
#line 5010 "src/extGram.ycc"
{
	yyval.flag= JCSqlOperExpr::notOp;
    ;
    break;}
case 651:
#line 5017 "src/extGram.ycc"
{    
	// TODO.
    ;
    break;}
case 652:
#line 5021 "src/extGram.ycc"
{    
	// TODO.
    ;
    break;}
case 653:
#line 5028 "src/extGram.ycc"
{
	yyval.sqlIdentList= new JCSqlIdentList(new JCSqlIdentifier(yyvsp[0].identifier));
    ;
    break;}
case 654:
#line 5032 "src/extGram.ycc"
{
	((JCSqlIdentList *)yyvsp[-2].sqlIdentList)->addElement(new JCSqlIdentifier(yyvsp[0].identifier));
	yyval.sqlIdentList= yyvsp[-2].sqlIdentList;
    ;
    break;}
case 655:
#line 5042 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlConstantExpr();		// TMPTMP !
    ;
    break;}
case 656:
#line 5048 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlConstantExpr();		// TMPTMP !
    ;
    break;}
case 657:
#line 5055 "src/extGram.ycc"
{
	yyval.sqlExpression= new JCSqlConstantExpr();		// TMPTMP !
    ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 5061 "src/extGram.ycc"


/* --------------- Fin de la grammaire --------------- */

