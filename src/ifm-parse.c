
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



#define	YYFINAL		328
#define	YYFLAG		-32768
#define	YYNTBASE	74

#define YYTRANSLATE(x) ((unsigned)(x) <= 325 ? yytranslate[x] : 126)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    72,     2,
    73,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
    67,    68,    69,    70,    71
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
   562,   564,   566,   568,   570,   572,   574,   576,   578,   581
};

static const short yyrhs[] = {    -1,
    74,    75,     0,    74,     1,     0,    76,     0,    77,     0,
    85,     0,    94,     0,    99,     0,   104,     0,   112,     0,
   115,     0,    32,   124,    72,     0,    26,   124,    72,     0,
    21,   122,    72,     0,     0,     3,   124,    78,    80,    72,
     0,     0,     3,    71,    79,    80,    72,     0,     0,    80,
    81,     0,     7,    71,     0,     9,   118,     6,    71,     0,
     9,   118,     0,    27,   118,     0,     5,    82,     0,    19,
    82,     0,    20,   121,     0,    10,     0,    12,     0,    48,
     0,    49,     0,    24,     0,    40,     0,    16,    90,     0,
    35,   109,     0,    15,   109,     0,    38,    91,     0,    31,
   123,     0,    18,   123,     0,    37,   125,     0,    37,     8,
   125,     0,    37,     6,   125,     0,    13,   124,     0,    51,
   116,     0,    83,     0,    82,    83,     0,    84,     0,    71,
     0,    45,     0,    23,     0,     0,     4,   124,    86,    88,
    72,     0,     0,     4,    71,    87,    88,    72,     0,     0,
    88,    89,     0,     7,    71,     0,    66,    84,     0,    13,
   124,     0,    11,     0,    28,     0,    29,     0,    54,     0,
    30,     0,    30,    53,    90,     0,    30,    46,   109,     0,
    16,    90,     0,    35,   109,     0,    15,   109,     0,    18,
   123,     0,    40,     0,    51,   116,     0,    92,     0,    90,
    92,     0,    90,     0,    43,     0,    43,    44,    90,     0,
    93,     0,    71,     0,    45,     0,    23,     0,     0,     5,
    84,     8,    84,    95,    97,    72,     0,     0,     5,    71,
    96,    97,    72,     0,     0,    97,    98,     0,     9,   118,
     0,    20,   121,     0,    10,     0,    11,     0,    49,     0,
    16,    90,     0,    35,   109,     0,    15,   109,     0,    38,
    91,     0,    31,   123,     0,    37,   125,     0,    37,     8,
   125,     0,    37,     6,   125,     0,     7,    71,     0,    51,
   116,     0,     0,    19,    84,     8,    84,   100,   102,    72,
     0,     0,    19,    71,   101,   102,    72,     0,     0,   102,
   103,     0,    20,   120,     0,    20,   121,     0,    10,     0,
    11,     0,    49,     0,    16,    90,     0,    35,   109,     0,
    15,   109,     0,    38,    91,     0,    31,   123,     0,    37,
   125,     0,    37,     8,   125,     0,    37,     6,   125,     0,
     7,    71,     0,    51,   116,     0,     0,    14,   124,   105,
   107,    72,     0,     0,    14,    71,   106,   107,    72,     0,
     0,   107,   108,     0,     7,    71,     0,    15,   109,     0,
    16,    90,     0,    41,    90,     0,    17,    90,     0,    55,
   109,     0,    42,    91,     0,    42,    91,    46,   109,     0,
    42,    91,    66,    84,     0,    42,    91,    66,    84,    46,
   109,     0,    42,    66,    84,     0,    42,    66,    84,    46,
   109,     0,    42,    46,   109,     0,    33,    90,     0,    25,
    84,     0,    36,   111,     0,    66,    84,     0,    66,    22,
     0,    54,     0,    34,     0,    18,   123,     0,    40,     0,
    37,   125,     0,    37,    50,     0,    13,   124,     0,    51,
   116,     0,   110,     0,   109,   110,     0,   111,     0,    71,
     0,    45,     0,    23,     0,   113,     0,    71,    73,   122,
   114,    72,     0,    71,    71,    73,   122,   114,    72,     0,
    71,    73,    70,   114,    72,     0,    71,    71,    73,    70,
   114,    72,     0,    71,    73,    39,   114,    72,     0,    71,
    71,    73,    39,   114,    72,     0,     0,    66,    51,    71,
     0,    51,    71,    72,     0,    52,    71,    72,     0,    52,
    72,     0,   117,     0,   116,   117,     0,    71,     0,   119,
     0,   118,   119,     0,   120,     0,   120,   123,     0,   120,
    47,   123,     0,    56,     0,    57,     0,    58,     0,    59,
     0,    60,     0,    61,     0,    62,     0,    63,     0,    66,
     0,    67,     0,    64,     0,    65,     0,    68,     0,    69,
     0,   122,     0,    70,     0,   124,     0,   124,   123,     0,
   124,    47,   123,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   104,   105,   106,   109,   110,   111,   112,   113,   114,   115,
   116,   123,   127,   133,   147,   157,   250,   258,   264,   265,
   268,   275,   294,   309,   322,   337,   352,   356,   360,   364,
   368,   372,   376,   380,   384,   388,   392,   398,   402,   406,
   411,   416,   421,   425,   428,   429,   432,   440,   445,   452,
   467,   475,   484,   492,   498,   499,   502,   509,   513,   517,
   521,   526,   530,   534,   538,   542,   546,   550,   554,   558,
   562,   566,   569,   570,   573,   574,   575,   578,   586,   591,
   598,   613,   621,   626,   634,   640,   641,   644,   649,   653,
   657,   661,   665,   669,   673,   677,   683,   687,   692,   697,
   702,   709,   716,   724,   729,   737,   743,   744,   747,   751,
   755,   759,   763,   767,   771,   775,   779,   785,   789,   794,
   799,   804,   811,   818,   825,   836,   844,   850,   851,   854,
   861,   865,   869,   873,   877,   881,   887,   894,   901,   909,
   913,   918,   922,   926,   930,   934,   938,   942,   946,   950,
   954,   958,   963,   967,   971,   974,   975,   978,   986,   991,
   998,  1013,  1021,  1025,  1030,  1034,  1039,  1043,  1050,  1051,
  1062,  1066,  1070,  1076,  1077,  1080,  1091,  1092,  1095,  1101,
  1110,  1122,  1123,  1124,  1125,  1126,  1127,  1128,  1129,  1132,
  1133,  1134,  1135,  1142,  1143,  1146,  1149,  1152,  1157,  1164
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
"OUT","INTEGER","REAL","STRING","ID","';'","'='","stmt_list","stmt","ctrl_stmt",
"room_stmt","@1","@2","room_attrs","room_attr","room_list","room_elt","room",
"item_stmt","@3","@4","item_attrs","item_attr","item_list","item_list_all","item_elt",
"item","link_stmt","@5","@6","link_attrs","link_attr","join_stmt","@7","@8",
"join_attrs","join_attr","task_stmt","@9","@10","task_attrs","task_attr","task_list",
"task_elt","task","vars_stmt","set_var","in_style","style_stmt","style_list",
"style_elt","dir_list","dir_elt","compass","otherdir","exp","integer","string",
"string_repeat", NULL
};
#endif

