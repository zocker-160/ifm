/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
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
#include "ifm.h"
#include "ifm-parse.h"
#include "ifm-raw.h"

/* Item function list */
itemfuncs raw_itemfuncs = {
    raw_item_start,
    raw_item_entry,
    NULL
};

/* Task function list */
taskfuncs raw_taskfuncs = {
    raw_task_start,
    raw_task_entry,
    NULL
};

/* Item functions */
void
raw_item_start(char *title)
{
    printf("%s\t%s\t%s\n", "ITEM", "ROOM", "NOTE");
}

void
raw_item_entry(vhash *item)
{
    vhash *room = vh_pget(item, "ROOM");
    char *idesc = vh_sgetref(item, "DESC");
    char *rdesc = (room == NULL ? "" : vh_sgetref(room, "DESC"));
    char *note = vh_sgetref(item, "NOTE");

    printf("%s\t%s\t%s\n",
           idesc,
           (rdesc == NULL ? "" : rdesc),
           (note == NULL ? "" : note));
}

/* Task functions */
void
raw_task_start(char *title)
{
    printf("%s\t%s\t%s\t%s\t%s\n",
           "ROOM", "TASK", "NOTE", "SCORE", "INV");
}

void
raw_task_entry(vhash *task)
{
    vhash *room = vh_pget(task, "ROOM");
    int score = vh_iget(task, "SCORE");
    vlist *inv = vh_pget(task, "INVENT");
    char *note = vh_sgetref(task, "NOTE");
    static vhash *last = NULL;
    vlist *carried = vl_create();
    vscalar *elt;

    vl_foreach(elt, inv)
        vl_spush(carried, vh_sgetref(vs_pget(elt), "DESC"));

    printf("%s\t%s\t%s\t%s\t%s\n",
           (room == last || room == NULL ? "" : vh_sgetref(room, "DESC")),
           vh_sgetref(task, "DESC"),
           (note == NULL ? "" : note),
           (score ? vh_sget(task, "SCORE") : ""),
           vl_join(carried, ", "));

    vl_destroy(carried);
    if (room != NULL)
        last = room;
}