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
}

void
raw_map_section(vhash *sect)
{
}

void
raw_map_room(vhash *room)
{
}

void
raw_map_link(vhash *link)
{
}

void
raw_map_join(vhash *join)
{
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
    int score = vh_iget(task, "SCORE");
    int type = vh_iget(task, "TYPE");
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

    if (vh_exists(task, "CMD"))
        printf("cmd: %s\n", vh_sgetref(task, "CMD"));

    if (score > 0)
        printf("score: %d\n", score);

    if (notes != NULL) {
        vl_foreach(elt, notes)
            printf("note: %s\n", vs_sgetref(elt));
    }
}
