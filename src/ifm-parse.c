
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



#define	YYFINAL		368
#define	YYFLAG		-32768
#define	YYNTBASE	87

#define YYTRANSLATE(x) ((unsigned)(x) <= 330 ? yytranslate[x] : 140)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    80,     2,     2,    85,
    86,    78,    76,     2,    77,     2,    79,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    84,     2,
    75,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    83,     2,     2,     2,     2,     2,     2,
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
    67,    68,    69,    70,    71,    72,    73,    74,    81,    82
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     7,     9,    11,    13,    15,    17,    19,
    21,    23,    27,    31,    35,    36,    42,    43,    49,    50,
    53,    56,    61,    64,    67,    70,    73,    76,    78,    80,
    82,    84,    86,    88,    91,    94,    97,   100,   103,   106,
   109,   113,   117,   120,   123,   125,   127,   129,   132,   134,
   136,   138,   140,   141,   147,   148,   154,   155,   158,   161,
   164,   167,   169,   171,   173,   175,   177,   181,   185,   188,
   191,   194,   197,   199,   202,   204,   207,   209,   211,   215,
   217,   219,   221,   223,   224,   232,   233,   239,   240,   243,
   246,   249,   251,   253,   255,   258,   261,   264,   267,   270,
   273,   277,   281,   284,   287,   289,   290,   298,   299,   305,
   306,   309,   312,   315,   317,   319,   321,   324,   327,   330,
   333,   336,   339,   343,   347,   350,   353,   354,   360,   361,
   367,   368,   371,   374,   377,   380,   383,   386,   389,   394,
   399,   406,   410,   416,   420,   423,   426,   429,   432,   435,
   437,   439,   442,   444,   447,   450,   453,   456,   458,   461,
   463,   465,   467,   469,   471,   473,   479,   486,   492,   499,
   505,   512,   517,   522,   523,   527,   531,   535,   539,   543,
   547,   551,   555,   559,   562,   564,   567,   569,   571,   573,
   575,   578,   580,   583,   587,   589,   591,   593,   595,   597,
   599,   601,   603,   605,   607,   609,   611,   613,   615,   617,
   620,   623,   627,   631,   635,   639,   643,   647,   651,   653,
   655,   657,   659,   662
};

