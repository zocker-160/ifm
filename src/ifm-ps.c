/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* PostScript output driver */

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
#include "ifm-main.h"
#include "ifm-map.h"
#include "ifm-util.h"
#include "ifm-vars.h"
#include "ifm-ps.h"

/* Map function list */
mapfuncs ps_mapfuncs = {
    ps_map_start,
    ps_map_section,
    ps_map_room,
    ps_map_link,
    NULL,
    ps_map_endsection,
    ps_map_finish
};

/* Standard paper sizes */
static struct paper_st {
    char *name;
    double width, height;
} paper_sizes[] = {
    "A3",       29.7,   42.01,
    "A4",       21.0,   29.7,
    "A",        21.59,  27.94,
    "B",        27.94,  43.18,
    "C",        43.18,  55.88,
    "Legal",    21.59,  35.56,
    "Letter",   21.59,  27.94,
    NULL,       0.0,    0.0
};

/* Internal variables */
static int ps_rotate = 0;       /* Whether to rotate pages */
static int ps_rotflag = 0;      /* Whether to override auto-rotation */
static int ps_pagenum = 0;      /* Current page */

static double ps_xoff;          /* Current X offset */
static double ps_yoff;          /* Current Y offset */
static double ps_page_width;    /* Width of a page (cm) */
static double ps_page_height;   /* Height of a page (cm) */
static double ps_room_width;    /* Current room width factor */
static double ps_room_height;   /* Current room height factor */
static double ps_font_scale;    /* Font scaling factor */

/* Internal functions */
static int ps_getsize(char *pagesize, double *width, double *height);
static char *ps_string(char *str);

