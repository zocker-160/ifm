/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Main functions */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "ifm.h"
#include "ifm-parse.h"
#include "ifm-driver.h"

/* Max. errors before aborting */
#define MAX_ERRORS 10

/* Varargs printing */
#define VPRINT(buf, fmt)	{ \
				      va_list ap; \
				      va_start(ap, fmt); \
				      vsprintf(buf, fmt, ap); \
				      va_end(ap); \
			        }

/* What's my name? */
char *progname;

/* Am I being verbose? */
static int verbose_flag;

/* Output required */
static int ifm_output = O_MAP;

/* Output format */
static int ifm_format = 0;

/* Current line number */
int line_number = 1;

/* No. of errors */
int ifm_errors = 0;

/* Scribble buffer */
static char buf[BUFSIZ];

/* Debugging flag */
int ifm_debug = 0;

/* Local functions */
static void parse_args(int argc, char *argv[]);
static void print_usage(void);

/* Main routine */
int
main(int argc, char *argv[])
{
    extern void yyparse();
    char *cp;

    /* Set program name */
    progname = argv[0];
    if ((cp = strrchr(progname, '/')) != NULL)
        progname = cp + 1;

    /* Parse command-line arguments */
    parse_args(argc, argv);

    /* Initialise */
    status("Running %s", progname);
    init_map();

    /* Parse input */
    status("Parsing input...");
    yyparse();
    if (ifm_errors > 0)
        return 1;

    /* Resolve tags */
    status("Resolving tags...");
    resolve_tags();
    if (ifm_errors > 0)
        return 1;

    /* Position rooms */
    status("Positioning rooms...");
    position_rooms();

    /* Set up links */
    status("Setting up room links...");
    setup_links();
    if (ifm_errors > 0)
        return 1;

    /* Set up sections */
    status("Setting up sections...");
    setup_sections();

    /* Do task setup if required */
    if (ifm_output == O_TASKS) {
        /* Connect rooms */
        status("Connecting rooms...");
        connect_rooms();

        /* Create task list */
        status("Creating tasks...");
        build_tasks();
        order_tasks();
    }

    /* Do what's required */
    switch (ifm_output) {
    case O_MAP:
        draw_map(ifm_format);
        break;
    case O_ITEMS:
        draw_items(ifm_format);
        break;
    case O_TASKS:
        draw_tasks(ifm_format);
        break;
    }

    /* Er... that's it */
    return 0;
}

/* Draw the map */
void
draw_map(int fmt)
{
    struct driver_st drv = drivers[fmt];
    mapfuncs *func = drv.mfunc;
    vlist *sects, *roomlist, *linklist;
    vhash *sect, *room, *link;
    vscalar *elt;

    if (func == NULL)
        fatal("no map driver for %s", drv.name);

    if (func->map_start != NULL)
        (*func->map_start)(vh_sget(map, "TITLE"));

    sects = vh_pget(map, "SECTS");
    FOREACH(elt, sects) {
        sect = vs_pval(elt);

        if (func->map_section != NULL)
            (*func->map_section)(sect);

        if (func->map_link != NULL) {
            linklist = vh_pget(sect, "LINKS");
            FOREACH(elt, linklist) {
                link = vs_pval(elt);
                (*func->map_link)(link);
            }
        }

        if (func->map_room != NULL) {
            roomlist = vh_pget(sect, "ROOMS");
            FOREACH(elt, roomlist) {
                room = vs_pval(elt);
                (*func->map_room)(room);
            }
        }

        if (func->map_endsection != NULL)
            (*func->map_endsection)();
    }

    if (func->map_finish != NULL)
        (*func->map_finish)();
}

/* Draw items table */
void
draw_items(int fmt)
{
    struct driver_st drv = drivers[fmt];
    itemfuncs *func = drv.ifunc;
    vscalar *elt;
    vlist *items;
    vhash *item;

    if (func == NULL)
        fatal("no item driver for %s", drv.name);

    if (func->item_start != NULL)
        (*func->item_start)(vh_sget(map, "TITLE"));

    items= vh_pget(map, "ITEMS");
    FOREACH(elt, items) {
        item = vs_pval(elt);
        if (func->item_entry != NULL)
            (*func->item_entry)(item);
    }

    if (func->item_finish != NULL)
        (*func->item_finish)();
}

/* Draw task table */
void
draw_tasks(int fmt)
{
    struct driver_st drv = drivers[fmt];
    taskfuncs *func = drv.tfunc;
    vscalar *elt;
    vlist *tasks;
    vhash *task;

    if (func == NULL)
        fatal("no task driver for %s", drv.name);

    if (func->task_start != NULL)
        (*func->task_start)(vh_sget(map, "TITLE"));

    tasks= vh_pget(map, "TASKS");
    FOREACH(elt, tasks) {
        task = vs_pval(elt);
        if (func->task_entry != NULL)
            (*func->task_entry)(task);
    }

    if (func->task_finish != NULL)
        (*func->task_finish)();
}

