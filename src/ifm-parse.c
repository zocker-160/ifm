
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
#define	NORTH	310
#define	EAST	311
#define	SOUTH	312
#define	WEST	313
#define	NORTHEAST	314
#define	NORTHWEST	315
#define	SOUTHEAST	316
#define	SOUTHWEST	317
#define	UP	318
#define	DOWN	319
#define	IN	320
#define	OUT	321
#define	INTEGER	322
#define	REAL	323
#define	STRING	324
#define	ID	325
#define	VAR	326
#define	PLUS	327
#define	MINUS	328

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



#define	YYFINAL		364
#define	YYFLAG		-32768
#define	YYNTBASE	85

#define YYTRANSLATE(x) ((unsigned)(x) <= 328 ? yytranslate[x] : 138)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    78,     2,     2,    83,
    84,    76,    74,     2,    75,     2,    77,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    82,     2,
    73,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    81,     2,     2,     2,     2,     2,     2,
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
    67,    68,    69,    70,    71,    72,    79,    80
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     7,     9,    11,    13,    15,    17,    19,
    21,    23,    27,    31,    32,    38,    39,    45,    46,    49,
    52,    57,    60,    63,    66,    69,    72,    74,    76,    78,
    80,    82,    85,    88,    91,    94,    97,   100,   103,   107,
   111,   114,   117,   119,   121,   123,   126,   128,   130,   132,
   134,   135,   141,   142,   148,   149,   152,   155,   158,   161,
   163,   165,   167,   169,   171,   175,   179,   182,   185,   188,
   191,   193,   196,   198,   201,   203,   205,   209,   211,   213,
   215,   217,   218,   226,   227,   233,   234,   237,   240,   243,
   245,   247,   249,   252,   255,   258,   261,   264,   267,   271,
   275,   278,   281,   283,   284,   292,   293,   299,   300,   303,
   306,   309,   311,   313,   315,   318,   321,   324,   327,   330,
   333,   337,   341,   344,   347,   348,   354,   355,   361,   362,
   365,   368,   371,   374,   377,   380,   383,   388,   393,   400,
   404,   410,   414,   417,   420,   423,   426,   429,   431,   433,
   436,   438,   441,   444,   447,   450,   452,   455,   457,   459,
   461,   463,   465,   467,   473,   480,   486,   493,   499,   506,
   511,   516,   517,   521,   525,   529,   533,   537,   541,   545,
   549,   553,   556,   558,   561,   563,   565,   567,   569,   572,
   574,   577,   581,   583,   585,   587,   589,   591,   593,   595,
   597,   599,   601,   603,   605,   607,   609,   611,   614,   617,
   621,   625,   629,   633,   637,   641,   645,   647,   649,   651,
   653,   656
};

