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
#include <vars.h>

#include "ifm-map.h"
#include "ifm-task.h"
#include "ifm-util.h"

#define SET_LIST(object, attr, list) \
        vlist *l = vh_pget(object, attr); \
        if (l == NULL) { \
                vh_pstore(object, attr, list); \
                list = NULL; \
        } else { \
                vl_append(l, list); \
                vl_destroy(list); \
                list = NULL; \
        }

#define WARN_IGNORED(attr) \
        warn("attribute `%s' ignored -- no `dir' link", #attr)

static vhash *curroom = NULL;   /* Current room */
static vhash *curlink = NULL;   /* Current link */
static vhash *curitem = NULL;   /* Current item */
static vhash *curjoin = NULL;   /* Current join */
static vhash *curtask = NULL;   /* Current task */

static vlist *curdirs = NULL;   /* Current direction list */

static vlist *curitems = NULL;  /* Current item list */
static vlist *curlinks = NULL;  /* Current link list */
static vlist *curjoins = NULL;  /* Current join list */
static vlist *curtasks = NULL;  /* Current task list */

static vhash *lastroom = NULL;  /* Last room visited */
static vhash *lastitem = NULL;  /* Last item mentioned */
static vhash *lasttask = NULL;  /* Last task mentioned */

static int modify;              /* Modification flag */
static int implicit;            /* Implicit-link flag */
%}

%union {
    int ival;
    double dval;
    char *sval;
    vscalar *vval;
}

%token	      ROOM ITEM LINK FROM TAG TO DIR ONEWAY HIDDEN PUZZLE NOTE TASK
%token	      AFTER NEED GET SCORE JOIN GO SPECIAL ANY LAST START GOTO MAP
%token        EXIT GIVEN LOST KEEP LENGTH TITLE LOSE SAFE BEFORE FOLLOW CMD
%token        LEAVE UNDEF FINISH

%token <ival> NORTH EAST SOUTH WEST NORTHEAST NORTHWEST SOUTHEAST SOUTHWEST
%token <ival> UP DOWN IN OUT INTEGER

%token <dval> REAL

%token <sval> STRING ID

%type  <ival> go dir

%type  <vval> var

%%

stmt_list	: /* empty */
		| stmt_list stmt
		| stmt_list error
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
                    implicit = 0;
                    modify = 0;
		}
                room_attrs ';'
                {
                    vhash *near, *sect, *link;
                    vlist *list, *dirs;
                    char *str;

                    /* Build new room */
                    vl_ppush(rooms, curroom);

                    if (startroom == NULL)
                        startroom = curroom;

                    /* Put it on appropriate section */
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

                    /* Build implicit link (if any) */
                    if ((dirs = vh_pget(curroom, "DIR")) != NULL) {
                        link = vh_create();

                        vh_pstore(link, "FROM", near);
                        vh_pstore(link, "TO", curroom);
                        vh_istore(link, "GO", vh_iget(curroom, "GO"));
                        vh_istore(link, "ONEWAY", vh_iget(curroom, "ONEWAY"));
                        vh_istore(link, "SPECIAL", vh_iget(curroom, "SPECIAL"));
                        vh_istore(link, "LEN", vh_iget(curroom, "LEN"));
                        vh_pstore(link, "BEFORE", vh_pget(curroom, "LINK_BEFORE"));
                        vh_pstore(link, "AFTER", vh_pget(curroom, "LINK_AFTER"));
                        vh_pstore(link, "NEED", vh_pget(curroom, "LINK_NEED"));
                        vh_pstore(link, "LEAVE", vh_pget(curroom, "LINK_LEAVE"));

                        if ((str = vh_sgetref(curroom, "TAG")) != NULL)
                            set_tag("link", str, link, linktags);

                        if ((str = vh_sgetref(curroom, "FROM_CMD")) != NULL)
                            vh_sstore(link, "FROM_CMD", str);

                        if ((str = vh_sgetref(curroom, "TO_CMD")) != NULL)
                            vh_sstore(link, "TO_CMD", str);

                        vh_pstore(link, "DIR", dirs);
                        vl_ppush(links, link);
                    } else {
                        if (vh_exists(curroom, "GO"))
                            WARN_IGNORED(go);
                        if (vh_exists(curroom, "ONEWAY"))
                            WARN_IGNORED(oneway);
                        if (vh_exists(curroom, "SPECIAL"))
                            WARN_IGNORED(special);
                        if (vh_exists(curroom, "TO_CMD"))
                            WARN_IGNORED(cmd);
                    }

                    lastroom = curroom;
                }
                | ROOM ID
                {
                    modify = 1;
                    if ((curroom = vh_pget(roomtags, $2)) == NULL) {
                        err("room tag `%s' not yet defined", $2);
                        curroom = vh_create();
                    }
                }
                room_attrs ';'
		;

