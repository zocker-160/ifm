%{
/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
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

#define CHANGE_ERROR(attr) \
        err("can't modify `%s' attribute", #attr)

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
static int repeat = 0;          /* String repeat count */
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
%token        LEAVE UNDEF FINISH GIVE DROP ALL EXCEPT IT UNTIL TIMES NOLINK
%token        NOPATH NONE ALIAS

%token <ival> NORTH EAST SOUTH WEST NORTHEAST NORTHWEST SOUTHEAST SOUTHWEST
%token <ival> UP DOWN IN OUT

%token <ival> INTEGER
%token <dval> REAL
%token <sval> STRING ID VAR

%type  <ival> compass otherdir integer
%type  <sval> string string_repeat
%type  <vval> room item task
%type  <dval> exp

%right        '='
%left	      '+' '-'
%left	      '*' '/' '%'
%left	      PLUS MINUS
%right	      '^'

%%

/************************************************************************/
/* Top-level
/************************************************************************/

stmt_list	: /* empty */
		| stmt_list stmt
		| stmt_list error
		;

stmt		: ctrl_stmt
                | room_stmt
		| item_stmt
		| link_stmt
		| join_stmt
		| task_stmt
		| vars_stmt
		;

/************************************************************************/
/* Control commands
/************************************************************************/

ctrl_stmt       : TITLE string ';'
                {
                    vh_sstore(map, "TITLE", $2);
                }
                | MAP string ';'
                {
                    if (sectnames == NULL)
                        sectnames = vl_create();
                    vl_spush(sectnames, $2);
                }
                ;

/************************************************************************/
/* Rooms
/************************************************************************/

room_stmt	: ROOM string
		{
                    curroom = vh_create();
		    vh_sstore(curroom, "DESC", $2);
                    vh_istore(curroom, "ID", ++roomid);
                    implicit = 0;
                    modify = 0;
		}
                room_attrs ';'
                {
                    vhash *near, *link, *sect = NULL;
                    vlist *list, *dirs;
                    char *str;

                    /* Build new room */
                    vl_ppush(rooms, curroom);

                    if (startroom == NULL)
                        startroom = curroom;

                    /* Put it on appropriate section */
                    if ((near = vh_pget(curroom, "NEAR")) != NULL)
                        sect = vh_pget(near, "SECT");

                    if (sect == NULL) {
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
                        vh_pstore(curroom, "LINK", link);

                        vh_pstore(link, "FROM", near);
                        vh_pstore(link, "TO", curroom);

                        vh_istore(link, "GO",
                                  vh_iget(curroom, "GO"));
                        vh_istore(link, "ONEWAY",
                                  vh_iget(curroom, "ONEWAY"));
                        vh_istore(link, "SPECIAL",
                                  vh_iget(curroom, "SPECIAL"));
                        vh_istore(link, "NOLINK",
                                  vh_iget(curroom, "NOLINK"));
                        vh_istore(link, "NOPATH",
                                  vh_iget(curroom, "NOPATH"));
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
                        vh_pstore(link, "FROM_CMD",
                                  vh_pget(curroom, "FROM_CMD"));
                        vh_pstore(link, "TO_CMD",
                                  vh_pget(curroom, "TO_CMD"));

                        if ((str = vh_sgetref(curroom, "TAG")) != NULL)
                            set_tag("link", str, link, linktags);

                        vh_pstore(link, "DIR", dirs);
                        vl_ppush(links, link);
                    }

                    /* Warn about ignored attributes */
                    if (dirs == NULL || vh_iget(curroom, "NOLINK")) {
                        if (vh_exists(curroom, "GO"))
                            WARN_IGNORED(go);
                        if (vh_exists(curroom, "ONEWAY"))
                            WARN_IGNORED(oneway);
                        if (vh_exists(curroom, "SPECIAL"))
                            WARN_IGNORED(special);
                        if (vh_exists(curroom, "LEN"))
                            WARN_IGNORED(length);
                        if (vh_exists(curroom, "NOPATH"))
                            WARN_IGNORED(nopath);
                        if (vh_exists(curroom, "TO_CMD"))
                            WARN_IGNORED(cmd);
                    }

                    if (dirs == NULL && vh_iget(curroom, "NOLINK"))
                        WARN_IGNORED(nolink);

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
		| room_attrs room_attr
		;

room_attr	: TAG ID
		{
                    if (!modify)
                        set_tag("room", $2, curroom, roomtags);
                    else
                        CHANGE_ERROR(tag);
		}
		| DIR dir_list FROM ID
		{
                    vhash *room;

                    if (!modify) {
                        implicit = 1;

                        vh_pstore(curroom, "DIR", curdirs);
                        curdirs = NULL;

                        room = vh_pget(roomtags, $4);
                        if (room != NULL)
                            vh_pstore(curroom, "NEAR", room);
                        else
                            err("room tag `%s' not yet defined", $4);
                    } else {
                        CHANGE_ERROR(from);
                    }
		}
		| DIR dir_list
		{
                    implicit = 1;

                    if (modify && !vh_exists(curroom, "DIR"))
                        CHANGE_ERROR(dir);

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
		| NOLINK
		{
                    vh_istore(curroom, "NOLINK", 1);
		}
		| NOPATH
		{
                    vh_istore(curroom, "NOPATH", 1);
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
		| LENGTH integer
		{
                    vh_istore(curroom, "LEN", $2);
		}
		| SCORE integer
		{
                    vh_istore(curroom, "SCORE", $2);
		}
                | CMD string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curroom, "TO_CMD", $2);
                }
                | CMD TO string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curroom, "TO_CMD", $3);
                }
                | CMD FROM string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curroom, "FROM_CMD", $3);
                }
		| NOTE string
		{
                    add_attr(curroom, "NOTE", $2);
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

/************************************************************************/
/* Items
/************************************************************************/

item_stmt	: ITEM string
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
		| item_attrs item_attr
		;

item_attr	: TAG ID
		{
                    if (!modify)
                        set_tag("item", $2, curitem, itemtags);
                    else
                        CHANGE_ERROR(tag);
		}
		| IN room
		{
                    vh_store(curitem, "IN", $2);
		}
		| NOTE string
		{
                    add_attr(curitem, "NOTE", $2);
		}
		| HIDDEN
		{
                    vh_istore(curitem, "HIDDEN", 1);
		}
		| GIVEN         /* obsolete */
		{
                    obsolete("`given' attribute", "task `give' attribute");
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
		| SCORE integer
		{
                    vh_istore(curitem, "SCORE", $2);
		}
                | FINISH
                {
                    vh_istore(curitem, "FINISH", 1);
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

/************************************************************************/
/* Links
/************************************************************************/

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
		| link_attrs link_attr
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
		| NOPATH
		{
                    vh_istore(curlink, "NOPATH", 1);
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
		| LENGTH integer
		{
                    vh_istore(curlink, "LEN", $2);
		}
                | CMD string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curlink, "TO_CMD", $2);
                }
                | CMD TO string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curlink, "TO_CMD", $3);
                }
                | CMD FROM string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curlink, "FROM_CMD", $3);
                }
                | TAG ID
		{
                    if (!modify)
                        set_tag("link", $2, curlink, linktags);
                    else
                        CHANGE_ERROR(tag);
		}
                ; 

