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
    int i, output = O_NONE, format = -1;
    extern void yyparse();
    vscalar *fmt;
    vhash *opts;
    vlist *args;
    char *file;

#ifdef DEBUG
    extern int yydebug;
    v_debug(V_DBG_PTRS);
#endif

    /* Set program name */
    progname = argv[0];

    /* Define options */
    v_option('m', "map", V_OPT_FLAG, NULL,
             "Print map");

    v_option('i', "items", V_OPT_FLAG, NULL,
             "Print item table");

    v_option('t', "tasks", V_OPT_FLAG, NULL,
             "Print task table");

    v_option('f', "format", V_OPT_ARG, "fmt",
             "Select output format");

    v_option('o', "output", V_OPT_ARG, "file",
             "Write output to file");

    v_option('v', "verbose", V_OPT_FLAG, NULL,
             "Be verbose about things");

    v_option('h', "help", V_OPT_FLAG, NULL,
             "This help message");

#ifdef DEBUG
    v_option('D', "debug", V_OPT_ARG, "flag", NULL);
#endif

    /* Parse command-line arguments */
    if ((opts = vh_getopt(argc, argv)) == NULL)
        v_die("Type `%s -help' for help", progname);

    if (vh_exists(opts, "help"))
        usage();

    if (vh_exists(opts, "map"))
        output |= O_MAP;

    if (vh_exists(opts, "items"))
        output |= O_ITEMS;

    if (vh_exists(opts, "tasks"))
        output |= O_TASKS;

    if (vh_exists(opts, "format"))
        format = select_format(vh_sgetref(opts, "format"));

    if (vh_exists(opts, "verbose"))
        verbose_flag = 1;

    if ((file = vh_sgetref(opts, "output")) != NULL)
        if (freopen(file, "w", stdout) == NULL)
            fatal("can't open %s", file);

#ifdef DEBUG
    switch (vh_iget(opts, "debug")) {
    case 1:
        ifm_debug = 1;
        break;
    case 2:
        yydebug = 1;
        break;
    }
#endif

    /* Last argument (if any) is input file */
    args = vh_pget(opts, "ARGS");
    file = vl_sshift(args);
    if (file != NULL && freopen(file, "r", stdin) == NULL)
	fatal("can't open %s", file);

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
    if (output == O_NONE || output & O_TASKS) {
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
        if ((fmt = get_var("output")) != NULL)
            format = select_format(vs_sget(fmt));
        else
            format = default_format(output);
    }

    ifm_format = drivers[format].name;

    /* Do what's required */
    if (output == O_NONE)
        printf("Syntax appears OK\n");

    if (output & O_MAP)
        draw_map(format);

    if (output & O_ITEMS)
        draw_items(format);

    if (output & O_TASKS)
        draw_tasks(format);

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

    ifm_output = "map";
    mapnum = 0;

    sects = vh_pget(map, "SECTS");
    if (vl_length(sects) == 0)
        fatal("no rooms found in input");

    if (func == NULL)
        fatal("no map driver for %s", drv.name);

    if (func->map_start != NULL)
        (*func->map_start)();

    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        mapnum++;

        if (func->map_section != NULL)
            (*func->map_section)(sect);

        if (func->map_link != NULL) {
            linklist = vh_pget(sect, "LINKS");
            vl_foreach(elt, linklist) {
                link = vs_pget(elt);
                (*func->map_link)(link);
            }
        }

        if (func->map_room != NULL) {
            roomlist = vh_pget(sect, "ROOMS");
            vl_foreach(elt, roomlist) {
                room = vs_pget(elt);
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

    ifm_output = "item";

    items = vh_pget(map, "ITEMS");

    if (func == NULL)
        fatal("no item table driver for %s", drv.name);

    sorted = vl_sort(items, itemsort);

    if (func->item_start != NULL)
        (*func->item_start)(vh_sgetref(map, "TITLE"));

    vl_foreach(elt, sorted) {
        item = vs_pget(elt);
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

    ifm_output = "task";

    tasks = vh_pget(map, "TASKS");

    if (func == NULL)
        fatal("no task table driver for %s", drv.name);

    if (func->task_start != NULL)
        (*func->task_start)(vh_sgetref(map, "TITLE"));

    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
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
    vhash *i1 = vs_pget(*ip1);
    vhash *i2 = vs_pget(*ip2);
    vhash *ir1, *ir2;
    int cmp;

    /* First, by item name */
    cmp = strcmp(vh_sgetref(i1, "DESC"), vh_sgetref(i2, "DESC"));
    if (cmp) return cmp;

    /* Next, by room name */
    ir1 = vh_pget(i1, "ROOM");
    ir2 = vh_pget(i2, "ROOM");
    cmp = strcmp((ir1 == NULL ? "" : vh_sgetref(ir1, "DESC")),
                 (ir2 == NULL ? "" : vh_sgetref(ir2, "DESC")));
    if (cmp) return cmp;

    /* Finally, by note */
    return strcmp(vh_sgetref(i1, "NOTE"), vh_sgetref(i2, "NOTE"));
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
        if (output & O_MAP)
            if (drivers[i].mfunc != NULL)
                return i;
        if (output & O_ITEMS)
            if (drivers[i].ifunc != NULL)
                return i;
        if (output & O_TASKS)
            if (drivers[i].tfunc != NULL)
                return i;
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
    int i;

    v_usage("Usage: %s [options] [file]", progname);
    printf("\nOutput formats (may be abbreviated):\n");
    for (i = 0; i < NUM_DRIVERS; i++)
        printf("    %-15s    %s\n", drivers[i].name, drivers[i].desc);

    exit(0);
}