room_attrs	: /* empty */
		| room_attrs room_attr
		;

room_attr	: TAG ID
		{
                    if (!modify)
                        set_tag("room", $2, curroom, roomtags);
                    else
                        err("can't change room tag name");
		}
		| DIR dir_list FROM ID
		{
                    vhash *room;

                    implicit = 1;

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
                    implicit = 1;

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
		| GO go
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
                    startroom = curroom;
		}
                | FINISH
                {
                    vh_istore(curroom, "FINISH", 1);
                }
                | NEED item_list
                {
                    char *attr = (implicit ? "LINK_NEED" : "NEED");
                    SET_LIST(curroom, attr, curitems);
                }
		| BEFORE task_list
		{
                    char *attr = (implicit ? "LINK_BEFORE" : "BEFORE");
                    SET_LIST(curroom, attr, curtasks);
		}
		| AFTER task_list
		{
                    char *attr = (implicit ? "LINK_AFTER" : "AFTER");
                    SET_LIST(curroom, attr, curtasks);
		}
                | LEAVE item_list
                {
                    char *attr = (implicit ? "LINK_LEAVE" : "LEAVE");
                    SET_LIST(curroom, attr, curitems);
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
                    add_note(curroom, $2);
		}
		;

item_stmt	: ITEM STRING
                {
                    curitem = vh_create();
                    vh_sstore(curitem, "DESC", $2);
                    modify = 0;
                }
                item_attrs ';'
		{
                    if (!vh_exists(curitem, "IN"))
                        vh_pstore(curitem, "IN", lastroom);

                    lastitem = curitem;
                    vl_ppush(items, curitem);
		}
                | ITEM ID
                {
                    modify = 1;
                    if ((curitem = vh_pget(itemtags, $2)) == NULL) {
                        err("item tag `%s' not yet defined", $2);
                        curitem = vh_create();
                    }
                }
                item_attrs ';'
		;

item_attrs	: /* empty */
		| item_attrs item_attr
		;

item_attr	: TAG ID
		{
                    if (!modify)
                        set_tag("item", $2, curitem, itemtags);
                    else
                        err("can't change item tag name");
		}
		| IN ID
		{
                    vh_sstore(curitem, "IN", $2);
		}
		| NOTE STRING
		{
                    add_note(curitem, $2);
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
                    SET_LIST(curitem, "NEED", curitems);
                }
                | BEFORE task_list
                {
                    SET_LIST(curitem, "BEFORE", curtasks);
                }
                | AFTER task_list
                {
                    SET_LIST(curitem, "AFTER", curtasks);
                }
		| SCORE INTEGER
		{
                    vh_istore(curitem, "SCORE", $2);
		}
                | FINISH
                {
                    vh_istore(curitem, "FINISH", 1);
                }
		;

link_stmt	: LINK ID TO ID
                {
                    curlink = vh_create();
                    vh_sstore(curlink, "FROM", $2);
                    vh_sstore(curlink, "TO", $4);
                    modify = 0;
                }
                link_attrs ';'
		{
                    vl_ppush(links, curlink);
		}
                | LINK ID
                {
                    modify = 1;
                    if ((curlink = vh_pget(linktags, $2)) == NULL) {
                        err("link tag `%s' not yet defined", $2);
                        curlink = vh_create();
                    }
                }
                link_attrs ';'
		;

link_attrs	: /* empty */
		| link_attrs link_attr
		;

