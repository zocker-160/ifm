%{
/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Lexical scanner */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vars.h>

#include "ifm-main.h"
#include "ifm-util.h"
#include "ifm-parse.h"

/* Internal string buffer */
static vbuffer *sbuf = NULL;

/* Current line number */
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
		    int c, quote = 0, eatspace = 0;

                    /* Initialise buffer */
                    if (sbuf == NULL)
                        sbuf = vb_create();
                    else
                        vb_empty(sbuf);

		    /* Slurp string in, one char at a time */
		    while (1) {
                        c = input();

                        if        (c == EOF) {
                            yyerror("unterminated string");
                            break;
                        } else if (c == '"' && !quote) {
                            break;
                        } else if (c == '\\' && !quote) {
                            quote = 1;
                            continue;
                        } else if (c == '\n') {
                            vb_putc(sbuf, ' ');
                            eatspace = 1;
                            line_number++;
                        } else if (!eatspace || !isspace(c)) {
                            vb_putc(sbuf, c);
                        }

                        if (!isspace(c))
                            eatspace = 0;
                        quote = 0;
		    }

		    yylval.sval = vb_getcopy(sbuf);
		    return STRING;
		}

"after"         { return AFTER; }
"any"           { return ANY; }
"before"        { return BEFORE; }
"cmd"           { return CMD; }
"d"		{ return DOWN; }
"dir"		{ return DIR; }
"down"		{ return DOWN; }
"e"		{ return EAST; }
"east"		{ return EAST; }
"exit"		{ return EXIT; }
"finish"        { return FINISH; }
"follow"        { return FOLLOW; }
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
"leave"		{ return LEAVE; }
"length"	{ return LENGTH; }
"link"		{ return LINK; }
"lose"          { return LOSE; }
"lost"          { return LOST; }
"map"           { return MAP; }
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
"safe"          { return SAFE; }
"score"         { return SCORE; }
"se"		{ return SOUTHEAST; }
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
"undef"         { return UNDEF; }
"up"		{ return UP; }
"w"		{ return WEST; }
"west"		{ return WEST; }

{IDENT}		{
		    if (yyleng >= BUFSIZ)
			yyerror("identifier too long");
		    yylval.sval = v_strdup(yytext);
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
