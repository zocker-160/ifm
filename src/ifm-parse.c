
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
#define	NORTH	309
#define	EAST	310
#define	SOUTH	311
#define	WEST	312
#define	NORTHEAST	313
#define	NORTHWEST	314
#define	SOUTHEAST	315
#define	SOUTHWEST	316
#define	UP	317
#define	DOWN	318
#define	IN	319
#define	OUT	320
#define	INTEGER	321
#define	REAL	322
#define	STRING	323
#define	ID	324
#define	VAR	325
#define	PLUS	326
#define	MINUS	327

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



#define	YYFINAL		362
#define	YYFLAG		-32768
#define	YYNTBASE	84

#define YYTRANSLATE(x) ((unsigned)(x) <= 327 ? yytranslate[x] : 137)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    77,     2,     2,    82,
    83,    75,    73,     2,    74,     2,    76,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    81,     2,
    72,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    80,     2,     2,     2,     2,     2,     2,
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
    67,    68,    69,    70,    71,    78,    79
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     7,     9,    11,    13,    15,    17,    19,
    21,    23,    27,    31,    32,    38,    39,    45,    46,    49,
    52,    57,    60,    63,    66,    69,    72,    74,    76,    78,
    80,    82,    85,    88,    91,    94,    97,   100,   103,   107,
   111,   114,   117,   119,   121,   123,   126,   128,   130,   132,
   134,   135,   141,   142,   148,   149,   152,   155,   158,   161,
   163,   165,   167,   169,   173,   177,   180,   183,   186,   189,
   191,   194,   196,   199,   201,   203,   207,   209,   211,   213,
   215,   216,   224,   225,   231,   232,   235,   238,   241,   243,
   245,   247,   250,   253,   256,   259,   262,   265,   269,   273,
   276,   279,   281,   282,   290,   291,   297,   298,   301,   304,
   307,   309,   311,   313,   316,   319,   322,   325,   328,   331,
   335,   339,   342,   345,   346,   352,   353,   359,   360,   363,
   366,   369,   372,   375,   378,   381,   386,   391,   398,   402,
   408,   412,   415,   418,   421,   424,   427,   429,   432,   434,
   437,   440,   443,   446,   448,   451,   453,   455,   457,   459,
   461,   463,   469,   476,   482,   489,   495,   502,   507,   512,
   513,   517,   521,   525,   529,   533,   537,   541,   545,   549,
   552,   554,   557,   559,   561,   563,   565,   568,   570,   573,
   577,   579,   581,   583,   585,   587,   589,   591,   593,   595,
   597,   599,   601,   603,   605,   607,   610,   613,   617,   621,
   625,   629,   633,   637,   641,   643,   645,   647,   649,   652
};

