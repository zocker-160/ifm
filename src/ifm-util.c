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
