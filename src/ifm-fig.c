/* Fig output driver */

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
#include <fig.h>

#include "ifm-driver.h"
#include "ifm-fig.h"
#include "ifm-main.h"
#include "ifm-map.h"
#include "ifm-util.h"
#include "ifm-vars.h"

#define MAPX(x) (fig_origin_x + room_size * (fig_xoff + (x)))

#if 0
#define MAPY(y) (fig_origin_y + room_size * (fig_yoff + (y)))
#else
#define MAPY(y) (fig_height - fig_origin_y - room_size * ((y) + fig_yoff))
#endif

/* Figure */
static vhash *fig = NULL;

/* Page dimensions */
static float fig_width, fig_height;
static float fig_origin_x, fig_origin_y;

/* Room offsets */
static float fig_xoff = 0.0, fig_yoff = 0.0;

/* Map function list */
mapfuncs fig_mapfuncs = {
    fig_map_start,
    fig_map_section,
    fig_map_room,
    fig_map_link,
    NULL,
    NULL,
    fig_map_finish
};

/* Debugging */
static void
msg(char *fmt, ...)
{
    char buf[BUFSIZ];
    V_VPRINT(buf, fmt);
    fprintf(stderr, "%s\n", buf);
}

/* Map functions */
void
fig_map_start(void)
{
    int ylen, width, height, orient;
    double ratio, tmp;
    vscalar *elt;
    char *title;
    vhash *sect;

    /* Set map variables */
    set_map_vars();

    /* Allow title space for sections with titles */
    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        if (vh_exists(sect, "TITLE")) {
            ylen = vh_iget(sect, "YLEN");
            vh_istore(sect, "YLEN", ylen + 1);
        }
    }

    /* Set room names */
    setup_room_names(1, show_tags);

    /* Determine orientation */
    if (VAR_DEF("page_rotate"))
        orient = var_int("page_rotate") ? FIG_LANDSCAPE : FIG_PORTRAIT;
    else
        orient = FIG_UNDEF;

    /* Get initial dimensions, in rooms */
    fig_width = page_width - 2 * page_margin;
    fig_height = page_height - 2 * page_margin;

    width = (int) (fig_width / room_size) + 1;
    height = (int) (fig_height / room_size) + 1;
    ratio = page_height / page_width;

    /* Increase dimensions until sections fit on one page */
    while (1) {
        msg("Trying: %d x %d", width, height);

        if (orient != FIG_LANDSCAPE &&
            pack_sections(width, height, 1) == 1) {
            orient = FIG_PORTRAIT;
            msg("Using portrait");
            break;
        }

        if (orient != FIG_PORTRAIT &&
            pack_sections(height, width, 1) == 1) {
            orient = FIG_LANDSCAPE;
            tmp = page_width;
            page_width = page_height;
            page_height = tmp;
            msg("Using landscape");
            break;
        }

        width++;
        height = (int) (width * ratio) + 1;
    }

    sect = vl_phead(sects);
    width = vh_iget(sect, "PXLEN");
    height = vh_iget(sect, "PYLEN");

    if (orient == FIG_PORTRAIT) {
        fig_width = width * room_size;
        fig_height = height * room_size;
    } else {
        fig_width = height * room_size;
        fig_height = width * room_size;
    }

    fig_width += 2 * page_margin;
    fig_height += 2 * page_margin;
    fig_width = V_MAX(fig_width, page_width - 2 * page_margin);
    fig_height = V_MAX(fig_height, page_height - 2 * page_margin);

    msg("Map size: %d x %d", width, height);
    msg("Room size: %g", room_size);
    msg("Page size: %g x %g", page_width, page_height);
    msg("Fig size: %g x %g", fig_width, fig_height);

    fig_origin_x = (page_width - width * room_size) / 2;
    fig_origin_y = (page_height - height * room_size) / 2;
    fig_origin_x = V_MAX(fig_origin_x, page_margin);
    fig_origin_y = V_MAX(fig_origin_y, page_margin);
    msg("Page margin: %g", page_margin);
    msg("Fig origin: %g x %g", fig_origin_x, fig_origin_y);

    /* Initialise figure */
    fig = fig_create(FIG_METRIC);
    fig_set_orientation(fig, orient);
    fig_set_papersize(fig, page_size);

    /* Draw background */
    fig_create_box(fig, page_margin, page_margin, fig_width, fig_height);

    /* Add title if required */
    if (var_int("show_title")) {
        if (vh_exists(map, "TITLE"))
            title = vh_sgetref(map, "TITLE");
        else
            title = "Interactive Fiction map";

        /* FINISH ME */
    }
}

