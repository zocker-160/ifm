/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Main functions */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <vars.h>

#include "ifm-driver.h"
#include "ifm-main.h"
#include "ifm-map.h"
#include "ifm-path.h"
#include "ifm-task.h"
#include "ifm-util.h"
#include "ifm-vars.h"

/* Output drivers */
#include "ifm-ps.h"
#include "ifm-text.h"
#include "ifm-tk.h"
#include "ifm-raw.h"
#include "ifm-rec.h"

static struct driver_st {
    char *name, *desc;
    mapfuncs  *mfunc;
    itemfuncs *ifunc;
    taskfuncs *tfunc;
    errfuncs  *efunc;
} drivers[] = {
    { "ps", "PostScript",
      &ps_mapfuncs, NULL, NULL, NULL },

    { "text", "Nicely-formatted ASCII text",
      NULL, &text_itemfuncs, &text_taskfuncs, NULL },

    { "tk", "Tcl/Tk program commands",
      &tk_mapfuncs, &tk_itemfuncs, &tk_taskfuncs, &tk_errfuncs },

    { "raw", "Raw ASCII text fields",
      &raw_mapfuncs, &raw_itemfuncs, &raw_taskfuncs, NULL },

    { "rec", "Recording of game commands",
      NULL, NULL, &rec_taskfuncs, NULL }
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

#define F_NONE -1

/* Max. errors before aborting */
#define MAX_ERRORS 10

/* What's my name? */
char *progname;

/* Input filename */
char ifm_input[BUFSIZ];

/* Current line number */
int line_number;

/* Search path */
vlist *ifm_search = NULL;

/* No. of errors */
static int ifm_errors = 0;

/* Whether to print warnings */
static int warning_flag = 1;

/* Scribble buffer */
static char buf[BUFSIZ];

/* Output format ID */
static int ifm_fmt = F_NONE;

/* Output format name */
char *ifm_format = NULL;

/* Parse function */
extern void yyparse();

/* Debugging flag */
int ifm_debug = 0;

/* Local functions */
static void print_map(void);
static void print_items(void);
static void print_tasks(void);
static int itemsort(vscalar **ip1, vscalar **ip2);
static int parse_input(char *file, int libflag, int required);
static void print_version(void);
static int select_format(char *str, int output);
static void show_info(char *type);
static void show_path(void);
static void usage(void);

/* Show options */
static struct show_st {
    char *name, *desc;
    void (*func)(void);
} showopts[] = {
    { "path", "Show file search path",  show_path },
    { "vars", "Show defined variables", var_list },
    { NULL,   NULL,                NULL }
};

/* Main routine */
int
main(int argc, char *argv[])
{
    int output = O_NONE, initfile = 1;
    char *env, *file, *info = NULL;
    vlist *args, *list;
    vscalar *elt;
    vhash *opts;

#ifdef BISON_DEBUG
    extern int yydebug;
#endif

#ifdef FLEX_DEBUG
    extern int yy_flex_debug;
    yy_flex_debug = 0;
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

    v_option('d', "debug", V_OPT_FLAG, NULL,
             "Print debugging information");

    v_option('s', "show", V_OPT_ARG, "type",
             "Show program information");

    v_option('I', "include", V_OPT_LIST, "dir",
             "Prepend directory to search path");

    v_option('\0', "noinit", V_OPT_FLAG, NULL,
             "Don't read personal init file");

    v_option('\0', "version", V_OPT_FLAG, NULL,
             "Print program version");

    v_option('h', "help", V_OPT_FLAG, NULL,
             "This help message");

    v_option('D', "DEBUG", V_OPT_ARG, "flag", NULL);

    /* Set file search path */
    env = getenv("IFMPATH");
    ifm_search = vl_split(env != NULL ? env : IFMPATH, ":");

    /* Parse command-line arguments */
    if ((opts = vh_getopt(argc, argv)) == NULL)
        v_die("Type `%s -help' for help", progname);

    if (vh_exists(opts, "help"))
        usage();

    if (vh_exists(opts, "version"))
        print_version();

    if ((list = vh_pget(opts, "include")) != NULL)
        while (vl_length(list) > 0)
            vl_sunshift(ifm_search, vl_spop(list));

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

    if (vh_exists(opts, "debug"))
        ifm_debug = 1;

    if (vh_exists(opts, "show"))
        info = vh_sgetref(opts, "show");

    if ((file = vh_sgetref(opts, "output")) != NULL)
        if (freopen(file, "w", stdout) == NULL)
            fatal("can't open %s", file);

    switch (vh_iget(opts, "DEBUG")) {
#ifdef FLEX_DEBUG
    case 1:
        yy_flex_debug = 1;
        break;
#endif

#ifdef BISON_DEBUG
    case 2:
        yydebug = 1;
        break;
#endif
    default:
        break;
    }

    /* Initialise */
    init_map();

    /* Parse system init file */
    if (!parse_input(SYSINIT, 1, 1))
        return 1;

    /* Parse personal init file if available */
    if (initfile && getenv("HOME") != NULL) {
        sprintf(buf, "%s/%s", getenv("HOME"), INITFILE);
        if (!parse_input(buf, 0, 0))
            return 1;
    }

    /* Parse input files (or stdin) */
    args = vh_pget(opts, "ARGS");
    if (vl_length(args) > 0) {
        vl_foreach(elt, args) {
            file = vs_sgetref(elt);
            parse_input(file, 0, 1);
        }
    } else if (info == NULL && !parse_input(NULL, 0, 1)) {
        return 1;
    }

    /* Set output format if not already specified */
    if (output != O_NONE && ifm_fmt == F_NONE) {
        char *str = NULL;
        if (VAR_DEF("format"))
            str = var_string("format");
        ifm_fmt = select_format(str, output);
    }

    /* Resolve tags */
    resolve_tags();
    if (ifm_errors)
        return 1;

    /* Set up rooms */
    setup_rooms();

    /* Set up links */
    setup_links();
    if (ifm_errors)
        return 1;

    /* Set up room exits */
    setup_exits();

    /* Set up sections */
    setup_sections();

    /* Solve game if required */
    if (output == O_NONE || output & O_TASKS) {
        connect_rooms();
        if (ifm_errors)
            return 1;

        setup_tasks();
        if (ifm_errors)
            return 1;

        check_cycles();
        if (ifm_errors)
            return 1;

        solve_game();
    }

    /* Do what's required */
    if (ifm_fmt != F_NONE)
        ifm_format = drivers[ifm_fmt].name;

    /* Just show info if required */
    if (info != NULL)
        show_info(info);

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

    vhash *sect, *room, *link, *join;
    vlist *sects, *list;
    vscalar *elt;

    if (func == NULL)
        fatal("no map driver for %s output", drv.name);

    if (func->map_start != NULL)
        (*func->map_start)();

    sects = vh_pget(map, "SECTS");

    vl_foreach(elt, sects) {
        sect = vs_pget(elt);

        if (func->map_section != NULL)
            (*func->map_section)(sect);

        if (func->map_room != NULL) {
            list = vh_pget(sect, "ROOMS");
            vl_foreach(elt, list) {
                room = vs_pget(elt);
                (*func->map_room)(room);
            }
        }

        if (func->map_link != NULL) {
            list = vh_pget(sect, "LINKS");
            vl_foreach(elt, list) {
                link = vs_pget(elt);
                if (vh_iget(link, "HIDDEN"))
                    continue;
                if (vh_iget(link, "NOLINK"))
                    continue;
                (*func->map_link)(link);
            }
        }

        if (func->map_endsection != NULL)
            (*func->map_endsection)();
    }

    if (func->map_finish != NULL)
        (*func->map_finish)();

    if (func->map_join != NULL) {
        vl_foreach(elt, joins) {
            join = vs_pget(elt);
            if (vh_iget(join, "HIDDEN"))
                continue;
            (*func->map_join)(join);
        }
    }
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

    items = vh_pget(map, "ITEMS");

    if (func == NULL)
        fatal("no item table driver for %s output", drv.name);

    if (func->item_start != NULL)
        (*func->item_start)();

    if (func->item_entry != NULL) {
        sorted = vl_sort(items, itemsort);

        vl_foreach(elt, sorted) {
            item = vs_pget(elt);
            (*func->item_entry)(item);
        }

        vl_destroy(sorted);
    }

    if (func->item_finish != NULL)
        (*func->item_finish)();
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

    tasks = vh_pget(map, "TASKS");

    if (func == NULL)
        fatal("no task table driver for %s output", drv.name);

    if (func->task_start != NULL)
        (*func->task_start)();

    if (func->task_entry != NULL) {
        vl_foreach(elt, tasks) {
            task = vs_pget(elt);
            (*func->task_entry)(task);
        }
    }

    if (func->task_finish != NULL)
        (*func->task_finish)();
}

/* Parse input from a file */
static int
parse_input(char *file, int libflag, int required)
{
    static int parses = 0;
    extern FILE *yyin;

    if (file != NULL) {
        if ((yyin = open_file(file, libflag, required)) == NULL)
            return 1;
    } else {
        strcpy(ifm_input, "<stdin>");
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
    int cmp;

    /* First, by item name */
    cmp = strcmp(vh_sgetref(i1, "DESC"), vh_sgetref(i2, "DESC"));
    if (cmp) return cmp;

    /* Next, by room name */
    ir1 = vh_pget(i1, "ROOM");
    ir2 = vh_pget(i2, "ROOM");
    return strcmp((ir1 == NULL ? "" : vh_sgetref(ir1, "DESC")),
                  (ir2 == NULL ? "" : vh_sgetref(ir2, "DESC")));
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
            if (strcmp(drivers[i].name, str) == 0)
                return i;
            if (strncmp(drivers[i].name, str, len) == 0) {
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
    printf("This is IFM version %s, copyright (C) G. Hutchings\n", VERSION);
    printf("\n");
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

/* Show some information */
static void
show_info(char *type)
{
    int i, match, nmatch = 0, len = strlen(type);

    /* Find info type */
    for (i = 0; showopts[i].name != NULL; i++) {
        if (strncmp(showopts[i].name, type, len) == 0) {
            nmatch++;
            match = i;
        }
    }

    if (nmatch == 0)
        fatal("unknown info type: %s", type);
    else if (nmatch > 1)
        fatal("ambiguous info type: %s", type);

    (*showopts[match].func)();
    exit(0);
}

/* Print file search path */
static void
show_path(void)
{
    printf("%s\n", vl_join(ifm_search, " "));
}

/* Print a usage message and exit */
static void
usage()
{
    int i;

    v_usage("Usage: %s [options] [file...]", progname);

    printf("\nOutput formats (may be abbreviated):\n");
    for (i = 0; i < NUM_DRIVERS; i++)
        printf("    %-15s    %s\n", drivers[i].name, drivers[i].desc);

    printf("\nShow options (may be abbreviated):\n");
    for (i = 0; showopts[i].name != NULL; i++)
        printf("    %-15s    %s\n", showopts[i].name, showopts[i].desc);

    exit(0);
}
