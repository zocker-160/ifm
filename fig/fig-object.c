/* Fig object functions */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "fig-attr.h"
#include "fig-object.h"
#include "fig-util.h"

#define SCALE FIG_RESOLUTION

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static vhash *fig_create_object(vhash *parent, int type);

/* Create a new figure */
vhash *
fig_create(int units, float scale)
{
    vlist *objects;
    char *uname;
    vhash *obj;

    switch (units) {
    case FIG_INCHES:
        uname = "Inches";
        break;
    case FIG_METRIC:
        uname = "Metric";
        scale *= 0.375;
        break;
    default:
        fig_fatal("invalid units");
        break;
    }

    obj = fig_create_object(NULL, FIG_ROOT);

    fig_set_papersize(obj, "A4");
    fig_set_orientation(obj, FIG_LANDSCAPE);

    vh_istore(obj, "RESOLUTION", SCALE);
    vh_sstore(obj, "UNITS", uname);
    vh_dstore(obj, "SCALE", scale);

    vh_istore(obj, "PENCOLOUR", -1);
    vh_istore(obj, "FILLCOLOUR", -1);
    vh_istore(obj, "LINEWIDTH", 1);

    fig_set_depth(obj, 100);
    fig_set_justify(obj, FIG_JUSTIFY_CENTRE);
    fig_set_arrowstyle(obj, FIG_CLOSED, FIG_FILLED, 1.0, 4.0, 8.0);

    return obj;
}

/* Create an arc object */
vhash *
fig_create_arc(vhash *parent, int subtype, float cx, float cy,
               float x1, float y1, float x2, float y2, float x3, float y3)
{
    vhash *obj;

    obj = fig_create_object(parent, FIG_ARC);
    vh_istore(obj, "SUBTYPE", subtype);

    fig_create_point(obj, cx, cy);
    fig_create_point(obj, x1, y1);
    fig_create_point(obj, x2, y2);
    fig_create_point(obj, x3, y3);

    return obj;
}

/* Create a box object */
vhash *
fig_create_box(vhash *parent, float x, float y, float width, float height)
{
    vhash *obj;

    obj = fig_create_polyline(parent, FIG_BOX);

    fig_create_point(obj, x, y);
    fig_create_point(obj, x + width, y);
    fig_create_point(obj, x + width, y + height);
    fig_create_point(obj, x, y + height);
    fig_create_point(obj, x, y);

    return obj;
}

/* Create a compound object */
vhash *
fig_create_compound(vhash *parent)
{
    return fig_create_object(parent, FIG_COMPOUND);
}

/* Create an ellipse object */
vhash *
fig_create_ellipse(vhash *parent, int subtype)
{
    vhash *obj;

    obj = fig_create_object(parent, FIG_ELLIPSE);
    vh_istore(obj, "SUBTYPE", subtype);
    /* FINISH ME */

    return obj;
}

/* Create a line object */
vhash *
fig_create_line(vhash *parent, float x1, float y1, float x2, float y2)
{
    vhash *obj;

    obj = fig_create_polyline(parent, FIG_LINE);

    fig_create_point(obj, x1, y1);
    fig_create_point(obj, x2, y2);

    return obj;
}

/* Add a new object */
static vhash *
fig_create_object(vhash *parent, int type)
{
    vlist *objects;
    vhash *obj;

    obj = vh_create();
    vh_istore(obj, "TYPE", type);

    if (parent != NULL) {
        if ((objects = vh_pget(parent, "OBJECTS")) == NULL) {
            objects = vl_create();
            vh_pstore(parent, "OBJECTS", objects);
        }

        vl_ppush(objects, obj);
        vh_pstore(obj, "PARENT", parent);
    }

    return obj;
}

/* Create a picture object */
vhash *
fig_create_picture(vhash *parent,
                   float x, float y,
                   float width, float height,
                   char *file)
{
    vhash *obj;

    obj = fig_create_polyline(parent, FIG_PICTURE);

    fig_create_point(obj, x, y);
    fig_create_point(obj, x + width, y);
    fig_create_point(obj, x + width, y + height);
    fig_create_point(obj, x, y + height);
    fig_create_point(obj, x, y);

    vh_sstore(obj, "PICFILE", file);

    return obj;
}

