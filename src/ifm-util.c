/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
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

/* Return an integer variable */
int
get_int(char *id, int def)
{
    vscalar *var = get_var(id);

    if (var != NULL)
        return vs_ival(var);
    return def;
}

/* Return a real variable */
double
get_real(char *id, double def)
{
    vscalar *var = get_var(id);

    if (var != NULL)
        return vs_dval(var);
    return def;
}

/* Return a string variable */
char *
get_string(char *id, char *def)
{
    vscalar *var = get_var(id);

    if (var != NULL)
        return vs_svalcopy(var);
    return def;
}

/* Return a scalar variable from the symbol table */
vscalar *
get_var(char *id)
{
    vhash *h1, *h2;
    vscalar *var;

    /* Try driver-based symbol table first */
    if (ifm_format != NULL) {
        h1 = vh_pget(vars, ifm_format);

        if (ifm_output != NULL) {
            h2 = vh_pget(h1, ifm_output);
            var = vh_get(h2, id);
        }

        if (var == NULL) {
            h2 = vh_pget(h1, "global");
            var = vh_get(h2, id);
        }
    }

    /* If not, try main symbol table */
    if (var == NULL) {
        h1 = vh_pget(vars, "default");

        if (ifm_output != NULL) {
            h2 = vh_pget(h1, ifm_output);
            var = vh_get(h2, id);
        }

        if (var == NULL) {
            h2 = vh_pget(h1, "global");
            var = vh_get(h2, id);
        }
    }

    return var;
}

/* Print currently defined variables */
void
print_vars()
{
    vlist *entries1, *entries2, *tables = vh_sortkeys(vars, NULL);
    char *table1, *table2, *var;
    vhash *symtab1, *symtab2;
    vscalar *elt;

    FOREACH(elt, tables) {
        table1 = vs_sval(elt);
        symtab1 = vh_pget(vars, table1);
        entries1 = vh_sortkeys(symtab1, NULL);

        FOREACH(elt, entries1) {
            table2 = vs_sval(elt);
            symtab2 = vh_pget(symtab1, table2);
            entries2 = vh_sortkeys(symtab2, NULL);

            FOREACH(elt, entries2) {
                var = vs_sval(elt);
                printf("%s %s %s = %s\n", table1, table2,
                       var, vh_sget(symtab2, var));
            }

            vl_destroy(entries2);
        }

        vl_destroy(entries1);
    }

    vl_destroy(tables);
}

/* Set a scalar variable */
void
set_var(char *table1, char *table2, char *var, vscalar *val)
{
    vhash *h1, *h2;

    h1 = vh_pget(vars, table1);

    if (h1 != NULL) {
        h2 = vh_pget(h1, table2);
        if (h2 != NULL)
            vh_store(h2, var, val);
        else
            err("no such output type: %s", table2);
    } else {
        warn("no such output driver: %s", table1);
    }
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

/* Truncate a link based on a given box width and height */
void
truncate_link(vhash *link, double wid, double ht)
{
    double x1, y1, x2, y2, xf, yf, xl, yl;
    vlist *x = vh_pget(link, "X");
    vlist *y = vh_pget(link, "Y");
    double xfac = 1 - wid / 2;
    double yfac = 1 - ht / 2;
    int np = vl_length(x);

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