static const short yyrhs[] = {    -1,
    87,    88,     0,    87,     1,     0,    89,     0,    90,     0,
    98,     0,   107,     0,   112,     0,   117,     0,   125,     0,
   129,     0,    32,   138,    84,     0,    26,   138,    84,     0,
    56,   136,    84,     0,     0,     3,   138,    91,    93,    84,
     0,     0,     3,    73,    92,    93,    84,     0,     0,    93,
    94,     0,     7,    73,     0,     9,   132,     6,    73,     0,
     9,   132,     0,    27,   132,     0,     5,    95,     0,    19,
    95,     0,    20,   135,     0,    10,     0,    57,     0,    48,
     0,    49,     0,    24,     0,    40,     0,    16,   103,     0,
    35,   122,     0,    15,   122,     0,    38,   104,     0,    31,
   137,     0,    18,   137,     0,    37,   139,     0,    37,     8,
   139,     0,    37,     6,   139,     0,    13,   138,     0,    52,
   130,     0,    21,     0,    12,     0,    96,     0,    95,    96,
     0,    97,     0,    73,     0,    45,     0,    23,     0,     0,
     4,   138,    99,   101,    84,     0,     0,     4,    73,   100,
   101,    84,     0,     0,   101,   102,     0,     7,    73,     0,
    68,    97,     0,    13,   138,     0,    11,     0,    28,     0,
    29,     0,    55,     0,    30,     0,    30,    54,   103,     0,
    30,    46,   122,     0,    16,   103,     0,    35,   122,     0,
    15,   122,     0,    18,   137,     0,    40,     0,    52,   130,
     0,   105,     0,   103,   105,     0,   103,     0,    43,     0,
    43,    44,   103,     0,   106,     0,    73,     0,    45,     0,
    23,     0,     0,     5,    97,     8,    97,   108,   110,    84,
     0,     0,     5,    73,   109,   110,    84,     0,     0,   110,
   111,     0,     9,   132,     0,    20,   135,     0,    10,     0,
    11,     0,    49,     0,    16,   103,     0,    35,   122,     0,
    15,   122,     0,    38,   104,     0,    31,   137,     0,    37,
   139,     0,    37,     8,   139,     0,    37,     6,   139,     0,
     7,    73,     0,    52,   130,     0,    21,     0,     0,    19,
    97,     8,    97,   113,   115,    84,     0,     0,    19,    73,
   114,   115,    84,     0,     0,   115,   116,     0,    20,   134,
     0,    20,   135,     0,    10,     0,    11,     0,    49,     0,
    16,   103,     0,    35,   122,     0,    15,   122,     0,    38,
   104,     0,    31,   137,     0,    37,   139,     0,    37,     8,
   139,     0,    37,     6,   139,     0,     7,    73,     0,    52,
   130,     0,     0,    14,   138,   118,   120,    84,     0,     0,
    14,    73,   119,   120,    84,     0,     0,   120,   121,     0,
     7,    73,     0,    15,   122,     0,    16,   103,     0,    41,
   103,     0,    17,   103,     0,    42,   104,     0,    42,   104,
    46,   122,     0,    42,   104,    68,    97,     0,    42,   104,
    68,    97,    46,   122,     0,    42,    68,    97,     0,    42,
    68,    97,    46,   122,     0,    42,    46,   122,     0,    33,
   103,     0,    25,    97,     0,    36,   124,     0,    68,    97,
     0,    68,    22,     0,    55,     0,    34,     0,    18,   137,
     0,    40,     0,    37,   139,     0,    37,    50,     0,    13,
   138,     0,    52,   130,     0,   123,     0,   122,   123,     0,
   124,     0,    73,     0,    45,     0,    23,     0,   126,     0,
   127,     0,    73,    75,   136,   128,    84,     0,    73,    73,
    75,   136,   128,    84,     0,    73,    75,    72,   128,    84,
     0,    73,    73,    75,    72,   128,    84,     0,    73,    75,
    39,   128,    84,     0,    73,    73,    75,    39,   128,    84,
     0,    73,    51,    73,    84,     0,    73,    51,    39,    84,
     0,     0,    68,    52,    73,     0,    68,    52,    12,     0,
    68,    52,    21,     0,    52,    73,    84,     0,    52,    12,
    84,     0,    52,    21,    84,     0,    53,    73,    84,     0,
    53,    12,    84,     0,    53,    21,    84,     0,    53,    84,
     0,   131,     0,   130,   131,     0,    73,     0,    12,     0,
    21,     0,   133,     0,   132,   133,     0,   134,     0,   134,
   137,     0,   134,    47,   137,     0,    58,     0,    59,     0,
    60,     0,    61,     0,    62,     0,    63,     0,    64,     0,
    65,     0,    68,     0,    69,     0,    66,     0,    67,     0,
    70,     0,    71,     0,    74,     0,    76,   136,     0,    77,
   136,     0,   136,    76,   136,     0,   136,    77,   136,     0,
   136,    78,   136,     0,   136,    79,   136,     0,   136,    83,
   136,     0,   136,    80,   136,     0,    85,   136,    86,     0,
   136,     0,    72,     0,    74,     0,   138,     0,   138,   137,
     0,   138,    47,   137,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   107,   108,   109,   112,   113,   114,   115,   116,   117,   118,
   119,   126,   130,   136,   150,   160,   255,   263,   269,   270,
   273,   280,   299,   314,   327,   342,   357,   361,   365,   369,
   373,   377,   381,   385,   389,   393,   397,   403,   407,   411,
   416,   421,   426,   430,   431,   437,   445,   446,   449,   457,
   461,   468,   481,   489,   498,   506,   512,   513,   516,   523,
   527,   531,   535,   540,   544,   548,   552,   556,   560,   564,
   568,   572,   576,   580,   583,   584,   587,   588,   589,   592,
   600,   604,   611,   624,   632,   637,   645,   651,   652,   655,
   660,   664,   668,   672,   676,   680,   684,   688,   694,   698,
   703,   708,   713,   720,   721,   733,   741,   746,   754,   760,
   761,   764,   768,   772,   776,   780,   784,   788,   792,   796,
   802,   806,   811,   816,   821,   828,   835,   842,   853,   861,
   867,   868,   871,   878,   882,   886,   890,   894,   900,   907,
   914,   922,   926,   931,   935,   939,   943,   947,   951,   955,
   959,   963,   967,   971,   976,   980,   984,   987,   988,   991,
   999,  1003,  1010,  1023,  1029,  1032,  1036,  1041,  1045,  1050,
  1054,  1061,  1065,  1071,  1072,  1077,  1082,  1093,  1097,  1101,
  1105,  1109,  1113,  1117,  1123,  1124,  1127,  1132,  1137,  1148,
  1149,  1152,  1158,  1167,  1179,  1180,  1181,  1182,  1183,  1184,
  1185,  1186,  1189,  1190,  1191,  1192,  1199,  1200,  1201,  1202,
  1203,  1204,  1205,  1206,  1207,  1208,  1209,  1210,  1213,  1216,
  1217,  1220,  1225,  1232
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ROOM","ITEM",
"LINK","FROM","TAG","TO","DIR","ONEWAY","HIDDEN","PUZZLE","NOTE","TASK","AFTER",
"NEED","GET","SCORE","JOIN","GO","SPECIAL","ANY","LAST","START","GOTO","MAP",
"EXIT","GIVEN","LOST","KEEP","LENGTH","TITLE","LOSE","SAFE","BEFORE","FOLLOW",
"CMD","LEAVE","UNDEF","FINISH","GIVE","DROP","ALL","EXCEPT","IT","UNTIL","TIMES",
"NOLINK","NOPATH","NONE","ALIAS","STYLE","ENDSTYLE","WITH","IGNORE","REQUIRE",
"NODROP","NORTH","EAST","SOUTH","WEST","NORTHEAST","NORTHWEST","SOUTHEAST","SOUTHWEST",
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
    87,    87,    87,    88,    88,    88,    88,    88,    88,    88,
    88,    89,    89,    89,    91,    90,    92,    90,    93,    93,
    94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
    94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
    94,    94,    94,    94,    94,    94,    95,    95,    96,    97,
    97,    97,    99,    98,   100,    98,   101,   101,   102,   102,
   102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
   102,   102,   102,   102,   103,   103,   104,   104,   104,   105,
   106,   106,   106,   108,   107,   109,   107,   110,   110,   111,
   111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
   111,   111,   111,   111,   111,   113,   112,   114,   112,   115,
   115,   116,   116,   116,   116,   116,   116,   116,   116,   116,
   116,   116,   116,   116,   116,   116,   118,   117,   119,   117,
   120,   120,   121,   121,   121,   121,   121,   121,   121,   121,
   121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
   121,   121,   121,   121,   121,   121,   121,   122,   122,   123,
   124,   124,   124,   125,   125,   126,   126,   126,   126,   126,
   126,   127,   127,   128,   128,   128,   128,   129,   129,   129,
   129,   129,   129,   129,   130,   130,   131,   131,   131,   132,
   132,   133,   133,   133,   134,   134,   134,   134,   134,   134,
   134,   134,   135,   135,   135,   135,   136,   136,   136,   136,
   136,   136,   136,   136,   136,   136,   136,   136,   137,   138,
   138,   139,   139,   139
};