static const short yyrhs[] = {    -1,
    85,    86,     0,    85,     1,     0,    87,     0,    88,     0,
    96,     0,   105,     0,   110,     0,   115,     0,   123,     0,
   127,     0,    32,   136,    82,     0,    26,   136,    82,     0,
     0,     3,   136,    89,    91,    82,     0,     0,     3,    71,
    90,    91,    82,     0,     0,    91,    92,     0,     7,    71,
     0,     9,   130,     6,    71,     0,     9,   130,     0,    27,
   130,     0,     5,    93,     0,    19,    93,     0,    20,   133,
     0,    10,     0,    48,     0,    49,     0,    24,     0,    40,
     0,    16,   101,     0,    35,   120,     0,    15,   120,     0,
    38,   102,     0,    31,   135,     0,    18,   135,     0,    37,
   137,     0,    37,     8,   137,     0,    37,     6,   137,     0,
    13,   136,     0,    52,   128,     0,    21,     0,    12,     0,
    94,     0,    93,    94,     0,    95,     0,    71,     0,    45,
     0,    23,     0,     0,     4,   136,    97,    99,    82,     0,
     0,     4,    71,    98,    99,    82,     0,     0,    99,   100,
     0,     7,    71,     0,    66,    95,     0,    13,   136,     0,
    11,     0,    28,     0,    29,     0,    55,     0,    30,     0,
    30,    54,   101,     0,    30,    46,   120,     0,    16,   101,
     0,    35,   120,     0,    15,   120,     0,    18,   135,     0,
    40,     0,    52,   128,     0,   103,     0,   101,   103,     0,
   101,     0,    43,     0,    43,    44,   101,     0,   104,     0,
    71,     0,    45,     0,    23,     0,     0,     5,    95,     8,
    95,   106,   108,    82,     0,     0,     5,    71,   107,   108,
    82,     0,     0,   108,   109,     0,     9,   130,     0,    20,
   133,     0,    10,     0,    11,     0,    49,     0,    16,   101,
     0,    35,   120,     0,    15,   120,     0,    38,   102,     0,
    31,   135,     0,    37,   137,     0,    37,     8,   137,     0,
    37,     6,   137,     0,     7,    71,     0,    52,   128,     0,
    21,     0,     0,    19,    95,     8,    95,   111,   113,    82,
     0,     0,    19,    71,   112,   113,    82,     0,     0,   113,
   114,     0,    20,   132,     0,    20,   133,     0,    10,     0,
    11,     0,    49,     0,    16,   101,     0,    35,   120,     0,
    15,   120,     0,    38,   102,     0,    31,   135,     0,    37,
   137,     0,    37,     8,   137,     0,    37,     6,   137,     0,
     7,    71,     0,    52,   128,     0,     0,    14,   136,   116,
   118,    82,     0,     0,    14,    71,   117,   118,    82,     0,
     0,   118,   119,     0,     7,    71,     0,    15,   120,     0,
    16,   101,     0,    41,   101,     0,    17,   101,     0,    42,
   102,     0,    42,   102,    46,   120,     0,    42,   102,    66,
    95,     0,    42,   102,    66,    95,    46,   120,     0,    42,
    66,    95,     0,    42,    66,    95,    46,   120,     0,    42,
    46,   120,     0,    33,   101,     0,    25,    95,     0,    36,
   122,     0,    66,    95,     0,    66,    22,     0,    55,     0,
    34,     0,    18,   135,     0,    40,     0,    37,   137,     0,
    37,    50,     0,    13,   136,     0,    52,   128,     0,   121,
     0,   120,   121,     0,   122,     0,    71,     0,    45,     0,
    23,     0,   124,     0,   125,     0,    71,    73,   134,   126,
    82,     0,    71,    71,    73,   134,   126,    82,     0,    71,
    73,    70,   126,    82,     0,    71,    71,    73,    70,   126,
    82,     0,    71,    73,    39,   126,    82,     0,    71,    71,
    73,    39,   126,    82,     0,    71,    51,    71,    82,     0,
    71,    51,    39,    82,     0,     0,    66,    52,    71,     0,
    66,    52,    12,     0,    66,    52,    21,     0,    52,    71,
    82,     0,    52,    12,    82,     0,    52,    21,    82,     0,
    53,    71,    82,     0,    53,    12,    82,     0,    53,    21,
    82,     0,    53,    82,     0,   129,     0,   128,   129,     0,
    71,     0,    12,     0,    21,     0,   131,     0,   130,   131,
     0,   132,     0,   132,   135,     0,   132,    47,   135,     0,
    56,     0,    57,     0,    58,     0,    59,     0,    60,     0,
    61,     0,    62,     0,    63,     0,    66,     0,    67,     0,
    64,     0,    65,     0,    68,     0,    69,     0,    72,     0,
    74,   134,     0,    75,   134,     0,   134,    74,   134,     0,
   134,    75,   134,     0,   134,    76,   134,     0,   134,    77,
   134,     0,   134,    81,   134,     0,   134,    78,   134,     0,
    83,   134,    84,     0,   134,     0,    70,     0,    72,     0,
   136,     0,   136,   135,     0,   136,    47,   135,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   107,   108,   109,   112,   113,   114,   115,   116,   117,   118,
   119,   126,   130,   142,   152,   245,   253,   259,   260,   263,
   270,   289,   304,   317,   332,   347,   351,   355,   359,   363,
   367,   371,   375,   379,   383,   389,   393,   397,   402,   407,
   412,   416,   417,   423,   431,   432,   435,   443,   447,   454,
   467,   475,   484,   492,   498,   499,   502,   509,   513,   517,
   521,   526,   530,   534,   538,   542,   546,   550,   554,   558,
   562,   566,   569,   570,   573,   574,   575,   578,   586,   590,
   597,   610,   618,   623,   631,   637,   638,   641,   646,   650,
   654,   658,   662,   666,   670,   674,   680,   684,   689,   694,
   699,   706,   707,   719,   727,   732,   740,   746,   747,   750,
   754,   758,   762,   766,   770,   774,   778,   782,   788,   792,
   797,   802,   807,   814,   821,   828,   839,   847,   853,   854,
   857,   864,   868,   872,   876,   880,   886,   893,   900,   908,
   912,   917,   921,   925,   929,   933,   937,   941,   945,   949,
   953,   957,   962,   966,   970,   973,   974,   977,   985,   989,
   996,  1009,  1015,  1018,  1022,  1026,  1030,  1034,  1038,  1044,
  1048,  1054,  1055,  1060,  1065,  1076,  1080,  1084,  1088,  1092,
  1096,  1100,  1106,  1107,  1110,  1115,  1120,  1131,  1132,  1135,
  1141,  1150,  1162,  1163,  1164,  1165,  1166,  1167,  1168,  1169,
  1172,  1173,  1174,  1175,  1182,  1183,  1184,  1185,  1186,  1187,
  1188,  1189,  1190,  1191,  1192,  1193,  1196,  1199,  1200,  1203,
  1208,  1215
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ROOM","ITEM",
"LINK","FROM","TAG","TO","DIR","ONEWAY","HIDDEN","PUZZLE","NOTE","TASK","AFTER",
"NEED","GET","SCORE","JOIN","GO","SPECIAL","ANY","LAST","START","GOTO","MAP",
"EXIT","GIVEN","LOST","KEEP","LENGTH","TITLE","LOSE","SAFE","BEFORE","FOLLOW",
"CMD","LEAVE","UNDEF","FINISH","GIVE","DROP","ALL","EXCEPT","IT","UNTIL","TIMES",
"NOLINK","NOPATH","NONE","ALIAS","STYLE","ENDSTYLE","WITH","IGNORE","NORTH",
"EAST","SOUTH","WEST","NORTHEAST","NORTHWEST","SOUTHEAST","SOUTHWEST","UP","DOWN",
"IN","OUT","INTEGER","REAL","STRING","ID","VAR","'='","'+'","'-'","'*'","'/'",
"'%'","PLUS","MINUS","'^'","';'","'('","')'","stmt_list","stmt","ctrl_stmt",
"room_stmt","@1","@2","room_attrs","room_attr","room_list","room_elt","room",
"item_stmt","@3","@4","item_attrs","item_attr","item_list","item_list_all","item_elt",
"item","link_stmt","@5","@6","link_attrs","link_attr","join_stmt","@7","@8",
"join_attrs","join_attr","task_stmt","@9","@10","task_attrs","task_attr","task_list",
"task_elt","task","vars_stmt","set_var","alias_var","in_style","style_stmt",
"style_list","style_elt","dir_list","dir_elt","compass","otherdir","exp","integer",
"string","string_repeat", NULL
};
#endif

