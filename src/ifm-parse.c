
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
#define	DO	309
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

#define SET_LIST(object, attr, list) {                                  \
        vlist *l = vh_pget(object, attr);                               \
        if (l == NULL) {                                                \
            vh_pstore(object, attr, list);                              \
            list = NULL;                                                \
        } else {                                                        \
            vl_append(l, list);                                         \
            vl_destroy(list);                                           \
            list = NULL;                                                \
        }                                                               \
}

#define ATTR(name) \
        (implicit ? "LINK_" #name : #name)

#define RESET_IT                                                        \
        RESET_VAR(itroom);                                              \
        RESET_VAR(ititem);                                              \
        RESET_VAR(ittask)

#define RESET_VAR(var) if (var != NULL) { vs_destroy(var); var = NULL; }

#define WARN_IGNORED(attr)                                              \
        warn("attribute '%s' ignored -- no implicit link", #attr)

#define CHANGE_ERROR(attr)                                              \
        err("can't modify '%s' attribute", #attr)

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

#line 71 "ifm-parse.y"
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



#define	YYFINAL		349
#define	YYFLAG		-32768
#define	YYNTBASE	85

#define YYTRANSLATE(x) ((unsigned)(x) <= 328 ? yytranslate[x] : 137)

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
   368,   371,   374,   377,   380,   383,   386,   391,   396,   403,
   407,   413,   417,   420,   423,   426,   429,   432,   434,   436,
   439,   441,   444,   447,   450,   453,   455,   458,   460,   462,
   464,   466,   468,   474,   481,   487,   494,   500,   507,   508,
   512,   516,   520,   523,   525,   528,   530,   532,   535,   537,
   540,   544,   546,   548,   550,   552,   554,   556,   558,   560,
   562,   564,   566,   568,   570,   572,   574,   577,   580,   584,
   588,   592,   596,   600,   604,   608,   610,   612,   614,   616,
   619
};

static const short yyrhs[] = {    -1,
    85,    86,     0,    85,     1,     0,    87,     0,    88,     0,
    96,     0,   105,     0,   110,     0,   115,     0,   123,     0,
   126,     0,    32,   135,    82,     0,    26,   135,    82,     0,
    21,   133,    82,     0,     0,     3,   135,    89,    91,    82,
     0,     0,     3,    71,    90,    91,    82,     0,     0,    91,
    92,     0,     7,    71,     0,     9,   129,     6,    71,     0,
     9,   129,     0,    27,   129,     0,     5,    93,     0,    19,
    93,     0,    20,   132,     0,    10,     0,    12,     0,    48,
     0,    49,     0,    24,     0,    40,     0,    16,   101,     0,
    35,   120,     0,    15,   120,     0,    38,   102,     0,    31,
   134,     0,    18,   134,     0,    37,   136,     0,    37,     8,
   136,     0,    37,     6,   136,     0,    13,   135,     0,    51,
   127,     0,    94,     0,    93,    94,     0,    95,     0,    71,
     0,    45,     0,    23,     0,     0,     4,   135,    97,    99,
    82,     0,     0,     4,    71,    98,    99,    82,     0,     0,
    99,   100,     0,     7,    71,     0,    66,    95,     0,    13,
   135,     0,    11,     0,    28,     0,    29,     0,    54,     0,
    30,     0,    30,    53,   101,     0,    30,    46,   120,     0,
    16,   101,     0,    35,   120,     0,    15,   120,     0,    18,
   134,     0,    40,     0,    51,   127,     0,   103,     0,   101,
   103,     0,   101,     0,    43,     0,    43,    44,   101,     0,
   104,     0,    71,     0,    45,     0,    23,     0,     0,     5,
    95,     8,    95,   106,   108,    82,     0,     0,     5,    71,
   107,   108,    82,     0,     0,   108,   109,     0,     9,   129,
     0,    20,   132,     0,    10,     0,    11,     0,    49,     0,
    16,   101,     0,    35,   120,     0,    15,   120,     0,    38,
   102,     0,    31,   134,     0,    37,   136,     0,    37,     8,
   136,     0,    37,     6,   136,     0,     7,    71,     0,    51,
   127,     0,     0,    19,    95,     8,    95,   111,   113,    82,
     0,     0,    19,    71,   112,   113,    82,     0,     0,   113,
   114,     0,    20,   131,     0,    20,   132,     0,    10,     0,
    11,     0,    49,     0,    16,   101,     0,    35,   120,     0,
    15,   120,     0,    38,   102,     0,    31,   134,     0,    37,
   136,     0,    37,     8,   136,     0,    37,     6,   136,     0,
     7,    71,     0,    51,   127,     0,     0,    14,   135,   116,
   118,    82,     0,     0,    14,    71,   117,   118,    82,     0,
     0,   118,   119,     0,     7,    71,     0,    15,   120,     0,
    16,   101,     0,    41,   101,     0,    17,   101,     0,    55,
   120,     0,    42,   102,     0,    42,   102,    46,   120,     0,
    42,   102,    66,    95,     0,    42,   102,    66,    95,    46,
   120,     0,    42,    66,    95,     0,    42,    66,    95,    46,
   120,     0,    42,    46,   120,     0,    33,   101,     0,    25,
    95,     0,    36,   122,     0,    66,    95,     0,    66,    22,
     0,    54,     0,    34,     0,    18,   134,     0,    40,     0,
    37,   136,     0,    37,    50,     0,    13,   135,     0,    51,
   127,     0,   121,     0,   120,   121,     0,   122,     0,    71,
     0,    45,     0,    23,     0,   124,     0,    71,    73,   133,
   125,    82,     0,    71,    71,    73,   133,   125,    82,     0,
    71,    73,    70,   125,    82,     0,    71,    71,    73,    70,
   125,    82,     0,    71,    73,    39,   125,    82,     0,    71,
    71,    73,    39,   125,    82,     0,     0,    66,    51,    71,
     0,    51,    71,    82,     0,    52,    71,    82,     0,    52,
    82,     0,   128,     0,   127,   128,     0,    71,     0,   130,
     0,   129,   130,     0,   131,     0,   131,   134,     0,   131,
    47,   134,     0,    56,     0,    57,     0,    58,     0,    59,
     0,    60,     0,    61,     0,    62,     0,    63,     0,    66,
     0,    67,     0,    64,     0,    65,     0,    68,     0,    69,
     0,    72,     0,    74,   133,     0,    75,   133,     0,   133,
    74,   133,     0,   133,    75,   133,     0,   133,    76,   133,
     0,   133,    77,   133,     0,   133,    81,   133,     0,   133,
    78,   133,     0,    83,   133,    84,     0,   133,     0,    70,
     0,    72,     0,   135,     0,   135,   134,     0,   135,    47,
   134,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   110,   111,   112,   115,   116,   117,   118,   119,   120,   121,
   122,   129,   133,   139,   153,   163,   256,   264,   270,   271,
   274,   281,   300,   315,   328,   343,   358,   362,   366,   370,
   374,   378,   382,   386,   390,   394,   398,   404,   408,   412,
   417,   422,   427,   431,   434,   435,   438,   446,   451,   458,
   473,   481,   490,   498,   504,   505,   508,   515,   519,   523,
   527,   532,   536,   540,   544,   548,   552,   556,   560,   564,
   568,   572,   575,   576,   579,   580,   581,   584,   592,   597,
   604,   619,   627,   632,   640,   646,   647,   650,   655,   659,
   663,   667,   671,   675,   679,   683,   689,   693,   698,   703,
   708,   715,   722,   730,   735,   743,   749,   750,   753,   757,
   761,   765,   769,   773,   777,   781,   785,   791,   795,   800,
   805,   810,   817,   824,   831,   842,   850,   856,   857,   860,
   867,   871,   875,   879,   883,   887,   893,   900,   907,   915,
   919,   924,   928,   932,   936,   940,   944,   948,   952,   956,
   960,   964,   969,   973,   977,   980,   981,   984,   992,   997,
  1004,  1019,  1027,  1031,  1036,  1040,  1045,  1049,  1056,  1057,
  1068,  1072,  1076,  1082,  1083,  1086,  1097,  1098,  1101,  1107,
  1116,  1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1138,
  1139,  1140,  1141,  1148,  1149,  1150,  1151,  1152,  1153,  1154,
  1155,  1156,  1157,  1158,  1159,  1162,  1165,  1166,  1169,  1174,
  1181
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ROOM","ITEM",
"LINK","FROM","TAG","TO","DIR","ONEWAY","HIDDEN","NODROP","NOTE","TASK","AFTER",
"NEED","GET","SCORE","JOIN","GO","REQUIRE","ANY","LAST","START","GOTO","MAP",
"EXIT","GIVEN","LOST","KEEP","LENGTH","TITLE","LOSE","SAFE","BEFORE","FOLLOW",
"CMD","LEAVE","UNDEF","FINISH","GIVE","DROP","ALL","EXCEPT","IT","UNTIL","TIMES",
"NOLINK","NOPATH","NONE","STYLE","ENDSTYLE","WITH","IGNORE","DO","NORTH","EAST",
"SOUTH","WEST","NORTHEAST","NORTHWEST","SOUTHEAST","SOUTHWEST","UP","DOWN","IN",
"OUT","INTEGER","REAL","STRING","ID","VAR","'='","'+'","'-'","'*'","'/'","'%'",
"PLUS","MINUS","'^'","';'","'('","')'","stmt_list","stmt","ctrl_stmt","room_stmt",
"@1","@2","room_attrs","room_attr","room_list","room_elt","room","item_stmt",
"@3","@4","item_attrs","item_attr","item_list","item_list_all","item_elt","item",
"link_stmt","@5","@6","link_attrs","link_attr","join_stmt","@7","@8","join_attrs",
"join_attr","task_stmt","@9","@10","task_attrs","task_attr","task_list","task_elt",
"task","vars_stmt","set_var","in_style","style_stmt","style_list","style_elt",
"dir_list","dir_elt","compass","otherdir","exp","integer","string","string_repeat", NULL
};
#endif

static const short yyr1[] = {     0,
    85,    85,    85,    86,    86,    86,    86,    86,    86,    86,
    86,    87,    87,    87,    89,    88,    90,    88,    91,    91,
    92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
    92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
    92,    92,    92,    92,    93,    93,    94,    95,    95,    95,
    97,    96,    98,    96,    99,    99,   100,   100,   100,   100,
   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
   100,   100,   101,   101,   102,   102,   102,   103,   104,   104,
   104,   106,   105,   107,   105,   108,   108,   109,   109,   109,
   109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
   109,   109,   111,   110,   112,   110,   113,   113,   114,   114,
   114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
   114,   114,   114,   116,   115,   117,   115,   118,   118,   119,
   119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
   119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
   119,   119,   119,   119,   119,   120,   120,   121,   122,   122,
   122,   123,   124,   124,   124,   124,   124,   124,   125,   125,
   126,   126,   126,   127,   127,   128,   129,   129,   130,   130,
   130,   131,   131,   131,   131,   131,   131,   131,   131,   132,
   132,   132,   132,   133,   133,   133,   133,   133,   133,   133,
   133,   133,   133,   133,   133,   134,   135,   135,   136,   136,
   136
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
     2,     2,     2,     2,     2,     2,     4,     4,     6,     3,
     5,     3,     2,     2,     2,     2,     2,     1,     1,     2,
     1,     2,     2,     2,     2,     1,     2,     1,     1,     1,
     1,     1,     5,     6,     5,     6,     5,     6,     0,     3,
     3,     3,     2,     1,     2,     1,     1,     2,     1,     2,
     3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     2,     2,     3,     3,
     3,     3,     3,     3,     3,     1,     1,     1,     1,     2,
     3
};

static const short yydefact[] = {     1,
     0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     2,     4,     5,     6,     7,     8,     9,
    10,   162,    11,   207,    17,   208,    15,    53,    51,    50,
    49,    84,     0,   126,   124,   105,     0,   194,   195,   196,
     0,     0,     0,     0,     0,     0,     0,     0,   173,     0,
     0,    19,    19,    55,    55,    86,     0,   128,   128,   107,
     0,   197,   198,     0,     0,     0,     0,     0,     0,     0,
    14,    13,    12,   171,   172,     0,   169,   169,   169,     0,
     0,     0,     0,     0,    48,    82,     0,     0,     0,   103,
   205,   199,   200,   201,   202,   204,   203,   169,   169,   169,
     0,     0,     0,     0,     0,     0,     0,    28,    29,     0,
     0,     0,     0,     0,     0,    32,     0,     0,     0,     0,
     0,    33,    30,    31,     0,    18,    20,    16,     0,    60,
     0,     0,     0,     0,    61,    62,    64,     0,    71,     0,
    63,     0,    54,    56,    52,     0,     0,    90,    91,     0,
     0,     0,     0,     0,     0,     0,    92,     0,    85,    87,
    86,     0,     0,     0,     0,     0,     0,     0,     0,   149,
     0,     0,   151,     0,     0,     0,   148,     0,     0,   127,
   129,   125,     0,   111,   112,     0,     0,     0,     0,     0,
     0,     0,   113,     0,   106,   108,   107,     0,     0,     0,
     0,   167,   165,   163,    25,    45,    47,    21,   182,   183,
   184,   185,   186,   187,   188,   189,    23,   177,   179,    43,
   161,   160,   159,    36,   156,   158,    81,    80,    79,    34,
    73,    78,   206,    39,    26,   192,   193,   190,   191,    27,
    24,    38,    35,     0,     0,   209,    40,    76,    75,    37,
   176,    44,   174,    57,    59,    69,    67,    70,     0,     0,
    68,    72,    58,   101,    88,    95,    93,    89,    97,    94,
     0,     0,    98,    96,   102,     0,   130,   154,   131,   132,
   134,   150,   144,   143,   145,   153,   152,   133,     0,     0,
   136,   155,   135,   147,   146,   122,   116,   114,   109,   110,
   118,   115,     0,     0,   119,   117,   123,     0,   168,   166,
   164,   170,    46,     0,   178,     0,   180,   157,    74,    42,
    41,     0,   210,     0,   175,    66,    65,   100,    99,    83,
   142,   140,     0,     0,   121,   120,   104,    22,   181,   211,
    77,     0,   137,   138,   141,     0,   139,     0,     0
};

static const short yydefgoto[] = {     1,
    14,    15,    16,    53,    52,    80,   127,   205,   206,   207,
    17,    55,    54,    82,   144,   249,   250,   231,   232,    18,
   161,    56,    84,   160,    19,   197,    60,    89,   196,    20,
    59,    58,    87,   181,   224,   225,   226,    21,    22,   102,
    23,   252,   253,   217,   218,   219,   240,   233,   234,   246,
   247
};

static const short yypact[] = {-32768,
   191,-32768,   136,   219,    -1,   226,    84,   252,    76,    76,
   -61,    39,    38,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    16,    37,-32768,-32768,    16,    42,-32768,-32768,-32768,
   252,   252,   252,   540,   -27,   -13,     1,    41,-32768,    13,
   498,-32768,-32768,-32768,-32768,-32768,   109,-32768,-32768,-32768,
   109,    -4,    -4,   398,   252,   252,   252,   252,   252,   252,
-32768,-32768,-32768,-32768,-32768,   518,    49,    49,   294,   220,
   268,   385,   417,   449,-32768,-32768,   297,   340,   513,-32768,
-32768,   172,   172,    -4,    -4,    -4,    -4,    49,    49,   294,
    68,    44,    57,    60,   109,    78,   572,-32768,-32768,    76,
   130,   142,   252,   109,   154,-32768,   572,   252,   130,    10,
   113,-32768,-32768,-32768,    86,-32768,-32768,-32768,    96,-32768,
    76,   130,   142,   252,-32768,-32768,    32,   130,-32768,    86,
-32768,   109,-32768,-32768,-32768,    97,   572,-32768,-32768,   130,
   142,   154,   252,   130,    25,   113,-32768,    86,-32768,-32768,
-32768,   101,    76,   130,   142,   142,   252,   109,   142,-32768,
   130,    46,-32768,   142,    79,    86,-32768,   130,     4,-32768,
-32768,-32768,   102,-32768,-32768,   130,   142,   546,   252,   130,
    33,   113,-32768,    86,-32768,-32768,-32768,    88,    94,   100,
   108,-32768,-32768,-32768,   109,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   447,-32768,   336,-32768,
-32768,-32768,-32768,   130,-32768,-32768,-32768,-32768,-32768,   142,
-32768,-32768,   189,-32768,   109,-32768,-32768,-32768,-32768,-32768,
   572,-32768,   130,    76,    76,   466,-32768,   144,   142,-32768,
-32768,    86,-32768,-32768,-32768,   130,   142,-32768,   130,   142,
   130,    86,-32768,-32768,   572,   130,   142,-32768,-32768,   130,
    76,    76,-32768,-32768,    86,   481,-32768,-32768,   130,   142,
   142,-32768,-32768,   142,-32768,-32768,-32768,   142,   130,   109,
   -43,    86,   130,-32768,-32768,-32768,   130,   142,-32768,-32768,
-32768,   130,    76,    76,-32768,-32768,    86,   545,-32768,-32768,
-32768,-32768,-32768,   115,-32768,   252,-32768,-32768,-32768,-32768,
-32768,   252,-32768,   142,-32768,   130,   142,-32768,-32768,-32768,
   130,   143,   130,   109,-32768,-32768,-32768,-32768,-32768,-32768,
   142,   130,   130,   147,   130,   130,   130,   200,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,   149,-32768,   112,  -197,    -5,
-32768,-32768,-32768,   156,-32768,  -108,  -141,  -137,-32768,-32768,
-32768,-32768,    53,-32768,-32768,-32768,-32768,    34,-32768,-32768,
-32768,-32768,   163,-32768,  -118,  -162,    63,-32768,-32768,    99,
-32768,  -123,  -233,   -80,  -103,    58,  -104,    22,  -113,     3,
  -144
};


#define	YYLAST		635


static const short yytable[] = {    33,
   243,    37,   333,   230,   242,    27,    29,   313,    35,    47,
   273,    45,    46,   256,   274,   244,   262,   245,   325,   261,
   258,    30,   334,   -48,   257,   294,    30,   287,   325,    44,
   271,   266,   272,   291,   275,   270,   241,   313,   303,   269,
   304,   325,   267,    31,    57,   279,   305,   268,    31,    61,
   306,    86,   292,   282,    72,    90,   280,   281,   325,   293,
   284,   318,    62,    63,    64,   288,   265,   297,    73,    32,
   307,   302,    79,   325,    85,   301,    70,   259,   298,    24,
   318,    26,    74,   300,   260,    76,    92,    93,    94,    95,
    96,    97,   319,   318,    24,   286,    26,   100,   318,   320,
   321,   227,    24,   318,    26,   317,    30,   318,    50,    48,
    51,   319,   220,   315,   101,    24,   318,    26,   201,   319,
    49,   248,    75,   228,   289,   202,   328,   329,    31,   319,
   318,    30,   323,   255,   318,   227,   263,   315,   203,   318,
   326,   204,   319,   319,   290,    24,   319,    26,   208,   229,
   319,   327,   221,    31,    36,   248,   251,   228,   335,   336,
   319,   315,   283,   318,   227,   278,   254,   264,   318,   309,
   331,   277,   296,   295,   222,   310,   103,   104,   312,    85,
   318,   311,   318,   229,   318,   338,   228,   324,   342,   319,
   348,     2,   346,     3,     4,     5,   198,   199,   200,   349,
   223,    81,   339,   319,     6,    24,    25,    26,   340,     7,
    83,     8,   229,   276,   343,   341,     9,   236,   237,   238,
   239,    88,    10,   345,   105,   235,   106,   347,   107,   108,
   308,   109,   110,   285,   111,   112,     0,   113,   114,   115,
     0,    11,    12,   116,     0,   299,   117,    67,    68,    69,
   118,     0,    70,     0,   119,     0,   120,   121,     0,   122,
     0,    13,    65,    66,    67,    68,    69,   123,   124,    70,
   125,     0,   105,     0,   106,     0,   107,   108,     0,   109,
   110,     0,   111,   112,   332,   113,   114,   115,    24,    28,
    26,   116,     0,     0,   117,    24,    34,    26,   118,     0,
     0,   126,   119,   162,   120,   121,     0,   122,     0,   163,
     0,   164,   165,   166,   167,   123,   124,     0,   125,    38,
    39,   168,     0,    40,     0,    41,    42,     0,   344,   169,
   170,     0,   171,   172,    43,     0,   173,   174,   175,     0,
     0,     0,     0,     0,     0,     0,   162,   176,     0,   128,
   177,   178,   163,     0,   164,   165,   166,   167,     0,   101,
     0,     0,   179,     0,   168,     0,     0,    65,    66,    67,
    68,    69,   169,   170,    70,   171,   172,     0,   180,   173,
   174,   175,   316,     0,     0,     0,     0,     0,     0,     0,
   176,   129,     0,   177,   178,   130,     0,   131,     0,   132,
   133,     0,   134,    38,    39,   179,     0,    40,     0,    41,
    42,     0,   135,   136,   137,     0,     0,     0,    43,   138,
     0,   182,     0,   129,   139,     0,     0,   130,     0,   131,
     0,   132,   133,     0,   134,   140,     0,     0,   141,     0,
     0,     0,     0,     0,   135,   136,   137,     0,     0,     0,
   142,   138,   314,     0,     0,   146,   139,   147,   148,   149,
     0,     0,     0,   150,   151,     0,   143,   140,   152,     0,
   141,    65,    66,    67,    68,    69,     0,     0,    70,   153,
     0,    91,   142,   154,     0,   155,   156,   146,     0,   147,
   148,   149,     0,     0,     0,   150,   151,   157,   145,   158,
   152,     0,   209,   210,   211,   212,   213,   214,   215,   216,
     0,   153,   322,     0,     0,   154,     0,   155,   156,   183,
     0,     0,   184,   185,     0,     0,     0,   186,   187,   157,
   159,   158,   188,    38,    39,     0,    77,    40,     0,    41,
    42,     0,     0,   189,     0,     0,     0,   190,    43,   191,
   192,   183,     0,     0,   184,   185,    98,     0,     0,   186,
   187,   193,   330,   194,   188,    38,    39,    78,     0,    40,
     0,    41,    42,     0,     0,   189,     0,     0,     0,   190,
    43,   191,   192,     0,     0,    38,    39,    99,     0,    40,
     0,    41,    42,   193,   195,   194,     0,     0,     0,     0,
    43,   209,   210,   211,   212,   213,   214,   215,   216,   236,
   237,   238,   239,    65,    66,    67,    68,    69,     0,     0,
    70,    71,     0,     0,     0,     0,   337,   209,   210,   211,
   212,   213,   214,   215,   216
};

static const short yycheck[] = {     5,
   119,     7,    46,   112,   118,     3,     4,   205,     6,    71,
   155,     9,    10,   132,   156,     6,   140,     8,   252,   138,
   134,    23,    66,     8,   133,    22,    23,   172,   262,     8,
     6,   150,     8,   175,   158,   154,   117,   235,     6,   153,
     8,   275,   151,    45,     8,   164,   191,   152,    45,     8,
   192,    57,   176,   167,    82,    61,   165,   166,   292,   178,
   169,   224,    41,    42,    43,   174,   147,   186,    82,    71,
   194,   190,    51,   307,    71,   189,    81,    46,   187,    70,
   243,    72,    82,   188,    53,    73,    65,    66,    67,    68,
    69,    70,   230,   256,    70,    50,    72,    76,   261,   244,
   245,    23,    70,   266,    72,   219,    23,   270,    71,    71,
    73,   249,   110,   217,    66,    70,   279,    72,    51,   257,
    82,    43,    82,    45,    46,    82,   271,   272,    45,   267,
   293,    23,   246,   131,   297,    23,   142,   241,    82,   302,
   259,    82,   280,   281,    66,    70,   284,    72,    71,    71,
   288,   260,    23,    45,    71,    43,    71,    45,   303,   304,
   298,   265,   168,   326,    23,   163,    71,    71,   331,    82,
   289,    71,    71,   179,    45,    82,    78,    79,    71,    71,
   343,    82,   345,    71,   347,    71,    45,    44,    46,   327,
     0,     1,    46,     3,     4,     5,    98,    99,   100,     0,
    71,    53,   316,   341,    14,    70,    71,    72,   322,    19,
    55,    21,    71,   161,   333,   324,    26,    64,    65,    66,
    67,    59,    32,   342,     5,   114,     7,   346,     9,    10,
   197,    12,    13,   171,    15,    16,    -1,    18,    19,    20,
    -1,    51,    52,    24,    -1,   188,    27,    76,    77,    78,
    31,    -1,    81,    -1,    35,    -1,    37,    38,    -1,    40,
    -1,    71,    74,    75,    76,    77,    78,    48,    49,    81,
    51,    -1,     5,    -1,     7,    -1,     9,    10,    -1,    12,
    13,    -1,    15,    16,   290,    18,    19,    20,    70,    71,
    72,    24,    -1,    -1,    27,    70,    71,    72,    31,    -1,
    -1,    82,    35,     7,    37,    38,    -1,    40,    -1,    13,
    -1,    15,    16,    17,    18,    48,    49,    -1,    51,    68,
    69,    25,    -1,    72,    -1,    74,    75,    -1,   334,    33,
    34,    -1,    36,    37,    83,    -1,    40,    41,    42,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,     7,    51,    -1,    82,
    54,    55,    13,    -1,    15,    16,    17,    18,    -1,    66,
    -1,    -1,    66,    -1,    25,    -1,    -1,    74,    75,    76,
    77,    78,    33,    34,    81,    36,    37,    -1,    82,    40,
    41,    42,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    51,     7,    -1,    54,    55,    11,    -1,    13,    -1,    15,
    16,    -1,    18,    68,    69,    66,    -1,    72,    -1,    74,
    75,    -1,    28,    29,    30,    -1,    -1,    -1,    83,    35,
    -1,    82,    -1,     7,    40,    -1,    -1,    11,    -1,    13,
    -1,    15,    16,    -1,    18,    51,    -1,    -1,    54,    -1,
    -1,    -1,    -1,    -1,    28,    29,    30,    -1,    -1,    -1,
    66,    35,     6,    -1,    -1,     7,    40,     9,    10,    11,
    -1,    -1,    -1,    15,    16,    -1,    82,    51,    20,    -1,
    54,    74,    75,    76,    77,    78,    -1,    -1,    81,    31,
    -1,    84,    66,    35,    -1,    37,    38,     7,    -1,     9,
    10,    11,    -1,    -1,    -1,    15,    16,    49,    82,    51,
    20,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
    -1,    31,    47,    -1,    -1,    35,    -1,    37,    38,     7,
    -1,    -1,    10,    11,    -1,    -1,    -1,    15,    16,    49,
    82,    51,    20,    68,    69,    -1,    39,    72,    -1,    74,
    75,    -1,    -1,    31,    -1,    -1,    -1,    35,    83,    37,
    38,     7,    -1,    -1,    10,    11,    39,    -1,    -1,    15,
    16,    49,    82,    51,    20,    68,    69,    70,    -1,    72,
    -1,    74,    75,    -1,    -1,    31,    -1,    -1,    -1,    35,
    83,    37,    38,    -1,    -1,    68,    69,    70,    -1,    72,
    -1,    74,    75,    49,    82,    51,    -1,    -1,    -1,    -1,
    83,    56,    57,    58,    59,    60,    61,    62,    63,    64,
    65,    66,    67,    74,    75,    76,    77,    78,    -1,    -1,
    81,    82,    -1,    -1,    -1,    -1,    82,    56,    57,    58,
    59,    60,    61,    62,    63
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
#line 130 "ifm-parse.y"
{
                    vh_sstore(map, "TITLE", yyvsp[-1].sval);
                ;
    break;}
case 13:
#line 134 "ifm-parse.y"
{
                    if (sectnames == NULL)
                        sectnames = vl_create();
                    vl_spush(sectnames, yyvsp[-1].sval);
                ;
    break;}
case 14:
#line 140 "ifm-parse.y"
{
                    float version;
                    sscanf(VERSION, "%f", &version);
                    if (yyvsp[-1].dval - version > 0.001)
                        fatal("version %g of IFM is required (this is %s)",
                              yyvsp[-1].dval, VERSION);
                ;
    break;}
case 15:
#line 154 "ifm-parse.y"
{
                    curobj = vh_create();
		    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_istore(curobj, "ID", roomid++);
                    vh_pstore(curobj, "STYLE", current_styles());
                    vh_pstore(curobj, "LINK_STYLE", current_styles());
                    implicit = 0;
                    modify = 0;
		;
    break;}
case 16:
#line 164 "ifm-parse.y"
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
#line 257 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(roomtags, yyvsp[0].sval)) == NULL) {
                        err("room tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 18:
#line 265 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 21:
#line 275 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("room", yyvsp[0].sval, curobj, roomtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 22:
#line 282 "ifm-parse.y"
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
                            err("room tag '%s' not yet defined", yyvsp[0].sval);
                    } else {
                        CHANGE_ERROR(from);
                    }
		;
    break;}
case 23:
#line 301 "ifm-parse.y"
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
#line 316 "ifm-parse.y"
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
#line 329 "ifm-parse.y"
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
#line 344 "ifm-parse.y"
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
#line 359 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 28:
#line 363 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 29:
#line 367 "ifm-parse.y"
{
                    vh_istore(curobj, "NODROP", 1);
		;
    break;}
case 30:
#line 371 "ifm-parse.y"
{
                    vh_istore(curobj, "NOLINK", 1);
		;
    break;}
case 31:
#line 375 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 32:
#line 379 "ifm-parse.y"
{
                    startroom = curobj;
		;
    break;}
case 33:
#line 383 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 34:
#line 387 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(NEED), curitems);
                ;
    break;}
case 35:
#line 391 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		;
    break;}