static const short yyr2[] = {     0,
     0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
     1,     3,     3,     3,     0,     5,     0,     5,     0,     2,
     2,     4,     2,     2,     2,     2,     2,     1,     1,     1,
     1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
     3,     3,     2,     2,     1,     1,     1,     2,     1,     1,
     1,     1,     0,     5,     0,     5,     0,     2,     2,     2,
     2,     1,     1,     1,     1,     1,     3,     3,     2,     2,
     2,     2,     1,     2,     1,     2,     1,     1,     3,     1,
     1,     1,     1,     0,     7,     0,     5,     0,     2,     2,
     2,     1,     1,     1,     2,     2,     2,     2,     2,     2,
     3,     3,     2,     2,     1,     0,     7,     0,     5,     0,
     2,     2,     2,     1,     1,     1,     2,     2,     2,     2,
     2,     2,     3,     3,     2,     2,     0,     5,     0,     5,
     0,     2,     2,     2,     2,     2,     2,     2,     4,     4,
     6,     3,     5,     3,     2,     2,     2,     2,     2,     1,
     1,     2,     1,     2,     2,     2,     2,     1,     2,     1,
     1,     1,     1,     1,     1,     5,     6,     5,     6,     5,
     6,     4,     4,     0,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     2,     1,     2,     1,     1,     1,     1,
     2,     1,     2,     3,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
     2,     3,     3,     3,     3,     3,     3,     3,     1,     1,
     1,     1,     2,     3
};

static const short yydefact[] = {     1,
     0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     2,     4,     5,     6,     7,     8,     9,
    10,   164,   165,    11,   220,    17,   221,    15,    55,    53,
    52,    51,    86,     0,   129,   127,   108,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   184,   207,   208,   209,
     0,     0,     0,     0,     0,     0,     0,    19,    19,    57,
    57,    88,     0,   131,   131,   110,     0,    13,    12,   179,
   180,   178,   182,   183,   181,   210,   211,     0,     0,     0,
     0,     0,     0,     0,    14,     0,     0,     0,   174,   174,
   174,     0,     0,     0,     0,     0,    50,    84,     0,     0,
     0,   106,   218,   212,   213,   214,   215,   217,   216,   173,
   172,   174,   174,   174,     0,     0,     0,     0,     0,     0,
     0,    28,    46,     0,     0,     0,     0,     0,     0,    45,
    32,     0,     0,     0,     0,     0,    33,    30,    31,     0,
    29,    18,    20,    16,     0,    62,     0,     0,     0,     0,
    63,    64,    66,     0,    73,     0,    65,     0,    56,    58,
    54,     0,     0,    92,    93,     0,     0,     0,   105,     0,
     0,     0,     0,    94,     0,    87,    89,    88,     0,     0,
     0,     0,     0,     0,     0,     0,   151,     0,     0,   153,
     0,     0,     0,   150,     0,   130,   132,   128,     0,   114,
   115,     0,     0,     0,     0,     0,     0,     0,   116,     0,
   109,   111,   110,     0,     0,     0,     0,   170,   168,   166,
    25,    47,    49,    21,   195,   196,   197,   198,   199,   200,
   201,   202,    23,   190,   192,    43,   163,   162,   161,    36,
   158,   160,    83,    82,    81,    34,    75,    80,   219,    39,
    26,   205,   206,   203,   204,    27,    24,    38,    35,     0,
     0,   222,    40,    78,    77,    37,   188,   189,   187,    44,
   185,    59,    61,    71,    69,    72,     0,     0,    70,    74,
    60,   103,    90,    97,    95,    91,    99,    96,     0,     0,
   100,    98,   104,     0,   133,   156,   134,   135,   137,   152,
   146,   145,   147,   155,   154,   136,     0,     0,   138,   157,
   149,   148,   125,   119,   117,   112,   113,   121,   118,     0,
     0,   122,   120,   126,     0,   171,   169,   167,   176,   177,
   175,    48,     0,   191,     0,   193,   159,    76,    42,    41,
     0,   223,     0,   186,    68,    67,   102,   101,    85,   144,
   142,     0,     0,   124,   123,   107,    22,   194,   224,    79,
     0,   139,   140,   143,     0,   141,     0,     0
};

static const short yydefgoto[] = {     1,
    14,    15,    16,    59,    58,    92,   143,   221,   222,   223,
    17,    61,    60,    94,   160,   265,   266,   247,   248,    18,
   178,    62,    96,   177,    19,   213,    66,   101,   212,    20,
    65,    64,    99,   197,   240,   241,   242,    21,    22,    23,
   116,    24,   270,   271,   233,   234,   235,   256,   249,   250,
   262,   263
};

