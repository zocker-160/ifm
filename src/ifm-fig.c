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
#define MAPY(y) (fig_height - (fig_origin_y + room_size * (fig_yoff + (y))))

/* Figure objects */
static vhash *fig = NULL;
static vhash *fig_section = NULL;
static vhash *fig_room = NULL;

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

/* Internal functions */
static void set_colour(vhash *object, char *colour);
static void set_fillcolour(vhash *object, char *colour);

/* Map functions */
void
fig_map_start(void)
{
    float ratio, tmp, scale = 1.0, xscale, yscale;
    int ylen, width, height, orient;
    vhash *sect, *box;
    vscalar *elt;
    char *title;

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
        fig_debug("trying map size: %d x %d", width, height);

        if (orient != FIG_LANDSCAPE && pack_sections(width, height, 1) == 1) {
            orient = FIG_PORTRAIT;
            fig_debug("using portrait");
            break;
        }

        if (orient != FIG_PORTRAIT && pack_sections(height, width, 1) == 1) {
            orient = FIG_LANDSCAPE;
            tmp = page_width;
            page_width = page_height;
            page_height = tmp;
            fig_debug("using landscape");
            break;
        }

        width++;
        height = (int) (width * ratio) + 1;
    }

    /* Find map size from first section that's output */
    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        if (!vh_iget(sect, "NOPRINT")) {
            width = vh_iget(sect, "PXLEN");
            height = vh_iget(sect, "PYLEN");
            vl_break(sects);
            break;
        }
    }

    /* Set dimensions and offsets */
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

    fig_debug("map size: %d x %d", width, height);
    fig_debug("room size: %g", room_size);
    fig_debug("page size: %g x %g", page_width, page_height);
    fig_debug("fig size: %g x %g", fig_width, fig_height);

    fig_origin_x = (page_width - width * room_size) / 2;
    fig_origin_y = (page_height - height * room_size) / 2;
    fig_origin_x = V_MAX(fig_origin_x, page_margin);
    fig_origin_y = V_MAX(fig_origin_y, page_margin);

    fig_debug("page margin: %g", page_margin);
    fig_debug("fig origin: %g x %g", fig_origin_x, fig_origin_y);

    if (var_int("fit_page")) {
        xscale = (page_width - 2 * page_margin) / fig_width;
        yscale = (page_height - 2 * page_margin) / fig_height;
        if (xscale < 1.0 || yscale < 1.0) {
            scale = V_MIN(xscale, yscale);
            fig_debug("scaling by %g", scale);
        }
    }

    /* Initialise figure */
    fig = fig_create(FIG_METRIC, scale);
    fig_set_orientation(fig, orient);
    fig_set_papersize(fig, page_size);

#if 0
    /* Draw border if required */
    if (show_border) {
        box = fig_create_box(fig,
                             page_margin, page_margin,
                             fig_width, fig_height);
        set_colour(box, page_border_colour);
        set_fillcolour(box, page_background_colour);
        fig_set_depth(box, 900);
    }

    /* Add title if required */
    if (show_title && vh_exists(map, "TITLE")) {
        /* FINISH ME */
    }
#endif
}

void
fig_map_section(vhash *sect)
{
    int xlen, ylen;
    vhash *text;
    float x, y;

    /* Create section object */
    fig_section = fig_create_compound(fig);

    /* Set section offsets */
    fig_xoff = vh_dget(sect, "XOFF");
    fig_yoff = vh_dget(sect, "YOFF");
    fig_debug("offsets: %g, %g", fig_xoff, fig_yoff);

    /* Print title if required */
    if (vh_exists(sect, "TITLE")) {
        x = vh_dget(sect, "XLEN") / 2;
        y = vh_dget(sect, "YLEN");
        text = fig_create_text(fig_section,
                               MAPX(x), MAPY(y - 1.5),
                               vh_sgetref(sect, "TITLE"));
        fig_set_font(text, map_text_font, map_text_fontsize);
        fig_set_depth(text, 250);
        set_colour(text, map_text_colour);
    }
}

