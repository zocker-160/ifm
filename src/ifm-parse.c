/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ROOM = 258,
     ITEM = 259,
     LINK = 260,
     FROM = 261,
     TAG = 262,
     TO = 263,
     DIR = 264,
     ONEWAY = 265,
     HIDDEN = 266,
     NODROP = 267,
     NOTE = 268,
     TASK = 269,
     AFTER = 270,
     NEED = 271,
     GET = 272,
     SCORE = 273,
     JOIN = 274,
     GO = 275,
     REQUIRE = 276,
     ANY = 277,
     LAST = 278,
     START = 279,
     GOTO = 280,
     MAP = 281,
     EXIT = 282,
     GIVEN = 283,
     LOST = 284,
     KEEP = 285,
     LENGTH = 286,
     TITLE = 287,
     LOSE = 288,
     SAFE = 289,
     BEFORE = 290,
     FOLLOW = 291,
     CMD = 292,
     LEAVE = 293,
     UNDEF = 294,
     FINISH = 295,
     GIVE = 296,
     DROP = 297,
     ALL = 298,
     EXCEPT = 299,
     IT = 300,
     UNTIL = 301,
     TIMES = 302,
     NOLINK = 303,
     NOPATH = 304,
     NONE = 305,
     STYLE = 306,
     ENDSTYLE = 307,
     WITH = 308,
     IGNORE = 309,
     DO = 310,
     THEM = 311,
     NORTH = 312,
     EAST = 313,
     SOUTH = 314,
     WEST = 315,
     NORTHEAST = 316,
     NORTHWEST = 317,
     SOUTHEAST = 318,
     SOUTHWEST = 319,
     UP = 320,
     DOWN = 321,
     IN = 322,
     OUT = 323,
     INTEGER = 324,
     TRUE = 325,
     FALSE = 326,
     REAL = 327,
     STRING = 328,
     ID = 329
   };
#endif
/* Tokens.  */
#define ROOM 258
#define ITEM 259
#define LINK 260
#define FROM 261
#define TAG 262
#define TO 263
#define DIR 264
#define ONEWAY 265
#define HIDDEN 266
#define NODROP 267
#define NOTE 268
#define TASK 269
#define AFTER 270
#define NEED 271
#define GET 272
#define SCORE 273
#define JOIN 274
#define GO 275
#define REQUIRE 276
#define ANY 277
#define LAST 278
#define START 279
#define GOTO 280
#define MAP 281
#define EXIT 282
#define GIVEN 283
#define LOST 284
#define KEEP 285
#define LENGTH 286
#define TITLE 287
#define LOSE 288
#define SAFE 289
#define BEFORE 290
#define FOLLOW 291
#define CMD 292
#define LEAVE 293
#define UNDEF 294
#define FINISH 295
#define GIVE 296
#define DROP 297
#define ALL 298
#define EXCEPT 299
#define IT 300
#define UNTIL 301
#define TIMES 302
#define NOLINK 303
#define NOPATH 304
#define NONE 305
#define STYLE 306
#define ENDSTYLE 307
#define WITH 308
#define IGNORE 309
#define DO 310
#define THEM 311
#define NORTH 312
#define EAST 313
#define SOUTH 314
#define WEST 315
#define NORTHEAST 316
#define NORTHWEST 317
#define SOUTHEAST 318
#define SOUTHWEST 319
#define UP 320
#define DOWN 321
#define IN 322
#define OUT 323
#define INTEGER 324
#define TRUE 325
#define FALSE 326
#define REAL 327
#define STRING 328
#define ID 329




/* Copy the first part of user declarations.  */
#line 1 "ifm-parse.y"

/*
 * This file is part of IFM (Interactive Fiction Mapper), copyright (C)
 * Glenn Hutchings 1997-2008.
 *
 * IFM comes with ABSOLUTELY NO WARRANTY.  This is free software, and you
 * are welcome to redistribute it under certain conditions; see the file
 * COPYING for details.
 */

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

#define RESET RESET_IT; RESET_THEM

#define RESET_IT                                                        \
        RESET_VAR(itroom);                                              \
        RESET_VAR(ititem);                                              \
        RESET_VAR(ittask)

#define RESET_THEM                                                      \
        { if (themitems != NULL) vl_destroy(themitems); themitems = NULL; }

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

static vlist *themitems = NULL; /* Items referred to by 'them' */

static int roomid = 0;          /* Current room ID */
static int itemid = 0;          /* Current item ID */

static vlist *curdirs = NULL;   /* Current direction list */