static const short yypact[] = {-32768,
   569,-32768,   138,   180,    67,   237,    98,    48,    48,    18,
    -2,   415,    79,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    15,    26,-32768,-32768,    15,    33,   -67,     5,
    20,    40,    57,    58,    61,    63,-32768,-32768,-32768,-32768,
   415,   415,   415,   540,     1,     4,   454,-32768,-32768,-32768,
-32768,-32768,   106,-32768,-32768,-32768,   106,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,    34,    34,   457,   415,   415,
   415,   415,   415,   415,-32768,    75,    77,   476,   100,   100,
   217,   157,   224,   342,   373,   423,-32768,-32768,   250,   299,
   507,-32768,-32768,   191,   191,    34,    34,    34,    34,-32768,
-32768,   100,   100,   217,   133,   105,   107,   112,   106,   120,
   574,-32768,-32768,    48,   113,   142,   415,   106,   211,-32768,
-32768,   574,   415,   113,    12,     8,-32768,-32768,-32768,    43,
-32768,-32768,-32768,-32768,   125,-32768,    48,   113,   142,   415,
-32768,-32768,   -30,   113,-32768,    43,-32768,   106,-32768,-32768,
-32768,   130,   574,-32768,-32768,   113,   142,   211,-32768,   415,
   113,    21,     8,-32768,    43,-32768,-32768,-32768,   131,    48,
   113,   142,   142,   415,   106,   142,-32768,   113,   152,-32768,
   142,    65,    43,-32768,    27,-32768,-32768,-32768,   135,-32768,
-32768,   113,   142,   544,   415,   113,    29,     8,-32768,    43,
-32768,-32768,-32768,   132,   134,   141,    55,-32768,-32768,-32768,
   106,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   405,-32768,   252,-32768,-32768,-32768,-32768,   113,
-32768,-32768,-32768,-32768,-32768,   142,-32768,-32768,   267,-32768,
   106,-32768,-32768,-32768,-32768,-32768,   574,-32768,   113,    48,
    48,   322,-32768,   183,   142,-32768,-32768,-32768,-32768,    43,
-32768,-32768,-32768,   113,   142,-32768,   113,   142,   113,    43,
-32768,-32768,   574,   113,   142,-32768,-32768,   113,    48,    48,
-32768,-32768,    43,   467,-32768,-32768,   113,   142,   142,-32768,
-32768,   142,-32768,-32768,-32768,   142,   113,   106,    37,    43,
-32768,-32768,-32768,   113,   142,-32768,-32768,-32768,   113,    48,
    48,-32768,-32768,    43,   547,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   162,-32768,   415,-32768,-32768,-32768,-32768,-32768,
   415,-32768,   142,-32768,   113,   142,-32768,-32768,-32768,   113,
   184,   113,   106,-32768,-32768,-32768,-32768,-32768,-32768,   142,
   113,   113,   192,   113,   113,   113,   246,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,   188,-32768,   121,  -185,    -5,
-32768,-32768,-32768,   189,-32768,  -123,     9,  -200,-32768,-32768,
-32768,-32768,    78,-32768,-32768,-32768,-32768,    45,-32768,-32768,
-32768,-32768,   195,-32768,  -133,  -227,    94,-32768,-32768,-32768,
   109,-32768,   -62,  -161,  -118,  -229,    84,   -90,   367,  -128,
     3,  -164
};


#define	YYLAST		642


static const short yytable[] = {    34,
   259,    38,   246,   334,   258,    28,    30,   291,    36,    44,
    39,    40,   337,   257,   274,   277,    68,   260,    45,   261,
   279,   276,   -50,   278,   305,   275,   289,   334,   290,    41,
   243,   337,   284,    63,   320,   332,   321,   288,    42,    86,
    67,   287,   322,   285,   283,   338,   337,   297,   311,    31,
   264,   337,   244,   334,   267,   300,   337,    98,   298,   299,
   337,   102,   302,   268,   338,   332,   329,   306,   314,   337,
    46,    32,   319,    87,   338,   330,   318,   286,    88,   315,
   245,    47,   352,    25,   338,    27,   337,   243,    69,    31,
    43,   337,    25,   280,    27,   339,   340,   338,   338,    97,
    25,   338,    27,    70,   353,   338,   336,   264,   344,   244,
   307,    32,   293,   317,   338,   269,    84,   337,   344,    25,
    31,    27,   337,    71,   347,   348,   236,   331,    31,    55,
   310,   344,   308,   342,   337,   237,   337,   245,   337,    33,
    72,    73,    32,   345,    74,   338,    75,   324,   344,   273,
    32,    56,   281,    57,   346,   354,   355,   238,   110,   338,
   111,   119,   344,   120,   243,   121,   122,   115,   123,   124,
    37,   125,   126,   350,   127,   128,   129,   130,    97,   301,
   131,   292,   296,   132,   217,   239,   244,   133,   218,   312,
   219,   134,   224,   135,   136,   220,   137,   272,   117,   118,
   309,   304,   282,   295,   138,   139,   358,   313,   140,    25,
    26,    27,   359,   141,   245,   326,   323,   327,   362,   360,
   214,   215,   216,    25,   328,    27,   343,   364,   119,   361,
   120,   366,   121,   122,   357,   123,   124,   365,   125,   126,
   142,   127,   128,   129,   130,   368,    93,   131,   251,    95,
   132,    25,    29,    27,   133,   294,   179,   325,   134,   100,
   135,   136,   180,   137,   181,   182,   183,   184,    81,    82,
    83,   138,   139,    84,   185,   140,   252,   253,   254,   255,
   141,   303,   186,   187,   115,   188,   189,   316,     0,   190,
   191,   192,    79,    80,    81,    82,    83,     0,   335,    84,
     0,   193,   351,     0,   194,   179,     0,   144,    25,    35,
    27,   180,     0,   181,   182,   183,   184,   195,     0,     0,
     0,    48,    49,   185,     0,    50,     0,    51,    52,     0,
     0,   186,   187,   196,   188,   189,    53,     0,   190,   191,
   192,     0,    79,    80,    81,    82,    83,   363,   145,    84,
   193,     0,   146,   194,   147,     0,   148,   149,     0,   150,
     0,     0,     0,     0,     0,     0,   195,     0,   341,   151,
   152,   153,     0,     0,     0,     0,   154,     0,    54,   145,
     0,   155,   198,   146,     0,   147,     0,   148,   149,     0,
   150,    48,    49,   156,     0,    50,   157,    51,    52,     0,
   151,   152,   153,     0,     0,     0,    53,   154,     0,   158,
   333,     0,   155,     0,     0,     0,     0,    76,    77,    78,
     0,     0,     0,    91,   156,   159,     0,   157,     0,   162,
     0,   163,   164,   165,     0,     0,     0,   166,   167,     0,
   158,     0,   168,   169,     0,   104,   105,   106,   107,   108,
   109,     0,     0,   170,   114,     0,   161,   171,     0,   172,
   173,     0,   225,   226,   227,   228,   229,   230,   231,   232,
     0,   174,     0,   162,   175,   163,   164,   165,     0,     0,
     0,   166,   167,     0,    48,    49,   168,   169,    50,     0,
    51,    52,    89,     0,     0,     0,     0,   170,     0,    53,
     0,   171,     0,   172,   173,     0,   176,     0,     0,     0,
     0,     0,     0,   199,   112,   174,   200,   201,   175,     0,
     0,   202,   203,    48,    49,    90,   204,    50,     0,    51,
    52,     0,    79,    80,    81,    82,    83,   205,    53,    84,
     0,   206,   103,   207,   208,    48,    49,   113,     0,    50,
   349,    51,    52,   199,     0,   209,   200,   201,   210,     0,
    53,   202,   203,     0,     0,     0,   204,     0,   367,     2,
     0,     3,     4,     5,     0,     0,     0,   205,     0,     0,
     0,   206,     6,   207,   208,     0,     0,     7,     0,     0,
   211,     0,     0,     0,     8,   209,     0,     0,   210,     0,
     9,   225,   226,   227,   228,   229,   230,   231,   232,   252,
   253,   254,   255,     0,     0,    79,    80,    81,    82,    83,
    10,    11,    84,    85,    12,     0,     0,     0,     0,     0,
   356,   225,   226,   227,   228,   229,   230,   231,   232,     0,
     0,    13
};

