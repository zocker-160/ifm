
/*  A Bison parser, made from ifm-parse.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

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
#define	NORTH	311
#define	EAST	312
#define	SOUTH	313
#define	WEST	314
#define	NORTHEAST	315
#define	NORTHWEST	316
#define	SOUTHEAST	317
#define	SOUTHWEST	318
#define	UP	319
#define	DOWN	320
#define	IN	321
#define	OUT	322
#define	INTEGER	323
#define	REAL	324
#define	STRING	325
#define	ID	326
#define	VAR	327
#define	PLUS	328
#define	MINUS	329

#line 1 "ifm-parse.y"

/* Input parser */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vars.h>

#include "ifm-map.h"
#include "ifm-util.h"
#include "ifm-vars.h"

#define SET_LIST(object, attr, list)                                    \
        {                                                               \
                vlist *l = vh_pget(object, attr);                       \
                if (l == NULL) {                                        \
                        vh_pstore(object, attr, list);                  \
                        list = NULL;                                    \
                } else {                                                \
                        vl_append(l, list);                             \
                        vl_destroy(list);                               \
                        list = NULL;                                    \
                }                                                       \
        }

#define ATTR(name) \
        (implicit ? "LINK_" #name : #name)

#define RESET_IT \
        itroom = ititem = ittask = NULL

#define WARN_IGNORED(attr) \
        warn("attribute `%s' ignored -- no implicit link", #attr)

#define CHANGE_ERROR(attr) \
        err("can't modify `%s' attribute", #attr)

static vhash *curobj = NULL;    /* Current object */

static vlist *currooms = NULL;  /* Current room list */
static vlist *curitems = NULL;  /* Current item list */
static vlist *curtasks = NULL;  /* Current task list */

static vhash *lastroom = NULL;  /* Last room mentioned */
static vhash *lastitem = NULL;  /* Last item mentioned */
static vhash *lasttask = NULL;  /* Last task mentioned */

static vscalar *itroom = NULL;  /* Room referred to by 'it' */
static vscalar *ititem = NULL;  /* Item referred to by 'it' */
static vscalar *ittask = NULL;  /* Task referred to by 'it' */

static int roomid = 0;          /* Current room ID */
static int itemid = 0;          /* Current item ID */

static vlist *curdirs = NULL;   /* Current direction list */

static int modify = 0;          /* Modification flag */
static int implicit = 0;        /* Implicit-link flag */
static int allflag = 0;         /* All-items flag */
static int repeat = 0;          /* String repeat count */
static int instyle = 0;         /* Set variable in different style? */

#line 68 "ifm-parse.y"
typedef union {
    int ival;
    double dval;
    char *sval;
    vscalar *vval;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		367
#define	YYFLAG		-32768
#define	YYNTBASE	86

#define YYTRANSLATE(x) ((unsigned)(x) <= 329 ? yytranslate[x] : 139)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    79,     2,     2,    84,
    85,    77,    75,     2,    76,     2,    78,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    83,     2,
    74,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    82,     2,     2,     2,     2,     2,     2,
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
    67,    68,    69,    70,    71,    72,    73,    80,    81
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     7,     9,    11,    13,    15,    17,    19,
    21,    23,    27,    31,    35,    36,    42,    43,    49,    50,
    53,    56,    61,    64,    67,    70,    73,    76,    78,    80,
    82,    84,    86,    89,    92,    95,    98,   101,   104,   107,
   111,   115,   118,   121,   123,   125,   127,   130,   132,   134,
   136,   138,   139,   145,   146,   152,   153,   156,   159,   162,
   165,   167,   169,   171,   173,   175,   179,   183,   186,   189,
   192,   195,   197,   200,   202,   205,   207,   209,   213,   215,
   217,   219,   221,   222,   230,   231,   237,   238,   241,   244,
   247,   249,   251,   253,   256,   259,   262,   265,   268,   271,
   275,   279,   282,   285,   287,   288,   296,   297,   303,   304,
   307,   310,   313,   315,   317,   319,   322,   325,   328,   331,
   334,   337,   341,   345,   348,   351,   352,   358,   359,   365,
   366,   369,   372,   375,   378,   381,   384,   387,   392,   397,
   404,   408,   414,   418,   421,   424,   427,   430,   433,   435,
   437,   440,   442,   445,   448,   451,   454,   456,   459,   461,
   463,   465,   467,   469,   471,   477,   484,   490,   497,   503,
   510,   515,   520,   521,   525,   529,   533,   537,   541,   545,
   549,   553,   557,   560,   562,   565,   567,   569,   571,   573,
   576,   578,   581,   585,   587,   589,   591,   593,   595,   597,
   599,   601,   603,   605,   607,   609,   611,   613,   615,   618,
   621,   625,   629,   633,   637,   641,   645,   649,   651,   653,
   655,   657,   660
};

static const short yyrhs[] = {    -1,
    86,    87,     0,    86,     1,     0,    88,     0,    89,     0,
    97,     0,   106,     0,   111,     0,   116,     0,   124,     0,
   128,     0,    32,   137,    83,     0,    26,   137,    83,     0,
    56,   135,    83,     0,     0,     3,   137,    90,    92,    83,
     0,     0,     3,    72,    91,    92,    83,     0,     0,    92,
    93,     0,     7,    72,     0,     9,   131,     6,    72,     0,
     9,   131,     0,    27,   131,     0,     5,    94,     0,    19,
    94,     0,    20,   134,     0,    10,     0,    48,     0,    49,
     0,    24,     0,    40,     0,    16,   102,     0,    35,   121,
     0,    15,   121,     0,    38,   103,     0,    31,   136,     0,
    18,   136,     0,    37,   138,     0,    37,     8,   138,     0,
    37,     6,   138,     0,    13,   137,     0,    52,   129,     0,
    21,     0,    12,     0,    95,     0,    94,    95,     0,    96,
     0,    72,     0,    45,     0,    23,     0,     0,     4,   137,
    98,   100,    83,     0,     0,     4,    72,    99,   100,    83,
     0,     0,   100,   101,     0,     7,    72,     0,    67,    96,
     0,    13,   137,     0,    11,     0,    28,     0,    29,     0,
    55,     0,    30,     0,    30,    54,   102,     0,    30,    46,
   121,     0,    16,   102,     0,    35,   121,     0,    15,   121,
     0,    18,   136,     0,    40,     0,    52,   129,     0,   104,
     0,   102,   104,     0,   102,     0,    43,     0,    43,    44,
   102,     0,   105,     0,    72,     0,    45,     0,    23,     0,
     0,     5,    96,     8,    96,   107,   109,    83,     0,     0,
     5,    72,   108,   109,    83,     0,     0,   109,   110,     0,
     9,   131,     0,    20,   134,     0,    10,     0,    11,     0,
    49,     0,    16,   102,     0,    35,   121,     0,    15,   121,
     0,    38,   103,     0,    31,   136,     0,    37,   138,     0,
    37,     8,   138,     0,    37,     6,   138,     0,     7,    72,
     0,    52,   129,     0,    21,     0,     0,    19,    96,     8,
    96,   112,   114,    83,     0,     0,    19,    72,   113,   114,
    83,     0,     0,   114,   115,     0,    20,   133,     0,    20,
   134,     0,    10,     0,    11,     0,    49,     0,    16,   102,
     0,    35,   121,     0,    15,   121,     0,    38,   103,     0,
    31,   136,     0,    37,   138,     0,    37,     8,   138,     0,
    37,     6,   138,     0,     7,    72,     0,    52,   129,     0,
     0,    14,   137,   117,   119,    83,     0,     0,    14,    72,
   118,   119,    83,     0,     0,   119,   120,     0,     7,    72,
     0,    15,   121,     0,    16,   102,     0,    41,   102,     0,
    17,   102,     0,    42,   103,     0,    42,   103,    46,   121,
     0,    42,   103,    67,    96,     0,    42,   103,    67,    96,
    46,   121,     0,    42,    67,    96,     0,    42,    67,    96,
    46,   121,     0,    42,    46,   121,     0,    33,   102,     0,
    25,    96,     0,    36,   123,     0,    67,    96,     0,    67,
    22,     0,    55,     0,    34,     0,    18,   136,     0,    40,
     0,    37,   138,     0,    37,    50,     0,    13,   137,     0,
    52,   129,     0,   122,     0,   121,   122,     0,   123,     0,
    72,     0,    45,     0,    23,     0,   125,     0,   126,     0,
    72,    74,   135,   127,    83,     0,    72,    72,    74,   135,
   127,    83,     0,    72,    74,    71,   127,    83,     0,    72,
    72,    74,    71,   127,    83,     0,    72,    74,    39,   127,
    83,     0,    72,    72,    74,    39,   127,    83,     0,    72,
    51,    72,    83,     0,    72,    51,    39,    83,     0,     0,
    67,    52,    72,     0,    67,    52,    12,     0,    67,    52,
    21,     0,    52,    72,    83,     0,    52,    12,    83,     0,
    52,    21,    83,     0,    53,    72,    83,     0,    53,    12,
    83,     0,    53,    21,    83,     0,    53,    83,     0,   130,
     0,   129,   130,     0,    72,     0,    12,     0,    21,     0,
   132,     0,   131,   132,     0,   133,     0,   133,   136,     0,
   133,    47,   136,     0,    57,     0,    58,     0,    59,     0,
    60,     0,    61,     0,    62,     0,    63,     0,    64,     0,
    67,     0,    68,     0,    65,     0,    66,     0,    69,     0,
    70,     0,    73,     0,    75,   135,     0,    76,   135,     0,
   135,    75,   135,     0,   135,    76,   135,     0,   135,    77,
   135,     0,   135,    78,   135,     0,   135,    82,   135,     0,
   135,    79,   135,     0,    84,   135,    85,     0,   135,     0,
    71,     0,    73,     0,   137,     0,   137,   136,     0,   137,
    47,   136,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   107,   108,   109,   112,   113,   114,   115,   116,   117,   118,
   119,   126,   130,   136,   150,   160,   253,   261,   267,   268,
   271,   278,   297,   312,   325,   340,   355,   359,   363,   367,
   371,   375,   379,   383,   387,   391,   397,   401,   405,   410,
   415,   420,   424,   425,   431,   439,   440,   443,   451,   455,
   462,   475,   483,   492,   500,   506,   507,   510,   517,   521,
   525,   529,   534,   538,   542,   546,   550,   554,   558,   562,
   566,   570,   574,   577,   578,   581,   582,   583,   586,   594,
   598,   605,   618,   626,   631,   639,   645,   646,   649,   654,
   658,   662,   666,   670,   674,   678,   682,   688,   692,   697,
   702,   707,   714,   715,   727,   735,   740,   748,   754,   755,
   758,   762,   766,   770,   774,   778,   782,   786,   790,   796,
   800,   805,   810,   815,   822,   829,   836,   847,   855,   861,
   862,   865,   872,   876,   880,   884,   888,   894,   901,   908,
   916,   920,   925,   929,   933,   937,   941,   945,   949,   953,
   957,   961,   965,   970,   974,   978,   981,   982,   985,   993,
   997,  1004,  1017,  1023,  1026,  1030,  1035,  1039,  1044,  1048,
  1055,  1059,  1065,  1066,  1071,  1076,  1087,  1091,  1095,  1099,
  1103,  1107,  1111,  1117,  1118,  1121,  1126,  1131,  1142,  1143,
  1146,  1152,  1161,  1173,  1174,  1175,  1176,  1177,  1178,  1179,
  1180,  1183,  1184,  1185,  1186,  1193,  1194,  1195,  1196,  1197,
  1198,  1199,  1200,  1201,  1202,  1203,  1204,  1207,  1210,  1211,
  1214,  1219,  1226
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ROOM","ITEM",
"LINK","FROM","TAG","TO","DIR","ONEWAY","HIDDEN","PUZZLE","NOTE","TASK","AFTER",
"NEED","GET","SCORE","JOIN","GO","SPECIAL","ANY","LAST","START","GOTO","MAP",
"EXIT","GIVEN","LOST","KEEP","LENGTH","TITLE","LOSE","SAFE","BEFORE","FOLLOW",
"CMD","LEAVE","UNDEF","FINISH","GIVE","DROP","ALL","EXCEPT","IT","UNTIL","TIMES",
"NOLINK","NOPATH","NONE","ALIAS","STYLE","ENDSTYLE","WITH","IGNORE","REQUIRE",
"NORTH","EAST","SOUTH","WEST","NORTHEAST","NORTHWEST","SOUTHEAST","SOUTHWEST",
"UP","DOWN","IN","OUT","INTEGER","REAL","STRING","ID","VAR","'='","'+'","'-'",
"'*'","'/'","'%'","PLUS","MINUS","'^'","';'","'('","')'","stmt_list","stmt",
"ctrl_stmt","room_stmt","@1","@2","room_attrs","room_attr","room_list","room_elt",
"room","item_stmt","@3","@4","item_attrs","item_attr","item_list","item_list_all",
"item_elt","item","link_stmt","@5","@6","link_attrs","link_attr","join_stmt",
"@7","@8","join_attrs","join_attr","task_stmt","@9","@10","task_attrs","task_attr",
"task_list","task_elt","task","vars_stmt","set_var","alias_var","in_style","style_stmt",
"style_list","style_elt","dir_list","dir_elt","compass","otherdir","exp","integer",
"string","string_repeat", NULL
};
#endif

static const short yyr1[] = {     0,
    86,    86,    86,    87,    87,    87,    87,    87,    87,    87,
    87,    88,    88,    88,    90,    89,    91,    89,    92,    92,
    93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
    93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
    93,    93,    93,    93,    93,    94,    94,    95,    96,    96,
    96,    98,    97,    99,    97,   100,   100,   101,   101,   101,
   101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
   101,   101,   101,   102,   102,   103,   103,   103,   104,   105,
   105,   105,   107,   106,   108,   106,   109,   109,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   110,   112,   111,   113,   111,   114,   114,
   115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
   115,   115,   115,   115,   115,   117,   116,   118,   116,   119,
   119,   120,   120,   120,   120,   120,   120,   120,   120,   120,
   120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
   120,   120,   120,   120,   120,   120,   121,   121,   122,   123,
   123,   123,   124,   124,   125,   125,   125,   125,   125,   125,
   126,   126,   127,   127,   127,   127,   128,   128,   128,   128,
   128,   128,   128,   129,   129,   130,   130,   130,   131,   131,
   132,   132,   132,   133,   133,   133,   133,   133,   133,   133,
   133,   134,   134,   134,   134,   135,   135,   135,   135,   135,
   135,   135,   135,   135,   135,   135,   135,   136,   137,   137,
   138,   138,   138
};

static const short yyr2[] = {     0,
     0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
     1,     3,     3,     3,     0,     5,     0,     5,     0,     2,
     2,     4,     2,     2,     2,     2,     2,     1,     1,     1,
     1,     1,     2,     2,     2,     2,     2,     2,     2,     3,
     3,     2,     2,     1,     1,     1,     2,     1,     1,     1,
     1,     0,     5,     0,     5,     0,     2,     2,     2,     2,
     1,     1,     1,     1,     1,     3,     3,     2,     2,     2,
     2,     1,     2,     1,     2,     1,     1,     3,     1,     1,
     1,     1,     0,     7,     0,     5,     0,     2,     2,     2,
     1,     1,     1,     2,     2,     2,     2,     2,     2,     3,
     3,     2,     2,     1,     0,     7,     0,     5,     0,     2,
     2,     2,     1,     1,     1,     2,     2,     2,     2,     2,
     2,     3,     3,     2,     2,     0,     5,     0,     5,     0,
     2,     2,     2,     2,     2,     2,     2,     4,     4,     6,
     3,     5,     3,     2,     2,     2,     2,     2,     1,     1,
     2,     1,     2,     2,     2,     2,     1,     2,     1,     1,
     1,     1,     1,     1,     5,     6,     5,     6,     5,     6,
     4,     4,     0,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     2,     1,     2,     1,     1,     1,     1,     2,
     1,     2,     3,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
     3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
     1,     2,     3
};

static const short yydefact[] = {     1,
     0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     2,     4,     5,     6,     7,     8,     9,
    10,   163,   164,    11,   219,    17,   220,    15,    54,    52,
    51,    50,    85,     0,   128,   126,   107,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   183,   206,   207,   208,
     0,     0,     0,     0,     0,     0,     0,    19,    19,    56,
    56,    87,     0,   130,   130,   109,     0,    13,    12,   178,
   179,   177,   181,   182,   180,   209,   210,     0,     0,     0,
     0,     0,     0,     0,    14,     0,     0,     0,   173,   173,
   173,     0,     0,     0,     0,     0,    49,    83,     0,     0,
     0,   105,   217,   211,   212,   213,   214,   216,   215,   172,
   171,   173,   173,   173,     0,     0,     0,     0,     0,     0,
     0,    28,    45,     0,     0,     0,     0,     0,     0,    44,
    31,     0,     0,     0,     0,     0,    32,    29,    30,     0,
    18,    20,    16,     0,    61,     0,     0,     0,     0,    62,
    63,    65,     0,    72,     0,    64,     0,    55,    57,    53,
     0,     0,    91,    92,     0,     0,     0,   104,     0,     0,
     0,     0,    93,     0,    86,    88,    87,     0,     0,     0,
     0,     0,     0,     0,     0,   150,     0,     0,   152,     0,
     0,     0,   149,     0,   129,   131,   127,     0,   113,   114,
     0,     0,     0,     0,     0,     0,     0,   115,     0,   108,
   110,   109,     0,     0,     0,     0,   169,   167,   165,    25,
    46,    48,    21,   194,   195,   196,   197,   198,   199,   200,
   201,    23,   189,   191,    42,   162,   161,   160,    35,   157,
   159,    82,    81,    80,    33,    74,    79,   218,    38,    26,
   204,   205,   202,   203,    27,    24,    37,    34,     0,     0,
   221,    39,    77,    76,    36,   187,   188,   186,    43,   184,
    58,    60,    70,    68,    71,     0,     0,    69,    73,    59,
   102,    89,    96,    94,    90,    98,    95,     0,     0,    99,
    97,   103,     0,   132,   155,   133,   134,   136,   151,   145,
   144,   146,   154,   153,   135,     0,     0,   137,   156,   148,
   147,   124,   118,   116,   111,   112,   120,   117,     0,     0,
   121,   119,   125,     0,   170,   168,   166,   175,   176,   174,
    47,     0,   190,     0,   192,   158,    75,    41,    40,     0,
   222,     0,   185,    67,    66,   101,   100,    84,   143,   141,
     0,     0,   123,   122,   106,    22,   193,   223,    78,     0,
   138,   139,   142,     0,   140,     0,     0
};

static const short yydefgoto[] = {     1,
    14,    15,    16,    59,    58,    92,   142,   220,   221,   222,
    17,    61,    60,    94,   159,   264,   265,   246,   247,    18,
   177,    62,    96,   176,    19,   212,    66,   101,   211,    20,
    65,    64,    99,   196,   239,   240,   241,    21,    22,    23,
   116,    24,   269,   270,   232,   233,   234,   255,   248,   249,
   261,   262
};

static const short yypact[] = {-32768,
   571,-32768,   290,   348,    66,   357,   174,   -33,   -33,     1,
     4,   276,   118,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,     7,    18,-32768,-32768,     7,    27,   -34,    -4,
    -1,     0,     9,    20,    35,    40,-32768,-32768,-32768,-32768,
   276,   276,   276,   504,   -31,   -24,   302,-32768,-32768,-32768,
-32768,-32768,   211,-32768,-32768,-32768,   211,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   -15,   -15,   478,   276,   276,
   276,   276,   276,   276,-32768,    43,    46,   392,    11,    11,
   251,   223,   272,    84,   397,   165,-32768,-32768,   298,   351,
   475,-32768,-32768,   116,   116,   -15,   -15,   -15,   -15,-32768,
-32768,    11,    11,   251,    80,    50,    54,    59,   211,    26,
   572,-32768,-32768,   -33,   214,   217,   276,   211,   158,-32768,
-32768,   572,   276,   214,    15,   105,-32768,-32768,-32768,    44,
-32768,-32768,-32768,    73,-32768,   -33,   214,   217,   276,-32768,
-32768,    31,   214,-32768,    44,-32768,   211,-32768,-32768,-32768,
    75,   572,-32768,-32768,   214,   217,   158,-32768,   276,   214,
    23,   105,-32768,    44,-32768,-32768,-32768,    83,   -33,   214,
   217,   217,   276,   211,   217,-32768,   214,   195,-32768,   217,
   206,    44,-32768,    99,-32768,-32768,-32768,    87,-32768,-32768,
   214,   217,   547,   276,   214,    36,   105,-32768,    44,-32768,
-32768,-32768,    81,   101,   104,    45,-32768,-32768,-32768,   211,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   337,-32768,   136,-32768,-32768,-32768,-32768,   214,-32768,
-32768,-32768,-32768,-32768,   217,-32768,-32768,   543,-32768,   211,
-32768,-32768,-32768,-32768,-32768,   572,-32768,   214,   -33,   -33,
   432,-32768,   119,   217,-32768,-32768,-32768,-32768,    44,-32768,
-32768,-32768,   214,   217,-32768,   214,   217,   214,    44,-32768,
-32768,   572,   214,   217,-32768,-32768,   214,   -33,   -33,-32768,
-32768,    44,   435,-32768,-32768,   214,   217,   217,-32768,-32768,
   217,-32768,-32768,-32768,   217,   214,   211,   -16,    44,-32768,
-32768,-32768,   214,   217,-32768,-32768,-32768,   214,   -33,   -33,
-32768,-32768,    44,   510,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   127,-32768,   276,-32768,-32768,-32768,-32768,-32768,   276,
-32768,   217,-32768,   214,   217,-32768,-32768,-32768,   214,   142,
   214,   211,-32768,-32768,-32768,-32768,-32768,-32768,   217,   214,
   214,   161,   214,   214,   214,   213,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,   157,-32768,   125,  -202,    -5,
-32768,-32768,-32768,   194,-32768,  -121,  -148,  -144,-32768,-32768,
-32768,-32768,    88,-32768,-32768,-32768,-32768,    52,-32768,-32768,
-32768,-32768,   192,-32768,  -133,  -203,    82,-32768,-32768,-32768,
   326,-32768,   -84,  -101,   -99,  -228,    64,  -157,   485,  -130,
     3,  -154
};


#define	YYLAST		643


static const short yytable[] = {    34,
   258,    38,   257,   333,   245,    28,    30,    86,    36,   285,
    39,    40,    41,   273,   -49,    44,   290,   331,   275,   278,
   259,    42,   260,   291,    45,    63,   274,   333,   288,   351,
   289,   283,   256,   304,    67,   336,   287,    25,   286,    27,
    87,   319,   308,   320,   284,   316,   296,   331,    68,    88,
   352,   321,   299,   333,   336,   266,   328,    98,   322,   297,
   298,   102,   282,   301,   267,   329,    84,   313,   305,   336,
   279,   318,    43,   317,   336,    46,   276,   115,    69,   336,
   314,    70,    71,   336,   277,    25,    47,    27,    31,   292,
   144,    72,   336,    25,   145,    27,   146,   223,   147,   148,
   337,   149,    73,   335,   338,   339,    25,   309,    27,   336,
    32,   150,   151,   152,   336,   268,   330,    74,   153,   337,
   310,    31,    75,   154,   323,   110,   235,   242,   111,   337,
   341,   216,   217,   346,   347,   155,   218,    33,   156,   337,
   336,   219,   344,    32,   271,   336,   281,   263,   272,   243,
   157,   280,   337,   337,   294,   345,   337,   336,   312,   336,
   337,   336,   342,   325,   353,   354,   158,   343,    55,   337,
    97,   161,   349,   162,   163,   164,   244,   343,   300,   165,
   166,   295,   334,   326,   167,   168,   327,   360,   311,    56,
   343,    57,    81,    82,    83,   169,    31,    84,   356,   170,
   337,   171,   172,   357,    48,    49,   364,   343,    50,   358,
    51,    52,   367,   173,   337,    93,   174,   361,    32,    53,
   359,   343,   251,   252,   253,   254,   363,   119,   242,   120,
   365,   121,   122,    31,   123,   124,   236,   125,   126,   242,
   127,   128,   129,   130,   303,    37,   131,   175,   263,   132,
   243,   306,   250,   133,    95,    32,   100,   134,   237,   135,
   136,   243,   137,   324,   293,    25,   315,    27,   302,     0,
   138,   139,   307,     0,   140,     0,   119,   244,   120,     0,
   121,   122,    97,   123,   124,   238,   125,   126,   244,   127,
   128,   129,   130,     0,     0,   131,     0,     0,   132,     0,
     0,   350,   133,     0,   178,   141,   134,     0,   135,   136,
   179,   137,   180,   181,   182,   183,     0,   115,     0,   138,
   139,     0,   184,   140,     0,    79,    80,    81,    82,    83,
   185,   186,    84,   187,   188,     0,     0,   189,   190,   191,
    89,     0,   332,     0,    48,    49,   362,     0,    50,   192,
    51,    52,   193,     0,   143,     0,     0,   178,     0,    53,
    25,    26,    27,   179,   194,   180,   181,   182,   183,     0,
    48,    49,    90,     0,    50,   184,    51,    52,     0,     0,
   195,     0,     0,   185,   186,    53,   187,   188,     0,     0,
   189,   190,   191,   224,   225,   226,   227,   228,   229,   230,
   231,     0,   192,   144,     0,   193,     0,   145,     0,   146,
     0,   147,   148,     0,   149,   117,   118,   194,    25,    29,
    27,     0,     0,     0,   150,   151,   152,    25,    35,    27,
   112,   153,     0,   197,     0,     0,   154,   213,   214,   215,
     0,   161,     0,   162,   163,   164,     0,     0,   155,   165,
   166,   156,     0,     0,   167,   168,     0,     0,     0,     0,
    48,    49,   113,   157,    50,   169,    51,    52,     0,   170,
     0,   171,   172,     0,     0,    53,     0,     0,   340,   160,
     0,   198,     0,   173,   199,   200,   174,     0,     0,   201,
   202,     0,     0,     0,   203,     0,    54,     0,     0,     0,
    48,    49,     0,     0,    50,   204,    51,    52,     0,   205,
     0,   206,   207,     0,     0,    53,   198,   348,     0,   199,
   200,     0,     0,   208,   201,   202,   209,     0,     0,   203,
     0,     0,     0,     0,     0,    76,    77,    78,     0,     0,
   204,    91,     0,     0,   205,     0,   206,   207,     0,     0,
     0,     0,    79,    80,    81,    82,    83,   210,   208,    84,
     0,   209,   103,   104,   105,   106,   107,   108,   109,     0,
   366,     2,   114,     3,     4,     5,     0,     0,    79,    80,
    81,    82,    83,     0,     6,    84,    85,     0,     0,     7,
     0,     0,   355,     0,     0,     0,     8,     0,     0,     0,
     0,     0,     9,   224,   225,   226,   227,   228,   229,   230,
   231,   251,   252,   253,   254,     0,     0,    79,    80,    81,
    82,    83,    10,    11,    84,     0,    12,     0,   224,   225,
   226,   227,   228,   229,   230,   231,     0,     0,     0,     0,
     0,     0,    13
};

static const short yycheck[] = {     5,
   134,     7,   133,   232,   126,     3,     4,    39,     6,   167,
     8,     9,    12,   147,     8,    12,   171,   220,   149,   153,
     6,    21,     8,   172,    21,     8,   148,   256,     6,    46,
     8,   165,   132,   188,     8,   239,   170,    71,   169,    73,
    72,     6,   191,     8,   166,   203,   180,   250,    83,    74,
    67,   206,   183,   282,   258,    12,    12,    63,   207,   181,
   182,    67,   162,   185,    21,    21,    82,   201,   190,   273,
   155,   205,    72,   204,   278,    72,    46,    67,    83,   283,
   202,    83,    83,   287,    54,    71,    83,    73,    23,   174,
     7,    83,   296,    71,    11,    73,    13,    72,    15,    16,
   245,    18,    83,   234,   259,   260,    71,   192,    73,   313,
    45,    28,    29,    30,   318,    72,    72,    83,    35,   264,
    22,    23,    83,    40,   209,    83,   124,    23,    83,   274,
   261,    52,    83,   288,   289,    52,    83,    72,    55,   284,
   344,    83,   276,    45,    72,   349,    72,    43,   146,    45,
    67,   157,   297,   298,    72,   277,   301,   361,    72,   363,
   305,   365,    44,    83,   319,   320,    83,   269,    51,   314,
    72,     7,   306,     9,    10,    11,    72,   279,   184,    15,
    16,   179,    47,    83,    20,    21,    83,    46,   194,    72,
   292,    74,    77,    78,    79,    31,    23,    82,    72,    35,
   345,    37,    38,   334,    69,    70,    46,   309,    73,   340,
    75,    76,     0,    49,   359,    59,    52,   351,    45,    84,
   342,   323,    65,    66,    67,    68,   360,     5,    23,     7,
   364,     9,    10,    23,    12,    13,    23,    15,    16,    23,
    18,    19,    20,    21,    50,    72,    24,    83,    43,    27,
    45,    46,   128,    31,    61,    45,    65,    35,    45,    37,
    38,    45,    40,   212,   177,    71,   203,    73,   187,    -1,
    48,    49,    67,    -1,    52,    -1,     5,    72,     7,    -1,
     9,    10,    72,    12,    13,    72,    15,    16,    72,    18,
    19,    20,    21,    -1,    -1,    24,    -1,    -1,    27,    -1,
    -1,   307,    31,    -1,     7,    83,    35,    -1,    37,    38,
    13,    40,    15,    16,    17,    18,    -1,    67,    -1,    48,
    49,    -1,    25,    52,    -1,    75,    76,    77,    78,    79,
    33,    34,    82,    36,    37,    -1,    -1,    40,    41,    42,
    39,    -1,     6,    -1,    69,    70,   352,    -1,    73,    52,
    75,    76,    55,    -1,    83,    -1,    -1,     7,    -1,    84,
    71,    72,    73,    13,    67,    15,    16,    17,    18,    -1,
    69,    70,    71,    -1,    73,    25,    75,    76,    -1,    -1,
    83,    -1,    -1,    33,    34,    84,    36,    37,    -1,    -1,
    40,    41,    42,    57,    58,    59,    60,    61,    62,    63,
    64,    -1,    52,     7,    -1,    55,    -1,    11,    -1,    13,
    -1,    15,    16,    -1,    18,    90,    91,    67,    71,    72,
    73,    -1,    -1,    -1,    28,    29,    30,    71,    72,    73,
    39,    35,    -1,    83,    -1,    -1,    40,   112,   113,   114,
    -1,     7,    -1,     9,    10,    11,    -1,    -1,    52,    15,
    16,    55,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,
    69,    70,    71,    67,    73,    31,    75,    76,    -1,    35,
    -1,    37,    38,    -1,    -1,    84,    -1,    -1,    47,    83,
    -1,     7,    -1,    49,    10,    11,    52,    -1,    -1,    15,
    16,    -1,    -1,    -1,    20,    -1,    12,    -1,    -1,    -1,
    69,    70,    -1,    -1,    73,    31,    75,    76,    -1,    35,
    -1,    37,    38,    -1,    -1,    84,     7,    83,    -1,    10,
    11,    -1,    -1,    49,    15,    16,    52,    -1,    -1,    20,
    -1,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    -1,
    31,    57,    -1,    -1,    35,    -1,    37,    38,    -1,    -1,
    -1,    -1,    75,    76,    77,    78,    79,    83,    49,    82,
    -1,    52,    85,    79,    80,    81,    82,    83,    84,    -1,
     0,     1,    88,     3,     4,     5,    -1,    -1,    75,    76,
    77,    78,    79,    -1,    14,    82,    83,    -1,    -1,    19,
    -1,    -1,    83,    -1,    -1,    -1,    26,    -1,    -1,    -1,
    -1,    -1,    32,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    66,    67,    68,    -1,    -1,    75,    76,    77,
    78,    79,    52,    53,    82,    -1,    56,    -1,    57,    58,
    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
    -1,    -1,    72
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/lib/bison.simple"
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

#line 217 "/usr/lib/bison.simple"

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

case 12:
#line 127 "ifm-parse.y"
{
                    vh_sstore(map, "TITLE", yyvsp[-1].sval);
                ;
    break;}
case 13:
#line 131 "ifm-parse.y"
{
                    if (sectnames == NULL)
                        sectnames = vl_create();
                    vl_spush(sectnames, yyvsp[-1].sval);
                ;
    break;}
case 14:
#line 137 "ifm-parse.y"
{
                    float version;
                    sscanf(VERSION, "%f", &version);
                    if (yyvsp[-1].dval - version > 0.001)
                        fatal("version %g of IFM is required (this is %s)",
                              yyvsp[-1].dval, VERSION);
                ;
    break;}
case 15:
#line 151 "ifm-parse.y"
{
                    curobj = vh_create();
		    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_istore(curobj, "ID", ++roomid);
                    vh_pstore(curobj, "STYLE", current_styles());
                    vh_pstore(curobj, "LINK_STYLE", current_styles());
                    implicit = 0;
                    modify = 0;
		;
    break;}
case 16:
#line 161 "ifm-parse.y"
{
                    vhash *near, *link, *sect = NULL;
                    vlist *list, *dirs;
                    char *str;

                    /* Build new room */
                    vl_ppush(rooms, curobj);

                    if (startroom == NULL)
                        startroom = curobj;

                    /* Put it on appropriate section */
                    if ((near = vh_pget(curobj, "NEAR")) != NULL)
                        sect = vh_pget(near, "SECT");

                    if (sect == NULL) {
                        sect = vh_create();
                        vl_ppush(sects, sect);
                        vh_istore(sect, "NUM", vl_length(sects));
                        vh_pstore(sect, "ROOMS", vl_create());
                        vh_pstore(sect, "LINKS", vl_create());
                    }

                    vh_pstore(curobj, "SECT", sect);
                    list = vh_pget(sect, "ROOMS");
                    vl_punshift(list, curobj);

                    /* Build implicit link (if any) */
                    if ((dirs = vh_pget(curobj, "DIR")) != NULL) {
                        link = vh_create();
                        vh_pstore(curobj, "LINK", link);

                        vh_pstore(link, "FROM", near);
                        vh_pstore(link, "TO", curobj);

                        vh_istore(link, "GO",
                                  vh_iget(curobj, "GO"));
                        vh_istore(link, "ONEWAY",
                                  vh_iget(curobj, "ONEWAY"));
                        vh_istore(link, "SPECIAL",
                                  vh_iget(curobj, "SPECIAL"));
                        vh_istore(link, "NOLINK",
                                  vh_iget(curobj, "NOLINK"));
                        vh_istore(link, "NOPATH",
                                  vh_iget(curobj, "NOPATH"));
                        vh_istore(link, "LEN",
                                  vh_iget(curobj, "LEN"));
                        vh_pstore(link, "BEFORE",
                                  vh_pget(curobj, "LINK_BEFORE"));
                        vh_pstore(link, "AFTER",
                                  vh_pget(curobj, "LINK_AFTER"));
                        vh_pstore(link, "NEED",
                                  vh_pget(curobj, "LINK_NEED"));
                        vh_pstore(link, "LEAVE",
                                  vh_pget(curobj, "LINK_LEAVE"));
                        vh_istore(link, "LEAVEALL",
                                  vh_iget(curobj, "LINK_LEAVEALL"));
                        vh_pstore(link, "STYLE",
                                  vh_pget(curobj, "LINK_STYLE"));
                        vh_pstore(link, "FROM_CMD",
                                  vh_pget(curobj, "FROM_CMD"));
                        vh_pstore(link, "TO_CMD",
                                  vh_pget(curobj, "TO_CMD"));

                        if (vh_exists(curobj, "TAG"))
                            set_tag("link", vh_sgetref(curobj, "TAG"),
                                    link, linktags);

                        vh_pstore(link, "DIR", dirs);
                        vl_ppush(links, link);
                    }

                    /* Warn about ignored attributes */
                    if (dirs == NULL || vh_iget(curobj, "NOLINK")) {
                        if (vh_exists(curobj, "GO"))
                            WARN_IGNORED(go);
                        if (vh_exists(curobj, "ONEWAY"))
                            WARN_IGNORED(oneway);
                        if (vh_exists(curobj, "LEN"))
                            WARN_IGNORED(length);
                        if (vh_exists(curobj, "NOPATH"))
                            WARN_IGNORED(nopath);
                        if (vh_exists(curobj, "TO_CMD"))
                            WARN_IGNORED(cmd);
                    }

                    if (dirs == NULL && vh_iget(curobj, "NOLINK"))
                        WARN_IGNORED(nolink);

                    lastroom = curobj;
                    RESET_IT;
                ;
    break;}
case 17:
#line 254 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(roomtags, yyvsp[0].sval)) == NULL) {
                        err("room tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 18:
#line 262 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 21:
#line 272 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("room", yyvsp[0].sval, curobj, roomtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 22:
#line 279 "ifm-parse.y"
{
                    vhash *room;

                    if (!modify) {
                        implicit = 1;

                        vh_pstore(curobj, "DIR", curdirs);
                        curdirs = NULL;

                        room = vh_pget(roomtags, yyvsp[0].sval);
                        if (room != NULL)
                            vh_pstore(curobj, "NEAR", room);
                        else
                            err("room tag `%s' not yet defined", yyvsp[0].sval);
                    } else {
                        CHANGE_ERROR(from);
                    }
		;
    break;}
case 23:
#line 298 "ifm-parse.y"
{
                    implicit = 1;

                    if (modify && !vh_exists(curobj, "DIR"))
                        CHANGE_ERROR(dir);

                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;

                    if (lastroom == NULL)
                        err("no last room");
                    else
                        vh_pstore(curobj, "NEAR", lastroom);
		;
    break;}
case 24:
#line 313 "ifm-parse.y"
{
                    vscalar *elt;
                    int dir;

                    vl_foreach(elt, curdirs) {
                        dir = vs_iget(elt);
                        room_exit(curobj, dirinfo[dir].xoff,
                                  dirinfo[dir].yoff, 1);
                    }

                    curdirs = NULL;
		;
    break;}
case 25:
#line 326 "ifm-parse.y"
{
                    vscalar *elt;
                    vhash *link;

                    vl_foreach(elt, currooms) {
                        link = vh_create();
                        vh_pstore(link, "FROM", curobj);
                        vh_store(link, "TO", vs_copy(elt));
                        vl_ppush(links, link);
                    }

                    vl_destroy(currooms);
                    currooms = NULL;
		;
    break;}
case 26:
#line 341 "ifm-parse.y"
{
                    vscalar *elt;
                    vhash *join;

                    vl_foreach(elt, currooms) {
                        join = vh_create();
                        vh_pstore(join, "FROM", curobj);
                        vh_store(join, "TO", vs_copy(elt));
                        vl_ppush(joins, join);
                    }

                    vl_destroy(currooms);
                    currooms = NULL;
		;
    break;}
case 27:
#line 356 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 28:
#line 360 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 29:
#line 364 "ifm-parse.y"
{
                    vh_istore(curobj, "NOLINK", 1);
		;
    break;}
case 30:
#line 368 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 31:
#line 372 "ifm-parse.y"
{
                    startroom = curobj;
		;
    break;}
case 32:
#line 376 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 33:
#line 380 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(NEED), curitems);
                ;
    break;}
case 34:
#line 384 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		;
    break;}
case 35:
#line 388 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		;
    break;}
case 36:
#line 392 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                ;
    break;}
case 37:
#line 398 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 38:
#line 402 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 39:
#line 406 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 40:
#line 411 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 41:
#line 416 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 42:
#line 421 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 44:
#line 426 "ifm-parse.y"
{
                    obsolete("`special' attribute", "`style special'");
                    add_attr(curobj, ATTR(STYLE), "special");
                    ref_style("special");
		;
    break;}
case 45:
#line 432 "ifm-parse.y"
{
                    obsolete("`puzzle' attribute", "`style puzzle'");
                    add_attr(curobj, ATTR(STYLE), "puzzle");
                    ref_style("puzzle");
		;
    break;}
case 48:
#line 444 "ifm-parse.y"
{
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, yyvsp[0].vval);
		;
    break;}