static const short yyrhs[] = {    -1,
    84,    85,     0,    84,     1,     0,    86,     0,    87,     0,
    95,     0,   104,     0,   109,     0,   114,     0,   122,     0,
   126,     0,    32,   135,    81,     0,    26,   135,    81,     0,
     0,     3,   135,    88,    90,    81,     0,     0,     3,    70,
    89,    90,    81,     0,     0,    90,    91,     0,     7,    70,
     0,     9,   129,     6,    70,     0,     9,   129,     0,    27,
   129,     0,     5,    92,     0,    19,    92,     0,    20,   132,
     0,    10,     0,    48,     0,    49,     0,    24,     0,    40,
     0,    16,   100,     0,    35,   119,     0,    15,   119,     0,
    38,   101,     0,    31,   134,     0,    18,   134,     0,    37,
   136,     0,    37,     8,   136,     0,    37,     6,   136,     0,
    13,   135,     0,    52,   127,     0,    21,     0,    12,     0,
    93,     0,    92,    93,     0,    94,     0,    70,     0,    45,
     0,    23,     0,     0,     4,   135,    96,    98,    81,     0,
     0,     4,    70,    97,    98,    81,     0,     0,    98,    99,
     0,     7,    70,     0,    65,    94,     0,    13,   135,     0,
    11,     0,    28,     0,    29,     0,    30,     0,    30,    54,
   100,     0,    30,    46,   119,     0,    16,   100,     0,    35,
   119,     0,    15,   119,     0,    18,   134,     0,    40,     0,
    52,   127,     0,   102,     0,   100,   102,     0,   100,     0,
    43,     0,    43,    44,   100,     0,   103,     0,    70,     0,
    45,     0,    23,     0,     0,     5,    94,     8,    94,   105,
   107,    81,     0,     0,     5,    70,   106,   107,    81,     0,
     0,   107,   108,     0,     9,   129,     0,    20,   132,     0,
    10,     0,    11,     0,    49,     0,    16,   100,     0,    35,
   119,     0,    15,   119,     0,    38,   101,     0,    31,   134,
     0,    37,   136,     0,    37,     8,   136,     0,    37,     6,
   136,     0,     7,    70,     0,    52,   127,     0,    21,     0,
     0,    19,    94,     8,    94,   110,   112,    81,     0,     0,
    19,    70,   111,   112,    81,     0,     0,   112,   113,     0,
    20,   131,     0,    20,   132,     0,    10,     0,    11,     0,
    49,     0,    16,   100,     0,    35,   119,     0,    15,   119,
     0,    38,   101,     0,    31,   134,     0,    37,   136,     0,
    37,     8,   136,     0,    37,     6,   136,     0,     7,    70,
     0,    52,   127,     0,     0,    14,   135,   115,   117,    81,
     0,     0,    14,    70,   116,   117,    81,     0,     0,   117,
   118,     0,     7,    70,     0,    15,   119,     0,    16,   100,
     0,    41,   100,     0,    17,   100,     0,    42,   101,     0,
    42,   101,    46,   119,     0,    42,   101,    65,    94,     0,
    42,   101,    65,    94,    46,   119,     0,    42,    65,    94,
     0,    42,    65,    94,    46,   119,     0,    42,    46,   119,
     0,    33,   100,     0,    25,    94,     0,    36,   121,     0,
    65,    94,     0,    65,    22,     0,    34,     0,    18,   134,
     0,    40,     0,    37,   136,     0,    37,    50,     0,    13,
   135,     0,    52,   127,     0,   120,     0,   119,   120,     0,
   121,     0,    70,     0,    45,     0,    23,     0,   123,     0,
   124,     0,    70,    72,   133,   125,    81,     0,    70,    70,
    72,   133,   125,    81,     0,    70,    72,    69,   125,    81,
     0,    70,    70,    72,    69,   125,    81,     0,    70,    72,
    39,   125,    81,     0,    70,    70,    72,    39,   125,    81,
     0,    70,    51,    70,    81,     0,    70,    51,    39,    81,
     0,     0,    65,    52,    70,     0,    65,    52,    12,     0,
    65,    52,    21,     0,    52,    70,    81,     0,    52,    12,
    81,     0,    52,    21,    81,     0,    53,    70,    81,     0,
    53,    12,    81,     0,    53,    21,    81,     0,    53,    81,
     0,   128,     0,   127,   128,     0,    70,     0,    12,     0,
    21,     0,   130,     0,   129,   130,     0,   131,     0,   131,
   134,     0,   131,    47,   134,     0,    55,     0,    56,     0,
    57,     0,    58,     0,    59,     0,    60,     0,    61,     0,
    62,     0,    65,     0,    66,     0,    63,     0,    64,     0,
    67,     0,    68,     0,    71,     0,    73,   133,     0,    74,
   133,     0,   133,    73,   133,     0,   133,    74,   133,     0,
   133,    75,   133,     0,   133,    76,   133,     0,   133,    80,
   133,     0,   133,    77,   133,     0,    82,   133,    83,     0,
   133,     0,    69,     0,    71,     0,   135,     0,   135,   134,
     0,   135,    47,   134,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   105,   106,   107,   110,   111,   112,   113,   114,   115,   116,
   117,   124,   128,   140,   150,   243,   251,   257,   258,   261,
   268,   287,   302,   315,   330,   345,   349,   353,   357,   361,
   365,   369,   373,   377,   381,   387,   391,   395,   400,   405,
   410,   414,   415,   421,   429,   430,   433,   441,   445,   452,
   465,   473,   482,   490,   496,   497,   500,   507,   511,   515,
   519,   524,   528,   532,   536,   540,   544,   548,   552,   556,
   560,   563,   564,   567,   568,   569,   572,   580,   584,   591,
   604,   612,   617,   625,   631,   632,   635,   640,   644,   648,
   652,   656,   660,   664,   668,   674,   678,   683,   688,   693,
   700,   701,   713,   721,   726,   734,   740,   741,   744,   748,
   752,   756,   760,   764,   768,   772,   776,   782,   786,   791,
   796,   801,   808,   815,   822,   833,   841,   847,   848,   851,
   858,   862,   866,   870,   874,   880,   887,   894,   902,   906,
   911,   915,   919,   923,   927,   931,   935,   939,   943,   947,
   952,   956,   960,   963,   964,   967,   975,   979,   986,   999,
  1005,  1008,  1012,  1016,  1020,  1024,  1028,  1034,  1038,  1044,
  1045,  1050,  1055,  1066,  1070,  1074,  1078,  1082,  1086,  1090,
  1096,  1097,  1100,  1105,  1110,  1121,  1122,  1125,  1131,  1140,
  1152,  1153,  1154,  1155,  1156,  1157,  1158,  1159,  1162,  1163,
  1164,  1165,  1172,  1173,  1174,  1175,  1176,  1177,  1178,  1179,
  1180,  1181,  1182,  1183,  1186,  1189,  1190,  1193,  1198,  1205
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ROOM","ITEM",
"LINK","FROM","TAG","TO","DIR","ONEWAY","HIDDEN","PUZZLE","NOTE","TASK","AFTER",
"NEED","GET","SCORE","JOIN","GO","SPECIAL","ANY","LAST","START","GOTO","MAP",
"EXIT","GIVEN","LOST","KEEP","LENGTH","TITLE","LOSE","SAFE","BEFORE","FOLLOW",
"CMD","LEAVE","UNDEF","FINISH","GIVE","DROP","ALL","EXCEPT","IT","UNTIL","TIMES",
"NOLINK","NOPATH","NONE","ALIAS","STYLE","ENDSTYLE","WITH","NORTH","EAST","SOUTH",
"WEST","NORTHEAST","NORTHWEST","SOUTHEAST","SOUTHWEST","UP","DOWN","IN","OUT",
"INTEGER","REAL","STRING","ID","VAR","'='","'+'","'-'","'*'","'/'","'%'","PLUS",
"MINUS","'^'","';'","'('","')'","stmt_list","stmt","ctrl_stmt","room_stmt","@1",
"@2","room_attrs","room_attr","room_list","room_elt","room","item_stmt","@3",
"@4","item_attrs","item_attr","item_list","item_list_all","item_elt","item",
"link_stmt","@5","@6","link_attrs","link_attr","join_stmt","@7","@8","join_attrs",
"join_attr","task_stmt","@9","@10","task_attrs","task_attr","task_list","task_elt",
"task","vars_stmt","set_var","alias_var","in_style","style_stmt","style_list",
"style_elt","dir_list","dir_elt","compass","otherdir","exp","integer","string",
"string_repeat", NULL
};
#endif

