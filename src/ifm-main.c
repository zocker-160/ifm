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

/* Current line number */
int line_number = 1;

/* No. of errors */
int ifm_errors = 0;

/* Scribble buffer */
static char buf[BUFSIZ];

/* Output format */
char *ifm_format = NULL;

/* Type of output */
char *ifm_output = NULL;

/* Debugging flag */
int ifm_debug = 0;

/* Local functions */
static void draw_map(int fmt);
static void draw_items(int fmt);
static void draw_tasks(int fmt);
static int itemsort(vscalar **ip1, vscalar **ip2);
static int select_format(char *str);
static int default_format(int output);
static void usage(void);

/* Main routine */
int
main(int argc, char *argv[])
{
    int c, i, output = O_NONE, format = -1, print = 0;
    extern void yyparse();
    extern char *optarg;
    extern int opterr;
    vhash *symtab;
    vscalar *fmt;

#ifdef DEBUG
    extern int yydebug;
    int dflag;
#endif

    /* Set program name */
    progname = argv[0];

    /* Parse command-line arguments */
    opterr = 0;
    while ((c = getopt(argc, argv, "f:himo:ptvD:")) != EOF) {
	switch (c) {
        case 'm':
            output = O_MAP;
            break;
        case 'i':
            output = O_ITEMS;
            break;
        case 't':
            output = O_TASKS;
            break;
        case 'f':
            format = select_format(optarg);
            break;
        case 'p':
            print = 1;
            break;
	case 'v':
	    verbose_flag = 1;
	    break;
	case 'o':
	    if (freopen(optarg, "w", stdout) == NULL)
		fatal("can't open %s", optarg);
	    break;
	case 'h':
            usage();
            break;
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
	    fatal("invalid option\nType `%s -h' for help", progname);
            break;
	}
    }

    /* Last argument (if any) is input file */
    if (optind < argc && freopen(argv[optind], "r", stdin) == NULL)
	fatal("can't open %s", argv[optind]);

    /* Initialise */
    status("Running %s", progname);
    init_map();

    /* Set up symbol tables */
    symtab = vh_create();
    vh_pstore(vars, "default", symtab);
    vh_pstore(symtab, "global", vh_create());
    vh_pstore(symtab, "map", vh_create());
    vh_pstore(symtab, "item", vh_create());
    vh_pstore(symtab, "task", vh_create());

    for (i = 0; i < NUM_DRIVERS; i++) {
        symtab = vh_create();
        vh_pstore(vars, drivers[i].name, symtab);
        vh_pstore(symtab, "global", vh_create());
        vh_pstore(symtab, "map", vh_create());
        vh_pstore(symtab, "item", vh_create());
        vh_pstore(symtab, "task", vh_create());
    }

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
    if (output == O_NONE || output == O_TASKS) {
        /* Connect rooms */
        status("Connecting rooms...");
        connect_rooms();

        /* Create task list */
        status("Creating tasks...");
        build_tasks();
        order_tasks();
    }

    /* Set output format if not already specified */
    if (output != O_NONE && format < 0) {
        switch (output) {
        case O_MAP:
            ifm_output = "map";
            break;
        case O_ITEMS:
            ifm_output = "item";
            break;
        case O_TASKS:
            ifm_output = "task";
            break;
        }

        if ((fmt = get_var("output")) != NULL)
            format = select_format(vs_sval(fmt));
        else
            format = default_format(output);
    }

    ifm_format = drivers[format].name;

    /* Do what's required */

    switch (output) {
    case O_NONE:
        printf("Syntax appears OK\n");
        break;
    case O_MAP:
        draw_map(format);
        break;
    case O_ITEMS:
        draw_items(format);
        break;
    case O_TASKS:
        draw_tasks(format);
        break;
    }

    if (print)
        print_vars();

    /* Er... that's it */
    return 0;
}