static const short yyr1[] = {     0,
    85,    85,    85,    86,    86,    86,    86,    86,    86,    86,
    86,    87,    87,    89,    88,    90,    88,    91,    91,    92,
    92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
    92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
    92,    92,    92,    92,    93,    93,    94,    95,    95,    95,
    97,    96,    98,    96,    99,    99,   100,   100,   100,   100,
   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
   100,   100,   101,   101,   102,   102,   102,   103,   104,   104,
   104,   106,   105,   107,   105,   108,   108,   109,   109,   109,
   109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
   109,   109,   109,   111,   110,   112,   110,   113,   113,   114,
   114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
   114,   114,   114,   114,   116,   115,   117,   115,   118,   118,
   119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
   119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
   119,   119,   119,   119,   119,   120,   120,   121,   122,   122,
   122,   123,   123,   124,   124,   124,   124,   124,   124,   125,
   125,   126,   126,   126,   126,   127,   127,   127,   127,   127,
   127,   127,   128,   128,   129,   129,   129,   130,   130,   131,
   131,   131,   132,   132,   132,   132,   132,   132,   132,   132,
   133,   133,   133,   133,   134,   134,   134,   134,   134,   134,
   134,   134,   134,   134,   134,   134,   135,   136,   136,   137,
   137,   137
};

static const short yyr2[] = {     0,
     0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
     1,     3,     3,     0,     5,     0,     5,     0,     2,     2,
     4,     2,     2,     2,     2,     2,     1,     1,     1,     1,
     1,     2,     2,     2,     2,     2,     2,     2,     3,     3,
     2,     2,     1,     1,     1,     2,     1,     1,     1,     1,
     0,     5,     0,     5,     0,     2,     2,     2,     2,     1,
     1,     1,     1,     1,     3,     3,     2,     2,     2,     2,
     1,     2,     1,     2,     1,     1,     3,     1,     1,     1,
     1,     0,     7,     0,     5,     0,     2,     2,     2,     1,
     1,     1,     2,     2,     2,     2,     2,     2,     3,     3,
     2,     2,     1,     0,     7,     0,     5,     0,     2,     2,
     2,     1,     1,     1,     2,     2,     2,     2,     2,     2,
     3,     3,     2,     2,     0,     5,     0,     5,     0,     2,
     2,     2,     2,     2,     2,     2,     4,     4,     6,     3,
     5,     3,     2,     2,     2,     2,     2,     1,     1,     2,
     1,     2,     2,     2,     2,     1,     2,     1,     1,     1,
     1,     1,     1,     5,     6,     5,     6,     5,     6,     4,
     4,     0,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     2,     1,     2,     1,     1,     1,     1,     2,     1,
     2,     3,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     2,     2,     3,
     3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
     2,     3
};

static const short yydefact[] = {     1,
     0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     2,     4,     5,     6,     7,     8,     9,    10,
   162,   163,    11,   218,    16,   219,    14,    53,    51,    50,
    49,    84,     0,   127,   125,   106,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   182,     0,     0,     0,    18,
    18,    55,    55,    86,     0,   129,   129,   108,     0,    13,
    12,   177,   178,   176,   180,   181,   179,     0,     0,     0,
   172,   205,   206,   172,   207,     0,     0,     0,   172,     0,
     0,     0,     0,     0,    48,    82,     0,     0,     0,   104,
   171,   170,   172,   172,   172,     0,     0,     0,   208,   209,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    27,    44,     0,     0,     0,     0,     0,     0,    43,
    30,     0,     0,     0,     0,     0,    31,    28,    29,     0,
    17,    19,    15,     0,    60,     0,     0,     0,     0,    61,
    62,    64,     0,    71,     0,    63,     0,    54,    56,    52,
     0,     0,    90,    91,     0,     0,     0,   103,     0,     0,
     0,     0,    92,     0,    85,    87,    86,     0,     0,     0,
     0,     0,     0,     0,     0,   149,     0,     0,   151,     0,
     0,     0,   148,     0,   128,   130,   126,     0,   112,   113,
     0,     0,     0,     0,     0,     0,     0,   114,     0,   107,
   109,   108,     0,     0,     0,     0,   168,   166,   216,   210,
   211,   212,   213,   215,   214,   164,    24,    45,    47,    20,
   193,   194,   195,   196,   197,   198,   199,   200,    22,   188,
   190,    41,   161,   160,   159,    34,   156,   158,    81,    80,
    79,    32,    73,    78,   217,    37,    25,   203,   204,   201,
   202,    26,    23,    36,    33,     0,     0,   220,    38,    76,
    75,    35,   186,   187,   185,    42,   183,    57,    59,    69,
    67,    70,     0,     0,    68,    72,    58,   101,    88,    95,
    93,    89,    97,    94,     0,     0,    98,    96,   102,     0,
   131,   154,   132,   133,   135,   150,   144,   143,   145,   153,
   152,   134,     0,     0,   136,   155,   147,   146,   123,   117,
   115,   110,   111,   119,   116,     0,     0,   120,   118,   124,
     0,   169,   167,   165,   174,   175,   173,    46,     0,   189,
     0,   191,   157,    74,    40,    39,     0,   221,     0,   184,
    66,    65,   100,    99,    83,   142,   140,     0,     0,   122,
   121,   105,    21,   192,   222,    77,     0,   137,   138,   141,
     0,   139,     0,     0
};

static const short yydefgoto[] = {     1,
    13,    14,    15,    51,    50,    80,   132,   217,   218,   219,
    16,    53,    52,    82,   149,   261,   262,   243,   244,    17,
   167,    54,    84,   166,    18,   202,    58,    89,   201,    19,
    57,    56,    87,   186,   236,   237,   238,    20,    21,    22,
    97,    23,   266,   267,   229,   230,   231,   252,   245,   246,
   258,   259
};