static const short yyr1[] = {     0,
    84,    84,    84,    85,    85,    85,    85,    85,    85,    85,
    85,    86,    86,    88,    87,    89,    87,    90,    90,    91,
    91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
    91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
    91,    91,    91,    91,    92,    92,    93,    94,    94,    94,
    96,    95,    97,    95,    98,    98,    99,    99,    99,    99,
    99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
    99,   100,   100,   101,   101,   101,   102,   103,   103,   103,
   105,   104,   106,   104,   107,   107,   108,   108,   108,   108,
   108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
   108,   108,   110,   109,   111,   109,   112,   112,   113,   113,
   113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
   113,   113,   113,   115,   114,   116,   114,   117,   117,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   119,   119,   120,   121,   121,   121,   122,
   122,   123,   123,   123,   123,   123,   123,   124,   124,   125,
   125,   125,   125,   126,   126,   126,   126,   126,   126,   126,
   127,   127,   128,   128,   128,   129,   129,   130,   130,   130,
   131,   131,   131,   131,   131,   131,   131,   131,   132,   132,
   132,   132,   133,   133,   133,   133,   133,   133,   133,   133,
   133,   133,   133,   133,   134,   135,   135,   136,   136,   136
};

static const short yyr2[] = {     0,
     0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
     1,     3,     3,     0,     5,     0,     5,     0,     2,     2,
     4,     2,     2,     2,     2,     2,     1,     1,     1,     1,
     1,     2,     2,     2,     2,     2,     2,     2,     3,     3,
     2,     2,     1,     1,     1,     2,     1,     1,     1,     1,
     0,     5,     0,     5,     0,     2,     2,     2,     2,     1,
     1,     1,     1,     3,     3,     2,     2,     2,     2,     1,
     2,     1,     2,     1,     1,     3,     1,     1,     1,     1,
     0,     7,     0,     5,     0,     2,     2,     2,     1,     1,
     1,     2,     2,     2,     2,     2,     2,     3,     3,     2,
     2,     1,     0,     7,     0,     5,     0,     2,     2,     2,
     1,     1,     1,     2,     2,     2,     2,     2,     2,     3,
     3,     2,     2,     0,     5,     0,     5,     0,     2,     2,
     2,     2,     2,     2,     2,     4,     4,     6,     3,     5,
     3,     2,     2,     2,     2,     2,     1,     2,     1,     2,
     2,     2,     2,     1,     2,     1,     1,     1,     1,     1,
     1,     5,     6,     5,     6,     5,     6,     4,     4,     0,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
     1,     2,     1,     1,     1,     1,     2,     1,     2,     3,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     2,     2,     3,     3,     3,
     3,     3,     3,     3,     1,     1,     1,     1,     2,     3
};

static const short yydefact[] = {     1,
     0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     2,     4,     5,     6,     7,     8,     9,    10,
   160,   161,    11,   216,    16,   217,    14,    53,    51,    50,
    49,    83,     0,   126,   124,   105,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   180,     0,     0,     0,    18,
    18,    55,    55,    85,     0,   128,   128,   107,     0,    13,
    12,   175,   176,   174,   178,   179,   177,     0,     0,     0,
   170,   203,   204,   170,   205,     0,     0,     0,   170,     0,
     0,     0,     0,     0,    48,    81,     0,     0,     0,   103,
   169,   168,   170,   170,   170,     0,     0,     0,   206,   207,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    27,    44,     0,     0,     0,     0,     0,     0,    43,
    30,     0,     0,     0,     0,     0,    31,    28,    29,     0,
    17,    19,    15,     0,    60,     0,     0,     0,     0,    61,
    62,    63,     0,    70,     0,     0,    54,    56,    52,     0,
     0,    89,    90,     0,     0,     0,   102,     0,     0,     0,
     0,    91,     0,    84,    86,    85,     0,     0,     0,     0,
     0,     0,     0,     0,   147,     0,     0,   149,     0,     0,
     0,     0,   127,   129,   125,     0,   111,   112,     0,     0,
     0,     0,     0,     0,     0,   113,     0,   106,   108,   107,
     0,     0,     0,     0,   166,   164,   214,   208,   209,   210,
   211,   213,   212,   162,    24,    45,    47,    20,   191,   192,
   193,   194,   195,   196,   197,   198,    22,   186,   188,    41,
   159,   158,   157,    34,   154,   156,    80,    79,    78,    32,
    72,    77,   215,    37,    25,   201,   202,   199,   200,    26,
    23,    36,    33,     0,     0,   218,    38,    75,    74,    35,
   184,   185,   183,    42,   181,    57,    59,    68,    66,    69,
     0,     0,    67,    71,    58,   100,    87,    94,    92,    88,
    96,    93,     0,     0,    97,    95,   101,     0,   130,   152,
   131,   132,   134,   148,   143,   142,   144,   151,   150,   133,
     0,     0,   135,   153,   146,   145,   122,   116,   114,   109,
   110,   118,   115,     0,     0,   119,   117,   123,     0,   167,
   165,   163,   172,   173,   171,    46,     0,   187,     0,   189,
   155,    73,    40,    39,     0,   219,     0,   182,    65,    64,
    99,    98,    82,   141,   139,     0,     0,   121,   120,   104,
    21,   190,   220,    76,     0,   136,   137,   140,     0,   138,
     0,     0
};

static const short yydefgoto[] = {     1,
    13,    14,    15,    51,    50,    80,   132,   215,   216,   217,
    16,    53,    52,    82,   148,   259,   260,   241,   242,    17,
   166,    54,    84,   165,    18,   200,    58,    89,   199,    19,
    57,    56,    87,   184,   234,   235,   236,    20,    21,    22,
    97,    23,   264,   265,   227,   228,   229,   250,   243,   244,
   256,   257
};