static const short yyr1[] = {     0,
    74,    74,    74,    75,    75,    75,    75,    75,    75,    75,
    75,    76,    76,    76,    78,    77,    79,    77,    80,    80,
    81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
    81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
    81,    81,    81,    81,    82,    82,    83,    84,    84,    84,
    86,    85,    87,    85,    88,    88,    89,    89,    89,    89,
    89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
    89,    89,    90,    90,    91,    91,    91,    92,    93,    93,
    93,    95,    94,    96,    94,    97,    97,    98,    98,    98,
    98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
    98,    98,   100,    99,   101,    99,   102,   102,   103,   103,
   103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
   103,   103,   103,   105,   104,   106,   104,   107,   107,   108,
   108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
   108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
   108,   108,   108,   108,   108,   109,   109,   110,   111,   111,
   111,   112,   113,   113,   113,   113,   113,   113,   114,   114,
   115,   115,   115,   116,   116,   117,   118,   118,   119,   119,
   119,   120,   120,   120,   120,   120,   120,   120,   120,   121,
   121,   121,   121,   122,   122,   123,   124,   125,   125,   125
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
     1,     1,     1,     1,     1,     1,     1,     1,     2,     3
};

static const short yydefact[] = {     1,
     0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     2,     4,     5,     6,     7,     8,     9,
    10,   162,    11,   197,    17,    15,    53,    51,    50,    49,
    84,     0,   126,   124,   105,     0,   194,   195,     0,     0,
     0,     0,     0,   173,     0,     0,    19,    19,    55,    55,
    86,     0,   128,   128,   107,     0,    14,    13,    12,   171,
   172,     0,   169,   169,   169,     0,     0,     0,     0,     0,
    48,    82,     0,     0,     0,   103,   169,   169,   169,     0,
     0,     0,     0,     0,     0,     0,    28,    29,     0,     0,
     0,     0,     0,     0,    32,     0,     0,     0,     0,     0,
    33,    30,    31,     0,    18,    20,    16,     0,    60,     0,
     0,     0,     0,    61,    62,    64,     0,    71,     0,    63,
     0,    54,    56,    52,     0,     0,    90,    91,     0,     0,
     0,     0,     0,     0,     0,    92,     0,    85,    87,    86,
     0,     0,     0,     0,     0,     0,     0,     0,   149,     0,
     0,   151,     0,     0,     0,   148,     0,     0,   127,   129,
   125,     0,   111,   112,     0,     0,     0,     0,     0,     0,
     0,   113,     0,   106,   108,   107,     0,     0,     0,     0,
   167,   165,   163,    25,    45,    47,    21,   182,   183,   184,
   185,   186,   187,   188,   189,    23,   177,   179,    43,   161,
   160,   159,    36,   156,   158,    81,    80,    79,    34,    73,
    78,   196,    39,    26,   192,   193,   190,   191,    27,    24,
    38,    35,     0,     0,   198,    40,    76,    75,    37,   176,
    44,   174,    57,    59,    69,    67,    70,     0,     0,    68,
    72,    58,   101,    88,    95,    93,    89,    97,    94,     0,
     0,    98,    96,   102,     0,   130,   154,   131,   132,   134,
   150,   144,   143,   145,   153,   152,   133,     0,     0,   136,
   155,   135,   147,   146,   122,   116,   114,   109,   110,   118,
   115,     0,     0,   119,   117,   123,     0,   168,   166,   164,
   170,    46,     0,   178,     0,   180,   157,    74,    42,    41,
     0,   199,     0,   175,    66,    65,   100,    99,    83,   142,
   140,     0,     0,   121,   120,   104,    22,   181,   200,    77,
     0,   137,   138,   141,     0,   139,     0,     0
};