static const short yycheck[] = {     5,
   134,     7,   126,   233,   133,     3,     4,   172,     6,    12,
     8,     9,   240,   132,   148,    46,    84,     6,    21,     8,
   154,   150,     8,    54,   189,   149,     6,   257,     8,    12,
    23,   259,   166,     8,     6,   221,     8,   171,    21,    39,
     8,   170,   207,   167,   163,   246,   274,   181,    22,    23,
    43,   279,    45,   283,    12,   184,   284,    63,   182,   183,
   288,    67,   186,    21,   265,   251,    12,   191,   202,   297,
    73,    45,   206,    73,   275,    21,   205,   168,    75,   203,
    73,    84,    46,    72,   285,    74,   314,    23,    84,    23,
    73,   319,    72,   156,    74,   260,   261,   298,   299,    73,
    72,   302,    74,    84,    68,   306,   235,    43,   270,    45,
    46,    45,   175,   204,   315,    73,    83,   345,   280,    72,
    23,    74,   350,    84,   289,   290,   124,    73,    23,    51,
   193,   293,    68,   262,   362,    23,   364,    73,   366,    73,
    84,    84,    45,   277,    84,   346,    84,   210,   310,   147,
    45,    73,   158,    75,   278,   320,   321,    45,    84,   360,
    84,     5,   324,     7,    23,     9,    10,    68,    12,    13,
    73,    15,    16,   307,    18,    19,    20,    21,    73,   185,
    24,   173,   180,    27,    52,    73,    45,    31,    84,   195,
    84,    35,    73,    37,    38,    84,    40,    73,    90,    91,
   192,    50,    73,    73,    48,    49,   335,    73,    52,    72,
    73,    74,   341,    57,    73,    84,   208,    84,   352,   343,
   112,   113,   114,    72,    84,    74,    44,   361,     5,    46,
     7,   365,     9,    10,    73,    12,    13,    46,    15,    16,
    84,    18,    19,    20,    21,     0,    59,    24,   128,    61,
    27,    72,    73,    74,    31,   178,     7,   213,    35,    65,
    37,    38,    13,    40,    15,    16,    17,    18,    78,    79,
    80,    48,    49,    83,    25,    52,    66,    67,    68,    69,
    57,   188,    33,    34,    68,    36,    37,   204,    -1,    40,
    41,    42,    76,    77,    78,    79,    80,    -1,    47,    83,
    -1,    52,   308,    -1,    55,     7,    -1,    84,    72,    73,
    74,    13,    -1,    15,    16,    17,    18,    68,    -1,    -1,
    -1,    70,    71,    25,    -1,    74,    -1,    76,    77,    -1,
    -1,    33,    34,    84,    36,    37,    85,    -1,    40,    41,
    42,    -1,    76,    77,    78,    79,    80,   353,     7,    83,
    52,    -1,    11,    55,    13,    -1,    15,    16,    -1,    18,
    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    47,    28,
    29,    30,    -1,    -1,    -1,    -1,    35,    -1,    12,     7,
    -1,    40,    84,    11,    -1,    13,    -1,    15,    16,    -1,
    18,    70,    71,    52,    -1,    74,    55,    76,    77,    -1,
    28,    29,    30,    -1,    -1,    -1,    85,    35,    -1,    68,
     6,    -1,    40,    -1,    -1,    -1,    -1,    51,    52,    53,
    -1,    -1,    -1,    57,    52,    84,    -1,    55,    -1,     7,
    -1,     9,    10,    11,    -1,    -1,    -1,    15,    16,    -1,
    68,    -1,    20,    21,    -1,    79,    80,    81,    82,    83,
    84,    -1,    -1,    31,    88,    -1,    84,    35,    -1,    37,
    38,    -1,    58,    59,    60,    61,    62,    63,    64,    65,
    -1,    49,    -1,     7,    52,     9,    10,    11,    -1,    -1,
    -1,    15,    16,    -1,    70,    71,    20,    21,    74,    -1,
    76,    77,    39,    -1,    -1,    -1,    -1,    31,    -1,    85,
    -1,    35,    -1,    37,    38,    -1,    84,    -1,    -1,    -1,
    -1,    -1,    -1,     7,    39,    49,    10,    11,    52,    -1,
    -1,    15,    16,    70,    71,    72,    20,    74,    -1,    76,
    77,    -1,    76,    77,    78,    79,    80,    31,    85,    83,
    -1,    35,    86,    37,    38,    70,    71,    72,    -1,    74,
    84,    76,    77,     7,    -1,    49,    10,    11,    52,    -1,
    85,    15,    16,    -1,    -1,    -1,    20,    -1,     0,     1,
    -1,     3,     4,     5,    -1,    -1,    -1,    31,    -1,    -1,
    -1,    35,    14,    37,    38,    -1,    -1,    19,    -1,    -1,
    84,    -1,    -1,    -1,    26,    49,    -1,    -1,    52,    -1,
    32,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    -1,    -1,    76,    77,    78,    79,    80,
    52,    53,    83,    84,    56,    -1,    -1,    -1,    -1,    -1,
    84,    58,    59,    60,    61,    62,    63,    64,    65,    -1,
    -1,    73
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
#line 256 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(roomtags, yyvsp[0].sval)) == NULL) {
                        err("room tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 18:
#line 264 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 21:
#line 274 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("room", yyvsp[0].sval, curobj, roomtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 22:
#line 281 "ifm-parse.y"
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
#line 300 "ifm-parse.y"
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
#line 315 "ifm-parse.y"
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
#line 328 "ifm-parse.y"
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
#line 343 "ifm-parse.y"
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
#line 358 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 28:
#line 362 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 29:
#line 366 "ifm-parse.y"
{
                    vh_istore(curobj, "NODROP", 1);
		;
    break;}
case 30:
#line 370 "ifm-parse.y"
{
                    vh_istore(curobj, "NOLINK", 1);
		;
    break;}
case 31:
#line 374 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 32:
#line 378 "ifm-parse.y"
{
                    startroom = curobj;
		;
    break;}
case 33:
#line 382 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 34:
#line 386 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(NEED), curitems);
                ;
    break;}
case 35:
#line 390 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		;
    break;}