static const short yypact[] = {-32768,
   438,-32768,    82,   188,    50,   293,   123,   -55,   -55,     7,
    19,   151,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    10,    16,-32768,-32768,    10,    21,   -48,   -31,   -21,
   -13,    -7,    12,    30,    38,-32768,   -35,    45,   487,-32768,
-32768,-32768,-32768,-32768,   152,-32768,-32768,-32768,   152,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    47,    51,   499,
    75,-32768,-32768,    75,-32768,   526,   526,   526,   210,   180,
   230,   332,   378,   416,-32768,-32768,   256,   300,    73,-32768,
-32768,-32768,    75,    75,   210,    91,    63,    66,    78,    78,
   548,   526,   526,   526,   526,   526,   526,    85,   152,    93,
   577,-32768,-32768,   -55,   160,   165,   526,   152,   292,-32768,
-32768,   577,   526,   160,    27,   113,-32768,-32768,-32768,    32,
-32768,-32768,-32768,    99,-32768,   -55,   160,   165,   526,-32768,
-32768,   -24,   160,-32768,    32,-32768,   152,-32768,-32768,-32768,
   100,   577,-32768,-32768,   160,   165,   292,-32768,   526,   160,
    58,   113,-32768,    32,-32768,-32768,-32768,   102,   -55,   160,
   165,   165,   526,   152,   165,-32768,   160,   183,-32768,   165,
   260,    32,-32768,   115,-32768,-32768,-32768,   110,-32768,-32768,
   160,   165,   554,   526,   160,    79,   113,-32768,    32,-32768,
-32768,-32768,   109,   121,   124,    36,-32768,-32768,-32768,   243,
   243,    78,    78,    78,    78,-32768,   152,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   317,-32768,
   468,-32768,-32768,-32768,-32768,   160,-32768,-32768,-32768,-32768,
-32768,   165,-32768,-32768,   567,-32768,   152,-32768,-32768,-32768,
-32768,-32768,   577,-32768,   160,   -55,   -55,   516,-32768,   138,
   165,-32768,-32768,-32768,-32768,    32,-32768,-32768,-32768,   160,
   165,-32768,   160,   165,   160,    32,-32768,-32768,   577,   160,
   165,-32768,-32768,   160,   -55,   -55,-32768,-32768,    32,   462,
-32768,-32768,   160,   165,   165,-32768,-32768,   165,-32768,-32768,
-32768,   165,   160,   152,    81,    32,-32768,-32768,-32768,   160,
   165,-32768,-32768,-32768,   160,   -55,   -55,-32768,-32768,    32,
   497,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   137,-32768,
   526,-32768,-32768,-32768,-32768,-32768,   526,-32768,   165,-32768,
   160,   165,-32768,-32768,-32768,   160,   163,   160,   152,-32768,
-32768,-32768,-32768,-32768,-32768,   165,   160,   160,   166,   160,
   160,   160,   214,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,   170,-32768,    98,  -209,    -5,
-32768,-32768,-32768,   174,-32768,  -113,  -116,  -179,-32768,-32768,
-32768,-32768,    74,-32768,-32768,-32768,-32768,    28,-32768,-32768,
-32768,-32768,   187,-32768,  -123,  -184,    70,-32768,-32768,-32768,
   235,-32768,  -122,  -250,    -8,  -155,    59,  -144,   418,  -118,
     3,  -151
};


#define	YYLAST		648