static const short yydefgoto[] = {     1,
    14,    15,    16,    48,    47,    66,   106,   184,   185,   186,
    17,    50,    49,    68,   123,   228,   229,   210,   211,    18,
   140,    51,    70,   139,    19,   176,    55,    75,   175,    20,
    54,    53,    73,   160,   203,   204,   205,    21,    22,    81,
    23,   231,   232,   196,   197,   198,   219,   212,   213,   225,
   226
};

static const short yypact[] = {-32768,
   191,-32768,   -21,    35,    55,    38,    76,    82,   -37,   -37,
   -32,   111,   -61,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    33,    47,-32768,-32768,    33,    57,-32768,-32768,    20,    22,
    29,    31,    46,-32768,    37,   100,-32768,-32768,-32768,-32768,
-32768,    91,-32768,-32768,-32768,    91,-32768,-32768,-32768,-32768,
-32768,   134,    61,    61,    61,   239,   286,   403,   433,   481,
-32768,-32768,   315,   358,   545,-32768,    61,    61,    61,    81,
    72,   102,   115,    91,    77,   345,-32768,-32768,   -37,   101,
   114,    82,    91,   170,-32768,   345,    82,   101,    -1,    90,
-32768,-32768,-32768,   118,-32768,-32768,-32768,   119,-32768,   -37,
   101,   114,    82,-32768,-32768,    -9,   101,-32768,   118,-32768,
    91,-32768,-32768,-32768,   122,   345,-32768,-32768,   101,   114,
   170,    82,   101,     3,    90,-32768,   118,-32768,-32768,-32768,
   126,   -37,   101,   114,   114,    82,    91,   114,-32768,   101,
   106,-32768,   114,    74,   118,-32768,   101,    67,-32768,-32768,
-32768,   135,-32768,-32768,   101,   114,   573,    82,   101,     7,
    90,-32768,   118,-32768,-32768,-32768,   136,   137,   139,   142,
-32768,-32768,-32768,    91,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,    24,-32768,    96,-32768,-32768,
-32768,-32768,   101,-32768,-32768,-32768,-32768,-32768,   114,-32768,
-32768,-32768,-32768,    91,-32768,-32768,-32768,-32768,-32768,   345,
-32768,   101,   -37,   -37,   131,-32768,   176,   114,-32768,-32768,
   118,-32768,-32768,-32768,   101,   114,-32768,   101,   114,   101,
   118,-32768,-32768,   345,   101,   114,-32768,-32768,   101,   -37,
   -37,-32768,-32768,   118,   513,-32768,-32768,   101,   114,   114,
-32768,-32768,   114,-32768,-32768,-32768,   114,   101,    91,   120,
   118,   101,-32768,-32768,-32768,   101,   114,-32768,-32768,-32768,
   101,   -37,   -37,-32768,-32768,   118,   577,-32768,-32768,-32768,
-32768,-32768,   143,-32768,    82,-32768,-32768,-32768,-32768,-32768,
    82,-32768,   114,-32768,   101,   114,-32768,-32768,-32768,   101,
   175,   101,    91,-32768,-32768,-32768,-32768,-32768,-32768,   114,
   101,   101,   179,   101,   101,   101,   222,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,   178,-32768,   145,  -155,    -5,
-32768,-32768,-32768,   180,-32768,   -87,  -109,   -79,-32768,-32768,
-32768,-32768,    89,-32768,-32768,-32768,-32768,    63,-32768,-32768,
-32768,-32768,   186,-32768,   -97,  -147,    95,-32768,-32768,   154,
-32768,  -102,  -223,   -62,  -129,    80,   -91,     8,   -94,    18,
  -128
};


