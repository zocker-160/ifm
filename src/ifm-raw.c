/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Raw output driver */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <vars.h>
#include "ifm-driver.h"
#include "ifm-map.h"
#include "ifm-util.h"
#include "ifm-raw.h"

/* Map function list */
mapfuncs raw_mapfuncs = {
    raw_map_start,
    raw_map_section,
    raw_map_room,
    raw_map_link,
    raw_map_join,
    NULL,
    NULL
};

/* Item function list */
itemfuncs raw_itemfuncs = {
    NULL,
    raw_item_entry,
    NULL
};

/* Task function list */
taskfuncs raw_taskfuncs = {
    NULL,
    raw_task_entry,
    NULL
};

/* Map functions */
void
raw_map_start(void)
{
    char *title;

    if ((title = get_string("title", NULL)) != NULL)
        printf("title: %s\n", title);
}

void
raw_map_section(vhash *sect)
{
    if (vh_exists(sect, "TITLE")) {
        printf("\nsection: %s\n", vh_sgetref(sect, "TITLE"));
        printf("width: %d\n", vh_iget(sect, "XLEN"));
        printf("height: %d\n", vh_iget(sect, "YLEN"));
    }
}

void
raw_map_room(vhash *room)
{
    vlist *list, *ex, *ey;
    vscalar *elt;
    vhash *item;

    printf("\nroom: %s\n", vh_sgetref(room, "DESC"));
    printf("id: %d\n", vh_iget(room, "ID"));
    printf("pos: %d %d\n", vh_iget(room, "X"), vh_iget(room, "Y"));

    if (vh_iget(room, "PUZZLE"))
        printf("puzzle: 1\n");

    if ((list = vh_pget(room, "ITEMS")) != NULL) {
        vl_foreach(elt, list) {
            item = vs_pget(elt);
            if (!vh_iget(item, "HIDDEN"))
                printf("item: %d\n", vh_iget(item, "ID"));
        }
    }

    ex = vh_pget(room, "EX");
    ey = vh_pget(room, "EY");
    if (ex != NULL) {
        while (vl_length(ex) > 0) {
            printf("exit: %d %d\n", vl_ishift(ex), vl_ishift(ey));
        }
    }
}

void
raw_map_link(vhash *link)
{
    vlist *x, *y, *cmds;
    vhash *from, *to;
    vscalar *elt;
    int go;

    from = vh_pget(link, "FROM");
    to = vh_pget(link, "TO");
    printf("\nlink: %d %d\n", vh_iget(from, "ID"), vh_iget(to, "ID"));

    x = vh_pget(link, "X");
    y = vh_pget(link, "Y");
    while (vl_length(x) > 0)
        printf("pos: %d %d\n", vl_ishift(x), vl_ishift(y));

    if (vh_iget(link, "SPECIAL"))
        printf("special: 1\n");

    if (vh_iget(link, "ONEWAY"))
        printf("oneway: 1\n");

    go = vh_iget(link, "GO");
    if (go != D_NONE)
        printf("go: %s\n", dirinfo[go].sname);

    if ((cmds = vh_pget(link, "CMD")) != NULL) {
        vl_foreach(elt, cmds)
            printf("cmd: %s\n", vs_sgetref(elt));
    }
}

void
raw_map_join(vhash *join)
{
    vhash *from, *to;
    vscalar *elt;
    vlist *cmds;
    int go;

    from = vh_pget(join, "FROM");
    to = vh_pget(join, "TO");
    printf("\njoin: %d %d\n", vh_iget(from, "ID"), vh_iget(to, "ID"));

    if (vh_iget(join, "SPECIAL"))
        printf("special: 1\n");

    if (vh_iget(join, "ONEWAY"))
        printf("oneway: 1\n");

    go = vh_iget(join, "GO");
    if (go != D_NONE)
        printf("go: %s\n", dirinfo[go].sname);

    if ((cmds = vh_pget(join, "CMD")) != NULL) {
        vl_foreach(elt, cmds)
            printf("cmd: %s\n", vs_sgetref(elt));
    }
}

/* Item functions */
void
raw_item_entry(vhash *item)
{
    vlist *notes = vh_pget(item, "NOTE");
    vhash *room = vh_pget(item, "ROOM");
    int score = vh_iget(item, "SCORE");
    static int first = 1;
    vscalar *elt;

    if (!first)
        printf("\n");
    first = 0;

    printf("item: %s\n", vh_sgetref(item, "DESC"));

    printf("id: %d\n", vh_iget(item, "ID"));

    if (vh_exists(item, "TAG"))
        printf("tag: %s\n", vh_sgetref(item, "TAG"));

    if (room != NULL)
        printf("room: %s\n", vh_sgetref(room, "DESC"));

    if (score > 0)
        printf("score: %d\n", score);

    if (notes != NULL) {
        vl_foreach(elt, notes)
            printf("note: %s\n", vs_sgetref(elt));
    }
}

/* Task functions */
void
raw_task_entry(vhash *task)
{
    vlist *notes = vh_pget(task, "NOTE");
    vhash *room = vh_pget(task, "ROOM");
    vlist *cmds = vh_pget(task, "CMD");
    int score = vh_iget(task, "SCORE");
    static int first = 1;
    vscalar *elt;

    if (!first)
        printf("\n");
    first = 0;

    printf("task: %s\n", vh_sgetref(task, "DESC"));

    if (vh_exists(task, "TAG"))
        printf("tag: %s\n", vh_sgetref(task, "TAG"));

    if (room != NULL)
        printf("room: %s\n", vh_sgetref(room, "DESC"));

    if (cmds != NULL) {
        vl_foreach(elt, cmds)
            printf("cmd: %s\n", vs_sgetref(elt));
    }

    if (score > 0)
        printf("score: %d\n", score);

    if (notes != NULL) {
        vl_foreach(elt, notes)
            printf("note: %s\n", vs_sgetref(elt));
    }
}