/* Map functions */
void
ps_map_start(void)
{
    int ylen, c, num_pages, width, height;
    char *title, *pagesize;
    double roomsize;
    vscalar *elt;
    vhash *sect;
    FILE *fp;

    /* Allow title space for sections with titles */
    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        if (vh_exists(sect, "TITLE")) {
            ylen = vh_iget(sect, "YLEN");
            vh_istore(sect, "YLEN", ylen + 1);
        }
    }

    /* Set room names */
    setup_room_names(1, var_int("show_tags"));

    /* Check overriding of page rotation */
    ps_rotflag = VAR_DEF("page_rotate");
    if (ps_rotflag)
        ps_rotate = var_int("page_rotate");

    /* Get paper size */
    pagesize = var_string("page_size");
    if (!ps_getsize(pagesize, &ps_page_width, &ps_page_height))
        fatal("invalid page size: %s", pagesize);

    if (VAR_DEF("page_width"))
        ps_page_width = var_real("page_width");
    if (VAR_DEF("page_height"))
        ps_page_height = var_real("page_height");

    /* Get global font scaling factor */
    ps_font_scale = var_real("font_scale");
    ps_font_scale = V_MAX(ps_font_scale, 0.1);

    /* Get desired dimensions, in rooms */
    roomsize = var_real("room_size");
    roomsize = V_MAX(roomsize, 0.1);
    width = (int) (ps_page_width / roomsize) + 1;
    height = (int) (ps_page_height / roomsize) + 1;
    ps_room_width = var_real("room_width");
    ps_room_height = var_real("room_height");

    /* Pack sections */
    num_pages = pack_sections(width, height, 1);

    /* Print header */
    if (vh_exists(map, "TITLE"))
        title = vh_sgetref(map, "TITLE");
    else
        title = "Interactive Fiction map";

    printf("%%!PS-Adobe-3.0\n");
    put_string("%%%%Title: %s\n", title);
    printf("%%%%Creator: IFM v%s\n", VERSION);
    printf("%%%%Pages: %d\n", num_pages);
    printf("%%%%EndComments\n\n");

    /* Print PostScript prolog */
    fp = open_file(var_string("prolog_file"), 1, 1);
    while ((c = fgetc(fp)) != EOF)
        putchar(c);
    fclose(fp);

    /* Page variables */
    printf("/pagemargin %g cm def\n",
           var_real("page_margin"));
    printf("/origpagewidth %g cm def\n",
           ps_page_width);
    printf("/origpageheight %g cm def\n",
           ps_page_height);
    printf("/origmapwidth %d def\n",
           width);
    printf("/origmapheight %d def\n",
           height);
    printf("/showborder %s def\n",
           var_int("show_border") ? "true" : "false");
    printf("/bordercolour [%s] def\n",
           var_colour("page_border_colour"));
    printf("/backgroundcolour [%s] def\n",
           var_colour("page_background_colour"));

    /* Title variables */
    if (title != NULL) {
        printf("/showtitle %s def\n",
               var_int("show_title") ? "true" : "false");
        put_string("/titlestring %s def\n",
                   ps_string(title));
        printf("/titlefont /%s def\n",
               var_string("title_font"));
        printf("/titlefontsize %g def\n",
               var_real("title_fontsize") * ps_font_scale);
        printf("/titlecolour [%s] def\n",
               var_colour("title_colour"));
    } else {
        printf("/showtitle false def\n");
    }

    /* Map variables */
    printf("/maptextcolour [%s] def\n",
           var_colour("map_text_colour"));
    printf("/mapfont /%s def\n",
           var_string("map_text_font"));
    printf("/mapfontsize %g def\n",
           var_real("map_text_fontsize") * ps_font_scale);

    /* Room variables */
    printf("/roomwidth %g def\n",
           ps_room_width);
    printf("/roomheight %g def\n",
           ps_room_height);
    printf("/roomfont /%s def\n",
           var_string("room_text_font"));
    printf("/roomfontsize %g def\n",
           var_real("room_text_fontsize") * ps_font_scale);
    printf("/roomcolour [%s] def\n",
           var_colour("room_colour"));
    printf("/roomtextcolour [%s] def\n",
           var_colour("room_text_colour"));
    printf("/roombordercolour [%s] def\n",
           var_colour("room_border_colour"));
    printf("/roomlinewidth %g def\n",
           var_real("room_border_width"));
    printf("/roompuzzlecolour [%s] def\n",
           var_colour("room_puzzle_colour"));
    printf("/roomshadowx %g def\n",
           var_real("room_shadow_xoff"));
    printf("/roomshadowy %g def\n",
           var_real("room_shadow_yoff"));
    printf("/roomshadowcolour [%s] def\n",
           var_colour("room_shadow_colour"));
    printf("/roomexitcolour [%s] def\n",
           var_colour("room_exit_colour"));
    printf("/roomexitlinewidth %g def\n",
           var_real("room_exit_width"));

    /* Item variables */
    printf("/showitems %s def\n",
           var_int("show_items") ? "true" : "false");
    printf("/itemfont /%s def\n",
           var_string("item_text_font"));
    printf("/itemfontsize %g def\n",
           var_real("item_text_fontsize") * ps_font_scale);
    printf("/itemtextcolour [%s] def\n",
           var_colour("item_text_colour"));

    /* Link variables */
    printf("/linkcolour [%s] def\n",
           var_colour("link_colour"));
    printf("/linktextcolour [%s] def\n",
           var_colour("link_text_colour"));
    printf("/linkspecialcolour [%s] def\n",
           var_colour("link_special_colour"));
    printf("/linkspecialdashed %s def\n",
           var_int("link_special_dashed") ? "true" : "false");
    printf("/linkarrowsize %g def\n",
           var_real("link_arrow_size"));
    printf("/linkfont /%s def\n",
           var_string("link_text_font"));
    printf("/linkfontsize %g def\n",
           var_real("link_text_fontsize") * ps_font_scale);
    printf("/linklinewidth %g def\n",
           var_real("link_line_width"));
    printf("/linkupdowntext %s def\n",
           ps_string(var_string("link_updown_string")));
    printf("/linkinouttext %s def\n",
           ps_string(var_string("link_inout_string")));

    printf("\n%%%%EndProlog\n");
}