case 36:
#line 394 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		;
    break;}
case 37:
#line 398 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                ;
    break;}
case 38:
#line 404 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 39:
#line 408 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 40:
#line 412 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 41:
#line 417 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 42:
#line 422 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 43:
#line 427 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 45:
#line 432 "ifm-parse.y"
{
                    obsolete("`special' attribute", "`style special'");
                    add_attr(curobj, ATTR(STYLE), "special");
                    ref_style("special");
		;
    break;}
case 46:
#line 438 "ifm-parse.y"
{
                    obsolete("`puzzle' attribute", "`style puzzle'");
                    add_attr(curobj, ATTR(STYLE), "puzzle");
                    ref_style("puzzle");
		;
    break;}
case 49:
#line 450 "ifm-parse.y"
{
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, yyvsp[0].vval);
		;
    break;}
case 50:
#line 458 "ifm-parse.y"
{
                    yyval.vval = itroom = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 51:
#line 462 "ifm-parse.y"
{
                    if (itroom == NULL)
                        err("no room referred to by `it'");
                    else
                        yyval.vval = vs_copy(itroom);
                ;
    break;}
case 52:
#line 469 "ifm-parse.y"
{
                    if (lastroom == NULL)
                        err("no room referred to by `last'");
                    else
                        yyval.vval = itroom = vs_pcreate(lastroom);
                ;
    break;}
case 53:
#line 482 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_istore(curobj, "ID", ++itemid);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 54:
#line 490 "ifm-parse.y"
{
                    if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lastitem = curobj;
                    vl_ppush(items, curobj);
                    RESET_IT;
		;
    break;}
case 55:
#line 499 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(itemtags, yyvsp[0].sval)) == NULL) {
                        err("item tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 56:
#line 507 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 59:
#line 517 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("item", yyvsp[0].sval, curobj, itemtags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 60:
#line 524 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 61:
#line 528 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 62:
#line 532 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 63:
#line 536 "ifm-parse.y"
{
                    obsolete("`given' attribute", "task `give' attribute");
                    vh_istore(curobj, "GIVEN", 1);
		;
    break;}
case 64:
#line 541 "ifm-parse.y"
{
                    vh_istore(curobj, "LOST", 1);
		;
    break;}
case 65:
#line 545 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 66:
#line 549 "ifm-parse.y"
{
                    vh_istore(curobj, "KEEP", 1);
		;
    break;}
case 67:
#line 553 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_WITH", curitems);
		;
    break;}
case 68:
#line 557 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_UNTIL", curtasks);
		;
    break;}
case 69:
#line 561 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 70:
#line 565 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
                ;
    break;}
case 71:
#line 569 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
                ;
    break;}
case 72:
#line 573 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 73:
#line 577 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 77:
#line 587 "ifm-parse.y"
{ allflag = 0; ;
    break;}
case 78:
#line 588 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 79:
#line 589 "ifm-parse.y"
{ allflag = 1; ;
    break;}
case 80:
#line 593 "ifm-parse.y"
{
                    if (curitems == NULL)
                        curitems = vl_create();
                    vl_push(curitems, yyvsp[0].vval);
		;
    break;}
