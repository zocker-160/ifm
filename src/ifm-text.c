/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Text output driver */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "ifm.h"
#include "ifm-parse.h"
#include "ifm-text.h"

/* Item function list */
itemfuncs text_itemfuncs = {
    NULL,
    text_item_entry,
    NULL
};

/* Task function list */
taskfuncs text_taskfuncs = {
    NULL,
    text_task_entry,
    text_task_finish,
};

/* Total score */
static int total = 0;

/* Item functions */
void
text_item_entry(vhash *item)
{
    vhash *room = vh_pget(item, "ROOM");
    static int count = 0;

    if (count++ == 0) {
        char *title = get_string("title", NULL);
        printf("Item list for %s\n",
               title != NULL ? title : "Interactive Fiction game");
    }

    printf("\n%s:\n", vh_sgetref(item, "DESC"));
    if (room == NULL) {
        printf("   carried at the start of the game\n");
    } else {
        printf("   found in %s\n", vh_sgetref(room, "DESC"));
        if (vh_iget(item, "HIDDEN"))
            printf("   not immediately obvious\n");
    }

    if (vh_exists(item, "SCORE"))
        printf("   scores %d points when picked up\n",
               vh_iget(item, "SCORE"));

    if (vh_exists(item, "NOTE"))
        printf("   note: %s\n", vh_sgetref(item, "NOTE"));
}

/* Task functions */
void
text_task_entry(vhash *task)
{
    vhash *room = vh_pget(task, "ROOM");
    static vhash *lastroom = NULL;
    static vhash *lastitem = NULL;
    int dist, type, score;
    static int count = 0;
    static int flag = 0;
    char *note = NULL;
    vscalar *elt;

    if (count++ == 0) {
        char *title = get_string("title", NULL);
        printf("High-level walkthrough for %s\n",
               title != NULL ? title : "Interactive Fiction game");
    }

    if (room != lastroom && room != NULL) {
        printf("\n%s", vh_sgetref(room, "DESC"));
        if ((dist = vh_iget(task, "DIST")) > 0)
            printf(" (%d room%s away)", dist, dist > 1 ? "s" : "");
        printf(":\n");
    } else if (lastroom == NULL && flag++ == 0) {
        printf("\nFirstly:\n");
    }

    printf("   %s\n", vh_sgetref(task, "DESC"));

    if ((score = vh_iget(task, "SCORE")) > 0)
        printf("      score: %d\n", score);

    type = vh_iget(task, "TYPE");
    switch (type) {
    case T_GET:
        lastitem = vh_pget(task, "DATA");
        note = vh_sgetref(lastitem, "NOTE");
        break;
    case T_DROP:
        if (lastroom == NULL || vh_pget(task, "DATA") == lastitem)
            note = "this item isn't used yet";
        break;
    case T_USER:
        lastitem = NULL;
        note = vh_sgetref(task, "NOTE");
        break;
    } 

    if (note != NULL && !STREQ(note, ""))
        printf("      note: %s\n", note);

    if (room != NULL)
        lastroom = room;
    total += score;
}

void
text_task_finish(void)
{
    if (total > 0)
        printf("\nTotal score: %d\n", total);
}