/* Parse arguments */
static void
parse_args(int argc, char *argv[])
{
    extern int optind, opterr;
    extern char *optarg;
    int c;

#ifdef DEBUG
    extern int yydebug;
    int dflag;
#endif

    opterr = 0;
    optind = 1;
    while ((c = getopt(argc, argv, "himo:tvD:")) != EOF) {
	switch (c) {
        case 'm':
            ifm_output = O_MAP;
            break;
        case 'i':
            ifm_output = O_ITEMS;
            break;
        case 't':
            ifm_output = O_TASKS;
            break;
        case 'f':
            ifm_format = select_format(optarg);
            break;
	case 'v':
	    verbose_flag = 1;
	    break;
	case 'o':
	    if (freopen(optarg, "w", stdout) == NULL)
		fatal("can't open %s", optarg);
	    break;
	case 'h':
            print_usage();
	    exit(0);
	case 'D':
#ifdef DEBUG
            dflag = atoi(optarg);
            if (dflag == 1)
                ifm_debug = 1;
            else
                yydebug = 1;
	    break;
#else
            fatal("no compiled-in debugging support");
#endif
        default:
	    fatal("invalid argument\nType `%s -h' for help", progname);
            break;
	}
    }

    /* Last argument (if any) is input file */
    if (optind < argc && freopen(argv[optind], "r", stdin) == NULL)
	fatal("can't open %s", argv[optind]);
}

/* Select an output format */
int
select_format(char *str)
{
    int nd = sizeof(drivers) / sizeof(drivers[0]);
    int i, match, nmatch = 0, len = strlen(str);

    for (i = 0; i < nd; i++) {
        if (!strcmp(drivers[i].name, str))
            return i;
        if (!strncmp(drivers[i].name, str, len)) {
            nmatch++;
            match = i;
        }
    }

    if (nmatch == 0)
        fatal("unknown output format: %s", str);
    else if (nmatch > 1)
        fatal("ambiguous output format: %s", str);

    return match;
}

/* Print a usage message */
static void
print_usage()
{
    int nd = sizeof(drivers) / sizeof(drivers[0]);
    int i;

    static char *fmt = "  %-15s %s\n";

    fprintf(stderr, "Usage: %s [options] [file]\n", progname);

    fprintf(stderr, fmt, "-m",         "draw map (default)");
    fprintf(stderr, fmt, "-i",         "print item table");
    fprintf(stderr, fmt, "-t",         "print task table");
    fprintf(stderr, fmt, "-f format",  "select output format");
    fprintf(stderr, fmt, "-o file",    "write output to file");
    fprintf(stderr, fmt, "-v",         "be verbose about things");
    fprintf(stderr, fmt, "-h",         "this usage message");

    fprintf(stderr, "\nOutput formats (may be abbreviated):\n");

    for (i = 0; i < nd; i++)
        fprintf(stderr, fmt, drivers[i].name, drivers[i].desc);
}

/* Parser-called parse error */
void
yyerror(char *msg)
{
    /* Write error message */
    fprintf(stderr, "%s: error: line %d: %s\n", progname, line_number,
	    (!strcmp(msg, "parse error") ? "syntax error" : msg));

    /* Increment errors and abort if necessary */
    if (++ifm_errors >= MAX_ERRORS)
	fatal("too many errors.  Goodbye!");
}

/* Write status message (only if verbose) */
void
status(char *fmt, ...)
{
    if (verbose_flag) {
	VPRINT(buf, fmt);
	fprintf(stderr, "%s\n", buf);
    }
}

/* Give a debugging message */
void
debug(char *fmt, ...)
{
    if (ifm_debug) {
        VPRINT(buf, fmt);
        fprintf(stderr, "%s\n", buf);
    }
}

/* Give a parse error */
void
err(char *fmt, ...)
{
    VPRINT(buf, fmt);
    yyerror(buf);
}

/* Give a parse warning */
void
warn(char *fmt, ...)
{
    VPRINT(buf, fmt);
    fprintf(stderr, "%s: warning: line %d: %s\n",
	    progname, line_number, buf);
}

/* Give a non-line-specific error */
void
error(char *fmt, ...)
{
    VPRINT(buf, fmt);
    fprintf(stderr, "%s: error: %s\n", progname, buf);

    /* Increment errors and abort if necessary */
    if (++ifm_errors >= MAX_ERRORS)
	fatal("too many errors.  Goodbye!");
}

/* Give a non-line-specific warning */
void
warning(char *fmt, ...)
{
    VPRINT(buf, fmt);
    fprintf(stderr, "%s: warning: %s\n", progname, buf);
}

/* Give a *fatal* error */
void
fatal(char *fmt, ...)
{
    VPRINT(buf, fmt);
    fprintf(stderr, "%s: error: %s\n", progname, buf);
    exit(1);
}