case 49:
#line 452 "ifm-parse.y"
{
                    yyval.vval = itroom = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 50:
#line 456 "ifm-parse.y"
{
                    if (itroom == NULL)
                        err("no room referred to by `it'");
                    else
                        yyval.vval = vs_copy(itroom);
                ;
    break;}
case 51:
#line 463 "ifm-parse.y"
{
                    if (lastroom == NULL)
                        err("no room referred to by `last'");
                    else
                        yyval.vval = itroom = vs_pcreate(lastroom);
                ;
    break;}
case 52:
#line 476 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_istore(curobj, "ID", ++itemid);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 53:
#line 484 "ifm-parse.y"
{
                    if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lastitem = curobj;
                    vl_ppush(items, curobj);
                    RESET_IT;
		;
    break;}
case 54:
#line 493 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(itemtags, yyvsp[0].sval)) == NULL) {
                        err("item tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 55:
#line 501 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 58:
#line 511 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("item", yyvsp[0].sval, curobj, itemtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 59:
#line 518 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 60:
#line 522 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 61:
#line 526 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 62:
#line 530 "ifm-parse.y"
{
                    obsolete("`given' attribute", "task `give' attribute");
                    vh_istore(curobj, "GIVEN", 1);
		;
    break;}
case 63:
#line 535 "ifm-parse.y"
{
                    vh_istore(curobj, "LOST", 1);
		;
    break;}
case 64:
#line 539 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 65:
#line 543 "ifm-parse.y"
{
                    vh_istore(curobj, "KEEP", 1);
		;
    break;}
case 66:
#line 547 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_WITH", curitems);
		;
    break;}
case 67:
#line 551 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_UNTIL", curtasks);
		;
    break;}
