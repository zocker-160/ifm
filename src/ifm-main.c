/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
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

/* Output drivers */
#include "ifm-ps.h"
#include "ifm-text.h"
#include "ifm-groff.h"
#include "ifm-tk.h"
#include "ifm-raw.h"

static struct driver_st {
    char *name, *desc;
    mapfuncs  *mfunc;
    itemfuncs *ifunc;
    taskfuncs *tfunc;
    errfuncs  *efunc;
} drivers[] = {
#ifdef PS
    {
        "ps", "PostScript",
        &ps_mapfuncs, NULL, NULL, NULL
    },
#endif

#ifdef TEXT
    {
        "text", "Nicely-formatted ASCII text",
        NULL, &text_itemfuncs, &text_taskfuncs, NULL
    },
#endif

#ifdef GROFF
    {
        "groff", "Groff with pic, tbl and -me macros",
        &groff_mapfuncs, &groff_itemfuncs, &groff_taskfuncs, NULL
    },
#endif

#ifdef TK
    {
        "tk", "Tcl/Tk program commands",
        &tk_mapfuncs, &tk_itemfuncs, &tk_taskfuncs, &tk_errfuncs
    },
#endif

#ifdef RAW
    {
        "raw", "Tab-delimited ASCII text fields",
        NULL, &raw_itemfuncs, &raw_taskfuncs, NULL
    },
#endif
};

#define NUM_DRIVERS (sizeof(drivers) / sizeof(drivers[0]))

/* Init file */
#ifndef INITFILE
# ifdef _WIN32
#  define INITFILE "ifm.ini"
# else
#  define INITFILE ".ifmrc"
# endif
#endif

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

/* Current line number */
int line_number;

/* No. of errors */
int ifm_errors = 0;

/* Whether to print warnings */
int warning_flag = 1;

/* Scribble buffer */
static char buf[BUFSIZ];

/* Input filename */
static char *ifm_input = NULL;

/* Output format ID */
static int ifm_fmt = -1;

/* Output format name */
char *ifm_format = NULL;

/* Output type name */
char *ifm_output = NULL;

/* Verbose flag */
int ifm_verbose = 0;

/* Debugging flag */
int ifm_debug = 0;

/* Parse function */
extern void yyparse();

/* Local functions */
static void print_map(void);
static void print_items(void);
static void print_tasks(void);
static int itemsort(vscalar **ip1, vscalar **ip2);
static int parse_input(char *file, int required);
static void print_version(void);
static int select_format(char *str, int output);
static void usage(void);

/* Main routine */
int
main(int argc, char *argv[])
{
    int i, output = O_NONE, sysinit = 1, initfile = 1;
    vhash *opts;
    vlist *args;
    char *file;

#ifdef DEBUG
    extern int yydebug;
#endif

    v_debug_env();

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

    v_option('w', "nowarn", V_OPT_FLAG, NULL,
             "Don't print warnings");

    v_option('v', "verbose", V_OPT_FLAG, NULL,
             "Be very verbose about things");

    v_option('\0', "noinit", V_OPT_FLAG, NULL,
             "Don't read personal init file");

    v_option('\0', "nosysinit", V_OPT_FLAG, NULL,
             "Don't read system init file");

    v_option('V', "version", V_OPT_FLAG, NULL,
             "Print program version");

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

    if (vh_exists(opts, "version"))
        print_version();

    if (vh_exists(opts, "map"))
        output |= O_MAP;

    if (vh_exists(opts, "items"))
        output |= O_ITEMS;

    if (vh_exists(opts, "tasks"))
        output |= O_TASKS;

    if (vh_exists(opts, "format"))
        ifm_fmt = select_format(vh_sgetref(opts, "format"), 0);

    if (vh_exists(opts, "nowarn"))
        warning_flag = 0;

    if (vh_exists(opts, "noinit"))
        initfile = 0;

    if (vh_exists(opts, "nosysinit"))
        sysinit = 0;

    if (vh_exists(opts, "verbose"))
        ifm_verbose = 1;

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
    if (vl_length(args) > 0)
        file = vl_sshift(args);
    else
        file = NULL;

    /* Initialise */
    init_map();

    /* Parse system init file */
    if (sysinit && !parse_input(SYSINIT, 0))
        return 1;

    /* Parse personal init file if available */
    if (initfile && getenv("HOME") != NULL) {
        sprintf(buf, "%s/%s", getenv("HOME"), INITFILE);
        if (!parse_input(buf, 0))
            return 1;
    }

    /* Parse input */
    if (!parse_input(file, 1))
        return 1;

    /* Set output format if not already specified */
    if (output != O_NONE && ifm_fmt < 0) {
        vscalar *var = get_var("format");
        ifm_fmt = select_format(var != NULL ? vs_sget(var) : NULL, output);
    }

    ifm_format = drivers[ifm_fmt].name;

    /* Resolve tags */
    resolve_tags();

    if (ifm_errors > 0)
        return 1;

    /* Set up rooms */
    setup_rooms();

    /* Set up links */
    setup_links();

    if (ifm_errors > 0)
        return 1;

    /* Set up room exits */
    setup_exits();

    /* Set up sections */
    setup_sections();

    /* Do task setup if required */
    if (output == O_NONE || output & O_TASKS) {
        connect_rooms();
        setup_tasks();

        if (ifm_errors > 0)
            return 1;

        solve_game();
    }

    /* Do what's required */
    if (output == O_NONE)
        printf("Syntax appears OK\n");

    if (output & O_MAP)
        print_map();

    if (output & O_ITEMS)
        print_items();

    if (output & O_TASKS)
        print_tasks();

    /* Er... that's it */
    return 0;
}

