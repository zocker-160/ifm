/* Fig attribute functions */

#include <stdarg.h>
#include "fig-attr.h"
#include "fig-object.h"

/* Font list */
static char *fontlist[] = {
    "Times Roman",
    "Times Italic",
    "Times Bold",
    "Times Bold Italic",
    "AvantGarde Book",
    "AvantGarde Book Oblique",
    "AvantGarde Demi",
    "AvantGarde Demi Oblique",
    "Bookman Light",
    "Bookman Light Italic",
    "Bookman Demi",
    "Bookman Demi Italic",
    "Courier",
    "Courier Oblique",
    "Courier Bold",
    "Courier Bold Oblique",
    "Helvetica",
    "Helvetica Oblique",
    "Helvetica Bold",
    "Helvetica Bold Oblique",
    "Helvetica Narrow",
    "Helvetica Narrow Oblique",
    "Helvetica Narrow Bold",
    "Helvetica Narrow Bold Oblique",
    "New Century Schoolbook Roman",
    "New Century Schoolbook Italic",
    "New Century Schoolbook Bold",
    "New Century Schoolbook Bold Italic",
    "Palatino Roman",
    "Palatino Italic",
    "Palatino Bold",
    "Palatino Bold Italic",
    "Symbol",
    "Zapf Chancery Medium Italic",
    "Zapf Dingbats",
    NULL
};

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static int fig_lookup_colour(vhash *object, int r, int g, int b);
static int fig_lookup_font(char *name);

/* Look up a colour given its RGB values */
static int
fig_lookup_colour(vhash *object, int r, int g, int b)
{
    vhash *figure, *colours;
    static int nextid = 32;
    char cbuf[20];
    int id;

    figure = fig_get_figure(object);
    if ((colours = vh_pget(figure, "COLOURS")) == NULL) {
        colours = vh_create();
        vh_pstore(figure, "COLOURS", colours);
    }

    sprintf(cbuf, "#%02x%02x%02x", r, g, b);

    if (vh_exists(colours, cbuf)) {
        id = vh_iget(colours, cbuf);
    } else {
        vh_istore(colours, cbuf, nextid);
        id = nextid++;
    }

    return id;
}

/* Look up a font ID given its name */
static int
fig_lookup_font(char *name)
{
    int i, len;

    len = strlen(name);
    for (i = 0; fontlist[i] != NULL; i++)
        if (strncmp(name, fontlist[i], len) == 0)
            return i;

    return -1;
}

/* Set the arrow flags of an object */
void
fig_set_arrow(vhash *object, int forward, int backward)
{
    vh_istore(object, "ARROW_FORWARD", forward);
    vh_istore(object, "ARROW_BACKWARD", backward);
}

/* Set the arrow style of an object */
void
fig_set_arrowstyle(vhash *object, int type, int style,
                   float thick, float width, float height)
{
    vh_istore(object, "ARROW_TYPE", type);
    vh_istore(object, "ARROW_STYLE", style);
    vh_fstore(object, "ARROW_THICK", thick);
    vh_fstore(object, "ARROW_WIDTH", width * 15);
    vh_fstore(object, "ARROW_HEIGHT", height * 15);
}

/* Set the colour of an object */
void
fig_set_colour(vhash *object, int r, int g, int b)
{
    int id = fig_lookup_colour(object, r, g, b);
    vh_istore(object, "PENCOLOUR", id);
}

/* Set the depth of an object */
void
fig_set_depth(vhash *object, int depth)
{
    vh_istore(object, "DEPTH", depth);
}

/* Set the fill colour of an object */
void
fig_set_fillcolour(vhash *object, int r, int g, int b)
{
    int id = fig_lookup_colour(object, r, g, b);
    vh_istore(object, "FILLCOLOUR", id);
    vh_istore(object, "FILLSTYLE", 20);
}

/* Set the fill style of an object */
void
fig_set_fillstyle(vhash *object, int style)
{
    vh_istore(object, "FILLSTYLE", style);
}

/* Set the font of an object */
void
fig_set_font(vhash *object, char *font, float fontsize)
{
    vh_istore(object, "FONT", fig_lookup_font(font));
    vh_fstore(object, "FONTSIZE", fontsize);
    vh_fstore(object, "HEIGHT", fontsize * FIG_TEXT_HSCALE);
}

/* Set the join style of an object */
void
fig_set_joinstyle(vhash *object, int style)
{
    vh_istore(object, "JOINSTYLE", style);
}

/* Set the justification of an object */
void
fig_set_justify(vhash *object, int justify)
{
    vh_istore(object, "JUSTIFY", justify);
}

/* Set the line style of an object */
void
fig_set_linestyle(vhash *object, int style)
{
    vh_istore(object, "LINESTYLE", style);
}

/* Set the name of an object */
void
fig_set_name(vhash *object, char *fmt, ...)
{
    V_VPRINT(buf, fmt);
    vh_sstore(object, "NAME", buf);
}