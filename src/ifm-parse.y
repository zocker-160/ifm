%{
/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Input parser */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ifm.h"

static char buf[BUFSIZ];
%}

%union {
    int ival;
    double dval;
    char *sval;
    vscalar *vval;
}

%token	      ROOM ITEM LINK FROM TAG TO DIR ONEWAY HIDDEN PUZZLE NOTE TASK
%token	      AFTER NEED GET SCORE JOIN GO SPECIAL ANY LAST START GOTO MAP
%token        EXIT GIVEN LOST KEEP LENGTH TITLE LOSE SAFE BEFORE NEXT UNDEF
%token        PREV CMD LEAVE

%token <ival> NORTH EAST SOUTH WEST NORTHEAST NORTHWEST SOUTHEAST SOUTHWEST
%token <ival> UP DOWN IN OUT INTEGER

%token <dval> REAL

%token <sval> STRING IDENT

%type  <ival> go_flag dir

%type  <vval> var

%%

stmt_list	: /* empty */
		| stmt_list stmt
		;

stmt		: room_stmt
		| item_stmt
		| link_stmt
		| join_stmt
		| task_stmt
		| ctrl_stmt
		;

room_stmt	: ROOM STRING room_attrs ';'
		{
		    set_room_attr("DESC", $2);
		    add_room();
		}
		;

room_attrs	: /* empty */
		| room_attrs room_attr
		;

room_attr	: TAG IDENT
		{
		    set_room_tag($2);
		}
		| DIR dir_list FROM IDENT
		{
		    set_room_dirs();
		    set_room_near($4);
		}
		| DIR dir_list
		{
		    set_room_dirs();
		    set_room_near(NULL);
		}
		| EXIT dir_list
		{
		    set_room_exits();
		}
		| LINK link_list
		{
		    set_room_links();
		}
		| JOIN join_list
		{
		    set_room_joins();
		}
		| GO go_flag
		{
		    sprintf(buf, "%d", $2);
		    set_room_attr("GO", buf);
		}
		| ONEWAY
		{
		    set_room_attr("ONEWAY", "1");
		}
		| SPECIAL
		{
		    set_room_attr("SPECIAL", "1");
		}
		| PUZZLE
		{
		    set_room_attr("PUZZLE", "1");
		}
		| START
		{
		    set_room_attr("START", "1");
		}
                | NEED item_list
                {
                    set_room_items();
                }
		| BEFORE task_list
		{
		    set_room_tasks("BEFORE");
		}
		| AFTER task_list
		{
		    set_room_tasks("AFTER");
		}
		| LENGTH INTEGER
		{
		    sprintf(buf, "%d", $2);
		    set_room_attr("LEN", buf);
		}
		| SCORE INTEGER
		{
		    sprintf(buf, "%d", $2);
		    set_room_attr("SCORE", buf);
		}
                | CMD STRING
                {
                    set_room_cmd($2);
                }
		| NOTE STRING
		{
		    set_room_attr("NOTE", $2);
		}
		;

item_stmt	: ITEM STRING item_attrs ';'
		{
		    set_item_attr("DESC", $2);
		    add_item();
		}
		;

item_attrs	: /* empty */
		| item_attrs item_attr
		;

item_attr	: TAG IDENT
		{
		    set_item_tag($2);
		}
		| IN IDENT
		{
		    set_item_attr("IN", $2);
		}
		| NOTE STRING
		{
		    set_item_attr("NOTE", $2);
		}
		| HIDDEN
		{
		    set_item_attr("HIDDEN", "1");
		}
		| GIVEN
		{
		    set_item_attr("GIVEN", "1");
		}
		| LOST
		{
		    set_item_attr("LOST", "1");
		}
		| KEEP
		{
		    set_item_attr("KEEP", "1");
		}
                | NEED item_list
                {
                    set_item_items();
                }
                | BEFORE task_list
                {
                    set_item_tasks("BEFORE");
                }
                | AFTER task_list
                {
                    set_item_tasks("AFTER");
                }
		| SCORE INTEGER
		{
		    sprintf(buf, "%d", $2);
		    set_item_attr("SCORE", buf);
		}
		;

link_stmt	: LINK IDENT TO IDENT link_attrs ';'
		{
		    add_link($2, $4);
		}
		;

link_attrs	: /* empty */
		| link_attrs link_attr
		;

link_attr	: DIR dir_list
		{
		    set_link_dirs();
		}
		| GO go_flag
		{
		    sprintf(buf, "%d", $2);
		    set_link_attr("GO", buf);
		}
		| ONEWAY
		{
		    set_link_attr("ONEWAY", "1");
		}
		| SPECIAL
		{
		    set_link_attr("SPECIAL", "1");
		}
		| HIDDEN
		{
		    set_link_attr("HIDDEN", "1");
		}
                | NEED item_list
                {
                    set_link_items();
                }
		| BEFORE task_list
		{
		    set_link_tasks("BEFORE");
		}
		| AFTER task_list
		{
		    set_link_tasks("AFTER");
		}
		| LENGTH INTEGER
		{
		    sprintf(buf, "%d", $2);
		    set_link_attr("LEN", buf);
		}
                | CMD STRING
                {
                    set_link_cmd($2);
                }
		;

