
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
#define	NODROP	266
#define	NOTE	267
#define	TASK	268
#define	AFTER	269
#define	NEED	270
#define	GET	271
#define	SCORE	272
#define	JOIN	273
#define	GO	274
#define	REQUIRE	275
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
#define	STYLE	305
#define	ENDSTYLE	306
#define	WITH	307
#define	IGNORE	308
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



#define	YYFINAL		347
#define	YYFLAG		-32768
#define	YYNTBASE	84

#define YYTRANSLATE(x) ((unsigned)(x) <= 327 ? yytranslate[x] : 136)

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
    21,    23,    27,    31,    35,    36,    42,    43,    49,    50,
    53,    56,    61,    64,    67,    70,    73,    76,    78,    80,
    82,    84,    86,    88,    91,    94,    97,   100,   103,   106,
   109,   113,   117,   120,   123,   125,   128,   130,   132,   134,
   136,   137,   143,   144,   150,   151,   154,   157,   160,   163,
   165,   167,   169,   171,   173,   177,   181,   184,   187,   190,
   193,   195,   198,   200,   203,   205,   207,   211,   213,   215,
   217,   219,   220,   228,   229,   235,   236,   239,   242,   245,
   247,   249,   251,   254,   257,   260,   263,   266,   269,   273,
   277,   280,   283,   284,   292,   293,   299,   300,   303,   306,
   309,   311,   313,   315,   318,   321,   324,   327,   330,   333,
   337,   341,   344,   347,   348,   354,   355,   361,   362,   365,
   368,   371,   374,   377,   380,   383,   388,   393,   400,   404,
   410,   414,   417,   420,   423,   426,   429,   431,   433,   436,
   438,   441,   444,   447,   450,   452,   455,   457,   459,   461,
   463,   465,   471,   478,   484,   491,   497,   504,   505,   509,
   513,   517,   520,   522,   525,   527,   529,   532,   534,   537,
   541,   543,   545,   547,   549,   551,   553,   555,   557,   559,
   561,   563,   565,   567,   569,   571,   574,   577,   581,   585,
   589,   593,   597,   601,   605,   607,   609,   611,   613,   616
};

