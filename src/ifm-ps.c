/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
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
#include "ifm.h"
#include "ifm-parse.h"
#include "ifm-ps.h"

/* Map function list */
mapfuncs ps_mapfuncs = {
    ps_map_start,
    ps_map_section,
    ps_map_room,
    ps_map_link,
    ps_map_endsection,
    ps_map_finish
};

/* Internal variables */
static int ps_pagenum = 0;      /* Current page */
static double ps_xoff;          /* Current X offset */
static double ps_yoff;          /* Current Y offset */
static double ps_roomwidth;     /* Current room width factor */
static double ps_roomheight;    /* Current room height factor */

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static char *ps_string(char *str);

/* Map functions */
void
ps_map_start(void)
{
    int ylen, c, num_pages, width, height;
    vhash *sect, *join, *from, *to;
    char *title, *name, tag[10];
    vscalar *elt;
    int jnum = 0;
    FILE *fp;

    /* Allow title space for sections with titles */
    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        if (vh_exists(sect, "TITLE")) {
            ylen = vh_iget(sect, "YLEN");
            vh_istore(sect, "YLEN", ylen + 1);
        }
    }

    /* Create joined room names */
    vl_foreach(elt, joins) {
        join = vs_pget(elt);
        from = vh_pget(join, "FROM");
        to = vh_pget(join, "TO");

        sprintf(tag, " (%d)", ++jnum);

        name = vh_sgetref(from, "PDESC");
        strcpy(buf, (name == NULL ? vh_sgetref(from, "DESC") : name));
        strcat(buf, tag);
        vh_sstore(from, "PDESC", buf);

        name = vh_sgetref(to, "PDESC");
        strcpy(buf, (name == NULL ? vh_sgetref(to, "DESC") : name));
        strcat(buf, tag);
        vh_sstore(to, "PDESC", buf);
    }

    /* Pack sections */
    width = get_int("map_width", 8);
    height = get_int("map_height", 12);
    num_pages = pack_sections(width, height, 1);

    /* Print header */
    title = get_string("title", NULL);

    printf("%%!PS-Adobe-3.0\n");
    printf("%%%%Title: %s\n",
           title != NULL ? title : "Interactive Fiction map");
    printf("%%%%Creator: IFM v%s\n", VERSION);
    printf("%%%%Pages: %d\n", num_pages);
    printf("%%%%EndComments\n");

    /* Find and print PostScript prolog */
    fp = open_libfile(get_string("prolog_file", PS_PROLOG));
    while ((c = fgetc(fp)) != EOF)
        putchar(c);
    fclose(fp);

    /* Print variables */
    printf("/origpagewidth %g inch def\n", get_real("page_width", 8.3));
    printf("/origpageheight %g inch def\n", get_real("page_height", 11.7));
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
    int page, xlen, ylen;
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

        printf("\n%d %d %s beginpage\n",
               vh_iget(sect, "PXLEN"),
               vh_iget(sect, "PYLEN"),
               (vh_iget(sect, "ROTATE") ? "true" : "false"));
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
    char *desc, *str, *itemlist = NULL;
    vlist *items;

    /* Initialise */
    desc = vh_sgetref(room, "PDESC");
    if (desc == NULL)
        desc = vh_sgetref(room, "DESC");
    if (desc == NULL)
        desc = "";

    /* Write coords */
    printf("%s %g %g", ps_string(desc),
           vh_dget(room, "X") + ps_xoff,
           vh_dget(room, "Y") + ps_yoff);

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
}

void
ps_map_link(vhash *link)
{
    int special = vh_iget(link, "SPECIAL");
    int oneway = vh_iget(link, "ONEWAY");
    int go = vh_iget(link, "GO");
    int updown = (go == UP || go == DOWN);
    int inout = (go == IN || go == OUT);
    vlist *x, *y;
    int i, np;

    truncate_link(link, ps_roomwidth, ps_roomheight);

    x = vh_pget(link, "X");
    y = vh_pget(link, "Y");

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
