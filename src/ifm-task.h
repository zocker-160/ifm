/* Task function header */

#ifndef IFM_TASK_H
#define IFM_TASK_H

/* Task types */
enum {
    T_MOVE, T_GET, T_DROP, T_GOTO, T_USER
};

/* Advertised functions */
extern void check_cycles(void);
extern vhash *require_task(vhash *step);
extern void setup_tasks(void);
extern void solve_game(void);
extern vgraph *task_graph(void);

#endif
