#ifndef BISON_IFM_PARSE_H
# define BISON_IFM_PARSE_H

#ifndef YYSTYPE
typedef union {
    int ival;
    double dval;
    char *sval;
    vscalar *vval;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	ROOM	257
# define	ITEM	258
# define	LINK	259
# define	FROM	260
# define	TAG	261
# define	TO	262
# define	DIR	263
# define	ONEWAY	264
# define	HIDDEN	265
# define	NODROP	266
# define	NOTE	267
# define	TASK	268
# define	AFTER	269
# define	NEED	270
# define	GET	271
# define	SCORE	272
# define	JOIN	273
# define	GO	274
# define	REQUIRE	275
# define	ANY	276
# define	LAST	277
# define	START	278
# define	GOTO	279
# define	MAP	280
# define	EXIT	281
# define	GIVEN	282
# define	LOST	283
# define	KEEP	284
# define	LENGTH	285
# define	TITLE	286
# define	LOSE	287
# define	SAFE	288
# define	BEFORE	289
# define	FOLLOW	290
# define	CMD	291
# define	LEAVE	292
# define	UNDEF	293
# define	FINISH	294
# define	GIVE	295
# define	DROP	296
# define	ALL	297
# define	EXCEPT	298
# define	IT	299
# define	UNTIL	300
# define	TIMES	301
# define	NOLINK	302
# define	NOPATH	303
# define	NONE	304
# define	STYLE	305
# define	ENDSTYLE	306
# define	WITH	307
# define	IGNORE	308
# define	DO	309
# define	NORTH	310
# define	EAST	311
# define	SOUTH	312
# define	WEST	313
# define	NORTHEAST	314
# define	NORTHWEST	315
# define	SOUTHEAST	316
# define	SOUTHWEST	317
# define	UP	318
# define	DOWN	319
# define	IN	320
# define	OUT	321
# define	INTEGER	322
# define	REAL	323
# define	STRING	324
# define	ID	325


extern YYSTYPE yylval;

#endif /* not BISON_IFM_PARSE_H */
