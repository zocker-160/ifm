%{
/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Lexical scanner */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ifm.h"
#include "ifm-parse.h"

extern int line_number;
%}

LETTER		[A-Za-z_]
DIGIT		[0-9]
INTEGER         {DIGIT}+
REAL		{DIGIT}*\.{DIGIT}+
ALNUM		{LETTER}|{DIGIT}
IDENT		{LETTER}{ALNUM}*
WHITE		[ \t\f]*

%%

#.*		; /* Ignore comments */

{WHITE}		; /* Strip whitespace */

\n              {
		    line_number++;
		}

\"		{
		    int c, cp = 0, quote = 0, eatspace = 0;

		    /* Slurp string in, one char at a time */
		    while (1) {
                        c = input();

                        if        (c == EOF) {
                            yyerror("unexpected EOF");
                            break;
                        } else if (c == '"' && !quote) {
                            break;
                        } else if (c == '\\' && !quote) {
                            quote = 1;
                            continue;
                        } else if (c == '\n') {
                            yylval.sval[cp++] = ' ';
                            eatspace = 1;
                            line_number++;
                        } else if (!eatspace || !isspace(c)) {
                            yylval.sval[cp++] = c;
                        }

                        if (!isspace(c))
                            eatspace = 0;
                        quote = 0;
                        if (cp == BUFSIZ)
                            yyerror("string too long");
		    }

		    yylval.sval[cp] = '\0';
		    return STRING;
		}

"after"         { return AFTER; }
"any"           { return ANY; }
"d"		{ return DOWN; }
"dir"		{ return DIR; }
"down"		{ return DOWN; }
"e"		{ return EAST; }
"east"		{ return EAST; }
"from"		{ return FROM; }
"get"           { return GET; }
"given"         { return GIVEN; }
"go"		{ return GO; }
"goto"		{ return GOTO; }
"hidden"	{ return HIDDEN; }
"in"		{ return IN; }
"item"		{ return ITEM; }
"join"		{ return JOIN; }
"keep"          { return KEEP; }
"last"		{ return LAST; }
"link"		{ return LINK; }
"lost"          { return LOST; }
"n"		{ return NORTH; }
"ne"		{ return NORTHEAST; }
"need"          { return NEED; }
"north"		{ return NORTH; }
"northeast"	{ return NORTHEAST; }
"northwest"	{ return NORTHWEST; }
"note"		{ return NOTE; }
"nw"		{ return NORTHWEST; }
"oneway"	{ return ONEWAY; }
"out"		{ return OUT; }
"puzzle"	{ return PUZZLE; }
"room"		{ return ROOM; }
"s"		{ return SOUTH; }
"score"         { return SCORE; }
"se"		{ return SOUTHEAST; }
"section"	{ return SECTION; }
"south"		{ return SOUTH; }
"southeast"	{ return SOUTHEAST; }
"southwest"	{ return SOUTHWEST; }
"special"	{ return SPECIAL; }
"start"         { return START; }
"sw"		{ return SOUTHWEST; }
"tag"		{ return TAG; }
"task"          { return TASK; }
"title"		{ return TITLE; }
"to"		{ return TO; }
"u"		{ return UP; }
"up"		{ return UP; }
"w"		{ return WEST; }
"west"		{ return WEST; }

{IDENT}		{
		    if (yyleng >= BUFSIZ)
			yyerror("identifier too long");
		    strcpy(yylval.sval, yytext);
		    return IDENT;
		}

{REAL}          {
                    yylval.dval = atof(yytext);
		    return REAL;
		}

{INTEGER}	{
		    yylval.ival = atoi(yytext);
		    return INTEGER;
		}

.		{ return yytext[0]; }

%%
