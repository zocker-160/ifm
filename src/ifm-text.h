/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Text output driver header */

#ifndef IFM_TEXT_H
#define IFM_TEXT_H

extern itemfuncs text_itemfuncs;
extern taskfuncs text_taskfuncs;

extern void text_item_entry(vhash *item);
extern void text_task_entry(vhash *task);
extern void text_task_finish(void);

#endif