void
ps_map_section(vhash *sect)
{
    int page, xlen, ylen, rotate;
    double xpos, ypos;

    /* Get section parameters */
    page = vh_iget(sect, "PAGE");
    ps_xoff = vh_dget(sect, "XOFF");
    ps_yoff = vh_dget(sect, "YOFF");

    /* Start a new page if required */
    if (page != ps_pagenum) {
        if (ps_pagenum > 0)
            printf("endpage\n");

        ps_pagenum = page;
        printf("\n%%%%Page: %d\n\n", ps_pagenum);

        rotate = (ps_rotflag ? ps_rotate : vh_iget(sect, "ROTATE"));

        printf("%d %d %s beginpage\n",
               vh_iget(sect, "PXLEN"),
               vh_iget(sect, "PYLEN"),
               (rotate ? "true" : "false"));
    }

    /* Print title if required */
    if (vh_exists(sect, "TITLE")) {
        xlen = vh_iget(sect, "XLEN");
        xpos = (double) (xlen - 1) / 2;
        ylen = vh_iget(sect, "YLEN");
        ypos = ylen - 1;
        put_string("%s %g %g map\n", ps_string(vh_sgetref(sect, "TITLE")),
                   xpos + ps_xoff, ypos + ps_yoff);
    }
}

void
ps_map_room(vhash *room)
{
    static vlist *px = NULL, *py = NULL;
    vlist *items, *ex, *ey;
    char *itemlist = NULL;
    int x, y;

    /* Write coords */
    x = vh_iget(room, "X");
    y = vh_iget(room, "Y");
    put_string("%s %g %g",
               ps_string(vh_sgetref(room, "RDESC")),
               x + ps_xoff, y + ps_yoff);

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
        put_string(" %s true", ps_string(itemlist));
    else
        printf(" false");

    printf(" %s", vh_iget(room, "PUZZLE") ? "true" : "false");
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
            truncate_points(px, py, ps_room_width, ps_room_height);
            x1 = vl_dget(px, 0);
            y1 = vl_dget(py, 0);
            x2 = vl_dget(px, 1);
            y2 = vl_dget(py, 1);

            x2 = x1 + 0.35 * (x2 - x1);
            y2 = y1 + 0.35 * (y2 - y1);

            printf("%g %g %g %g roomexit\n",
                   ps_xoff + x1, ps_yoff + y1,
                   ps_xoff + x2, ps_yoff + y2);
        }
    }
}

void
ps_map_link(vhash *link)
{
    int special = vh_iget(link, "SPECIAL");
    int oneway = vh_iget(link, "ONEWAY");
    int go = vh_iget(link, "GO");
    int updown = (go == D_UP || go == D_DOWN);
    int inout = (go == D_IN || go == D_OUT);
    vlist *x, *y;
    int i, np;

    x = vh_pget(link, "X");
    y = vh_pget(link, "Y");
    truncate_points(x, y, ps_room_width, ps_room_height);

    printf("[");
    np = vl_length(x);
    for (i = 0; i < np; i++)
        printf(" %g %g",
               vl_dget(x, i) + ps_xoff,
               vl_dget(y, i) + ps_yoff);
    printf(" ]");

    printf(" %s", (updown ? "true" : "false"));
    printf(" %s", (inout ? "true" : "false"));
    printf(" %s", (oneway ? "true" : "false"));
    printf(" %s", (special ? "true" : "false"));

    printf(" link\n");
}

void
ps_map_endsection(void)
{
    /* Nothing to do */
}

void
ps_map_finish(void)
{
    printf("endpage\n");
}

/* Get page dimensions given a page description */
static int
ps_getsize(char *pagesize, double *width, double *height)
{
    int i;

    for (i = 0; paper_sizes[i].name != NULL; i++) {
        if (!strcasecmp(pagesize, paper_sizes[i].name)) {
            *width = paper_sizes[i].width;
            *height = paper_sizes[i].height;
            return 1;
        }
    }

    return 0;
}

/* Return a string suitable for passing to PostScript */
static char *
ps_string(char *str)
{
    static vbuffer *b = NULL;

    if (b == NULL)
        b = vb_create();
    else
        vb_empty(b);

    vb_putc(b, '(');

    while (*str != '\0') {
        if (strchr("()\\", *str) != NULL)
            vb_putc(b, '\\');
        vb_putc(b, *str++);
    }

    vb_putc(b, ')');
    return vb_get(b);
}
