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

/* Internal stuff */
static vhash *rpos = NULL;      /* Room positions */

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static void put_room_at(vhash *room, int sect, int x, int y);
static vhash *room_at(int sect, int x, int y);
static void resolve_tag(char *type, vscalar *elt, vhash *table);
static void resolve_tag_list(char *type, vlist *list, vhash *table);

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

/* Put room at a given location */
static void
put_room_at(vhash * room, int sect, int x, int y)
{
    sprintf(buf, "%d,%d,%d", sect, x, y);
    vh_pstore(rpos, buf, room);
    vh_istore(room, "X", x);
    vh_istore(room, "Y", y);
}

/* Resolve a tag */
static void
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
static void
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

/* Return room at given location */
static vhash *
room_at(int sect, int x, int y)
{
    sprintf(buf, "%d,%d,%d", sect, x, y);
    return vh_pget(rpos, buf);
}

/* Set/unset a room exit */
void
room_exit(vhash *room, int xoff, int yoff, int flag)
{
    vhash *flags;

    if (xoff == 0 && yoff == 0)
        fatal("internal: invalid direction offset");

    flags = vh_pget(room, "EXIT");
    if (flags == NULL) {
        if (!flag)
            return;
        flags = vh_create();
        vh_pstore(room, "EXIT", flags);
    }

    sprintf(buf, "%d,%d", xoff, yoff);

    if (flag)
        vh_istore(flags, buf, 1);
    else
        vh_delete(flags, buf);
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

/* Set up room exits */
void
setup_exits(void)
{
    vhash *room, *flags;
    vlist *ex, *ey;
    vscalar *elt;
    char *tag;
    int x, y;

    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        flags = vh_pget(room, "EXIT");
        if (flags == NULL)
            continue;

        ex = ey = NULL;
        vh_foreach(tag, elt, flags) {
            if (ex == NULL) {
                ex = vl_create();
                ey = vl_create();
                vh_pstore(room, "EX", ex);
                vh_pstore(room, "EY", ey);
            }

            sscanf(tag, "%d,%d", &x, &y);
            vl_ipush(ex, x);
            vl_ipush(ey, y);
        }

        vh_destroy(flags);
        vh_delete(room, "EXIT");
    }
}

