/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* PostScript output driver */

/* Prototypes */
void ps_map_start(void);
void ps_map_section(vhash *sect);
void ps_map_room(vhash *room);
void ps_map_link(vhash *link);
void ps_map_endsection(void);
void ps_map_finish(void);

/* Map function list */
mapfuncs ps_mapfuncs = {
    ps_map_start,
    ps_map_section,
    ps_map_room,
    ps_map_link,
    ps_map_endsection,
    ps_map_finish
};

/* Controllable map parameters */
static char *ps_title;          /* Title */
static char *ps_titlefont;      /* Title font */
static char *ps_roomfont;       /* Room font */
static char *ps_itemfont;       /* Item font */
static char *ps_labelfont;      /* Label font */
static char *ps_prolog;         /* PostScript prolog file */

static double ps_ptsize;        /* Text point size */
static double ps_room_height;   /* Room height */
static double ps_room_width;    /* Room width */
static double ps_page_width;    /* Page width */
static double ps_page_height;   /* Page height */

static int ps_map_width;        /* Map width */
static int ps_map_height;       /* Map height */
static int ps_room_items;       /* Print items in rooms? */

/* Internal variables */
static int ps_pagenum = 0;      /* Current page */
static int ps_xoff;             /* Current X offset */
static int ps_yoff;             /* Current Y offset */

/* Internal functions */
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

/* Map functions */
void
ps_map_start(void)
{
    vscalar *elt;
    vhash *sect;
    int ylen, c;
    FILE *fp;

    /* Get variables */
    ps_title =       get_string("title",       NULL);
    ps_titlefont =   get_string("title_font",  "Times-Bold");
    ps_prolog =      get_string("prolog",      PS_PROLOG);

    ps_page_width =  get_real("page_width",    8.3);
    ps_page_height = get_real("page_height",   11.7);

    ps_map_width =   get_int("map_width",      8);
    ps_map_height =  get_int("map_height",     12);

    /* Allow title space for sections with titles */
    vl_foreach(elt, sects) {
        sect = vs_pget(elt);
        if (vh_exists(sect, "TITLE")) {
            ylen = vh_iget(sect, "YLEN");
            vh_istore(sect, "YLEN", ylen + 1);
        }
    }

    /* Pack sections */
    pack_sections(ps_map_width, ps_map_height, 1);

    /* Print header */
    printf("%%!PS-Adobe-3.0\n\n");

    /* Find and print PostScript prolog */
    fp = open_libfile(ps_prolog);
    while ((c = fgetc(fp)) != EOF)
        putchar(c);
}

void
ps_map_section(vhash *sect)
{
    int page, xlen, ylen;
    double xpos, ypos;

    /* Get variables */
    ps_room_width =  get_real("room_width",    0.8);
    ps_room_height = get_real("room_height",   0.65);
    ps_ptsize =      get_real("pointsize",     10.0);

    ps_roomfont =    get_string("room_font",   "Times-Bold");
    ps_itemfont =    get_string("item_font",   "Times-Roman");
    ps_labelfont =   get_string("label_font",  "Times-Roman");

    ps_room_items =  get_int("show_items",     0);

    /* Get section parameters */
    page = vh_iget(sect, "PAGE");
    ps_xoff = vh_iget(sect, "XOFF");
    ps_yoff = vh_iget(sect, "YOFF");

    /* Start a new page if required */
    if (page != ps_pagenum) {
        if (ps_pagenum > 0)
            printf("endpage\n");

        ps_pagenum = page;
        printf("\n%d %d %s beginpage\n",
               vh_iget(sect, "PXLEN"),
               vh_iget(sect, "PYLEN"),
               (vh_iget(sect, "ROTATE") ? "true" : "false"));
    }

    /* Print title if required */
    if (vh_exists(sect, "TITLE")) {
        xlen = vh_iget(sect, "XLEN");
        xpos = (xlen - 1) / 2;
        ylen = vh_iget(sect, "YLEN");
        ypos = ylen - 1;
        printf("%s %g %g map\n", ps_string(vh_sgetref(sect, "TITLE")),
               xpos + ps_xoff, ypos + ps_yoff);
    }
}

void
ps_map_room(vhash *room)
{
    int puzzle, doitems;
    vlist *list, *items;
    char *desc, *str;
    vhash *item;
    vscalar *elt;

    /* Initialise */
    desc = vh_sgetref(room, "PDESC");
    if (desc == NULL)
        desc = vh_sgetref(room, "DESC");
    if (desc == NULL)
        desc = "";

    items = vh_pget(room, "ITEMS");
    doitems = ps_room_items && items && vl_length(items) > 0;
    puzzle = vh_iget(room, "PUZZLE");

    /* Write coords */
    printf("%s %g %g room\n", ps_string(desc),
           vh_dget(room, "X") + ps_xoff,
           vh_dget(room, "Y") + ps_yoff);

#if 0
    /* Get item list */
    if (doitems) {
        vl_foreach(elt, items) {
            item = vs_pget(elt);
            if (!vh_iget(item, "HIDDEN"))
                vl_spush(list, vh_sgetref(item, "DESC"));
        }

        if (vl_length(list) > 0) {
            str = vl_join(list, ", ");
            vl_destroy(list);
            list = split_line(str, 3.5);
            vl_foreach(elt, list)
                printf(" \"\\s-2\\f[%s]%s\\fP\\s0\"",
                       groff_itemfont, vs_sget(elt));
        }
    }

    vl_destroy(list);
#endif
}

void
ps_map_link(vhash *link)
{
}

void
ps_map_endsection(void)
{
}

void
ps_map_finish(void)
{
    printf("endpage\n");
}