static int modify = 0;          /* Modification flag */
static int implicit = 0;        /* Implicit-link flag */
static int allflag = 0;         /* All-items flag */
static int repeat = 0;          /* String repeat count */
static int instyle = 0;         /* Set variable in different style? */


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 87 "ifm-parse.y"
{
    int ival;
    double dval;
    char *sval;
    vscalar *vval;
}
/* Line 193 of yacc.c.  */
#line 337 "ifm-parse.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 350 "ifm-parse.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   606

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  202
/* YYNRULES -- Number of states.  */
#define YYNSTATES  329

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    75,
       2,    76,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    30,    34,    38,    39,    45,    46,
      52,    53,    56,    59,    64,    67,    70,    73,    76,    79,
      81,    83,    85,    87,    89,    91,    94,    97,   100,   103,
     106,   109,   112,   116,   120,   123,   126,   128,   131,   133,
     135,   137,   139,   140,   146,   147,   153,   154,   157,   160,
     163,   166,   168,   170,   172,   174,   176,   180,   184,   187,
     190,   193,   196,   198,   201,   203,   206,   208,   210,   212,
     216,   218,   220,   222,   224,   225,   233,   234,   240,   241,
     244,   247,   250,   252,   254,   256,   259,   262,   265,   268,
     271,   274,   278,   282,   285,   288,   289,   297,   298,   304,
     305,   308,   311,   314,   316,   318,   320,   323,   326,   329,
     332,   335,   338,   342,   346,   349,   352,   353,   359,   360,
     366,   367,   370,   373,   376,   379,   382,   385,   388,   391,
     396,   401,   408,   412,   418,   422,   425,   428,   431,   434,
     437,   439,   441,   444,   446,   449,   452,   455,   458,   460,
     463,   465,   467,   469,   471,   473,   479,   486,   492,   499,
     505,   512,   513,   517,   521,   525,   528,   530,   533,   535,
     537,   540,   542,   545,   549,   551,   553,   555,   557,   559,
     561,   563,   565,   567,   569,   571,   573,   575,   577,   579,
     581,   583,   586
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      78,     0,    -1,    -1,    78,    79,    -1,    78,     1,    -1,
      80,    -1,    81,    -1,    89,    -1,    98,    -1,   103,    -1,
     108,    -1,   116,    -1,   119,    -1,    32,    73,    75,    -1,
      26,    73,    75,    -1,    21,   126,    75,    -1,    -1,     3,
      73,    82,    84,    75,    -1,    -1,     3,    74,    83,    84,
      75,    -1,    -1,    84,    85,    -1,     7,    74,    -1,     9,
     122,     6,    74,    -1,     9,   122,    -1,    27,   122,    -1,
       5,    86,    -1,    19,    86,    -1,    20,   125,    -1,    10,
      -1,    12,    -1,    48,    -1,    49,    -1,    24,    -1,    40,
      -1,    16,    94,    -1,    35,   113,    -1,    15,   113,    -1,
      38,    95,    -1,    31,    69,    -1,    18,    69,    -1,    37,
     127,    -1,    37,     8,   127,    -1,    37,     6,   127,    -1,
      13,    73,    -1,    51,   120,    -1,    87,    -1,    86,    87,
      -1,    88,    -1,    74,    -1,    45,    -1,    23,    -1,    -1,
       4,    73,    90,    92,    75,    -1,    -1,     4,    74,    91,
      92,    75,    -1,    -1,    92,    93,    -1,     7,    74,    -1,
      67,    88,    -1,    13,    73,    -1,    11,    -1,    28,    -1,
      29,    -1,    54,    -1,    30,    -1,    30,    53,    94,    -1,
      30,    46,   113,    -1,    16,    94,    -1,    35,   113,    -1,
      15,   113,    -1,    18,    69,    -1,    40,    -1,    51,   120,
      -1,    96,    -1,    94,    96,    -1,    56,    -1,    94,    -1,
      43,    -1,    43,    44,    94,    -1,    97,    -1,    74,    -1,
      45,    -1,    23,    -1,    -1,     5,    88,     8,    88,    99,
     101,    75,    -1,    -1,     5,    74,   100,   101,    75,    -1,
      -1,   101,   102,    -1,     9,   122,    -1,    20,   125,    -1,
      10,    -1,    11,    -1,    49,    -1,    16,    94,    -1,    35,
     113,    -1,    15,   113,    -1,    38,    95,    -1,    31,    69,
      -1,    37,   127,    -1,    37,     8,   127,    -1,    37,     6,
     127,    -1,     7,    74,    -1,    51,   120,    -1,    -1,    19,
      88,     8,    88,   104,   106,    75,    -1,    -1,    19,    74,
     105,   106,    75,    -1,    -1,   106,   107,    -1,    20,   124,
      -1,    20,   125,    -1,    10,    -1,    11,    -1,    49,    -1,
      16,    94,    -1,    35,   113,    -1,    15,   113,    -1,    38,
      95,    -1,    31,    69,    -1,    37,   127,    -1,    37,     8,
     127,    -1,    37,     6,   127,    -1,     7,    74,    -1,    51,
     120,    -1,    -1,    14,    73,   109,   111,    75,    -1,    -1,
      14,    74,   110,   111,    75,    -1,    -1,   111,   112,    -1,
       7,    74,    -1,    15,   113,    -1,    16,    94,    -1,    41,
      94,    -1,    17,    94,    -1,    55,   113,    -1,    42,    95,
      -1,    42,    95,    46,   113,    -1,    42,    95,    67,    88,
      -1,    42,    95,    67,    88,    46,   113,    -1,    42,    67,
      88,    -1,    42,    67,    88,    46,   113,    -1,    42,    46,
     113,    -1,    33,    94,    -1,    25,    88,    -1,    36,   115,
      -1,    67,    88,    -1,    67,    22,    -1,    54,    -1,    34,
      -1,    18,    69,    -1,    40,    -1,    37,   127,    -1,    37,
      50,    -1,    13,    73,    -1,    51,   120,    -1,   114,    -1,
     113,   114,    -1,   115,    -1,    74,    -1,    45,    -1,    23,
      -1,   117,    -1,    74,    76,   126,   118,    75,    -1,    74,
      74,    76,   126,   118,    75,    -1,    74,    76,    73,   118,
      75,    -1,    74,    74,    76,    73,   118,    75,    -1,    74,
      76,    39,   118,    75,    -1,    74,    74,    76,    39,   118,
      75,    -1,    -1,    67,    51,    74,    -1,    51,    74,    75,
      -1,    52,    74,    75,    -1,    52,    75,    -1,   121,    -1,
     120,   121,    -1,    74,    -1,   123,    -1,   122,   123,    -1,
     124,    -1,   124,    69,    -1,   124,    47,    69,    -1,    57,
      -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,    62,
      -1,    63,    -1,    64,    -1,    67,    -1,    68,    -1,    65,
      -1,    66,    -1,    69,    -1,    72,    -1,    70,    -1,    71,
      -1,    73,    -1,    73,    69,    -1,    73,    47,    69,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   120,   120,   121,   122,   125,   126,   127,   128,   129,
     130,   131,   132,   139,   143,   149,   164,   163,   267,   266,
     281,   282,   285,   292,   310,   325,   338,   355,   372,   376,
     380,   384,   388,   392,   396,   400,   404,   408,   412,   418,
     422,   426,   431,   436,   441,   445,   448,   449,   452,   460,
     465,   472,   488,   487,   505,   504,   518,   519,   522,   529,
     533,   537,   541,   546,   550,   554,   558,   562,   566,   570,
     574,   578,   582,   586,   589,   590,   591,   604,   605,   606,
     609,   623,   628,   635,   651,   650,   664,   663,   677,   678,
     681,   686,   690,   694,   698,   702,   706,   710,   714,   720,
     724,   729,   734,   739,   746,   754,   753,   767,   766,   780,
     781,   784,   788,   792,   796,   800,   804,   808,   812,   816,
     822,   826,   831,   836,   841,   848,   856,   855,   874,   873,
     887,   888,   891,   898,   902,   906,   910,   914,   918,   924,
     931,   938,   946,   950,   955,   959,   963,   967,   971,   975,
     979,   983,   987,   991,   995,  1000,  1004,  1008,  1011,  1012,
    1015,  1023,  1028,  1035,  1050,  1058,  1062,  1067,  1071,  1076,
    1080,  1087,  1088,  1099,  1103,  1107,  1113,  1114,  1117,  1128,
    1129,  1132,  1138,  1147,  1159,  1160,  1161,  1162,  1163,  1164,
    1165,  1166,  1169,  1170,  1171,  1172,  1179,  1180,  1181,  1182,
    1185,  1190,  1197
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ROOM", "ITEM", "LINK", "FROM", "TAG",
  "TO", "DIR", "ONEWAY", "HIDDEN", "NODROP", "NOTE", "TASK", "AFTER",
  "NEED", "GET", "SCORE", "JOIN", "GO", "REQUIRE", "ANY", "LAST", "START",
  "GOTO", "MAP", "EXIT", "GIVEN", "LOST", "KEEP", "LENGTH", "TITLE",
  "LOSE", "SAFE", "BEFORE", "FOLLOW", "CMD", "LEAVE", "UNDEF", "FINISH",
  "GIVE", "DROP", "ALL", "EXCEPT", "IT", "UNTIL", "TIMES", "NOLINK",
  "NOPATH", "NONE", "STYLE", "ENDSTYLE", "WITH", "IGNORE", "DO", "THEM",
  "NORTH", "EAST", "SOUTH", "WEST", "NORTHEAST", "NORTHWEST", "SOUTHEAST",
  "SOUTHWEST", "UP", "DOWN", "IN", "OUT", "INTEGER", "TRUE", "FALSE",
  "REAL", "STRING", "ID", "';'", "'='", "$accept", "stmt_list", "stmt",
  "ctrl_stmt", "room_stmt", "@1", "@2", "room_attrs", "room_attr",
  "room_list", "room_elt", "room", "item_stmt", "@3", "@4", "item_attrs",
  "item_attr", "item_list", "item_list_all", "item_elt", "item",
  "link_stmt", "@5", "@6", "link_attrs", "link_attr", "join_stmt", "@7",
  "@8", "join_attrs", "join_attr", "task_stmt", "@9", "@10", "task_attrs",
  "task_attr", "task_list", "task_elt", "task", "vars_stmt", "set_var",
  "in_style", "style_stmt", "style_list", "style_elt", "dir_list",
  "dir_elt", "compass", "otherdir", "number", "strings", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,    59,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    79,    80,    80,    80,    82,    81,    83,    81,
      84,    84,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    86,    86,    87,    88,
      88,    88,    90,    89,    91,    89,    92,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    94,    94,    94,    95,    95,    95,
      96,    97,    97,    97,    99,    98,   100,    98,   101,   101,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   104,   103,   105,   103,   106,
     106,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   109,   108,   110,   108,
     111,   111,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   113,   113,
     114,   115,   115,   115,   116,   117,   117,   117,   117,   117,
     117,   118,   118,   119,   119,   119,   120,   120,   121,   122,
     122,   123,   123,   123,   124,   124,   124,   124,   124,   124,
     124,   124,   125,   125,   125,   125,   126,   126,   126,   126,
     127,   127,   127
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     0,     5,     0,     5,
       0,     2,     2,     4,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     2,     2,     1,     2,     1,     1,
       1,     1,     0,     5,     0,     5,     0,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     3,     3,     2,     2,
       2,     2,     1,     2,     1,     2,     1,     1,     1,     3,
       1,     1,     1,     1,     0,     7,     0,     5,     0,     2,
       2,     2,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     3,     3,     2,     2,     0,     7,     0,     5,     0,
       2,     2,     2,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     3,     3,     2,     2,     0,     5,     0,     5,
       0,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       4,     6,     3,     5,     3,     2,     2,     2,     2,     2,
       1,     1,     2,     1,     2,     2,     2,     2,     1,     2,
       1,     1,     1,     1,     1,     5,     6,     5,     6,     5,
       6,     0,     3,     3,     3,     2,     1,     2,     1,     1,
       2,     1,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     5,     6,     7,     8,
       9,    10,    11,   164,    12,    16,    18,    52,    54,    51,
      50,    86,     0,   126,   128,   107,     0,   196,   198,   199,
     197,     0,     0,     0,     0,     0,   175,     0,     0,    20,
      20,    56,    56,    88,     0,   130,   130,   109,     0,    15,
      14,    13,   173,   174,     0,   171,   171,   171,     0,     0,
       0,     0,     0,    49,    84,     0,     0,     0,   105,   171,
     171,   171,     0,     0,     0,     0,     0,     0,     0,    29,
      30,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,    34,    31,    32,     0,    17,    21,    19,
       0,    61,     0,     0,     0,     0,    62,    63,    65,     0,
      72,     0,    64,     0,    53,    57,    55,     0,     0,    92,
      93,     0,     0,     0,     0,     0,     0,     0,    94,     0,
      87,    89,    88,     0,     0,     0,     0,     0,     0,     0,
       0,   151,     0,     0,   153,     0,     0,     0,   150,     0,
       0,   127,   131,   129,     0,   113,   114,     0,     0,     0,
       0,     0,     0,     0,   115,     0,   108,   110,   109,     0,
       0,     0,     0,   169,   167,   165,    26,    46,    48,    22,
     184,   185,   186,   187,   188,   189,   190,   191,    24,   179,
     181,    44,   163,   162,   161,    37,   158,   160,    83,    82,
      76,    81,    35,    74,    80,    40,    27,   194,   195,   192,
     193,    28,    25,    39,    36,     0,     0,   200,    41,    78,
      77,    38,   178,    45,   176,    58,    60,    70,    68,    71,
       0,     0,    69,    73,    59,   103,    90,    97,    95,    91,
      99,    96,     0,     0,   100,    98,   104,     0,   132,   156,
     133,   134,   136,   152,   146,   145,   147,   155,   154,   135,
       0,     0,   138,   157,   137,   149,   148,   124,   118,   116,
     111,   112,   120,   117,     0,     0,   121,   119,   125,     0,
     170,   168,   166,   172,    47,     0,   180,     0,   182,   159,
      75,    43,    42,     0,   201,     0,   177,    67,    66,   102,
     101,    85,   144,   142,     0,     0,   123,   122,   106,    23,
     183,   202,    79,     0,   139,   140,   143,     0,   141
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    15,    16,    17,    49,    50,    68,   108,   186,
     187,   188,    18,    51,    52,    70,   125,   230,   231,   213,
     214,    19,   142,    53,    72,   141,    20,   178,    57,    77,
     177,    21,    55,    56,    75,   162,   205,   206,   207,    22,
      23,    83,    24,   233,   234,   198,   199,   200,   221,    41,
     228
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -215
static const yytype_int16 yypact[] =
{
    -215,    30,  -215,  -215,    45,    91,    -5,   105,    18,   255,
     -61,    -9,   -53,   111,   -52,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,    68,    77,  -215,  -215,    68,    82,  -215,  -215,  -215,
    -215,    20,    35,    38,    54,    62,  -215,    29,   216,  -215,
    -215,  -215,  -215,  -215,    57,  -215,  -215,  -215,    57,  -215,
    -215,  -215,  -215,  -215,   223,    73,    73,    73,   182,   229,
     348,   378,   424,  -215,  -215,   266,   298,   499,  -215,    73,
      73,    73,   117,    67,    95,    97,    57,   100,   420,  -215,
    -215,   103,    85,    32,   119,    57,   280,  -215,   420,   121,
      85,    -3,   110,  -215,  -215,  -215,   122,  -215,  -215,  -215,
     125,  -215,   130,    85,    32,   136,  -215,  -215,   116,    85,
    -215,   122,  -215,    57,  -215,  -215,  -215,   133,   420,  -215,
    -215,    85,    32,   280,   139,    85,     2,   110,  -215,   122,
    -215,  -215,  -215,   138,   141,    85,    32,    32,   149,    57,
      32,  -215,    85,   -23,  -215,    32,   137,   122,  -215,    85,
      -7,  -215,  -215,  -215,   147,  -215,  -215,    85,    32,   526,
     154,    85,     5,   110,  -215,   122,  -215,  -215,  -215,   135,
     150,   151,   153,  -215,  -215,  -215,    57,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    87,  -215,
     -41,  -215,  -215,  -215,  -215,    85,  -215,  -215,  -215,  -215,
    -215,  -215,    89,  -215,  -215,  -215,    57,  -215,  -215,  -215,
    -215,  -215,   420,  -215,    85,   156,   156,    47,  -215,   188,
      89,  -215,  -215,   122,  -215,  -215,  -215,    85,    89,  -215,
      85,    32,    85,   122,  -215,  -215,   420,    85,    89,  -215,
    -215,    85,   156,   156,  -215,  -215,   122,   456,  -215,  -215,
      85,    89,    89,  -215,  -215,    89,  -215,  -215,  -215,    89,
      85,    57,    69,   122,    85,  -215,  -215,  -215,    85,    89,
    -215,  -215,  -215,    85,   156,   156,  -215,  -215,   122,   531,
    -215,  -215,  -215,  -215,  -215,   161,  -215,   168,  -215,  -215,
    -215,  -215,  -215,   171,  -215,    32,  -215,    85,    89,  -215,
    -215,  -215,    85,   197,    85,    57,  -215,  -215,  -215,  -215,
    -215,  -215,    89,    85,    85,   200,    85,    85,    85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -215,  -215,  -215,  -215,  -215,  -215,  -215,   201,  -215,   155,
    -179,    -6,  -215,  -215,  -215,   202,  -215,   -89,   -34,  -141,
    -215,  -215,  -215,  -215,   126,  -215,  -215,  -215,  -215,    74,
    -215,  -215,  -215,  -215,   203,  -215,   -99,  -151,   106,  -215,
    -215,   263,  -215,   -74,  -214,   -14,  -111,    92,  -116,   -25,
    -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -50
static const yytype_int16 yytable[] =
{
      32,   224,    36,   225,   212,   226,   297,   294,   252,   254,
     253,   284,    42,   285,   237,   275,    29,   249,    29,   306,
     242,    44,    47,    67,    48,   238,   268,   267,   298,   306,
       2,     3,   247,     4,     5,     6,   251,   294,    30,    81,
      30,    29,   306,   248,     7,   286,   260,   243,    74,     8,
     227,     9,    78,   281,   299,   208,    10,   261,   262,   306,
     274,   265,    11,    30,    43,   256,   269,    73,   278,    31,
     227,   300,   283,   299,   306,   227,   -49,   209,   227,   279,
      29,    12,    13,   273,   222,    54,   299,   296,   210,   300,
      58,   299,    35,   295,   303,    59,   299,   300,   301,   302,
     299,   288,    30,   255,    14,    64,   211,   300,   202,   299,
      60,   296,   208,    61,   246,   314,   304,   244,    25,    26,
     300,   300,   272,   299,   300,   309,   310,   299,   300,    62,
     203,    73,   299,   208,   209,   296,   315,    63,   300,   287,
      82,   307,   183,   264,   190,   191,   192,   193,   194,   195,
     196,   197,   308,   229,   276,   209,   299,   316,   317,   204,
     208,   299,   240,   211,    27,    28,   210,   300,   182,   241,
     184,   312,   185,   299,   189,   299,   201,   299,    33,    34,
     229,   300,   209,   270,   211,    45,    46,    86,   215,    87,
     223,    88,    89,   210,    90,    91,   232,    92,    93,   235,
      94,    95,    96,   236,   271,   239,    97,   245,   250,    98,
     290,   211,   258,    99,   259,   324,   322,   100,   263,   101,
     102,   277,   103,   282,   326,   291,   292,   293,   328,   227,
     104,   105,   305,   106,    86,   319,    87,   320,    88,    89,
     321,    90,    91,   323,    92,    93,   327,    94,    95,    96,
     216,    69,   289,    97,    71,    65,    98,   107,   266,    76,
      99,   280,    79,     0,   100,   313,   101,   102,   257,   103,
       0,     0,     0,   143,     0,     0,     0,   104,   105,   144,
     106,   145,   146,   147,   148,    37,    38,    39,    40,    66,
       0,   149,    37,    38,    39,    40,    80,     0,     0,   150,
     151,     0,   152,   153,   109,   143,   154,   155,   156,   325,
       0,   144,     0,   145,   146,   147,   148,   157,     0,     0,
     158,   159,     0,   149,    37,    38,    39,    40,     0,    84,
      85,   150,   151,   160,   152,   153,     0,     0,   154,   155,
     156,   161,   179,   180,   181,   217,   218,   219,   220,   157,
       0,     0,   158,   159,     0,   110,     0,     0,     0,   111,
       0,   112,     0,   113,   114,   160,   115,     0,     0,     0,
       0,     0,     0,   163,     0,     0,   116,   117,   118,     0,
       0,     0,     0,   119,     0,   110,     0,     0,   120,   111,
       0,   112,     0,   113,   114,     0,   115,     0,     0,   121,
       0,     0,   122,     0,     0,     0,   116,   117,   118,     0,
       0,     0,     0,   119,     0,   123,     0,     0,   120,     0,
       0,     0,     0,   124,     0,     0,     0,     0,     0,   121,
       0,   127,   122,   128,   129,   130,     0,     0,     0,   131,
     132,     0,     0,     0,   133,   123,     0,     0,     0,     0,
       0,     0,     0,   126,     0,   134,     0,     0,     0,   135,
       0,   136,   137,   127,     0,   128,   129,   130,     0,     0,
       0,   131,   132,   138,     0,   139,   133,   190,   191,   192,
     193,   194,   195,   196,   197,     0,     0,   134,     0,     0,
       0,   135,     0,   136,   137,     0,     0,     0,     0,   140,
       0,     0,     0,     0,     0,   138,   164,   139,     0,   165,
     166,     0,     0,     0,   167,   168,     0,     0,     0,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     170,   311,     0,     0,   171,     0,   172,   173,   164,     0,
       0,   165,   166,     0,     0,     0,   167,   168,   174,     0,
     175,   169,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   170,     0,     0,     0,   171,     0,   172,   173,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
     174,     0,   175,   190,   191,   192,   193,   194,   195,   196,
     197,   217,   218,   219,   220,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   318
};

static const yytype_int16 yycheck[] =
{
       6,   100,     8,     6,    93,     8,    47,   186,     6,   136,
       8,     6,    73,     8,   113,    22,    23,   133,    23,   233,
     119,    74,    74,    48,    76,   114,   153,    50,    69,   243,
       0,     1,   131,     3,     4,     5,   135,   216,    45,    64,
      45,    23,   256,   132,    14,   172,   145,   121,    54,    19,
      73,    21,    58,   169,   205,    23,    26,   146,   147,   273,
     159,   150,    32,    45,    73,   139,   155,    74,   167,    74,
      73,   212,   171,   224,   288,    73,     8,    45,    73,   168,
      23,    51,    52,   157,    98,     8,   237,   198,    56,   230,
       8,   242,    74,     6,    47,    75,   247,   238,   225,   226,
     251,   175,    45,   137,    74,    76,    74,   248,    23,   260,
      75,   222,    23,    75,   128,    46,    69,   123,    73,    74,
     261,   262,   156,   274,   265,   252,   253,   278,   269,    75,
      45,    74,   283,    23,    45,   246,    67,    75,   279,   173,
      67,   240,    75,   149,    57,    58,    59,    60,    61,    62,
      63,    64,   241,    43,   160,    45,   307,   284,   285,    74,
      23,   312,    46,    74,    73,    74,    56,   308,    51,    53,
      75,   270,    75,   324,    74,   326,    73,   328,    73,    74,
      43,   322,    45,    46,    74,    74,    75,     5,    69,     7,
      69,     9,    10,    56,    12,    13,    74,    15,    16,    74,
      18,    19,    20,    73,    67,    69,    24,    74,    69,    27,
      75,    74,    74,    31,    73,   314,   305,    35,    69,    37,
      38,    74,    40,    69,   323,    75,    75,    74,   327,    73,
      48,    49,    44,    51,     5,    74,     7,    69,     9,    10,
      69,    12,    13,    46,    15,    16,    46,    18,    19,    20,
      95,    50,   178,    24,    52,    39,    27,    75,   152,    56,
      31,   169,    39,    -1,    35,   271,    37,    38,   142,    40,
      -1,    -1,    -1,     7,    -1,    -1,    -1,    48,    49,    13,
      51,    15,    16,    17,    18,    69,    70,    71,    72,    73,
      -1,    25,    69,    70,    71,    72,    73,    -1,    -1,    33,
      34,    -1,    36,    37,    75,     7,    40,    41,    42,   315,
      -1,    13,    -1,    15,    16,    17,    18,    51,    -1,    -1,
      54,    55,    -1,    25,    69,    70,    71,    72,    -1,    66,
      67,    33,    34,    67,    36,    37,    -1,    -1,    40,    41,
      42,    75,    79,    80,    81,    65,    66,    67,    68,    51,
      -1,    -1,    54,    55,    -1,     7,    -1,    -1,    -1,    11,
      -1,    13,    -1,    15,    16,    67,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    28,    29,    30,    -1,
      -1,    -1,    -1,    35,    -1,     7,    -1,    -1,    40,    11,
      -1,    13,    -1,    15,    16,    -1,    18,    -1,    -1,    51,
      -1,    -1,    54,    -1,    -1,    -1,    28,    29,    30,    -1,
      -1,    -1,    -1,    35,    -1,    67,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    51,
      -1,     7,    54,     9,    10,    11,    -1,    -1,    -1,    15,
      16,    -1,    -1,    -1,    20,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    31,    -1,    -1,    -1,    35,
      -1,    37,    38,     7,    -1,     9,    10,    11,    -1,    -1,
      -1,    15,    16,    49,    -1,    51,    20,    57,    58,    59,
      60,    61,    62,    63,    64,    -1,    -1,    31,    -1,    -1,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    49,     7,    51,    -1,    10,
      11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    75,    -1,    -1,    35,    -1,    37,    38,     7,    -1,
      -1,    10,    11,    -1,    -1,    -1,    15,    16,    49,    -1,
      51,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    51,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    78,     0,     1,     3,     4,     5,    14,    19,    21,
      26,    32,    51,    52,    74,    79,    80,    81,    89,    98,
     103,   108,   116,   117,   119,    73,    74,    73,    74,    23,
      45,    74,    88,    73,    74,    74,    88,    69,    70,    71,
      72,   126,    73,    73,    74,    74,    75,    74,    76,    82,
      83,    90,    91,   100,     8,   109,   110,   105,     8,    75,
      75,    75,    75,    75,    76,    39,    73,   126,    84,    84,
      92,    92,   101,    74,    88,   111,   111,   106,    88,    39,
      73,   126,    67,   118,   118,   118,     5,     7,     9,    10,
      12,    13,    15,    16,    18,    19,    20,    24,    27,    31,
      35,    37,    38,    40,    48,    49,    51,    75,    85,    75,
       7,    11,    13,    15,    16,    18,    28,    29,    30,    35,
      40,    51,    54,    67,    75,    93,    75,     7,     9,    10,
      11,    15,    16,    20,    31,    35,    37,    38,    49,    51,
      75,   102,    99,     7,    13,    15,    16,    17,    18,    25,
      33,    34,    36,    37,    40,    41,    42,    51,    54,    55,
      67,    75,   112,    75,     7,    10,    11,    15,    16,    20,
      31,    35,    37,    38,    49,    51,    75,   107,   104,   118,
     118,   118,    51,    75,    75,    75,    86,    87,    88,    74,
      57,    58,    59,    60,    61,    62,    63,    64,   122,   123,
     124,    73,    23,    45,    74,   113,   114,   115,    23,    45,
      56,    74,    94,    96,    97,    69,    86,    65,    66,    67,
      68,   125,   122,    69,   113,     6,     8,    73,   127,    43,
      94,    95,    74,   120,   121,    74,    73,   113,    94,    69,
      46,    53,   113,   120,    88,    74,   122,   113,    94,   125,
      69,   113,     6,     8,   127,    95,   120,   101,    74,    73,
     113,    94,    94,    69,    88,    94,   115,    50,   127,    94,
      46,    67,    95,   120,   113,    22,    88,    74,   113,    94,
     124,   125,    69,   113,     6,     8,   127,    95,   120,   106,
      75,    75,    75,    74,    87,     6,   123,    47,    69,   114,
      96,   127,   127,    47,    69,    44,   121,   113,    94,   127,
     127,    75,   113,    88,    46,    67,   127,   127,    75,    74,
      69,    69,    94,    46,   113,    88,   113,    46,   113
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


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
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 13:
#line 140 "ifm-parse.y"
    {
                    vh_sstore(map, "TITLE", (yyvsp[(2) - (3)].sval));
                }
    break;

  case 14:
#line 144 "ifm-parse.y"
    {
                    if (sectnames == NULL)
                        sectnames = vl_create();
                    vl_spush(sectnames, (yyvsp[(2) - (3)].sval));
                }
    break;

  case 15:
#line 150 "ifm-parse.y"
    {
                    float version;
                    sscanf(VERSION, "%f", &version);
                    if ((yyvsp[(2) - (3)].dval) - version > 0.001)
                        fatal("version %g of IFM is required (this is %s)",
                              (yyvsp[(2) - (3)].dval), VERSION);
                }
    break;

  case 16:
#line 164 "ifm-parse.y"
    {
                    curobj = vh_create();
		    vh_sstore(curobj, "DESC", (yyvsp[(2) - (2)].sval));
                    vh_istore(curobj, "ID", roomid++);
                    vh_pstore(curobj, "STYLE", current_styles());
                    vh_pstore(curobj, "LINK_STYLE", current_styles());
                    implicit = 0;
                    modify = 0;
		}
    break;

  case 17:
#line 174 "ifm-parse.y"
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
                    RESET;
                }
    break;

  case 18:
#line 267 "ifm-parse.y"
    {
                    implicit = 0;
                    modify = 1;
                    if ((curobj = vh_pget(roomtags, (yyvsp[(2) - (2)].sval))) == NULL) {
                        err("room tag '%s' not yet defined", (yyvsp[(2) - (2)].sval));
                        curobj = vh_create();
                    }
                }
    break;

  case 19:
#line 276 "ifm-parse.y"
    {
                    RESET;
                }
    break;

  case 22:
#line 286 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("room", (yyvsp[(2) - (2)].sval), curobj, roomtags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 23:
#line 293 "ifm-parse.y"
    {
                    vhash *room;

                    if (!modify) {
                        implicit = 1;

                        vh_pstore(curobj, "DIR", curdirs);
                        curdirs = NULL;

                        if ((room = vh_pget(roomtags, (yyvsp[(4) - (4)].sval))) != NULL)
                            vh_pstore(curobj, "NEAR", room);
                        else
                            err("room tag '%s' not yet defined", (yyvsp[(4) - (4)].sval));
                    } else {
                        CHANGE_ERROR(from);
                    }
		}
    break;

  case 24:
#line 311 "ifm-parse.y"
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

  case 25:
#line 326 "ifm-parse.y"
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

  case 26:
#line 339 "ifm-parse.y"
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

  case 27:
#line 356 "ifm-parse.y"
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

  case 28:
#line 373 "ifm-parse.y"
    {
                    vh_istore(curobj, "GO", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 29:
#line 377 "ifm-parse.y"
    {
                    vh_istore(curobj, "ONEWAY", 1);
		}
    break;

  case 30:
#line 381 "ifm-parse.y"
    {
                    vh_istore(curobj, "NODROP", 1);
		}
    break;

  case 31:
#line 385 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOLINK", 1);
		}
    break;

  case 32:
#line 389 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOPATH", 1);
		}
    break;

  case 33:
#line 393 "ifm-parse.y"
    {
                    startroom = curobj;
		}
    break;

  case 34:
#line 397 "ifm-parse.y"
    {
                    vh_istore(curobj, "FINISH", 1);
                }
    break;

  case 35:
#line 401 "ifm-parse.y"
    {
                    SET_LIST(curobj, ATTR(NEED), curitems);
                }
    break;

  case 36:
#line 405 "ifm-parse.y"
    {
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		}
    break;

  case 37:
#line 409 "ifm-parse.y"
    {
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		}
    break;

  case 38:
#line 413 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                }
    break;

  case 39:
#line 419 "ifm-parse.y"
    {
                    vh_istore(curobj, "LEN", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 40:
#line 423 "ifm-parse.y"
    {
                    vh_istore(curobj, "SCORE", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 41:
#line 427 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(2) - (2)].sval));
                }
    break;

  case 42:
#line 432 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 43:
#line 437 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 44:
#line 442 "ifm-parse.y"
    {
                    add_attr(curobj, "NOTE", (yyvsp[(2) - (2)].sval));
		}
    break;

  case 48:
#line 453 "ifm-parse.y"
    {
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, (yyvsp[(1) - (1)].vval));
		}
    break;

  case 49:
#line 461 "ifm-parse.y"
    {
                    (yyval.vval) = vs_screate((yyvsp[(1) - (1)].sval));
                    itroom = vs_copy((yyval.vval));
                }
    break;

  case 50:
#line 466 "ifm-parse.y"
    {
                    if (itroom == NULL)
                        err("no room referred to by 'it'");
                    else
                        (yyval.vval) = vs_copy(itroom);
                }
    break;

  case 51:
#line 473 "ifm-parse.y"
    {
                    if (lastroom == NULL) {
                        err("no room referred to by 'last'");
                    } else {
                        (yyval.vval) = vs_pcreate(lastroom);
                        itroom = vs_copy((yyval.vval));
                    }                        
                }
    break;

  case 52:
#line 488 "ifm-parse.y"
    {
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", (yyvsp[(2) - (2)].sval));
                    vh_istore(curobj, "ID", itemid++);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;

  case 53:
#line 496 "ifm-parse.y"
    {
                    if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lastitem = curobj;
                    vl_ppush(items, curobj);
                    RESET;
		}
    break;

  case 54:
#line 505 "ifm-parse.y"
    {
                    modify = 1;
                    if ((curobj = vh_pget(itemtags, (yyvsp[(2) - (2)].sval))) == NULL) {
                        err("item tag '%s' not yet defined", (yyvsp[(2) - (2)].sval));
                        curobj = vh_create();
                    }
                }
    break;

  case 55:
#line 513 "ifm-parse.y"
    {
                    RESET;
                }
    break;

  case 58:
#line 523 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("item", (yyvsp[(2) - (2)].sval), curobj, itemtags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 59:
#line 530 "ifm-parse.y"
    {
                    vh_store(curobj, "IN", (yyvsp[(2) - (2)].vval));
		}
    break;

  case 60:
#line 534 "ifm-parse.y"
    {
                    add_attr(curobj, "NOTE", (yyvsp[(2) - (2)].sval));
		}
    break;

  case 61:
#line 538 "ifm-parse.y"
    {
                    vh_istore(curobj, "HIDDEN", 1);
		}
    break;

  case 62:
#line 542 "ifm-parse.y"
    {
                    obsolete("'given' attribute", "task 'give' attribute");
                    vh_istore(curobj, "GIVEN", 1);
		}
    break;

  case 63:
#line 547 "ifm-parse.y"
    {
                    vh_istore(curobj, "LOST", 1);
		}
    break;

  case 64:
#line 551 "ifm-parse.y"
    {
                    vh_istore(curobj, "IGNORE", 1);
		}
    break;

  case 65:
#line 555 "ifm-parse.y"
    {
                    vh_istore(curobj, "KEEP", 1);
		}
    break;

  case 66:
#line 559 "ifm-parse.y"
    {
                    SET_LIST(curobj, "KEEP_WITH", curitems);
		}
    break;

  case 67:
#line 563 "ifm-parse.y"
    {
                    SET_LIST(curobj, "KEEP_UNTIL", curtasks);
		}
    break;

  case 68:
#line 567 "ifm-parse.y"
    {
                    SET_LIST(curobj, "NEED", curitems);
                }
    break;

  case 69:
#line 571 "ifm-parse.y"
    {
                    SET_LIST(curobj, "BEFORE", curtasks);
                }
    break;

  case 70:
#line 575 "ifm-parse.y"
    {
                    SET_LIST(curobj, "AFTER", curtasks);
                }
    break;

  case 71:
#line 579 "ifm-parse.y"
    {
                    vh_istore(curobj, "SCORE", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 72:
#line 583 "ifm-parse.y"
    {
                    vh_istore(curobj, "FINISH", 1);
                }
    break;

  case 76:
#line 592 "ifm-parse.y"
    {
                    if (themitems != NULL) {
                        if (curitems == NULL)
                            curitems = vl_copy(themitems);
                        else
                            vl_append(curitems, themitems);
                    } else {
                        err("no items referred to by 'them'");
                    }
                }
    break;

  case 77:
#line 604 "ifm-parse.y"
    { allflag = 0; }
    break;

  case 78:
#line 605 "ifm-parse.y"
    { allflag = 1; }
    break;

  case 79:
#line 606 "ifm-parse.y"
    { allflag = 1; }
    break;

  case 80:
#line 610 "ifm-parse.y"
    {
                    if (curitems == NULL)
                        curitems = vl_create();

                    vl_push(curitems, (yyvsp[(1) - (1)].vval));

                    if (themitems == NULL)
                        themitems = vl_create();

                    vl_push(themitems, vs_copy((yyvsp[(1) - (1)].vval)));
		}
    break;

  case 81:
#line 624 "ifm-parse.y"
    {
                    (yyval.vval) = vs_screate((yyvsp[(1) - (1)].sval));
                    ititem = vs_copy((yyval.vval));
                }
    break;

  case 82:
#line 629 "ifm-parse.y"
    {
                    if (ititem == NULL)
                        err("no item referred to by 'it'");
                    else
                        (yyval.vval) = vs_copy(ititem);
                }
    break;

  case 83:
#line 636 "ifm-parse.y"
    {
                    if (lastitem == NULL) {
                        err("no item referred to by 'last'");
                    } else {
                        (yyval.vval) = vs_pcreate(lastitem);
                        ititem = vs_copy((yyval.vval));
                    }
                }
    break;

  case 84:
#line 651 "ifm-parse.y"
    {
                    curobj = vh_create();
                    vh_store(curobj, "FROM", (yyvsp[(2) - (4)].vval));
                    vh_store(curobj, "TO", (yyvsp[(4) - (4)].vval));
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;

  case 85:
#line 659 "ifm-parse.y"
    {
                    vl_ppush(links, curobj);
                    RESET;
		}
    break;

  case 86:
#line 664 "ifm-parse.y"
    {
                    modify = 1;
                    if ((curobj = vh_pget(linktags, (yyvsp[(2) - (2)].sval))) == NULL) {
                        err("link tag '%s' not yet defined", (yyvsp[(2) - (2)].sval));
                        curobj = vh_create();
                    }
                }
    break;

  case 87:
#line 672 "ifm-parse.y"
    {
                    RESET;
                }
    break;

  case 90:
#line 682 "ifm-parse.y"
    {
                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;
		}
    break;

  case 91:
#line 687 "ifm-parse.y"
    {
                    vh_istore(curobj, "GO", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 92:
#line 691 "ifm-parse.y"
    {
                    vh_istore(curobj, "ONEWAY", 1);
		}
    break;

  case 93:
#line 695 "ifm-parse.y"
    {
                    vh_istore(curobj, "HIDDEN", 1);
		}
    break;

  case 94:
#line 699 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOPATH", 1);
		}
    break;

  case 95:
#line 703 "ifm-parse.y"
    {
                    SET_LIST(curobj, "NEED", curitems);
                }
    break;

  case 96:
#line 707 "ifm-parse.y"
    {
                    SET_LIST(curobj, "BEFORE", curtasks);
		}
    break;

  case 97:
#line 711 "ifm-parse.y"
    {
                    SET_LIST(curobj, "AFTER", curtasks);
		}
    break;

  case 98:
#line 715 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                }
    break;

  case 99:
#line 721 "ifm-parse.y"
    {
                    vh_istore(curobj, "LEN", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 100:
#line 725 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(2) - (2)].sval));
                }
    break;

  case 101:
#line 730 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 102:
#line 735 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 103:
#line 740 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("link", (yyvsp[(2) - (2)].sval), curobj, linktags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 105:
#line 754 "ifm-parse.y"
    {
                    curobj = vh_create();
                    vh_store(curobj, "FROM", (yyvsp[(2) - (4)].vval));
                    vh_store(curobj, "TO", (yyvsp[(4) - (4)].vval));
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;

  case 106:
#line 762 "ifm-parse.y"
    {
                    vl_ppush(joins, curobj);
                    RESET;
		}
    break;

  case 107:
#line 767 "ifm-parse.y"
    {
                    modify = 1;
                    if ((curobj = vh_pget(jointags, (yyvsp[(2) - (2)].sval))) == NULL) {
                        err("join tag '%s' not yet defined", (yyvsp[(2) - (2)].sval));
                        curobj = vh_create();
                    }
                }
    break;

  case 108:
#line 775 "ifm-parse.y"
    {
                    RESET;
                }
    break;

  case 111:
#line 785 "ifm-parse.y"
    {
                    vh_istore(curobj, "GO", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 112:
#line 789 "ifm-parse.y"
    {
                    vh_istore(curobj, "GO", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 113:
#line 793 "ifm-parse.y"
    {
                    vh_istore(curobj, "ONEWAY", 1);
		}
    break;

  case 114:
#line 797 "ifm-parse.y"
    {
                    vh_istore(curobj, "HIDDEN", 1);
		}
    break;

  case 115:
#line 801 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOPATH", 1);
		}
    break;

  case 116:
#line 805 "ifm-parse.y"
    {
                    SET_LIST(curobj, "NEED", curitems);
                }
    break;

  case 117:
#line 809 "ifm-parse.y"
    {
                    SET_LIST(curobj, "BEFORE", curtasks);
		}
    break;

  case 118:
#line 813 "ifm-parse.y"
    {
                    SET_LIST(curobj, "AFTER", curtasks);
		}
    break;

  case 119:
#line 817 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                }
    break;

  case 120:
#line 823 "ifm-parse.y"
    {
                    vh_istore(curobj, "LEN", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 121:
#line 827 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(2) - (2)].sval));
                }
    break;

  case 122:
#line 832 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 123:
#line 837 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 124:
#line 842 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("join", (yyvsp[(2) - (2)].sval), curobj, jointags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 126:
#line 856 "ifm-parse.y"
    {
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", (yyvsp[(2) - (2)].sval));
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;

  case 127:
#line 863 "ifm-parse.y"
    {
                    if (vh_iget(curobj, "NOROOM"))
                        vh_pstore(curobj, "IN", NULL);
                    else if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lasttask = curobj;
                    vl_ppush(tasks, curobj);
                    RESET;
		}
    break;

  case 128:
#line 874 "ifm-parse.y"
    {
                    modify = 1;
                    if ((curobj = vh_pget(tasktags, (yyvsp[(2) - (2)].sval))) == NULL) {
                        err("task tag '%s' not yet defined", (yyvsp[(2) - (2)].sval));
                        curobj = vh_create();
                    }
                }
    break;

  case 129:
#line 882 "ifm-parse.y"
    {
                    RESET;
                }
    break;

  case 132:
#line 892 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("task", (yyvsp[(2) - (2)].sval), curobj, tasktags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 133:
#line 899 "ifm-parse.y"
    {
                    SET_LIST(curobj, "AFTER", curtasks);
		}
    break;

  case 134:
#line 903 "ifm-parse.y"
    {
                    SET_LIST(curobj, "NEED", curitems);
		}
    break;

  case 135:
#line 907 "ifm-parse.y"
    {
                    SET_LIST(curobj, "GIVE", curitems);
		}
    break;

  case 136:
#line 911 "ifm-parse.y"
    {
                    SET_LIST(curobj, "GET", curitems);
		}
    break;

  case 137:
#line 915 "ifm-parse.y"
    {
                    SET_LIST(curobj, "DO", curtasks);
		}
    break;

  case 138:
#line 919 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
		}
    break;

  case 139:
#line 925 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		}
    break;

  case 140:
#line 932 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", (yyvsp[(4) - (4)].vval));
		}
    break;

  case 141:
#line 939 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", (yyvsp[(4) - (6)].vval));
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		}
    break;

  case 142:
#line 947 "ifm-parse.y"
    {
                    vh_store(curobj, "DROPROOM", (yyvsp[(3) - (3)].vval));
		}
    break;

  case 143:
#line 951 "ifm-parse.y"
    {
                    vh_store(curobj, "DROPROOM", (yyvsp[(3) - (5)].vval));
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		}
    break;

  case 144:
#line 956 "ifm-parse.y"
    {
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
                }
    break;

  case 145:
#line 960 "ifm-parse.y"
    {
                    SET_LIST(curobj, "LOSE", curitems);
		}
    break;

  case 146:
#line 964 "ifm-parse.y"
    {
                    vh_store(curobj, "GOTO", (yyvsp[(2) - (2)].vval));
                }
    break;

  case 147:
#line 968 "ifm-parse.y"
    {
                    vh_store(curobj, "FOLLOW", (yyvsp[(2) - (2)].vval));
                }
    break;

  case 148:
#line 972 "ifm-parse.y"
    {
                    vh_store(curobj, "IN", (yyvsp[(2) - (2)].vval));
		}
    break;

  case 149:
#line 976 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOROOM", 1);
		}
    break;

  case 150:
#line 980 "ifm-parse.y"
    {
                    vh_istore(curobj, "IGNORE", 1);
		}
    break;

  case 151:
#line 984 "ifm-parse.y"
    {
                    vh_istore(curobj, "SAFE", 1);
                }
    break;

  case 152:
#line 988 "ifm-parse.y"
    {
                    vh_istore(curobj, "SCORE", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 153:
#line 992 "ifm-parse.y"
    {
                    vh_istore(curobj, "FINISH", 1);
                }
    break;

  case 154:
#line 996 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", (yyvsp[(2) - (2)].sval));
                }
    break;

  case 155:
#line 1001 "ifm-parse.y"
    {
                    add_attr(curobj, "CMD", NULL);
                }
    break;

  case 156:
#line 1005 "ifm-parse.y"
    {
                    add_attr(curobj, "NOTE", (yyvsp[(2) - (2)].sval));
		}
    break;

  case 160:
#line 1016 "ifm-parse.y"
    {
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, (yyvsp[(1) - (1)].vval));
		}
    break;

  case 161:
#line 1024 "ifm-parse.y"
    {
                    (yyval.vval) = vs_screate((yyvsp[(1) - (1)].sval));
                    ittask = vs_copy((yyval.vval));
                }
    break;

  case 162:
#line 1029 "ifm-parse.y"
    {
                    if (ittask == NULL)
                        err("no task referred to by 'it'");
                    else
                        (yyval.vval) = vs_copy(ittask);
                }
    break;

  case 163:
#line 1036 "ifm-parse.y"
    {
                    if (lasttask == NULL) {
                        err("no task referred to by 'last'");
                    } else {
                        (yyval.vval) = vs_pcreate(lasttask);
                        ittask = vs_copy((yyval.vval));
                    }
                }
    break;

  case 164:
#line 1051 "ifm-parse.y"
    {
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                }
    break;

  case 165:
#line 1059 "ifm-parse.y"
    {
                    var_set(NULL, (yyvsp[(1) - (5)].sval), vs_dcreate((yyvsp[(3) - (5)].dval)));
                }
    break;

  case 166:
#line 1063 "ifm-parse.y"
    {
                    var_set((yyvsp[(1) - (6)].sval), (yyvsp[(2) - (6)].sval), vs_dcreate((yyvsp[(4) - (6)].dval)));
                    obsolete("variable assignment", "dotted notation");
                }
    break;

  case 167:
#line 1068 "ifm-parse.y"
    {
                    var_set(NULL, (yyvsp[(1) - (5)].sval), vs_screate((yyvsp[(3) - (5)].sval)));
                }
    break;

  case 168:
#line 1072 "ifm-parse.y"
    {
                    var_set((yyvsp[(1) - (6)].sval), (yyvsp[(2) - (6)].sval), vs_screate((yyvsp[(4) - (6)].sval)));
                    obsolete("variable assignment", "dotted notation");
                }
    break;

  case 169:
#line 1077 "ifm-parse.y"
    {
                    var_set(NULL, (yyvsp[(1) - (5)].sval), NULL);
                }
    break;

  case 170:
#line 1081 "ifm-parse.y"
    {
                    var_set((yyvsp[(1) - (6)].sval), (yyvsp[(2) - (6)].sval), NULL);
                    obsolete("variable assignment", "dotted notation");
                }
    break;

  case 172:
#line 1089 "ifm-parse.y"
    {
                    push_style((yyvsp[(3) - (3)].sval));
                    instyle++;
                }
    break;

  case 173:
#line 1100 "ifm-parse.y"
    {
                    push_style((yyvsp[(2) - (3)].sval));
                }
    break;

  case 174:
#line 1104 "ifm-parse.y"
    {
                    pop_style((yyvsp[(2) - (3)].sval));
                }
    break;

  case 175:
#line 1108 "ifm-parse.y"
    {
                    pop_style(NULL);
                }
    break;

  case 178:
#line 1118 "ifm-parse.y"
    {
                    add_attr(curobj, "STYLE", (yyvsp[(1) - (1)].sval));
                    ref_style((yyvsp[(1) - (1)].sval));
                }
    break;

  case 181:
#line 1133 "ifm-parse.y"
    {
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, (yyvsp[(1) - (1)].ival));
		}
    break;

  case 182:
#line 1139 "ifm-parse.y"
    {
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if ((yyvsp[(2) - (2)].ival) <= 0)
                        err("invalid repeat count");
                    while ((yyvsp[(2) - (2)].ival)-- > 0)
                        vl_ipush(curdirs, (yyvsp[(1) - (2)].ival));
                }
    break;

  case 183:
#line 1148 "ifm-parse.y"
    {
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if ((yyvsp[(3) - (3)].ival) <= 0)
                        err("invalid repeat count");
                    while ((yyvsp[(3) - (3)].ival)-- > 0)
                        vl_ipush(curdirs, (yyvsp[(1) - (3)].ival));
                    obsolete("'times' keyword", "just the repeat count");
                }
    break;

  case 184:
#line 1159 "ifm-parse.y"
    { (yyval.ival) = D_NORTH;	    }
    break;

  case 185:
#line 1160 "ifm-parse.y"
    { (yyval.ival) = D_EAST;	    }
    break;

  case 186:
#line 1161 "ifm-parse.y"
    { (yyval.ival) = D_SOUTH;	    }
    break;

  case 187:
#line 1162 "ifm-parse.y"
    { (yyval.ival) = D_WEST;	    }
    break;

  case 188:
#line 1163 "ifm-parse.y"
    { (yyval.ival) = D_NORTHEAST; }
    break;

  case 189:
#line 1164 "ifm-parse.y"
    { (yyval.ival) = D_NORTHWEST; }
    break;

  case 190:
#line 1165 "ifm-parse.y"
    { (yyval.ival) = D_SOUTHEAST; }
    break;

  case 191:
#line 1166 "ifm-parse.y"
    { (yyval.ival) = D_SOUTHWEST; }
    break;

  case 192:
#line 1169 "ifm-parse.y"
    { (yyval.ival) = D_IN;   }
    break;

  case 193:
#line 1170 "ifm-parse.y"
    { (yyval.ival) = D_OUT;  }
    break;

  case 194:
#line 1171 "ifm-parse.y"
    { (yyval.ival) = D_UP;   }
    break;

  case 195:
#line 1172 "ifm-parse.y"
    { (yyval.ival) = D_DOWN; }
    break;

  case 196:
#line 1179 "ifm-parse.y"
    { (yyval.dval) = (yyvsp[(1) - (1)].ival); }
    break;

  case 197:
#line 1180 "ifm-parse.y"
    { (yyval.dval) = (yyvsp[(1) - (1)].dval); }
    break;

  case 198:
#line 1181 "ifm-parse.y"
    { (yyval.dval) =  1; }
    break;

  case 199:
#line 1182 "ifm-parse.y"
    { (yyval.dval) =  0; }
    break;

  case 200:
#line 1186 "ifm-parse.y"
    {
                    (yyval.sval) = (yyvsp[(1) - (1)].sval);
                    repeat = 1;
                }
    break;

  case 201:
#line 1191 "ifm-parse.y"
    {
                    (yyval.sval) = (yyvsp[(1) - (2)].sval);
                    repeat = (yyvsp[(2) - (2)].ival);
                    if ((yyvsp[(2) - (2)].ival) <= 0)
                        err("invalid repeat count");
                }
    break;

  case 202:
#line 1198 "ifm-parse.y"
    {
                    (yyval.sval) = (yyvsp[(1) - (3)].sval);
                    repeat = (yyvsp[(3) - (3)].ival);
                    if ((yyvsp[(3) - (3)].ival) <= 0)
                        err("invalid repeat count");
                    obsolete("'times' keyword", "just the repeat count");
                }
    break;


/* Line 1267 of yacc.c.  */
#line 3364 "ifm-parse.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1207 "ifm-parse.y"


