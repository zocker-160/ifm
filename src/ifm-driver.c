/* Driver functions */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <vars.h>

#include "ifm-driver.h"
#include "ifm-util.h"
#include "ifm-vars.h"

#define SET_BOOL(name)     name = var_int(#name)
#define SET_COLOUR(name)   name = var_colour(#name)
#define SET_REAL(name)     name = var_real(#name)
#define SET_FONT(name)     SET_STRING(name)
#define SET_FONTSIZE(name) name = var_real(#name) * font_scale
#define SET_INT(name)      name= var_int(#name)
#define SET_STRING(name)   name = var_string(#name)

/* Control variables */
char *room_text_font, *room_text_colour, *room_colour;
char *room_border_colour, *room_shadow_colour, *item_text_font;
char *item_text_colour, *link_colour, *link_text_colour;
char *link_text_font, *link_updown_string, *link_inout_string;
char *map_text_font, *page_border_colour, *page_background_colour;
char *title_font, *title_colour, *map_text_colour;
char *room_exit_colour, *page_size;

float room_text_fontsize, room_border_width, room_shadow_xoff;
float room_shadow_yoff, room_exit_width, item_text_fontsize;
float link_arrow_size, link_text_fontsize, link_line_width;
float map_text_fontsize, title_fontsize, font_scale, page_margin;
float room_width, room_height, room_size, page_width, page_height;

int room_border_dashed, show_items, link_dashed, show_border;
int show_title, show_tags, link_spline;

/* Set map style variables */
void
set_map_vars(void)
{
    SET_BOOL(show_border);
    SET_BOOL(show_tags);
    SET_BOOL(show_title);

    SET_COLOUR(map_text_colour);
    SET_COLOUR(page_background_colour);
    SET_COLOUR(page_border_colour);
    SET_COLOUR(title_colour);

    SET_FONT(map_text_font);
    SET_FONT(title_font);

    SET_FONTSIZE(map_text_fontsize);
    SET_FONTSIZE(title_fontsize);

    SET_REAL(font_scale);
    SET_REAL(page_margin);

    SET_STRING(page_size);
    if (!get_papersize(page_size, &page_width, &page_height))
        fatal("invalid paper size: %s", page_size);

    if (VAR_DEF("page_height"))
        SET_REAL(page_height);

    if (VAR_DEF("page_width"))
        SET_REAL(page_width);

    SET_REAL(room_size);
    room_size = V_MAX(room_size, 0.1);

    SET_REAL(room_height);
    SET_REAL(room_width);
}

/* Set room style variables */
void
set_room_vars(void)
{
    SET_BOOL(room_border_dashed);
    SET_BOOL(show_items);

    SET_COLOUR(item_text_colour);
    SET_COLOUR(room_border_colour);
    SET_COLOUR(room_colour);
    SET_COLOUR(room_exit_colour);
    SET_COLOUR(room_shadow_colour);
    SET_COLOUR(room_text_colour);

    SET_FONT(item_text_font);
    SET_FONT(room_text_font);

    SET_FONTSIZE(item_text_fontsize);
    SET_FONTSIZE(room_text_fontsize);

    SET_REAL(room_border_width);
    SET_REAL(room_exit_width);
    SET_REAL(room_shadow_xoff);
    SET_REAL(room_shadow_yoff);
}

/* Set link style variables */
void
set_link_vars(void)
{
    SET_BOOL(link_dashed);
    SET_BOOL(link_spline);

    SET_COLOUR(link_colour);
    SET_COLOUR(link_text_colour);

    SET_FONT(link_text_font);

    SET_FONTSIZE(link_text_fontsize);

    SET_REAL(link_arrow_size);
    SET_REAL(link_line_width);

    SET_STRING(link_inout_string);
    SET_STRING(link_updown_string);
}