join_stmt	: JOIN IDENT TO IDENT join_attrs ';'
		{
		    add_join($2, $4);
		}
		;

join_attrs	: /* empty */
		| join_attrs join_attr
		;

join_attr	: GO go_flag
		{
		    sprintf(buf, "%d", $2);
		    set_join_attr("GO", buf);
		}
		| ONEWAY
		{
		    set_join_attr("ONEWAY", "1");
		}
		| HIDDEN
		{
		    set_join_attr("HIDDEN", "1");
		}
                | NEED item_list
                {
                    set_join_items();
                }
		| BEFORE task_list
		{
		    set_join_tasks("BEFORE");
		}
		| AFTER task_list
		{
		    set_join_tasks("AFTER");
		}
		| LENGTH INTEGER
		{
		    sprintf(buf, "%d", $2);
		    set_join_attr("LEN", buf);
		}
                | CMD STRING
                {
                    set_join_cmd($2);
                }
		;

task_stmt	: TASK STRING task_attrs ';'
		{
		    set_task_attr("DESC", $2);
		    add_task();
		}
		;

task_attrs	: /* empty */
		| task_attrs task_attr
		;

task_attr	: TAG IDENT
		{
		    set_task_tag($2);
		}
		| AFTER task_list
		{
		    set_task_after();
		}
		| NEED item_list
		{
		    set_task_items("NEED");
		}
		| GET item_list
		{
		    set_task_items("GET");
		}
		| LOSE item_list
		{
		    set_task_items("LOSE");
		}
                | GOTO IDENT
                {
                    set_task_attr("GOTO", $2);
                }
                | NEXT IDENT
                {
                    set_task_attr("NEXT", $2);
                }
                | PREV IDENT
                {
                    set_task_attr("PREV", $2);
                }
		| IN IDENT
		{
		    set_task_attr("IN", $2);
		}
		| IN ANY
		{
		    set_task_attr("NOROOM", "1");
		}
                | SAFE
                {
                    set_task_attr("SAFE", "1");
                }
		| SCORE INTEGER
		{
		    sprintf(buf, "%d", $2);
		    set_task_attr("SCORE", buf);
		}
		| NOTE STRING
		{
		    set_task_attr("NOTE", $2);
		}
		;

ctrl_stmt       : TITLE var ';'
                {
                    set_var(NULL, NULL, "title", $2);
                }
                | MAP STRING ';'
                {
                    if (sectnames == NULL)
                        sectnames = vl_create();
                    vl_spush(sectnames, $2);
                    mapnum++;
                }
                | IDENT '=' var ';'
                {
                    set_var(NULL, NULL, $1, $3);
                }
                | IDENT IDENT '=' var ';'
                {
                    set_var($1, NULL, $2, $4);
                }
                | MAP IDENT '=' var ';'
                {
                    set_var(NULL, "map", $2, $4);
                }
                | ITEM IDENT '=' var ';'
                {
                    set_var(NULL, "item", $2, $4);
                }
                | TASK IDENT '=' var ';'
                {
                    set_var(NULL, "task", $2, $4);
                }
                | IDENT MAP IDENT '=' var ';'
                {
                    set_var($1, "map", $3, $5);
                }
                | IDENT ITEM IDENT '=' var ';'
                {
                    set_var($1, "item", $3, $5);
                }
                | IDENT TASK IDENT '=' var ';'
                {
                    set_var($1, "task", $3, $5);
                }
		;

link_list	: link_elt
		| link_list link_elt
		;

link_elt	: IDENT
		{
		    add_room_link($1);
		}
		;

join_list	: join_elt
		| join_list join_elt
		;

join_elt	: IDENT
		{
		    add_room_join($1);
		}
		;

task_list	: task_elt
		| task_list task_elt
		;

task_elt	: IDENT
		{
		    add_task_list($1);
		}
                | LAST
		{
		    add_task_list(NULL);
		}
		;

item_list	: item_elt
		| item_list item_elt
		;

item_elt	: IDENT
		{
		    add_item_list($1);
		}
                | LAST
		{
		    add_item_list(NULL);
		}
		;

dir_list	: dir_elt
		| dir_list dir_elt
		;

dir_elt		: dir
		{
		    add_dir($1);
		}
		;

dir		: NORTH		{ $$ = D_NORTH;	  }
		| EAST		{ $$ = D_EAST;	  }
		| SOUTH		{ $$ = D_SOUTH;	  }
		| WEST		{ $$ = D_WEST;	  }
		| NORTHEAST	{ $$ = D_NORTHEAST; }
		| NORTHWEST	{ $$ = D_NORTHWEST; }
		| SOUTHEAST	{ $$ = D_SOUTHEAST; }
		| SOUTHWEST	{ $$ = D_SOUTHWEST; }
		;

go_flag		: IN            { $$ = D_IN;   }
		| OUT           { $$ = D_OUT;  }
		| UP            { $$ = D_UP;   }
		| DOWN          { $$ = D_DOWN; }
		;

var             : INTEGER       { $$ = vs_istore(NULL, $1); }
                | REAL          { $$ = vs_dstore(NULL, $1); }
                | STRING        { $$ = vs_sstore(NULL, $1); }
                | UNDEF         { $$ = NULL; }
                ;

%%
