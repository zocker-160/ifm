/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Utility functions */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <vars.h>

#include "ifm-main.h"
#include "ifm-map.h"
#include "ifm-util.h"

/* Direction info (same order as direction enum list) */
struct d_info dirinfo[] = {
    "?",   "none",      D_NONE,      D_NONE,       0,  0,
    "N",   "north",     D_NORTH,     D_SOUTH,      0,  1,
    "S",   "south",     D_SOUTH,     D_NORTH,      0, -1,
    "E",   "east",      D_EAST,      D_WEST,       1,  0,
    "W",   "west",      D_WEST,      D_EAST,      -1,  0,
    "NE",  "northeast", D_NORTHEAST, D_SOUTHWEST,  1,  1,
    "SW",  "southwest", D_SOUTHWEST, D_NORTHEAST, -1, -1,
    "NW",  "northwest", D_NORTHWEST, D_SOUTHEAST, -1,  1,
    "SE",  "southeast", D_SOUTHEAST, D_NORTHWEST,  1, -1,
    "U",   "up",        D_UP,        D_DOWN,       0,  0,
    "D",   "down",      D_DOWN,      D_UP,         0,  0,
    "IN",  "in",        D_IN,        D_OUT,        0,  0,
    "OUT", "out",       D_OUT,       D_IN,         0,  0,
    NULL,  NULL,        D_NONE,      D_NONE,       0,  0
};

/* Variable encoding buffer */
static char encbuf[BUFSIZ];

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static vlist *var_decode(char *code);
static char *var_encode(char *driver, char *type, int mapnum, char *var);

/* Add a list attribute to an object */
void
add_attr(vhash *obj, char *attr, char *fmt, ...)
{
    vlist *list;

    if ((list = vh_pget(obj, attr)) == NULL) {
        list = vl_create();
        vh_pstore(obj, attr, list);
    }

    if (fmt != NULL) {
        VPRINT(buf, fmt);
        vl_spush(list, buf);
    } else {
        vl_empty(list);
    }
}

/* Return direction given offsets */
int
get_direction(int xoff, int yoff)
{
    int dir;

    for (dir = 0; dirinfo[dir].sname != NULL; dir++)
        if (xoff == dirinfo[dir].xoff && yoff == dirinfo[dir].yoff)
            return dir;

    return D_NONE;
}

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

/* Indent output line */
void
indent(int num)
{
    int i;

    for (i = 0; i < 4 * num; i++)
        putchar(' ');
}

/* Warn about obsolete syntax */
void
obsolete(char *old, char *new)
{
    static vhash *warned = NULL;

    if (warned == NULL)
        warned = vh_create();

    if (vh_exists(warned, old))
        return;

    vh_sstore(warned, old, new);
    warn("%s is obsolete -- use %s instead", old, new);
}

/* Open a file */
FILE *
open_file(char *file, int libflag)
{
    FILE *fp = NULL;
    vscalar *elt;

    /* Try the search path if required */
    if (libflag) {
        vl_foreach(elt, ifm_search) {
            sprintf(buf, "%s/%s", vs_sgetref(elt), file);
            if ((fp = fopen(buf, "r")) != NULL) {
                strcpy(ifm_input, buf);
                vl_break(ifm_search);
                break;
            }
        }
    } else {
        fp = fopen(file, "r");
        strcpy(ifm_input, file);
    }

    if (fp == NULL)
        fatal("can't open %s `%s'", (libflag ? "library file" : "file"), file);

    return fp;
}