static const short yyrhs[] = {    -1,
    84,    85,     0,    84,     1,     0,    86,     0,    87,     0,
    95,     0,   104,     0,   109,     0,   114,     0,   122,     0,
   125,     0,    32,   134,    81,     0,    26,   134,    81,     0,
    21,   132,    81,     0,     0,     3,   134,    88,    90,    81,
     0,     0,     3,    70,    89,    90,    81,     0,     0,    90,
    91,     0,     7,    70,     0,     9,   128,     6,    70,     0,
     9,   128,     0,    27,   128,     0,     5,    92,     0,    19,
    92,     0,    20,   131,     0,    10,     0,    12,     0,    48,
     0,    49,     0,    24,     0,    40,     0,    16,   100,     0,
    35,   119,     0,    15,   119,     0,    38,   101,     0,    31,
   133,     0,    18,   133,     0,    37,   135,     0,    37,     8,
   135,     0,    37,     6,   135,     0,    13,   134,     0,    51,
   126,     0,    93,     0,    92,    93,     0,    94,     0,    70,
     0,    45,     0,    23,     0,     0,     4,   134,    96,    98,
    81,     0,     0,     4,    70,    97,    98,    81,     0,     0,
    98,    99,     0,     7,    70,     0,    65,    94,     0,    13,
   134,     0,    11,     0,    28,     0,    29,     0,    54,     0,
    30,     0,    30,    53,   100,     0,    30,    46,   119,     0,
    16,   100,     0,    35,   119,     0,    15,   119,     0,    18,
   133,     0,    40,     0,    51,   126,     0,   102,     0,   100,
   102,     0,   100,     0,    43,     0,    43,    44,   100,     0,
   103,     0,    70,     0,    45,     0,    23,     0,     0,     5,
    94,     8,    94,   105,   107,    81,     0,     0,     5,    70,
   106,   107,    81,     0,     0,   107,   108,     0,     9,   128,
     0,    20,   131,     0,    10,     0,    11,     0,    49,     0,
    16,   100,     0,    35,   119,     0,    15,   119,     0,    38,
   101,     0,    31,   133,     0,    37,   135,     0,    37,     8,
   135,     0,    37,     6,   135,     0,     7,    70,     0,    51,
   126,     0,     0,    19,    94,     8,    94,   110,   112,    81,
     0,     0,    19,    70,   111,   112,    81,     0,     0,   112,
   113,     0,    20,   130,     0,    20,   131,     0,    10,     0,
    11,     0,    49,     0,    16,   100,     0,    35,   119,     0,
    15,   119,     0,    38,   101,     0,    31,   133,     0,    37,
   135,     0,    37,     8,   135,     0,    37,     6,   135,     0,
     7,    70,     0,    51,   126,     0,     0,    14,   134,   115,
   117,    81,     0,     0,    14,    70,   116,   117,    81,     0,
     0,   117,   118,     0,     7,    70,     0,    15,   119,     0,
    16,   100,     0,    41,   100,     0,    17,   100,     0,    42,
   101,     0,    42,   101,    46,   119,     0,    42,   101,    65,
    94,     0,    42,   101,    65,    94,    46,   119,     0,    42,
    65,    94,     0,    42,    65,    94,    46,   119,     0,    42,
    46,   119,     0,    33,   100,     0,    25,    94,     0,    36,
   121,     0,    65,    94,     0,    65,    22,     0,    54,     0,
    34,     0,    18,   133,     0,    40,     0,    37,   135,     0,
    37,    50,     0,    13,   134,     0,    51,   126,     0,   120,
     0,   119,   120,     0,   121,     0,    70,     0,    45,     0,
    23,     0,   123,     0,    70,    72,   132,   124,    81,     0,
    70,    70,    72,   132,   124,    81,     0,    70,    72,    69,
   124,    81,     0,    70,    70,    72,    69,   124,    81,     0,
    70,    72,    39,   124,    81,     0,    70,    70,    72,    39,
   124,    81,     0,     0,    65,    51,    70,     0,    51,    70,
    81,     0,    52,    70,    81,     0,    52,    81,     0,   127,
     0,   126,   127,     0,    70,     0,   129,     0,   128,   129,
     0,   130,     0,   130,   133,     0,   130,    47,   133,     0,
    55,     0,    56,     0,    57,     0,    58,     0,    59,     0,
    60,     0,    61,     0,    62,     0,    65,     0,    66,     0,
    63,     0,    64,     0,    67,     0,    68,     0,    71,     0,
    73,   132,     0,    74,   132,     0,   132,    73,   132,     0,
   132,    74,   132,     0,   132,    75,   132,     0,   132,    76,
   132,     0,   132,    80,   132,     0,   132,    77,   132,     0,
    82,   132,    83,     0,   132,     0,    69,     0,    71,     0,
   134,     0,   134,   133,     0,   134,    47,   133,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   107,   108,   109,   112,   113,   114,   115,   116,   117,   118,
   119,   126,   130,   136,   150,   160,   253,   261,   267,   268,
   271,   278,   297,   312,   325,   340,   355,   359,   363,   367,
   371,   375,   379,   383,   387,   391,   395,   401,   405,   409,
   414,   419,   424,   428,   431,   432,   435,   443,   447,   454,
   467,   475,   484,   492,   498,   499,   502,   509,   513,   517,
   521,   526,   530,   534,   538,   542,   546,   550,   554,   558,
   562,   566,   569,   570,   573,   574,   575,   578,   586,   590,
   597,   610,   618,   623,   631,   637,   638,   641,   646,   650,
   654,   658,   662,   666,   670,   674,   680,   684,   689,   694,
   699,   706,   713,   721,   726,   734,   740,   741,   744,   748,
   752,   756,   760,   764,   768,   772,   776,   782,   786,   791,
   796,   801,   808,   815,   822,   833,   841,   847,   848,   851,
   858,   862,   866,   870,   874,   880,   887,   894,   902,   906,
   911,   915,   919,   923,   927,   931,   935,   939,   943,   947,
   951,   956,   960,   964,   967,   968,   971,   979,   983,   990,
  1003,  1011,  1015,  1020,  1024,  1029,  1033,  1040,  1041,  1052,
  1056,  1060,  1066,  1067,  1070,  1081,  1082,  1085,  1091,  1100,
  1112,  1113,  1114,  1115,  1116,  1117,  1118,  1119,  1122,  1123,
  1124,  1125,  1132,  1133,  1134,  1135,  1136,  1137,  1138,  1139,
  1140,  1141,  1142,  1143,  1146,  1149,  1150,  1153,  1158,  1165
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ROOM","ITEM",
"LINK","FROM","TAG","TO","DIR","ONEWAY","HIDDEN","NODROP","NOTE","TASK","AFTER",
"NEED","GET","SCORE","JOIN","GO","REQUIRE","ANY","LAST","START","GOTO","MAP",
"EXIT","GIVEN","LOST","KEEP","LENGTH","TITLE","LOSE","SAFE","BEFORE","FOLLOW",
"CMD","LEAVE","UNDEF","FINISH","GIVE","DROP","ALL","EXCEPT","IT","UNTIL","TIMES",
"NOLINK","NOPATH","NONE","STYLE","ENDSTYLE","WITH","IGNORE","NORTH","EAST","SOUTH",
"WEST","NORTHEAST","NORTHWEST","SOUTHEAST","SOUTHWEST","UP","DOWN","IN","OUT",
"INTEGER","REAL","STRING","ID","VAR","'='","'+'","'-'","'*'","'/'","'%'","PLUS",
"MINUS","'^'","';'","'('","')'","stmt_list","stmt","ctrl_stmt","room_stmt","@1",
"@2","room_attrs","room_attr","room_list","room_elt","room","item_stmt","@3",
"@4","item_attrs","item_attr","item_list","item_list_all","item_elt","item",
"link_stmt","@5","@6","link_attrs","link_attr","join_stmt","@7","@8","join_attrs",
"join_attr","task_stmt","@9","@10","task_attrs","task_attr","task_list","task_elt",
"task","vars_stmt","set_var","in_style","style_stmt","style_list","style_elt",
"dir_list","dir_elt","compass","otherdir","exp","integer","string","string_repeat", NULL
};
#endif

