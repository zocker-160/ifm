/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* PostScript output driver */

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
    "A3",       11.69,  16.54,
    "A4",       8.27,   11.69,
    "A",        8.5,    11.0,
    "B",        11.0,   17.0,
    "C",        17.0,   22.0,
    "Legal",    8.5,    14.0,
    "Letter",   8.5,    11.0,
    NULL,       0.0,    0.0
};

/* Internal variables */
static int ps_rotate = 0;       /* Whether to rotate pages */
static int ps_rotflag = 0;      /* Whether to override auto-rotation */
static int ps_pagenum = 0;      /* Current page */
static double ps_xoff;          /* Current X offset */
static double ps_yoff;          /* Current Y offset */
static double ps_roomwidth;     /* Current room width factor */
static double ps_roomheight;    /* Current room height factor */

/* Internal functions */
static char *ps_string(char *str);

/* Map functions */
void
ps_map_start(void)
{
    int ylen, c, num_pages, width, height, i, found;
    double page_width, page_height;
    char *title, *pagesize;
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
    setup_room_names(1, get_int("show_tags", 0));

    /* Pack sections */
    width = get_int("map_width", 8);
    height = get_int("map_height", 12);
    num_pages = pack_sections(width, height, 1);

    /* Check overriding of page rotation */
    ps_rotflag = (get_var("page_rotate") != NULL);
    if (ps_rotflag)
        ps_rotate = get_int("page_rotate", 0);

    /* Get paper size */
    pagesize = get_string("page_size", "A4");

    for (i = 0, found = 0; paper_sizes[i].name != NULL; i++) {
        if (!strcasecmp(pagesize, paper_sizes[i].name)) {
            page_width = paper_sizes[i].width;
            page_height = paper_sizes[i].height;
            found = 1;
        }
    }
    
    if (!found)
        warn("invalid page size: %s", pagesize);

    /* Allow override */
    page_width = get_real("page_width", page_width);
    page_height = get_real("page_height", page_height);

    /* Print header */
    title = get_string("title", NULL);

    printf("%%!PS-Adobe-3.0\n");
    printf("%%%%Title: %s\n",
           title != NULL ? title : "Interactive Fiction map");
    printf("%%%%Creator: IFM v%s\n", VERSION);
    printf("%%%%Pages: %d\n", num_pages);
    printf("%%%%EndComments\n");

    /* Print PostScript prolog */
    fp = open_libfile(get_string("prolog_file", PS_PROLOG));
    while ((c = fgetc(fp)) != EOF)
        putchar(c);
    fclose(fp);

    /* Print variables */
    printf("/origpagewidth %g inch def\n", page_width);
    printf("/origpageheight %g inch def\n", page_height);
    printf("/pagemargin %g inch def\n", get_real("page_margin", 0.7));

    printf("/origmapwidth %d def\n", width);
    printf("/origmapheight %d def\n", height);

    printf("/titlefont /%s def\n", get_string("title_font", "Times-Bold"));
    printf("/titlefontsize %g def\n", get_real("title_fontsize", 18));

    if (title != NULL)
        printf("/titlestring %s def\n", ps_string(title));

    printf("/showtitle %s def\n",
           title != NULL && get_int("show_title", 1) ? "true" : "false");

    printf("/showborder %s def\n",
           get_int("show_border", 0) ? "true" : "false");

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
    ps_roomwidth = get_real("room_width", 0.8);
    ps_roomheight = get_real("room_height", 0.65);

    /* Start a new page if required */
    if (page != ps_pagenum) {
        if (ps_pagenum > 0)
            printf("\nendpage\n");

        ps_pagenum = page;
        printf("\n%%%%Page: %d\n\n", ps_pagenum);

        printf("/mapfont /%s def\n", get_string("map_font", "Times-Bold"));
        printf("/mapfontsize %g def\n", get_real("map_fontsize", 14));

        printf("/roomwidth %g def\n", ps_roomwidth);
        printf("/roomheight %g def\n", ps_roomheight);

        printf("/roomfont /%s def\n", get_string("room_font", "Times-Bold"));
        printf("/roomfontsize %g def\n", get_real("room_fontsize", 10));

        printf("/itemfont /%s def\n", get_string("item_font", "Times-Italic"));
        printf("/itemfontsize %g def\n", get_real("item_fontsize", 6));

        printf("/labelfont /%s def\n", get_string("label_font", "Times-Roman"));
        printf("/labelfontsize %g def\n", get_real("label_fontsize", 6));

        printf("/roomshading %g def\n", 1 - get_real("room_shading", 0.0));

        printf("/showitems %s def\n",
               get_int("show_items", 0) ? "true" : "false");

        printf("/roomlinewidth %g def\n", get_real("room_linewidth", 0.8));
        printf("/linklinewidth %g def\n", get_real("link_linewidth", 0.8));
        printf("/exitlinewidth %g def\n", get_real("exit_linewidth", 1.2));

        printf("/arrowsize %g def\n", get_real("link_arrowsize", 0.08));

        rotate = (ps_rotflag ? ps_rotate : vh_iget(sect, "ROTATE"));

        printf("\n%d %d %s beginpage\n",
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
        printf("\n%s %g %g map\n", ps_string(vh_sgetref(sect, "TITLE")),
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
    printf("%s %g %g",
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
        printf(" %s true", ps_string(itemlist));
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
            truncate_points(px, py, ps_roomwidth, ps_roomheight);
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
    truncate_points(x, y, ps_roomwidth, ps_roomheight);

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
    printf("\nendpage\n");
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
