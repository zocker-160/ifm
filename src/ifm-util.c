/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Utility functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ifm.h"

/* Variable encoding buffer */
static char encbuf[BUFSIZ];

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static vlist *var_decode(char *code);
static char *var_encode(char *driver, char *type, int mapnum, char *var);

/* Return an integer variable */
int
get_int(char *id, int def)
{
    vscalar *var = get_var(id);

    if (var != NULL)
        return vs_iget(var);
    return def;
}

/* Return a real variable */
double
get_real(char *id, double def)
{
    vscalar *var = get_var(id);

    if (var != NULL)
        return vs_dget(var);
    return def;
}

/* Return a string variable */
char *
get_string(char *id, char *def)
{
    vscalar *var = get_var(id);

    if (var != NULL)
        return vs_sgetcopy(var);
    return def;
}

/* Return value of a variable */
vscalar *
get_var(char *id)
{
    vscalar *var = NULL;
    int n1, n2, n3;
    char *key;

    /* Check current map first */
    for (n1 = 0; n1 < 2; n1++) {
        if (n1 == 0 && mapnum == 0)
            continue;

        /* Check current output format first */
        for (n2 = 0; n2 < 2; n2++) {
            if (n2 == 0 && ifm_output == NULL)
                continue;

            /* Check current output type first */
            for (n3 = 0; n3 < 2; n3++) {
                if (n3 == 0 && ifm_format == NULL)
                    continue;

                key = var_encode((n3 ? NULL : ifm_format),
                                 (n2 ? NULL : ifm_output),
                                 (n1 ? 0 : mapnum), id);
                if ((var = vh_get(vars, key)) != NULL)
                    return var;
            }
        }
    }

    return NULL;
}

/* Open a library file for reading */
FILE *
open_libfile(char *name)
{
    vlist *pathlist = search_path();
    vscalar *elt;
    FILE *fp;

    /* Try each path */
    vl_foreach(elt, pathlist) {
        sprintf(buf, "%s/%s", vs_sgetref(elt), name);
        if ((fp = fopen(buf, "r")) != NULL)
            return fp;
    }

    /* Give up */
    fatal("can't find `%s' in any of these directories:\n   %s",
          name, vl_join(pathlist, "\n   "));

    /* Shut lint up */
    return NULL;
}

/* Return the library file search path */
vlist *
search_path(void)
{
    static vlist *pathlist = NULL;

    if (pathlist == NULL) {
        char *env = getenv("IFMPATH");
        pathlist = vl_split(env != NULL ? env : IFMPATH, ":");
    }

    return pathlist;
}

/* Set a scalar variable */
void
set_var(char *driver, char *type, char *var, vscalar *val)
{
    char *key = var_encode(driver, type, mapnum, var);
    vh_store(vars, key, val);
}

/* Split a line based on a given width/height ratio */
vlist *
split_line(char *string, double ratio)
{
    int llen = (int) (sqrt((double) strlen(string)) * ratio);
    vlist *list = vl_create();
    static char buf[BUFSIZ];
    char *tok;

    tok = strtok(string, " \t");
    strcpy(buf, tok);

    while ((tok = strtok(NULL, " \t")) != NULL) {
        if (strlen(buf) + strlen(tok) + 1 > llen) {
            vl_spush(list, buf);
            strcpy(buf, tok);
        } else {
            strcat(buf, " ");
            strcat(buf, tok);
        }
    }

    vl_spush(list, buf);
    return list;
}

/* Truncate a list of points based on a given box width and height */
void
truncate_points(vlist *x, vlist *y, double wid, double ht)
{
    double x1, y1, x2, y2, xf, yf, xl, yl;
    double xfac = 1 - wid / 2;
    double yfac = 1 - ht / 2;
    int np = vl_length(x);

    if (np < 2)
        return;

    /* Truncate first point */
    x1 = vl_dget(x, 1);
    y1 = vl_dget(y, 1);
    x2 = vl_dget(x, 0);
    y2 = vl_dget(y, 0);
    xf = x1 + xfac * (x2 - x1);
    yf = y1 + yfac * (y2 - y1);

    /* Truncate last point */
    x1 = vl_dget(x, np - 2);
    y1 = vl_dget(y, np - 2);
    x2 = vl_dget(x, np - 1);
    y2 = vl_dget(y, np - 1);
    xl = x1 + xfac * (x2 - x1);
    yl = y1 + yfac * (y2 - y1);

    /* Replace points */
    vl_dstore(x, 0, xf);
    vl_dstore(y, 0, yf);
    vl_dstore(x, np - 1, xl);
    vl_dstore(y, np - 1, yl);
}

/* Decode an encoded variable */
static vlist *
var_decode(char *code)
{
    static vlist *list = NULL;
    vscalar *val;

    if (list != NULL)
        vl_destroy(list);
    list = vl_split(code, NULL);

    val = vh_get(vars, code);
    vl_push(list, vs_copy(val));

    return list;
}

/* Encode a variable */
static char *
var_encode(char *driver, char *type, int mapnum, char *var)
{
    sprintf(encbuf, "%s %s %d %s",
            (driver == NULL ? "default" : driver),
            (type == NULL ? "global" : type),
            mapnum, var);

    return encbuf;
}
