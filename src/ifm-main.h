/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Main function header */

#ifndef IFM_MAIN_H
#define IFM_MAIN_H

/* Output types */
#define O_NONE  0x0             /* No output */
#define O_MAP   0x1             /* Map */
#define O_ITEMS 0x2             /* Item list */
#define O_TASKS 0x4             /* Task list */

/* Various useful macros */
#define STREQ(s1, s2)           !strcmp(s1, s2)
#define ABS(x)                  ((x) > 0 ? (x) : -(x))
#define MIN(x, y)               ((x) < (y) ? (x) : (y))
#define MAX(x, y)               ((x) > (y) ? (x) : (y))

/* Driver structs */
typedef struct mapfuncs_st {
    void (*map_start)(void);
    void (*map_section)(vhash *sect);
    void (*map_room)(vhash *room);
    void (*map_link)(vhash *link);
    void (*map_endsection)(void);
    void (*map_finish)(void);
} mapfuncs;

typedef struct itemfuncs_st {
    void (*item_start)(char *title);
    void (*item_entry)(vhash *item);
    void (*item_finish)(void);
} itemfuncs;

typedef struct taskfuncs_st {
    void (*task_start)(char *title);
    void (*task_entry)(vhash *task);
    void (*task_finish)(void);
} taskfuncs;

/* External vars */
extern char *progname;
extern int line_number, ifm_errors, ifm_debug;
extern char *ifm_format, *ifm_output;

/* Advertised functions */
extern void yyerror(char *msg);
extern void status(char *fmt, ...);
extern void debug(char *fmt, ...);
extern void err(char *fmt, ...);
extern void warn(char *fmt, ...);
extern void error(char *fmt, ...);
extern void warning(char *fmt, ...);
extern void fatal(char *fmt, ...);

#endif
