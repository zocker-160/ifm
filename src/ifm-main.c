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
#include "ifm-gpp.h"
#include "ifm-main.h"
#include "ifm-map.h"
#include "ifm-path.h"
#include "ifm-task.h"
#include "ifm-util.h"
#include "ifm-vars.h"

/* Output drivers */
#include "ifm-ps.h"
#include "ifm-fig.h"
#include "ifm-text.h"
#include "ifm-tk.h"
#include "ifm-raw.h"
#include "ifm-rec.h"
#include "ifm-dot.h"

static struct driver_st {
    char *name, *desc;
    mapfuncs  *mfunc;
    itemfuncs *ifunc;
    taskfuncs *tfunc;
    errfuncs  *efunc;
} drivers[] = {
    { "ps", "PostScript",
      &ps_mapfuncs, NULL, NULL, NULL },

    { "fig", "Fig drawing commands",
      &fig_mapfuncs, NULL, NULL, NULL },

    { "text", "Nicely-formatted ASCII text",
      NULL, &text_itemfuncs, &text_taskfuncs, NULL },

    { "rec", "Recording of game commands",
      NULL, NULL, &rec_taskfuncs, NULL },

    { "dot", "Graph of task dependencies",
      NULL, NULL, &dot_taskfuncs, NULL },

    { "raw", "Raw ASCII text fields",
      &raw_mapfuncs, &raw_itemfuncs, &raw_taskfuncs, NULL },

    { "tk", "Tcl/Tk program commands (tkifm)",
      &tk_mapfuncs, &tk_itemfuncs, &tk_taskfuncs, &tk_errfuncs }
};

#define NUM_DRIVERS (int) (sizeof(drivers) / sizeof(drivers[0]))

