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

/* Output types */
#define O_NONE  0x0             /* No output */
#define O_MAP   0x1             /* Map */
#define O_ITEMS 0x2             /* Item list */
#define O_TASKS 0x4             /* Task list */

/* Max. errors before aborting */
#define MAX_ERRORS 10

char *ifm_format = NULL;        /* Output format name */

int line_number;                /* Current line number */

vlist *ifm_search = NULL;       /* Search path */
vlist *ifm_styles = NULL;       /* Global styles */

static char *progname;          /* Program name */
static char ifm_input[BUFSIZ];  /* Input filename */

static int ifm_driver = -1;     /* Output driver ID */
static int ifm_errors = 0;      /* No. of errors */
static int prep_only = 0;       /* Whether to only preprocess */
static int warning_flag = 1;    /* Whether to print warnings */

static vlist *sections = NULL;  /* List of map sections to output */

/* Internal functions */
static void message(char *type, char *msg);
static void print_version(void);
static int select_format(char *str, int output);
static void show_info(char *type);
static void show_maps(void);
static void show_path(void);
static void usage(void);

/* Info options */
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
    char *env, *file, *info = NULL, *spec, *fmt = NULL, *home;
    int output = O_NONE, initfile = 1;
    vlist *args, *list;
    vscalar *elt;
    vhash *opts;
    V_BUF_DECL;

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

    if (vh_exists(opts, "version")) {
        print_version();
        return 0;
    }

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
        ifm_driver = select_format(fmt, 0);
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

    /* Set search path */
    ifm_search = vl_split(IFMPATH, PATHSEP);

    if ((env = getenv("IFMPATH")) != NULL) {
        list = vl_split(env, PATHSEP);
        while (vl_length(list) > 0)
            vl_sunshift(ifm_search, vl_spop(list));
    }

    if ((list = vh_pget(opts, "I")) != NULL)
        while (vl_length(list) > 0)
            vl_sunshift(ifm_search, vl_spop(list));

    /* Set up preprocessor */
    gpp_init();
    if (ifm_errors)
        return 1;

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
    if (initfile) {
        home = getenv("HOME");
        V_BUF_SET2("%s/%s", home != NULL ? home : ".", INITFILE);
        if (!parse_input(V_BUF_VAL, 0, 0))
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
    if (output != O_NONE && ifm_driver < 0)
        ifm_driver = select_format(NULL, output);

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

    /* Set up map sections */
    setup_sections();

    /* Connect rooms together */
    connect_rooms();
    if (ifm_errors)
        return 1;

    /* Set up tasks */
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
    if (ifm_driver >= 0)
        ifm_format = drivers[ifm_driver].name;

    /* Just show info if required */
    if (info == NULL) {
        if (output == O_NONE && !TASK_VERBOSE)
            printf("Syntax appears OK\n");

        if (output & O_MAP)
            print_map(ifm_driver, sections);

        if (output & O_ITEMS)
            print_items(ifm_driver);

        if (output & O_TASKS)
            print_tasks(ifm_driver);
    } else {
        show_info(info);
    }

    /* Er... that's it */
    return 0;
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

/* Select an output format */
static int
select_format(char *str, int output)
{
    int i, match, nmatch = 0, len = 0;

    if (str != NULL)
        len = strlen(str);

    for (i = 0; drivers[i].name != NULL; i++) {
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

    if (str == NULL)
        fatal("internal: no output format found");
    else if (nmatch == 0)
        fatal("unknown output format: %s", str);
    else if (nmatch > 1)
        fatal("ambiguous output format: %s", str);

    return match;
}

/* Switch to new input file */
void
switch_file(char *file, int line, int flag)
{
    strcpy(ifm_input, file);
    line_number = line;

    switch (flag) {
    case 0:
        debug("switching to file: %s, line %d", file, line);
        break;
    case 1:
        debug("including file: %s, line %d", file, line);
        break;
    case 2:
        debug("returning to file: %s, line %d", file, line);
        break;
    }
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
    V_BUF_DECL;
    char *msg;

    ifm_errors++;
    V_BUF_FMT(fmt, msg);

    if (ifm_driver >= 0)
        func = drivers[ifm_driver].efunc;

    if (func == NULL) {
        message("error", msg);
        if (ifm_errors >= MAX_ERRORS)
            fatal("too many errors.  Goodbye!");
    } else {
        func->error(ifm_input, line_number, msg);
    }
}

/* Give a parse warning */
void
warn(char *fmt, ...)
{
    errfuncs *func = NULL;
    V_BUF_DECL;
    char *msg;

    if (!warning_flag)
        return;

    V_BUF_FMT(fmt, msg);

    if (ifm_driver >= 0)
        func = drivers[ifm_driver].efunc;

    if (func == NULL)
        message("warning", msg);
    else
        func->warning(ifm_input, line_number, msg);
}

/* Give a debugging message */
void
debug(char *fmt, ...)
{
    V_BUF_DECL;
    char *msg;

    if (getenv("IFM_DEBUG")) {
        V_BUF_FMT(fmt, msg);
        fprintf(stderr, "IFM: %s\n", msg);
    }
}

/* Give a general message */
static void
message(char *type, char *msg)
{
    fprintf(stderr, "%s: %s", progname, type);

    if (strlen(ifm_input) > 0) {
        fprintf(stderr, ": %s", ifm_input);
        if (line_number > 0)
            fprintf(stderr, ", line %d", line_number);
    }

    fprintf(stderr, ": %s\n", msg);
}

/* Give a *fatal* error */
void
fatal(char *fmt, ...)
{
    V_BUF_DECL;
    char *msg;

    V_BUF_FMT(fmt, msg);
    fprintf(stderr, "%s: error: %s\n", progname, msg);
    exit(1);
}

/* Print program version */
static void
print_version(void)
{
    printf("IFM version %s\n", VERSION);
    printf("Copyright (C) Glenn Hutchings <%s>\n\n", PACKAGE_BUGREPORT);

    printf("This program is free software; you can redistribute it and/or modify\n");
    printf("it under the terms of the GNU General Public License as published by\n");
    printf("the Free Software Foundation; either version 2, or (at your option)\n");
    printf("any later version.\n\n");

    printf("This program is distributed in the hope that it will be useful,\n");
    printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
    printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
    printf("GNU General Public License for more details.\n\n");

    printf("You should have received a copy of the GNU General Public License\n");
    printf("along with this program; if not, write to the Free Software\n");
    printf("Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.\n");
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
    V_BUF_DECL;

    set_map_vars();

    printf("%s\t%s\t%s\t%s\t%s\n",
           "No.", "Rooms", "Width", "Height", "Name");

    vl_foreach(elt, sects) {
        sect = vs_pget(elt);

        if (vh_exists(sect, "TITLE"))
            title = vh_sgetref(sect, "TITLE");
        else
            title = V_BUF_SET1("Map section %d", num);

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
    for (i = 0; drivers[i].name != NULL; i++)
        printf("    %-15s     %s\n", drivers[i].name, drivers[i].desc);

    printf("\nShow options (may be abbreviated):\n");
    for (i = 0; showopts[i].name != NULL; i++)
        printf("    %-15s     %s\n", showopts[i].name, showopts[i].desc);

    exit(0);
}
