/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Functions for building the map */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ifm.h"

vhash *map = NULL;              /* The map */

vlist *rooms = NULL;            /* List of rooms */
vlist *links = NULL;            /* List of links */
vlist *joins = NULL;            /* List of joins */
vlist *items = NULL;            /* List of items */
vlist *tasks = NULL;            /* List of tasks */
vlist *sects = NULL;            /* List of sections */

vhash *rpos = NULL;             /* Room positions */
vhash *vars = NULL;             /* Variables */

vhash *roomtags = NULL;         /* Tag -> room mapping */
vhash *itemtags = NULL;         /* Tag -> item mapping */
vhash *tasktags = NULL;         /* Tag -> task mapping */

vhash *curroom = NULL;          /* Current room */
vhash *curlink = NULL;          /* Current link */
vhash *curitem = NULL;          /* Current item */
vhash *curjoin = NULL;          /* Current join */
vhash *curtask = NULL;          /* Current task */

vlist *curdirs = NULL;          /* Current direction list */

vlist *curitems = NULL;         /* Current item list */
vlist *curlinks = NULL;         /* Current link list */
vlist *curjoins = NULL;         /* Current join list */
vlist *curtasks = NULL;         /* Current task list */

vhash *startroom = NULL;        /* Starting room */

vhash *lastroom = NULL;         /* Last room visited */
vhash *lastitem = NULL;         /* Last item mentioned */
vhash *lasttask = NULL;         /* Last task mentioned */

vlist *taskorder = NULL;        /* Ordered task list */
vlist *sectnames = NULL;	/* List of section names */

int mapnum = 0;                 /* Current map section number */

/* Scribble buffer */
static char buf[BUFSIZ];

/* Add a direction to the current direction list */
void
add_dir(int dir)
{
    if (curdirs == NULL)
	curdirs = vl_create();
    vl_ipush(curdirs, dir);
}

/* Initialise the map */
void
init_map(void)
{
    map = vh_create();
    rooms = vl_create();
    links = vl_create();
    items = vl_create();
    joins = vl_create();
    tasks = vl_create();
    sects = vl_create();

    rpos = vh_create();
    vars = vh_create();

    roomtags = vh_create();
    itemtags = vh_create();
    tasktags = vh_create();

    taskorder = vl_create();

    vh_pstore(map, "ROOMS", rooms);
    vh_pstore(map, "LINKS", links);
    vh_pstore(map, "ITEMS", items);
    vh_pstore(map, "JOINS", joins);
    vh_pstore(map, "TASKS", taskorder);
    vh_pstore(map, "SECTS", sects);

    vh_pstore(map, "RPOS", rpos);
    vh_pstore(map, "VARS", vars);

    vh_pstore(map, "ROOMTAGS", roomtags);
    vh_pstore(map, "ITEMTAGS", itemtags);
    vh_pstore(map, "TASKTAGS", tasktags);
}

/* Resolve a tag */
void
resolve_tag(char *type, vscalar *elt, vhash *table)
{
    vhash *hash;
    char *tag;

    if (elt == NULL)
        return;

    if (vs_type(elt) != V_STRING)
        return;

    tag = vs_sgetref(elt);
    hash = vh_pget(table, tag);

    if (hash != NULL) {
        vs_pstore(elt, hash);
    } else {
        err("%s tag `%s' not defined", type, tag);
        vh_pstore(table, tag, table);
    }
}

/* Resolve a tag list */
void
resolve_tag_list(char *type, vlist *list, vhash *table)
{
    vscalar *elt;

    if (list == NULL)
        return;

    vl_foreach(elt, list)
        resolve_tag(type, elt, table);
}

