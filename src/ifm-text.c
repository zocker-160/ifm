/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Text output driver */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <vars.h>

#include "ifm-driver.h"
#include "ifm-map.h"
#include "ifm-task.h"
#include "ifm-util.h"

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

/* Total distance travelled */
static int travel = 0;

/* Item functions */
void
text_item_entry(vhash *item)
{
    vlist *notes = vh_pget(item, "NOTE");
    vhash *room = vh_pget(item, "ROOM");
    static int count = 0;
    vscalar *elt;

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

    if (notes != NULL) {
        vl_foreach(elt, notes)
            printf("   note: %s\n", vs_sgetref(elt));
    }
}

/* Task functions */
void
text_task_entry(vhash *task)
{
    vlist *notes = vh_pget(task, "NOTE");
    vhash *room = vh_pget(task, "ROOM");
    vlist *cmds = vh_pget(task, "CMD");
    static vhash *lastroom = NULL;
    static int moved = 0;
    static int count = 0;
    int type, score;
    vscalar *elt;

    if (count == 0) {
        char *title = get_string("title", NULL);
        printf("High-level walkthrough for %s\n",
               title != NULL ? title : "Interactive Fiction game");
    }

    type = vh_iget(task, "TYPE");

    if (type == T_MOVE) {
        if (count == 0)
            printf("\nStart: %s\n", vh_sgetref(startroom, "DESC"));
        if (!moved)
            printf("\n");
        printf("%s", vh_sgetref(task, "DESC"));
        if (cmds != NULL)
            printf(" (%s)", vl_join(cmds, ". "));
        printf("\n");

        travel++;
        moved++;
    } else {
        if (room != NULL && (moved || room != lastroom))
            printf("\n%s:\n", vh_sgetref(room, "DESC"));
        else if (!count)
            printf("\nFirstly:\n");

        printf("   %s\n", vh_sgetref(task, "DESC"));

        if (cmds != NULL) {
            vl_foreach(elt, cmds)
                printf("      cmd: %s\n", vs_sgetref(elt));
        }

        moved = 0;
    }

    if ((score = vh_iget(task, "SCORE")) > 0) {
        if (type != T_MOVE)
            printf("   ");
        printf("   score: %d\n", score);
    }

    if (notes != NULL) {
        vl_foreach(elt, notes) {
            if (type != T_MOVE)
                printf("   ");
            printf("   note: %s\n", vs_sgetref(elt));
        }
    }

    if (room != NULL)
        lastroom = room;
    total += score;
    count++;
}

void
text_task_finish(void)
{
    if (travel > 0)
        printf("\nTotal distance travelled: %d\n", travel);
    if (total > 0)
        printf("\nTotal score: %d\n", total);
}