/* Set up room links */
void
setup_links(void)
{
    vhash *room, *near, *link, *from, *to, *other, *sect;
    int x, y, xt, yt, xoff, yoff, dir, num, count, ndirs;
    vlist *dirs, *xpos, *ypos, *list;
    char *fname, *tname, *str;
    vscalar *elt;

    /* Set up links between 'near' rooms */
    vl_foreach(elt, rooms) {
	room = vs_pget(elt);
	near = vh_pget(room, "NEAR");
	if (near == NULL)
	    continue;

	link = vh_create();

	vh_pstore(link, "FROM", near);
	vh_pstore(link, "TO", room);
	vh_istore(link, "GO", vh_iget(room, "GO"));
	vh_istore(link, "ONEWAY", vh_iget(room, "ONEWAY"));
	vh_istore(link, "SPECIAL", vh_iget(room, "SPECIAL"));
	vh_istore(link, "LEN", vh_iget(room, "LEN"));
        vh_pstore(link, "BEFORE", vh_pget(room, "LINK_BEFORE"));
        vh_pstore(link, "AFTER", vh_pget(room, "LINK_AFTER"));
        vh_pstore(link, "NEED", vh_pget(room, "LINK_NEED"));

        if ((str = vh_sgetref(room, "FROM_CMD")) != NULL)
            vh_sstore(link, "FROM_CMD", str);

        if ((str = vh_sgetref(room, "TO_CMD")) != NULL)
            vh_sstore(link, "TO_CMD", str);

	dirs = vh_pget(room, "DIR");
	vl_ipop(dirs);
	vh_pstore(link, "DIR", dirs);

	vl_ppush(links, link);
    }

    /* Build coordinate list for each link */
    vl_foreach(elt, links) {
	link = vs_pget(elt);

	from = vh_pget(link, "FROM");
	fname = vh_sgetref(from, "DESC");

	to = vh_pget(link, "TO");
	tname = vh_sgetref(to, "DESC");

	sect = vh_pget(from, "SECT");
        num = vh_iget(sect, "NUM");

        /* Check rooms are linkable */
	if (vh_pget(to, "SECT") != sect) {
	    err("can't link `%s' to `%s' -- different map sections",
                fname, tname);
	    continue;
	}

        /* Add link to section links */
        list = vh_pget(sect, "LINKS");
        vl_ppush(list, link);
        vh_pstore(link, "SECT", sect);

        /* Get from/to locations */
	x = vh_iget(from, "X");
	y = vh_iget(from, "Y");
	xt = vh_iget(to, "X");
	yt = vh_iget(to, "Y");

        /* Initialise coordinate lists */
	xpos = vl_create();
	vh_pstore(link, "X", xpos);
	ypos = vl_create();
	vh_pstore(link, "Y", ypos);

        vl_ipush(xpos, x);
        vl_ipush(ypos, y);
        count = 0;

        /* Traverse direction list */
        if ((dirs = vh_pget(link, "DIR")) != NULL) {
            ndirs = vl_length(dirs);

            vl_foreach(elt, dirs) {
                dir = vs_iget(elt);
                xoff = dirinfo[dir].xoff;
                yoff = dirinfo[dir].yoff;

                /* Move to new coordinates */
                x += xoff;
                y += yoff;
                vl_ipush(xpos, x);
                vl_ipush(ypos, y);

                /* Check for first direction */
                if (count++ == 0) {
                    /* Remove any room exits */
                    room_exit(from, xoff, yoff, 0);

                    /* Record 'to' direction */
                    vh_istore(link, "TO_DIR", dir);
                }

                /* Check for crossing other rooms */
                if ((x != xt || y != yt || count < ndirs)
                    && (other = room_at(num, x, y)) != NULL)
                    warn("room `%s' crossed by link line",
                         vh_sgetref(other, "DESC"));
            }
        }

        if (x == xt && y == yt) {
            /* Already at target room */
            room_exit(to, -xoff, -yoff, 0);
        } else {
            /* Get final direction to target room */
            xoff = xt - x;
            yoff = yt - y;

            /* Check it's on the grid */
            if (xoff != 0 && yoff != 0 && abs(xoff) != abs(yoff)) {
                warn("link from `%s' to `%s' outside grid",
                     fname, tname);
            } else {
                /* Unitize direction */
                if (xoff != 0)
                    xoff = (xoff > 0 ? 1 : -1);
                if (yoff != 0)
                    yoff = (yoff > 0 ? 1 : -1);

                /* Remove room exits */
                if (count == 0)
                    room_exit(from, xoff, yoff, 0);
                room_exit(to, -xoff, -yoff, 0);

                /* Add final coordinates */
                while (1) {
                    x += xoff;
                    y += yoff;
                    if (x == xt && y == yt)
                        break;

                    vl_ipush(xpos, x);
                    vl_ipush(ypos, y);
                    if ((other = room_at(num, x, y)) != NULL)
                        warn("room `%s' crossed by link line",
                             vh_sgetref(other, "DESC"));
                }
            }

            vl_ipush(xpos, xt);
            vl_ipush(ypos, yt);
        }

        /* Record 'from' direction */
        vh_istore(link, "FROM_DIR", get_direction(-xoff, -yoff));

        /* Record 'to' direction if not already done */
        if (count == 0)
            vh_istore(link, "TO_DIR", get_direction(xoff, yoff));
    }
}

/* Set up room positions */
void
setup_rooms(void)
{
    vhash *base, *room, *near, *other, *sect;
    int nfound, x, y, dir, num;
    vlist *list, *dirs;
    vscalar *elt;

    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        num = vh_iget(sect, "NUM");
        list = vh_pget(sect, "ROOMS");

	/* Position base room */
	base = vl_ptail(list);
	put_room_at(base, num, 0, 0);

	/* Position all other rooms relative to it */
        do {
	    nfound = 0;

	    vl_foreach(elt, list) {
		room = vs_pget(elt);
                if (vh_exists(room, "X"))
		    continue;
		if ((near = vh_pget(room, "NEAR")) == NULL)
		    continue;
                if (!vh_exists(near, "X"))
		    continue;

		x = vh_iget(near, "X");
		y = vh_iget(near, "Y");

		dirs = vh_pget(room, "DIR");
		vl_foreach(elt, dirs) {
		    dir = vs_iget(elt);
		    x += dirinfo[dir].xoff;
		    y += dirinfo[dir].yoff;
		}

		if ((other = room_at(num, x, y)) != NULL)
		    warn("rooms `%s' and `%s' overlap",
                         vh_sgetref(room, "DESC"),
                         vh_sgetref(other, "DESC"));

		put_room_at(room, num, x, y);
		nfound++;
	    }
	} while (nfound > 0);
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
