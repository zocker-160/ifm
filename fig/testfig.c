/* Figlib test */

#include "fig.h"

int
main(void)
{
    vhash *figure, *box, *group, *text, *pic, *line, *spline, *arc;

    v_debug(V_DBG_PTRS);

    figure = fig_create(FIG_INCHES);
    group = fig_create_compound(figure);
    text = fig_create_text(group, 6.0, 6.0, "Hi there");
    box = fig_create_box(group, 3.0, 3.0, 5.0, 6.0);
    line = fig_create_line(figure, 1.0, 1.0, 7.0, 3.0);
    spline = fig_create_spline(figure, FIG_OPEN_INTERP);

#if 0
    arc = fig_create_arc(figure, FIG_WEDGE, 10, 10, 4, 4, 6, 2, 8, 4);
#endif

    fig_create_point(spline, 1.0, 1.0);
    fig_create_point(spline, 1.0, 2.0);
    fig_create_point(spline, 2.0, 2.0);
    fig_create_point(spline, 2.0, 3.0);

    fig_set_colour(spline, 0.0, 0.0, 1.0);
    fig_set_font(text, "Helvet", 20.0);
    fig_set_fillcolour(box, 1.0, 1.0, 0.0);
    fig_set_colour(box, 0.0, 1.0, 0.0);
    fig_set_colour(text, 1.0, 0.0, 0.0);
    fig_set_name(box, "My box");
    fig_set_arrow(line, 1, 0);
    fig_set_arrow(spline, 1, 0);

#if 0
    pic = fig_create_picture(figure, 4.0, 2.0, 6.6, 6.0, "piccie.jpg");
    fig_set_depth(pic, 50);
#endif

    fig_write_figure(figure, stdout);

    return 0;
}