void
fig_map_section(vhash *sect)
{
    int xlen, ylen;
    vhash *text;
    float x, y;

    /* Set section offsets */
    fig_xoff = vh_dget(sect, "XOFF");
    fig_yoff = vh_dget(sect, "YOFF");
    msg("Offsets: %g, %g", fig_xoff, fig_yoff);

    /* Print title if required */
    if (vh_exists(sect, "TITLE")) {
        x = vh_dget(sect, "XLEN") / 2;
        y = vh_dget(sect, "YLEN");
        text = fig_create_text(fig, MAPX(x), MAPY(y - 1),
                               vh_sgetref(sect, "TITLE"));
        fig_set_font(text, "Times Bold", 20);
    }
}

void
fig_map_room(vhash *room)
{
    static vlist *px = NULL, *py = NULL;
    vlist *items, *ex, *ey;
    char *itemlist = NULL;
    vhash *line;
    int x, y;

    set_room_vars();

    /* Get coords */
    x = vh_iget(room, "X");
    y = vh_iget(room, "Y");
    msg("Room at: %d, %d", x, y);

    /* Draw room box */
    fig_create_box(fig,
                   MAPX(x + (1 - room_width) / 2),
                   MAPY(y + (1 - room_height) / 2),
                   room_size * room_width, room_size * room_height);

    /* Write item list (if any) */
    items = vh_pget(room, "ITEMS");
    if (items != NULL && vl_length(items) > 0) {
        vscalar *elt;
        vhash *item;
        vlist *list;

        list = vl_create();
        vl_foreach(elt, items) {
            item = vs_pget(elt);
            if (!vh_iget(item, "HIDDEN"))
                vl_spush(list, vh_sgetref(item, "DESC"));
        }

        if (vl_length(list) > 0)
            itemlist = vl_join(list, ", ");
        vl_destroy(list);
    }

    /* Write room exits (if any) */
    ex = vh_pget(room, "EX");
    ey = vh_pget(room, "EY");
    if (ex != NULL) {
        double x1, y1, x2, y2;

        if (px == NULL) {
            px = vl_create();
            py = vl_create();
        }

        while (vl_length(ex) > 0) {
            vl_istore(px, 0, x);
            vl_istore(py, 0, y);
            vl_istore(px, 1, x + vl_ishift(ex));
            vl_istore(py, 1, y + vl_ishift(ey));
            truncate_points(px, py, room_width, room_height);
            x1 = vl_dget(px, 0);
            y1 = vl_dget(py, 0);
            x2 = vl_dget(px, 1);
            y2 = vl_dget(py, 1);

            x2 = x1 + 0.35 * (x2 - x1);
            y2 = y1 + 0.35 * (y2 - y1);

            /* Might have to adjust these */
            line = fig_create_line(fig,
                                   MAPX(x1), MAPY(y1),
                                   MAPX(x2), MAPY(y2));
        }
    }
}

void
fig_map_link(vhash *link)
{
    int oneway = vh_iget(link, "ONEWAY");
    int go = vh_iget(link, "GO");
    int updown = (go == D_UP || go == D_DOWN);
    int inout = (go == D_IN || go == D_OUT);
    vlist *x = vh_pget(link, "X");
    vlist *y = vh_pget(link, "Y");
    int i, np = vl_length(x);
    vhash *spline;
    double xp, yp;

    set_link_vars();

    truncate_points(x, y, room_width, room_height);
    spline = fig_create_spline(fig, FIG_OPEN_XSPLINE);

    for (i = 0; i < np; i++) {
        xp = vl_dget(x, i) + 0.5;
        yp = vl_dget(y, i) + 0.5 - room_height;
        msg("Point: %g, %g", xp, yp);
        fig_create_point(spline, MAPX(xp), MAPY(yp));
    }
}

void
fig_map_finish(void)
{
    /* Write figure */
    fig_write_figure(fig, stdout);
}