case 81:
#line 601 "ifm-parse.y"
{
                    yyval.vval = ititem = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 82:
#line 605 "ifm-parse.y"
{
                    if (ititem == NULL)
                        err("no item referred to by `it'");
                    else
                        yyval.vval = vs_copy(ititem);
                ;
    break;}
case 83:
#line 612 "ifm-parse.y"
{
                    if (lastitem == NULL)
                        err("no item referred to by `last'");
                    else
                        yyval.vval = ititem = vs_pcreate(lastitem);
                ;
    break;}
case 84:
#line 625 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 85:
#line 633 "ifm-parse.y"
{
                    vl_ppush(links, curobj);
                    RESET_IT;
		;
    break;}
case 86:
#line 638 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(linktags, yyvsp[0].sval)) == NULL) {
                        err("link tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 87:
#line 646 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 90:
#line 656 "ifm-parse.y"
{
                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;
		;
    break;}
case 91:
#line 661 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 92:
#line 665 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 93:
#line 669 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 94:
#line 673 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 95:
#line 677 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 96:
#line 681 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 97:
#line 685 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 98:
#line 689 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 99:
#line 695 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 100:
#line 699 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 101:
#line 704 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 102:
#line 709 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 103:
#line 714 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("link", yyvsp[0].sval, curobj, linktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 105:
#line 722 "ifm-parse.y"
{
                    obsolete("`special' attribute", "`style special'");
                    add_attr(curobj, "STYLE", "special");
                    ref_style("special");
		;
    break;}
case 106:
#line 734 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 107:
#line 742 "ifm-parse.y"
{
                    vl_ppush(joins, curobj);
                    RESET_IT;
		;
    break;}
case 108:
#line 747 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(jointags, yyvsp[0].sval)) == NULL) {
                        err("join tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 109:
#line 755 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 112:
#line 765 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 113:
#line 769 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		;
    break;}
case 114:
#line 773 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		;
    break;}
case 115:
#line 777 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		;
    break;}
case 116:
#line 781 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		;
    break;}
case 117:
#line 785 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                ;
    break;}
case 118:
#line 789 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		;
    break;}
case 119:
#line 793 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 120:
#line 797 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                ;
    break;}
case 121:
#line 803 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		;
    break;}
case 122:
#line 807 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 123:
#line 812 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                ;
    break;}
case 124:
#line 817 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                ;
    break;}
case 125:
#line 822 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("join", yyvsp[0].sval, curobj, jointags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 127:
#line 836 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                ;
    break;}
case 128:
#line 843 "ifm-parse.y"
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
case 129:
#line 854 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(tasktags, yyvsp[0].sval)) == NULL) {
                        err("task tag `%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                ;
    break;}
case 130:
#line 862 "ifm-parse.y"
{
                    RESET_IT;
                ;
    break;}
case 133:
#line 872 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("task", yyvsp[0].sval, curobj, tasktags);
                    else
                        CHANGE_ERROR(tag);
		;
    break;}
case 134:
#line 879 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		;
    break;}
case 135:
#line 883 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
		;
    break;}
case 136:
#line 887 "ifm-parse.y"
{
                    SET_LIST(curobj, "GIVE", curitems);
		;
    break;}
case 137:
#line 891 "ifm-parse.y"
{
                    SET_LIST(curobj, "GET", curitems);
		;
    break;}
case 138:
#line 895 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
		;
    break;}
case 139:
#line 901 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 140:
#line 908 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 141:
#line 915 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 142:
#line 923 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		;
    break;}
case 143:
#line 927 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		;
    break;}
case 144:
#line 932 "ifm-parse.y"
{
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
                ;
    break;}
case 145:
#line 936 "ifm-parse.y"
{
                    SET_LIST(curobj, "LOSE", curitems);
		;
    break;}
case 146:
#line 940 "ifm-parse.y"
{
                    vh_store(curobj, "GOTO", yyvsp[0].vval);
                ;
    break;}
case 147:
#line 944 "ifm-parse.y"
{
                    vh_store(curobj, "FOLLOW", yyvsp[0].vval);
                ;
    break;}
case 148:
#line 948 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		;
    break;}
case 149:
#line 952 "ifm-parse.y"
{
                    vh_istore(curobj, "NOROOM", 1);
		;
    break;}
case 150:
#line 956 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		;
    break;}
case 151:
#line 960 "ifm-parse.y"
{
                    vh_istore(curobj, "SAFE", 1);
                ;
    break;}
case 152:
#line 964 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		;
    break;}
case 153:
#line 968 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                ;
    break;}
case 154:
#line 972 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", yyvsp[0].sval);
                ;
    break;}
case 155:
#line 977 "ifm-parse.y"
{
                    add_attr(curobj, "CMD", NULL);
                ;
    break;}
case 156:
#line 981 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		;
    break;}
case 160:
#line 992 "ifm-parse.y"
{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, yyvsp[0].vval);
		;
    break;}
case 161:
#line 1000 "ifm-parse.y"
{
                    yyval.vval = ittask = vs_screate(yyvsp[0].sval);
                ;
    break;}
case 162:
#line 1004 "ifm-parse.y"
{
                    if (ittask == NULL)
                        err("no task referred to by `it'");
                    else
                        yyval.vval = vs_copy(ittask);
                ;
    break;}
case 163:
#line 1011 "ifm-parse.y"
{
                    if (lasttask == NULL)
                        err("no task referred to by `last'");
                    else
                        yyval.vval = ittask = vs_pcreate(lasttask);
                ;
    break;}
case 164:
#line 1024 "ifm-parse.y"
{
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                ;
    break;}
case 166:
#line 1033 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                ;
    break;}
case 167:
#line 1037 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 168:
#line 1042 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                ;
    break;}