#define PRINT_MSG(type, msg) \
        fprintf(stderr, "%s: %s", progname, #type);                     \
        if (strlen(ifm_input) > 0) {                                    \
            fprintf(stderr, ": %s", ifm_input);                         \
            if (line_number > 0)                                        \
                fprintf(stderr, ", line %d", line_number);              \
        }                                                               \
        fprintf(stderr, ": %s\n", buf)

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

/* Global styles */
vlist *ifm_styles = NULL;

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

/* List of map sections to output */
static vlist *sections = NULL;

/* Whether to only preprocess */
static int prep_only = 0;

/* Internal functions */
static void print_map(void);
static void print_items(void);
static void print_tasks(void);
static int itemsort(vscalar **ip1, vscalar **ip2);
static void print_version(void);
static int select_format(char *str, int output);
static void show_info(char *type);
static void show_maps(void);
static void show_path(void);
static void usage(void);

/* Show options */
static struct show_st {
    char *name, *desc;
    void (*func)(void);
} showopts[] = {
    { "maps", "Show map sections",      show_maps },
    { "vars", "Show defined variables", var_list  },
    { "path", "Show file search path",  show_path },
    { NULL,   NULL,                NULL }
};

/* Main routine */
int
main(int argc, char *argv[])
{
    char *env, *file, *info = NULL, *spec, *fmt = NULL;
    int output = O_NONE, initfile = 1;
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

    /* Initialise */
    v_debug_env();
    progname = argv[0];

    /* Define options */
    v_optgroup("Output options:");

    v_option('m', "map", V_OPT_OPTARG, "sections",
             "Select map output");

    v_option('i', "items", V_OPT_FLAG, NULL,
             "Select item output");

    v_option('t', "tasks", V_OPT_FLAG, NULL,
             "Select task output");

    v_option('f', "format", V_OPT_ARG, "fmt",
             "Select output format");

    v_option('o', "output", V_OPT_ARG, "file",
             "Write output to file");

    v_optgroup("Auxiliary options:");

    v_option('S', "style", V_OPT_LIST, "name",
             "Push a style onto the style list");

    v_option('s', "set", V_OPT_LIST, "var=val",
             "Set a customization variable");

    v_option('w', "nowarn", V_OPT_FLAG, NULL,
             "Don't print warnings");

    v_option('\0', "noinit", V_OPT_FLAG, NULL,
             "Don't read personal init file");

    v_optgroup("Preprocessor options:");

    v_option('D', NULL, V_OPT_LIST, "var[=val]",
             "Define a preprocessor symbol");

    v_option('I', NULL, V_OPT_LIST, "dir",
             "Prepend directory to search path");

    v_option('P', NULL, V_OPT_FLAG, NULL,
             "Just preprocess input");

    v_optgroup("Information options:");

    v_option('\0', "show", V_OPT_ARG, "type",
             "Show information");

    v_option('v', "version", V_OPT_FLAG, NULL,
             "Print program version");

    v_option('h', "help", V_OPT_FLAG, NULL,
             "This help message");

    v_option('\0', "DEBUG", V_OPT_ARG, "flag", NULL);

    /* Parse command-line arguments */
    if ((opts = vh_getopt(argc, argv)) == NULL)
        v_die("Type '%s -help' for help", progname);

    if (vh_exists(opts, "help"))
        usage();

    if (vh_exists(opts, "version"))
        print_version();

    if (vh_exists(opts, "map")) {
        output |= O_MAP;
        spec = vh_sgetref(opts, "map");
        if (strlen(spec) > 0 && (sections = vl_parse_list(spec)) == NULL)
            fatal("invalid map section spec: %s", spec);
    }

    if (vh_exists(opts, "items"))
        output |= O_ITEMS;

    if (vh_exists(opts, "tasks"))
        output |= O_TASKS;

    if (vh_exists(opts, "format")) {
        fmt = vh_sgetref(opts, "format");
        ifm_fmt = select_format(fmt, 0);
    }

    if (vh_exists(opts, "nowarn"))
        warning_flag = 0;

    if (vh_exists(opts, "noinit"))
        initfile = 0;

    if (vh_exists(opts, "show"))
        info = vh_sgetref(opts, "show");

    if ((ifm_styles = vh_pget(opts, "style")) != NULL) {
        vl_foreach(elt, ifm_styles)
            ref_style(vs_sgetref(elt));
    }

    /* Set up preprocessor stuff */
    gpp_init();

    ifm_search = vl_split(IFMPATH, PATHSEP);

    if ((env = getenv("IFMPATH")) != NULL) {
        list = vl_split(env, PATHSEP);
        while (vl_length(list) > 0)
            vl_sunshift(ifm_search, vl_spop(list));
    }

    if ((list = vh_pget(opts, "I")) != NULL)
        while (vl_length(list) > 0)
            vl_sunshift(ifm_search, vl_spop(list));

    vl_foreach(elt, ifm_search)
        gpp_include(vs_sgetref(elt));

    if ((list = vh_pget(opts, "D")) != NULL) {
        vl_foreach(elt, list)
            gpp_define(vs_sgetref(elt), NULL);
    }

    gpp_define("IFM_VERSION", VERSION);

    if (fmt != NULL)
        gpp_define("IFM_FORMAT", fmt);

    prep_only = vh_iget(opts, "P");

    /* Set internal debugging options */
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

    debug("gpp command: %s", gpp_command());

    /* Initialise map stuff */
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

    /* That's it if only preprocessing */
    if (prep_only)
        return 0;

    /* Load style definitions */
    set_style_list(ifm_styles);
    load_styles();
    if (ifm_errors)
        return 1;

    /* Set any variables from command line */
    if ((list = vh_pget(opts, "set")) != NULL) {
        char *cp;
        vl_foreach(elt, list) {
            spec = vs_sgetref(elt);
            if ((cp = strchr(spec, '=')) != NULL) {
                *cp++ = '\0';
                var_set(NULL, spec, vs_screate(cp));
            }
        }
    }

    /* Set output format if not already specified */
    if (output != O_NONE && ifm_fmt == F_NONE)
        ifm_fmt = select_format(NULL, output);

    /* Open output file if required */
    if (vh_exists(opts, "output")) {
        file = vh_sgetref(opts, "output");
        if (freopen(file, "w", stdout) == NULL)
            fatal("can't open %s", file);
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

    /* Set up tasks */
    connect_rooms();
    if (ifm_errors)
        return 1;

    setup_tasks();
    if (ifm_errors)
        return 1;

    /* Solve game if required */
    if (output == O_NONE || output & O_TASKS) {
        check_cycles();
        if (!ifm_errors)
            solve_game();
        else
            return 1;
    }

    /* Do what's required */
    if (ifm_fmt != F_NONE)
        ifm_format = drivers[ifm_fmt].name;

    /* Just show info if required */
    if (info != NULL)
        show_info(info);

    if (output == O_NONE && !TASK_VERBOSE)
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
    int num = 1;

    if (func == NULL)
        fatal("no map driver for %s output", drv.name);

    sects = vh_pget(map, "SECTS");
    vl_foreach(elt, sects) {    
        sect = vs_pget(elt);
        if (sections != NULL && !vl_iget(sections, num++))
            vh_istore(sect, "NOPRINT", 1);
    }

    set_map_vars();

    if (func->map_start != NULL)
        (*func->map_start)();

    vl_foreach(elt, sects) {
        sect = vs_pget(elt);

        if (vh_iget(sect, "NOPRINT"))
            continue;

        if (func->map_section != NULL)
            (*func->map_section)(sect);

        if (func->map_room != NULL) {
            list = vh_pget(sect, "ROOMS");
            vl_foreach(elt, list) {
                room = vs_pget(elt);
                set_style_list(vh_pget(room, "STYLE"));
                set_room_vars();
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

                set_style_list(vh_pget(link, "STYLE"));
                set_link_vars();
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

            set_style_list(vh_pget(join, "STYLE"));
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
        fatal("no item driver for %s output", drv.name);

    if (func->item_start != NULL)
        (*func->item_start)();

    if (func->item_entry != NULL) {
        sorted = vl_sort(items, itemsort);

        vl_foreach(elt, sorted) {
            item = vs_pget(elt);
            set_style_list(vh_pget(item, "STYLE"));
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
        fatal("no task driver for %s output", drv.name);

    if (func->task_start != NULL)
        (*func->task_start)();

    if (func->task_entry != NULL) {
        vl_foreach(elt, tasks) {
            task = vs_pget(elt);
            set_style_list(vh_pget(task, "STYLE"));
            (*func->task_entry)(task);
        }
    }

    if (func->task_finish != NULL)
        (*func->task_finish)();
}

/* Parse input from a file */
int
parse_input(char *file, int libflag, int required)
{
    static int parses = 0;
    extern FILE *yyin;
    char *path = file;
    int c;

    line_number = 0;

    if (file == NULL || V_STREQ(file, "-")) {
        strcpy(ifm_input, "<stdin>");
        path = NULL;
    } else {
        if (libflag)
            path = find_file(file);

        if (!required && (path == NULL || !v_exists(path)))
            return 1;

        if (path == NULL)
            fatal("can't locate file '%s'", file);
        else if (!v_exists(path))
            fatal("file '%s' not found", path);

        strcpy(ifm_input, path);
    }

    line_number = 1;
    ifm_errors = 0;

    yyin = gpp_open(path);

    if (prep_only) {
        while ((c = fgetc(yyin)) != EOF)
            putchar(c);
    } else {
        if (parses++)
            yyrestart(yyin);
        yyparse();
    }

    gpp_close(yyin);
    line_number = 0;
    strcpy(ifm_input, "");

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
    if (V_STREQ(msg, "parse error"))
        err("syntax error");
    else
        err(msg);
}

/* Give a parse error */
void
err(char *fmt, ...)
{
    errfuncs *func = NULL;

    ifm_errors++;
    V_VPRINT(buf, fmt);

    if (ifm_fmt >= 0)
        func = drivers[ifm_fmt].efunc;

    if (func == NULL) {
        PRINT_MSG(error, buf);
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

    V_VPRINT(buf, fmt);

    if (ifm_fmt >= 0)
        func = drivers[ifm_fmt].efunc;

    if (func == NULL) {
        PRINT_MSG(warning, buf);
    } else {
        (*func->warning)(ifm_input, line_number, buf);
    }
}

/* Give a debugging message */
void
debug(char *fmt, ...)
{
    if (getenv("IFM_DEBUG")) {
        V_VPRINT(buf, fmt);
        fprintf(stderr, "IFM: %s\n", buf);
    }
}

/* Give a *fatal* error */
void
fatal(char *fmt, ...)
{
    V_VPRINT(buf, fmt);
    fprintf(stderr, "%s: error: %s\n", progname, buf);
    exit(1);
}

/* Print program version and exit */
static void
print_version(void)
{
    printf("IFM version %s\n", VERSION);
    printf("Copyright (C) Glenn Hutchings <%s>\n", PACKAGE_BUGREPORT);
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

    showopts[match].func();
    exit(0);
}

/* Print map sections */
static void
show_maps(void)
{
    int num = 1, xlen, ylen;
    vlist *rooms;
    vscalar *elt;
    char *title;
    vhash *sect;

    set_map_vars();

    printf("%s\t%s\t%s\t%s\t%s\n",
           "No.", "Rooms", "Width", "Height", "Name");

    vl_foreach(elt, sects) {
        sect = vs_pget(elt);

        if (vh_exists(sect, "TITLE")) {
            title = vh_sgetref(sect, "TITLE");
        } else {
            sprintf(buf, "Map section %d", num);
            title = buf;
        }

        rooms = vh_pget(sect, "ROOMS");
        xlen = vh_iget(sect, "XLEN");
        ylen = vh_iget(sect, "YLEN");

        if (show_map_title && vh_exists(sect, "TITLE"))
            ylen++;

        printf("%d\t%d\t%d\t%d\t%s\n",
               num++, vl_length(rooms), xlen, ylen, title);
    }
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
        printf("    %-15s     %s\n", drivers[i].name, drivers[i].desc);

    printf("\nShow options (may be abbreviated):\n");
    for (i = 0; showopts[i].name != NULL; i++)
        printf("    %-15s     %s\n", showopts[i].name, showopts[i].desc);

    exit(0);
}