static const short yyr1[] = {     0,
    84,    84,    84,    85,    85,    85,    85,    85,    85,    85,
    85,    86,    86,    86,    88,    87,    89,    87,    90,    90,
    91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
    91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
    91,    91,    91,    91,    92,    92,    93,    94,    94,    94,
    96,    95,    97,    95,    98,    98,    99,    99,    99,    99,
    99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
    99,    99,   100,   100,   101,   101,   101,   102,   103,   103,
   103,   105,   104,   106,   104,   107,   107,   108,   108,   108,
   108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
   108,   108,   110,   109,   111,   109,   112,   112,   113,   113,
   113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
   113,   113,   113,   115,   114,   116,   114,   117,   117,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   119,   119,   120,   121,   121,   121,
   122,   123,   123,   123,   123,   123,   123,   124,   124,   125,
   125,   125,   126,   126,   127,   128,   128,   129,   129,   129,
   130,   130,   130,   130,   130,   130,   130,   130,   131,   131,
   131,   131,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   133,   134,   134,   135,   135,   135
};

static const short yyr2[] = {     0,
     0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
     1,     3,     3,     3,     0,     5,     0,     5,     0,     2,
     2,     4,     2,     2,     2,     2,     2,     1,     1,     1,
     1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
     3,     3,     2,     2,     1,     2,     1,     1,     1,     1,
     0,     5,     0,     5,     0,     2,     2,     2,     2,     1,
     1,     1,     1,     1,     3,     3,     2,     2,     2,     2,
     1,     2,     1,     2,     1,     1,     3,     1,     1,     1,
     1,     0,     7,     0,     5,     0,     2,     2,     2,     1,
     1,     1,     2,     2,     2,     2,     2,     2,     3,     3,
     2,     2,     0,     7,     0,     5,     0,     2,     2,     2,
     1,     1,     1,     2,     2,     2,     2,     2,     2,     3,
     3,     2,     2,     0,     5,     0,     5,     0,     2,     2,
     2,     2,     2,     2,     2,     4,     4,     6,     3,     5,
     3,     2,     2,     2,     2,     2,     1,     1,     2,     1,
     2,     2,     2,     2,     1,     2,     1,     1,     1,     1,
     1,     5,     6,     5,     6,     5,     6,     0,     3,     3,
     3,     2,     1,     2,     1,     1,     2,     1,     2,     3,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     2,     2,     3,     3,     3,
     3,     3,     3,     3,     1,     1,     1,     1,     2,     3
};

