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

/* Room offsets */
static float fig_xoff, fig_yoff;

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
    int ylen, c, width, height;
    char *title, *pagesize;
    double room_size;
    vscalar *elt;
    vhash *sect;

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

    /* Get global font scaling factor */

#if 0
    /* Get desired dimensions, in rooms */
    room_size = V_MAX(room_size, 0.1);
    width = (int) (fig_page_width / room_size) + 1;
    height = (int) (fig_page_height / room_size) + 1;

    /* Pack sections */
    pack_sections(width, height, 1);
#endif

    /* Print header */
    if (vh_exists(map, "TITLE"))
        title = vh_sgetref(map, "TITLE");
    else
        title = "Interactive Fiction map";
}

void
fig_map_section(vhash *sect)
{
    int xlen, ylen;
    double xpos, ypos;

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

    if (itemlist != NULL)
        ;
    else
        printf(" false");

    printf(" room\n");

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

            printf("%g %g %g %g roomexit\n",
                   fig_xoff + x1, fig_yoff + y1,
                   fig_xoff + x2, fig_yoff + y2);
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

    printf("[");
    np = vl_length(x);
    for (i = 0; i < np; i++)
        printf(" %g %g",
               vl_dget(x, i) + fig_xoff,
               vl_dget(y, i) + fig_yoff);
    printf(" ]");

    printf(" %s", (updown ? "true" : "false"));
    printf(" %s", (inout ? "true" : "false"));
    printf(" %s", (oneway ? "true" : "false"));

    printf(" link\n");
}

void
fig_map_endsection(void)
{
    /* Nothing to do */
}

void
fig_map_finish(void)
{
    /* Nothing to do */
}
