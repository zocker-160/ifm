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

#define MAPX(x) (fig_origin_x + room_size * (fig_xoff + x))
#define MAPY(y) (fig_origin_y + room_size * (fig_yoff + y))

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
    fig_map_endsection,
    fig_map_finish
};

/* Map functions */
void
fig_map_start(void)
{
    int ylen, width, height, orient;
    double ratio;
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

    /* Get initial dimensions, in rooms */
    fig_width = page_width - 2 * page_margin;
    fig_height = page_height - 2 * page_margin;

    width = (int) (fig_width / room_size) + 1;
    height = (int) (fig_height / room_size) + 1;
    ratio = page_height / page_width;

    /* Increase dimensions until sections fit on one page */
    while (pack_sections(width, height, 1) > 1) {
        width++;
        height = (int) (width * ratio) + 1;
    }

    fig_width = width * room_size;
    fig_height = height * room_size;
    page_width = 2 * page_margin + fig_width;
    page_height = 2 * page_margin + fig_height;

    fig_origin_x = page_width / 2 - width * room_size;
    fig_origin_y = page_height / 2 - height * room_size;
    fig_origin_x = V_MAX(fig_origin_x, page_margin);
    fig_origin_y = V_MAX(fig_origin_y, page_margin);

    /* Determine orientation */
    if (VAR_DEF("page_rotate"))
        orient = var_int("page_rotate") ? FIG_LANDSCAPE : FIG_PORTRAIT;
    else if (width < height)
        orient = FIG_PORTRAIT;
    else
        orient = FIG_LANDSCAPE;

    /* Initialise figure */
    fig = fig_create(FIG_METRIC);
    fig_set_orientation(fig, orient);
    fig_set_papersize(fig, page_size);

    /* Draw background */
    fig_create_box(fig,
                   page_margin, page_margin,
                   page_width - page_margin, page_height - page_margin);

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
    double xpos, ypos;
    int xlen, ylen;

    /* Set section offsets */
    fig_xoff = vh_dget(sect, "XOFF");
    fig_yoff = vh_dget(sect, "YOFF");

    /* Print title if required */
    if (vh_exists(sect, "TITLE")) {
        xlen = vh_iget(sect, "XLEN");
        xpos = (double) (xlen - 1) / 2;
        ylen = vh_iget(sect, "YLEN");
        ypos = ylen - 1;
    }
}

void
fig_map_room(vhash *room)
{
    static vlist *px = NULL, *py = NULL;
    vlist *items, *ex, *ey;
    char *itemlist = NULL;
    int x, y;

    /* Write coords */
    x = vh_iget(room, "X");
    y = vh_iget(room, "Y");

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
    vlist *x, *y;
    int i, np;

    x = vh_pget(link, "X");
    y = vh_pget(link, "Y");
    truncate_points(x, y, room_width, room_height);
}

void
fig_map_endsection(void)
{
    /* Nothing to do */
}

void
fig_map_finish(void)
{
    /* Write figure */
    fig_write_figure(fig, stdout);
}