void
fig_map_room(vhash *room)
{
    float xp, yp, width, height, xborder = 0.02, yborder = 0.02;
    static vlist *px = NULL, *py = NULL;
    vhash *line, *box, *text;
    vlist *items, *ex, *ey;
    char *itemlist = NULL;
    int x, y;

    /* Create room object */
    fig_room = fig_create_compound(fig_section);

    /* Get coords */
    x = vh_iget(room, "X");
    y = vh_iget(room, "Y");

    /* Draw room box */
    xp = x + (1 - room_width) / 2;
    yp = y + (1 - room_height) / 2;
    width = room_size * room_width;
    height = room_size * room_height;

    fig_debug("room at %d %d, offset %g %g, size %g %g",
              x, y, xp, yp, width, height);

    box = fig_create_box(fig_room, MAPX(xp), MAPY(yp), width, height);

    set_colour(box, room_border_colour);
    set_fillcolour(box, room_colour);
    fig_set_linewidth(box, room_border_width);

    if (room_border_dashed)
        fig_set_linestyle(box, FIG_DASH);

    /* Draw room shadow if required */
    if (room_shadow_xoff != 0 || room_shadow_yoff != 0) {
        box = fig_create_box(fig_room,
                             MAPX(xp - room_shadow_xoff),
                             MAPY(yp - room_shadow_yoff),
                             width, height);
        fig_set_depth(box, 200);
        set_colour(box, room_shadow_colour);
        set_fillcolour(box, room_shadow_colour);
    }

    /* Get item list (if any) */
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

    /* Draw room text (and items if any) */
    if (itemlist == NULL) {
        text = fig_create_textbox(fig_room, room_text_font,
                                  room_text_fontsize,
                                  FIG_JUSTIFY_CENTRE,
                                  MAPX(xp + xborder),
                                  MAPY(yp - yborder),
                                  width * (1 - 2 * xborder),
                                  height * (1 - 2 * yborder),
                                  "%s", vh_sgetref(room, "DESC"));

        fig_set_depth(text, 50);
        set_colour(text, room_text_colour);
    } else {
        text = fig_create_textbox(fig_room, room_text_font,
                                  room_text_fontsize,
                                  FIG_JUSTIFY_CENTRE,
                                  MAPX(xp + xborder),
                                  MAPY(yp - yborder),
                                  width * (1 - 2 * xborder),
                                  height * (1 - 2 * yborder) / 2,
                                  "%s", vh_sgetref(room, "DESC"));

        fig_set_depth(text, 50);
        set_colour(text, room_text_colour);

        text = fig_create_textbox(fig_room, item_text_font,
                                  item_text_fontsize,
                                  FIG_JUSTIFY_CENTRE,
                                  MAPX(xp + xborder),
                                  MAPY(yp - yborder - 0.3),
                                  width * (1 - 2 * xborder),
                                  height * (1 - 2 * yborder) / 2,
                                  "%s", itemlist);            

        fig_set_depth(text, 50);
        set_colour(text, item_text_colour);
    }

    /* Draw room exits (if any) */
    ex = vh_pget(room, "EX");
    ey = vh_pget(room, "EY");

    if (ex != NULL && ey != NULL) {
        double x1, y1, x2, y2, xoff = 0.5, yoff = 0.5 - room_height;

        vl_init(px);
        vl_init(py);

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

            line = fig_create_line(fig_room,
                                   MAPX(x1 + xoff), MAPY(y1 + yoff),
                                   MAPX(x2 + xoff), MAPY(y2 + yoff));

            set_colour(line, room_exit_colour);
            fig_set_linewidth(line, room_exit_width);
            fig_set_depth(line, 150);
        }
    }
}

void
fig_map_link(vhash *link)
{
    int go = vh_iget(link, "GO");
    int updown = (go == D_UP || go == D_DOWN);
    int inout = (go == D_IN || go == D_OUT);

    vlist *x = vh_pget(link, "X");
    vlist *y = vh_pget(link, "Y");

    int i, np = vl_length(x);
    vhash *line, *text;
    double xp, yp;

    /* Draw link line */
    truncate_points(x, y, room_width, room_height);

    if (link_spline && np > 2)
        line = fig_create_spline(fig_section, FIG_OPEN_XSPLINE);
    else
        line = fig_create_polyline(fig_section, FIG_LINE);

    for (i = 0; i < np; i++) {
        xp = vl_dget(x, i) + 0.5;
        yp = vl_dget(y, i) + 0.5 - room_height;
        fig_create_point(line, MAPX(xp), MAPY(yp));
    }

    fig_set_linewidth(line, link_line_width);
    set_colour(line, link_colour);

    if (link_dashed)
        fig_set_linestyle(line, FIG_DASH);

    fig_set_depth(line, 150);
    fig_set_arrow(line, vh_iget(link, "ONEWAY"), 0);

    /* Add text if required */
    if (updown || inout) {
        xp = (vl_dget(x, 0) + vl_dget(x, 1)) / 2;
        yp = (vl_dget(y, 0) + vl_dget(y, 1)) / 2;

        xp += 0.5;
        yp += 0.5 - room_height;

        text = fig_create_text(fig_section, MAPX(xp), MAPY(yp),
                               updown ? link_updown_string : link_inout_string);

        fig_set_font(text, link_text_font, link_text_fontsize);
        fig_set_depth(text, 100);
        set_colour(text, link_text_colour);
        set_fillcolour(text, page_background_colour);
    }
}

void
fig_map_finish(void)
{
    /* Write figure */
    fig_write_figure(fig, stdout);
}

/* Set the colour of an object */
static void
set_colour(vhash *object, char *colour)
{
    float r, g, b;

    if (sscanf(colour, "%f %f %f", &r, &g, &b) == 3)
        fig_set_colour(object, r, g, b);
}

/* Set the fill colour of an object */
static void
set_fillcolour(vhash *object, char *colour)
{
    float r, g, b;

    if (sscanf(colour, "%f %f %f", &r, &g, &b) == 3)
        fig_set_fillcolour(object, r, g, b);
}