case 36:
#line 395 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		;
    break;}
case 37:
#line 399 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                ;
    break;}
case 38:
#line 405 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 39:
#line 409 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 40:
#line 413 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 41:
#line 418 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 42:
#line 423 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 43:
#line 428 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 47:
#line 439 "ifm-parse.y"
{
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, yyvsp[0].vval);
		;
    break;}
case 48:
#line 447 "ifm-parse.y"
{
                    yyval.vval = vs_screate(yyvsp[0].sval);
                    itroom = vs_copy(yyval.vval);
                ;
    break;}
case 49:
#line 452 "ifm-parse.y"
{
                    if (itroom == NULL)
                        err("no room referred to by 'it'");
                    else
                        yyval.vval = vs_copy(itroom);
                ;
    break;}
case 50:
#line 459 "ifm-parse.y"
{
                    if (lastroom == NULL) {
                        err("no room referred to by 'last'");
                    } else {
                        yyval.vval = vs_pcreate(lastroom);
                        itroom = vs_copy(yyval.vval);
                    }                        
                ;
    break;}
case 51:
#line 474 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_istore(curobj, "ID", itemid++);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 52:
#line 482 "ifm-parse.y"
{
                    if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lastitem = curobj;
                    vl_ppush(items, curobj);
                    RESET_IT;
		;
    break;}
