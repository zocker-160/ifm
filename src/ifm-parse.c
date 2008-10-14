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
     NORTH = 311,
     EAST = 312,
     SOUTH = 313,
     WEST = 314,
     NORTHEAST = 315,
     NORTHWEST = 316,
     SOUTHEAST = 317,
     SOUTHWEST = 318,
     UP = 319,
     DOWN = 320,
     IN = 321,
     OUT = 322,
     INTEGER = 323,
     TRUE = 324,
     FALSE = 325,
     REAL = 326,
     STRING = 327,
     ID = 328
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
#define NORTH 311
#define EAST 312
#define SOUTH 313
#define WEST 314
#define NORTHEAST 315
#define NORTHWEST 316
#define SOUTHEAST 317
#define SOUTHWEST 318
#define UP 319
#define DOWN 320
#define IN 321
#define OUT 322
#define INTEGER 323
#define TRUE 324
#define FALSE 325
#define REAL 326
#define STRING 327
#define ID 328




/* Copy the first part of user declarations.  */
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
#line 71 "ifm-parse.y"
{
    int ival;
    double dval;
    char *sval;
    vscalar *vval;
}
/* Line 193 of yacc.c.  */
#line 319 "ifm-parse.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 332 "ifm-parse.c"

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
#define YYLAST   552

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  201
/* YYNRULES -- Number of states.  */
#define YYNSTATES  328

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

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
       2,     2,     2,     2,     2,     2,     2,     2,     2,    74,
       2,    75,     2,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73
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
     190,   193,   196,   198,   201,   203,   206,   208,   210,   214,
     216,   218,   220,   222,   223,   231,   232,   238,   239,   242,
     245,   248,   250,   252,   254,   257,   260,   263,   266,   269,
     272,   276,   280,   283,   286,   287,   295,   296,   302,   303,
     306,   309,   312,   314,   316,   318,   321,   324,   327,   330,
     333,   336,   340,   344,   347,   350,   351,   357,   358,   364,
     365,   368,   371,   374,   377,   380,   383,   386,   389,   394,
     399,   406,   410,   416,   420,   423,   426,   429,   432,   435,
     437,   439,   442,   444,   447,   450,   453,   456,   458,   461,
     463,   465,   467,   469,   471,   477,   484,   490,   497,   503,
     510,   511,   515,   519,   523,   526,   528,   531,   533,   535,
     538,   540,   543,   547,   549,   551,   553,   555,   557,   559,
     561,   563,   565,   567,   569,   571,   573,   575,   577,   579,
     581,   584
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      77,     0,    -1,    -1,    77,    78,    -1,    77,     1,    -1,
      79,    -1,    80,    -1,    88,    -1,    97,    -1,   102,    -1,
     107,    -1,   115,    -1,   118,    -1,    32,    72,    74,    -1,
      26,    72,    74,    -1,    21,   125,    74,    -1,    -1,     3,
      72,    81,    83,    74,    -1,    -1,     3,    73,    82,    83,
      74,    -1,    -1,    83,    84,    -1,     7,    73,    -1,     9,
     121,     6,    73,    -1,     9,   121,    -1,    27,   121,    -1,
       5,    85,    -1,    19,    85,    -1,    20,   124,    -1,    10,
      -1,    12,    -1,    48,    -1,    49,    -1,    24,    -1,    40,
      -1,    16,    93,    -1,    35,   112,    -1,    15,   112,    -1,
      38,    94,    -1,    31,    68,    -1,    18,    68,    -1,    37,
     126,    -1,    37,     8,   126,    -1,    37,     6,   126,    -1,
      13,    72,    -1,    51,   119,    -1,    86,    -1,    85,    86,
      -1,    87,    -1,    73,    -1,    45,    -1,    23,    -1,    -1,
       4,    72,    89,    91,    74,    -1,    -1,     4,    73,    90,
      91,    74,    -1,    -1,    91,    92,    -1,     7,    73,    -1,
      66,    87,    -1,    13,    72,    -1,    11,    -1,    28,    -1,
      29,    -1,    54,    -1,    30,    -1,    30,    53,    93,    -1,
      30,    46,   112,    -1,    16,    93,    -1,    35,   112,    -1,
      15,   112,    -1,    18,    68,    -1,    40,    -1,    51,   119,
      -1,    95,    -1,    93,    95,    -1,    93,    -1,    43,    -1,
      43,    44,    93,    -1,    96,    -1,    73,    -1,    45,    -1,
      23,    -1,    -1,     5,    87,     8,    87,    98,   100,    74,
      -1,    -1,     5,    73,    99,   100,    74,    -1,    -1,   100,
     101,    -1,     9,   121,    -1,    20,   124,    -1,    10,    -1,
      11,    -1,    49,    -1,    16,    93,    -1,    35,   112,    -1,
      15,   112,    -1,    38,    94,    -1,    31,    68,    -1,    37,
     126,    -1,    37,     8,   126,    -1,    37,     6,   126,    -1,
       7,    73,    -1,    51,   119,    -1,    -1,    19,    87,     8,
      87,   103,   105,    74,    -1,    -1,    19,    73,   104,   105,
      74,    -1,    -1,   105,   106,    -1,    20,   123,    -1,    20,
     124,    -1,    10,    -1,    11,    -1,    49,    -1,    16,    93,
      -1,    35,   112,    -1,    15,   112,    -1,    38,    94,    -1,
      31,    68,    -1,    37,   126,    -1,    37,     8,   126,    -1,
      37,     6,   126,    -1,     7,    73,    -1,    51,   119,    -1,
      -1,    14,    72,   108,   110,    74,    -1,    -1,    14,    73,
     109,   110,    74,    -1,    -1,   110,   111,    -1,     7,    73,
      -1,    15,   112,    -1,    16,    93,    -1,    41,    93,    -1,
      17,    93,    -1,    55,   112,    -1,    42,    94,    -1,    42,
      94,    46,   112,    -1,    42,    94,    66,    87,    -1,    42,
      94,    66,    87,    46,   112,    -1,    42,    66,    87,    -1,
      42,    66,    87,    46,   112,    -1,    42,    46,   112,    -1,
      33,    93,    -1,    25,    87,    -1,    36,   114,    -1,    66,
      87,    -1,    66,    22,    -1,    54,    -1,    34,    -1,    18,
      68,    -1,    40,    -1,    37,   126,    -1,    37,    50,    -1,
      13,    72,    -1,    51,   119,    -1,   113,    -1,   112,   113,
      -1,   114,    -1,    73,    -1,    45,    -1,    23,    -1,   116,
      -1,    73,    75,   125,   117,    74,    -1,    73,    73,    75,
     125,   117,    74,    -1,    73,    75,    72,   117,    74,    -1,
      73,    73,    75,    72,   117,    74,    -1,    73,    75,    39,
     117,    74,    -1,    73,    73,    75,    39,   117,    74,    -1,
      -1,    66,    51,    73,    -1,    51,    73,    74,    -1,    52,
      73,    74,    -1,    52,    74,    -1,   120,    -1,   119,   120,
      -1,    73,    -1,   122,    -1,   121,   122,    -1,   123,    -1,
     123,    68,    -1,   123,    47,    68,    -1,    56,    -1,    57,
      -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,    62,
      -1,    63,    -1,    66,    -1,    67,    -1,    64,    -1,    65,
      -1,    68,    -1,    71,    -1,    69,    -1,    70,    -1,    72,
      -1,    72,    68,    -1,    72,    47,    68,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   105,   106,   109,   110,   111,   112,   113,
     114,   115,   116,   123,   127,   133,   148,   147,   251,   250,
     265,   266,   269,   276,   294,   309,   322,   339,   356,   360,
     364,   368,   372,   376,   380,   384,   388,   392,   396,   402,
     406,   410,   415,   420,   425,   429,   432,   433,   436,   444,
     449,   456,   472,   471,   489,   488,   502,   503,   506,   513,
     517,   521,   525,   530,   534,   538,   542,   546,   550,   554,
     558,   562,   566,   570,   573,   574,   577,   578,   579,   582,
     590,   595,   602,   618,   617,   631,   630,   644,   645,   648,
     653,   657,   661,   665,   669,   673,   677,   681,   687,   691,
     696,   701,   706,   713,   721,   720,   734,   733,   747,   748,
     751,   755,   759,   763,   767,   771,   775,   779,   783,   789,
     793,   798,   803,   808,   815,   823,   822,   841,   840,   854,
     855,   858,   865,   869,   873,   877,   881,   885,   891,   898,
     905,   913,   917,   922,   926,   930,   934,   938,   942,   946,
     950,   954,   958,   962,   967,   971,   975,   978,   979,   982,
     990,   995,  1002,  1017,  1025,  1029,  1034,  1038,  1043,  1047,
    1054,  1055,  1066,  1070,  1074,  1080,  1081,  1084,  1095,  1096,
    1099,  1105,  1114,  1126,  1127,  1128,  1129,  1130,  1131,  1132,
    1133,  1136,  1137,  1138,  1139,  1146,  1147,  1148,  1149,  1152,
    1157,  1164
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
  "NOPATH", "NONE", "STYLE", "ENDSTYLE", "WITH", "IGNORE", "DO", "NORTH",
  "EAST", "SOUTH", "WEST", "NORTHEAST", "NORTHWEST", "SOUTHEAST",
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
     325,   326,   327,   328,    59,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    77,    77,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    79,    79,    81,    80,    82,    80,
      83,    83,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    85,    85,    86,    87,
      87,    87,    89,    88,    90,    88,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    93,    93,    94,    94,    94,    95,
      96,    96,    96,    98,    97,    99,    97,   100,   100,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   103,   102,   104,   102,   105,   105,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   108,   107,   109,   107,   110,
     110,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   112,   112,   113,
     114,   114,   114,   115,   116,   116,   116,   116,   116,   116,
     117,   117,   118,   118,   118,   119,   119,   120,   121,   121,
     122,   122,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   124,   124,   124,   124,   125,   125,   125,   125,   126,
     126,   126
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
       2,     2,     1,     2,     1,     2,     1,     1,     3,     1,
       1,     1,     1,     0,     7,     0,     5,     0,     2,     2,
       2,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       3,     3,     2,     2,     0,     7,     0,     5,     0,     2,
       2,     2,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     3,     3,     2,     2,     0,     5,     0,     5,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     4,
       6,     3,     5,     3,     2,     2,     2,     2,     2,     1,
       1,     2,     1,     2,     2,     2,     2,     1,     2,     1,
       1,     1,     1,     1,     5,     6,     5,     6,     5,     6,
       0,     3,     3,     3,     2,     1,     2,     1,     1,     2,
       1,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     5,     6,     7,     8,
       9,    10,    11,   163,    12,    16,    18,    52,    54,    51,
      50,    85,     0,   125,   127,   106,     0,   195,   197,   198,
     196,     0,     0,     0,     0,     0,   174,     0,     0,    20,
      20,    56,    56,    87,     0,   129,   129,   108,     0,    15,
      14,    13,   172,   173,     0,   170,   170,   170,     0,     0,
       0,     0,     0,    49,    83,     0,     0,     0,   104,   170,
     170,   170,     0,     0,     0,     0,     0,     0,     0,    29,
      30,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,    34,    31,    32,     0,    17,    21,    19,
       0,    61,     0,     0,     0,     0,    62,    63,    65,     0,
      72,     0,    64,     0,    53,    57,    55,     0,     0,    91,
      92,     0,     0,     0,     0,     0,     0,     0,    93,     0,
      86,    88,    87,     0,     0,     0,     0,     0,     0,     0,
       0,   150,     0,     0,   152,     0,     0,     0,   149,     0,
       0,   126,   130,   128,     0,   112,   113,     0,     0,     0,
       0,     0,     0,     0,   114,     0,   107,   109,   108,     0,
       0,     0,     0,   168,   166,   164,    26,    46,    48,    22,
     183,   184,   185,   186,   187,   188,   189,   190,    24,   178,
     180,    44,   162,   161,   160,    37,   157,   159,    82,    81,
      80,    35,    74,    79,    40,    27,   193,   194,   191,   192,
      28,    25,    39,    36,     0,     0,   199,    41,    77,    76,
      38,   177,    45,   175,    58,    60,    70,    68,    71,     0,
       0,    69,    73,    59,   102,    89,    96,    94,    90,    98,
      95,     0,     0,    99,    97,   103,     0,   131,   155,   132,
     133,   135,   151,   145,   144,   146,   154,   153,   134,     0,
       0,   137,   156,   136,   148,   147,   123,   117,   115,   110,
     111,   119,   116,     0,     0,   120,   118,   124,     0,   169,
     167,   165,   171,    47,     0,   179,     0,   181,   158,    75,
      43,    42,     0,   200,     0,   176,    67,    66,   101,   100,
      84,   143,   141,     0,     0,   122,   121,   105,    23,   182,
     201,    78,     0,   138,   139,   142,     0,   140
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    15,    16,    17,    49,    50,    68,   108,   186,
     187,   188,    18,    51,    52,    70,   125,   229,   230,   212,
     213,    19,   142,    53,    72,   141,    20,   178,    57,    77,
     177,    21,    55,    56,    75,   162,   205,   206,   207,    22,
      23,    83,    24,   232,   233,   198,   199,   200,   220,    41,
     227
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -198
static const yytype_int16 yypact[] =
{
    -198,   155,  -198,  -198,   -49,    65,     5,    69,    54,   148,
     -62,   -59,   -54,   121,    60,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,    47,    57,  -198,  -198,    47,    67,  -198,  -198,  -198,
    -198,    10,    24,    39,    70,    83,  -198,    33,   215,  -198,
    -198,  -198,  -198,  -198,    77,  -198,  -198,  -198,    77,  -198,
    -198,  -198,  -198,  -198,   222,    73,    73,    73,   173,   225,
     339,   369,   401,  -198,  -198,   264,   307,    -4,  -198,    73,
      73,    73,   133,    98,   103,   116,    77,   106,   368,  -198,
    -198,   129,   100,   126,   130,    77,   202,  -198,   368,   134,
     100,     9,    59,  -198,  -198,  -198,   132,  -198,  -198,  -198,
     136,  -198,   131,   100,   126,   144,  -198,  -198,    78,   100,
    -198,   132,  -198,    77,  -198,  -198,  -198,   147,   368,  -198,
    -198,   100,   126,   202,   157,   100,    29,    59,  -198,   132,
    -198,  -198,  -198,   153,   159,   100,   126,   126,   161,    77,
     126,  -198,   100,    40,  -198,   126,   290,   132,  -198,   100,
      74,  -198,  -198,  -198,   160,  -198,  -198,   100,   126,   474,
     168,   100,    34,    59,  -198,   132,  -198,  -198,  -198,   165,
     172,   174,   169,  -198,  -198,  -198,    77,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   105,  -198,
      68,  -198,  -198,  -198,  -198,   100,  -198,  -198,  -198,  -198,
    -198,   126,  -198,  -198,  -198,    77,  -198,  -198,  -198,  -198,
    -198,   368,  -198,   100,   178,   178,   128,  -198,   207,   126,
    -198,  -198,   132,  -198,  -198,  -198,   100,   126,  -198,   100,
     126,   100,   132,  -198,  -198,   368,   100,   126,  -198,  -198,
     100,   178,   178,  -198,  -198,   132,   446,  -198,  -198,   100,
     126,   126,  -198,  -198,   126,  -198,  -198,  -198,   126,   100,
      77,   -37,   132,   100,  -198,  -198,  -198,   100,   126,  -198,
    -198,  -198,   100,   178,   178,  -198,  -198,   132,   478,  -198,
    -198,  -198,  -198,  -198,   180,  -198,   187,  -198,  -198,  -198,
    -198,  -198,   189,  -198,   126,  -198,   100,   126,  -198,  -198,
    -198,   100,   212,   100,    77,  -198,  -198,  -198,  -198,  -198,
    -198,   126,   100,   100,   213,   100,   100,   100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -198,  -198,  -198,  -198,  -198,  -198,  -198,   220,  -198,   177,
    -156,    -6,  -198,  -198,  -198,   223,  -198,   -89,   -27,  -173,
    -198,  -198,  -198,  -198,   146,  -198,  -198,  -198,  -198,   117,
    -198,  -198,  -198,  -198,   240,  -198,   -99,  -197,   150,  -198,
    -198,   322,  -198,   -50,  -169,   -77,  -129,   109,  -115,    19,
    -131
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -50
static const yytype_int16 yytable[] =
{
      32,   223,    36,   164,   211,   253,   165,   166,   298,   313,
      42,   167,   168,    43,   236,   224,   169,   225,   248,    44,
     241,   221,   267,    25,    26,   237,   298,   170,    29,   314,
     293,   171,   246,   172,   173,   251,   250,   252,   299,   298,
     283,   285,   284,   247,   298,   174,   259,   175,    74,   298,
      30,   245,    78,   298,   280,   -49,   299,   260,   261,   293,
     273,   264,   298,   305,   299,    54,   268,    67,   277,   295,
     176,   242,   282,   305,   299,    58,   298,    29,    31,   278,
     298,   226,   208,    81,    59,   298,   305,   299,   299,   255,
     266,   299,   295,   300,   301,   299,   274,    29,    60,    30,
      29,   226,   228,   305,   209,   299,   226,   272,    64,   298,
     254,   294,   226,    61,   298,   296,   295,   243,   305,    30,
     308,   309,    30,   202,   239,   287,   298,    35,   298,   271,
     298,   240,   210,    47,   299,    48,   297,    27,    28,    82,
     306,    33,    34,   263,    62,   203,   286,    73,   299,   208,
      73,   307,   315,   316,   275,     2,     3,    63,     4,     5,
       6,   190,   191,   192,   193,   194,   195,   196,   197,     7,
     311,   209,   183,   204,     8,   302,     9,   184,    86,   189,
      87,    10,    88,    89,   182,    90,    91,    11,    92,    93,
     185,    94,    95,    96,    45,    46,   303,    97,   214,   210,
      98,   201,   222,   235,    99,   231,    12,    13,   100,   234,
     101,   102,   238,   103,   323,   321,    37,    38,    39,    40,
     244,   104,   105,   325,   106,   249,   257,   327,    14,   262,
      86,   258,    87,   276,    88,    89,   281,    90,    91,   289,
      92,    93,   292,    94,    95,    96,   290,   107,   291,    97,
     226,   304,    98,   318,    65,   319,    99,   320,   322,   326,
     100,    79,   101,   102,   312,   103,   216,   217,   218,   219,
      69,   143,   215,   104,   105,    71,   106,   144,   279,   145,
     146,   147,   148,    37,    38,    39,    40,    66,   256,   149,
      37,    38,    39,    40,    80,   288,    76,   150,   151,   109,
     152,   153,   265,     0,   154,   155,   156,     0,   324,     0,
       0,     0,     0,   208,   143,   157,     0,     0,   158,   159,
     144,     0,   145,   146,   147,   148,     0,     0,     0,     0,
     160,     0,   149,   228,     0,   209,   269,     0,   161,     0,
     150,   151,     0,   152,   153,     0,   110,   154,   155,   156,
     111,     0,   112,     0,   113,   114,   270,   115,   157,     0,
       0,   158,   159,   210,     0,     0,     0,   116,   117,   118,
       0,     0,     0,   160,   119,     0,   110,     0,     0,   120,
     111,   163,   112,     0,   113,   114,     0,   115,    84,    85,
     121,     0,     0,   122,     0,     0,     0,   116,   117,   118,
       0,   179,   180,   181,   119,   123,     0,     0,   127,   120,
     128,   129,   130,   124,     0,     0,   131,   132,     0,     0,
     121,   133,     0,   122,   190,   191,   192,   193,   194,   195,
     196,   197,   134,     0,     0,   123,   135,     0,   136,   137,
       0,     0,     0,   126,     0,     0,     0,     0,     0,     0,
     138,     0,   139,   127,     0,   128,   129,   130,     0,     0,
       0,   131,   132,     0,     0,     0,   133,     0,     0,     0,
       0,     0,     0,     0,     0,   140,     0,   134,     0,     0,
       0,   135,     0,   136,   137,   164,     0,     0,   165,   166,
       0,     0,     0,   167,   168,   138,     0,   139,   169,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   170,
       0,     0,     0,   171,     0,   172,   173,     0,     0,     0,
     310,     0,     0,     0,     0,     0,     0,   174,     0,   175,
     190,   191,   192,   193,   194,   195,   196,   197,   216,   217,
     218,   219,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   317
};

static const yytype_int16 yycheck[] =
{
       6,   100,     8,     7,    93,   136,    10,    11,   205,    46,
      72,    15,    16,    72,   113,     6,    20,     8,   133,    73,
     119,    98,   153,    72,    73,   114,   223,    31,    23,    66,
     186,    35,   131,    37,    38,     6,   135,     8,   211,   236,
       6,   172,     8,   132,   241,    49,   145,    51,    54,   246,
      45,   128,    58,   250,   169,     8,   229,   146,   147,   215,
     159,   150,   259,   232,   237,     8,   155,    48,   167,   198,
      74,   121,   171,   242,   247,     8,   273,    23,    73,   168,
     277,    72,    23,    64,    74,   282,   255,   260,   261,   139,
      50,   264,   221,   224,   225,   268,    22,    23,    74,    45,
      23,    72,    43,   272,    45,   278,    72,   157,    75,   306,
     137,     6,    72,    74,   311,    47,   245,   123,   287,    45,
     251,   252,    45,    23,    46,   175,   323,    73,   325,   156,
     327,    53,    73,    73,   307,    75,    68,    72,    73,    66,
     239,    72,    73,   149,    74,    45,   173,    73,   321,    23,
      73,   240,   283,   284,   160,     0,     1,    74,     3,     4,
       5,    56,    57,    58,    59,    60,    61,    62,    63,    14,
     269,    45,    74,    73,    19,    47,    21,    74,     5,    73,
       7,    26,     9,    10,    51,    12,    13,    32,    15,    16,
      74,    18,    19,    20,    73,    74,    68,    24,    68,    73,
      27,    72,    68,    72,    31,    73,    51,    52,    35,    73,
      37,    38,    68,    40,   313,   304,    68,    69,    70,    71,
      73,    48,    49,   322,    51,    68,    73,   326,    73,    68,
       5,    72,     7,    73,     9,    10,    68,    12,    13,    74,
      15,    16,    73,    18,    19,    20,    74,    74,    74,    24,
      72,    44,    27,    73,    39,    68,    31,    68,    46,    46,
      35,    39,    37,    38,   270,    40,    64,    65,    66,    67,
      50,     7,    95,    48,    49,    52,    51,    13,   169,    15,
      16,    17,    18,    68,    69,    70,    71,    72,   142,    25,
      68,    69,    70,    71,    72,   178,    56,    33,    34,    74,
      36,    37,   152,    -1,    40,    41,    42,    -1,   314,    -1,
      -1,    -1,    -1,    23,     7,    51,    -1,    -1,    54,    55,
      13,    -1,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      66,    -1,    25,    43,    -1,    45,    46,    -1,    74,    -1,
      33,    34,    -1,    36,    37,    -1,     7,    40,    41,    42,
      11,    -1,    13,    -1,    15,    16,    66,    18,    51,    -1,
      -1,    54,    55,    73,    -1,    -1,    -1,    28,    29,    30,
      -1,    -1,    -1,    66,    35,    -1,     7,    -1,    -1,    40,
      11,    74,    13,    -1,    15,    16,    -1,    18,    66,    67,
      51,    -1,    -1,    54,    -1,    -1,    -1,    28,    29,    30,
      -1,    79,    80,    81,    35,    66,    -1,    -1,     7,    40,
       9,    10,    11,    74,    -1,    -1,    15,    16,    -1,    -1,
      51,    20,    -1,    54,    56,    57,    58,    59,    60,    61,
      62,    63,    31,    -1,    -1,    66,    35,    -1,    37,    38,
      -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    51,     7,    -1,     9,    10,    11,    -1,    -1,
      -1,    15,    16,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    31,    -1,    -1,
      -1,    35,    -1,    37,    38,     7,    -1,    -1,    10,    11,
      -1,    -1,    -1,    15,    16,    49,    -1,    51,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    51,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    77,     0,     1,     3,     4,     5,    14,    19,    21,
      26,    32,    51,    52,    73,    78,    79,    80,    88,    97,
     102,   107,   115,   116,   118,    72,    73,    72,    73,    23,
      45,    73,    87,    72,    73,    73,    87,    68,    69,    70,
      71,   125,    72,    72,    73,    73,    74,    73,    75,    81,
      82,    89,    90,    99,     8,   108,   109,   104,     8,    74,
      74,    74,    74,    74,    75,    39,    72,   125,    83,    83,
      91,    91,   100,    73,    87,   110,   110,   105,    87,    39,
      72,   125,    66,   117,   117,   117,     5,     7,     9,    10,
      12,    13,    15,    16,    18,    19,    20,    24,    27,    31,
      35,    37,    38,    40,    48,    49,    51,    74,    84,    74,
       7,    11,    13,    15,    16,    18,    28,    29,    30,    35,
      40,    51,    54,    66,    74,    92,    74,     7,     9,    10,
      11,    15,    16,    20,    31,    35,    37,    38,    49,    51,
      74,   101,    98,     7,    13,    15,    16,    17,    18,    25,
      33,    34,    36,    37,    40,    41,    42,    51,    54,    55,
      66,    74,   111,    74,     7,    10,    11,    15,    16,    20,
      31,    35,    37,    38,    49,    51,    74,   106,   103,   117,
     117,   117,    51,    74,    74,    74,    85,    86,    87,    73,
      56,    57,    58,    59,    60,    61,    62,    63,   121,   122,
     123,    72,    23,    45,    73,   112,   113,   114,    23,    45,
      73,    93,    95,    96,    68,    85,    64,    65,    66,    67,
     124,   121,    68,   112,     6,     8,    72,   126,    43,    93,
      94,    73,   119,   120,    73,    72,   112,    93,    68,    46,
      53,   112,   119,    87,    73,   121,   112,    93,   124,    68,
     112,     6,     8,   126,    94,   119,   100,    73,    72,   112,
      93,    93,    68,    87,    93,   114,    50,   126,    93,    46,
      66,    94,   119,   112,    22,    87,    73,   112,    93,   123,
     124,    68,   112,     6,     8,   126,    94,   119,   105,    74,
      74,    74,    73,    86,     6,   122,    47,    68,   113,    95,
     126,   126,    47,    68,    44,   120,   112,    93,   126,   126,
      74,   112,    87,    46,    66,   126,   126,    74,    73,    68,
      68,    93,    46,   112,    87,   112,    46,   112
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
#line 124 "ifm-parse.y"
    {
                    vh_sstore(map, "TITLE", (yyvsp[(2) - (3)].sval));
                }
    break;

  case 14:
#line 128 "ifm-parse.y"
    {
                    if (sectnames == NULL)
                        sectnames = vl_create();
                    vl_spush(sectnames, (yyvsp[(2) - (3)].sval));
                }
    break;

  case 15:
#line 134 "ifm-parse.y"
    {
                    float version;
                    sscanf(VERSION, "%f", &version);
                    if ((yyvsp[(2) - (3)].dval) - version > 0.001)
                        fatal("version %g of IFM is required (this is %s)",
                              (yyvsp[(2) - (3)].dval), VERSION);
                }
    break;

  case 16:
#line 148 "ifm-parse.y"
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

  case 18:
#line 251 "ifm-parse.y"
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
#line 260 "ifm-parse.y"
    {
                    RESET_IT;
                }
    break;

  case 22:
#line 270 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("room", (yyvsp[(2) - (2)].sval), curobj, roomtags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 23:
#line 277 "ifm-parse.y"
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

  case 25:
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

  case 26:
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

  case 27:
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

  case 28:
#line 357 "ifm-parse.y"
    {
                    vh_istore(curobj, "GO", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 29:
#line 361 "ifm-parse.y"
    {
                    vh_istore(curobj, "ONEWAY", 1);
		}
    break;

  case 30:
#line 365 "ifm-parse.y"
    {
                    vh_istore(curobj, "NODROP", 1);
		}
    break;

  case 31:
#line 369 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOLINK", 1);
		}
    break;

  case 32:
#line 373 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOPATH", 1);
		}
    break;

  case 33:
#line 377 "ifm-parse.y"
    {
                    startroom = curobj;
		}
    break;

  case 34:
#line 381 "ifm-parse.y"
    {
                    vh_istore(curobj, "FINISH", 1);
                }
    break;

  case 35:
#line 385 "ifm-parse.y"
    {
                    SET_LIST(curobj, ATTR(NEED), curitems);
                }
    break;

  case 36:
#line 389 "ifm-parse.y"
    {
                    SET_LIST(curobj, ATTR(BEFORE), curtasks);
		}
    break;

  case 37:
#line 393 "ifm-parse.y"
    {
                    SET_LIST(curobj, ATTR(AFTER), curtasks);
		}
    break;

  case 38:
#line 397 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, ATTR(LEAVE), curitems);
                    vh_istore(curobj, ATTR(LEAVEALL), allflag);
                }
    break;

  case 39:
#line 403 "ifm-parse.y"
    {
                    vh_istore(curobj, "LEN", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 40:
#line 407 "ifm-parse.y"
    {
                    vh_istore(curobj, "SCORE", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 41:
#line 411 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(2) - (2)].sval));
                }
    break;

  case 42:
#line 416 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 43:
#line 421 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 44:
#line 426 "ifm-parse.y"
    {
                    add_attr(curobj, "NOTE", (yyvsp[(2) - (2)].sval));
		}
    break;

  case 48:
#line 437 "ifm-parse.y"
    {
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, (yyvsp[(1) - (1)].vval));
		}
    break;

  case 49:
#line 445 "ifm-parse.y"
    {
                    (yyval.vval) = vs_screate((yyvsp[(1) - (1)].sval));
                    itroom = vs_copy((yyval.vval));
                }
    break;

  case 50:
#line 450 "ifm-parse.y"
    {
                    if (itroom == NULL)
                        err("no room referred to by 'it'");
                    else
                        (yyval.vval) = vs_copy(itroom);
                }
    break;

  case 51:
#line 457 "ifm-parse.y"
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
#line 472 "ifm-parse.y"
    {
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", (yyvsp[(2) - (2)].sval));
                    vh_istore(curobj, "ID", itemid++);
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;

  case 53:
#line 480 "ifm-parse.y"
    {
                    if (!vh_exists(curobj, "IN"))
                        vh_pstore(curobj, "IN", lastroom);

                    lastitem = curobj;
                    vl_ppush(items, curobj);
                    RESET_IT;
		}
    break;

  case 54:
#line 489 "ifm-parse.y"
    {
                    modify = 1;
                    if ((curobj = vh_pget(itemtags, (yyvsp[(2) - (2)].sval))) == NULL) {
                        err("item tag '%s' not yet defined", (yyvsp[(2) - (2)].sval));
                        curobj = vh_create();
                    }
                }
    break;

  case 55:
#line 497 "ifm-parse.y"
    {
                    RESET_IT;
                }
    break;

  case 58:
#line 507 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("item", (yyvsp[(2) - (2)].sval), curobj, itemtags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 59:
#line 514 "ifm-parse.y"
    {
                    vh_store(curobj, "IN", (yyvsp[(2) - (2)].vval));
		}
    break;

  case 60:
#line 518 "ifm-parse.y"
    {
                    add_attr(curobj, "NOTE", (yyvsp[(2) - (2)].sval));
		}
    break;

  case 61:
#line 522 "ifm-parse.y"
    {
                    vh_istore(curobj, "HIDDEN", 1);
		}
    break;

  case 62:
#line 526 "ifm-parse.y"
    {
                    obsolete("'given' attribute", "task 'give' attribute");
                    vh_istore(curobj, "GIVEN", 1);
		}
    break;

  case 63:
#line 531 "ifm-parse.y"
    {
                    vh_istore(curobj, "LOST", 1);
		}
    break;

  case 64:
#line 535 "ifm-parse.y"
    {
                    vh_istore(curobj, "IGNORE", 1);
		}
    break;

  case 65:
#line 539 "ifm-parse.y"
    {
                    vh_istore(curobj, "KEEP", 1);
		}
    break;

  case 66:
#line 543 "ifm-parse.y"
    {
                    SET_LIST(curobj, "KEEP_WITH", curitems);
		}
    break;

  case 67:
#line 547 "ifm-parse.y"
    {
                    SET_LIST(curobj, "KEEP_UNTIL", curtasks);
		}
    break;

  case 68:
#line 551 "ifm-parse.y"
    {
                    SET_LIST(curobj, "NEED", curitems);
                }
    break;

  case 69:
#line 555 "ifm-parse.y"
    {
                    SET_LIST(curobj, "BEFORE", curtasks);
                }
    break;

  case 70:
#line 559 "ifm-parse.y"
    {
                    SET_LIST(curobj, "AFTER", curtasks);
                }
    break;

  case 71:
#line 563 "ifm-parse.y"
    {
                    vh_istore(curobj, "SCORE", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 72:
#line 567 "ifm-parse.y"
    {
                    vh_istore(curobj, "FINISH", 1);
                }
    break;

  case 76:
#line 577 "ifm-parse.y"
    { allflag = 0; }
    break;

  case 77:
#line 578 "ifm-parse.y"
    { allflag = 1; }
    break;

  case 78:
#line 579 "ifm-parse.y"
    { allflag = 1; }
    break;

  case 79:
#line 583 "ifm-parse.y"
    {
                    if (curitems == NULL)
                        curitems = vl_create();
                    vl_push(curitems, (yyvsp[(1) - (1)].vval));
		}
    break;

  case 80:
#line 591 "ifm-parse.y"
    {
                    (yyval.vval) = vs_screate((yyvsp[(1) - (1)].sval));
                    ititem = vs_copy((yyval.vval));
                }
    break;

  case 81:
#line 596 "ifm-parse.y"
    {
                    if (ititem == NULL)
                        err("no item referred to by 'it'");
                    else
                        (yyval.vval) = vs_copy(ititem);
                }
    break;

  case 82:
#line 603 "ifm-parse.y"
    {
                    if (lastitem == NULL) {
                        err("no item referred to by 'last'");
                    } else {
                        (yyval.vval) = vs_pcreate(lastitem);
                        ititem = vs_copy((yyval.vval));
                    }
                }
    break;

  case 83:
#line 618 "ifm-parse.y"
    {
                    curobj = vh_create();
                    vh_store(curobj, "FROM", (yyvsp[(2) - (4)].vval));
                    vh_store(curobj, "TO", (yyvsp[(4) - (4)].vval));
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;

  case 84:
#line 626 "ifm-parse.y"
    {
                    vl_ppush(links, curobj);
                    RESET_IT;
		}
    break;

  case 85:
#line 631 "ifm-parse.y"
    {
                    modify = 1;
                    if ((curobj = vh_pget(linktags, (yyvsp[(2) - (2)].sval))) == NULL) {
                        err("link tag '%s' not yet defined", (yyvsp[(2) - (2)].sval));
                        curobj = vh_create();
                    }
                }
    break;

  case 86:
#line 639 "ifm-parse.y"
    {
                    RESET_IT;
                }
    break;

  case 89:
#line 649 "ifm-parse.y"
    {
                    vh_pstore(curobj, "DIR", curdirs);
                    curdirs = NULL;
		}
    break;

  case 90:
#line 654 "ifm-parse.y"
    {
                    vh_istore(curobj, "GO", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 91:
#line 658 "ifm-parse.y"
    {
                    vh_istore(curobj, "ONEWAY", 1);
		}
    break;

  case 92:
#line 662 "ifm-parse.y"
    {
                    vh_istore(curobj, "HIDDEN", 1);
		}
    break;

  case 93:
#line 666 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOPATH", 1);
		}
    break;

  case 94:
#line 670 "ifm-parse.y"
    {
                    SET_LIST(curobj, "NEED", curitems);
                }
    break;

  case 95:
#line 674 "ifm-parse.y"
    {
                    SET_LIST(curobj, "BEFORE", curtasks);
		}
    break;

  case 96:
#line 678 "ifm-parse.y"
    {
                    SET_LIST(curobj, "AFTER", curtasks);
		}
    break;

  case 97:
#line 682 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                }
    break;

  case 98:
#line 688 "ifm-parse.y"
    {
                    vh_istore(curobj, "LEN", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 99:
#line 692 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(2) - (2)].sval));
                }
    break;

  case 100:
#line 697 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 101:
#line 702 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 102:
#line 707 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("link", (yyvsp[(2) - (2)].sval), curobj, linktags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 104:
#line 721 "ifm-parse.y"
    {
                    curobj = vh_create();
                    vh_store(curobj, "FROM", (yyvsp[(2) - (4)].vval));
                    vh_store(curobj, "TO", (yyvsp[(4) - (4)].vval));
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;

  case 105:
#line 729 "ifm-parse.y"
    {
                    vl_ppush(joins, curobj);
                    RESET_IT;
		}
    break;

  case 106:
#line 734 "ifm-parse.y"
    {
                    modify = 1;
                    if ((curobj = vh_pget(jointags, (yyvsp[(2) - (2)].sval))) == NULL) {
                        err("join tag '%s' not yet defined", (yyvsp[(2) - (2)].sval));
                        curobj = vh_create();
                    }
                }
    break;

  case 107:
#line 742 "ifm-parse.y"
    {
                    RESET_IT;
                }
    break;

  case 110:
#line 752 "ifm-parse.y"
    {
                    vh_istore(curobj, "GO", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 111:
#line 756 "ifm-parse.y"
    {
                    vh_istore(curobj, "GO", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 112:
#line 760 "ifm-parse.y"
    {
                    vh_istore(curobj, "ONEWAY", 1);
		}
    break;

  case 113:
#line 764 "ifm-parse.y"
    {
                    vh_istore(curobj, "HIDDEN", 1);
		}
    break;

  case 114:
#line 768 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOPATH", 1);
		}
    break;

  case 115:
#line 772 "ifm-parse.y"
    {
                    SET_LIST(curobj, "NEED", curitems);
                }
    break;

  case 116:
#line 776 "ifm-parse.y"
    {
                    SET_LIST(curobj, "BEFORE", curtasks);
		}
    break;

  case 117:
#line 780 "ifm-parse.y"
    {
                    SET_LIST(curobj, "AFTER", curtasks);
		}
    break;

  case 118:
#line 784 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "LEAVE", curitems);
                    vh_istore(curobj, "LEAVEALL", allflag);
                }
    break;

  case 119:
#line 790 "ifm-parse.y"
    {
                    vh_istore(curobj, "LEN", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 120:
#line 794 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(2) - (2)].sval));
                }
    break;

  case 121:
#line 799 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "TO_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 122:
#line 804 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "FROM_CMD", (yyvsp[(3) - (3)].sval));
                }
    break;

  case 123:
#line 809 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("join", (yyvsp[(2) - (2)].sval), curobj, jointags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 125:
#line 823 "ifm-parse.y"
    {
                    curobj = vh_create();
                    vh_sstore(curobj, "DESC", (yyvsp[(2) - (2)].sval));
                    vh_pstore(curobj, "STYLE", current_styles());
                    modify = 0;
                }
    break;

  case 126:
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

  case 127:
#line 841 "ifm-parse.y"
    {
                    modify = 1;
                    if ((curobj = vh_pget(tasktags, (yyvsp[(2) - (2)].sval))) == NULL) {
                        err("task tag '%s' not yet defined", (yyvsp[(2) - (2)].sval));
                        curobj = vh_create();
                    }
                }
    break;

  case 128:
#line 849 "ifm-parse.y"
    {
                    RESET_IT;
                }
    break;

  case 131:
#line 859 "ifm-parse.y"
    {
                    if (!modify)
                        set_tag("task", (yyvsp[(2) - (2)].sval), curobj, tasktags);
                    else
                        CHANGE_ERROR(tag);
		}
    break;

  case 132:
#line 866 "ifm-parse.y"
    {
                    SET_LIST(curobj, "AFTER", curtasks);
		}
    break;

  case 133:
#line 870 "ifm-parse.y"
    {
                    SET_LIST(curobj, "NEED", curitems);
		}
    break;

  case 134:
#line 874 "ifm-parse.y"
    {
                    SET_LIST(curobj, "GIVE", curitems);
		}
    break;

  case 135:
#line 878 "ifm-parse.y"
    {
                    SET_LIST(curobj, "GET", curitems);
		}
    break;

  case 136:
#line 882 "ifm-parse.y"
    {
                    SET_LIST(curobj, "DO", curtasks);
		}
    break;

  case 137:
#line 886 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
		}
    break;

  case 138:
#line 892 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		}
    break;

  case 139:
#line 899 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", (yyvsp[(4) - (4)].vval));
		}
    break;

  case 140:
#line 906 "ifm-parse.y"
    {
                    if (curitems != NULL)
                        SET_LIST(curobj, "DROP", curitems);
                    vh_istore(curobj, "DROPALL", allflag);
                    vh_store(curobj, "DROPROOM", (yyvsp[(4) - (6)].vval));
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		}
    break;

  case 141:
#line 914 "ifm-parse.y"
    {
                    vh_store(curobj, "DROPROOM", (yyvsp[(3) - (3)].vval));
		}
    break;

  case 142:
#line 918 "ifm-parse.y"
    {
                    vh_store(curobj, "DROPROOM", (yyvsp[(3) - (5)].vval));
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
		}
    break;

  case 143:
#line 923 "ifm-parse.y"
    {
                    SET_LIST(curobj, "DROPUNTIL", curtasks);
                }
    break;

  case 144:
#line 927 "ifm-parse.y"
    {
                    SET_LIST(curobj, "LOSE", curitems);
		}
    break;

  case 145:
#line 931 "ifm-parse.y"
    {
                    vh_store(curobj, "GOTO", (yyvsp[(2) - (2)].vval));
                }
    break;

  case 146:
#line 935 "ifm-parse.y"
    {
                    vh_store(curobj, "FOLLOW", (yyvsp[(2) - (2)].vval));
                }
    break;

  case 147:
#line 939 "ifm-parse.y"
    {
                    vh_store(curobj, "IN", (yyvsp[(2) - (2)].vval));
		}
    break;

  case 148:
#line 943 "ifm-parse.y"
    {
                    vh_istore(curobj, "NOROOM", 1);
		}
    break;

  case 149:
#line 947 "ifm-parse.y"
    {
                    vh_istore(curobj, "IGNORE", 1);
		}
    break;

  case 150:
#line 951 "ifm-parse.y"
    {
                    vh_istore(curobj, "SAFE", 1);
                }
    break;

  case 151:
#line 955 "ifm-parse.y"
    {
                    vh_istore(curobj, "SCORE", (yyvsp[(2) - (2)].ival));
		}
    break;

  case 152:
#line 959 "ifm-parse.y"
    {
                    vh_istore(curobj, "FINISH", 1);
                }
    break;

  case 153:
#line 963 "ifm-parse.y"
    {
                    while (repeat-- > 0)
                        add_attr(curobj, "CMD", (yyvsp[(2) - (2)].sval));
                }
    break;

  case 154:
#line 968 "ifm-parse.y"
    {
                    add_attr(curobj, "CMD", NULL);
                }
    break;

  case 155:
#line 972 "ifm-parse.y"
    {
                    add_attr(curobj, "NOTE", (yyvsp[(2) - (2)].sval));
		}
    break;

  case 159:
#line 983 "ifm-parse.y"
    {
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, (yyvsp[(1) - (1)].vval));
		}
    break;

  case 160:
#line 991 "ifm-parse.y"
    {
                    (yyval.vval) = vs_screate((yyvsp[(1) - (1)].sval));
                    ittask = vs_copy((yyval.vval));
                }
    break;

  case 161:
#line 996 "ifm-parse.y"
    {
                    if (ittask == NULL)
                        err("no task referred to by 'it'");
                    else
                        (yyval.vval) = vs_copy(ittask);
                }
    break;

  case 162:
#line 1003 "ifm-parse.y"
    {
                    if (lasttask == NULL) {
                        err("no task referred to by 'last'");
                    } else {
                        (yyval.vval) = vs_pcreate(lasttask);
                        ittask = vs_copy((yyval.vval));
                    }
                }
    break;

  case 163:
#line 1018 "ifm-parse.y"
    {
                    if (instyle)
                        pop_style(NULL);
                    instyle = 0;
                }
    break;

  case 164:
#line 1026 "ifm-parse.y"
    {
                    var_set(NULL, (yyvsp[(1) - (5)].sval), vs_dcreate((yyvsp[(3) - (5)].dval)));
                }
    break;

  case 165:
#line 1030 "ifm-parse.y"
    {
                    var_set((yyvsp[(1) - (6)].sval), (yyvsp[(2) - (6)].sval), vs_dcreate((yyvsp[(4) - (6)].dval)));
                    obsolete("variable assignment", "dotted notation");
                }
    break;

  case 166:
#line 1035 "ifm-parse.y"
    {
                    var_set(NULL, (yyvsp[(1) - (5)].sval), vs_screate((yyvsp[(3) - (5)].sval)));
                }
    break;

  case 167:
#line 1039 "ifm-parse.y"
    {
                    var_set((yyvsp[(1) - (6)].sval), (yyvsp[(2) - (6)].sval), vs_screate((yyvsp[(4) - (6)].sval)));
                    obsolete("variable assignment", "dotted notation");
                }
    break;

  case 168:
#line 1044 "ifm-parse.y"
    {
                    var_set(NULL, (yyvsp[(1) - (5)].sval), NULL);
                }
    break;

  case 169:
#line 1048 "ifm-parse.y"
    {
                    var_set((yyvsp[(1) - (6)].sval), (yyvsp[(2) - (6)].sval), NULL);
                    obsolete("variable assignment", "dotted notation");
                }
    break;

  case 171:
#line 1056 "ifm-parse.y"
    {
                    push_style((yyvsp[(3) - (3)].sval));
                    instyle++;
                }
    break;

  case 172:
#line 1067 "ifm-parse.y"
    {
                    push_style((yyvsp[(2) - (3)].sval));
                }
    break;

  case 173:
#line 1071 "ifm-parse.y"
    {
                    pop_style((yyvsp[(2) - (3)].sval));
                }
    break;

  case 174:
#line 1075 "ifm-parse.y"
    {
                    pop_style(NULL);
                }
    break;

  case 177:
#line 1085 "ifm-parse.y"
    {
                    add_attr(curobj, "STYLE", (yyvsp[(1) - (1)].sval));
                    ref_style((yyvsp[(1) - (1)].sval));
                }
    break;

  case 180:
#line 1100 "ifm-parse.y"
    {
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, (yyvsp[(1) - (1)].ival));
		}
    break;

  case 181:
#line 1106 "ifm-parse.y"
    {
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if ((yyvsp[(2) - (2)].ival) <= 0)
                        err("invalid repeat count");
                    while ((yyvsp[(2) - (2)].ival)-- > 0)
                        vl_ipush(curdirs, (yyvsp[(1) - (2)].ival));
                }
    break;

  case 182:
#line 1115 "ifm-parse.y"
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

  case 183:
#line 1126 "ifm-parse.y"
    { (yyval.ival) = D_NORTH;	    }
    break;

  case 184:
#line 1127 "ifm-parse.y"
    { (yyval.ival) = D_EAST;	    }
    break;

  case 185:
#line 1128 "ifm-parse.y"
    { (yyval.ival) = D_SOUTH;	    }
    break;

  case 186:
#line 1129 "ifm-parse.y"
    { (yyval.ival) = D_WEST;	    }
    break;

  case 187:
#line 1130 "ifm-parse.y"
    { (yyval.ival) = D_NORTHEAST; }
    break;

  case 188:
#line 1131 "ifm-parse.y"
    { (yyval.ival) = D_NORTHWEST; }
    break;

  case 189:
#line 1132 "ifm-parse.y"
    { (yyval.ival) = D_SOUTHEAST; }
    break;

  case 190:
#line 1133 "ifm-parse.y"
    { (yyval.ival) = D_SOUTHWEST; }
    break;

  case 191:
#line 1136 "ifm-parse.y"
    { (yyval.ival) = D_IN;   }
    break;

  case 192:
#line 1137 "ifm-parse.y"
    { (yyval.ival) = D_OUT;  }
    break;

  case 193:
#line 1138 "ifm-parse.y"
    { (yyval.ival) = D_UP;   }
    break;

  case 194:
#line 1139 "ifm-parse.y"
    { (yyval.ival) = D_DOWN; }
    break;

  case 195:
#line 1146 "ifm-parse.y"
    { (yyval.dval) = (yyvsp[(1) - (1)].ival); }
    break;

  case 196:
#line 1147 "ifm-parse.y"
    { (yyval.dval) = (yyvsp[(1) - (1)].dval); }
    break;

  case 197:
#line 1148 "ifm-parse.y"
    { (yyval.dval) =  1; }
    break;

  case 198:
#line 1149 "ifm-parse.y"
    { (yyval.dval) =  0; }
    break;

  case 199:
#line 1153 "ifm-parse.y"
    {
                    (yyval.sval) = (yyvsp[(1) - (1)].sval);
                    repeat = 1;
                }
    break;

  case 200:
#line 1158 "ifm-parse.y"
    {
                    (yyval.sval) = (yyvsp[(1) - (2)].sval);
                    repeat = (yyvsp[(2) - (2)].ival);
                    if ((yyvsp[(2) - (2)].ival) <= 0)
                        err("invalid repeat count");
                }
    break;

  case 201:
#line 1165 "ifm-parse.y"
    {
                    (yyval.sval) = (yyvsp[(1) - (3)].sval);
                    repeat = (yyvsp[(3) - (3)].ival);
                    if ((yyvsp[(3) - (3)].ival) <= 0)
                        err("invalid repeat count");
                    obsolete("'times' keyword", "just the repeat count");
                }
    break;


/* Line 1267 of yacc.c.  */
#line 3316 "ifm-parse.c"
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


#line 1174 "ifm-parse.y"


