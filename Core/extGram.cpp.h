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


extern YYSTYPE yylval;
