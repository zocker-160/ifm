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
extern void setup_tasks(void);
extern void solve_game(void);

#endif