case 53:
#line 491 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(itemtags, yyvsp[0].sval)) == NULL) {
                        err("item tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 54:
#line 499 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 57:
#line 509 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("item", yyvsp[0].sval, curobj, itemtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 58:
#line 516 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 59:
#line 520 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 60:
#line 524 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 61:
#line 528 "ifm-parse.y"
{
                    obsolete("'given' attribute", "task 'give' attribute");
                    vh_istore(curobj, "GIVEN", 1);
		;
    break;}
case 62:
#line 533 "ifm-parse.y"
{
                    vh_istore(curobj, "LOST", 1);
		;
    break;}
case 63:
#line 537 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 64:
#line 541 "ifm-parse.y"
{
                    vh_istore(curobj, "KEEP", 1);
		;
    break;}
case 65:
#line 545 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_WITH", curitems);
		;
    break;}
case 66:
#line 549 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_UNTIL", curtasks);
		;
    break;}
case 67:
#line 553 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 68:
#line 557 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
                ;
    break;}
case 69:
#line 561 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
                ;
    break;}
case 70:
#line 565 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 71:
#line 569 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 75:
#line 579 "ifm-parse.y"
{ allflag = 0; ;
    break;}
case 76:
#line 580 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 77:
#line 581 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 78:
#line 585 "ifm-parse.y"
{
                    if (curitems == NULL)
                        curitems = vl_create();
                    vl_push(curitems, yyvsp[0].vval);
		;
    break;}
