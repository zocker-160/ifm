/* Object function header */

#ifndef FIG_OBJECT_H
#define FIG_OBJECT_H

#include <vars.h>

/* Object types */
enum {
    FIG_COLOUR, FIG_ELLIPSE, FIG_POLYLINE, FIG_SPLINE, FIG_TEXT, FIG_ARC,
    FIG_COMPOUND, FIG_ROOT
};

/* Polyline types */
enum {
    FIG_LINE = 1, FIG_BOX, FIG_POLYGON, FIG_ARCBOX, FIG_PICTURE
};

extern void fig_add_point(vhash *object, float x, float y);
extern vhash *fig_create(void);
extern vhash *fig_create_arc(vhash *parent, int subtype);
extern vhash *fig_create_box(vhash *parent, float x1, float y1, float x2,
                             float y2);
extern vhash *fig_create_compound(vhash *parent);
extern vhash *fig_create_ellipse(vhash *parent, int subtype);
extern vhash *fig_create_line(vhash *parent, float x1, float y1, float x2,
                              float y2);
extern vhash *fig_create_picture(vhash *parent, float x1, float y1, float x2,
                                 float y2, char *file);
extern vhash *fig_create_polygon(vhash *parent, float x1, float y1, float x2,
                                 float y2, float x3, float y3);
extern vhash *fig_create_polyline(vhash *parent, int subtype);
extern vhash *fig_create_spline(vhash *parent, int subtype);
extern vhash *fig_create_text(vhash *parent, float x, float y, char *fmt,
                              ...);
extern void fig_destroy(vhash *figure);
extern vhash *fig_get_figure(vhash *object);

#endif
