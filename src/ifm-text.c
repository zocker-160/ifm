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
    text_item_start,
    text_item_entry,
    NULL
};

/* Task function list */
taskfuncs text_taskfuncs = {
    text_task_start,
    text_task_entry,
    NULL
};

/* Item functions */
void
text_item_start(void)
{
    char *title;

    title = get_string("title", NULL);
    printf("Item list for %s\n",
           title != NULL ? title : "Interactive Fiction game");
}

void
text_item_entry(vhash *item)
{
    vhash *room = vh_pget(item, "ROOM");

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
text_task_start(void)
{
    char *title;

    title = get_string("title", NULL);
    printf("High-level walkthrough for %s\n",
           title != NULL ? title : "Interactive Fiction game");
}

void
text_task_entry(vhash *task)
{
    vhash *room = vh_pget(task, "ROOM");
    int score = vh_iget(task, "SCORE");
    char *note = vh_sgetref(task, "NOTE");
    static vhash *last = NULL;
    vscalar *elt;

    if (room != last && room != NULL)
        printf("\n%s:\n", vh_sgetref(room, "DESC"));
    else if (last == NULL)
        printf("\nFirstly:\n");

    printf("   %s\n", vh_sgetref(task, "DESC"));

    if (score > 0)
        printf("      score %d for doing this\n", score);

    if (note != NULL && !STREQ(note, ""))
        printf("      note: %s\n", note);

    if (room != NULL)
        last = room;
}
