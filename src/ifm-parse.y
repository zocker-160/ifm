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
        { \
                vlist *l = vh_pget(object, attr); \
                if (l == NULL) { \
                        vh_pstore(object, attr, list); \
                        list = NULL; \
                } else { \
                        vl_append(l, list); \
                        vl_destroy(list); \
                        list = NULL; \
                } \
        }

#define ATTR(name) \
        (implicit ? "LINK_" #name : #name)

#define RESET_IT \
        itroom = ititem = ittask = NULL

#define WARN_IGNORED(attr) \
        warn("attribute `%s' ignored -- no implicit link", #attr)

static vhash *curroom = NULL;   /* Current room */
static vhash *curlink = NULL;   /* Current link */
static vhash *curitem = NULL;   /* Current item */
static vhash *curjoin = NULL;   /* Current join */
static vhash *curtask = NULL;   /* Current task */

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
%token        LEAVE UNDEF FINISH GIVE DROP ALL EXCEPT IT UNTIL

%token <ival> NORTH EAST SOUTH WEST NORTHEAST NORTHWEST SOUTHEAST SOUTHWEST
%token <ival> UP DOWN IN OUT

%token <ival> INTEGER
%token <dval> REAL
%token <sval> STRING ID

%type  <ival> compass otherdir
%type  <vval> var room item task

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
                    vh_istore(curroom, "ID", ++roomid);
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

                        vh_istore(link, "GO",
                                  vh_iget(curroom, "GO"));
                        vh_istore(link, "ONEWAY",
                                  vh_iget(curroom, "ONEWAY"));
                        vh_istore(link, "SPECIAL",
                                  vh_iget(curroom, "SPECIAL"));
                        vh_istore(link, "LEN",
                                  vh_iget(curroom, "LEN"));
                        vh_pstore(link, "BEFORE",
                                  vh_pget(curroom, "LINK_BEFORE"));
                        vh_pstore(link, "AFTER",
                                  vh_pget(curroom, "LINK_AFTER"));
                        vh_pstore(link, "NEED",
                                  vh_pget(curroom, "LINK_NEED"));
                        vh_pstore(link, "LEAVE",
                                  vh_pget(curroom, "LINK_LEAVE"));
                        vh_istore(link, "LEAVEALL",
                                  vh_iget(curroom, "LINK_LEAVEALL"));

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
                        if (vh_exists(curroom, "LEN"))
                            WARN_IGNORED(length);
                        if (vh_exists(curroom, "TO_CMD"))
                            WARN_IGNORED(cmd);
                    }

                    lastroom = curroom;
                    RESET_IT;
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
                {
                    RESET_IT;
                }
		;

room_attrs	: /* empty */
		| room_attrs room_attr sep
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
		| LINK room_list
		{
                    vscalar *elt;
                    vhash *link;
                    char *tag;

                    vl_foreach(elt, currooms) {
                        tag = vs_sgetref(elt);
                        link = vh_create();
                        vh_pstore(link, "FROM", curroom);
                        vh_sstore(link, "TO", tag);
                        vl_ppush(links, link);
                    }

                    vl_destroy(currooms);
                    currooms = NULL;
		}
		| JOIN room_list
		{
                    vscalar *elt;
                    vhash *join;
                    char *tag;

                    vl_foreach(elt, currooms) {
                        tag = vs_sgetref(elt);
                        join = vh_create();
                        vh_pstore(join, "FROM", curroom);
                        vh_sstore(join, "TO", tag);
                        vl_ppush(joins, join);
                    }

                    vl_destroy(currooms);
                    currooms = NULL;
		}
		| GO otherdir
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
                    SET_LIST(curroom, ATTR(NEED), curitems);
                }
		| BEFORE task_list
		{
                    SET_LIST(curroom, ATTR(BEFORE), curtasks);
		}
		| AFTER task_list
		{
                    SET_LIST(curroom, ATTR(AFTER), curtasks);
		}
                | LEAVE item_list_all
                {
                    if (curitems != NULL)
                        SET_LIST(curroom, ATTR(LEAVE), curitems);
                    vh_istore(curroom, ATTR(LEAVEALL), allflag);
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
                    vh_istore(curitem, "ID", ++itemid);
                    modify = 0;
                }
                item_attrs ';'
		{
                    if (!vh_exists(curitem, "IN"))
                        vh_pstore(curitem, "IN", lastroom);

                    lastitem = curitem;
                    vl_ppush(items, curitem);
                    RESET_IT;
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
                {
                    RESET_IT;
                }
		;

item_attrs	: /* empty */
		| item_attrs item_attr sep
		;

item_attr	: TAG ID
		{
                    if (!modify)
                        set_tag("item", $2, curitem, itemtags);
                    else
                        err("can't change item tag name");
		}
		| IN room
		{
                    vh_store(curitem, "IN", $2);
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

link_stmt	: LINK room TO room
                {
                    curlink = vh_create();
                    vh_store(curlink, "FROM", $2);
                    vh_store(curlink, "TO", $4);
                    modify = 0;
                }
                link_attrs ';'
		{
                    vl_ppush(links, curlink);
                    RESET_IT;
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
                {
                    RESET_IT;
                }
		;

link_attrs	: /* empty */
		| link_attrs link_attr sep
		;

link_attr	: DIR dir_list
		{
                    vh_pstore(curlink, "DIR", curdirs);
                    curdirs = NULL;
		}
		| GO otherdir
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
                | LEAVE item_list_all
                {
                    if (curitems != NULL)
                        SET_LIST(curlink, "LEAVE", curitems);
                    vh_istore(curlink, "LEAVEALL", allflag);
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

join_stmt	: JOIN room TO room
                {
                    curjoin = vh_create();
                    vh_store(curjoin, "FROM", $2);
                    vh_store(curjoin, "TO", $4);
                    modify = 0;
                }
                join_attrs ';'
		{
                    vl_ppush(joins, curjoin);
                    RESET_IT;
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
                {
                    RESET_IT;
                }
		;

join_attrs	: /* empty */
		| join_attrs join_attr sep
		;

join_attr	: GO compass
		{
                    vh_istore(curjoin, "GO", $2);
		}
                | GO otherdir
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
                | LEAVE item_list_all
                {
                    if (curitems != NULL)
                        SET_LIST(curjoin, "LEAVE", curitems);
                    vh_istore(curjoin, "LEAVEALL", allflag);
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
                    RESET_IT;
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
                {
                    RESET_IT;
                }
		;

task_attrs	: /* empty */
		| task_attrs task_attr sep
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
		| GIVE item_list
		{
                    SET_LIST(curtask, "GIVE", curitems);
		}
		| GET item_list
		{
                    SET_LIST(curtask, "GET", curitems);
		}
		| DROP item_list_all
		{
                    if (curitems != NULL)
                        SET_LIST(curtask, "DROP", curitems);
                    vh_istore(curtask, "DROPALL", allflag);
		}
		| DROP item_list_all UNTIL task_list
		{
                    if (curitems != NULL)
                        SET_LIST(curtask, "DROP", curitems);
                    vh_istore(curtask, "DROPALL", allflag);
                    SET_LIST(curtask, "DROPUNTIL", curtasks);
		}
		| DROP item_list_all IN room
		{
                    if (curitems != NULL)
                        SET_LIST(curtask, "DROP", curitems);
                    vh_istore(curtask, "DROPALL", allflag);
                    vh_store(curtask, "DROPROOM", $4);
		}
		| DROP item_list_all IN room UNTIL task_list
		{
                    if (curitems != NULL)
                        SET_LIST(curtask, "DROP", curitems);
                    vh_istore(curtask, "DROPALL", allflag);
                    vh_store(curtask, "DROPROOM", $4);
                    SET_LIST(curtask, "DROPUNTIL", curtasks);
		}
		| DROP IN room
		{
                    vh_store(curtask, "DROPROOM", $3);
		}
		| DROP IN room UNTIL task_list
		{
                    vh_store(curtask, "DROPROOM", $3);
                    SET_LIST(curtask, "DROPUNTIL", curtasks);
		}
                | DROP UNTIL task_list
                {
                    SET_LIST(curtask, "DROPUNTIL", curtasks);
                }
		| LOSE item_list
		{
                    SET_LIST(curtask, "LOSE", curitems);
		}
                | GOTO room
                {
                    vh_store(curtask, "GOTO", $2);
                }
                | FOLLOW task
                {
                    vh_store(curtask, "FOLLOW", $2);
                }
		| IN room
		{
                    vh_store(curtask, "IN", $2);
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
                | CMD STRING
                {
                    vh_sstore(curtask, "CMD", $2);
                }
		| NOTE STRING
		{
                    add_note(curtask, $2);
		}
		;

ctrl_stmt       : TITLE STRING ';'
                {
                    set_var(NULL, NULL, "title", vs_screate($2));
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

room_list	: room_elt
		| room_list room_elt
		;

room_elt	: room
		{
                    if (currooms == NULL)
                        currooms = vl_create();
                    vl_push(currooms, $1);
		}
		;

room            : ID
                {
                    $$ = itroom = vs_screate($1);
                }
                | IT
                {
                    if (itroom == NULL)
                        err("no room referred to by `it'");
                    else
                        $$ = vs_copy(itroom);
                }
                | LAST
                {
                    if (lastroom == NULL)
                        err("no room referred to by `last'");
                    else
                        $$ = itroom = vs_pcreate(lastroom);
                }
                ;

item_list	: item_elt
		| item_list item_elt
		;

item_list_all   : item_list                     { allflag = 0; }
                | ALL                           { allflag = 1; }
                | ALL EXCEPT item_list          { allflag = 1; }
                ;

item_elt	: item
		{
                    if (curitems == NULL)
                        curitems = vl_create();
                    vl_push(curitems, $1);
		}
		;

item            : ID
                {
                    $$ = ititem = vs_screate($1);
                }
                | IT
                {
                    if (ititem == NULL)
                        err("no item referred to by `it'");
                    else
                        $$ = vs_copy(ititem);
                }
                | LAST
                {
                    if (lastitem == NULL)
                        err("no item referred to by `last'");
                    else
                        $$ = ititem = vs_pcreate(lastitem);
                }
                ;

task_list	: task_elt
		| task_list task_elt
		;

task_elt	: task
		{
                    if (curtasks == NULL)
                        curtasks = vl_create();
                    vl_push(curtasks, $1);
		}
		;

task            : ID
                {
                    $$ = ittask = vs_screate($1);
                }
                | IT
                {
                    if (ittask == NULL)
                        err("no task referred to by `it'");
                    else
                        $$ = vs_copy(ittask);
                }
                | LAST
                {
                    if (lasttask == NULL)
                        err("no task referred to by `last'");
                    else
                        $$ = ittask = vs_pcreate(lasttask);
                }
                ;

dir_list	: dir_elt
		| dir_list dir_elt
		;

dir_elt		: compass
		{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, $1);
		}
		;

compass		: NORTH		{ $$ = D_NORTH;	    }
		| EAST		{ $$ = D_EAST;	    }
		| SOUTH		{ $$ = D_SOUTH;	    }
		| WEST		{ $$ = D_WEST;	    }
		| NORTHEAST	{ $$ = D_NORTHEAST; }
		| NORTHWEST	{ $$ = D_NORTHWEST; }
		| SOUTHEAST	{ $$ = D_SOUTHEAST; }
		| SOUTHWEST	{ $$ = D_SOUTHWEST; }
		;

otherdir	: IN            { $$ = D_IN;   }
		| OUT           { $$ = D_OUT;  }
		| UP            { $$ = D_UP;   }
		| DOWN          { $$ = D_DOWN; }
		;

var             : INTEGER       { $$ = vs_icreate($1); }
                | REAL          { $$ = vs_dcreate($1); }
                | STRING        { $$ = vs_screate($1); }
                | UNDEF         { $$ = NULL; }
                ;

sep             : ','
                | /* empty */
                ;

%%