case 79:
#line 593 "ifm-parse.y"
{
                    yyval.vval = vs_screate(yyvsp[0].sval);
                    ititem = vs_copy(yyval.vval);
                ;
    break;}
case 80:
#line 598 "ifm-parse.y"
{
                    if (ititem == NULL)
                        err("no item referred to by 'it'");
                    else
                        yyval.vval = vs_copy(ititem);
                ;
    break;}
case 81:
#line 605 "ifm-parse.y"
{
                    if (lastitem == NULL) {
                        err("no item referred to by 'last'");
                    } else {
                        yyval.vval = vs_pcreate(lastitem);
                        ititem = vs_copy(yyval.vval);
                    }
                ;
    break;}
case 82:
#line 620 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 83:
#line 628 "ifm-parse.y"
{
                    vl_ppush(links, curobj);
                    RESET_IT;
		;
    break;}
case 84:
#line 633 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(linktags, yyvsp[0].sval)) == NULL) {
                        err("link tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 85:
#line 641 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 88:
#line 651 "ifm-parse.y"
{
                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;
		;
    break;}
case 89:
#line 656 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 90:
#line 660 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 91:
#line 664 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 92:
#line 668 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 93:
#line 672 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 94:
#line 676 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 95:
#line 680 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 96:
#line 684 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 97:
#line 690 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 98:
#line 694 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 99:
#line 699 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 100:
#line 704 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 101:
#line 709 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("link", yyvsp[0].sval, curobj, linktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 103:
#line 723 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 104:
#line 731 "ifm-parse.y"
{
                    vl_ppush(joins, curobj);
                    RESET_IT;
		;
    break;}
case 105:
#line 736 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(jointags, yyvsp[0].sval)) == NULL) {
                        err("join tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 106:
#line 744 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 109:
#line 754 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 110:
#line 758 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 111:
#line 762 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 112:
#line 766 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 113:
#line 770 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 114:
#line 774 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 115:
#line 778 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 116:
#line 782 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 117:
#line 786 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 118:
#line 792 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 119:
#line 796 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 120:
#line 801 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 121:
#line 806 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 122:
#line 811 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("join", yyvsp[0].sval, curobj, jointags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 124:
#line 825 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 125:
#line 832 "ifm-parse.y"
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
#line 843 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(tasktags, yyvsp[0].sval)) == NULL) {
                        err("task tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 127:
#line 851 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 130:
#line 861 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("task", yyvsp[0].sval, curobj, tasktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 131:
#line 868 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 132:
#line 872 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
		;
    break;}
case 133:
#line 876 "ifm-parse.y"
{
                    SET_LIST(curobj, "GIVE", curitems);
		;
    break;}
case 134:
#line 880 "ifm-parse.y"
{
                    SET_LIST(curobj, "GET", curitems);
		;
    break;}
case 135:
#line 884 "ifm-parse.y"
{
                    SET_LIST(curobj, "DO", curtasks);
		;
    break;}
case 136:
#line 888 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
		;
    break;}
case 137:
#line 894 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 138:
#line 901 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 139:
#line 908 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 140:
#line 916 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 141:
#line 920 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 142:
#line 925 "ifm-parse.y"
{
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
                ;
    break;}
case 143:
#line 929 "ifm-parse.y"
{
                    SET_LIST(curobj, "LOSE", curitems);
		;
    break;}
case 144:
#line 933 "ifm-parse.y"
{
                    vh_store(curobj, "GOTO", yyvsp[0].vval);
                ;
    break;}
case 145:
#line 937 "ifm-parse.y"
{
                    vh_store(curobj, "FOLLOW", yyvsp[0].vval);
                ;
    break;}
case 146:
#line 941 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 147:
#line 945 "ifm-parse.y"
{
                    vh_istore(curobj, "NOROOM", 1);
		;
    break;}
case 148:
#line 949 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 149:
#line 953 "ifm-parse.y"
{
                    vh_istore(curobj, "SAFE", 1);
                ;
    break;}
case 150:
#line 957 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 151:
#line 961 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 152:
#line 965 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", yyvsp[0].sval);
                ;
    break;}
