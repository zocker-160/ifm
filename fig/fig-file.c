/* Fig file functions */

#include "fig-attr.h"
#include "fig-file.h"
#include "fig-object.h"
#include "fig-util.h"

/* Internal functions */
static void fig_write_arrows(vhash *object, FILE *fp);
static void fig_write_object(vhash *object, FILE *fp);

/* Write object arrows to a stream */
static void
fig_write_arrows(vhash *object, FILE *fp)
{
    int arrow_forward = vh_iget(object, "ARROW_FORWARD");
    int arrow_backward = vh_iget(object, "ARROW_BACKWARD");
    int arrow_type = vh_iget(object, "ARROW_TYPE");
    int arrow_style = vh_iget(object, "ARROW_STYLE");
    float thickness = vh_fget(object, "ARROW_THICK");
    float width = vh_fget(object, "ARROW_WIDTH");
    float height = vh_fget(object, "ARROW_HEIGHT");

    if (arrow_forward)
        fprintf(fp, "\t%d %d %g %g %g\n",
                arrow_type, arrow_style, thickness, width, height);

    if (arrow_backward)
        fprintf(fp, "\t%d %d %g %g %g\n",
                arrow_type, arrow_style, thickness, width, height);
}

/* Write figure to a stream */
void
fig_write_figure(vhash *figure, FILE *fp)
{
    int orient = vh_iget(figure, "ORIENTATION");
    vlist *objects;
    vhash *colours;
    vscalar *elt;
    char *key;

    /* Calculate bounding box */
    fig_calc_bbox(figure);

    /* Write header info */
    fprintf(fp, "#FIG 3.2\n");
    fprintf(fp, "%s\n", orient == FIG_LANDSCAPE ? "Landscape" : "Portrait");
    fprintf(fp, "Center\n");
    fprintf(fp, "%s\n", vh_sgetref(figure, "UNITS"));
    fprintf(fp, "%s\n", vh_sgetref(figure, "PAPERSIZE"));
    fprintf(fp, "100.00\n");
    fprintf(fp, "Multiple\n");
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
    int radius = 1, npoints, type, subtype, pen_style = 0, cap_style = 0;
    float style_val = 1.0, width, height, thickness;
    int i, font_flags = 4, direction = 0;
    vlist *objects, *xp, *yp, *shape;
    vscalar *elt;

    type = vh_iget(object, "TYPE");
    subtype = vh_iget(object, "SUBTYPE");

    xp = vh_pget(object, "XP");
    yp = vh_pget(object, "YP");
    shape = vh_pget(object, "SHAPE");
    npoints = (xp != NULL ? vl_length(xp) : 0);

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
        fprintf(fp, "%d ", vh_iget(object, "ARROW_FORWARD"));
        fprintf(fp, "%d ", vh_iget(object, "ARROW_BACKWARD"));
        fprintf(fp, "%d\n", npoints);

        if (subtype == FIG_PICTURE)
            fprintf(fp, "\t0 %s\n", vh_sgetref(object, "PICFILE"));
        else
            fig_write_arrows(object, fp);

        fprintf(fp, "\t");
        for (i = 0; i < npoints; i++)
            fprintf(fp, " %d %d", vl_iget(xp, i), vl_iget(yp, i));
        fprintf(fp, "\n");

        break;

    case FIG_SPLINE:
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
        fprintf(fp, "%d ", cap_style);
        fprintf(fp, "%d ", vh_iget(object, "ARROW_FORWARD"));
        fprintf(fp, "%d ", vh_iget(object, "ARROW_BACKWARD"));
        fprintf(fp, "%d\n", npoints);

        fig_write_arrows(object, fp);

        fprintf(fp, "\t");
        for (i = 0; i < npoints; i++)
            fprintf(fp, " %d %d", vl_iget(xp, i), vl_iget(yp, i));
        fprintf(fp, "\n");

        fprintf(fp, "\t");
        for (i = 0; i < npoints; i++)
            fprintf(fp, " %g", vl_dget(shape, i));
        fprintf(fp, "\n");

        break;

    case FIG_TEXT:
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
        fprintf(fp, "%d ", cap_style);
        fprintf(fp, "%d ", direction);
        fprintf(fp, "%d ", vh_iget(object, "ARROW_FORWARD"));
        fprintf(fp, "%d ", vh_iget(object, "ARROW_BACKWARD"));

        for (i = 0; i < npoints; i++)
            fprintf(fp, " %g %g", vl_fget(xp, i), vl_fget(yp, i));

        fprintf(fp, "\n");
        fig_write_arrows(object, fp);
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