#define	YYLAST		649


static const short yytable[] = {    32,
   222,    36,   221,   209,   223,   252,   224,   304,   250,    45,
   251,    46,   282,   235,   283,    39,   241,   304,   237,   240,
    26,    28,   266,    34,   236,   253,    40,    41,   292,   293,
   304,   245,    24,   220,   254,   249,   238,   248,    42,   247,
   -48,   284,   246,   239,   270,   258,    72,   304,    24,    25,
    76,   261,   271,    65,    52,   297,   259,   260,   292,   272,
   263,   285,   304,   244,    56,   267,   294,   276,    24,    79,
   286,   281,    24,   280,   297,   279,    24,    29,   277,   188,
   189,   190,   191,   192,   193,   194,   195,   297,   273,    29,
   294,    57,   297,    58,   299,   300,   206,   297,    29,    30,
    59,   297,    60,   296,    24,    27,   199,    24,    33,    62,
   297,    30,   206,    29,   294,   242,   227,    61,   207,   268,
    30,   307,   308,   200,   297,    31,    80,   234,   297,   298,
   302,   180,   227,   297,   207,    30,   206,    71,    63,   269,
   305,   262,   295,   181,   208,   201,    35,   187,   298,    37,
    38,   306,   274,   314,   315,   265,   298,   297,   207,   257,
   208,    71,   297,    37,    38,   312,   298,    37,    38,    64,
   310,   202,    77,   182,   297,    24,   297,   301,   297,   298,
   298,    43,    44,   298,   208,   313,   183,   298,   230,   233,
   327,     2,   243,     3,     4,     5,   256,   298,    37,    38,
   318,    37,    38,    78,     6,   275,   319,   288,   289,     7,
   290,     8,   291,   317,   322,   320,     9,    82,    83,   303,
   321,   328,    10,   324,   325,    67,   298,   326,   255,    69,
   177,   178,   179,   215,   216,   217,   218,   214,   287,    74,
   298,    11,    12,    84,   264,    85,   278,    86,    87,     0,
    88,    89,     0,    90,    91,     0,    92,    93,    94,     0,
     0,    13,    95,   311,     0,    96,     0,     0,     0,    97,
     0,     0,     0,    98,     0,    99,   100,     0,   101,     0,
     0,     0,     0,     0,     0,     0,   102,   103,     0,   104,
    84,     0,    85,     0,    86,    87,     0,    88,    89,     0,
    90,    91,     0,    92,    93,    94,     0,   323,     0,    95,
   105,     0,    96,     0,     0,     0,    97,     0,     0,     0,
    98,   141,    99,   100,     0,   101,     0,   142,     0,   143,
   144,   145,   146,   102,   103,     0,   104,     0,     0,   147,
     0,     0,     0,     0,     0,     0,     0,   148,   149,     0,
   150,   151,     0,     0,   152,   153,   154,   107,     0,     0,
     0,     0,     0,     0,   141,   155,     0,     0,   156,   157,
   142,     0,   143,   144,   145,   146,     0,     0,     0,     0,
   158,     0,   147,     0,     0,     0,   159,     0,     0,     0,
   148,   149,     0,   150,   151,     0,     0,   152,   153,   154,
   188,   189,   190,   191,   192,   193,   194,   195,   155,   108,
     0,   156,   157,   109,     0,   110,     0,   111,   112,     0,
   113,     0,     0,   158,     0,     0,     0,     0,     0,   161,
   114,   115,   116,     0,     0,     0,     0,   117,     0,   108,
     0,     0,   118,   109,     0,   110,     0,   111,   112,     0,
   113,     0,     0,   119,     0,     0,   120,     0,     0,     0,
   114,   115,   116,     0,     0,     0,     0,   117,   121,     0,
     0,     0,   118,     0,   122,     0,     0,     0,     0,     0,
     0,     0,     0,   119,     0,     0,   120,   125,     0,   126,
   127,   128,     0,     0,     0,   129,   130,     0,   121,     0,
   131,     0,     0,     0,   124,     0,     0,     0,     0,     0,
     0,   132,     0,     0,     0,   133,     0,   134,   135,   125,
     0,   126,   127,   128,     0,     0,     0,   129,   130,   136,
     0,   137,   131,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   132,     0,     0,     0,   133,     0,   134,
   135,   162,   138,     0,   163,   164,     0,     0,     0,   165,
   166,   136,     0,   137,   167,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   168,     0,     0,     0,   169,
     0,   170,   171,   162,   309,     0,   163,   164,     0,     0,
     0,   165,   166,   172,     0,   173,   167,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   168,     0,     0,
     0,   169,     0,   170,   171,     0,   174,     0,     0,     0,
     0,     0,     0,     0,     0,   172,     0,   173,   188,   189,
   190,   191,   192,   193,   194,   195,   215,   216,   217,   218,
     0,     0,     0,     0,     0,     0,     0,     0,   316
};