static const short yydefact[] = {     1,
     0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     2,     4,     5,     6,     7,     8,     9,
    10,   161,    11,   206,    17,   207,    15,    53,    51,    50,
    49,    84,     0,   126,   124,   105,     0,   193,   194,   195,
     0,     0,     0,     0,     0,     0,     0,     0,   172,     0,
     0,    19,    19,    55,    55,    86,     0,   128,   128,   107,
     0,   196,   197,     0,     0,     0,     0,     0,     0,     0,
    14,    13,    12,   170,   171,     0,   168,   168,   168,     0,
     0,     0,     0,     0,    48,    82,     0,     0,     0,   103,
   204,   198,   199,   200,   201,   203,   202,   168,   168,   168,
     0,     0,     0,     0,     0,     0,     0,    28,    29,     0,
     0,     0,     0,     0,     0,    32,     0,     0,     0,     0,
     0,    33,    30,    31,     0,    18,    20,    16,     0,    60,
     0,     0,     0,     0,    61,    62,    64,     0,    71,     0,
    63,     0,    54,    56,    52,     0,     0,    90,    91,     0,
     0,     0,     0,     0,     0,     0,    92,     0,    85,    87,
    86,     0,     0,     0,     0,     0,     0,     0,     0,   148,
     0,     0,   150,     0,     0,     0,   147,     0,   127,   129,
   125,     0,   111,   112,     0,     0,     0,     0,     0,     0,
     0,   113,     0,   106,   108,   107,     0,     0,     0,     0,
   166,   164,   162,    25,    45,    47,    21,   181,   182,   183,
   184,   185,   186,   187,   188,    23,   176,   178,    43,   160,
   159,   158,    36,   155,   157,    81,    80,    79,    34,    73,
    78,   205,    39,    26,   191,   192,   189,   190,    27,    24,
    38,    35,     0,     0,   208,    40,    76,    75,    37,   175,
    44,   173,    57,    59,    69,    67,    70,     0,     0,    68,
    72,    58,   101,    88,    95,    93,    89,    97,    94,     0,
     0,    98,    96,   102,     0,   130,   153,   131,   132,   134,
   149,   143,   142,   144,   152,   151,   133,     0,     0,   135,
   154,   146,   145,   122,   116,   114,   109,   110,   118,   115,
     0,     0,   119,   117,   123,     0,   167,   165,   163,   169,
    46,     0,   177,     0,   179,   156,    74,    42,    41,     0,
   209,     0,   174,    66,    65,   100,    99,    83,   141,   139,
     0,     0,   121,   120,   104,    22,   180,   210,    77,     0,
   136,   137,   140,     0,   138,     0,     0
};

static const short yydefgoto[] = {     1,
    14,    15,    16,    53,    52,    80,   127,   204,   205,   206,
    17,    55,    54,    82,   144,   248,   249,   230,   231,    18,
   161,    56,    84,   160,    19,   196,    60,    89,   195,    20,
    59,    58,    87,   180,   223,   224,   225,    21,    22,   102,
    23,   251,   252,   216,   217,   218,   239,   232,   233,   245,
   246
};

static const short yypact[] = {-32768,
   500,-32768,    76,   150,    -1,   235,    18,   565,   -45,   -45,
   -36,   -62,     0,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    54,    57,-32768,-32768,    54,    74,-32768,-32768,-32768,
   565,   565,   565,   272,     6,    15,    30,    33,-32768,    11,
   509,-32768,-32768,-32768,-32768,-32768,    78,-32768,-32768,-32768,
    78,    55,    55,   129,   565,   565,   565,   565,   565,   565,
-32768,-32768,-32768,-32768,-32768,   532,    38,    38,   159,   238,
   283,   410,   441,   180,-32768,-32768,   326,   368,    69,-32768,
-32768,   191,   191,    55,    55,    55,    55,    38,    38,   159,
    87,    62,    71,    81,    78,    66,   605,-32768,-32768,   -45,
    79,    85,   565,    78,   324,-32768,   605,   565,    79,    22,
    72,-32768,-32768,-32768,    83,-32768,-32768,-32768,    95,-32768,
   -45,    79,    85,   565,-32768,-32768,     2,    79,-32768,    83,
-32768,    78,-32768,-32768,-32768,    97,   605,-32768,-32768,    79,
    85,   324,   565,    79,    23,    72,-32768,    83,-32768,-32768,
-32768,    99,   -45,    79,    85,    85,   565,    78,    85,-32768,
    79,    89,-32768,    85,   327,    83,-32768,    -6,-32768,-32768,
-32768,   101,-32768,-32768,    79,    85,   593,   565,    79,    41,
    72,-32768,    83,-32768,-32768,-32768,    91,    93,   105,   106,
-32768,-32768,-32768,    78,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   123,-32768,   542,-32768,-32768,
-32768,-32768,    79,-32768,-32768,-32768,-32768,-32768,    85,-32768,
-32768,   281,-32768,    78,-32768,-32768,-32768,-32768,-32768,   605,
-32768,    79,   -45,   -45,   555,-32768,   144,    85,-32768,-32768,
    83,-32768,-32768,-32768,    79,    85,-32768,    79,    85,    79,
    83,-32768,-32768,   605,    79,    85,-32768,-32768,    79,   -45,
   -45,-32768,-32768,    83,   478,-32768,-32768,    79,    85,    85,
-32768,-32768,    85,-32768,-32768,-32768,    85,    79,    78,    63,
    83,-32768,-32768,-32768,    79,    85,-32768,-32768,-32768,    79,
   -45,   -45,-32768,-32768,    83,   523,-32768,-32768,-32768,-32768,
-32768,   122,-32768,   565,-32768,-32768,-32768,-32768,-32768,   565,
-32768,    85,-32768,    79,    85,-32768,-32768,-32768,    79,   147,
    79,    78,-32768,-32768,-32768,-32768,-32768,-32768,    85,    79,
    79,   151,    79,    79,    79,   198,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,   155,-32768,    96,  -107,    -5,
-32768,-32768,-32768,   161,-32768,  -108,  -138,  -206,-32768,-32768,
-32768,-32768,    64,-32768,-32768,-32768,-32768,    31,-32768,-32768,
-32768,-32768,   171,-32768,  -118,  -101,    67,-32768,-32768,   181,
-32768,  -125,  -130,   -31,  -205,    50,  -149,   499,  -113,     3,
  -145
};


