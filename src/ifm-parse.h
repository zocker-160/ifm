typedef union {
    int ival;
    double dval;
    char *sval;
    vscalar *vval;
} YYSTYPE;
#define	ROOM	257
#define	ITEM	258
#define	LINK	259
#define	FROM	260
#define	TAG	261
#define	TO	262
#define	DIR	263
#define	ONEWAY	264
#define	HIDDEN	265
#define	PUZZLE	266
#define	NOTE	267
#define	TASK	268
#define	AFTER	269
#define	NEED	270
#define	GET	271
#define	SCORE	272
#define	JOIN	273
#define	GO	274
#define	SPECIAL	275
#define	ANY	276
#define	LAST	277
#define	START	278
#define	GOTO	279
#define	MAP	280
#define	EXIT	281
#define	GIVEN	282
#define	LOST	283
#define	KEEP	284
#define	LENGTH	285
#define	TITLE	286
#define	LOSE	287
#define	SAFE	288
#define	BEFORE	289
#define	FOLLOW	290
#define	CMD	291
#define	LEAVE	292
#define	UNDEF	293
#define	FINISH	294
#define	GIVE	295
#define	DROP	296
#define	ALL	297
#define	EXCEPT	298
#define	IT	299
#define	UNTIL	300
#define	TIMES	301
#define	NOLINK	302
#define	NOPATH	303
#define	NONE	304
#define	ALIAS	305
#define	STYLE	306
#define	ENDSTYLE	307
#define	WITH	308
#define	IGNORE	309
#define	REQUIRE	310
#define	NODROP	311
#define	NORTH	312
#define	EAST	313
#define	SOUTH	314
#define	WEST	315
#define	NORTHEAST	316
#define	NORTHWEST	317
#define	SOUTHEAST	318
#define	SOUTHWEST	319
#define	UP	320
#define	DOWN	321
#define	IN	322
#define	OUT	323
#define	INTEGER	324
#define	REAL	325
#define	STRING	326
#define	ID	327
#define	VAR	328
#define	PLUS	329
#define	MINUS	330


extern YYSTYPE yylval;
