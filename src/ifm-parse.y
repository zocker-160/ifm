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

room_stmt	: ROOM STRING
		{
                    curroom = vh_create();
		    vh_sstore(curroom, "DESC", $2);
		}
                room_attrs ';'
                {
                    vhash *near, *sect;
                    vlist *list;

                    if (curroom != NULL)
                        vl_ppush(rooms, curroom);

                    if (startroom == NULL || vh_iget(curroom, "START"))
                        startroom = curroom;

                    near = vh_pget(curroom, "NEAR");
                    if (near != NULL) {
                        sect = vh_pget(near, "SECT");
                    } else {
                        sect = vh_create();
                        vl_ppush(sects, sect);
                        vh_istore(sect, "NUM", vl_length(sects));
                        vh_pstore(sect, "ROOMS", vl_create());
                        vh_pstore(sect, "LINKS", vl_create());
                    }

                    vh_pstore(curroom, "SECT", sect);
                    list = vh_pget(sect, "ROOMS");
                    vl_punshift(list, curroom);

                    if (!vh_exists(curroom, "DIR")) {
                        if (vh_exists(curroom, "ONEWAY"))
                            warn("attribute `oneway' ignored -- no `dir' link");
                        if (vh_exists(curroom, "SPECIAL"))
                            warn("attribute `special' ignored -- no `dir' link");
                    }

                    lastroom = curroom;
                    curroom = NULL;
                }
		;

room_attrs	: /* empty */
		| room_attrs room_attr
		;

room_attr	: TAG IDENT
		{
                    set_tag("room", $2, curroom, roomtags);
		}
		| DIR dir_list FROM IDENT
		{
                    vhash *room;

                    vh_pstore(curroom, "DIR", curdirs);
                    curdirs = NULL;

                    room = vh_pget(roomtags, $4);
                    if (room != NULL)
                        vh_pstore(curroom, "NEAR", room);
                    else
                        err("room tag `%s' not yet defined", $4);
		}
		| DIR dir_list
		{
                    vh_pstore(curroom, "DIR", curdirs);
                    curdirs = NULL;

                    if (lastroom == NULL)
                        err("no last room");
                    else
                        vh_pstore(curroom, "NEAR", lastroom);
		}
		| EXIT dir_list
		{
                    vscalar *elt;
                    int dir;

                    vl_foreach(elt, curdirs) {
                        dir = vs_iget(elt);
                        room_exit(curroom, dirinfo[dir].xoff,
                                  dirinfo[dir].yoff, 1);
                    }

                    curdirs = NULL;
		}
		| LINK link_list
		{
                    vscalar *elt;
                    vhash *link;
                    char *tag;

                    vl_foreach(elt, curlinks) {
                        tag = vs_sgetref(elt);
                        link = vh_create();
                        vh_pstore(link, "FROM", curroom);
                        vh_sstore(link, "TO", tag);
                        vl_ppush(links, link);
                    }

                    vl_destroy(curlinks);
                    curlinks = NULL;
		}
		| JOIN join_list
		{
                    vscalar *elt;
                    vhash *join;
                    char *tag;

                    vl_foreach(elt, curjoins) {
                        tag = vs_sgetref(elt);
                        join = vh_create();
                        vh_pstore(join, "FROM", curroom);
                        vh_sstore(join, "TO", tag);
                        vl_ppush(joins, join);
                    }

                    vl_destroy(curjoins);
                    curjoins = NULL;
		}
		| GO go_flag
		{
                    vh_istore(curroom, "GO", $2);
		}
		| ONEWAY
		{
                    vh_istore(curroom, "ONEWAY", 1);
		}
		| SPECIAL
		{
                    vh_istore(curroom, "SPECIAL", 1);
		}
		| PUZZLE
		{
                    vh_istore(curroom, "PUZZLE", 1);
		}
		| START
		{
                    vh_istore(curroom, "START", 1);
		}
                | NEED item_list
                {
                    if (vh_exists(curroom, "DIR"))
                        vh_pstore(curroom, "LINK_NEED", curitems);
                    else
                        vh_pstore(curroom, "NEED", curitems);

                    curitems = NULL;
                }
		| BEFORE task_list
		{
                    if (vh_exists(curroom, "DIR"))
                        vh_pstore(curroom, "LINK_BEFORE", curtasks);
                    else
                        vh_pstore(curroom, "BEFORE", curtasks);

                    curtasks = NULL;
		}
		| AFTER task_list
		{
                    if (vh_exists(curroom, "DIR"))
                        vh_pstore(curroom, "LINK_AFTER", curtasks);
                    else
                        vh_pstore(curroom, "AFTER", curtasks);

                    curtasks = NULL;
		}
                | LEAVE item_list
                {
                    /* FINISH ME */
                }
		| LENGTH INTEGER
		{
                    vh_istore(curroom, "LEN", $2);
		}
		| SCORE INTEGER
		{
                    vh_istore(curroom, "SCORE", $2);
		}
                | CMD STRING
                {
                    if (!vh_exists(curroom, "TO_CMD"))
                        vh_sstore(curroom, "TO_CMD", $2);
                    else
                        vh_sstore(curroom, "FROM_CMD", $2);
                }
		| NOTE STRING
		{
                    vh_sstore(curroom, "NOTE", $2);
		}
		;