case 68:
#line 555 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 69:
#line 559 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
                ;
    break;}
case 70:
#line 563 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
                ;
    break;}
case 71:
#line 567 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 72:
#line 571 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 76:
#line 581 "ifm-parse.y"
{ allflag = 0; ;
    break;}
case 77:
#line 582 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 78:
#line 583 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 79:
#line 587 "ifm-parse.y"
{
                    if (curitems == NULL)
                        curitems = vl_create();
                    vl_push(curitems, yyvsp[0].vval);
		;
    break;}
case 80:
#line 595 "ifm-parse.y"
{
                    yyval.vval = ititem = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 81:
#line 599 "ifm-parse.y"
{
                    if (ititem == NULL)
                        err("no item referred to by `it'");
                    else
                        yyval.vval = vs_copy(ititem);
                ;
    break;}
case 82:
#line 606 "ifm-parse.y"
{
                    if (lastitem == NULL)
                        err("no item referred to by `last'");
                    else
                        yyval.vval = ititem = vs_pcreate(lastitem);
                ;
    break;}
case 83:
#line 619 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 84:
#line 627 "ifm-parse.y"
{
                    vl_ppush(links, curobj);
                    RESET_IT;
		;
    break;}
case 85:
#line 632 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(linktags, yyvsp[0].sval)) == NULL) {
                        err("link tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 86:
#line 640 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 89:
#line 650 "ifm-parse.y"
{
                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;
		;
    break;}
case 90:
#line 655 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 91:
#line 659 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 92:
#line 663 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 93:
#line 667 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 94:
#line 671 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 95:
#line 675 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 96:
#line 679 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 97:
#line 683 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 98:
#line 689 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 99:
#line 693 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 100:
#line 698 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 101:
#line 703 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 102:
#line 708 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("link", yyvsp[0].sval, curobj, linktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 104:
#line 716 "ifm-parse.y"
{
                    obsolete("`special' attribute", "`style special'");
                    add_attr(curobj, "STYLE", "special");
                    ref_style("special");
		;
    break;}
case 105:
#line 728 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 106:
#line 736 "ifm-parse.y"
{
                    vl_ppush(joins, curobj);
                    RESET_IT;
		;
    break;}
case 107:
#line 741 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(jointags, yyvsp[0].sval)) == NULL) {
                        err("join tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 108:
#line 749 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 111:
#line 759 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 112:
#line 763 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 113:
#line 767 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 114:
#line 771 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 115:
#line 775 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 116:
#line 779 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 117:
#line 783 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 118:
#line 787 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 119:
#line 791 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 120:
#line 797 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 121:
#line 801 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 122:
#line 806 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 123:
#line 811 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 124:
#line 816 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("join", yyvsp[0].sval, curobj, jointags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 126:
#line 830 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 127:
#line 837 "ifm-parse.y"
{
                    if (vh_iget(curobj, "NOROOM"))
                        vh_pstore(curobj, "IN", NULL);
                    else if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lasttask = curobj;
                    vl_ppush(tasks, curobj);
                    RESET_IT;
		;
    break;}
case 128:
#line 848 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(tasktags, yyvsp[0].sval)) == NULL) {
                        err("task tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 129:
#line 856 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 132:
#line 866 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("task", yyvsp[0].sval, curobj, tasktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 133:
#line 873 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 134:
#line 877 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
		;
    break;}
case 135:
#line 881 "ifm-parse.y"
{
                    SET_LIST(curobj, "GIVE", curitems);
		;
    break;}
case 136:
#line 885 "ifm-parse.y"
{
                    SET_LIST(curobj, "GET", curitems);
		;
    break;}
case 137:
#line 889 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
		;
    break;}
case 138:
#line 895 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 139:
#line 902 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 140:
#line 909 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 141:
#line 917 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 142:
#line 921 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 143:
#line 926 "ifm-parse.y"
{
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
                ;
    break;}
case 144:
#line 930 "ifm-parse.y"
{
                    SET_LIST(curobj, "LOSE", curitems);
		;
    break;}
case 145:
#line 934 "ifm-parse.y"
{
                    vh_store(curobj, "GOTO", yyvsp[0].vval);
                ;
    break;}
case 146:
#line 938 "ifm-parse.y"
{
                    vh_store(curobj, "FOLLOW", yyvsp[0].vval);
                ;
    break;}
case 147:
#line 942 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 148:
#line 946 "ifm-parse.y"
{
                    vh_istore(curobj, "NOROOM", 1);
		;
    break;}
case 149:
#line 950 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 150:
#line 954 "ifm-parse.y"
{
                    vh_istore(curobj, "SAFE", 1);
                ;
    break;}
case 151:
#line 958 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 152:
#line 962 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 153:
#line 966 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", yyvsp[0].sval);
                ;
    break;}
case 154:
#line 971 "ifm-parse.y"
{
                    add_attr(curobj, "CMD", NULL);
                ;
    break;}
case 155:
#line 975 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 159:
#line 986 "ifm-parse.y"
{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, yyvsp[0].vval);
		;
    break;}
