/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Functions for building the map */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ifm.h"
#include "ifm-parse.h"

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

/* Add a direction to the current direction list */
void
add_dir(int dir)
{
    if (curdirs == NULL)
	curdirs = vl_create();
    vl_ipush(curdirs, dir);
}

/* Convert direction to X/Y offset */
void
get_offset(int dir, int *xoff, int *yoff)
{
    *xoff = *yoff = 0;

    switch (dir) {
    case NORTH:
	*yoff = 1;
	break;
    case EAST:
	*xoff = 1;
	break;
    case SOUTH:
	*yoff = -1;
	break;
    case WEST:
	*xoff = -1;
	break;
    case NORTHEAST:
	*xoff = 1;
	*yoff = 1;
	break;
    case NORTHWEST:
	*xoff = -1;
	*yoff = 1;
	break;
    case SOUTHEAST:
	*xoff = 1;
	*yoff = -1;
	break;
    case SOUTHWEST:
	*xoff = -1;
	*yoff = -1;
	break;
    default:
        fatal("internal: invalid direction offset");
    }
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

/* Pack sections onto virtual pages */
int
pack_sections(int xmax, int ymax, int border)
{
    int xo1, yo1, xo2, yo2, xc1, yc1, xc2, yc2, v1, v2, rflag;
    int pos, packed, x1, y1, x2, y2, xo, yo, num, xlen, ylen;
    vlist *pages, *newpages, *psects, *opsects;
    vhash *page, *sect, *p1, *p2;
    double r1, r2, ratio;
    vscalar *elt;

    /* Initialise -- one section per page */
    pages = vl_create();
    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        xlen = vh_iget(sect, "XLEN");
        ylen = vh_iget(sect, "YLEN");

        page = vh_create();
        vh_istore(page, "XLEN", xlen);
        vh_istore(page, "YLEN", ylen);
        vl_ppush(pages, page);

        psects = vl_create();
        vh_pstore(page, "SECTS", psects);
        vl_ppush(psects, sect);
    }

    ratio = (double) xmax / ymax;

    /* Pack sections */
    do {
        pos = packed = 0;
        newpages = vl_create();

        while (pos < vl_length(pages)) {
            /* Get next page */
            p1 = vl_pget(pages, pos);
            x1 = vh_iget(p1, "XLEN");
            y1 = vh_iget(p1, "YLEN");

            /* Check if it's better off rotated */
            vh_istore(p1, "ROTATE", ((x1 < y1 && xmax > ymax) ||
                                     (x1 > y1 && xmax < ymax)));

            /* Check if this is the last page */
            if (pos + 1 == vl_length(pages)) {
                vl_ppush(newpages, p1);
                break;
            }

            /* Get following page */
            p2 = vl_pget(pages, pos + 1);
            x2 = vh_iget(p2, "XLEN");
            y2 = vh_iget(p2, "YLEN");

            /* Try combining pages in X direction */
            xc1 = x1 + x2 + border;
            yc1 = MAX(y1, y2);
            v1 = (xc1 <= xmax && yc1 <= ymax);
            r1 = (double) xc1 / yc1;

            /* Try combining pages in Y direction */
            xc2 = MAX(x1, x2);
            yc2 = y1 + y2 + border;
            v2 = (xc2 <= xmax && yc2 <= ymax);
            r2 = (double) xc2 / yc2;

            /* See which is best */
            if (v1 && v2) {
                if (ABS(ratio - r1) < ABS(ratio - r2))
                    v2 = 0;
                else
                    v1 = 0;
            }

            /* Just copy page if nothing can be done */
            if (!v1 && !v2) {
                vl_ppush(newpages, p1);
                pos++;
                continue;
            }

            /* Create merged page */
            page = vh_create();
            psects = vl_create();
            vh_pstore(page, "SECTS", psects);
            xo1 = yo1 = xo2 = yo2 = 0;

            if (v1) {
                vh_istore(page, "XLEN", xc1);
                vh_istore(page, "YLEN", yc1);
                xo2 = x1 + border;

                if (y1 < y2)
                    yo1 = (yc1 - y1) / 2;
                else
                    yo2 = (yc1 - y2) / 2;
            }

            if (v2) {
                vh_istore(page, "XLEN", xc2);
                vh_istore(page, "YLEN", yc2);
                yo1 = y2 + border;

                if (x1 < x2)
                    xo1 = (xc2 - x1) / 2;
                else
                    xo2 = (xc2 - x2) / 2;
            }

            /* Copy sections to new page, updating offsets */
            opsects = vh_pget(p1, "SECTS");
            vl_foreach(elt, opsects) {
                sect = vs_pget(elt);
                vl_ppush(psects, sect);
                xo = vh_iget(sect, "XOFF");
                vh_istore(sect, "XOFF", xo + xo1);
                yo = vh_iget(sect, "YOFF");
                vh_istore(sect, "YOFF", yo + yo1);
            }

            opsects = vh_pget(p2, "SECTS");
            vl_foreach(elt, opsects) {
                sect = vs_pget(elt);
                vl_ppush(psects, sect);
                xo = vh_iget(sect, "XOFF");
                vh_istore(sect, "XOFF", xo + xo2);
                yo = vh_iget(sect, "YOFF");
                vh_istore(sect, "YOFF", yo + yo2);
            }

            /* Get rid of old pages */
            vh_destroy(p1);
            vh_destroy(p2);

            /* Add merged page to list and go to next page pair */
            vl_ppush(newpages, page);
            pos += 2;
            packed++;
        }

        /* Switch to new page list */
        vl_destroy(pages);
        pages = newpages;
    } while (packed);

    /* Give each section its page info and clean up */
    num = 0;
    vl_foreach(elt, pages) {
        page = vs_pget(elt);
        psects = vh_pget(page, "SECTS");
        xlen = vh_iget(page, "XLEN");
        ylen = vh_iget(page, "YLEN");
        rflag = vh_iget(page, "ROTATE");

        num++;
        vl_foreach(elt, psects) {
            sect = vs_pget(elt);
            vh_istore(sect, "PAGE", num);
            vh_istore(sect, "PXLEN", xlen);
            vh_istore(sect, "PYLEN", ylen);
            vh_istore(sect, "ROTATE", rflag);
        }

        vh_destroy(page);
    }

    vl_destroy(pages);
    return num;
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
        error("%s tag `%s' not defined", type, tag);
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
        resolve_tag_list("task", vh_pget(room, "AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(room, "NEED"), itemtags);
    }

    /* Resolve link tags */
    vl_foreach(elt, links) {
        link = vs_pget(elt);
        resolve_tag("room", vh_get(link, "FROM"), roomtags);
        resolve_tag("room", vh_get(link, "TO"), roomtags);
        resolve_tag_list("task", vh_pget(link, "AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(link, "NEED"), itemtags);
    }

    /* Resolve join tags */
    vl_foreach(elt, joins) {
        join = vs_pget(elt);
        resolve_tag("room", vh_get(join, "FROM"), roomtags);
        resolve_tag("room", vh_get(join, "TO"), roomtags);
        resolve_tag_list("task", vh_pget(join, "AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(join, "NEED"), itemtags);
    }

    /* Resolve item tags and build room items lists */
    vl_foreach(elt, items) {
        item = vs_pget(elt);
        resolve_tag("room", vh_get(item, "IN"), roomtags);
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
        resolve_tag_list("task", vh_pget(task, "AFTER"), tasktags);
        resolve_tag_list("item", vh_pget(task, "NEED"), itemtags);
        resolve_tag_list("item", vh_pget(task, "GET"), itemtags);
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