/************************************************************************/
/* Joins
/************************************************************************/

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
		| join_attrs join_attr
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
		| NOPATH
		{
                    vh_istore(curjoin, "NOPATH", 1);
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
		| LENGTH integer
		{
                    vh_istore(curjoin, "LEN", $2);
		}
                | CMD string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curjoin, "TO_CMD", $2);
                }
                | CMD TO string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curjoin, "TO_CMD", $3);
                }
                | CMD FROM string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curjoin, "FROM_CMD", $3);
                }
                | TAG ID
		{
                    if (!modify)
                        set_tag("join", $2, curjoin, jointags);
                    else
                        CHANGE_ERROR(tag);
		}
		;

/************************************************************************/
/* Tasks
/************************************************************************/

task_stmt	: TASK string
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
		| task_attrs task_attr
		;

task_attr	: TAG ID
		{
                    if (!modify)
                        set_tag("task", $2, curtask, tasktags);
                    else
                        CHANGE_ERROR(tag);
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
		| SCORE integer
		{
                    vh_istore(curtask, "SCORE", $2);
		}
                | FINISH
                {
                    vh_istore(curtask, "FINISH", 1);
                }
                | CMD string_repeat
                {
                    while (repeat-- > 0)
                        add_attr(curtask, "CMD", $2);
                }
                | CMD NONE
                {
                    add_attr(curtask, "CMD", NULL);
                }
		| NOTE string
		{
                    add_attr(curtask, "NOTE", $2);
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

/************************************************************************/
/* Variables
/************************************************************************/

vars_stmt       : ID '=' exp ';'
                {
                    var_set(NULL, $1, vs_dcreate($3));
                }
                | ID ID '=' exp ';'
                {
                    var_set($1, $2, vs_dcreate($4));
                }
                | ID '=' STRING ';'
                {
                    var_set(NULL, $1, vs_screate($3));
                }
                | ID ID '=' STRING ';'
                {
                    var_set($1, $2, vs_screate($4));
                }
                | ID '=' UNDEF ';'
                {
                    var_set(NULL, $1, NULL);
                }
                | ID ID '=' UNDEF ';'
                {
                    var_set($1, $2, NULL);
                }
                | ID ALIAS ID ';'
                {
                    var_alias($1, $3);
                }
                | ID ALIAS UNDEF ';'
                {
                    var_alias($1, NULL);
                }
		;

exp             : INTEGER               { $$ = $1; }
                | REAL                  { $$ = $1; }
                | VAR                   { $$ = var_real($1); }
                | '+' exp %prec PLUS    { $$ = $2; }
                | '-' exp %prec MINUS   { $$ = -$2; }
                | exp '+' exp           { $$ = $1 + $3; }
                | exp '-' exp           { $$ = $1 - $3; }
                | exp '*' exp           { $$ = $1 * $3; }
                | exp '/' exp           { $$ = $1 / $3; }
                | exp '^' exp           { $$ = pow($1, $3); }
                | exp '%' exp           { $$ = fmod($1, $3); }
                | '(' exp ')'           { $$ = $2; }
                ;

integer         : exp                   { $$ = (int) $1; }
                ;

string          : STRING                { $$ = $1; }
                | VAR                   { $$ = var_string($1); }
                ;

string_repeat   : string
                {
                    $$ = $1;
                    repeat = 1;
                }
                | string integer
                {
                    $$ = $1;
                    repeat = $2;
                    if ($2 <= 0)
                        err("invalid repeat count");
                }
                | string TIMES integer /* obsolete */
                {
                    $$ = $1;
                    repeat = $3;
                    if ($3 <= 0)
                        err("invalid repeat count");
                    obsolete("`times' keyword", "just the repeat count");
                }
                ;

/************************************************************************/
/* Directions
/************************************************************************/

dir_list	: dir_elt
		| dir_list dir_elt
		;

dir_elt		: compass
		{
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    vl_ipush(curdirs, $1);
		}
                | compass integer
                {
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if ($2 <= 0)
                        err("invalid repeat count");
                    while ($2-- > 0)
                        vl_ipush(curdirs, $1);
                }
                | compass TIMES integer /* obsolete */
                {
                    if (curdirs == NULL)
                        curdirs = vl_create();
                    if ($3 <= 0)
                        err("invalid repeat count");
                    while ($3-- > 0)
                        vl_ipush(curdirs, $1);
                    obsolete("`times' keyword", "just the repeat count");
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

%%