case 160:
#line 994 "ifm-parse.y"
{
                    yyval.vval = ittask = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 161:
#line 998 "ifm-parse.y"
{
                    if (ittask == NULL)
                        err("no task referred to by `it'");
                    else
                        yyval.vval = vs_copy(ittask);
                ;
    break;}
case 162:
#line 1005 "ifm-parse.y"
{
                    if (lasttask == NULL)
                        err("no task referred to by `last'");
                    else
                        yyval.vval = ittask = vs_pcreate(lasttask);
                ;
    break;}
case 163:
#line 1018 "ifm-parse.y"
{
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                ;
    break;}
case 165:
#line 1027 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                ;
    break;}
case 166:
#line 1031 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 167:
#line 1036 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                ;
    break;}
case 168:
#line 1040 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 169:
#line 1045 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, NULL);
                ;
    break;}
case 170:
#line 1049 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, NULL);
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 171:
#line 1056 "ifm-parse.y"
{
                    var_alias(yyvsp[-3].sval, yyvsp[-1].sval);
                ;
    break;}
case 172:
#line 1060 "ifm-parse.y"
{
                    var_alias(yyvsp[-3].sval, NULL);
                ;
    break;}
case 174:
#line 1067 "ifm-parse.y"
{
                    push_style(yyvsp[0].sval);
                    instyle++;
                ;
    break;}
