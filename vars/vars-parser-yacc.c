/* A Bison parser, made from vars-parser-yacc.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	VALUE	257
# define	ID	258
# define	EQ	259
# define	NE	260
# define	GE	261
# define	GT	262
# define	LE	263
# define	LT	264
# define	MAT	265
# define	NMAT	266
# define	AND	267
# define	OR	268
# define	PLUS	269
# define	MINUS	270

#line 1 "vars-parser-yacc.y"

/* Expression parser */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

#include "vars-buffer.h"
#include "vars-hash.h"
#include "vars-parser.h"
#include "vars-parser-lex.h"
#include "vars-parser-yacc.h"
#include "vars-regex.h"

/* Convenience macros */
#define COPY(s)  vs_copy(s)
#define DSET(s)  vs_dcreate(s)
#define DVAL(s)  vs_dget(s)
#define ISET(s)  vs_icreate(s)
#define IVAL(s)  vs_iget(s)
#define PUSH(s)  vl_push(vp_stack, s)
#define STR(s)   (vs_type(s) == V_TYPE_STRING)
#define SVAL(s)  vs_sgetref(s)

#define YYPRINT(fp, type, value) \
        yyprint(fp, type, value)

#define YYERROR_VERBOSE 1
#define YYDEBUG 1

/* Current parser for evaluation */
vparser *vp_parser = NULL;

/* Current value stack */
static vlist *vp_stack = NULL;

/* Current function arg list */
static vlist *vp_arglist = NULL;

/* Internal arg list */
static vlist *args = NULL;

/* Internal functions */
static vregex *get_regexp(char *str);
static void yyprint(FILE *fp, int type, vscalar *s);
void yyerror(char *msg);

#ifndef YYSTYPE
# define YYSTYPE int
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		68
#define	YYFLAG		-32768
#define	YYNTBASE	32

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 270 ? yytranslate[x] : 38)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,     2,     2,    23,     2,     2,
      29,    30,    21,    19,    31,    20,     2,    22,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    18,    15,
       2,    16,     2,    17,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    27,     2,     2,     2,     2,     2,
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
       6,     7,     8,     9,    10,    11,    12,    13,    14,    24,
      25
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     6,     9,    12,    14,    16,    19,
      22,    26,    30,    34,    38,    42,    46,    50,    54,    58,
      62,    66,    70,    74,    78,    82,    86,    90,    94,    97,
     103,   107,   108,   114,   115,   117,   121
};
static const short yyrhs[] =
{
      -1,    32,    33,     0,    28,     0,    34,    28,     0,     1,
      28,     0,     3,     0,     4,     0,    19,    34,     0,    20,
      34,     0,    34,    19,    34,     0,    34,    20,    34,     0,
      34,    21,    34,     0,    34,    22,    34,     0,    34,    27,
      34,     0,    34,    23,    34,     0,    34,    15,    34,     0,
      29,    34,    30,     0,    34,     5,    34,     0,    34,     6,
      34,     0,    34,     8,    34,     0,    34,    10,    34,     0,
      34,     7,    34,     0,    34,     9,    34,     0,    34,    13,
      34,     0,    34,    14,    34,     0,    34,    11,    34,     0,
      34,    12,    34,     0,    26,    34,     0,    34,    17,    34,
      18,    34,     0,     4,    16,    34,     0,     0,     4,    29,
      35,    36,    30,     0,     0,    37,     0,    36,    31,    37,
       0,    34,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    73,    74,    77,    78,    79,    85,    89,   101,   105,
     109,   113,   117,   121,   125,   132,   139,   143,   147,   156,
     165,   174,   183,   192,   201,   205,   209,   215,   221,   225,
     229,   236,   236,   253,   254,   255,   258
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "VALUE", "ID", "EQ", "NE", "GE", "GT", "LE", 
  "LT", "MAT", "NMAT", "AND", "OR", "';'", "'='", "'?'", "':'", "'+'", 
  "'-'", "'*'", "'/'", "'%'", "PLUS", "MINUS", "'!'", "'^'", "'\\n'", 
  "'('", "')'", "','", "input", "line", "exp", "@1", "arglist", "arg", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    32,    32,    33,    33,    33,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    35,    34,    36,    36,    36,    37
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     1,     2,     2,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     5,
       3,     0,     5,     0,     1,     3,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     6,     7,     0,     0,     0,     3,     0,
       2,     0,     5,     0,    31,     8,     9,    28,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,    30,    33,
      17,    18,    19,    22,    20,    23,    21,    26,    27,    24,
      25,    16,     0,    10,    11,    12,    13,    15,    14,    36,
       0,    34,     0,    32,     0,    29,    35,     0,     0
};