item_stmt	: ITEM STRING
                {
                    curitem = vh_create();
                    vh_sstore(curitem, "DESC", $2);
                }
                item_attrs ';'
		{
                    if (!vh_exists(curitem, "IN"))
                        vh_pstore(curitem, "IN", lastroom);

                    lastitem = curitem;
                    vl_ppush(items, curitem);
                    curitem = NULL;
		}
		;

item_attrs	: /* empty */
		| item_attrs item_attr
		;

item_attr	: TAG IDENT
		{
                    set_tag("item", $2, curitem, itemtags);
		}
		| IN IDENT
		{
                    vh_sstore(curitem, "IN", $2);
		}
		| NOTE STRING
		{
                    vh_sstore(curitem, "NOTE", $2);
		}
		| HIDDEN
		{
                    vh_istore(curitem, "HIDDEN", 1);
		}
		| GIVEN
		{
                    vh_istore(curitem, "GIVEN", 1);
		}
		| LOST
		{
                    vh_istore(curitem, "LOST", 1);
		}
		| KEEP
		{
                    vh_istore(curitem, "KEEP", 1);
		}
                | NEED item_list
                {
                    vh_pstore(curitem, "NEED", curitems);
                    curitems = NULL;
                }
                | BEFORE task_list
                {
                    vh_pstore(curitem, "BEFORE", curtasks);
                    curtasks = NULL;
                }
                | AFTER task_list
                {
                    vh_pstore(curitem, "AFTER", curtasks);
                    curtasks = NULL;
                }
		| SCORE INTEGER
		{
                    vh_istore(curitem, "SCORE", $2);
		}
		;

link_stmt	: LINK IDENT TO IDENT
                {
                    curlink = vh_create();
                    vh_sstore(curlink, "FROM", $2);
                    vh_sstore(curlink, "TO", $4);
                }
                link_attrs ';'
		{
                    vl_ppush(links, curlink);
                    curlink = NULL;
		}
		;

link_attrs	: /* empty */
		| link_attrs link_attr
		;

link_attr	: DIR dir_list
		{
                    vh_pstore(curlink, "DIR", curdirs);
                    curdirs = NULL;
		}
		| GO go_flag
		{
                    vh_istore(curlink, "GO", $2);
		}
		| ONEWAY
		{
                    vh_istore(curlink, "ONEWAY", 1);
		}
		| SPECIAL
		{
                    vh_istore(curlink, "SPECIAL", 1);
		}
		| HIDDEN
		{
                    vh_istore(curlink, "HIDDEN", 1);
		}
                | NEED item_list
                {
                    vh_pstore(curlink, "NEED", curitems);
                    curitems = NULL;
                }
		| BEFORE task_list
		{
                    vh_pstore(curlink, "BEFORE", curtasks);
                    curtasks = NULL;
		}
		| AFTER task_list
		{
                    vh_pstore(curlink, "AFTER", curtasks);
                    curtasks = NULL;
		}
		| LENGTH INTEGER
		{
                    vh_istore(curlink, "LEN", $2);
		}
                | CMD STRING
                {
                    if (!vh_exists(curlink, "TO_CMD"))
                        vh_sstore(curlink, "TO_CMD", $2);
                    else
                        vh_sstore(curlink, "FROM_CMD", $2);
                }
		;

join_stmt	: JOIN IDENT TO IDENT
                {
                    curjoin = vh_create();
                    vh_sstore(curjoin, "FROM", $2);
                    vh_sstore(curjoin, "TO", $4);
                }
                join_attrs ';'
		{
                    vl_ppush(joins, curjoin);
                    curjoin = NULL;
		}
		;