/* Pack sections onto virtual pages */
int
pack_sections(int xmax, int ymax, int border)
{
    int pos, packed, x1, y1, x2, y2, xo, yo, num, xlen, ylen;
    vlist *pages, *newpages, *psects, *opsects;
    double xo1, yo1, xo2, yo2, r1, r2, ratio;
    int v1, v2, rflag, xc1, yc1, xc2, yc2;
    vhash *page, *sect, *p1, *p2;
    vscalar *elt;

    /* Initialise -- one section per page */
    pages = vl_create();
    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        xlen = vh_iget(sect, "XLEN");
        ylen = vh_iget(sect, "YLEN");

        page = vh_create();
        vh_istore(page, "XLEN", xlen);
        vh_istore(page, "YLEN", ylen);
        vl_ppush(pages, page);

        psects = vl_create();
        vh_pstore(page, "SECTS", psects);
        vl_ppush(psects, sect);
    }

    ratio = (double) xmax / ymax;

    /* Pack sections */
    do {
        pos = packed = 0;
        newpages = vl_create();

        while (pos < vl_length(pages)) {
            /* Get next page */
            p1 = vl_pget(pages, pos);
            x1 = vh_iget(p1, "XLEN");
            y1 = vh_iget(p1, "YLEN");

            /* Check if it's better off rotated */
            vh_istore(p1, "ROTATE", ((x1 < y1 && xmax > ymax) ||
                                     (x1 > y1 && xmax < ymax)));

            /* Check if this is the last page */
            if (pos + 1 == vl_length(pages)) {
                vl_ppush(newpages, p1);
                break;
            }

            /* Get following page */
            p2 = vl_pget(pages, pos + 1);
            x2 = vh_iget(p2, "XLEN");
            y2 = vh_iget(p2, "YLEN");

            /* Try combining pages in X direction */
            xc1 = x1 + x2 + border;
            yc1 = MAX(y1, y2);
            v1 = (xc1 <= xmax && yc1 <= ymax);
            r1 = (double) xc1 / yc1;

            /* Try combining pages in Y direction */
            xc2 = MAX(x1, x2);
            yc2 = y1 + y2 + border;
            v2 = (xc2 <= xmax && yc2 <= ymax);
            r2 = (double) xc2 / yc2;

            /* See which is best */
            if (v1 && v2) {
                if (ABS(ratio - r1) < ABS(ratio - r2))
                    v2 = 0;
                else
                    v1 = 0;
            }

            /* Just copy page if nothing can be done */
            if (!v1 && !v2) {
                vl_ppush(newpages, p1);
                pos++;
                continue;
            }

            /* Create merged page */
            page = vh_create();
            psects = vl_create();
            vh_pstore(page, "SECTS", psects);
            xo1 = yo1 = xo2 = yo2 = 0;

            if (v1) {
                vh_istore(page, "XLEN", xc1);
                vh_istore(page, "YLEN", yc1);
                xo2 = x1 + border;

                if (y1 < y2)
                    yo1 = (yc1 - y1) / 2;
                else
                    yo2 = (yc1 - y2) / 2;
            }

            if (v2) {
                vh_istore(page, "XLEN", xc2);
                vh_istore(page, "YLEN", yc2);
                yo1 = y2 + border;

                if (x1 < x2)
                    xo1 = (xc2 - x1) / 2;
                else
                    xo2 = (xc2 - x2) / 2;
            }

            /* Copy sections to new page, updating offsets */
            opsects = vh_pget(p1, "SECTS");
            vl_foreach(elt, opsects) {
                sect = vs_pget(elt);
                vl_ppush(psects, sect);
                xo = vh_iget(sect, "XOFF");
                vh_dstore(sect, "XOFF", xo + xo1);
                yo = vh_iget(sect, "YOFF");
                vh_dstore(sect, "YOFF", yo + yo1);
            }

            opsects = vh_pget(p2, "SECTS");
            vl_foreach(elt, opsects) {
                sect = vs_pget(elt);
                vl_ppush(psects, sect);
                xo = vh_iget(sect, "XOFF");
                vh_dstore(sect, "XOFF", xo + xo2);
                yo = vh_iget(sect, "YOFF");
                vh_dstore(sect, "YOFF", yo + yo2);
            }

            /* Get rid of old pages */
            vh_destroy(p1);
            vh_destroy(p2);

            /* Add merged page to list and go to next page pair */
            vl_ppush(newpages, page);
            pos += 2;
            packed++;
        }

        /* Switch to new page list */
        vl_destroy(pages);
        pages = newpages;
    } while (packed);

    /* Give each section its page info and clean up */
    num = 0;
    vl_foreach(elt, pages) {
        page = vs_pget(elt);
        psects = vh_pget(page, "SECTS");
        xlen = vh_iget(page, "XLEN");
        ylen = vh_iget(page, "YLEN");
        rflag = vh_iget(page, "ROTATE");

        num++;
        vl_foreach(elt, psects) {
            sect = vs_pget(elt);
            vh_istore(sect, "PAGE", num);
            vh_istore(sect, "PXLEN", xlen);
            vh_istore(sect, "PYLEN", ylen);
            vh_istore(sect, "ROTATE", rflag);
        }

        vh_destroy(page);
    }

    vl_destroy(pages);
    return num;
}

/* Set a scalar variable */
void
set_var(char *driver, char *type, char *var, vscalar *val)
{
    char *key = var_encode(driver, type, mapnum, var);

    if (val != NULL)
        vh_store(vars, key, val);
    else
        vh_delete(vars, key);
}

/* Set up room names */
void
setup_room_names(int jflag, int tflag)
{
    vhash *room, *join, *from, *to;
    char tag[10], *name;
    int jnum = 0;
    vscalar *elt;

    /* Add join numbers if required */
    if (jflag) {
        vl_foreach(elt, joins) {
            join = vs_pget(elt);
            if (vh_iget(join, "HIDDEN"))
                continue;

            from = vh_pget(join, "FROM");
            to = vh_pget(join, "TO");

            sprintf(tag, " (%d)", ++jnum);

            name = vh_sgetref(from, "RDESC");
            strcpy(buf, (name == NULL ? vh_sgetref(from, "DESC") : name));
            strcat(buf, tag);
            vh_sstore(from, "RDESC", buf);

            name = vh_sgetref(to, "RDESC");
            strcpy(buf, (name == NULL ? vh_sgetref(to, "DESC") : name));
            strcat(buf, tag);
            vh_sstore(to, "RDESC", buf);
        }
    }

    /* Set room names of rooms that don't have one yet */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        if (!vh_exists(room, "RDESC"))
            vh_sstore(room, "RDESC", vh_sgetref(room, "DESC"));
    }

    /* Add tag names if required */
    if (tflag) {
        vl_foreach(elt, rooms) {
            room = vs_pget(elt);
            if (vh_exists(room, "TAG")) {
                sprintf(buf, "%s [%s]", vh_sgetref(room, "RDESC"),
                        vh_sgetref(room, "TAG"));
                vh_sstore(room, "RDESC", buf);
            }
        }
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
