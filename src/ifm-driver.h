/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Output drivers */

#ifndef DRIVER_H
#define DRIVER_H

#ifdef TEXT
#include "drv-text.c"
#endif

#ifdef GROFF
#include "drv-groff.c"
#endif

#define NUM_DRIVERS (sizeof(drivers) / sizeof(drivers[0]))

struct driver_st {
    char *name, *desc;
    mapfuncs  *mfunc;
    itemfuncs *ifunc;
    taskfuncs *tfunc;
} drivers[] = {
#ifdef TEXT
    {
        "text", "Tab-delimited ASCII text fields",
        NULL, &text_itemfuncs, &text_taskfuncs
    },
#endif

#ifdef GROFF
    {
        "groff", "Groff with pic, tbl and -me macros",
        &groff_mapfuncs, &groff_itemfuncs, &groff_taskfuncs
    },
#endif
};

#endif /* DRIVER_H */
