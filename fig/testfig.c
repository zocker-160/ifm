/* Figlib test */

#include "fig.h"

int
main(void)
{
    vhash *figure, *box, *group, *text, *pic, *line;

    v_debug(V_DBG_PTRS);

    figure = fig_create();

    group = fig_create_compound(figure);
    text = fig_create_text(group, 6.0, 6.0, "Hi there");
    box = fig_create_box(group, 3.0, 3.0, 5.0, 6.0);
    line = fig_create_line(figure, 1.0, 1.0, 15.0, 3.0);

    fig_set_font(text, "Helvet", 50.0);
    fig_set_fillcolour(box, 1.0, 1.0, 0.0);
    fig_set_colour(box, 0.0, 1.0, 0.0);
    fig_set_colour(text, 1.0, 0.0, 0.0);
    fig_set_name(box, "My box");
    fig_set_arrow(line, 1, 0);

#if 1
    pic = fig_create_picture(figure, 4.0, 2.0, 6.6, 6.0, "piccie.jpg");
    fig_set_depth(pic, 200);
#endif

    fig_write_figure(figure, stdout);

    return 0;
}
