/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Raw output driver header */

#ifndef IFM_RAW_H
#define IFM_RAW_H

extern itemfuncs raw_itemfuncs;
extern taskfuncs raw_taskfuncs;

extern void raw_item_start(void);
extern void raw_item_entry(vhash *item);
extern void raw_task_start(void);
extern void raw_task_entry(vhash *task);

#endif