#define	YYLAST		667


static const short yytable[] = {    33,
   242,    37,   267,   229,   241,    27,    29,    48,    35,   272,
   313,    45,    46,   255,   261,   292,    30,   273,    49,   260,
   257,    30,   317,    24,   256,    26,   286,   243,   270,   244,
   271,   265,   274,    47,   313,   269,   290,   298,    31,   268,
    30,   317,   266,    31,   303,   278,   301,   258,   302,   317,
   291,    86,   304,   281,   259,    90,   279,   280,   313,   317,
   283,   -48,    31,    85,    57,   287,   295,   305,    32,    50,
   300,    51,   317,   317,   299,   182,   317,   296,   183,   184,
   317,    61,    76,   185,   186,   240,    72,    36,   187,   317,
    24,    24,    26,    26,   226,    73,   311,   318,   319,   188,
    30,   220,   101,   189,   315,   190,   191,   226,   331,    24,
    74,    26,   219,    75,   247,   264,   227,   192,   317,   193,
   323,   316,    31,   221,   326,   327,   311,   332,   312,   227,
   323,   321,   317,   254,    70,   207,   262,   200,   285,   324,
   316,   228,   201,   323,    24,    25,    26,    85,   222,   194,
   325,   202,   250,   316,   228,   333,   334,    24,   316,    26,
   323,   203,   282,   316,   253,   277,   263,   316,   276,   329,
   294,   307,   293,   308,   323,   310,   316,   208,   209,   210,
   211,   212,   213,   214,   215,   309,   146,   322,   147,   148,
   149,   336,   340,   316,   150,   151,   344,   347,   316,   152,
   337,    65,    66,    67,    68,    69,   338,    81,    70,   234,
   153,    91,   341,   339,   154,    83,   155,   156,    24,    28,
    26,   343,   316,   101,   275,   345,   306,   316,   157,    88,
   158,    65,    66,    67,    68,    69,   297,   284,    70,   316,
     0,   316,   105,   316,   106,     0,   107,   108,     0,   109,
   110,     0,   111,   112,     0,   113,   114,   115,   103,   104,
   159,   116,     0,     0,   117,    67,    68,    69,   118,     0,
    70,     0,   119,     0,   120,   121,     0,   122,   197,   198,
   199,     0,     0,   330,     0,   123,   124,   105,   125,   106,
     0,   107,   108,     0,   109,   110,     0,   111,   112,     0,
   113,   114,   115,    24,    34,    26,   116,     0,     0,   117,
     0,     0,     0,   118,     0,     0,     0,   119,   126,   120,
   121,     0,   122,     0,     0,     0,   342,     0,     0,     0,
   123,   124,   162,   125,     0,     0,     0,     0,   163,     0,
   164,   165,   166,   167,    65,    66,    67,    68,    69,   226,
   168,    70,    71,    65,    66,    67,    68,    69,   169,   170,
    70,   171,   172,   128,     0,   173,   174,   175,     0,   247,
     0,   227,   288,     0,   162,     0,   176,     0,     0,   177,
   163,     0,   164,   165,   166,   167,   235,   236,   237,   238,
   178,   289,   168,     0,     0,     0,   228,     0,     0,     0,
   169,   170,     0,   171,   172,     0,   179,   173,   174,   175,
     0,     0,     0,     0,     0,     0,   129,     0,   176,     0,
   130,   177,   131,     0,   132,   133,     0,   134,     0,     0,
     0,     0,   178,     0,     0,     0,     0,   135,   136,   137,
     0,     0,     0,     0,   138,     0,     0,   129,   181,   139,
     0,   130,     0,   131,     0,   132,   133,     0,   134,     0,
   140,     0,     0,   141,     0,     0,     0,     0,   135,   136,
   137,     0,     0,     0,   142,   138,     0,     0,     0,     0,
   139,     0,     0,     0,   146,     0,   147,   148,   149,     0,
   143,   140,   150,   151,   141,     0,     0,   152,     0,   346,
     2,     0,     3,     4,     5,   142,    44,     0,   153,     0,
     0,     0,   154,     6,   155,   156,     0,     0,     7,     0,
     8,   145,     0,     0,     0,     9,   157,     0,   158,   182,
     0,    10,   183,   184,     0,     0,     0,   185,   186,    62,
    63,    64,   187,     0,     0,     0,     0,    77,     0,    79,
    11,    12,     0,   188,     0,     0,     0,   189,   328,   190,
   191,     0,     0,    92,    93,    94,    95,    96,    97,    13,
    98,   192,     0,   193,   100,    38,    39,    78,     0,    40,
     0,    41,    42,     0,     0,     0,     0,     0,   314,     0,
    43,     0,     0,     0,     0,     0,     0,     0,    38,    39,
    99,   320,    40,   335,    41,    42,     0,     0,    38,    39,
     0,     0,    40,    43,    41,    42,     0,     0,     0,     0,
     0,    38,    39,    43,     0,    40,     0,    41,    42,     0,
     0,    38,    39,     0,     0,    40,    43,    41,    42,     0,
     0,     0,     0,     0,     0,     0,    43,   208,   209,   210,
   211,   212,   213,   214,   215,   235,   236,   237,   238,   208,
   209,   210,   211,   212,   213,   214,   215
};