case 175:
#line 1072 "ifm-parse.y"
{
                    push_style("puzzle");
                    instyle++;
                ;
    break;}
case 176:
#line 1077 "ifm-parse.y"
{
                    push_style("special");
                    instyle++;
                ;
    break;}
case 177:
#line 1088 "ifm-parse.y"
{
                    push_style(yyvsp[-1].sval);
                ;
    break;}
case 178:
#line 1092 "ifm-parse.y"
{
                    push_style("puzzle");
                ;
    break;}
case 179:
#line 1096 "ifm-parse.y"
{
                    push_style("special");
                ;
    break;}
case 180:
#line 1100 "ifm-parse.y"
{
                    pop_style(yyvsp[-1].sval);
                ;
    break;}
case 181:
#line 1104 "ifm-parse.y"
{
                    pop_style("puzzle");
                ;
    break;}
case 182:
#line 1108 "ifm-parse.y"
{
                    pop_style("special");
                ;
    break;}
case 183:
#line 1112 "ifm-parse.y"
{
                    pop_style(NULL);
                ;
    break;}
case 186:
#line 1122 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", yyvsp[0].sval);
                    ref_style(yyvsp[0].sval);
                ;
    break;}
case 187:
#line 1127 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", "puzzle");
                    ref_style("puzzle");
                ;
    break;}