case 153:
#line 970 "ifm-parse.y"
{
                    add_attr(curobj, "CMD", NULL);
                ;
    break;}
case 154:
#line 974 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 158:
#line 985 "ifm-parse.y"
{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, yyvsp[0].vval);
		;
    break;}
case 159:
#line 993 "ifm-parse.y"
{
                    yyval.vval = vs_screate(yyvsp[0].sval);
                    ittask = vs_copy(yyval.vval);
                ;
    break;}
case 160:
#line 998 "ifm-parse.y"
{
                    if (ittask == NULL)
                        err("no task referred to by 'it'");
                    else
                        yyval.vval = vs_copy(ittask);
                ;
    break;}
case 161:
#line 1005 "ifm-parse.y"
{
                    if (lasttask == NULL) {
                        err("no task referred to by 'last'");
                    } else {
                        yyval.vval = vs_pcreate(lasttask);
                        ittask = vs_copy(yyval.vval);
                    }
                ;
    break;}
case 162:
#line 1020 "ifm-parse.y"
{
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                ;
    break;}
case 163:
#line 1028 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                ;
    break;}
case 164:
#line 1032 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 165:
#line 1037 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                ;
    break;}
case 166:
#line 1041 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 167:
#line 1046 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, NULL);
                ;
    break;}