static const short yydefgoto[] =
{
       1,    10,    59,    39,    60,    61
};

static const short yypact[] =
{
  -32768,    36,   -21,-32768,   -15,    40,    40,    40,-32768,    40,
  -32768,    91,-32768,    40,-32768,   -14,   -14,   -14,    65,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,-32768,   161,    40,
  -32768,   228,   228,    26,    26,    26,    26,   228,   228,   207,
     184,   161,   115,   -12,   -12,   -14,   -14,   -14,   -14,   138,
     -28,-32768,    40,-32768,    40,   161,-32768,    16,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,    -1,-32768,-32768,   -47
};


#define	YYLAST		255


static const short yytable[] =
{
      11,    13,    63,    64,    15,    16,    17,    12,    18,    33,
      34,    35,    38,    36,    14,    36,    68,    66,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    67,     2,     0,     3,
       4,     0,     0,     3,     4,    31,    32,    33,    34,    35,
       0,     0,     0,    36,     0,     5,     6,     0,     0,     5,
       6,    65,     7,     0,     8,     9,     7,     0,     0,     9,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,    30,     0,    31,    32,    33,    34,    35,     0,
       0,     0,    36,     0,     0,    40,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     0,    30,     0,
      31,    32,    33,    34,    35,     0,     0,     0,    36,    37,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,    30,    62,    31,    32,    33,    34,    35,     0,
       0,     0,    36,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     0,    30,     0,    31,    32,    33,
      34,    35,     0,     0,     0,    36,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     0,     0,    30,     0,
      31,    32,    33,    34,    35,     0,     0,     0,    36,    19,
      20,    21,    22,    23,    24,    25,    26,    27,     0,     0,
       0,     0,     0,    31,    32,    33,    34,    35,     0,     0,
       0,    36,    19,    20,    21,    22,    23,    24,    25,    26,
       0,     0,     0,     0,     0,     0,    31,    32,    33,    34,
      35,     0,     0,     0,    36,    21,    22,    23,    24,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,    33,
      34,    35,     0,     0,     0,    36
};

