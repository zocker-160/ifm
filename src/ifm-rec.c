/* Recording output driver */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <vars.h>

#include "ifm-driver.h"
#include "ifm-map.h"
#include "ifm-util.h"
#include "ifm-vars.h"
#include "ifm-rec.h"

/* Task function list */
taskfuncs rec_taskfuncs = {
    NULL,
    rec_task_entry,
    NULL
};

/* Internal functions */
static void putline(char *str);

/* Task functions */
void
rec_task_entry(vhash *task)
{
    vscalar *elt;
    vlist *cmds;

    if ((cmds = vh_pget(task, "CMD")) != NULL) {
        vl_foreach(elt, cmds)
            putline(vs_sgetref(elt));
    } else {
        putline(vh_sgetref(task, "DESC"));
    }
}

static void
putline(char *str)
{
    str = var_subst(str);
    while (*str != '\0')
        putchar(toupper(*str++));
    putchar('\n');
}