static const short yytable[] = {    33,
   255,    37,   242,    68,   254,    27,    29,   328,    35,   287,
    38,    39,   282,   270,    24,   340,    26,   -48,    40,   275,
   272,   273,   276,    55,   271,   340,   301,    41,    59,   274,
    43,   280,   256,    60,   257,    69,   284,   328,   340,    44,
   283,   289,   281,   263,   318,   288,   293,   325,   313,    86,
    61,   333,   264,    90,   296,   340,   326,   294,   295,   306,
    62,   298,   334,   285,   305,   286,   302,   310,    63,   340,
   333,   315,    30,   330,    64,   314,   320,    42,   311,   188,
   319,   334,   189,   190,   316,   333,   317,   191,   192,    45,
   333,   334,   193,    65,    31,   333,    24,   330,    26,   333,
    46,   334,   265,   194,   335,   336,   327,   195,   333,   196,
   197,    66,   332,   253,   334,   334,   232,    70,   334,    67,
    32,   198,   334,   330,   199,   333,   348,    24,    91,    26,
   333,   334,    92,   343,   344,   239,   307,    30,   269,   338,
    96,   277,   206,   279,   207,    30,   349,   208,    24,   341,
    26,    24,    25,    26,   200,   260,   333,   240,   107,    31,
   342,   333,   334,   220,   350,   351,   216,    31,   297,   268,
   278,   292,   291,   333,    30,   333,   334,   333,   308,   346,
   309,   339,   233,   241,   109,    85,   110,   239,   111,   112,
   322,   113,   114,    36,   115,   116,    31,   117,   118,   119,
   120,    47,   323,   121,   234,   324,   122,   353,   357,   240,
   123,   361,   354,   364,   124,   247,   125,   126,   355,   127,
    81,    48,    85,    49,   358,   356,    83,   128,   129,   321,
   235,   130,   300,   360,   109,   241,   110,   362,   111,   112,
   290,   113,   114,    88,   115,   116,   299,   117,   118,   119,
   120,   312,    24,   121,    26,     0,   122,    24,    28,    26,
   123,   131,   168,     0,   124,     0,   125,   126,   169,   127,
   170,   171,   172,   173,     0,    96,     0,   128,   129,     0,
   174,   130,   239,   102,   103,   104,   105,   106,   175,   176,
   107,   177,   178,     0,     0,   179,   180,   181,   347,     0,
     0,     0,   260,     0,   240,   303,   168,   182,    98,     0,
   183,   133,   169,   108,   170,   171,   172,   173,   104,   105,
   106,   184,   329,   107,   174,   304,     0,   203,   204,   205,
   241,     0,   175,   176,     0,   177,   178,   185,   134,   179,
   180,   181,   135,   359,   136,     0,   137,   138,     0,   139,
     0,   182,     0,     0,   183,   248,   249,   250,   251,   140,
   141,   142,    24,    34,    26,   184,   143,     0,     0,     0,
     0,   144,   221,   222,   223,   224,   225,   226,   227,   228,
     0,   187,     0,   145,   134,     0,   146,     0,   135,     0,
   136,     0,   137,   138,     0,   139,     0,   147,     0,     0,
     0,     0,     0,     0,     0,   140,   141,   142,     0,     0,
     0,     0,   143,   148,     0,     0,     0,   144,     0,     0,
     0,     0,   151,     0,   152,   153,   154,     0,     0,   145,
   155,   156,   146,     0,     0,   157,   158,   363,     2,     0,
     3,     4,     5,   147,     0,     0,   159,     0,     0,     0,
   160,     6,   161,   162,     0,     0,     7,     0,     0,   150,
     0,     0,     0,     8,   163,     0,    79,   164,   151,     9,
   152,   153,   154,     0,     0,     0,   155,   156,     0,     0,
     0,   157,   158,     0,     0,     0,     0,    95,     0,    10,
    11,     0,   159,    99,   100,   101,   160,   165,   161,   162,
     0,     0,     0,   188,     0,     0,   189,   190,    12,     0,
   163,   191,   192,   164,   331,     0,   193,     0,     0,   210,
   211,   212,   213,   214,   215,    71,     0,   194,     0,     0,
     0,   195,     0,   196,   197,    72,    73,    93,     0,    75,
     0,    76,    77,   345,     0,   198,     0,     0,   199,     0,
    78,     0,     0,     0,    72,    73,    74,     0,    75,     0,
    76,    77,   337,     0,     0,     0,    72,    73,    94,    78,
    75,     0,    76,    77,     0,     0,     0,     0,   352,     0,
     0,    78,     0,    72,    73,     0,     0,    75,     0,    76,
    77,     0,     0,    72,    73,     0,     0,    75,    78,    76,
    77,     0,     0,     0,     0,     0,     0,     0,    78,   221,
   222,   223,   224,   225,   226,   227,   228,   248,   249,   250,
   251,   102,   103,   104,   105,   106,     0,     0,   107,     0,
     0,   209,   221,   222,   223,   224,   225,   226,   227,   228,
   102,   103,   104,   105,   106,     0,     0,   107
};