static const short yycheck[] = {     5,
   119,     7,   152,   112,   118,     3,     4,    70,     6,   155,
   216,     9,    10,   132,   140,    22,    23,   156,    81,   138,
   134,    23,   229,    69,   133,    71,   172,     6,     6,     8,
     8,   150,   158,    70,   240,   154,   175,   187,    45,   153,
    23,   248,   151,    45,   190,   164,     6,    46,     8,   256,
   176,    57,   191,   167,    53,    61,   165,   166,   264,   266,
   169,     8,    45,    70,     8,   174,   185,   193,    70,    70,
   189,    72,   279,   280,   188,     7,   283,   186,    10,    11,
   287,     8,    72,    15,    16,   117,    81,    70,    20,   296,
    69,    69,    71,    71,    23,    81,   204,   243,   244,    31,
    23,    23,    65,    35,   218,    37,    38,    23,    46,    69,
    81,    71,   110,    81,    43,   147,    45,    49,   325,    51,
   251,   223,    45,    45,   270,   271,   234,    65,     6,    45,
   261,   245,   339,   131,    80,    70,   142,    51,    50,   258,
   242,    70,    81,   274,    69,    70,    71,    70,    70,    81,
   259,    81,    70,   255,    70,   301,   302,    69,   260,    71,
   291,    81,   168,   265,    70,   163,    70,   269,    70,   288,
    70,    81,   178,    81,   305,    70,   278,    55,    56,    57,
    58,    59,    60,    61,    62,    81,     7,    44,     9,    10,
    11,    70,    46,   295,    15,    16,    46,     0,   300,    20,
   314,    73,    74,    75,    76,    77,   320,    53,    80,   114,
    31,    83,   331,   322,    35,    55,    37,    38,    69,    70,
    71,   340,   324,    65,   161,   344,   196,   329,    49,    59,
    51,    73,    74,    75,    76,    77,   187,   171,    80,   341,
    -1,   343,     5,   345,     7,    -1,     9,    10,    -1,    12,
    13,    -1,    15,    16,    -1,    18,    19,    20,    78,    79,
    81,    24,    -1,    -1,    27,    75,    76,    77,    31,    -1,
    80,    -1,    35,    -1,    37,    38,    -1,    40,    98,    99,
   100,    -1,    -1,   289,    -1,    48,    49,     5,    51,     7,
    -1,     9,    10,    -1,    12,    13,    -1,    15,    16,    -1,
    18,    19,    20,    69,    70,    71,    24,    -1,    -1,    27,
    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    81,    37,
    38,    -1,    40,    -1,    -1,    -1,   332,    -1,    -1,    -1,
    48,    49,     7,    51,    -1,    -1,    -1,    -1,    13,    -1,
    15,    16,    17,    18,    73,    74,    75,    76,    77,    23,
    25,    80,    81,    73,    74,    75,    76,    77,    33,    34,
    80,    36,    37,    81,    -1,    40,    41,    42,    -1,    43,
    -1,    45,    46,    -1,     7,    -1,    51,    -1,    -1,    54,
    13,    -1,    15,    16,    17,    18,    63,    64,    65,    66,
    65,    65,    25,    -1,    -1,    -1,    70,    -1,    -1,    -1,
    33,    34,    -1,    36,    37,    -1,    81,    40,    41,    42,
    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    51,    -1,
    11,    54,    13,    -1,    15,    16,    -1,    18,    -1,    -1,
    -1,    -1,    65,    -1,    -1,    -1,    -1,    28,    29,    30,
    -1,    -1,    -1,    -1,    35,    -1,    -1,     7,    81,    40,
    -1,    11,    -1,    13,    -1,    15,    16,    -1,    18,    -1,
    51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    28,    29,
    30,    -1,    -1,    -1,    65,    35,    -1,    -1,    -1,    -1,
    40,    -1,    -1,    -1,     7,    -1,     9,    10,    11,    -1,
    81,    51,    15,    16,    54,    -1,    -1,    20,    -1,     0,
     1,    -1,     3,     4,     5,    65,     8,    -1,    31,    -1,
    -1,    -1,    35,    14,    37,    38,    -1,    -1,    19,    -1,
    21,    81,    -1,    -1,    -1,    26,    49,    -1,    51,     7,
    -1,    32,    10,    11,    -1,    -1,    -1,    15,    16,    41,
    42,    43,    20,    -1,    -1,    -1,    -1,    39,    -1,    51,
    51,    52,    -1,    31,    -1,    -1,    -1,    35,    81,    37,
    38,    -1,    -1,    65,    66,    67,    68,    69,    70,    70,
    39,    49,    -1,    51,    76,    67,    68,    69,    -1,    71,
    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    47,    -1,
    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
    69,    47,    71,    81,    73,    74,    -1,    -1,    67,    68,
    -1,    -1,    71,    82,    73,    74,    -1,    -1,    -1,    -1,
    -1,    67,    68,    82,    -1,    71,    -1,    73,    74,    -1,
    -1,    67,    68,    -1,    -1,    71,    82,    73,    74,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    82,    55,    56,    57,
    58,    59,    60,    61,    62,    63,    64,    65,    66,    55,
    56,    57,    58,    59,    60,    61,    62
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
                        vh_istore(link, "NODROP",
                                  vh_iget(curobj, "NODROP"));
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
                    vh_istore(curobj, "NODROP", 1);
		;
    break;}