case 188:
#line 1132 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", "special");
                    ref_style("special");
                ;
    break;}
case 191:
#line 1147 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, yyvsp[0].ival);
		;
    break;}
case 192:
#line 1153 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-1].ival);
                ;
    break;}
case 193:
#line 1162 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-2].ival);
                    obsolete("`times' keyword", "just the repeat count");
                ;
    break;}
case 194:
#line 1173 "ifm-parse.y"
{ yyval.ival = D_NORTH;	    ;
    break;}
case 195:
#line 1174 "ifm-parse.y"
{ yyval.ival = D_EAST;	    ;
    break;}
case 196:
#line 1175 "ifm-parse.y"
{ yyval.ival = D_SOUTH;	    ;
    break;}
case 197:
#line 1176 "ifm-parse.y"
{ yyval.ival = D_WEST;	    ;
    break;}
case 198:
#line 1177 "ifm-parse.y"
{ yyval.ival = D_NORTHEAST; ;
    break;}
case 199:
#line 1178 "ifm-parse.y"
{ yyval.ival = D_NORTHWEST; ;
    break;}
case 200:
#line 1179 "ifm-parse.y"
{ yyval.ival = D_SOUTHEAST; ;
    break;}
case 201:
#line 1180 "ifm-parse.y"
{ yyval.ival = D_SOUTHWEST; ;
    break;}