static const short yypact[] = {-32768,
   500,-32768,    57,   127,    87,   187,   136,   -41,   -41,    13,
     1,    73,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    24,    41,-32768,-32768,    24,    61,    -7,    -1,     6,
    34,    54,    59,    68,    71,-32768,    21,     4,   472,-32768,
-32768,-32768,-32768,-32768,   159,-32768,-32768,-32768,   159,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    75,    91,   505,
    46,-32768,-32768,    46,-32768,   321,   321,   321,   352,   228,
   280,    77,   405,   164,-32768,-32768,   318,   332,   443,-32768,
-32768,-32768,    46,    46,   352,   124,   122,   129,   134,   134,
   543,   321,   321,   321,   321,   321,   321,   130,   159,   148,
   572,-32768,-32768,   -41,   160,   194,   321,   159,   101,-32768,
-32768,   572,   321,   160,    10,    -6,-32768,-32768,-32768,    30,
-32768,-32768,-32768,   152,-32768,   -41,   160,   194,   321,-32768,
-32768,    43,   160,-32768,    30,   159,-32768,-32768,-32768,   154,
   572,-32768,-32768,   160,   194,   101,-32768,   321,   160,    27,
    -6,-32768,    30,-32768,-32768,-32768,   161,   -41,   160,   194,
   194,   321,   159,   194,-32768,   160,   150,-32768,   194,   401,
    30,    99,-32768,-32768,-32768,   172,-32768,-32768,   160,   194,
   549,   321,   160,    49,    -6,-32768,    30,-32768,-32768,-32768,
   139,   153,   169,    44,-32768,-32768,-32768,   195,   195,   134,
   134,   134,   134,-32768,   159,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   131,-32768,   394,-32768,
-32768,-32768,-32768,   160,-32768,-32768,-32768,-32768,-32768,   194,
-32768,-32768,   562,-32768,   159,-32768,-32768,-32768,-32768,-32768,
   572,-32768,   160,   -41,   -41,   521,-32768,   209,   194,-32768,
-32768,-32768,-32768,    30,-32768,-32768,-32768,   160,   194,-32768,
   160,   194,   160,    30,-32768,-32768,   572,   160,   194,-32768,
-32768,   160,   -41,   -41,-32768,-32768,    30,   370,-32768,-32768,
   160,   194,   194,-32768,-32768,   194,-32768,-32768,-32768,   194,
   160,   159,   -25,    30,-32768,-32768,-32768,   160,   194,-32768,
-32768,-32768,   160,   -41,   -41,-32768,-32768,    30,   478,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   184,-32768,   321,-32768,
-32768,-32768,-32768,-32768,   321,-32768,   194,-32768,   160,   194,
-32768,-32768,-32768,   160,   214,   160,   159,-32768,-32768,-32768,
-32768,-32768,-32768,   194,   160,   160,   216,   160,   160,   160,
   267,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,   218,-32768,   155,  -192,    -5,
-32768,-32768,-32768,   225,-32768,  -112,   -76,  -146,-32768,-32768,
-32768,-32768,   113,-32768,-32768,-32768,-32768,    81,-32768,-32768,
-32768,-32768,   226,-32768,  -123,  -205,   106,-32768,-32768,-32768,
   133,-32768,  -136,   -13,  -107,  -152,    93,  -144,   458,  -120,
     2,  -153
};


#define	YYLAST		642


