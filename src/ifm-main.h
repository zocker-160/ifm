/* Main function header */

#ifndef IFM_MAIN_H
#define IFM_MAIN_H

/* Output types */
#define O_NONE  0x0             /* No output */
#define O_MAP   0x1             /* Map */
#define O_ITEMS 0x2             /* Item list */
#define O_TASKS 0x4             /* Task list */

/* External vars */
extern char *progname;
extern int line_number;
extern char ifm_input[];
extern vlist *ifm_search;
extern vlist *ifm_styles;
extern char *ifm_format;

/* Advertised functions */
extern int parse_input(char *file, int libflag, int required);
extern void yyerror(char *msg);
extern void err(char *fmt, ...);
extern void warn(char *fmt, ...);
extern void debug(char *fmt, ...);
extern void fatal(char *fmt, ...);

#endif
