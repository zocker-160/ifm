/* Attribute function header */

#ifndef FIG_ATTR_H
#define FIG_ATTR_H

#include <vars.h>

#define FIG_RESOLUTION 1200

#define FIG_TEXT_WSCALE 10
#define FIG_TEXT_HSCALE 10

/* Orientation */
enum {
    FIG_LANDSCAPE, FIG_PORTRAIT
};

/* Indexed colours */
enum {
    FIG_BLACK, FIG_BLUE, FIG_GREEN, FIG_CYAN, FIG_RED, FIG_MAGENTA,
    FIG_YELLOW, FIG_WHITE
};

/* Line styles */
enum {
    FIG_SOLID, FIG_DASH, FIG_DOTTED, FIG_DASH_DOT, FIG_DASH_2_DOTS,
    FIG_DASH_3_DOTS
};

/* Join styles */
enum {
    FIG_MITRE, FIG_BEVEL, FIG_ROUND
};

/* Arrow types */
enum {
    FIG_STICK, FIG_CLOSED, FIG_INDENTED, FIG_POINTED
};

/* Arrow styles */
enum {
    FIG_HOLLOW, FIG_FILLED
};

/* Text justification types */
enum {
    FIG_JUSTIFY_LEFT, FIG_JUSTIFY_CENTRE, FIG_JUSTIFY_RIGHT
};

extern void fig_set_arrow(vhash *object, int forward, int backward);
extern void fig_set_arrowstyle(vhash *object, int type, int style,
                               float thick, float width, float height);
extern void fig_set_colour(vhash *object, float r, float g, float b);
extern void fig_set_depth(vhash *object, int depth);
extern void fig_set_fillcolour(vhash *object, int r, int g, int b);
extern void fig_set_fillstyle(vhash *object, int style);
extern void fig_set_font(vhash *object, char *font, float fontsize);
extern void fig_set_joinstyle(vhash *object, int style);
extern void fig_set_justify(vhash *object, int justify);
extern void fig_set_linestyle(vhash *object, int style);
extern void fig_set_name(vhash *object, char *fmt, ...);

#endif
