/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Task function header */

#ifndef IFM_TASK_H
#define IFM_TASK_H

/* Task types */
enum {
    T_MOVE, T_GET, T_DROP, T_GOTO, T_USER
};

/* Advertised functions */
extern void add_task(void);
extern void add_task_list(char *tag);
extern void set_task_after(void);
extern void set_task_attr(char *attr, char *val);
extern void set_task_items(char *attr);
extern void set_task_tag(char *str);
extern void setup_tasks(void);
extern void solve_game(void);

#endif