/* Print the map */
static void
print_map(void)
{
    struct driver_st drv = drivers[ifm_fmt];
    mapfuncs *func = drv.mfunc;
    vlist *sects, *roomlist, *linklist;
    vhash *sect, *room, *link;
    vscalar *elt;

    ifm_output = "map";
    mapnum = 0;

    if (func == NULL)
        fatal("no map driver for %s output", drv.name);

    if (func->map_start != NULL)
        (*func->map_start)();

    sects = vh_pget(map, "SECTS");

    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        mapnum++;

        if (func->map_section != NULL)
            (*func->map_section)(sect);

        if (func->map_link != NULL) {
            linklist = vh_pget(sect, "LINKS");
            vl_foreach(elt, linklist) {
                link = vs_pget(elt);
                if (!vh_iget(link, "HIDDEN"))
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

/* Print items table */
static void
print_items(void)
{
    struct driver_st drv = drivers[ifm_fmt];
    itemfuncs *func = drv.ifunc;
    vlist *items, *sorted;
    vscalar *elt;
    vhash *item;

    ifm_output = "item";

    items = vh_pget(map, "ITEMS");

    if (func == NULL)
        fatal("no item table driver for %s output", drv.name);

    if (func->item_start != NULL)
        (*func->item_start)();

    sorted = vl_sort(items, itemsort);

    vl_foreach(elt, sorted) {
        item = vs_pget(elt);
        if (func->item_entry != NULL)
            (*func->item_entry)(item);
    }

    if (func->item_finish != NULL)
        (*func->item_finish)();

    vl_destroy(sorted);
}

/* Print task table */
static void
print_tasks(void)
{
    struct driver_st drv = drivers[ifm_fmt];
    taskfuncs *func = drv.tfunc;
    vscalar *elt;
    vlist *tasks;
    vhash *task;

    ifm_output = "task";

    tasks = vh_pget(map, "TASKS");

    if (func == NULL)
        fatal("no task table driver for %s output", drv.name);

    if (func->task_start != NULL)
        (*func->task_start)();

    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        if (func->task_entry != NULL)
            (*func->task_entry)(task);
    }

    if (func->task_finish != NULL)
        (*func->task_finish)();
}

/* Parse input from a file */
static int
parse_input(char *file, int required)
{
    static int parses = 0;
    extern FILE *yyin;

    if (file != NULL) {
        ifm_input = file;
        if ((yyin = fopen(file, "r")) == NULL) {
            if (required)
                fatal("can't open %s", file);
            else
                return 1;
        }
    } else {
        ifm_input = "<stdin>";
        yyin = stdin;
    }

    ifm_errors = 0;
    line_number = 1;
    if (parses++)
        yyrestart(yyin);

    yyparse();
    line_number = 0;

    return (ifm_errors == 0);
}

/* Item sort function */
static int
itemsort(vscalar **ip1, vscalar **ip2)
{
    vhash *i1 = vs_pget(*ip1);
    vhash *i2 = vs_pget(*ip2);
    vhash *ir1, *ir2;
    char *n1, *n2;
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
    n1 = vh_sgetref(i1, "NOTE");
    n2 = vh_sgetref(i2, "NOTE");

    return strcmp((n1 == NULL ? "" : n1),
                  (n2 == NULL ? "" : n2));
}

/* Select an output format */
static int
select_format(char *str, int output)
{
    int i, match, nmatch = 0, len = 0;

    if (str != NULL)
        len = strlen(str);

    for (i = 0; i < NUM_DRIVERS; i++) {
        if (str == NULL) {
            if (output & O_MAP)
                if (drivers[i].mfunc != NULL)
                    return i;
            if (output & O_ITEMS)
                if (drivers[i].ifunc != NULL)
                    return i;
            if (output & O_TASKS)
                if (drivers[i].tfunc != NULL)
                    return i;
        } else {
            if (!strcmp(drivers[i].name, str))
                return i;
            if (!strncmp(drivers[i].name, str, len)) {
                nmatch++;
                match = i;
            }
        }
    }

    if (str == NULL) {
        fatal("internal: no output format found");
    } else {
        if (nmatch == 0)
            fatal("unknown output format: %s", str);
        else if (nmatch > 1)
            fatal("ambiguous output format: %s", str);
    }

    return match;
}

/* Parser-called parse error */
void
yyerror(char *msg)
{
    if (STREQ(msg, "parse error"))
        err("syntax error");
    else
        err(msg);
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
    errfuncs *func = NULL;

    ifm_errors++;
    VPRINT(buf, fmt);

    if (ifm_fmt >= 0)
        func = drivers[ifm_fmt].efunc;

    if (func == NULL) {
        if (line_number > 0)
            fprintf(stderr, "%s: error: %s, line %d: %s\n",
                    progname, ifm_input, line_number, buf);
        else
            fprintf(stderr, "%s: error: %s: %s\n",
                    progname, ifm_input, buf);

        if (ifm_errors >= MAX_ERRORS)
            fatal("too many errors.  Goodbye!");
    } else {
        (*func->error)(ifm_input, line_number, buf);
    }
}

/* Give a parse warning */
void
warn(char *fmt, ...)
{
    errfuncs *func = NULL;

    if (!warning_flag)
        return;

    VPRINT(buf, fmt);

    if (ifm_fmt >= 0)
        func = drivers[ifm_fmt].efunc;

    if (func == NULL) {
        if (line_number > 0)
            fprintf(stderr, "%s: warning: %s, line %d: %s\n",
                    progname, ifm_input, line_number, buf);
        else
            fprintf(stderr, "%s: warning: %s: %s\n",
                    progname, ifm_input, buf);
    } else {
        (*func->warning)(ifm_input, line_number, buf);
    }
}

/* Give a *fatal* error */
void
fatal(char *fmt, ...)
{
    VPRINT(buf, fmt);
    fprintf(stderr, "%s: error: %s\n", progname, buf);
    exit(1);
}

/* Print program version and exit */
static void
print_version(void)
{
    printf("This is Ifm version %s, copyright (C) G. Hutchings\n", VERSION);

    printf("\nLibrary file search path:\n   %s\n\n",
           vl_join(search_path(), "\n   "));

    printf("This program is free software; you can redistribute it and/or modify\n");
    printf("it under the terms of the GNU General Public License as published by\n");
    printf("the Free Software Foundation; either version 2, or (at your option)\n");
    printf("any later version.\n");
    printf("\n");
    printf("This program is distributed in the hope that it will be useful,\n");
    printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
    printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
    printf("GNU General Public License for more details.\n");
    printf("\n");
    printf("You should have received a copy of the GNU General Public License\n");
    printf("along with this program; if not, write to the Free Software\n");
    printf("Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.\n");

    exit(0);
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