static const short yycheck[] = {     5,
   124,     7,   116,    39,   123,     3,     4,   217,     6,   161,
     8,     9,   157,   137,    70,   266,    72,     8,    12,   143,
   139,    46,   145,     8,   138,   276,   178,    21,     8,    54,
    12,   155,     6,    82,     8,    71,   160,   247,   289,    21,
   159,   164,   156,    12,   196,   162,   170,    12,   193,    55,
    82,   236,    21,    59,   173,   306,    21,   171,   172,   182,
    82,   175,   242,     6,   181,     8,   180,   191,    82,   320,
   255,   195,    23,   229,    82,   194,   199,    71,   192,     7,
   197,   261,    10,    11,     6,   270,     8,    15,    16,    71,
   275,   271,    20,    82,    45,   280,    70,   253,    72,   284,
    82,   281,    71,    31,   256,   257,    71,    35,   293,    37,
    38,    82,   231,   122,   294,   295,   114,    73,   298,    82,
    71,    49,   302,   279,    52,   310,    46,    70,    82,    72,
   315,   311,    82,   285,   286,    23,    22,    23,   136,   258,
    66,   147,    52,   152,    82,    23,    66,    82,    70,   273,
    72,    70,    71,    72,    82,    43,   341,    45,    81,    45,
   274,   346,   342,    71,   316,   317,    82,    45,   174,    71,
    71,   169,    71,   358,    23,   360,   356,   362,   184,   303,
    71,    44,    23,    71,     5,    71,     7,    23,     9,    10,
    82,    12,    13,    71,    15,    16,    45,    18,    19,    20,
    21,    51,    82,    24,    45,    82,    27,    71,    46,    45,
    31,    46,   331,     0,    35,   118,    37,    38,   337,    40,
    51,    71,    71,    73,   348,   339,    53,    48,    49,   202,
    71,    52,    50,   357,     5,    71,     7,   361,     9,    10,
   167,    12,    13,    57,    15,    16,   177,    18,    19,    20,
    21,   193,    70,    24,    72,    -1,    27,    70,    71,    72,
    31,    82,     7,    -1,    35,    -1,    37,    38,    13,    40,
    15,    16,    17,    18,    -1,    66,    -1,    48,    49,    -1,
    25,    52,    23,    74,    75,    76,    77,    78,    33,    34,
    81,    36,    37,    -1,    -1,    40,    41,    42,   304,    -1,
    -1,    -1,    43,    -1,    45,    46,     7,    52,    74,    -1,
    55,    82,    13,    79,    15,    16,    17,    18,    76,    77,
    78,    66,     6,    81,    25,    66,    -1,    93,    94,    95,
    71,    -1,    33,    34,    -1,    36,    37,    82,     7,    40,
    41,    42,    11,   349,    13,    -1,    15,    16,    -1,    18,
    -1,    52,    -1,    -1,    55,    64,    65,    66,    67,    28,
    29,    30,    70,    71,    72,    66,    35,    -1,    -1,    -1,
    -1,    40,    56,    57,    58,    59,    60,    61,    62,    63,
    -1,    82,    -1,    52,     7,    -1,    55,    -1,    11,    -1,
    13,    -1,    15,    16,    -1,    18,    -1,    66,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    28,    29,    30,    -1,    -1,
    -1,    -1,    35,    82,    -1,    -1,    -1,    40,    -1,    -1,
    -1,    -1,     7,    -1,     9,    10,    11,    -1,    -1,    52,
    15,    16,    55,    -1,    -1,    20,    21,     0,     1,    -1,
     3,     4,     5,    66,    -1,    -1,    31,    -1,    -1,    -1,
    35,    14,    37,    38,    -1,    -1,    19,    -1,    -1,    82,
    -1,    -1,    -1,    26,    49,    -1,    49,    52,     7,    32,
     9,    10,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,
    -1,    20,    21,    -1,    -1,    -1,    -1,    70,    -1,    52,
    53,    -1,    31,    76,    77,    78,    35,    82,    37,    38,
    -1,    -1,    -1,     7,    -1,    -1,    10,    11,    71,    -1,
    49,    15,    16,    52,    47,    -1,    20,    -1,    -1,   102,
   103,   104,   105,   106,   107,    39,    -1,    31,    -1,    -1,
    -1,    35,    -1,    37,    38,    68,    69,    39,    -1,    72,
    -1,    74,    75,    82,    -1,    49,    -1,    -1,    52,    -1,
    83,    -1,    -1,    -1,    68,    69,    70,    -1,    72,    -1,
    74,    75,    47,    -1,    -1,    -1,    68,    69,    70,    83,
    72,    -1,    74,    75,    -1,    -1,    -1,    -1,    82,    -1,
    -1,    83,    -1,    68,    69,    -1,    -1,    72,    -1,    74,
    75,    -1,    -1,    68,    69,    -1,    -1,    72,    83,    74,
    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    74,    75,    76,    77,    78,    -1,    -1,    81,    -1,
    -1,    84,    56,    57,    58,    59,    60,    61,    62,    63,
    74,    75,    76,    77,    78,    -1,    -1,    81
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
#line 143 "ifm-parse.y"
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
case 15:
#line 153 "ifm-parse.y"
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
case 16:
#line 246 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(roomtags, yyvsp[0].sval)) == NULL) {
                        err("room tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 17:
#line 254 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 20:
#line 264 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("room", yyvsp[0].sval, curobj, roomtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 21:
#line 271 "ifm-parse.y"
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
case 22:
#line 290 "ifm-parse.y"
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
case 23:
#line 305 "ifm-parse.y"
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
case 24:
#line 318 "ifm-parse.y"
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
case 25:
#line 333 "ifm-parse.y"
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
case 26:
#line 348 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 27:
#line 352 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 28:
#line 356 "ifm-parse.y"
{
                    vh_istore(curobj, "NOLINK", 1);
		;
    break;}
case 29:
#line 360 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 30:
#line 364 "ifm-parse.y"
{
                    startroom = curobj;
		;
    break;}
case 31:
#line 368 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 32:
#line 372 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(NEED), curitems);
                ;
    break;}
case 33:
#line 376 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		;
    break;}
case 34:
#line 380 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		;
    break;}
case 35:
#line 384 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                ;
    break;}
case 36:
#line 390 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 37:
#line 394 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 38:
#line 398 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 39:
#line 403 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 40:
#line 408 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 41:
#line 413 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 43:
#line 418 "ifm-parse.y"
{
                    obsolete("`special' attribute", "`style special'");
                    add_attr(curobj, ATTR(STYLE), "special");
                    ref_style("special");
		;
    break;}
case 44:
#line 424 "ifm-parse.y"
{
                    obsolete("`puzzle' attribute", "`style puzzle'");
                    add_attr(curobj, ATTR(STYLE), "puzzle");
                    ref_style("puzzle");
		;
    break;}
case 47:
#line 436 "ifm-parse.y"
{
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, yyvsp[0].vval);
		;
    break;}
case 48:
#line 444 "ifm-parse.y"
{
                    yyval.vval = itroom = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 49:
#line 448 "ifm-parse.y"
{
                    if (itroom == NULL)
                        err("no room referred to by `it'");
                    else
                        yyval.vval = vs_copy(itroom);
                ;
    break;}
case 50:
#line 455 "ifm-parse.y"
{
                    if (lastroom == NULL)
                        err("no room referred to by `last'");
                    else
                        yyval.vval = itroom = vs_pcreate(lastroom);
                ;
    break;}
case 51:
#line 468 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_istore(curobj, "ID", ++itemid);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 52:
#line 476 "ifm-parse.y"
{
                    if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lastitem = curobj;
                    vl_ppush(items, curobj);
                    RESET_IT;
		;
    break;}
case 53:
#line 485 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(itemtags, yyvsp[0].sval)) == NULL) {
                        err("item tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 54:
#line 493 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 57:
#line 503 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("item", yyvsp[0].sval, curobj, itemtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 58:
#line 510 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 59:
#line 514 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 60:
#line 518 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 61:
#line 522 "ifm-parse.y"
{
                    obsolete("`given' attribute", "task `give' attribute");
                    vh_istore(curobj, "GIVEN", 1);
		;
    break;}
case 62:
#line 527 "ifm-parse.y"
{
                    vh_istore(curobj, "LOST", 1);
		;
    break;}
case 63:
#line 531 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 64:
#line 535 "ifm-parse.y"
{
                    vh_istore(curobj, "KEEP", 1);
		;
    break;}
case 65:
#line 539 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_WITH", curitems);
		;
    break;}
case 66:
#line 543 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_UNTIL", curtasks);
		;
    break;}