case 30:
#line 368 "ifm-parse.y"
{
                    vh_istore(curobj, "NOLINK", 1);
		;
    break;}
case 31:
#line 372 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 32:
#line 376 "ifm-parse.y"
{
                    startroom = curobj;
		;
    break;}
case 33:
#line 380 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 34:
#line 384 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(NEED), curitems);
                ;
    break;}
case 35:
#line 388 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		;
    break;}
case 36:
#line 392 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		;
    break;}
case 37:
#line 396 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                ;
    break;}
case 38:
#line 402 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 39:
#line 406 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 40:
#line 410 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 41:
#line 415 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 42:
#line 420 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 43:
#line 425 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
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
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 148:
#line 940 "ifm-parse.y"
{
                    vh_istore(curobj, "SAFE", 1);
                ;
    break;}
case 149:
#line 944 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 150:
#line 948 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 151:
#line 952 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", yyvsp[0].sval);
                ;
    break;}
case 152:
#line 957 "ifm-parse.y"
{
                    add_attr(curobj, "CMD", NULL);
                ;
    break;}
case 153:
#line 961 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 157:
#line 972 "ifm-parse.y"
{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, yyvsp[0].vval);
		;
    break;}
case 158:
#line 980 "ifm-parse.y"
{
                    yyval.vval = ittask = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 159:
#line 984 "ifm-parse.y"
{
                    if (ittask == NULL)
                        err("no task referred to by `it'");
                    else
                        yyval.vval = vs_copy(ittask);
                ;
    break;}
case 160:
#line 991 "ifm-parse.y"
{
                    if (lasttask == NULL)
                        err("no task referred to by `last'");
                    else
                        yyval.vval = ittask = vs_pcreate(lasttask);
                ;
    break;}
case 161:
#line 1004 "ifm-parse.y"
{
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                ;
    break;}
case 162:
#line 1012 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                ;
    break;}