static const short yytable[] = {    33,
   253,    37,   252,   240,    27,    29,   285,    35,   274,    38,
    39,   280,    43,   268,   251,   254,   237,   255,   270,   273,
   346,    44,   326,   299,    40,   269,   287,    24,   331,    26,
   278,   -48,   283,    41,   284,   282,   258,   281,   238,   347,
   316,   261,   279,   277,   304,   291,   311,   331,    55,    86,
   262,   294,   326,    90,   314,   323,   315,   292,   293,    68,
   318,   296,   331,   239,   324,   308,   300,   331,    59,   313,
    45,   312,   331,    60,   328,    70,   331,   309,    24,    61,
    26,    46,    42,   134,   286,   331,    62,   135,   271,   136,
    69,   137,   138,   332,   139,    24,   272,    26,   328,   263,
   333,   334,   331,   303,   140,   141,   142,   331,   330,    30,
    96,   143,   332,   325,    63,   230,   144,    24,   317,    26,
   305,    30,   332,    47,   328,    24,    25,    26,   145,   341,
   342,    31,   332,   331,    64,   336,   327,   267,   331,    65,
   275,   146,    48,    31,    49,   332,   332,   339,    66,   332,
   331,    67,   331,   332,   331,    91,    32,   147,    30,   340,
   348,   349,   332,   246,   247,   248,   249,   295,    85,   290,
   150,    92,   151,   152,   153,   204,   306,   344,   154,   155,
    31,    30,   231,   156,   157,   219,   220,   221,   222,   223,
   224,   225,   226,   332,   158,    24,    28,    26,   159,   298,
   160,   161,   205,    31,   232,    36,    98,   332,   352,   206,
   214,   108,   162,   107,   353,   163,   237,   218,    24,   320,
    26,   266,   356,   276,   354,   201,   202,   203,    85,   233,
   289,   358,   109,   321,   110,   360,   111,   112,   238,   113,
   114,   307,   115,   116,   164,   117,   118,   119,   120,   322,
   338,   121,   337,   351,   122,    24,    34,    26,   123,   355,
   338,   359,   124,   239,   125,   126,   362,   127,    81,   104,
   105,   106,   245,   338,   107,   128,   129,    83,   288,   130,
   319,   297,    88,   310,   109,     0,   110,     0,   111,   112,
   338,   113,   114,     0,   115,   116,   345,   117,   118,   119,
   120,     0,     0,   121,   338,     0,   122,     0,   131,     0,
   123,     0,     0,     0,   124,     0,   125,   126,     0,   127,
     0,     0,     0,     0,   167,     0,     0,   128,   129,     0,
   168,   130,   169,   170,   171,   172,     0,     0,   167,     0,
     0,   357,   173,     0,   168,     0,   169,   170,   171,   172,
   174,   175,     0,   176,   177,     0,   173,   178,   179,   180,
   133,     0,     0,     0,   174,   175,     0,   176,   177,   181,
     0,   178,   179,   180,     0,     0,   150,     0,   151,   152,
   153,     0,   182,   181,   154,   155,     0,    72,    73,   156,
   157,    75,     0,    76,    77,     0,   182,     0,   183,     0,
   158,     0,    78,     0,   159,     0,   160,   161,     0,     0,
     0,   134,   185,     0,     0,   135,    96,   136,   162,   137,
   138,   163,   139,   237,   102,   103,   104,   105,   106,     0,
     0,   107,   140,   141,   142,     0,     0,     0,     0,   143,
   329,     0,     0,   258,   144,   238,   301,     0,     0,   186,
   343,     0,   187,   188,     0,     0,   145,   189,   190,     0,
    72,    73,   191,     0,    75,   302,    76,    77,     0,   146,
   239,     0,     0,   192,     0,    78,     0,   193,     0,   194,
   195,     0,     0,     0,   186,   149,     0,   187,   188,     0,
     0,   196,   189,   190,   197,     0,     0,   191,     0,   361,
     2,     0,     3,     4,     5,     0,    79,     0,   192,     0,
    71,     0,   193,     6,   194,   195,     0,     0,     7,     0,
     0,     0,     0,   198,     0,     8,   196,    95,     0,   197,
     0,     9,     0,    99,   100,   101,     0,     0,    72,    73,
    74,     0,    75,    93,    76,    77,     0,     0,     0,     0,
     0,    10,    11,    78,     0,     0,     0,     0,   350,   208,
   209,   210,   211,   212,   213,     0,     0,   335,     0,    12,
     0,    72,    73,    94,     0,    75,     0,    76,    77,     0,
     0,     0,     0,     0,     0,     0,    78,    72,    73,     0,
     0,    75,     0,    76,    77,     0,     0,     0,     0,     0,
     0,     0,    78,   219,   220,   221,   222,   223,   224,   225,
   226,   246,   247,   248,   249,   102,   103,   104,   105,   106,
     0,     0,   107,     0,     0,   207,   219,   220,   221,   222,
   223,   224,   225,   226,   102,   103,   104,   105,   106,     0,
     0,   107
};