static const short yycheck[] =
{
       1,    16,    30,    31,     5,     6,     7,    28,     9,    21,
      22,    23,    13,    27,    29,    27,     0,    64,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,     0,     1,    -1,     3,
       4,    -1,    -1,     3,     4,    19,    20,    21,    22,    23,
      -1,    -1,    -1,    27,    -1,    19,    20,    -1,    -1,    19,
      20,    62,    26,    -1,    28,    29,    26,    -1,    -1,    29,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    -1,    19,    20,    21,    22,    23,    -1,
      -1,    -1,    27,    -1,    -1,    30,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    -1,
      19,    20,    21,    22,    23,    -1,    -1,    -1,    27,    28,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    -1,    27,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    17,    -1,    19,    20,    21,
      22,    23,    -1,    -1,    -1,    27,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    17,    -1,
      19,    20,    21,    22,    23,    -1,    -1,    -1,    27,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    27,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    -1,    -1,    -1,    27,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    -1,    -1,    -1,    27
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

case 5:
#line 80 "vars-parser-yacc.y"
{
                    yyerrok;
                }
    break;
case 6:
#line 86 "vars-parser-yacc.y"
{
                    PUSH(yyvsp[0]);
                }
    break;
case 7:
#line 90 "vars-parser-yacc.y"
{
                    yyval = vp_get(vp_parser, SVAL(yyvsp[0]));

                    if (yyval != NULL)
                        yyval = COPY(yyval);
                    else
                        yyval = vs_create(V_TYPE_UNDEF);

                    PUSH(yyvsp[0]);
                    PUSH(yyval);
                }
    break;
case 8:
#line 102 "vars-parser-yacc.y"
{
                    yyval = DSET(DVAL(yyvsp[0])); PUSH(yyval);
                }
    break;
case 9:
#line 106 "vars-parser-yacc.y"
{
                    yyval = DSET(-DVAL(yyvsp[0])); PUSH(yyval);
                }
    break;
case 10:
#line 110 "vars-parser-yacc.y"
{
                    yyval = DSET(DVAL(yyvsp[-2]) + DVAL(yyvsp[0])); PUSH(yyval);
                }
    break;
case 11:
#line 114 "vars-parser-yacc.y"
{
                    yyval = DSET(DVAL(yyvsp[-2]) - DVAL(yyvsp[0])); PUSH(yyval);
                }
    break;
case 12:
#line 118 "vars-parser-yacc.y"
{
                    yyval = DSET(DVAL(yyvsp[-2]) * DVAL(yyvsp[0])); PUSH(yyval);
                }
    break;
case 13:
#line 122 "vars-parser-yacc.y"
{
                    yyval = DSET(DVAL(yyvsp[-2]) / DVAL(yyvsp[0])); PUSH(yyval);
                }
    break;
case 14:
#line 126 "vars-parser-yacc.y"
{
                    errno = 0;
                    yyval = DSET(pow(DVAL(yyvsp[-2]), DVAL(yyvsp[0]))); PUSH(yyval);
                    if (errno)
                        vp_errno("^", errno);
                }
    break;
case 15:
#line 133 "vars-parser-yacc.y"
{
                    errno = 0;
                    yyval = DSET(fmod(DVAL(yyvsp[-2]), DVAL(yyvsp[0]))); PUSH(yyval);
                    if (errno)
                        vp_errno("%", errno);
                }
    break;
case 16:
#line 140 "vars-parser-yacc.y"
{
                    yyval = COPY(yyvsp[0]); PUSH(yyval);
                }
    break;
case 17:
#line 144 "vars-parser-yacc.y"
{
                    yyval = COPY(yyvsp[-1]); PUSH(yyval);
                }
    break;
case 18:
#line 148 "vars-parser-yacc.y"
{
                    if (STR(yyvsp[-2]) && STR(yyvsp[0]))
                        yyval = ISET(strcmp(SVAL(yyvsp[-2]), SVAL(yyvsp[0])) == 0);
                    else
                        yyval = ISET(DVAL(yyvsp[-2]) == DVAL(yyvsp[0]));

                    PUSH(yyval);
                }
    break;
case 19:
#line 157 "vars-parser-yacc.y"
{
                    if (STR(yyvsp[-2]) && STR(yyvsp[0]))
                        yyval = ISET(strcmp(SVAL(yyvsp[-2]), SVAL(yyvsp[0])) != 0);
                    else
                        yyval = ISET(DVAL(yyvsp[-2]) != DVAL(yyvsp[0]));

                    PUSH(yyval);
                }
    break;
case 20:
#line 166 "vars-parser-yacc.y"
{
                    if (STR(yyvsp[-2]) && STR(yyvsp[0]))
                        yyval = ISET(strcmp(SVAL(yyvsp[-2]), SVAL(yyvsp[0])) > 0);
                    else
                        yyval = ISET(DVAL(yyvsp[-2]) > DVAL(yyvsp[0]));

                    PUSH(yyval);
                }
    break;
case 21:
#line 175 "vars-parser-yacc.y"
{
                    if (STR(yyvsp[-2]) && STR(yyvsp[0]))
                        yyval = ISET(strcmp(SVAL(yyvsp[-2]), SVAL(yyvsp[0])) < 0);
                    else
                        yyval = ISET(DVAL(yyvsp[-2]) < DVAL(yyvsp[0]));

                    PUSH(yyval);
                }
    break;
case 22:
#line 184 "vars-parser-yacc.y"
{
                    if (STR(yyvsp[-2]) && STR(yyvsp[0]))
                        yyval = ISET(strcmp(SVAL(yyvsp[-2]), SVAL(yyvsp[0])) >= 0);
                    else
                        yyval = ISET(DVAL(yyvsp[-2]) >= DVAL(yyvsp[0]));

                    PUSH(yyval);
                }
    break;
case 23:
#line 193 "vars-parser-yacc.y"
{
                    if (STR(yyvsp[-2]) && STR(yyvsp[0]))
                        yyval = ISET(strcmp(SVAL(yyvsp[-2]), SVAL(yyvsp[0])) <= 0);
                    else
                        yyval = ISET(DVAL(yyvsp[-2]) <= DVAL(yyvsp[0]));

                    PUSH(yyval);
                }
    break;
case 24:
#line 202 "vars-parser-yacc.y"
{
                    yyval = ISET(IVAL(yyvsp[-2]) && IVAL(yyvsp[0])); PUSH(yyval);
                }
    break;
case 25:
#line 206 "vars-parser-yacc.y"
{
                    yyval = ISET(IVAL(yyvsp[-2]) || IVAL(yyvsp[0])); PUSH(yyval);
                }
    break;
case 26:
#line 210 "vars-parser-yacc.y"
{
                    vregex *r = get_regexp(SVAL(yyvsp[0]));
                    yyval = ISET(r != NULL ? vr_match(SVAL(yyvsp[-2]), r) : 0);
                    PUSH(yyval);
                }
    break;
case 27:
#line 216 "vars-parser-yacc.y"
{
                    vregex *r = get_regexp(SVAL(yyvsp[0]));
                    yyval = ISET(r != NULL ? !vr_match(SVAL(yyvsp[-2]), r) : 0);
                    PUSH(yyval);
                }
    break;
case 28:
#line 222 "vars-parser-yacc.y"
{
                    yyval = ISET(!IVAL(yyvsp[0])); PUSH(yyval);
                }
    break;
case 29:
#line 226 "vars-parser-yacc.y"
{
                    yyval = COPY(IVAL(yyvsp[-4]) ? yyvsp[-2] : yyvsp[0]); PUSH(yyval);
                }
    break;
case 30:
#line 230 "vars-parser-yacc.y"
{
                    yyval = COPY(yyvsp[0]);
                    PUSH(yyvsp[-2]);
                    PUSH(yyval);
                    vp_store(vp_parser, SVAL(yyvsp[-2]), COPY(yyvsp[0]));
                }
    break;
case 31:
#line 237 "vars-parser-yacc.y"
{
                    PUSH(yyvsp[-1]);
                    if (args != NULL)
                        vl_ppush(vp_arglist, args);
                    args = vl_create();
                }
    break;
case 32:
#line 244 "vars-parser-yacc.y"
{
                    if ((yyval = vp_call(vp_parser, SVAL(yyvsp[-4]), args)) == NULL)
                        yyval = vs_create(V_TYPE_UNDEF);
                    PUSH(yyval);
                    vl_destroy(args);
                    args = vl_ppop(vp_arglist);
                }
    break;
case 36:
#line 259 "vars-parser-yacc.y"
{
                    vl_push(args, COPY(yyvsp[0]));
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
#line 264 "vars-parser-yacc.y"


/* Parse current input */
vscalar *
vp_parse(vparser *p, char *expr)
{
    vscalar *retval;
    V_BUF_DECL;

    /* Initialize */
    vp_parser = p;

    /* Add final newline */
    V_BUF_SET(expr);
    V_BUF_ADD("\n");

    /* Clear stack */
    vl_init(vp_stack);

    /* Create argument list */
    if (vp_arglist == NULL)
        vp_arglist = vl_create();

    /* Let's parse! */
    vp_scan_start(V_BUF_VAL);
    yyparse();
    vp_scan_finish();

    /* Get return value */
    if (vl_length(vp_stack) > 0)
        retval = vl_pop(vp_stack);
    else
        retval = vs_create(V_TYPE_UNDEF);

    /* Clean up */
    vp_parser = NULL;

    return retval;
}

/* Get a cached regexp */
static vregex *
get_regexp(char *str)
{
    static vhash *cache = NULL;
    vregex *r = NULL;

    if (cache == NULL)
        cache = vh_create();

    if ((r = vh_pget(cache, str)) != NULL)
        return r;

    if ((r = vr_create(str)) != NULL)
        vh_pstore(cache, str, r);
    else
        vp_err("invalid regexp: %s", str);

    return r;
}

/* Parser print function */
static void
yyprint(FILE *fp, int type, vscalar *s)
{
    switch (type) {
    case ID:
    case VALUE:
        fprintf(fp, " %s", vs_sget(s));
        break;
    }
}

/* Parser error function */
void
yyerror(char *msg)
{
    vp_err(msg);
}