case 67:
#line 547 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 68:
#line 551 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
                ;
    break;}
case 69:
#line 555 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
                ;
    break;}
case 70:
#line 559 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 71:
#line 563 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 75:
#line 573 "ifm-parse.y"
{ allflag = 0; ;
    break;}
case 76:
#line 574 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 77:
#line 575 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 78:
#line 579 "ifm-parse.y"
{
                    if (curitems == NULL)
                        curitems = vl_create();
                    vl_push(curitems, yyvsp[0].vval);
		;
    break;}
case 79:
#line 587 "ifm-parse.y"
{
                    yyval.vval = ititem = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 80:
#line 591 "ifm-parse.y"
{
                    if (ititem == NULL)
                        err("no item referred to by `it'");
                    else
                        yyval.vval = vs_copy(ititem);
                ;
    break;}
case 81:
#line 598 "ifm-parse.y"
{
                    if (lastitem == NULL)
                        err("no item referred to by `last'");
                    else
                        yyval.vval = ititem = vs_pcreate(lastitem);
                ;
    break;}
case 82:
#line 611 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 83:
#line 619 "ifm-parse.y"
{
                    vl_ppush(links, curobj);
                    RESET_IT;
		;
    break;}
case 84:
#line 624 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(linktags, yyvsp[0].sval)) == NULL) {
                        err("link tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 85:
#line 632 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 88:
#line 642 "ifm-parse.y"
{
                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;
		;
    break;}
case 89:
#line 647 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 90:
#line 651 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 91:
#line 655 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 92:
#line 659 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 93:
#line 663 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 94:
#line 667 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 95:
#line 671 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 96:
#line 675 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 97:
#line 681 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 98:
#line 685 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 99:
#line 690 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 100:
#line 695 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 101:
#line 700 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("link", yyvsp[0].sval, curobj, linktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 103:
#line 708 "ifm-parse.y"
{
                    obsolete("`special' attribute", "`style special'");
                    add_attr(curobj, "STYLE", "special");
                    ref_style("special");
		;
    break;}
case 104:
#line 720 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 105:
#line 728 "ifm-parse.y"
{
                    vl_ppush(joins, curobj);
                    RESET_IT;
		;
    break;}
case 106:
#line 733 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(jointags, yyvsp[0].sval)) == NULL) {
                        err("join tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 107:
#line 741 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 110:
#line 751 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 111:
#line 755 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 112:
#line 759 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 113:
#line 763 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 114:
#line 767 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 115:
#line 771 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 116:
#line 775 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 117:
#line 779 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 118:
#line 783 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 119:
#line 789 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 120:
#line 793 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 121:
#line 798 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 122:
#line 803 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 123:
#line 808 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("join", yyvsp[0].sval, curobj, jointags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 125:
#line 822 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 126:
#line 829 "ifm-parse.y"
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
case 127:
#line 840 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(tasktags, yyvsp[0].sval)) == NULL) {
                        err("task tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 128:
#line 848 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 131:
#line 858 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("task", yyvsp[0].sval, curobj, tasktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 132:
#line 865 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 133:
#line 869 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
		;
    break;}
case 134:
#line 873 "ifm-parse.y"
{
                    SET_LIST(curobj, "GIVE", curitems);
		;
    break;}
case 135:
#line 877 "ifm-parse.y"
{
                    SET_LIST(curobj, "GET", curitems);
		;
    break;}
case 136:
#line 881 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
		;
    break;}
case 137:
#line 887 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 138:
#line 894 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 139:
#line 901 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 140:
#line 909 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 141:
#line 913 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 142:
#line 918 "ifm-parse.y"
{
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
                ;
    break;}
case 143:
#line 922 "ifm-parse.y"
{
                    SET_LIST(curobj, "LOSE", curitems);
		;
    break;}
case 144:
#line 926 "ifm-parse.y"
{
                    vh_store(curobj, "GOTO", yyvsp[0].vval);
                ;
    break;}
case 145:
#line 930 "ifm-parse.y"
{
                    vh_store(curobj, "FOLLOW", yyvsp[0].vval);
                ;
    break;}
case 146:
#line 934 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 147:
#line 938 "ifm-parse.y"
{
                    vh_istore(curobj, "NOROOM", 1);
		;
    break;}
case 148:
#line 942 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 149:
#line 946 "ifm-parse.y"
{
                    vh_istore(curobj, "SAFE", 1);
                ;
    break;}
case 150:
#line 950 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 151:
#line 954 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 152:
#line 958 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", yyvsp[0].sval);
                ;
    break;}
case 153:
#line 963 "ifm-parse.y"
{
                    add_attr(curobj, "CMD", NULL);
                ;
    break;}
case 154:
#line 967 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 158:
#line 978 "ifm-parse.y"
{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, yyvsp[0].vval);
		;
    break;}
case 159:
#line 986 "ifm-parse.y"
{
                    yyval.vval = ittask = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 160:
#line 990 "ifm-parse.y"
{
                    if (ittask == NULL)
                        err("no task referred to by `it'");
                    else
                        yyval.vval = vs_copy(ittask);
                ;
    break;}
case 161:
#line 997 "ifm-parse.y"
{
                    if (lasttask == NULL)
                        err("no task referred to by `last'");
                    else
                        yyval.vval = ittask = vs_pcreate(lasttask);
                ;
    break;}
case 162:
#line 1010 "ifm-parse.y"
{
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                ;
    break;}
case 164:
#line 1019 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                ;
    break;}