static const short yycheck[] = {     5,
   124,     7,   123,   116,     3,     4,   160,     6,   145,     8,
     9,   156,    12,   137,   122,     6,    23,     8,   139,   143,
    46,    21,   215,   177,    12,   138,   163,    69,   234,    71,
   154,     8,     6,    21,     8,   159,    43,   158,    45,    65,
   194,    12,   155,   151,   181,   169,   191,   253,     8,    55,
    21,   172,   245,    59,     6,    12,     8,   170,   171,    39,
   197,   174,   268,    70,    21,   189,   179,   273,     8,   193,
    70,   192,   278,    81,   227,    72,   282,   190,    69,    81,
    71,    81,    70,     7,   161,   291,    81,    11,    46,    13,
    70,    15,    16,   240,    18,    69,    54,    71,   251,    70,
   254,   255,   308,   180,    28,    29,    30,   313,   229,    23,
    65,    35,   259,    70,    81,   114,    40,    69,   195,    71,
    22,    23,   269,    51,   277,    69,    70,    71,    52,   283,
   284,    45,   279,   339,    81,   256,     6,   136,   344,    81,
   146,    65,    70,    45,    72,   292,   293,   271,    81,   296,
   356,    81,   358,   300,   360,    81,    70,    81,    23,   272,
   314,   315,   309,    63,    64,    65,    66,   173,    70,   168,
     7,    81,     9,    10,    11,    52,   182,   301,    15,    16,
    45,    23,    23,    20,    21,    55,    56,    57,    58,    59,
    60,    61,    62,   340,    31,    69,    70,    71,    35,    50,
    37,    38,    81,    45,    45,    70,    74,   354,   329,    81,
    81,    79,    49,    80,   335,    52,    23,    70,    69,    81,
    71,    70,   346,    70,   337,    93,    94,    95,    70,    70,
    70,   355,     5,    81,     7,   359,     9,    10,    45,    12,
    13,    70,    15,    16,    81,    18,    19,    20,    21,    81,
   264,    24,    44,    70,    27,    69,    70,    71,    31,    46,
   274,    46,    35,    70,    37,    38,     0,    40,    51,    75,
    76,    77,   118,   287,    80,    48,    49,    53,   166,    52,
   200,   176,    57,   191,     5,    -1,     7,    -1,     9,    10,
   304,    12,    13,    -1,    15,    16,   302,    18,    19,    20,
    21,    -1,    -1,    24,   318,    -1,    27,    -1,    81,    -1,
    31,    -1,    -1,    -1,    35,    -1,    37,    38,    -1,    40,
    -1,    -1,    -1,    -1,     7,    -1,    -1,    48,    49,    -1,
    13,    52,    15,    16,    17,    18,    -1,    -1,     7,    -1,
    -1,   347,    25,    -1,    13,    -1,    15,    16,    17,    18,
    33,    34,    -1,    36,    37,    -1,    25,    40,    41,    42,
    81,    -1,    -1,    -1,    33,    34,    -1,    36,    37,    52,
    -1,    40,    41,    42,    -1,    -1,     7,    -1,     9,    10,
    11,    -1,    65,    52,    15,    16,    -1,    67,    68,    20,
    21,    71,    -1,    73,    74,    -1,    65,    -1,    81,    -1,
    31,    -1,    82,    -1,    35,    -1,    37,    38,    -1,    -1,
    -1,     7,    81,    -1,    -1,    11,    65,    13,    49,    15,
    16,    52,    18,    23,    73,    74,    75,    76,    77,    -1,
    -1,    80,    28,    29,    30,    -1,    -1,    -1,    -1,    35,
    47,    -1,    -1,    43,    40,    45,    46,    -1,    -1,     7,
    81,    -1,    10,    11,    -1,    -1,    52,    15,    16,    -1,
    67,    68,    20,    -1,    71,    65,    73,    74,    -1,    65,
    70,    -1,    -1,    31,    -1,    82,    -1,    35,    -1,    37,
    38,    -1,    -1,    -1,     7,    81,    -1,    10,    11,    -1,
    -1,    49,    15,    16,    52,    -1,    -1,    20,    -1,     0,
     1,    -1,     3,     4,     5,    -1,    49,    -1,    31,    -1,
    39,    -1,    35,    14,    37,    38,    -1,    -1,    19,    -1,
    -1,    -1,    -1,    81,    -1,    26,    49,    70,    -1,    52,
    -1,    32,    -1,    76,    77,    78,    -1,    -1,    67,    68,
    69,    -1,    71,    39,    73,    74,    -1,    -1,    -1,    -1,
    -1,    52,    53,    82,    -1,    -1,    -1,    -1,    81,   102,
   103,   104,   105,   106,   107,    -1,    -1,    47,    -1,    70,
    -1,    67,    68,    69,    -1,    71,    -1,    73,    74,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    82,    67,    68,    -1,
    -1,    71,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    82,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    66,    73,    74,    75,    76,    77,
    -1,    -1,    80,    -1,    -1,    83,    55,    56,    57,    58,
    59,    60,    61,    62,    73,    74,    75,    76,    77,    -1,
    -1,    80
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
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

#line 217 "/usr/local/share/bison.simple"

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
#line 125 "ifm-parse.y"
{
                    vh_sstore(map, "TITLE", yyvsp[-1].sval);
                ;
    break;}
case 13:
#line 129 "ifm-parse.y"
{
                    if (sectnames == NULL)
                        sectnames = vl_create();
                    vl_spush(sectnames, yyvsp[-1].sval);
                ;
    break;}
case 14:
#line 141 "ifm-parse.y"
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
#line 151 "ifm-parse.y"
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
#line 244 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(roomtags, yyvsp[0].sval)) == NULL) {
                        err("room tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 17:
#line 252 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 20:
#line 262 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("room", yyvsp[0].sval, curobj, roomtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 21:
#line 269 "ifm-parse.y"
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
#line 288 "ifm-parse.y"
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
#line 303 "ifm-parse.y"
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
#line 316 "ifm-parse.y"
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
#line 331 "ifm-parse.y"
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
#line 346 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 27:
#line 350 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 28:
#line 354 "ifm-parse.y"
{
                    vh_istore(curobj, "NOLINK", 1);
		;
    break;}
case 29:
#line 358 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 30:
#line 362 "ifm-parse.y"
{
                    startroom = curobj;
		;
    break;}
case 31:
#line 366 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 32:
#line 370 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(NEED), curitems);
                ;
    break;}
case 33:
#line 374 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		;
    break;}
case 34:
#line 378 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		;
    break;}
case 35:
#line 382 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                ;
    break;}
case 36:
#line 388 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 37:
#line 392 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 38:
#line 396 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 39:
#line 401 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 40:
#line 406 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 41:
#line 411 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 43:
#line 416 "ifm-parse.y"
{
                    obsolete("`special' attribute", "`style special'");
                    add_attr(curobj, ATTR(STYLE), "special");
                    ref_style("special");
		;
    break;}
case 44:
#line 422 "ifm-parse.y"
{
                    obsolete("`puzzle' attribute", "`style puzzle'");
                    add_attr(curobj, ATTR(STYLE), "puzzle");
                    ref_style("puzzle");
		;
    break;}
case 47:
#line 434 "ifm-parse.y"
{
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, yyvsp[0].vval);
		;
    break;}
case 48:
#line 442 "ifm-parse.y"
{
                    yyval.vval = itroom = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 49:
#line 446 "ifm-parse.y"
{
                    if (itroom == NULL)
                        err("no room referred to by `it'");
                    else
                        yyval.vval = vs_copy(itroom);
                ;
    break;}
case 50:
#line 453 "ifm-parse.y"
{
                    if (lastroom == NULL)
                        err("no room referred to by `last'");
                    else
                        yyval.vval = itroom = vs_pcreate(lastroom);
                ;
    break;}
case 51:
#line 466 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_istore(curobj, "ID", ++itemid);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 52:
#line 474 "ifm-parse.y"
{
                    if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lastitem = curobj;
                    vl_ppush(items, curobj);
                    RESET_IT;
		;
    break;}
case 53:
#line 483 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(itemtags, yyvsp[0].sval)) == NULL) {
                        err("item tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 54:
#line 491 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 57:
#line 501 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("item", yyvsp[0].sval, curobj, itemtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 58:
#line 508 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 59:
#line 512 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 60:
#line 516 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 61:
#line 520 "ifm-parse.y"
{
                    obsolete("`given' attribute", "task `give' attribute");
                    vh_istore(curobj, "GIVEN", 1);
		;
    break;}
case 62:
#line 525 "ifm-parse.y"
{
                    vh_istore(curobj, "LOST", 1);
		;
    break;}
case 63:
#line 529 "ifm-parse.y"
{
                    vh_istore(curobj, "KEEP", 1);
		;
    break;}
case 64:
#line 533 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_WITH", curitems);
		;
    break;}
case 65:
#line 537 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_UNTIL", curtasks);
		;
    break;}
