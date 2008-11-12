#ifndef BISON_VARS_PARSER_YACC_H
# define BISON_VARS_PARSER_YACC_H

# ifndef YYSTYPE
#  define YYSTYPE int
#  define YYSTYPE_IS_TRIVIAL 1
# endif
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


extern YYSTYPE yylval;

#endif /* not BISON_VARS_PARSER_YACC_H */
