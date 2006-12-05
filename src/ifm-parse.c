/* A Bison parser, made from ifm-parse.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

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
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		326
#define	YYFLAG		-32768
#define	YYNTBASE	74

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 325 ? yytranslate[x] : 124)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    72,
       2,    73,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    27,    31,    35,    36,    42,    43,    49,
      50,    53,    56,    61,    64,    67,    70,    73,    76,    78,
      80,    82,    84,    86,    88,    91,    94,    97,   100,   103,
     106,   109,   113,   117,   120,   123,   125,   128,   130,   132,
     134,   136,   137,   143,   144,   150,   151,   154,   157,   160,
     163,   165,   167,   169,   171,   173,   177,   181,   184,   187,
     190,   193,   195,   198,   200,   203,   205,   207,   211,   213,
     215,   217,   219,   220,   228,   229,   235,   236,   239,   242,
     245,   247,   249,   251,   254,   257,   260,   263,   266,   269,
     273,   277,   280,   283,   284,   292,   293,   299,   300,   303,
     306,   309,   311,   313,   315,   318,   321,   324,   327,   330,
     333,   337,   341,   344,   347,   348,   354,   355,   361,   362,
     365,   368,   371,   374,   377,   380,   383,   386,   391,   396,
     403,   407,   413,   417,   420,   423,   426,   429,   432,   434,
     436,   439,   441,   444,   447,   450,   453,   455,   458,   460,
     462,   464,   466,   468,   474,   481,   487,   494,   500,   507,
     508,   512,   516,   520,   523,   525,   528,   530,   532,   535,
     537,   540,   544,   546,   548,   550,   552,   554,   556,   558,
     560,   562,   564,   566,   568,   570,   572,   574,   577
};
static const short yyrhs[] =
{
      -1,    74,    75,     0,    74,     1,     0,    76,     0,    77,
       0,    85,     0,    94,     0,    99,     0,   104,     0,   112,
       0,   115,     0,    32,    70,    72,     0,    26,    70,    72,
       0,    21,   122,    72,     0,     0,     3,    70,    78,    80,
      72,     0,     0,     3,    71,    79,    80,    72,     0,     0,
      80,    81,     0,     7,    71,     0,     9,   118,     6,    71,
       0,     9,   118,     0,    27,   118,     0,     5,    82,     0,
      19,    82,     0,    20,   121,     0,    10,     0,    12,     0,
      48,     0,    49,     0,    24,     0,    40,     0,    16,    90,
       0,    35,   109,     0,    15,   109,     0,    38,    91,     0,
      31,    68,     0,    18,    68,     0,    37,   123,     0,    37,
       8,   123,     0,    37,     6,   123,     0,    13,    70,     0,
      51,   116,     0,    83,     0,    82,    83,     0,    84,     0,
      71,     0,    45,     0,    23,     0,     0,     4,    70,    86,
      88,    72,     0,     0,     4,    71,    87,    88,    72,     0,
       0,    88,    89,     0,     7,    71,     0,    66,    84,     0,
      13,    70,     0,    11,     0,    28,     0,    29,     0,    54,
       0,    30,     0,    30,    53,    90,     0,    30,    46,   109,
       0,    16,    90,     0,    35,   109,     0,    15,   109,     0,
      18,    68,     0,    40,     0,    51,   116,     0,    92,     0,
      90,    92,     0,    90,     0,    43,     0,    43,    44,    90,
       0,    93,     0,    71,     0,    45,     0,    23,     0,     0,
       5,    84,     8,    84,    95,    97,    72,     0,     0,     5,
      71,    96,    97,    72,     0,     0,    97,    98,     0,     9,
     118,     0,    20,   121,     0,    10,     0,    11,     0,    49,
       0,    16,    90,     0,    35,   109,     0,    15,   109,     0,
      38,    91,     0,    31,    68,     0,    37,   123,     0,    37,
       8,   123,     0,    37,     6,   123,     0,     7,    71,     0,
      51,   116,     0,     0,    19,    84,     8,    84,   100,   102,
      72,     0,     0,    19,    71,   101,   102,    72,     0,     0,
     102,   103,     0,    20,   120,     0,    20,   121,     0,    10,
       0,    11,     0,    49,     0,    16,    90,     0,    35,   109,
       0,    15,   109,     0,    38,    91,     0,    31,    68,     0,
      37,   123,     0,    37,     8,   123,     0,    37,     6,   123,
       0,     7,    71,     0,    51,   116,     0,     0,    14,    70,
     105,   107,    72,     0,     0,    14,    71,   106,   107,    72,
       0,     0,   107,   108,     0,     7,    71,     0,    15,   109,
       0,    16,    90,     0,    41,    90,     0,    17,    90,     0,
      55,   109,     0,    42,    91,     0,    42,    91,    46,   109,
       0,    42,    91,    66,    84,     0,    42,    91,    66,    84,
      46,   109,     0,    42,    66,    84,     0,    42,    66,    84,
      46,   109,     0,    42,    46,   109,     0,    33,    90,     0,
      25,    84,     0,    36,   111,     0,    66,    84,     0,    66,
      22,     0,    54,     0,    34,     0,    18,    68,     0,    40,
       0,    37,   123,     0,    37,    50,     0,    13,    70,     0,
      51,   116,     0,   110,     0,   109,   110,     0,   111,     0,
      71,     0,    45,     0,    23,     0,   113,     0,    71,    73,
     122,   114,    72,     0,    71,    71,    73,   122,   114,    72,
       0,    71,    73,    70,   114,    72,     0,    71,    71,    73,
      70,   114,    72,     0,    71,    73,    39,   114,    72,     0,
      71,    71,    73,    39,   114,    72,     0,     0,    66,    51,
      71,     0,    51,    71,    72,     0,    52,    71,    72,     0,
      52,    72,     0,   117,     0,   116,   117,     0,    71,     0,
     119,     0,   118,   119,     0,   120,     0,   120,    68,     0,
     120,    47,    68,     0,    56,     0,    57,     0,    58,     0,
      59,     0,    60,     0,    61,     0,    62,     0,    63,     0,
      66,     0,    67,     0,    64,     0,    65,     0,    68,     0,
      69,     0,    70,     0,    70,    68,     0,    70,    47,    68,
       0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   104,   105,   106,   109,   110,   111,   112,   113,   114,
     115,   116,   123,   127,   133,   147,   147,   250,   250,   265,
     266,   269,   276,   294,   309,   322,   339,   356,   360,   364,
     368,   372,   376,   380,   384,   388,   392,   396,   402,   406,
     410,   415,   420,   425,   429,   432,   433,   436,   444,   449,
     456,   471,   471,   488,   488,   502,   503,   506,   513,   517,
     521,   525,   530,   534,   538,   542,   546,   550,   554,   558,
     562,   566,   570,   573,   574,   577,   578,   579,   582,   590,
     595,   602,   617,   617,   630,   630,   644,   645,   648,   653,
     657,   661,   665,   669,   673,   677,   681,   687,   691,   696,
     701,   706,   713,   720,   720,   733,   733,   747,   748,   751,
     755,   759,   763,   767,   771,   775,   779,   783,   789,   793,
     798,   803,   808,   815,   822,   822,   840,   840,   854,   855,
     858,   865,   869,   873,   877,   881,   885,   891,   898,   905,
     913,   917,   922,   926,   930,   934,   938,   942,   946,   950,
     954,   958,   962,   967,   971,   975,   978,   979,   982,   990,
     995,  1002,  1017,  1025,  1029,  1034,  1038,  1043,  1047,  1054,
    1055,  1066,  1070,  1074,  1080,  1081,  1084,  1095,  1096,  1099,
    1105,  1114,  1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,
    1136,  1137,  1138,  1139,  1146,  1147,  1150,  1155,  1162
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "ROOM", "ITEM", "LINK", "FROM", "TAG", "TO", 
  "DIR", "ONEWAY", "HIDDEN", "NODROP", "NOTE", "TASK", "AFTER", "NEED", 
  "GET", "SCORE", "JOIN", "GO", "REQUIRE", "ANY", "LAST", "START", "GOTO", 
  "MAP", "EXIT", "GIVEN", "LOST", "KEEP", "LENGTH", "TITLE", "LOSE", 
  "SAFE", "BEFORE", "FOLLOW", "CMD", "LEAVE", "UNDEF", "FINISH", "GIVE", 
  "DROP", "ALL", "EXCEPT", "IT", "UNTIL", "TIMES", "NOLINK", "NOPATH", 
  "NONE", "STYLE", "ENDSTYLE", "WITH", "IGNORE", "DO", "NORTH", "EAST", 
  "SOUTH", "WEST", "NORTHEAST", "NORTHWEST", "SOUTHEAST", "SOUTHWEST", 
  "UP", "DOWN", "IN", "OUT", "INTEGER", "REAL", "STRING", "ID", "';'", 
  "'='", "stmt_list", "stmt", "ctrl_stmt", "room_stmt", "@1", "@2", 
  "room_attrs", "room_attr", "room_list", "room_elt", "room", "item_stmt", 
  "@3", "@4", "item_attrs", "item_attr", "item_list", "item_list_all", 
  "item_elt", "item", "link_stmt", "@5", "@6", "link_attrs", "link_attr", 
  "join_stmt", "@7", "@8", "join_attrs", "join_attr", "task_stmt", "@9", 
  "@10", "task_attrs", "task_attr", "task_list", "task_elt", "task", 
  "vars_stmt", "set_var", "in_style", "style_stmt", "style_list", 
  "style_elt", "dir_list", "dir_elt", "compass", "otherdir", "number", 
  "strings", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    74,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    76,    76,    76,    78,    77,    79,    77,    80,
      80,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    82,    82,    83,    84,    84,
      84,    86,    85,    87,    85,    88,    88,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    90,    91,    91,    91,    92,    93,
      93,    93,    95,    94,    96,    94,    97,    97,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,   100,    99,   101,    99,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   105,   104,   106,   104,   107,   107,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   109,   109,   110,   111,
     111,   111,   112,   113,   113,   113,   113,   113,   113,   114,
     114,   115,   115,   115,   116,   116,   117,   118,   118,   119,
     119,   119,   120,   120,   120,   120,   120,   120,   120,   120,
     121,   121,   121,   121,   122,   122,   123,   123,   123
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     0,     5,     0,     5,     0,
       2,     2,     4,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     2,     2,     1,     2,     1,     1,     1,
       1,     0,     5,     0,     5,     0,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     3,     3,     2,     2,     2,
       2,     1,     2,     1,     2,     1,     1,     3,     1,     1,
       1,     1,     0,     7,     0,     5,     0,     2,     2,     2,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     3,
       3,     2,     2,     0,     7,     0,     5,     0,     2,     2,
       2,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       3,     3,     2,     2,     0,     5,     0,     5,     0,     2,
       2,     2,     2,     2,     2,     2,     2,     4,     4,     6,
       3,     5,     3,     2,     2,     2,     2,     2,     1,     1,
       2,     1,     2,     2,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     5,     6,     5,     6,     5,     6,     0,
       3,     3,     3,     2,     1,     2,     1,     1,     2,     1,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     4,     5,     6,     7,     8,
       9,    10,   162,    11,    15,    17,    51,    53,    50,    49,
      84,     0,   124,   126,   105,     0,   194,   195,     0,     0,
       0,     0,     0,   173,     0,     0,    19,    19,    55,    55,
      86,     0,   128,   128,   107,     0,    14,    13,    12,   171,
     172,     0,   169,   169,   169,     0,     0,     0,     0,     0,
      48,    82,     0,     0,     0,   103,   169,   169,   169,     0,
       0,     0,     0,     0,     0,     0,    28,    29,     0,     0,
       0,     0,     0,     0,    32,     0,     0,     0,     0,     0,
      33,    30,    31,     0,    16,    20,    18,     0,    60,     0,
       0,     0,     0,    61,    62,    64,     0,    71,     0,    63,
       0,    52,    56,    54,     0,     0,    90,    91,     0,     0,
       0,     0,     0,     0,     0,    92,     0,    85,    87,    86,
       0,     0,     0,     0,     0,     0,     0,     0,   149,     0,
       0,   151,     0,     0,     0,   148,     0,     0,   125,   129,
     127,     0,   111,   112,     0,     0,     0,     0,     0,     0,
       0,   113,     0,   106,   108,   107,     0,     0,     0,     0,
     167,   165,   163,    25,    45,    47,    21,   182,   183,   184,
     185,   186,   187,   188,   189,    23,   177,   179,    43,   161,
     160,   159,    36,   156,   158,    81,    80,    79,    34,    73,
      78,    39,    26,   192,   193,   190,   191,    27,    24,    38,
      35,     0,     0,   196,    40,    76,    75,    37,   176,    44,
     174,    57,    59,    69,    67,    70,     0,     0,    68,    72,
      58,   101,    88,    95,    93,    89,    97,    94,     0,     0,
      98,    96,   102,     0,   130,   154,   131,   132,   134,   150,
     144,   143,   145,   153,   152,   133,     0,     0,   136,   155,
     135,   147,   146,   122,   116,   114,   109,   110,   118,   115,
       0,     0,   119,   117,   123,     0,   168,   166,   164,   170,
      46,     0,   178,     0,   180,   157,    74,    42,    41,     0,
     197,     0,   175,    66,    65,   100,    99,    83,   142,   140,
       0,     0,   121,   120,   104,    22,   181,   198,    77,     0,
     137,   138,   141,     0,   139,     0,     0
};

static const short yydefgoto[] =
{
       1,    14,    15,    16,    46,    47,    65,   105,   183,   184,
     185,    17,    48,    49,    67,   122,   226,   227,   209,   210,
      18,   139,    50,    69,   138,    19,   175,    54,    74,   174,
      20,    52,    53,    72,   159,   202,   203,   204,    21,    22,
      80,    23,   229,   230,   195,   196,   197,   217,    38,   224
};

static const short yypact[] =
{
  -32768,   162,-32768,    60,    83,     0,   108,    57,   130,   -49,
     -39,   -36,   136,    14,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
      51,    85,-32768,-32768,    51,    97,-32768,-32768,    40,    54,
      78,    92,    96,-32768,    41,    38,-32768,-32768,-32768,-32768,
  -32768,    74,-32768,-32768,-32768,    74,-32768,-32768,-32768,-32768,
  -32768,   116,    81,    81,    81,   229,   276,   393,   423,   186,
  -32768,-32768,   305,   348,   503,-32768,    81,    81,    81,   120,
     102,   110,   115,    74,   109,   335,-32768,-32768,   119,    98,
      99,   124,    74,    93,-32768,   335,   132,    98,    -1,    75,
  -32768,-32768,-32768,   138,-32768,-32768,-32768,   139,-32768,   141,
      98,    99,   144,-32768,-32768,    42,    98,-32768,   138,-32768,
      74,-32768,-32768,-32768,   147,   335,-32768,-32768,    98,    99,
      93,   151,    98,     5,    75,-32768,   138,-32768,-32768,-32768,
     149,   152,    98,    99,    99,   158,    74,    99,-32768,    98,
     -42,-32768,    99,    58,   138,-32768,    98,     7,-32768,-32768,
  -32768,   156,-32768,-32768,    98,    99,   531,   160,    98,     6,
      75,-32768,   138,-32768,-32768,-32768,   159,   168,   171,   161,
  -32768,-32768,-32768,    74,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,    77,-32768,   -21,-32768,-32768,
  -32768,-32768,    98,-32768,-32768,-32768,-32768,-32768,    99,-32768,
  -32768,-32768,    74,-32768,-32768,-32768,-32768,-32768,   335,-32768,
      98,   176,   176,    45,-32768,   206,    99,-32768,-32768,   138,
  -32768,-32768,-32768,    98,    99,-32768,    98,    99,    98,   138,
  -32768,-32768,   335,    98,    99,-32768,-32768,    98,   176,   176,
  -32768,-32768,   138,   471,-32768,-32768,    98,    99,    99,-32768,
  -32768,    99,-32768,-32768,-32768,    99,    98,    74,   -27,   138,
      98,-32768,-32768,-32768,    98,    99,-32768,-32768,-32768,    98,
     176,   176,-32768,-32768,   138,   535,-32768,-32768,-32768,-32768,
  -32768,   180,-32768,   184,-32768,-32768,-32768,-32768,-32768,   187,
  -32768,    99,-32768,    98,    99,-32768,-32768,-32768,    98,   208,
      98,    74,-32768,-32768,-32768,-32768,-32768,-32768,    99,    98,
      98,   211,    98,    98,    98,   230,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,-32768,   212,-32768,   169,  -163,
      -5,-32768,-32768,-32768,   214,-32768,   -86,  -117,  -193,-32768,
  -32768,-32768,-32768,   126,-32768,-32768,-32768,-32768,    95,-32768,
  -32768,-32768,-32768,   215,-32768,   -94,  -147,   122,-32768,-32768,
     127,-32768,  -112,  -185,   -85,  -186,   106,  -103,    49,  -132
};


#define	YYLAST		607


static const short yytable[] =
{
      31,   250,    35,   220,   208,   221,   239,   222,   263,   292,
     218,   248,   280,   249,   281,   296,   233,   251,   264,   310,
     290,    39,   238,    28,   252,   234,   293,   245,   223,   271,
      28,    40,   292,   296,   243,    41,   268,   282,   247,   311,
     242,   296,   269,   244,   302,    29,    71,   294,   256,   290,
      75,   296,    29,   283,   302,   295,   292,   257,   258,   -48,
     284,   261,   270,   277,   296,   296,   265,   302,   296,   223,
     274,    30,   296,   295,   279,   223,   223,    62,    70,   275,
      28,   205,   296,   291,   302,    44,   295,    45,   236,   297,
     298,   295,   299,    51,    64,   237,   295,    28,   205,   302,
     295,   225,    29,   206,   266,    55,    36,    37,    63,   295,
      78,   296,    56,   300,    61,   240,   305,   306,   225,    29,
     206,   199,   205,   295,   267,   296,    57,   295,    34,   207,
      24,    25,   295,   187,   188,   189,   190,   191,   192,   193,
     194,   260,   303,   200,   206,    70,   207,    79,   312,   313,
      58,   304,   272,    26,    27,    76,   295,   213,   214,   215,
     216,   295,   325,     2,    59,     3,     4,     5,    60,   201,
     207,   179,   308,   295,   180,   295,     6,   295,    32,    33,
     186,     7,   181,     8,    36,    37,    77,   182,     9,   198,
      81,    82,   211,   124,    10,   125,   126,   127,    36,    37,
     219,   128,   129,   176,   177,   178,   130,    42,    43,   228,
     231,   232,   235,    11,    12,   318,   320,   131,   241,   246,
     254,   132,   255,   133,   134,   322,   259,   273,   278,   324,
     326,   286,   289,    13,    83,   135,    84,   136,    85,    86,
     287,    87,    88,   288,    89,    90,   223,    91,    92,    93,
     301,   315,   316,    94,   319,   317,    95,   323,   137,    66,
      96,   212,   309,    68,    97,   253,    98,    99,    73,   100,
     285,   262,   276,     0,     0,     0,     0,   101,   102,     0,
     103,    83,     0,    84,     0,    85,    86,     0,    87,    88,
       0,    89,    90,     0,    91,    92,    93,     0,     0,     0,
      94,   104,     0,    95,     0,     0,   321,    96,     0,     0,
       0,    97,   140,    98,    99,     0,   100,     0,   141,     0,
     142,   143,   144,   145,   101,   102,     0,   103,     0,     0,
     146,     0,     0,     0,     0,     0,     0,     0,   147,   148,
       0,   149,   150,     0,     0,   151,   152,   153,   106,     0,
       0,     0,     0,     0,     0,   140,   154,     0,     0,   155,
     156,   141,     0,   142,   143,   144,   145,     0,     0,     0,
       0,   157,     0,   146,     0,     0,     0,   158,     0,     0,
       0,   147,   148,     0,   149,   150,     0,     0,   151,   152,
     153,   187,   188,   189,   190,   191,   192,   193,   194,   154,
     107,     0,   155,   156,   108,     0,   109,     0,   110,   111,
       0,   112,     0,     0,   157,     0,     0,     0,     0,     0,
     160,   113,   114,   115,     0,     0,     0,     0,   116,     0,
     107,     0,     0,   117,   108,     0,   109,     0,   110,   111,
       0,   112,     0,     0,   118,     0,     0,   119,     0,     0,
       0,   113,   114,   115,     0,     0,     0,     0,   116,   120,
       0,     0,     0,   117,     0,   121,     0,     0,     0,     0,
       0,     0,     0,     0,   118,     0,     0,   119,   124,     0,
     125,   126,   127,     0,     0,     0,   128,   129,     0,   120,
       0,   130,     0,     0,     0,   123,     0,     0,     0,     0,
       0,     0,   131,     0,     0,     0,   132,     0,   133,   134,
     161,     0,     0,   162,   163,     0,     0,     0,   164,   165,
     135,     0,   136,   166,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   167,     0,     0,     0,   168,     0,
     169,   170,   161,   307,     0,   162,   163,     0,     0,     0,
     164,   165,   171,     0,   172,   166,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   167,     0,     0,     0,
     168,     0,   169,   170,     0,   173,     0,     0,     0,     0,
       0,     0,     0,     0,   171,     0,   172,   187,   188,   189,
     190,   191,   192,   193,   194,   213,   214,   215,   216,     0,
       0,     0,     0,     0,     0,     0,     0,   314
};

static const short yycheck[] =
{
       5,   133,     7,    97,    90,     6,   118,     8,    50,   195,
      95,     6,     6,     8,     8,   208,   110,   134,   150,    46,
     183,    70,   116,    23,   136,   111,    47,   130,    70,    22,
      23,    70,   218,   226,   128,    71,   153,   169,   132,    66,
     125,   234,   154,   129,   229,    45,    51,    68,   142,   212,
      55,   244,    45,   170,   239,   202,   242,   143,   144,     8,
     172,   147,   156,   166,   257,   258,   152,   252,   261,    70,
     164,    71,   265,   220,   168,    70,    70,    39,    71,   165,
      23,    23,   275,     6,   269,    71,   233,    73,    46,   221,
     222,   238,    47,     8,    45,    53,   243,    23,    23,   284,
     247,    43,    45,    45,    46,     8,    68,    69,    70,   256,
      61,   304,    72,    68,    73,   120,   248,   249,    43,    45,
      45,    23,    23,   270,    66,   318,    72,   274,    71,    71,
      70,    71,   279,    56,    57,    58,    59,    60,    61,    62,
      63,   146,   236,    45,    45,    71,    71,    66,   280,   281,
      72,   237,   157,    70,    71,    39,   303,    64,    65,    66,
      67,   308,     0,     1,    72,     3,     4,     5,    72,    71,
      71,    51,   266,   320,    72,   322,    14,   324,    70,    71,
      71,    19,    72,    21,    68,    69,    70,    72,    26,    70,
      63,    64,    68,     7,    32,     9,    10,    11,    68,    69,
      68,    15,    16,    76,    77,    78,    20,    71,    72,    71,
      71,    70,    68,    51,    52,   301,   310,    31,    71,    68,
      71,    35,    70,    37,    38,   319,    68,    71,    68,   323,
       0,    72,    71,    71,     5,    49,     7,    51,     9,    10,
      72,    12,    13,    72,    15,    16,    70,    18,    19,    20,
      44,    71,    68,    24,    46,    68,    27,    46,    72,    47,
      31,    92,   267,    49,    35,   139,    37,    38,    53,    40,
     175,   149,   166,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,     5,    -1,     7,    -1,     9,    10,    -1,    12,    13,
      -1,    15,    16,    -1,    18,    19,    20,    -1,    -1,    -1,
      24,    72,    -1,    27,    -1,    -1,   311,    31,    -1,    -1,
      -1,    35,     7,    37,    38,    -1,    40,    -1,    13,    -1,
      15,    16,    17,    18,    48,    49,    -1,    51,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    36,    37,    -1,    -1,    40,    41,    42,    72,    -1,
      -1,    -1,    -1,    -1,    -1,     7,    51,    -1,    -1,    54,
      55,    13,    -1,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    66,    -1,    25,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    33,    34,    -1,    36,    37,    -1,    -1,    40,    41,
      42,    56,    57,    58,    59,    60,    61,    62,    63,    51,
       7,    -1,    54,    55,    11,    -1,    13,    -1,    15,    16,
      -1,    18,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      72,    28,    29,    30,    -1,    -1,    -1,    -1,    35,    -1,
       7,    -1,    -1,    40,    11,    -1,    13,    -1,    15,    16,
      -1,    18,    -1,    -1,    51,    -1,    -1,    54,    -1,    -1,
      -1,    28,    29,    30,    -1,    -1,    -1,    -1,    35,    66,
      -1,    -1,    -1,    40,    -1,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    54,     7,    -1,
       9,    10,    11,    -1,    -1,    -1,    15,    16,    -1,    66,
      -1,    20,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    35,    -1,    37,    38,
       7,    -1,    -1,    10,    11,    -1,    -1,    -1,    15,    16,
      49,    -1,    51,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    -1,
      37,    38,     7,    72,    -1,    10,    11,    -1,    -1,    -1,
      15,    16,    49,    -1,    51,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      35,    -1,    37,    38,    -1,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    51,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
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
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
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
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 12:
#line 124 "ifm-parse.y"
{
                    vh_sstore(map, "TITLE", yyvsp[-1].sval);
                }
    break;
case 13:
#line 128 "ifm-parse.y"
{
                    if (sectnames == NULL)
                        sectnames = vl_create();
                    vl_spush(sectnames, yyvsp[-1].sval);
                }
    break;
case 14:
#line 134 "ifm-parse.y"
{
                    float version;
                    sscanf(VERSION, "%f", &version);
                    if (yyvsp[-1].dval - version > 0.001)
                        fatal("version %g of IFM is required (this is %s)",
                              yyvsp[-1].dval, VERSION);
                }
    break;
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
		}
    break;
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
                }
    break;
case 17:
#line 251 "ifm-parse.y"
{
                    implicit = 0;
                    modify = 1;
                    if ((curobj = vh_pget(roomtags, yyvsp[0].sval)) == NULL) {
                        err("room tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                }
    break;
case 18:
#line 260 "ifm-parse.y"
{
                    RESET_IT;
                }
    break;
case 21:
#line 270 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("room", yyvsp[0].sval, curobj, roomtags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;
case 22:
#line 277 "ifm-parse.y"
{
                    vhash *room;

                    if (!modify) {
                        implicit = 1;

                        vh_pstore(curobj, "DIR", curdirs);
                        curdirs = NULL;

                        if ((room = vh_pget(roomtags, yyvsp[0].sval)) != NULL)
                            vh_pstore(curobj, "NEAR", room);
                        else
                            err("room tag '%s' not yet defined", yyvsp[0].sval);
                    } else {
                        CHANGE_ERROR(from);
                    }
		}
    break;
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
		}
    break;
case 24:
#line 310 "ifm-parse.y"
{
                    viter iter;
                    int dir;

                    v_iterate(curdirs, iter) {
                        dir = vl_iter_ival(iter);
                        room_exit(curobj, dirinfo[dir].xoff,
                                  dirinfo[dir].yoff, 1);
                    }

                    curdirs = NULL;
		}
    break;
case 25:
#line 323 "ifm-parse.y"
{
                    vscalar *elt;
                    vhash *link;
                    viter iter;

                    v_iterate(currooms, iter) {
                        elt = vl_iter_val(iter);
                        link = vh_create();
                        vh_pstore(link, "FROM", curobj);
                        vh_store(link, "TO", vs_copy(elt));
                        vl_ppush(links, link);
                    }

                    vl_destroy(currooms);
                    currooms = NULL;
		}
    break;
case 26:
#line 340 "ifm-parse.y"
{
                    vscalar *elt;
                    vhash *join;
                    viter iter;

                    v_iterate(currooms, iter) {
                        elt = vl_iter_val(iter);
                        join = vh_create();
                        vh_pstore(join, "FROM", curobj);
                        vh_store(join, "TO", vs_copy(elt));
                        vl_ppush(joins, join);
                    }

                    vl_destroy(currooms);
                    currooms = NULL;
		}
    break;
case 27:
#line 357 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		}
    break;
case 28:
#line 361 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		}
    break;
case 29:
#line 365 "ifm-parse.y"
{
                    vh_istore(curobj, "NODROP", 1);
		}
    break;
case 30:
#line 369 "ifm-parse.y"
{
                    vh_istore(curobj, "NOLINK", 1);
		}
    break;
case 31:
#line 373 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		}
    break;
case 32:
#line 377 "ifm-parse.y"
{
                    startroom = curobj;
		}
    break;
case 33:
#line 381 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                }
    break;
case 34:
#line 385 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(NEED), curitems);
                }
    break;
case 35:
#line 389 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		}
    break;
case 36:
#line 393 "ifm-parse.y"
{
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		}
    break;
case 37:
#line 397 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                }
    break;
case 38:
#line 403 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		}
    break;
case 39:
#line 407 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		}
    break;
case 40:
#line 411 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                }
    break;
case 41:
#line 416 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                }
    break;
case 42:
#line 421 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                }
    break;
case 43:
#line 426 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		}
    break;
case 47:
#line 437 "ifm-parse.y"
{
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, yyvsp[0].vval);
		}
    break;
case 48:
#line 445 "ifm-parse.y"
{
                    yyval.vval = vs_screate(yyvsp[0].sval);
                    itroom = vs_copy(yyval.vval);
                }
    break;
case 49:
#line 450 "ifm-parse.y"
{
                    if (itroom == NULL)
                        err("no room referred to by 'it'");
                    else
                        yyval.vval = vs_copy(itroom);
                }
    break;
case 50:
#line 457 "ifm-parse.y"
{
                    if (lastroom == NULL) {
                        err("no room referred to by 'last'");
                    } else {
                        yyval.vval = vs_pcreate(lastroom);
                        itroom = vs_copy(yyval.vval);
                    }                        
                }
    break;
case 51:
#line 472 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_istore(curobj, "ID", itemid++);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;
case 52:
#line 480 "ifm-parse.y"
{
                    if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lastitem = curobj;
                    vl_ppush(items, curobj);
                    RESET_IT;
		}
    break;
case 53:
#line 489 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(itemtags, yyvsp[0].sval)) == NULL) {
                        err("item tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                }
    break;
case 54:
#line 497 "ifm-parse.y"
{
                    RESET_IT;
                }
    break;
case 57:
#line 507 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("item", yyvsp[0].sval, curobj, itemtags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;
case 58:
#line 514 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		}
    break;
case 59:
#line 518 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		}
    break;
case 60:
#line 522 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		}
    break;
case 61:
#line 526 "ifm-parse.y"
{
                    obsolete("'given' attribute", "task 'give' attribute");
                    vh_istore(curobj, "GIVEN", 1);
		}
    break;
case 62:
#line 531 "ifm-parse.y"
{
                    vh_istore(curobj, "LOST", 1);
		}
    break;
case 63:
#line 535 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		}
    break;
case 64:
#line 539 "ifm-parse.y"
{
                    vh_istore(curobj, "KEEP", 1);
		}
    break;
case 65:
#line 543 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_WITH", curitems);
		}
    break;
case 66:
#line 547 "ifm-parse.y"
{
                    SET_LIST(curobj, "KEEP_UNTIL", curtasks);
		}
    break;
case 67:
#line 551 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                }
    break;
case 68:
#line 555 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
                }
    break;
case 69:
#line 559 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
                }
    break;
case 70:
#line 563 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		}
    break;
case 71:
#line 567 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                }
    break;
case 75:
#line 577 "ifm-parse.y"
{ allflag = 0; }
    break;
case 76:
#line 578 "ifm-parse.y"
{ allflag = 1; }
    break;
case 77:
#line 579 "ifm-parse.y"
{ allflag = 1; }
    break;
case 78:
#line 583 "ifm-parse.y"
{
                    if (curitems == NULL)
                        curitems = vl_create();
                    vl_push(curitems, yyvsp[0].vval);
		}
    break;
case 79:
#line 591 "ifm-parse.y"
{
                    yyval.vval = vs_screate(yyvsp[0].sval);
                    ititem = vs_copy(yyval.vval);
                }
    break;
case 80:
#line 596 "ifm-parse.y"
{
                    if (ititem == NULL)
                        err("no item referred to by 'it'");
                    else
                        yyval.vval = vs_copy(ititem);
                }
    break;
case 81:
#line 603 "ifm-parse.y"
{
                    if (lastitem == NULL) {
                        err("no item referred to by 'last'");
                    } else {
                        yyval.vval = vs_pcreate(lastitem);
                        ititem = vs_copy(yyval.vval);
                    }
                }
    break;
case 82:
#line 618 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;
case 83:
#line 626 "ifm-parse.y"
{
                    vl_ppush(links, curobj);
                    RESET_IT;
		}
    break;
case 84:
#line 631 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(linktags, yyvsp[0].sval)) == NULL) {
                        err("link tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                }
    break;
case 85:
#line 639 "ifm-parse.y"
{
                    RESET_IT;
                }
    break;
case 88:
#line 649 "ifm-parse.y"
{
                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;
		}
    break;
case 89:
#line 654 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		}
    break;
case 90:
#line 658 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		}
    break;
case 91:
#line 662 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		}
    break;
case 92:
#line 666 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		}
    break;
case 93:
#line 670 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                }
    break;
case 94:
#line 674 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		}
    break;
case 95:
#line 678 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		}
    break;
case 96:
#line 682 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                }
    break;
case 97:
#line 688 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		}
    break;
case 98:
#line 692 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                }
    break;
case 99:
#line 697 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                }
    break;
case 100:
#line 702 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                }
    break;
case 101:
#line 707 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("link", yyvsp[0].sval, curobj, linktags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;
case 103:
#line 721 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_store(curobj, "FROM", yyvsp[-2].vval);
                    vh_store(curobj, "TO", yyvsp[0].vval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;
case 104:
#line 729 "ifm-parse.y"
{
                    vl_ppush(joins, curobj);
                    RESET_IT;
		}
    break;
case 105:
#line 734 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(jointags, yyvsp[0].sval)) == NULL) {
                        err("join tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                }
    break;
case 106:
#line 742 "ifm-parse.y"
{
                    RESET_IT;
                }
    break;
case 109:
#line 752 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		}
    break;
case 110:
#line 756 "ifm-parse.y"
{
                    vh_istore(curobj, "GO", yyvsp[0].ival);
		}
    break;
case 111:
#line 760 "ifm-parse.y"
{
                    vh_istore(curobj, "ONEWAY", 1);
		}
    break;
case 112:
#line 764 "ifm-parse.y"
{
                    vh_istore(curobj, "HIDDEN", 1);
		}
    break;
case 113:
#line 768 "ifm-parse.y"
{
                    vh_istore(curobj, "NOPATH", 1);
		}
    break;
case 114:
#line 772 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
                }
    break;
case 115:
#line 776 "ifm-parse.y"
{
                    SET_LIST(curobj, "BEFORE", curtasks);
		}
    break;
case 116:
#line 780 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		}
    break;
case 117:
#line 784 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                }
    break;
case 118:
#line 790 "ifm-parse.y"
{
                    vh_istore(curobj, "LEN", yyvsp[0].ival);
		}
    break;
case 119:
#line 794 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                }
    break;
case 120:
#line 799 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", yyvsp[0].sval);
                }
    break;
case 121:
#line 804 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", yyvsp[0].sval);
                }
    break;
case 122:
#line 809 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("join", yyvsp[0].sval, curobj, jointags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;
case 124:
#line 823 "ifm-parse.y"
{
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", yyvsp[0].sval);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;
case 125:
#line 830 "ifm-parse.y"
{
                    if (vh_iget(curobj, "NOROOM"))
                        vh_pstore(curobj, "IN", NULL);
                    else if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lasttask = curobj;
                    vl_ppush(tasks, curobj);
                    RESET_IT;
		}
    break;
case 126:
#line 841 "ifm-parse.y"
{
                    modify = 1;
                    if ((curobj = vh_pget(tasktags, yyvsp[0].sval)) == NULL) {
                        err("task tag '%s' not yet defined", yyvsp[0].sval);
                        curobj = vh_create();
                    }
                }
    break;
case 127:
#line 849 "ifm-parse.y"
{
                    RESET_IT;
                }
    break;
case 130:
#line 859 "ifm-parse.y"
{
                    if (!modify)
                        set_tag("task", yyvsp[0].sval, curobj, tasktags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;
case 131:
#line 866 "ifm-parse.y"
{
                    SET_LIST(curobj, "AFTER", curtasks);
		}
    break;
case 132:
#line 870 "ifm-parse.y"
{
                    SET_LIST(curobj, "NEED", curitems);
		}
    break;
case 133:
#line 874 "ifm-parse.y"
{
                    SET_LIST(curobj, "GIVE", curitems);
		}
    break;
case 134:
#line 878 "ifm-parse.y"
{
                    SET_LIST(curobj, "GET", curitems);
		}
    break;
case 135:
#line 882 "ifm-parse.y"
{
                    SET_LIST(curobj, "DO", curtasks);
		}
    break;
case 136:
#line 886 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
		}
    break;
case 137:
#line 892 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		}
    break;
case 138:
#line 899 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		}
    break;
case 139:
#line 906 "ifm-parse.y"
{
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		}
    break;
case 140:
#line 914 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[0].vval);
		}
    break;
case 141:
#line 918 "ifm-parse.y"
{
                    vh_store(curobj, "DROPROOM", yyvsp[-2].vval);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		}
    break;
case 142:
#line 923 "ifm-parse.y"
{
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
                }
    break;
case 143:
#line 927 "ifm-parse.y"
{
                    SET_LIST(curobj, "LOSE", curitems);
		}
    break;
case 144:
#line 931 "ifm-parse.y"
{
                    vh_store(curobj, "GOTO", yyvsp[0].vval);
                }
    break;
case 145:
#line 935 "ifm-parse.y"
{
                    vh_store(curobj, "FOLLOW", yyvsp[0].vval);
                }
    break;
case 146:
#line 939 "ifm-parse.y"
{
                    vh_store(curobj, "IN", yyvsp[0].vval);
		}
    break;
case 147:
#line 943 "ifm-parse.y"
{
                    vh_istore(curobj, "NOROOM", 1);
		}
    break;
case 148:
#line 947 "ifm-parse.y"
{
                    vh_istore(curobj, "IGNORE", 1);
		}
    break;
case 149:
#line 951 "ifm-parse.y"
{
                    vh_istore(curobj, "SAFE", 1);
                }
    break;
case 150:
#line 955 "ifm-parse.y"
{
                    vh_istore(curobj, "SCORE", yyvsp[0].ival);
		}
    break;
case 151:
#line 959 "ifm-parse.y"
{
                    vh_istore(curobj, "FINISH", 1);
                }
    break;
case 152:
#line 963 "ifm-parse.y"
{
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", yyvsp[0].sval);
                }
    break;
case 153:
#line 968 "ifm-parse.y"
{
                    add_attr(curobj, "CMD", NULL);
                }
    break;
case 154:
#line 972 "ifm-parse.y"
{
                    add_attr(curobj, "NOTE", yyvsp[0].sval);
		}
    break;
case 158:
#line 983 "ifm-parse.y"
{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, yyvsp[0].vval);
		}
    break;
case 159:
#line 991 "ifm-parse.y"
{
                    yyval.vval = vs_screate(yyvsp[0].sval);
                    ittask = vs_copy(yyval.vval);
                }
    break;
case 160:
#line 996 "ifm-parse.y"
{
                    if (ittask == NULL)
                        err("no task referred to by 'it'");
                    else
                        yyval.vval = vs_copy(ittask);
                }
    break;
case 161:
#line 1003 "ifm-parse.y"
{
                    if (lasttask == NULL) {
                        err("no task referred to by 'last'");
                    } else {
                        yyval.vval = vs_pcreate(lasttask);
                        ittask = vs_copy(yyval.vval);
                    }
                }
    break;
case 162:
#line 1018 "ifm-parse.y"
{
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                }
    break;
case 163:
#line 1026 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                }
    break;
case 164:
#line 1030 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_dcreate(yyvsp[-2].dval));
                    obsolete("variable assignment", "dotted notation");
                }
    break;
case 165:
#line 1035 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                }
    break;
case 166:
#line 1039 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, vs_screate(yyvsp[-2].sval));
                    obsolete("variable assignment", "dotted notation");
                }
    break;
case 167:
#line 1044 "ifm-parse.y"
{
                    var_set(NULL, yyvsp[-4].sval, NULL);
                }
    break;
case 168:
#line 1048 "ifm-parse.y"
{
                    var_set(yyvsp[-5].sval, yyvsp[-4].sval, NULL);
                    obsolete("variable assignment", "dotted notation");
                }
    break;
case 170:
#line 1056 "ifm-parse.y"
{
                    push_style(yyvsp[0].sval);
                    instyle++;
                }
    break;
case 171:
#line 1067 "ifm-parse.y"
{
                    push_style(yyvsp[-1].sval);
                }
    break;
case 172:
#line 1071 "ifm-parse.y"
{
                    pop_style(yyvsp[-1].sval);
                }
    break;
case 173:
#line 1075 "ifm-parse.y"
{
                    pop_style(NULL);
                }
    break;
case 176:
#line 1085 "ifm-parse.y"
{
                    add_attr(curobj, "STYLE", yyvsp[0].sval);
                    ref_style(yyvsp[0].sval);
                }
    break;
case 179:
#line 1100 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, yyvsp[0].ival);
		}
    break;
case 180:
#line 1106 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-1].ival);
                }
    break;
case 181:
#line 1115 "ifm-parse.y"
{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    while (yyvsp[0].ival-- > 0)
                        vl_ipush(curdirs, yyvsp[-2].ival);
                    obsolete("'times' keyword", "just the repeat count");
                }
    break;
case 182:
#line 1126 "ifm-parse.y"
{ yyval.ival = D_NORTH;	    }
    break;
case 183:
#line 1127 "ifm-parse.y"
{ yyval.ival = D_EAST;	    }
    break;
case 184:
#line 1128 "ifm-parse.y"
{ yyval.ival = D_SOUTH;	    }
    break;
case 185:
#line 1129 "ifm-parse.y"
{ yyval.ival = D_WEST;	    }
    break;
case 186:
#line 1130 "ifm-parse.y"
{ yyval.ival = D_NORTHEAST; }
    break;
case 187:
#line 1131 "ifm-parse.y"
{ yyval.ival = D_NORTHWEST; }
    break;
case 188:
#line 1132 "ifm-parse.y"
{ yyval.ival = D_SOUTHEAST; }
    break;
case 189:
#line 1133 "ifm-parse.y"
{ yyval.ival = D_SOUTHWEST; }
    break;
case 190:
#line 1136 "ifm-parse.y"
{ yyval.ival = D_IN;   }
    break;
case 191:
#line 1137 "ifm-parse.y"
{ yyval.ival = D_OUT;  }
    break;
case 192:
#line 1138 "ifm-parse.y"
{ yyval.ival = D_UP;   }
    break;
case 193:
#line 1139 "ifm-parse.y"
{ yyval.ival = D_DOWN; }
    break;
case 194:
#line 1146 "ifm-parse.y"
{ yyval.dval = yyvsp[0].ival; }
    break;
case 195:
#line 1147 "ifm-parse.y"
{ yyval.dval = yyvsp[0].dval; }
    break;
case 196:
#line 1151 "ifm-parse.y"
{
                    yyval.sval = yyvsp[0].sval;
                    repeat = 1;
                }
    break;
case 197:
#line 1156 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-1].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                }
    break;
case 198:
#line 1163 "ifm-parse.y"
{
                    yyval.sval = yyvsp[-2].sval;
                    repeat = yyvsp[0].ival;
                    if (yyvsp[0].ival <= 0)
                        err("invalid repeat count");
                    obsolete("'times' keyword", "just the repeat count");
                }
    break;
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
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

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 1172 "ifm-parse.y"