case 168:
#line 1050 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, NULL);
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 170:
#line 1058 "ifm-parse.y"
{
                    push_style(yyvsp[0].sval);
                    instyle++;
                ;
    break;}
case 171:
#line 1069 "ifm-parse.y"
{
                    push_style(yyvsp[-1].sval);
                ;
    break;}
case 172:
#line 1073 "ifm-parse.y"
{
                    pop_style(yyvsp[-1].sval);
                ;
    break;}
case 173:
#line 1077 "ifm-parse.y"
{
                    pop_style(NULL);
                ;
    break;}
case 176:
#line 1087 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", yyvsp[0].sval);
                    ref_style(yyvsp[0].sval);
                ;
    break;}
case 179:
#line 1102 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, yyvsp[0].ival);
		;
    break;}
case 180:
#line 1108 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-1].ival);
                ;
    break;}
case 181:
#line 1117 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-2].ival);
                    obsolete("'times' keyword", "just the repeat count");
                ;
    break;}
case 182:
#line 1128 "ifm-parse.y"
{ yyval.ival = D_NORTH;	    ;
    break;}
case 183:
#line 1129 "ifm-parse.y"
{ yyval.ival = D_EAST;	    ;
    break;}
case 184:
#line 1130 "ifm-parse.y"
{ yyval.ival = D_SOUTH;	    ;
    break;}