case 163:
#line 1016 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 164:
#line 1021 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                ;
    break;}
case 165:
#line 1025 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 166:
#line 1030 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, NULL);
                ;
    break;}
case 167:
#line 1034 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, NULL);
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 169:
#line 1042 "ifm-parse.y"
{
                    push_style(yyvsp[0].sval);
                    instyle++;
                ;
    break;}
case 170:
#line 1053 "ifm-parse.y"
{
                    push_style(yyvsp[-1].sval);
                ;
    break;}
case 171:
#line 1057 "ifm-parse.y"
{
                    pop_style(yyvsp[-1].sval);
                ;
    break;}
case 172:
#line 1061 "ifm-parse.y"
{
                    pop_style(NULL);
                ;
    break;}
case 175:
#line 1071 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", yyvsp[0].sval);
                    ref_style(yyvsp[0].sval);
                ;
    break;}
case 178:
#line 1086 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, yyvsp[0].ival);
		;
    break;}
case 179:
#line 1092 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-1].ival);
                ;
    break;}
case 180:
#line 1101 "ifm-parse.y"
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
case 181:
#line 1112 "ifm-parse.y"
{ yyval.ival = D_NORTH;	    ;
    break;}
case 182:
#line 1113 "ifm-parse.y"
{ yyval.ival = D_EAST;	    ;
    break;}
case 183:
#line 1114 "ifm-parse.y"
{ yyval.ival = D_SOUTH;	    ;
    break;}
case 184:
#line 1115 "ifm-parse.y"
{ yyval.ival = D_WEST;	    ;
    break;}
case 185:
#line 1116 "ifm-parse.y"
{ yyval.ival = D_NORTHEAST; ;
    break;}
case 186:
#line 1117 "ifm-parse.y"
{ yyval.ival = D_NORTHWEST; ;
    break;}
case 187:
#line 1118 "ifm-parse.y"
{ yyval.ival = D_SOUTHEAST; ;
    break;}
case 188:
#line 1119 "ifm-parse.y"
{ yyval.ival = D_SOUTHWEST; ;
    break;}
case 189:
#line 1122 "ifm-parse.y"
{ yyval.ival = D_IN;   ;
    break;}
case 190:
#line 1123 "ifm-parse.y"
{ yyval.ival = D_OUT;  ;
    break;}
case 191:
#line 1124 "ifm-parse.y"
{ yyval.ival = D_UP;   ;
    break;}
case 192:
#line 1125 "ifm-parse.y"
{ yyval.ival = D_DOWN; ;
    break;}
case 193:
#line 1132 "ifm-parse.y"
{ yyval.dval = yyvsp[0].ival; ;
    break;}
case 194:
#line 1133 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 195:
#line 1134 "ifm-parse.y"
{ yyval.dval = var_real(yyvsp[0].sval); ;
    break;}
case 196:
#line 1135 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 197:
#line 1136 "ifm-parse.y"
{ yyval.dval = -yyvsp[0].dval; ;
    break;}
case 198:
#line 1137 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval + yyvsp[0].dval; ;
    break;}
case 199:
#line 1138 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval - yyvsp[0].dval; ;
    break;}
case 200:
#line 1139 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval * yyvsp[0].dval; ;
    break;}
case 201:
#line 1140 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval / yyvsp[0].dval; ;
    break;}
case 202:
#line 1141 "ifm-parse.y"
{ yyval.dval = pow(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 203:
#line 1142 "ifm-parse.y"
{ yyval.dval = fmod(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 204:
#line 1143 "ifm-parse.y"
{ yyval.dval = yyvsp[-1].dval; ;
    break;}
case 205:
#line 1146 "ifm-parse.y"
{ yyval.ival = (int) yyvsp[0].dval; ;
    break;}
case 206:
#line 1149 "ifm-parse.y"
{ yyval.sval = yyvsp[0].sval; ;
    break;}
case 207:
#line 1150 "ifm-parse.y"
{ yyval.sval = var_string(yyvsp[0].sval); ;
    break;}
case 208:
#line 1154 "ifm-parse.y"
{
                    yyval.sval = yyvsp[0].sval;
                    repeat = 1;
                ;
    break;}
case 209:
#line 1159 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-1].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                ;
    break;}
case 210:
#line 1166 "ifm-parse.y"
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
#line 1175 "ifm-parse.y"

