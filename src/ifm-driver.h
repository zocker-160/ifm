/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Output drivers */

#ifndef DRIVER_H
#define DRIVER_H

#ifndef CPROTO

/* List of drivers to include */
#define GROFF
#define TEXT

#ifdef GROFF
#include "groff.drv"
#endif

#ifdef TEXT
#include "text.drv"
#endif

#define NUM_DRIVERS (sizeof(drivers) / sizeof(drivers[0]))

struct driver_st {
    char *name, *desc;
    mapfuncs  *mfunc;
    itemfuncs *ifunc;
    taskfuncs *tfunc;
} drivers[] = {
#ifdef GROFF
    {
        "groff", "Groff with pic, tbl and -me macros",
        &groff_mapfuncs, &groff_itemfuncs, &groff_taskfuncs
    },
#endif

#ifdef TEXT
    {
        "text", "Tab-delimited ASCII text fields",
        NULL, &text_itemfuncs, &text_taskfuncs
    },
#endif
};

#endif /* !CPROTO */
#endif /* DRIVER_H */