case 66:
#line 541 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 67:
#line 545 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
                ;
    break;}
case 68:
#line 549 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
                ;
    break;}
case 69:
#line 553 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 70:
#line 557 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 74:
#line 567 "ifm-parse.y"
{ allflag = 0; ;
    break;}
case 75:
#line 568 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 76:
#line 569 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 77:
#line 573 "ifm-parse.y"
{
                    if (curitems == NULL)
                        curitems = vl_create();
                    vl_push(curitems, yyvsp[0].vval);
		;
    break;}
case 78:
#line 581 "ifm-parse.y"
{
                    yyval.vval = ititem = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 79:
#line 585 "ifm-parse.y"
{
                    if (ititem == NULL)
                        err("no item referred to by `it'");
                    else
                        yyval.vval = vs_copy(ititem);
                ;
    break;}
case 80:
#line 592 "ifm-parse.y"
{
                    if (lastitem == NULL)
                        err("no item referred to by `last'");
                    else
                        yyval.vval = ititem = vs_pcreate(lastitem);
                ;
    break;}
case 81:
#line 605 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 82:
#line 613 "ifm-parse.y"
{
                    vl_ppush(links, curobj);
                    RESET_IT;
		;
    break;}
case 83:
#line 618 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(linktags, yyvsp[0].sval)) == NULL) {
                        err("link tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 84:
#line 626 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 87:
#line 636 "ifm-parse.y"
{
                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;
		;
    break;}
case 88:
#line 641 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 89:
#line 645 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 90:
#line 649 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 91:
#line 653 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 92:
#line 657 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 93:
#line 661 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 94:
#line 665 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 95:
#line 669 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 96:
#line 675 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 97:
#line 679 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 98:
#line 684 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 99:
#line 689 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 100:
#line 694 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("link", yyvsp[0].sval, curobj, linktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 102:
#line 702 "ifm-parse.y"
{
                    obsolete("`special' attribute", "`style special'");
                    add_attr(curobj, "STYLE", "special");
                    ref_style("special");
		;
    break;}
case 103:
#line 714 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 104:
#line 722 "ifm-parse.y"
{
                    vl_ppush(joins, curobj);
                    RESET_IT;
		;
    break;}
case 105:
#line 727 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(jointags, yyvsp[0].sval)) == NULL) {
                        err("join tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 106:
#line 735 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 109:
#line 745 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 110:
#line 749 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 111:
#line 753 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 112:
#line 757 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 113:
#line 761 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 114:
#line 765 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 115:
#line 769 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 116:
#line 773 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 117:
#line 777 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 118:
#line 783 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 119:
#line 787 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 120:
#line 792 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 121:
#line 797 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 122:
#line 802 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("join", yyvsp[0].sval, curobj, jointags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 124:
#line 816 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 125:
#line 823 "ifm-parse.y"
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
case 126:
#line 834 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(tasktags, yyvsp[0].sval)) == NULL) {
                        err("task tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 127:
#line 842 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 130:
#line 852 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("task", yyvsp[0].sval, curobj, tasktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 131:
#line 859 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 132:
#line 863 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
		;
    break;}
case 133:
#line 867 "ifm-parse.y"
{
                    SET_LIST(curobj, "GIVE", curitems);
		;
    break;}
case 134:
#line 871 "ifm-parse.y"
{
                    SET_LIST(curobj, "GET", curitems);
		;
    break;}
case 135:
#line 875 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
		;
    break;}
case 136:
#line 881 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 137:
#line 888 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 138:
#line 895 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 139:
#line 903 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 140:
#line 907 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 141:
#line 912 "ifm-parse.y"
{
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
                ;
    break;}
case 142:
#line 916 "ifm-parse.y"
{
                    SET_LIST(curobj, "LOSE", curitems);
		;
    break;}
case 143:
#line 920 "ifm-parse.y"
{
                    vh_store(curobj, "GOTO", yyvsp[0].vval);
                ;
    break;}
case 144:
#line 924 "ifm-parse.y"
{
                    vh_store(curobj, "FOLLOW", yyvsp[0].vval);
                ;
    break;}
case 145:
#line 928 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 146:
#line 932 "ifm-parse.y"
{
                    vh_istore(curobj, "NOROOM", 1);
		;
    break;}
case 147:
#line 936 "ifm-parse.y"
{
                    vh_istore(curobj, "SAFE", 1);
                ;
    break;}
case 148:
#line 940 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 149:
#line 944 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 150:
#line 948 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", yyvsp[0].sval);
                ;
    break;}
case 151:
#line 953 "ifm-parse.y"
{
                    add_attr(curobj, "CMD", NULL);
                ;
    break;}
case 152:
#line 957 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 156:
#line 968 "ifm-parse.y"
{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, yyvsp[0].vval);
		;
    break;}
case 157:
#line 976 "ifm-parse.y"
{
                    yyval.vval = ittask = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 158:
#line 980 "ifm-parse.y"
{
                    if (ittask == NULL)
                        err("no task referred to by `it'");
                    else
                        yyval.vval = vs_copy(ittask);
                ;
    break;}
case 159:
#line 987 "ifm-parse.y"
{
                    if (lasttask == NULL)
                        err("no task referred to by `last'");
                    else
                        yyval.vval = ittask = vs_pcreate(lasttask);
                ;
    break;}
case 160:
#line 1000 "ifm-parse.y"
{
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                ;
    break;}
case 162:
#line 1009 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                ;
    break;}