case 202:
#line 1183 "ifm-parse.y"
{ yyval.ival = D_IN;   ;
    break;}
case 203:
#line 1184 "ifm-parse.y"
{ yyval.ival = D_OUT;  ;
    break;}
case 204:
#line 1185 "ifm-parse.y"
{ yyval.ival = D_UP;   ;
    break;}
case 205:
#line 1186 "ifm-parse.y"
{ yyval.ival = D_DOWN; ;
    break;}
case 206:
#line 1193 "ifm-parse.y"
{ yyval.dval = yyvsp[0].ival; ;
    break;}
case 207:
#line 1194 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 208:
#line 1195 "ifm-parse.y"
{ yyval.dval = var_real(yyvsp[0].sval); ;
    break;}
case 209:
#line 1196 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 210:
#line 1197 "ifm-parse.y"
{ yyval.dval = -yyvsp[0].dval; ;
    break;}
case 211:
#line 1198 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval + yyvsp[0].dval; ;
    break;}
case 212:
#line 1199 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval - yyvsp[0].dval; ;
    break;}
case 213:
#line 1200 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval * yyvsp[0].dval; ;
    break;}
case 214:
#line 1201 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval / yyvsp[0].dval; ;
    break;}
case 215:
#line 1202 "ifm-parse.y"
{ yyval.dval = pow(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 216:
#line 1203 "ifm-parse.y"
{ yyval.dval = fmod(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 217:
#line 1204 "ifm-parse.y"
{ yyval.dval = yyvsp[-1].dval; ;
    break;}
case 218:
#line 1207 "ifm-parse.y"
{ yyval.ival = (int) yyvsp[0].dval; ;
    break;}
case 219:
#line 1210 "ifm-parse.y"
{ yyval.sval = yyvsp[0].sval; ;
    break;}
case 220:
#line 1211 "ifm-parse.y"
{ yyval.sval = var_string(yyvsp[0].sval); ;
    break;}
case 221:
#line 1215 "ifm-parse.y"
{
                    yyval.sval = yyvsp[0].sval;
                    repeat = 1;
                ;
    break;}
case 222:
#line 1220 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-1].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                ;
    break;}
case 223:
#line 1227 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-2].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    obsolete("`times' keyword", "just the repeat count");
                ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/lib/bison.simple"

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
#line 1236 "ifm-parse.y"