/* Add an X,Y point to an object */
int
fig_create_point(vhash *parent, float x, float y)
{
    vhash *figure = fig_get_figure(parent);
    float scale = vh_dget(figure, "SCALE");
    vlist *list;
    int num;

    if ((list = vh_pget(parent, "XP")) == NULL) {
        list = vl_create();
        vh_pstore(parent, "XP", list);
    }

    vl_ipush(list, (int) (x * scale * SCALE));

    if ((list = vh_pget(parent, "YP")) == NULL) {
        list = vl_create();
        vh_pstore(parent, "YP", list);
    }

    vl_ipush(list, (int) (y * scale * SCALE));

    if ((list = vh_pget(parent, "SHAPE")) == NULL) {
        list = vl_create();
        vh_pstore(parent, "SHAPE", list);
    }

    num = vl_length(list);
    vl_fpush(list, num == 0 ? 0.0 : 1.0);

    return num;
}

/* Create a polygon object */
vhash *
fig_create_polygon(vhash *parent,
                   float x1, float y1,
                   float x2, float y2,
                   float x3, float y3)
{
    vhash *obj;

    obj = fig_create_polyline(parent, FIG_POLYGON);

    fig_create_point(obj, x1, y1);
    fig_create_point(obj, x2, y2);
    fig_create_point(obj, x3, y3);

    return obj;
}

/* Create a polyline object */
vhash *
fig_create_polyline(vhash *parent, int subtype)
{
    vhash *obj;

    obj = fig_create_object(parent, FIG_POLYLINE);
    vh_istore(obj, "SUBTYPE", subtype);

    return obj;
}

/* Create a spline object */
vhash *
fig_create_spline(vhash *parent, int subtype)
{
    vhash *obj;

    obj = fig_create_object(parent, FIG_SPLINE);
    vh_istore(obj, "SUBTYPE", subtype);

    return obj;
}

/* Create a text object */
vhash *
fig_create_text(vhash *parent, float x, float y, char *fmt, ...)
{
    vhash *figure = fig_get_figure(parent);
    float scale = vh_dget(figure, "SCALE");
    vhash *obj;

    obj = fig_create_object(parent, FIG_TEXT);

    V_VPRINT(buf, fmt);
    vh_sstore(obj, "TEXT", buf);

    vh_istore(obj, "FONT", 0);
    vh_fstore(obj, "FONTSIZE", 10.0 * scale);

    vh_fstore(obj, "WIDTH", strlen(buf) * FIG_TEXT_WSCALE * scale);
    vh_fstore(obj, "HEIGHT", 10.0 * FIG_TEXT_HSCALE * scale);
    vh_fstore(obj, "ANGLE", 0.0);

    vh_istore(obj, "X", (int) (x * scale * SCALE));
    vh_istore(obj, "Y", (int) (y * scale * SCALE));

    return obj;
}

/* Create text that fits in a box */
vhash *
fig_create_textbox(vhash *parent,
                   char *font, float fontsize, int justify,
                   float x, float y, float width, float height,
                   char *fmt, ...)
{
    vhash *figure = fig_get_figure(parent);
#if 1
    float scale = vh_dget(figure, "SCALE") * SCALE;
#else
    float scale = SCALE;
#endif

    float xt, yt, textwidth, textheight, linegap, offset;
    int i, nrows, ncols;
    vhash *obj, *text;
    vlist *lines;

    V_VPRINT(buf, fmt);

    /* Reduce font size until it fits the box */
    while (1) {
        linegap = fontsize * FIG_TEXT_HSCALE * 1.1;
        ncols = width * scale / (FIG_TEXT_WSCALE * fontsize);
        lines = vl_filltext(buf, ncols);
        nrows = vl_length(lines);

        fig_debug("trying fontsize %g: %d rows, %d cols",
                  fontsize, nrows, ncols);

        fig_value(nrows * linegap);
        fig_value(height * scale);

        if (nrows * linegap <= height * scale)
            break;

        if (fontsize <= 4)
            break;

        fontsize--;
        vl_destroy(lines);
    }

    /* Create text objects */
    obj = fig_create_compound(parent);

    switch (justify) {
    case FIG_JUSTIFY_LEFT:
        xt = x;
        break;
    case FIG_JUSTIFY_CENTRE:
        xt = x + width / 2;
        break;
    case FIG_JUSTIFY_RIGHT:
        xt = x + width;
        break;
    }

    for (i = 0; i < nrows; i++) {
        offset = i + 0.7 - nrows / 2.0;
        yt = y + height / 2;
        yt += (offset * linegap) / scale;
        text = fig_create_text(obj, xt, yt, "%s", vl_sgetref(lines, i));
        fig_set_font(text, font, fontsize);
        fig_set_justify(text, justify);
    }

    vl_destroy(lines);
    return obj;
}

/* Destroy a figure */
void
fig_destroy(vhash *figure)
{
    v_destroy(figure);
}
