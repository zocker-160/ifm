/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Task function header */

#ifndef IFM_TASK_H
#define IFM_TASK_H

/* Task types */
#define T_GET   1               /* Internal get-item task */
#define T_DROP  2               /* Internal drop-item task */
#define T_GOTO  3               /* Internal goto-room task */
#define T_USER  4               /* User-defined task */

/* Advertised functions */
extern void add_task(void);
extern void add_task_list(char *tag);
extern void build_tasks(void);
extern void do_task(vhash *task, vhash *from, vhash *to);
extern void order_tasks(void);
extern void set_task_after(void);
extern void set_task_attr(char *attr, char *val);
extern void set_task_items(char *attr);
extern void set_task_tag(char *str);
extern void task_pair(vhash *before, vhash *after);
extern int task_priority(vhash *room, vhash *step);
extern vhash *task_step(int type, vhash *data);

#endif