/* Draw the map */
static void
draw_map(int fmt)
{
    struct driver_st drv = drivers[fmt];
    mapfuncs *func = drv.mfunc;
    vlist *sects, *roomlist, *linklist;
    vhash *sect, *room, *link;
    vscalar *elt;

    sects = vh_pget(map, "SECTS");
    if (vl_length(sects) == 0)
        fatal("no rooms found in input");

    if (func == NULL)
        fatal("no map driver for %s", drv.name);

    if (func->map_start != NULL)
        (*func->map_start)();

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
static void
draw_items(int fmt)
{
    struct driver_st drv = drivers[fmt];
    itemfuncs *func = drv.ifunc;
    vlist *items, *sorted;
    vscalar *elt;
    vhash *item;

    items = vh_pget(map, "ITEMS");
    if (vl_length(items) == 0)
        fatal("no items found in input");

    if (func == NULL)
        fatal("no item table driver for %s", drv.name);

    sorted = vl_sort(items, itemsort);

    if (func->item_start != NULL)
        (*func->item_start)(vh_sget(map, "TITLE"));

    FOREACH(elt, sorted) {
        item = vs_pval(elt);
        if (func->item_entry != NULL)
            (*func->item_entry)(item);
    }

    if (func->item_finish != NULL)
        (*func->item_finish)();

    vl_destroy(sorted);
}

/* Draw task table */
static void
draw_tasks(int fmt)
{
    struct driver_st drv = drivers[fmt];
    taskfuncs *func = drv.tfunc;
    vscalar *elt;
    vlist *tasks;
    vhash *task;

    tasks = vh_pget(map, "TASKS");
    if (vl_length(tasks) == 0)
        fatal("no tasks found in input");

    if (func == NULL)
        fatal("no task table driver for %s", drv.name);

    if (func->task_start != NULL)
        (*func->task_start)(vh_sget(map, "TITLE"));

    FOREACH(elt, tasks) {
        task = vs_pval(elt);
        if (func->task_entry != NULL)
            (*func->task_entry)(task);
    }

    if (func->task_finish != NULL)
        (*func->task_finish)();
}

/* Item sort function */
static int
itemsort(vscalar **ip1, vscalar **ip2)
{
    vhash *i1 = vs_pval(*ip1);
    vhash *i2 = vs_pval(*ip2);
    vhash *ir1, *ir2;
    int cmp;

    /* First, by item name */
    cmp = strcmp(vh_sget(i1, "DESC"), vh_sget(i2, "DESC"));
    if (cmp) return cmp;

    /* Next, by room name */
    ir1 = vh_pget(i1, "ROOM");
    ir2 = vh_pget(i2, "ROOM");
    cmp = strcmp((ir1 == NULL ? "" : vh_sget(ir1, "DESC")),
                 (ir2 == NULL ? "" : vh_sget(ir2, "DESC")));
    if (cmp) return cmp;

    /* Finally, by note */
    return strcmp(vh_sget(i1, "NOTE"), vh_sget(i2, "NOTE"));
}

/* Select an output format */
static int
select_format(char *str)
{
    int i, match, nmatch = 0, len = strlen(str);

    for (i = 0; i < NUM_DRIVERS; i++) {
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

/* Return default output format */
static int
default_format(int output)
{
    int i;

    for (i = 0; i < NUM_DRIVERS; i++) {
        switch (output) {
        case O_MAP:
            if (drivers[i].mfunc != NULL)
                return i;
            break;
        case O_ITEMS:
            if (drivers[i].ifunc != NULL)
                return i;
            break;
        case O_TASKS:
            if (drivers[i].tfunc != NULL)
                return i;
            break;
        }
    }

    fatal("internal: no output format found");
    return -1;
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

/* Print a usage message and exit */
static void
usage()
{
    int nd = sizeof(drivers) / sizeof(drivers[0]);
    int i;

    static char *fmt = "  %-15s %s\n";

    fprintf(stderr, "Usage: %s [options] [file]\n", progname);

    fprintf(stderr, "\nOptions:\n");

    fprintf(stderr, fmt, "-m",         "draw map");
    fprintf(stderr, fmt, "-i",         "print item table");
    fprintf(stderr, fmt, "-t",         "print task table");
    fprintf(stderr, fmt, "-f format",  "select output format");
    fprintf(stderr, fmt, "-o file",    "write output to file");
    fprintf(stderr, fmt, "-p",         "print parameters"); 
    fprintf(stderr, fmt, "-v",         "be verbose about things");
    fprintf(stderr, fmt, "-h",         "this usage message");

    fprintf(stderr, "\nOutput formats (may be abbreviated):\n");

    for (i = 0; i < nd; i++)
        fprintf(stderr, fmt, drivers[i].name, drivers[i].desc);

    exit(0);
}