case 165:
#line 1023 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                ;
    break;}
case 166:
#line 1027 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                ;
    break;}
case 167:
#line 1031 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                ;
    break;}
case 168:
#line 1035 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, NULL);
                ;
    break;}
case 169:
#line 1039 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, NULL);
                ;
    break;}
case 170:
#line 1045 "ifm-parse.y"
{
                    var_alias(yyvsp[-3].sval, yyvsp[-1].sval);
                ;
    break;}
case 171:
#line 1049 "ifm-parse.y"
{
                    var_alias(yyvsp[-3].sval, NULL);
                ;
    break;}
case 173:
#line 1056 "ifm-parse.y"
{
                    push_style(yyvsp[0].sval);
                    instyle++;
                ;
    break;}
case 174:
#line 1061 "ifm-parse.y"
{
                    push_style("puzzle");
                    instyle++;
                ;
    break;}
case 175:
#line 1066 "ifm-parse.y"
{
                    push_style("special");
                    instyle++;
                ;
    break;}
case 176:
#line 1077 "ifm-parse.y"
{
                    push_style(yyvsp[-1].sval);
                ;
    break;}
case 177:
#line 1081 "ifm-parse.y"
{
                    push_style("puzzle");
                ;
    break;}
case 178:
#line 1085 "ifm-parse.y"
{
                    push_style("special");
                ;
    break;}
case 179:
#line 1089 "ifm-parse.y"
{
                    pop_style(yyvsp[-1].sval);
                ;
    break;}
case 180:
#line 1093 "ifm-parse.y"
{
                    pop_style("puzzle");
                ;
    break;}
case 181:
#line 1097 "ifm-parse.y"
{
                    pop_style("special");
                ;
    break;}
case 182:
#line 1101 "ifm-parse.y"
{
                    pop_style(NULL);
                ;
    break;}
case 185:
#line 1111 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", yyvsp[0].sval);
                    ref_style(yyvsp[0].sval);
                ;
    break;}
case 186:
#line 1116 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", "puzzle");
                    ref_style("puzzle");
                ;
    break;}
case 187:
#line 1121 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", "special");
                    ref_style("special");
                ;
    break;}
case 190:
#line 1136 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, yyvsp[0].ival);
		;
    break;}
case 191:
#line 1142 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-1].ival);
                ;
    break;}
case 192:
#line 1151 "ifm-parse.y"
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
case 193:
#line 1162 "ifm-parse.y"
{ yyval.ival = D_NORTH;	    ;
    break;}
case 194:
#line 1163 "ifm-parse.y"
{ yyval.ival = D_EAST;	    ;
    break;}
case 195:
#line 1164 "ifm-parse.y"
{ yyval.ival = D_SOUTH;	    ;
    break;}
case 196:
#line 1165 "ifm-parse.y"
{ yyval.ival = D_WEST;	    ;
    break;}
case 197:
#line 1166 "ifm-parse.y"
{ yyval.ival = D_NORTHEAST; ;
    break;}
case 198:
#line 1167 "ifm-parse.y"
{ yyval.ival = D_NORTHWEST; ;
    break;}
case 199:
#line 1168 "ifm-parse.y"
{ yyval.ival = D_SOUTHEAST; ;
    break;}
case 200:
#line 1169 "ifm-parse.y"
{ yyval.ival = D_SOUTHWEST; ;
    break;}
case 201:
#line 1172 "ifm-parse.y"
{ yyval.ival = D_IN;   ;
    break;}
case 202:
#line 1173 "ifm-parse.y"
{ yyval.ival = D_OUT;  ;
    break;}
case 203:
#line 1174 "ifm-parse.y"
{ yyval.ival = D_UP;   ;
    break;}
case 204:
#line 1175 "ifm-parse.y"
{ yyval.ival = D_DOWN; ;
    break;}
case 205:
#line 1182 "ifm-parse.y"
{ yyval.dval = yyvsp[0].ival; ;
    break;}
case 206:
#line 1183 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 207:
#line 1184 "ifm-parse.y"
{ yyval.dval = var_real(yyvsp[0].sval); ;
    break;}
case 208:
#line 1185 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 209:
#line 1186 "ifm-parse.y"
{ yyval.dval = -yyvsp[0].dval; ;
    break;}
case 210:
#line 1187 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval + yyvsp[0].dval; ;
    break;}
case 211:
#line 1188 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval - yyvsp[0].dval; ;
    break;}
case 212:
#line 1189 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval * yyvsp[0].dval; ;
    break;}
case 213:
#line 1190 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval / yyvsp[0].dval; ;
    break;}
case 214:
#line 1191 "ifm-parse.y"
{ yyval.dval = pow(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 215:
#line 1192 "ifm-parse.y"
{ yyval.dval = fmod(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 216:
#line 1193 "ifm-parse.y"
{ yyval.dval = yyvsp[-1].dval; ;
    break;}
case 217:
#line 1196 "ifm-parse.y"
{ yyval.ival = (int) yyvsp[0].dval; ;
    break;}
case 218:
#line 1199 "ifm-parse.y"
{ yyval.sval = yyvsp[0].sval; ;
    break;}
case 219:
#line 1200 "ifm-parse.y"
{ yyval.sval = var_string(yyvsp[0].sval); ;
    break;}
case 220:
#line 1204 "ifm-parse.y"
{
                    yyval.sval = yyvsp[0].sval;
                    repeat = 1;
                ;
    break;}
case 221:
#line 1209 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-1].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                ;
    break;}
case 222:
#line 1216 "ifm-parse.y"
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
#line 1225 "ifm-parse.y"

