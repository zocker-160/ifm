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

#define PRINT_COLOUR(name) \
        if (var_changed(#name)) \
                printf("/%s [%s] def\n", #name, var_colour(#name))

#define PRINT_FONT(name) \
        if (var_changed(#name)) \
                printf("/%s /%s def\n", #name, var_string(#name))

#define PRINT_FONTSIZE(name) \
        if (var_changed(#name)) \
                printf("/%s %g def\n", #name, var_real(#name) * ps_font_scale)

#define PRINT_INT(name) \
        if (var_changed(#name)) \
                printf("/%s %d def\n", #name, var_int(#name))

#define PRINT_REAL(name) \
        if (var_changed(#name)) \
                printf("/%s %g def\n", #name, var_real(#name))

#define PRINT_STRING(name) \
        if (var_changed(#name)) \
                printf("/%s %s def\n", #name, ps_string(var_string(#name)))

#define PRINT_BOOL(name) \
        if (var_changed(#name)) \
                printf("/%s %s def\n", #name, var_int(#name) ? "true" : "false")

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

/* Internal variables */
static int ps_rotate = 0;       /* Whether to rotate pages */
static int ps_rotflag = 0;      /* Whether to override auto-rotation */
static int ps_pagenum = 0;      /* Current page */

static double ps_xoff;          /* Current X offset */
static double ps_yoff;          /* Current Y offset */

static float ps_page_width;     /* Width of a page (cm) */
static float ps_page_height;    /* Height of a page (cm) */

static double ps_room_width;    /* Current room width factor */
static double ps_room_height;   /* Current room height factor */
static double ps_font_scale;    /* Font scaling factor */

/* Internal functions */
static void ps_print_room_vars(void);
static void ps_print_link_vars(void);
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
    if (!get_papersize(pagesize, &ps_page_width, &ps_page_height))
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
    printf("/page_margin %g cm def\n", var_real("page_margin"));
    printf("/page_width %g cm def\n", ps_page_width);
    printf("/page_height %g cm def\n", ps_page_height);
    printf("/map_width %d def\n", width);
    printf("/map_height %d def\n", height);

    PRINT_BOOL(show_border);
    PRINT_COLOUR(page_border_colour);
    PRINT_COLOUR(page_background_colour);

    /* Title variables */
    if (title != NULL) {
        PRINT_BOOL(show_title);
        put_string("/titlestring %s def\n", ps_string(title));
        PRINT_FONT(title_font);
        PRINT_FONTSIZE(title_fontsize);
        PRINT_COLOUR(title_colour);
    } else {
        printf("/show_title false def\n");
    }

    /* Map variables */
    PRINT_FONT(map_text_font);
    PRINT_FONTSIZE(map_text_fontsize);
    PRINT_COLOUR(map_text_colour);
    printf("/room_width %g def\n", ps_room_width);
    printf("/room_height %g def\n", ps_room_height);

    /* Room style variables */
    ps_print_room_vars();

    /* Link style variables */
    ps_print_link_vars();

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

    /* Room style variables */
    ps_print_room_vars();

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
    int oneway = vh_iget(link, "ONEWAY");
    int go = vh_iget(link, "GO");
    int updown = (go == D_UP || go == D_DOWN);
    int inout = (go == D_IN || go == D_OUT);
    vlist *x, *y;
    int i, np;

    /* Link style variables */
    ps_print_link_vars();

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

/* Print room style variables */
static void
ps_print_room_vars(void)
{
    PRINT_FONT(room_text_font);
    PRINT_FONTSIZE(room_text_fontsize);
    PRINT_COLOUR(room_colour);
    PRINT_COLOUR(room_text_colour);
    PRINT_COLOUR(room_border_colour);
    PRINT_BOOL(room_border_dashed);
    PRINT_REAL(room_border_width);
    PRINT_REAL(room_shadow_xoff);
    PRINT_REAL(room_shadow_yoff);
    PRINT_COLOUR(room_shadow_colour);
    PRINT_COLOUR(room_exit_colour);
    PRINT_REAL(room_exit_width);
    PRINT_BOOL(show_items);
    PRINT_FONT(item_text_font);
    PRINT_FONTSIZE(item_text_fontsize);
    PRINT_COLOUR(item_text_colour);
}

/* Print room style variables */
static void
ps_print_link_vars(void)
{
    PRINT_COLOUR(link_colour);
    PRINT_BOOL(link_dashed);
    PRINT_REAL(link_arrow_size);
    PRINT_FONT(link_text_font);
    PRINT_FONTSIZE(link_text_fontsize);
    PRINT_COLOUR(link_text_colour);
    PRINT_REAL(link_line_width);
    PRINT_STRING(link_updown_string);
    PRINT_STRING(link_inout_string);
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
        if (strchr("()", *str) != NULL)
            vb_putc(b, '\\');
        vb_putc(b, *str++);
    }

    vb_putc(b, ')');
    return vb_get(b);
}
