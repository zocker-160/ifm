/* Utility functions */

#include <stdio.h>
#include <stdarg.h>
#include "fig-object.h"
#include "fig-util.h"

/* Calculate bounding box of an object */
int
fig_calc_bbox(vhash *object)
{
    int i, num, xmin, xmax, ymin, ymax, x, y, justify, count = 0;
    int type, bxmin, bxmax, bymin, bymax, width, height;
    vlist *objects, *xp, *yp;
    vscalar *elt;
    vhash *obj;

    type = vh_iget(object, "TYPE");

    switch (type) {

    case FIG_ROOT:
    case FIG_COMPOUND:
        if ((objects = vh_pget(object, "OBJECTS")) == NULL)
            return 0;

        vl_foreach(elt, objects) {
            obj = vs_pget(elt);
            if (!fig_calc_bbox(obj))
                continue;

            xmin = vh_iget(obj, "XMIN");
            xmax = vh_iget(obj, "XMAX");
            ymin = vh_iget(obj, "YMIN");
            ymax = vh_iget(obj, "YMAX");

            if (count++ == 0) {
                bxmin = xmin;
                bxmax = xmax;
                bymin = ymin;
                bymax = ymax;
            } else {
                bxmin = V_MIN(xmin, bxmin);
                bxmax = V_MAX(xmax, bxmax);
                bymin = V_MIN(ymin, bymin);
                bymax = V_MAX(ymax, bymax);
            }
        }

        break;

    case FIG_TEXT:
        x = vh_iget(object, "X");
        y = vh_iget(object, "Y");
        width = vh_fget(object, "WIDTH");
        height = vh_fget(object, "HEIGHT");
        justify = vh_iget(object, "JUSTIFY");

        bxmin = x;
        bxmax = x + height;
        bymin = y - width / 2;
        bymax = y + width / 2;

        /* FINISH ME -- adjust for justification */
        break;

    default:
        if ((xp = vh_pget(object, "XP")) == NULL)
            return 0;

        if ((yp = vh_pget(object, "YP")) == NULL)
            return 0;

        num = vl_length(xp);
        for (i = 0; i < num; i++) {
            x = vl_iget(xp, i);
            y = vl_iget(yp, i);

            if (count++ == 0) {
                bxmin = x;
                bxmax = x;
                bymin = y;
                bymax = y;
            } else {
                bxmin = V_MIN(x, bxmin);
                bxmax = V_MAX(x, bxmax);
                bymin = V_MIN(y, bymin);
                bymax = V_MAX(y, bymax);
            }
        }

        break;
    }

    vh_istore(object, "XMIN", bxmin);
    vh_istore(object, "XMAX", bxmax);
    vh_istore(object, "YMIN", bymin);
    vh_istore(object, "YMAX", bymax);

    return 1;
}

/* Print a debugging message */
void
fig_debug(char *fmt, ...)
{
    char buf[BUFSIZ];

    if (getenv("FIG_DEBUG") != NULL) {
        V_VPRINT(buf, fmt);
        fprintf(stderr, "Fig: %s\n", buf);
    }
}

/* Print a fatal error and die */
void
fig_fatal(char *fmt, ...)
{
    char buf[BUFSIZ];

    V_VPRINT(buf, fmt);
    fprintf(stderr, "Fig fatal: %s\n", buf);
    exit(2);
}

/* Get an attribute of an object */
vscalar *
fig_get_attr(vhash *object, char *attr)
{
    vhash *parent;

    while (!vh_exists(object, attr) &&
           (parent = vh_pget(object, "PARENT")) != NULL)
        object = parent;

#if 0
    if (!vh_exists(object, attr))
        fig_fatal("no such attribute: %s", attr);
#endif

    return vh_get(object, attr);
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