static const short yycheck[] = {     5,
    98,     7,    97,    91,     6,   134,     8,   231,     6,    71,
     8,    73,     6,   111,     8,     8,   119,   241,   113,   117,
     3,     4,   151,     6,   112,   135,     9,    10,   184,     6,
   254,   129,    70,    96,   137,   133,    46,   132,    71,   131,
     8,   170,   130,    53,   154,   143,    52,   271,    70,    71,
    56,   146,   155,    46,     8,   203,   144,   145,   214,   157,
   148,   171,   286,   126,     8,   153,   196,   165,    70,    62,
   173,   169,    70,   168,   222,   167,    70,    23,   166,    56,
    57,    58,    59,    60,    61,    62,    63,   235,    22,    23,
   220,    72,   240,    72,   223,   224,    23,   245,    23,    45,
    72,   249,    72,   198,    70,    71,    89,    70,    71,    73,
   258,    45,    23,    23,   244,   121,    43,    72,    45,    46,
    45,   250,   251,    23,   272,    71,    66,   110,   276,   209,
   225,    51,    43,   281,    45,    45,    23,    71,    39,    66,
   238,   147,    47,    72,    71,    45,    71,    71,   228,    68,
    69,   239,   158,   282,   283,    50,   236,   305,    45,   142,
    71,    71,   310,    68,    69,    46,   246,    68,    69,    70,
   268,    71,    39,    72,   322,    70,   324,    47,   326,   259,
   260,    71,    72,   263,    71,    66,    72,   267,    71,    71,
     0,     1,    71,     3,     4,     5,    71,   277,    68,    69,
   295,    68,    69,    70,    14,    71,   301,    72,    72,    19,
    72,    21,    71,    71,   312,   303,    26,    64,    65,    44,
    46,     0,    32,   321,    46,    48,   306,   325,   140,    50,
    77,    78,    79,    64,    65,    66,    67,    93,   176,    54,
   320,    51,    52,     5,   150,     7,   167,     9,    10,    -1,
    12,    13,    -1,    15,    16,    -1,    18,    19,    20,    -1,
    -1,    71,    24,   269,    -1,    27,    -1,    -1,    -1,    31,
    -1,    -1,    -1,    35,    -1,    37,    38,    -1,    40,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,
     5,    -1,     7,    -1,     9,    10,    -1,    12,    13,    -1,
    15,    16,    -1,    18,    19,    20,    -1,   313,    -1,    24,
    72,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
    35,     7,    37,    38,    -1,    40,    -1,    13,    -1,    15,
    16,    17,    18,    48,    49,    -1,    51,    -1,    -1,    25,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
    36,    37,    -1,    -1,    40,    41,    42,    72,    -1,    -1,
    -1,    -1,    -1,    -1,     7,    51,    -1,    -1,    54,    55,
    13,    -1,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
    66,    -1,    25,    -1,    -1,    -1,    72,    -1,    -1,    -1,
    33,    34,    -1,    36,    37,    -1,    -1,    40,    41,    42,
    56,    57,    58,    59,    60,    61,    62,    63,    51,     7,
    -1,    54,    55,    11,    -1,    13,    -1,    15,    16,    -1,
    18,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    72,
    28,    29,    30,    -1,    -1,    -1,    -1,    35,    -1,     7,
    -1,    -1,    40,    11,    -1,    13,    -1,    15,    16,    -1,
    18,    -1,    -1,    51,    -1,    -1,    54,    -1,    -1,    -1,
    28,    29,    30,    -1,    -1,    -1,    -1,    35,    66,    -1,
    -1,    -1,    40,    -1,    72,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    51,    -1,    -1,    54,     7,    -1,     9,
    10,    11,    -1,    -1,    -1,    15,    16,    -1,    66,    -1,
    20,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,
    -1,    31,    -1,    -1,    -1,    35,    -1,    37,    38,     7,
    -1,     9,    10,    11,    -1,    -1,    -1,    15,    16,    49,
    -1,    51,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    -1,    37,
    38,     7,    72,    -1,    10,    11,    -1,    -1,    -1,    15,
    16,    49,    -1,    51,    20,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,
    -1,    37,    38,     7,    72,    -1,    10,    11,    -1,    -1,
    -1,    15,    16,    49,    -1,    51,    20,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
    -1,    35,    -1,    37,    38,    -1,    72,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    56,    57,
    58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72
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
#line 124 "ifm-parse.y"
{
                    vh_sstore(map, "TITLE", yyvsp[-1].sval);
                ;
    break;}
case 13:
#line 128 "ifm-parse.y"
{
                    if (sectnames == NULL)
                        sectnames = vl_create();
                    vl_spush(sectnames, yyvsp[-1].sval);
                ;
    break;}
case 14:
#line 134 "ifm-parse.y"
{
                    float version;
                    sscanf(VERSION, "%f", &version);
                    if (yyvsp[-1].dval - version > 0.001)
                        fatal("version %g of IFM is required (this is %s)",
                              yyvsp[-1].dval, VERSION);
                ;
    break;}
case 15:
#line 148 "ifm-parse.y"
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
#line 158 "ifm-parse.y"
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
#line 251 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(roomtags, yyvsp[0].sval)) == NULL) {
                        err("room tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 18:
#line 259 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 21:
#line 269 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("room", yyvsp[0].sval, curobj, roomtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 22:
#line 276 "ifm-parse.y"
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
#line 295 "ifm-parse.y"
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
#line 310 "ifm-parse.y"
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
#line 323 "ifm-parse.y"
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
#line 338 "ifm-parse.y"
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
#line 353 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 28:
#line 357 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 29:
#line 361 "ifm-parse.y"
{
                    vh_istore(curobj, "NODROP", 1);
		;
    break;}
case 30:
#line 365 "ifm-parse.y"
{
                    vh_istore(curobj, "NOLINK", 1);
		;
    break;}
case 31:
#line 369 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 32:
#line 373 "ifm-parse.y"
{
                    startroom = curobj;
		;
    break;}
case 33:
#line 377 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 34:
#line 381 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(NEED), curitems);
                ;
    break;}
case 35:
#line 385 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		;
    break;}