/* Resolve all tags */
void
resolve_tags(void)
{
    vhash *room, *item, *link, *join, *task;
    vlist *list;
    vscalar *elt;

    /* Resolve room tags */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        resolve_tag_list("task", vh_pget(room, "BEFORE"), tasktags);
        resolve_tag_list("task", vh_pget(room, "AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(room, "NEED"), itemtags);
        resolve_tag_list("task", vh_pget(room, "LINK_BEFORE"), tasktags);
        resolve_tag_list("task", vh_pget(room, "LINK_AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(room, "LINK_NEED"), itemtags);
    }

    /* Resolve link tags */
    vl_foreach(elt, links) {
        link = vs_pget(elt);
        resolve_tag("room", vh_get(link, "FROM"), roomtags);
        resolve_tag("room", vh_get(link, "TO"), roomtags);
        resolve_tag_list("task", vh_pget(link, "BEFORE"), tasktags);
        resolve_tag_list("task", vh_pget(link, "AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(link, "NEED"), itemtags);
    }

    /* Resolve join tags */
    vl_foreach(elt, joins) {
        join = vs_pget(elt);
        resolve_tag("room", vh_get(join, "FROM"), roomtags);
        resolve_tag("room", vh_get(join, "TO"), roomtags);
        resolve_tag_list("task", vh_pget(join, "BEFORE"), tasktags);
        resolve_tag_list("task", vh_pget(join, "AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(join, "NEED"), itemtags);
    }

    /* Resolve item tags and build room item lists */
    vl_foreach(elt, items) {
        item = vs_pget(elt);
        resolve_tag("room", vh_get(item, "IN"), roomtags);
        resolve_tag_list("task", vh_pget(item, "BEFORE"), tasktags);
        resolve_tag_list("task", vh_pget(item, "AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(item, "NEED"), itemtags);

        room = vh_pget(item, "IN");

        if (room != NULL) {
            vh_pstore(item, "ROOM", room);
            list = vh_pget(room, "ITEMS");

            if (list == NULL) {
                list = vl_create();
                vh_pstore(room, "ITEMS", list);
            }

            vl_ppush(list, item);
        }
    }

    /* Resolve task tags */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        resolve_tag("room", vh_get(task, "IN"), roomtags);
        resolve_tag("room", vh_get(task, "GOTO"), roomtags);
        resolve_tag("task", vh_get(task, "PREV"), tasktags);
        resolve_tag("task", vh_get(task, "NEXT"), tasktags);
        resolve_tag_list("task", vh_pget(task, "AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(task, "NEED"), itemtags);
        resolve_tag_list("item", vh_pget(task, "GET"), itemtags);
        resolve_tag_list("item", vh_pget(task, "LOSE"), itemtags);
        vh_pstore(task, "ROOM", vh_pget(task, "IN"));
    }
}

/* Set a tag table entry */
void
set_tag(char *type, char *tag, vhash *val, vhash *table)
{
    if (vh_pget(table, tag) == NULL) {
	vh_pstore(table, tag, val);
	vh_sstore(val, "TAG", tag);
    } else {
	err("%s tag `%s' already defined", type, tag);
    }
}

/* Set up room names */
void
setup_room_names(int jflag, int tflag)
{
    vhash *room, *join, *from, *to;
    char tag[10], *name;
    int jnum = 0;
    vscalar *elt;

    /* Add join numbers if required */
    if (jflag) {
        vl_foreach(elt, joins) {
            join = vs_pget(elt);
            if (vh_iget(join, "HIDDEN"))
                continue;

            from = vh_pget(join, "FROM");
            to = vh_pget(join, "TO");

            sprintf(tag, " (%d)", ++jnum);

            name = vh_sgetref(from, "RDESC");
            strcpy(buf, (name == NULL ? vh_sgetref(from, "DESC") : name));
            strcat(buf, tag);
            vh_sstore(from, "RDESC", buf);

            name = vh_sgetref(to, "RDESC");
            strcpy(buf, (name == NULL ? vh_sgetref(to, "DESC") : name));
            strcat(buf, tag);
            vh_sstore(to, "RDESC", buf);
        }
    }

    /* Set room names of rooms that don't have one yet */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        if (!vh_exists(room, "RDESC"))
            vh_sstore(room, "RDESC", vh_sgetref(room, "DESC"));
    }

    /* Add tag names if required */
    if (tflag) {
        vl_foreach(elt, rooms) {
            room = vs_pget(elt);
            if (vh_exists(room, "TAG")) {
                sprintf(buf, "%s [%s]", vh_sgetref(room, "RDESC"),
                        vh_sgetref(room, "TAG"));
                vh_sstore(room, "RDESC", buf);
            }
        }
    }
}

/* Set up sections */
void
setup_sections(void)
{
    int minx, miny, maxx, maxy, x, y, first, i;
    vhash *sect, *room, *link;
    vlist *list, *xpos, *ypos;
    vscalar *elt;
    char *title;

    vl_foreach(elt, sects) {
        sect = vs_pget(elt);

        /* Set title */
        if (sectnames != NULL && vl_length(sectnames) > 0) {
            title = vl_sshift(sectnames);
            vh_sstore(sect, "TITLE", title);
        }

        /* Find width and length of section */
        first = 1;
        list = vh_pget(sect, "ROOMS");
        vl_foreach(elt, list) {
            room = vs_pget(elt);
            x = vh_iget(room, "X");
            y = vh_iget(room, "Y");

            if (first) {
                minx = maxx = x;
                miny = maxy = y;
            } else {
                minx = MIN(minx, x);
                maxx = MAX(maxx, x);
                miny = MIN(miny, y);
                maxy = MAX(maxy, y);
            }
        }

        list = vh_pget(sect, "LINKS");
        vl_foreach(elt, list) {
            link = vs_pget(elt);

            xpos = vh_pget(link, "X");
            vl_foreach(elt, xpos) {
                x = vs_iget(elt);
                minx = MIN(minx, x);
                maxx = MAX(maxx, x);
            }

            ypos = vh_pget(link, "Y");
            vl_foreach(elt, ypos) {
                y = vs_iget(elt);
                miny = MIN(miny, y);
                maxy = MAX(maxy, y);
            }
        }

        vh_istore(sect, "XLEN", maxx - minx + 1);
        vh_istore(sect, "YLEN", maxy - miny + 1);

        /* Normalize all coordinates */
        list = vh_pget(sect, "ROOMS");
        vl_foreach(elt, list) {
            room = vs_pget(elt);
            x = vh_iget(room, "X");
            y = vh_iget(room, "Y");
            vh_istore(room, "X", x - minx);
            vh_istore(room, "Y", y - miny);
        }

        list = vh_pget(sect, "LINKS");
        vl_foreach(elt, list) {
            link = vs_pget(elt);

            xpos = vh_pget(link, "X");
            for (i = 0; i < vl_length(xpos); i++) {
                x = vl_iget(xpos, i);
                vl_istore(xpos, i, x - minx);
            }

            ypos = vh_pget(link, "Y");
            for (i = 0; i < vl_length(ypos); i++) {
                y = vl_iget(ypos, i);
                vl_istore(ypos, i, y - miny);
            }
        }
    }
}