join_attrs	: /* empty */
		| join_attrs join_attr
		;

join_attr	: GO go_flag
		{
                    vh_istore(curjoin, "GO", $2);
		}
		| ONEWAY
		{
                    vh_istore(curjoin, "ONEWAY", 1);
		}
		| HIDDEN
		{
                    vh_istore(curjoin, "HIDDEN", 1);
		}
                | NEED item_list
                {
                    vh_pstore(curjoin, "NEED", curitems);
                    curitems = NULL;
                }
		| BEFORE task_list
		{
                    vh_pstore(curjoin, "BEFORE", curtasks);
                    curtasks = NULL;
		}
		| AFTER task_list
		{
                    vh_pstore(curjoin, "AFTER", curtasks);
                    curtasks = NULL;
		}
		| LENGTH INTEGER
		{
                    vh_istore(curjoin, "LEN", $2);
		}
                | CMD STRING
                {
                    if (!vh_exists(curjoin, "TO_CMD"))
                        vh_sstore(curjoin, "TO_CMD", $2);
                    else
                        vh_sstore(curjoin, "FROM_CMD", $2);
                }
		;

task_stmt	: TASK STRING
                {
                    curtask = vh_create();
                    vh_sstore(curtask, "DESC", $2);
                }
                task_attrs ';'
		{
                    if (vh_iget(curtask, "NOROOM"))
                        vh_pstore(curtask, "IN", NULL);
                    else if (!vh_exists(curtask, "IN"))
                        vh_pstore(curtask, "IN", lastroom);

                    lasttask = curtask;
                    vl_ppush(tasks, curtask);
                    curtask = NULL;
		}
		;

task_attrs	: /* empty */
		| task_attrs task_attr
		;

task_attr	: TAG IDENT
		{
                    set_tag("task", $2, curtask, tasktags);
		}
		| AFTER task_list
		{
                    vh_pstore(curtask, "AFTER", curtasks);
                    curtasks = NULL;
		}
		| NEED item_list
		{
                    vh_pstore(curtask, "NEED", curitems);
                    curitems = NULL;
		}
		| GET item_list
		{
                    vh_pstore(curtask, "GET", curitems);
                    curitems = NULL;
		}
		| LOSE item_list
		{
                    vh_pstore(curtask, "LOSE", curitems);
                    curitems = NULL;
		}
                | GOTO IDENT
                {
                    vh_sstore(curtask, "GOTO", $2);
                }
                | NEXT IDENT
                {
                    vh_sstore(curtask, "NEXT", $2);
                }
                | PREV IDENT
                {
                    vh_sstore(curtask, "PREV", $2);
                }
		| IN IDENT
		{
                    vh_sstore(curtask, "IN", $2);
		}
		| IN ANY
		{
                    vh_istore(curtask, "NOROOM", 1);
		}
                | SAFE
                {
                    vh_istore(curtask, "SAFE", 1);
                }
		| SCORE INTEGER
		{
                    vh_istore(curtask, "SCORE", $2);
		}
		| NOTE STRING
		{
                    vh_sstore(curtask, "NOTE", $2);
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
                    if (curlinks == NULL)
                        curlinks = vl_create();
                    vl_spush(curlinks, $1);
		}
		;

join_list	: join_elt
		| join_list join_elt
		;

join_elt	: IDENT
		{
                    if (curjoins == NULL)
                        curjoins = vl_create();
                    vl_spush(curjoins, $1);
		}
		;

task_list	: task_elt
		| task_list task_elt
		;

task_elt	: IDENT
		{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_spush(curtasks, $1);
		}
                | LAST
		{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    if (lasttask == NULL)
                        err("no last task");
                    else
                        vl_ppush(curtasks, lasttask);
		}
		;

item_list	: item_elt
		| item_list item_elt
		;

item_elt	: IDENT
		{
                    if (curitems == NULL)
                        curitems = vl_create();
                    vl_spush(curitems, $1);
		}
                | LAST
		{
                    if (curitems == NULL)
                        curitems = vl_create();
                    if (lastitem == NULL)
                        err("no last item");
                    else
                        vl_ppush(curitems, lastitem);
		}
		;

dir_list	: dir_elt
		| dir_list dir_elt
		;

dir_elt		: dir
		{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, $1);
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