case 36:
#line 389 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		;
    break;}
case 37:
#line 393 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                ;
    break;}
case 38:
#line 399 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 39:
#line 403 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 40:
#line 407 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 41:
#line 412 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 42:
#line 417 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 43:
#line 422 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 47:
#line 433 "ifm-parse.y"
{
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, yyvsp[0].vval);
		;
    break;}
case 48:
#line 441 "ifm-parse.y"
{
                    yyval.vval = vs_screate(yyvsp[0].sval);
                    itroom = vs_copy(yyval.vval);
                ;
    break;}
case 49:
#line 446 "ifm-parse.y"
{
                    if (itroom == NULL)
                        err("no room referred to by 'it'");
                    else
                        yyval.vval = vs_copy(itroom);
                ;
    break;}
case 50:
#line 453 "ifm-parse.y"
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
#line 468 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_istore(curobj, "ID", itemid++);
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
                        err("item tag '%s' not yet defined", yyvsp[0].sval);
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
                    obsolete("'given' attribute", "task 'give' attribute");
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
                    yyval.vval = vs_screate(yyvsp[0].sval);
                    ititem = vs_copy(yyval.vval);
                ;
    break;}
case 80:
#line 592 "ifm-parse.y"
{
                    if (ititem == NULL)
                        err("no item referred to by 'it'");
                    else
                        yyval.vval = vs_copy(ititem);
                ;
    break;}
