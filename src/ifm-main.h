/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
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

/* Debugging stuff */
#define DEBUG0(level, msg) \
        if (ifm_debug) { \
                indent(level); \
                printf(msg); \
                putchar('\n'); \
        }

#define DEBUG1(level, msg, arg1) \
        if (ifm_debug) { \
                indent(level); \
                printf(msg, arg1); \
                putchar('\n'); \
        }

#define DEBUG2(level, msg, arg1, arg2) \
        if (ifm_debug) { \
                indent(level); \
                printf(msg, arg1, arg2); \
                putchar('\n'); \
        }

/* External vars */
extern char *progname;
extern int line_number;
extern int ifm_debug;
extern char ifm_input[];
extern vlist *ifm_search;
extern char *ifm_format, *ifm_output;

/* Advertised functions */
extern void yyerror(char *msg);
extern void debug(char *fmt, ...);
extern void err(char *fmt, ...);
extern void warn(char *fmt, ...);
extern void fatal(char *fmt, ...);

#endif