case 185:
#line 1131 "ifm-parse.y"
{ yyval.ival = D_WEST;	    ;
    break;}
case 186:
#line 1132 "ifm-parse.y"
{ yyval.ival = D_NORTHEAST; ;
    break;}
case 187:
#line 1133 "ifm-parse.y"
{ yyval.ival = D_NORTHWEST; ;
    break;}
case 188:
#line 1134 "ifm-parse.y"
{ yyval.ival = D_SOUTHEAST; ;
    break;}
case 189:
#line 1135 "ifm-parse.y"
{ yyval.ival = D_SOUTHWEST; ;
    break;}
case 190:
#line 1138 "ifm-parse.y"
{ yyval.ival = D_IN;   ;
    break;}
case 191:
#line 1139 "ifm-parse.y"
{ yyval.ival = D_OUT;  ;
    break;}
case 192:
#line 1140 "ifm-parse.y"
{ yyval.ival = D_UP;   ;
    break;}
case 193:
#line 1141 "ifm-parse.y"
{ yyval.ival = D_DOWN; ;
    break;}
case 194:
#line 1148 "ifm-parse.y"
{ yyval.dval = yyvsp[0].ival; ;
    break;}
case 195:
#line 1149 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 196:
#line 1150 "ifm-parse.y"
{ yyval.dval = var_real(yyvsp[0].sval); ;
    break;}