case 81:
#line 599 "ifm-parse.y"
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
#line 614 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 83:
#line 622 "ifm-parse.y"
{
                    vl_ppush(links, curobj);
                    RESET_IT;
		;
    break;}
case 84:
#line 627 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(linktags, yyvsp[0].sval)) == NULL) {
                        err("link tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 85:
#line 635 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 88:
#line 645 "ifm-parse.y"
{
                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;
		;
    break;}
case 89:
#line 650 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 90:
#line 654 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 91:
#line 658 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 92:
#line 662 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 93:
#line 666 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 94:
#line 670 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 95:
#line 674 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 96:
#line 678 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 97:
#line 684 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 98:
#line 688 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
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
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 101:
#line 703 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("link", yyvsp[0].sval, curobj, linktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 103:
#line 717 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 104:
#line 725 "ifm-parse.y"
{
                    vl_ppush(joins, curobj);
                    RESET_IT;
		;
    break;}
case 105:
#line 730 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(jointags, yyvsp[0].sval)) == NULL) {
                        err("join tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 106:
#line 738 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 109:
#line 748 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 110:
#line 752 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 111:
#line 756 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 112:
#line 760 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 113:
#line 764 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 114:
#line 768 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 115:
#line 772 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 116:
#line 776 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 117:
#line 780 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 118:
#line 786 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 119:
#line 790 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 120:
#line 795 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 121:
#line 800 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 122:
#line 805 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("join", yyvsp[0].sval, curobj, jointags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 124:
#line 819 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 125:
#line 826 "ifm-parse.y"
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
#line 837 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(tasktags, yyvsp[0].sval)) == NULL) {
                        err("task tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 127:
#line 845 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 130:
#line 855 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("task", yyvsp[0].sval, curobj, tasktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 131:
#line 862 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 132:
#line 866 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
		;
    break;}
case 133:
#line 870 "ifm-parse.y"
{
                    SET_LIST(curobj, "GIVE", curitems);
		;
    break;}
case 134:
#line 874 "ifm-parse.y"
{
                    SET_LIST(curobj, "GET", curitems);
		;
    break;}
case 135:
#line 878 "ifm-parse.y"
{
                    SET_LIST(curobj, "DO", curtasks);
		;
    break;}
case 136:
#line 882 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
		;
    break;}
case 137:
#line 888 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 138:
#line 895 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 139:
#line 902 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 140:
#line 910 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 141:
#line 914 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 142:
#line 919 "ifm-parse.y"
{
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
                ;
    break;}
case 143:
#line 923 "ifm-parse.y"
{
                    SET_LIST(curobj, "LOSE", curitems);
		;
    break;}
case 144:
#line 927 "ifm-parse.y"
{
                    vh_store(curobj, "GOTO", yyvsp[0].vval);
                ;
    break;}
case 145:
#line 931 "ifm-parse.y"
{
                    vh_store(curobj, "FOLLOW", yyvsp[0].vval);
                ;
    break;}
case 146:
#line 935 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 147:
#line 939 "ifm-parse.y"
{
                    vh_istore(curobj, "NOROOM", 1);
		;
    break;}
case 148:
#line 943 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 149:
#line 947 "ifm-parse.y"
{
                    vh_istore(curobj, "SAFE", 1);
                ;
    break;}
case 150:
#line 951 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 151:
#line 955 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 152:
#line 959 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", yyvsp[0].sval);
                ;
    break;}