link_attr	: DIR dir_list
		{
                    vh_pstore(curlink, "DIR", curdirs);
                    curdirs = NULL;
		}
		| GO go
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
                    SET_LIST(curlink, "NEED", curitems);
                }
		| BEFORE task_list
		{
                    SET_LIST(curlink, "BEFORE", curtasks);
		}
		| AFTER task_list
		{
                    SET_LIST(curlink, "AFTER", curtasks);
		}
                | LEAVE item_list
                {
                    SET_LIST(curlink, "LEAVE", curitems);
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
                | TAG ID
		{
                    if (!modify)
                        set_tag("link", $2, curlink, linktags);
                    else
                        err("can't change link tag name");
		}
                ; 

join_stmt	: JOIN ID TO ID
                {
                    curjoin = vh_create();
                    vh_sstore(curjoin, "FROM", $2);
                    vh_sstore(curjoin, "TO", $4);
                    modify = 0;
                }
                join_attrs ';'
		{
                    vl_ppush(joins, curjoin);
		}
                | JOIN ID
                {
                    modify = 1;
                    if ((curjoin = vh_pget(jointags, $2)) == NULL) {
                        err("join tag `%s' not yet defined", $2);
                        curjoin = vh_create();
                    }
                }
                join_attrs ';'
		;

join_attrs	: /* empty */
		| join_attrs join_attr
		;

join_attr	: GO go
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
                    SET_LIST(curjoin, "NEED", curitems);
                }
		| BEFORE task_list
		{
                    SET_LIST(curjoin, "BEFORE", curtasks);
		}
		| AFTER task_list
		{
                    SET_LIST(curjoin, "AFTER", curtasks);
		}
                | LEAVE item_list
                {
                    SET_LIST(curjoin, "LEAVE", curitems);
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
                | TAG ID
		{
                    if (!modify)
                        set_tag("join", $2, curjoin, jointags);
                    else
                        err("can't change join tag name");
		}
		;

task_stmt	: TASK STRING
                {
                    curtask = vh_create();
                    vh_sstore(curtask, "DESC", $2);
                    modify = 0;
                }
                task_attrs ';'
		{
                    if (vh_iget(curtask, "NOROOM"))
                        vh_pstore(curtask, "IN", NULL);
                    else if (!vh_exists(curtask, "IN"))
                        vh_pstore(curtask, "IN", lastroom);

                    lasttask = curtask;
                    vl_ppush(tasks, curtask);
		}
                | TASK ID
                {
                    modify = 1;
                    if ((curtask = vh_pget(tasktags, $2)) == NULL) {
                        err("task tag `%s' not yet defined", $2);
                        curtask = vh_create();
                    }
                }
                task_attrs ';'
		;

task_attrs	: /* empty */
		| task_attrs task_attr
		;

task_attr	: TAG ID
		{
                    if (!modify)
                        set_tag("task", $2, curtask, tasktags);
                    else
                        err("can't change task tag name");
		}
		| AFTER task_list
		{
                    SET_LIST(curtask, "AFTER", curtasks);
		}
		| NEED item_list
		{
                    SET_LIST(curtask, "NEED", curitems);
		}
		| GET item_list
		{
                    SET_LIST(curtask, "GET", curitems);
		}
		| LOSE item_list
		{
                    SET_LIST(curtask, "LOSE", curitems);
		}
                | GOTO ID
                {
                    vh_sstore(curtask, "GOTO", $2);
                }
                | FOLLOW ID
                {
                    vh_sstore(curtask, "FOLLOW", $2);
                }
		| IN ID
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
                | FINISH
                {
                    vh_istore(curtask, "FINISH", 1);
                }
		| NOTE STRING
		{
                    add_note(curtask, $2);
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
                | ID '=' var ';'
                {
                    set_var(NULL, NULL, $1, $3);
                }
                | ID ID '=' var ';'
                {
                    set_var($1, NULL, $2, $4);
                }
                | MAP ID '=' var ';'
                {
                    set_var(NULL, "map", $2, $4);
                }
                | ITEM ID '=' var ';'
                {
                    set_var(NULL, "item", $2, $4);
                }
                | TASK ID '=' var ';'
                {
                    set_var(NULL, "task", $2, $4);
                }
                | ID MAP ID '=' var ';'
                {
                    set_var($1, "map", $3, $5);
                }
                | ID ITEM ID '=' var ';'
                {
                    set_var($1, "item", $3, $5);
                }
                | ID TASK ID '=' var ';'
                {
                    set_var($1, "task", $3, $5);
                }
		;

link_list	: link_elt
		| link_list link_elt
		;

link_elt	: ID
		{
                    if (curlinks == NULL)
                        curlinks = vl_create();
                    vl_spush(curlinks, $1);
		}
		;

join_list	: join_elt
		| join_list join_elt
		;

join_elt	: ID
		{
                    if (curjoins == NULL)
                        curjoins = vl_create();
                    vl_spush(curjoins, $1);
		}
		;

task_list	: task_elt
		| task_list task_elt
		;

task_elt	: ID
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

item_elt	: ID
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

dir		: NORTH		{ $$ = D_NORTH;	    }
		| EAST		{ $$ = D_EAST;	    }
		| SOUTH		{ $$ = D_SOUTH;	    }
		| WEST		{ $$ = D_WEST;	    }
		| NORTHEAST	{ $$ = D_NORTHEAST; }
		| NORTHWEST	{ $$ = D_NORTHWEST; }
		| SOUTHEAST	{ $$ = D_SOUTHEAST; }
		| SOUTHWEST	{ $$ = D_SOUTHWEST; }
		;

go		: IN            { $$ = D_IN;   }
		| OUT           { $$ = D_OUT;  }
		| UP            { $$ = D_UP;   }
		| DOWN          { $$ = D_DOWN; }
                | dir
		;

var             : INTEGER       { $$ = vs_icreate($1); }
                | REAL          { $$ = vs_dcreate($1); }
                | STRING        { $$ = vs_screate($1); }
                | UNDEF         { $$ = NULL; }
                ;

%%