case 163:
#line 1013 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                ;
    break;}
case 164:
#line 1017 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                ;
    break;}
case 165:
#line 1021 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                ;
    break;}
case 166:
#line 1025 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, NULL);
                ;
    break;}
case 167:
#line 1029 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, NULL);
                ;
    break;}
case 168:
#line 1035 "ifm-parse.y"
{
                    var_alias(yyvsp[-3].sval, yyvsp[-1].sval);
                ;
    break;}
case 169:
#line 1039 "ifm-parse.y"
{
                    var_alias(yyvsp[-3].sval, NULL);
                ;
    break;}
case 171:
#line 1046 "ifm-parse.y"
{
                    push_style(yyvsp[0].sval);
                    instyle++;
                ;
    break;}
case 172:
#line 1051 "ifm-parse.y"
{
                    push_style("puzzle");
                    instyle++;
                ;
    break;}
case 173:
#line 1056 "ifm-parse.y"
{
                    push_style("special");
                    instyle++;
                ;
    break;}
case 174:
#line 1067 "ifm-parse.y"
{
                    push_style(yyvsp[-1].sval);
                ;
    break;}
case 175:
#line 1071 "ifm-parse.y"
{
                    push_style("puzzle");
                ;
    break;}
case 176:
#line 1075 "ifm-parse.y"
{
                    push_style("special");
                ;
    break;}
case 177:
#line 1079 "ifm-parse.y"
{
                    pop_style(yyvsp[-1].sval);
                ;
    break;}
case 178:
#line 1083 "ifm-parse.y"
{
                    pop_style("puzzle");
                ;
    break;}
case 179:
#line 1087 "ifm-parse.y"
{
                    pop_style("special");
                ;
    break;}
case 180:
#line 1091 "ifm-parse.y"
{
                    pop_style(NULL);
                ;
    break;}
case 183:
#line 1101 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", yyvsp[0].sval);
                    ref_style(yyvsp[0].sval);
                ;
    break;}
case 184:
#line 1106 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", "puzzle");
                    ref_style("puzzle");
                ;
    break;}
case 185:
#line 1111 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", "special");
                    ref_style("special");
                ;
    break;}
case 188:
#line 1126 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, yyvsp[0].ival);
		;
    break;}
case 189:
#line 1132 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-1].ival);
                ;
    break;}
case 190:
#line 1141 "ifm-parse.y"
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
case 191:
#line 1152 "ifm-parse.y"
{ yyval.ival = D_NORTH;	    ;
    break;}
case 192:
#line 1153 "ifm-parse.y"
{ yyval.ival = D_EAST;	    ;
    break;}
case 193:
#line 1154 "ifm-parse.y"
{ yyval.ival = D_SOUTH;	    ;
    break;}
case 194:
#line 1155 "ifm-parse.y"
{ yyval.ival = D_WEST;	    ;
    break;}
case 195:
#line 1156 "ifm-parse.y"
{ yyval.ival = D_NORTHEAST; ;
    break;}
case 196:
#line 1157 "ifm-parse.y"
{ yyval.ival = D_NORTHWEST; ;
    break;}
case 197:
#line 1158 "ifm-parse.y"
{ yyval.ival = D_SOUTHEAST; ;
    break;}
case 198:
#line 1159 "ifm-parse.y"
{ yyval.ival = D_SOUTHWEST; ;
    break;}
case 199:
#line 1162 "ifm-parse.y"
{ yyval.ival = D_IN;   ;
    break;}
case 200:
#line 1163 "ifm-parse.y"
{ yyval.ival = D_OUT;  ;
    break;}
case 201:
#line 1164 "ifm-parse.y"
{ yyval.ival = D_UP;   ;
    break;}
case 202:
#line 1165 "ifm-parse.y"
{ yyval.ival = D_DOWN; ;
    break;}
case 203:
#line 1172 "ifm-parse.y"
{ yyval.dval = yyvsp[0].ival; ;
    break;}
case 204:
#line 1173 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 205:
#line 1174 "ifm-parse.y"
{ yyval.dval = var_real(yyvsp[0].sval); ;
    break;}
case 206:
#line 1175 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 207:
#line 1176 "ifm-parse.y"
{ yyval.dval = -yyvsp[0].dval; ;
    break;}
case 208:
#line 1177 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval + yyvsp[0].dval; ;
    break;}
case 209:
#line 1178 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval - yyvsp[0].dval; ;
    break;}
case 210:
#line 1179 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval * yyvsp[0].dval; ;
    break;}
case 211:
#line 1180 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval / yyvsp[0].dval; ;
    break;}
case 212:
#line 1181 "ifm-parse.y"
{ yyval.dval = pow(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 213:
#line 1182 "ifm-parse.y"
{ yyval.dval = fmod(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 214:
#line 1183 "ifm-parse.y"
{ yyval.dval = yyvsp[-1].dval; ;
    break;}
case 215:
#line 1186 "ifm-parse.y"
{ yyval.ival = (int) yyvsp[0].dval; ;
    break;}
case 216:
#line 1189 "ifm-parse.y"
{ yyval.sval = yyvsp[0].sval; ;
    break;}
case 217:
#line 1190 "ifm-parse.y"
{ yyval.sval = var_string(yyvsp[0].sval); ;
    break;}
case 218:
#line 1194 "ifm-parse.y"
{
                    yyval.sval = yyvsp[0].sval;
                    repeat = 1;
                ;
    break;}
case 219:
#line 1199 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-1].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                ;
    break;}
case 220:
#line 1206 "ifm-parse.y"
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
#line 543 "/usr/local/share/bison.simple"

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
#line 1215 "ifm-parse.y"