case 153:
#line 964 "ifm-parse.y"
{
                    add_attr(curobj, "CMD", NULL);
                ;
    break;}
case 154:
#line 968 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 158:
#line 979 "ifm-parse.y"
{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, yyvsp[0].vval);
		;
    break;}
case 159:
#line 987 "ifm-parse.y"
{
                    yyval.vval = vs_screate(yyvsp[0].sval);
                    ittask = vs_copy(yyval.vval);
                ;
    break;}
case 160:
#line 992 "ifm-parse.y"
{
                    if (ittask == NULL)
                        err("no task referred to by 'it'");
                    else
                        yyval.vval = vs_copy(ittask);
                ;
    break;}
case 161:
#line 999 "ifm-parse.y"
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
#line 1014 "ifm-parse.y"
{
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                ;
    break;}
case 163:
#line 1022 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                ;
    break;}
case 164:
#line 1026 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 165:
#line 1031 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                ;
    break;}
case 166:
#line 1035 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 167:
#line 1040 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, NULL);
                ;
    break;}
case 168:
#line 1044 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, NULL);
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 170:
#line 1052 "ifm-parse.y"
{
                    push_style(yyvsp[0].sval);
                    instyle++;
                ;
    break;}
case 171:
#line 1063 "ifm-parse.y"
{
                    push_style(yyvsp[-1].sval);
                ;
    break;}
case 172:
#line 1067 "ifm-parse.y"
{
                    pop_style(yyvsp[-1].sval);
                ;
    break;}
case 173:
#line 1071 "ifm-parse.y"
{
                    pop_style(NULL);
                ;
    break;}
case 176:
#line 1081 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", yyvsp[0].sval);
                    ref_style(yyvsp[0].sval);
                ;
    break;}
case 179:
#line 1096 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, yyvsp[0].ival);
		;
    break;}
case 180:
#line 1102 "ifm-parse.y"
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
#line 1111 "ifm-parse.y"
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
#line 1122 "ifm-parse.y"
{ yyval.ival = D_NORTH;	    ;
    break;}
case 183:
#line 1123 "ifm-parse.y"
{ yyval.ival = D_EAST;	    ;
    break;}
case 184:
#line 1124 "ifm-parse.y"
{ yyval.ival = D_SOUTH;	    ;
    break;}
case 185:
#line 1125 "ifm-parse.y"
{ yyval.ival = D_WEST;	    ;
    break;}
case 186:
#line 1126 "ifm-parse.y"
{ yyval.ival = D_NORTHEAST; ;
    break;}
case 187:
#line 1127 "ifm-parse.y"
{ yyval.ival = D_NORTHWEST; ;
    break;}
case 188:
#line 1128 "ifm-parse.y"
{ yyval.ival = D_SOUTHEAST; ;
    break;}
case 189:
#line 1129 "ifm-parse.y"
{ yyval.ival = D_SOUTHWEST; ;
    break;}
case 190:
#line 1132 "ifm-parse.y"
{ yyval.ival = D_IN;   ;
    break;}
case 191:
#line 1133 "ifm-parse.y"
{ yyval.ival = D_OUT;  ;
    break;}
case 192:
#line 1134 "ifm-parse.y"
{ yyval.ival = D_UP;   ;
    break;}
case 193:
#line 1135 "ifm-parse.y"
{ yyval.ival = D_DOWN; ;
    break;}
case 194:
#line 1142 "ifm-parse.y"
{ yyval.dval = yyvsp[0].ival; ;
    break;}
case 195:
#line 1143 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 196:
#line 1146 "ifm-parse.y"
{ yyval.ival = (int) yyvsp[0].dval; ;
    break;}
case 197:
#line 1149 "ifm-parse.y"
{ yyval.sval = yyvsp[0].sval; ;
    break;}
case 198:
#line 1153 "ifm-parse.y"
{
                    yyval.sval = yyvsp[0].sval;
                    repeat = 1;
                ;
    break;}
case 199:
#line 1158 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-1].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                ;
    break;}
case 200:
#line 1165 "ifm-parse.y"
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
#line 1174 "ifm-parse.y"

