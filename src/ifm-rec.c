/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Recording output driver */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <vars.h>
#include "ifm-driver.h"
#include "ifm-map.h"
#include "ifm-util.h"
#include "ifm-rec.h"

/* Task function list */
taskfuncs rec_taskfuncs = {
    NULL,
    rec_task_entry,
    NULL
};

/* Task functions */
void
rec_task_entry(vhash *task)
{
    char *cmd;

    cmd = vh_sgetref(task, "DESC");
    if (vh_exists(task, "CMD"))
        cmd = vh_sgetref(task, "CMD");

    while (*cmd != '\0')
        putchar(toupper(*cmd++));

    putchar('\n');
}
