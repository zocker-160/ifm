/* Fig object functions */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "fig-attr.h"
#include "fig-object.h"

#define SCALE FIG_RESOLUTION

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static vhash *fig_create_object(vhash *parent, int type);

/* Add an X,Y point to an object */
void
fig_add_point(vhash *object, float x, float y)
{
    vlist *list;

    if ((list = vh_pget(object, "XP")) == NULL) {
        list = vl_create();
        vh_pstore(object, "XP", list);
    }

    x *= SCALE;
    vl_ipush(list, (int) x);

    if ((list = vh_pget(object, "YP")) == NULL) {
        list = vl_create();
        vh_pstore(object, "YP", list);
    }

    y *= SCALE;
    vl_ipush(list, (int) y);
}

/* Create a new figure */
vhash *
fig_create(void)
{
    vlist *objects;
    vhash *obj;

    obj = fig_create_object(NULL, FIG_ROOT);

    vh_istore(obj, "RESOLUTION", SCALE);
    vh_istore(obj, "ORIENTATION", FIG_LANDSCAPE);

    return obj;
}

/* Create an arc object */
vhash *
fig_create_arc(vhash *parent, int subtype)
{
    vhash *obj;

    obj = fig_create_object(parent, FIG_ARC);
    vh_istore(obj, "SUBTYPE", subtype);
    /* FINISH ME */

    return obj;
}

/* Create a box object */
vhash *
fig_create_box(vhash *parent, float x1, float y1, float x2, float y2)
{
    vhash *obj;

    obj = fig_create_polyline(parent, FIG_BOX);

    fig_add_point(obj, x1, y1);
    fig_add_point(obj, x2, y1);
    fig_add_point(obj, x2, y2);
    fig_add_point(obj, x1, y2);
    fig_add_point(obj, x1, y1);

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

    fig_add_point(obj, x1, y1);
    fig_add_point(obj, x2, y2);

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

    vh_istore(obj, "PENCOLOUR", -1);
    vh_istore(obj, "FILLCOLOUR", -1);
    vh_istore(obj, "THICKNESS", 1);

    fig_set_depth(obj, 100);
    fig_set_justify(obj, FIG_JUSTIFY_CENTRE);
    fig_set_arrowstyle(obj, FIG_CLOSED, FIG_FILLED, 1.0, 4.0, 8.0);

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
                   float x1, float y1,
                   float x2, float y2,
                   char *file)
{
    vhash *obj;

    obj = fig_create_polyline(parent, FIG_PICTURE);

    fig_add_point(obj, x1, y1);
    fig_add_point(obj, x2, y1);
    fig_add_point(obj, x2, y2);
    fig_add_point(obj, x1, y2);
    fig_add_point(obj, x1, y1);

    vh_sstore(obj, "PICFILE", file);

    return obj;
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

    fig_add_point(obj, x1, y1);
    fig_add_point(obj, x2, y2);
    fig_add_point(obj, x3, y3);

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
    /* FINISH ME */

    return obj;
}

/* Create a text object */
vhash *
fig_create_text(vhash *parent, float x, float y, char *fmt, ...)
{
    vhash *obj;

    obj = fig_create_object(parent, FIG_TEXT);

    V_VPRINT(buf, fmt);
    vh_sstore(obj, "TEXT", buf);

    vh_istore(obj, "FONT", 0);
    vh_fstore(obj, "FONTSIZE", 10.0);

    vh_fstore(obj, "WIDTH", strlen(buf) * FIG_TEXT_WSCALE);
    vh_fstore(obj, "HEIGHT", 10.0 * FIG_TEXT_HSCALE);

    x *= SCALE;
    vh_istore(obj, "X", (int) x);

    y *= SCALE;
    vh_istore(obj, "Y", (int) y);

    return obj;
}

/* Destroy a figure */
void
fig_destroy(vhash *figure)
{
    v_destroy(figure);
}

/* Get the root figure of an object */
vhash *
fig_get_figure(vhash *object)
{
    vhash *parent;

    while ((parent = vh_pget(object, "PARENT")) != NULL)
        object = parent;

    return object;
}