case 169:
#line 1046 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 170:
#line 1051 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, NULL);
                ;
    break;}
case 171:
#line 1055 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, NULL);
                    obsolete("variable assignment", "dotted notation");
                ;
    break;}
case 172:
#line 1062 "ifm-parse.y"
{
                    var_alias(yyvsp[-3].sval, yyvsp[-1].sval);
                ;
    break;}
case 173:
#line 1066 "ifm-parse.y"
{
                    var_alias(yyvsp[-3].sval, NULL);
                ;
    break;}
case 175:
#line 1073 "ifm-parse.y"
{
                    push_style(yyvsp[0].sval);
                    instyle++;
                ;
    break;}
case 176:
#line 1078 "ifm-parse.y"
{
                    push_style("puzzle");
                    instyle++;
                ;
    break;}
case 177:
#line 1083 "ifm-parse.y"
{
                    push_style("special");
                    instyle++;
                ;
    break;}
case 178:
#line 1094 "ifm-parse.y"
{
                    push_style(yyvsp[-1].sval);
                ;
    break;}
case 179:
#line 1098 "ifm-parse.y"
{
                    push_style("puzzle");
                ;
    break;}
case 180:
#line 1102 "ifm-parse.y"
{
                    push_style("special");
                ;
    break;}
case 181:
#line 1106 "ifm-parse.y"
{
                    pop_style(yyvsp[-1].sval);
                ;
    break;}
case 182:
#line 1110 "ifm-parse.y"
{
                    pop_style("puzzle");
                ;
    break;}
case 183:
#line 1114 "ifm-parse.y"
{
                    pop_style("special");
                ;
    break;}
case 184:
#line 1118 "ifm-parse.y"
{
                    pop_style(NULL);
                ;
    break;}
case 187:
#line 1128 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", yyvsp[0].sval);
                    ref_style(yyvsp[0].sval);
                ;
    break;}
case 188:
#line 1133 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", "puzzle");
                    ref_style("puzzle");
                ;
    break;}
case 189:
#line 1138 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", "special");
                    ref_style("special");
                ;
    break;}
case 192:
#line 1153 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, yyvsp[0].ival);
		;
    break;}
case 193:
#line 1159 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-1].ival);
                ;
    break;}
case 194:
#line 1168 "ifm-parse.y"
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
case 195:
#line 1179 "ifm-parse.y"
{ yyval.ival = D_NORTH;	    ;
    break;}
case 196:
#line 1180 "ifm-parse.y"
{ yyval.ival = D_EAST;	    ;
    break;}
case 197:
#line 1181 "ifm-parse.y"
{ yyval.ival = D_SOUTH;	    ;
    break;}
case 198:
#line 1182 "ifm-parse.y"
{ yyval.ival = D_WEST;	    ;
    break;}
case 199:
#line 1183 "ifm-parse.y"
{ yyval.ival = D_NORTHEAST; ;
    break;}
case 200:
#line 1184 "ifm-parse.y"
{ yyval.ival = D_NORTHWEST; ;
    break;}
case 201:
#line 1185 "ifm-parse.y"
{ yyval.ival = D_SOUTHEAST; ;
    break;}
case 202:
#line 1186 "ifm-parse.y"
{ yyval.ival = D_SOUTHWEST; ;
    break;}
case 203:
#line 1189 "ifm-parse.y"
{ yyval.ival = D_IN;   ;
    break;}
case 204:
#line 1190 "ifm-parse.y"
{ yyval.ival = D_OUT;  ;
    break;}
case 205:
#line 1191 "ifm-parse.y"
{ yyval.ival = D_UP;   ;
    break;}
case 206:
#line 1192 "ifm-parse.y"
{ yyval.ival = D_DOWN; ;
    break;}
case 207:
#line 1199 "ifm-parse.y"
{ yyval.dval = yyvsp[0].ival; ;
    break;}
case 208:
#line 1200 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 209:
#line 1201 "ifm-parse.y"
{ yyval.dval = var_real(yyvsp[0].sval); ;
    break;}
case 210:
#line 1202 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 211:
#line 1203 "ifm-parse.y"
{ yyval.dval = -yyvsp[0].dval; ;
    break;}
case 212:
#line 1204 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval + yyvsp[0].dval; ;
    break;}
case 213:
#line 1205 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval - yyvsp[0].dval; ;
    break;}
case 214:
#line 1206 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval * yyvsp[0].dval; ;
    break;}
case 215:
#line 1207 "ifm-parse.y"
{ yyval.dval = yyvsp[-2].dval / yyvsp[0].dval; ;
    break;}
case 216:
#line 1208 "ifm-parse.y"
{ yyval.dval = pow(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 217:
#line 1209 "ifm-parse.y"
{ yyval.dval = fmod(yyvsp[-2].dval, yyvsp[0].dval); ;
    break;}
case 218:
#line 1210 "ifm-parse.y"
{ yyval.dval = yyvsp[-1].dval; ;
    break;}
case 219:
#line 1213 "ifm-parse.y"
{ yyval.ival = (int) yyvsp[0].dval; ;
    break;}
case 220:
#line 1216 "ifm-parse.y"
{ yyval.sval = yyvsp[0].sval; ;
    break;}
case 221:
#line 1217 "ifm-parse.y"
{ yyval.sval = var_string(yyvsp[0].sval); ;
    break;}
case 222:
#line 1221 "ifm-parse.y"
{
                    yyval.sval = yyvsp[0].sval;
                    repeat = 1;
                ;
    break;}
case 223:
#line 1226 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-1].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                ;
    break;}
case 224:
#line 1233 "ifm-parse.y"
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
#line 1242 "ifm-parse.y"