case 197:
#line 1151 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 198:
#line 1152 "ifm-parse.y"
{ yyval.dval = -yyvsp[0].dval; ;
    break;}
case 199:
#line 1153 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval + yyvsp[0].dval; ;
    break;}
case 200:
#line 1154 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval - yyvsp[0].dval; ;
    break;}
case 201:
#line 1155 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval * yyvsp[0].dval; ;
    break;}
case 202:
#line 1156 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval / yyvsp[0].dval; ;
    break;}
case 203:
#line 1157 "ifm-parse.y"
{ yyval.dval = pow(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 204:
#line 1158 "ifm-parse.y"
{ yyval.dval = fmod(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 205:
#line 1159 "ifm-parse.y"
{ yyval.dval = yyvsp[-1].dval; ;
    break;}
case 206:
#line 1162 "ifm-parse.y"
{ yyval.ival = (int) yyvsp[0].dval; ;
    break;}
case 207:
#line 1165 "ifm-parse.y"
{ yyval.sval = yyvsp[0].sval; ;
    break;}
case 208:
#line 1166 "ifm-parse.y"
{ yyval.sval = var_string(yyvsp[0].sval); ;
    break;}
case 209:
#line 1170 "ifm-parse.y"
{
                    yyval.sval = yyvsp[0].sval;
                    repeat = 1;
                ;
    break;}
case 210:
#line 1175 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-1].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                ;
    break;}
case 211:
#line 1182 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-2].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    obsolete("'times' keyword", "just the repeat count");
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
#line 1191 "ifm-parse.y"

