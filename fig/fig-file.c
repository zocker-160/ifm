/* Fig file functions */

#include "fig-attr.h"
#include "fig-file.h"
#include "fig-object.h"

/* Internal functions */
static int fig_calc_bbox(vhash *object);
static void fig_write_object(vhash *object, FILE *fp);

/* Calculate bounding box of an object */
static int
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

/* Write figure to a stream */
void
fig_write_figure(vhash *figure, FILE *fp)
{
    vlist *objects;
    vhash *colours;
    vscalar *elt;
    char *key;

    /* Calculate bounding box */
    fig_calc_bbox(figure);

    /* Write header info */
    fprintf(fp, "#FIG 3.2\n");

    fprintf(fp, "%s\n", vh_iget(figure, "ORIENTATION") == FIG_LANDSCAPE ?
            "Landscape" : "Portrait");

    fprintf(fp, "Center\n");
    fprintf(fp, "Inches\n");
    fprintf(fp, "A4\n");
    fprintf(fp, "100.00\n");
    fprintf(fp, "Single\n");
    fprintf(fp, "-2\n");
    fprintf(fp, "%d 2\n", FIG_RESOLUTION);

    /* Write colour table entries (if any) */
    if ((colours = vh_pget(figure, "COLOURS")) != NULL)
        vh_foreach(key, elt, colours)
            fprintf(fp, "%d %d %s\n", FIG_COLOUR, vs_iget(elt), key);

    /* Write objects */
    if ((objects = vh_pget(figure, "OBJECTS")) != NULL)
        vl_foreach(elt, objects)
            fig_write_object(vs_pget(elt), fp);
}

/* Write an object to a stream */
static void
fig_write_object(vhash *object, FILE *fp)
{
    int arrow_forward, arrow_backward, radius, npoints;
    int type, subtype, pen_style, cap_style;
    int i, arrow_type, arrow_style, font_flags;
    float style_val, width, height, thickness;
    vlist *objects, *xp, *yp;
    vscalar *elt;

    type = vh_iget(object, "TYPE");
    subtype = vh_iget(object, "SUBTYPE");

    pen_style = 0;
    style_val = 1.0;
    cap_style = 0;
    radius = 1;

    xp = vh_pget(object, "XP");
    yp = vh_pget(object, "YP");
    npoints = (xp != NULL ? vl_length(xp) : 0);
    arrow_forward = vh_iget(object, "ARROW_FORWARD");
    arrow_backward = vh_iget(object, "ARROW_BACKWARD");

    if (vh_exists(object, "NAME"))
        fprintf(fp, "# %s\n", vh_sgetref(object, "NAME"));

    switch (type) {

    case FIG_ELLIPSE:
        /* FINISH ME */
        break;

    case FIG_POLYLINE:
        fprintf(fp, "%d ", type);
        fprintf(fp, "%d ", subtype);
        fprintf(fp, "%d ", vh_iget(object, "LINESTYLE"));
        fprintf(fp, "%d ", vh_iget(object, "THICKNESS"));
        fprintf(fp, "%d ", vh_iget(object, "PENCOLOUR"));
        fprintf(fp, "%d ", vh_iget(object, "FILLCOLOUR"));
        fprintf(fp, "%d ", vh_iget(object, "DEPTH"));
        fprintf(fp, "%d ", pen_style);
        fprintf(fp, "%d ", vh_iget(object, "FILLSTYLE"));
        fprintf(fp, "%.3f ", style_val);
        fprintf(fp, "%d ", vh_iget(object, "JOINSTYLE"));
        fprintf(fp, "%d ", cap_style);
        fprintf(fp, "%d ", radius);
        fprintf(fp, "%d ", arrow_forward);
        fprintf(fp, "%d ", arrow_backward);
        fprintf(fp, "%d\n", npoints);

        switch (subtype) {

        case FIG_PICTURE:
            fprintf(fp, "\t0 %s\n", vh_sgetref(object, "PICFILE"));
            break;

        default:
            arrow_type = vh_iget(object, "ARROW_TYPE");
            arrow_style = vh_iget(object, "ARROW_STYLE");
            thickness = vh_fget(object, "ARROW_THICK");
            width = vh_fget(object, "ARROW_WIDTH");
            height = vh_fget(object, "ARROW_HEIGHT");

            if (arrow_forward)
                fprintf(fp, "\t%d %d %g %g %g\n",
                        arrow_type, arrow_style, thickness, width, height);

            if (arrow_backward)
                fprintf(fp, "\t%d %d %g %g %g\n",
                        arrow_type, arrow_style, thickness, width, height);

            break;
        }

        fprintf(fp, "\t");
        for (i = 0; i < npoints; i++)
            fprintf(fp, " %d %d", vl_iget(xp, i), vl_iget(yp, i));
        fprintf(fp, "\n");

        break;

    case FIG_SPLINE:
        /* FINISH ME */
        break;

    case FIG_TEXT:
        font_flags = 4;

        fprintf(fp, "%d ", type);
        fprintf(fp, "%d ", vh_iget(object, "JUSTIFY"));
        fprintf(fp, "%d ", vh_iget(object, "PENCOLOUR"));
        fprintf(fp, "%d ", vh_iget(object, "DEPTH"));
        fprintf(fp, "%d ", pen_style);
        fprintf(fp, "%d ", vh_iget(object, "FONT"));
        fprintf(fp, "%g ", vh_fget(object, "FONTSIZE"));
        fprintf(fp, "%g ", vh_fget(object, "ANGLE"));
        fprintf(fp, "%d ", font_flags);
        fprintf(fp, "%g ", vh_fget(object, "HEIGHT"));
        fprintf(fp, "%g ", vh_fget(object, "WIDTH"));
        fprintf(fp, "%d ", vh_iget(object, "X"));
        fprintf(fp, "%d ", vh_iget(object, "Y"));
        fprintf(fp, "%s\\001\n", vh_sgetref(object, "TEXT"));
        break;

    case FIG_ARC:
        /* FINISH ME */
        break;

    case FIG_COMPOUND:
        fprintf(fp, "%d ", type);
        fprintf(fp, "%d ", vh_iget(object, "XMAX"));
        fprintf(fp, "%d ", vh_iget(object, "YMAX"));
        fprintf(fp, "%d ", vh_iget(object, "XMIN"));
        fprintf(fp, "%d\n", vh_iget(object, "YMIN"));

        if ((objects = vh_pget(object, "OBJECTS")) != NULL)
            vl_foreach(elt, objects)
                fig_write_object(vs_pget(elt), fp);

        fprintf(fp, "-6\n");
        break;
    }
}
