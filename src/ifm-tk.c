/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Tcl/Tk output driver */

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
#include "ifm-map.h"
#include "ifm-task.h"
#include "ifm-util.h"
#include "ifm-vars.h"
#include "ifm-tk.h"
#include "ifm-text.h"

/* Map function list */
mapfuncs tk_mapfuncs = {
    tk_map_start,
    tk_map_section,
    tk_map_room,
    tk_map_link,
    NULL,
    NULL,
    NULL
};

/* Item function list */
itemfuncs tk_itemfuncs = {
    tk_item_start,
    tk_item_entry,
    tk_item_finish
};

/* Task function list */
taskfuncs tk_taskfuncs = {
    tk_task_start,
    tk_task_entry,
    tk_task_finish
};

/* Error function list */
errfuncs tk_errfuncs = {
    tk_warning,
    tk_error
};

/* Map functions */
void
tk_map_start(void)
{
    /* Set room names */
    setup_room_names(1, var_int("show_tags"));

    /* Canvas variables */
    printf("set ifm(mapwidth) %d\n",
           var_int("canvas_width"));
    printf("set ifm(mapheight) %d\n",
           var_int("canvas_height"));
    printf("set ifm(mapcol) %s\n",
           var_string("canvas_background_colour"));

    /* Room variables */
    printf("set ifm(roomsize) %g\n",
           var_real("room_size"));
    printf("set ifm(roomwidth) %g\n",
           var_real("room_width"));
    printf("set ifm(roomheight) %g\n",
           var_real("room_height"));
    printf("set ifm(roomlinewidth) %g\n",
           var_real("room_border_width"));
    printf("set ifm(roomshadow) %g\n",
           var_real("room_shadow_size"));
    printf("set ifm(roomfont) {%s}\n",
           var_string("room_text_fontdef"));
    printf("set ifm(puzzlecol) %s\n",
           var_string("room_puzzle_colour"));
    printf("set ifm(roomtextcol) %s\n",
           var_string("room_text_colour"));
    printf("set ifm(bordercol) %s\n",
           var_string("room_border_colour"));
    printf("set ifm(roomcol) %s\n",
           var_string("room_colour"));
    printf("set ifm(shadowcol) %s\n",
           var_string("room_shadow_colour"));
    printf("set ifm(exitwidth) %g\n",
           var_real("room_exit_width"));
    printf("set ifm(exitcol) %s\n",
           var_string("room_exit_colour"));

    /* Item variables */
    printf("set ifm(showitems) %d\n",
           var_int("show_items"));
    printf("set ifm(itemfont) {%s}\n",
           var_string("item_text_fontdef"));
    printf("set ifm(itemcol) {%s}\n",
           var_string("item_text_colour"));

    /* Link variables */
    printf("set ifm(linkcol) %s\n",
           var_string("link_colour"));
    printf("set ifm(linkwidth) %g\n",
           var_real("link_line_width"));
    printf("set ifm(linkspline) %s\n",
           (var_int("link_spline") ? "true" : "false"));
    printf("set ifm(linkspecialcol) %s\n",
           var_string("link_special_colour"));
    printf("set ifm(linktextcol) %s\n",
           var_string("link_text_colour"));
    printf("set ifm(linkfont) {%s}\n",
           var_string("link_text_fontdef"));
    printf("set ifm(linkupdown) {%s}\n",
           var_string("link_updown_string"));
    printf("set ifm(linkinout) {%s}\n",
           var_string("link_inout_string"));
}

void
tk_map_section(vhash *sect)
{
    char *title = vh_sgetref(sect, "TITLE");
    static char buf[BUFSIZ];
    static int num = 0;

    num++;

    if (title == NULL)
        sprintf(buf, "Map section %d", num);
    else
        strcpy(buf, title);

    printf("AddSect {%s} %d %d\n", buf,
           vh_iget(sect, "XLEN"),
           vh_iget(sect, "YLEN"));
}

void
tk_map_room(vhash *room)
{
    vlist *items, *ex, *ey;
    char *itemlist = NULL;
    int x, y, xoff, yoff;
    vscalar *elt;

    /* Build item list if required */
    items = vh_pget(room, "ITEMS");
    if (items != NULL && vl_length(items) > 0) {
        vhash *item;
        vlist *list;

        list = vl_create();
        vl_foreach(elt, items) {
            item = vs_pget(elt);
            if (!vh_iget(item, "HIDDEN"))
                vl_spush(list, vh_sgetref(item, "DESC"));
        }

        if (vl_length(list) > 0)
            itemlist = vl_join(list, ", ");
        vl_destroy(list);
    }

    /* Do room command */
    x = vh_iget(room, "X");
    y = vh_iget(room, "Y");
    printf("AddRoom {%s} {%s} %d %d %d\n",
           vh_sgetref(room, "RDESC"),
           (itemlist != NULL ? itemlist : ""), x, y,
           vh_iget(room, "PUZZLE"));

    /* Do room exit commands (if any) */
    ex = vh_pget(room, "EX");
    ey = vh_pget(room, "EY");
    if (ex != NULL) {
        while (vl_length(ex) > 0) {
            xoff = vl_ishift(ex);
            yoff = vl_ishift(ey);
            printf("AddExit {%d %d} {%d %d}\n", x, x + xoff, y, y + yoff);
        }
    }
}

void
tk_map_link(vhash *link)
{
    vlist *x = vh_pget(link, "X");
    vlist *y = vh_pget(link, "Y");
    int go = vh_iget(link, "GO");
    int updown = (go == D_UP || go == D_DOWN);
    int inout = (go == D_IN || go == D_OUT);

    printf("AddLink");
    printf(" {%s}", vl_join(x, " "));
    printf(" {%s}", vl_join(y, " "));
    printf(" %d %d %d %d\n",
           updown, inout,
           vh_iget(link, "ONEWAY"),
           vh_iget(link, "SPECIAL"));
}

/* Item functions */
void
tk_item_start(void)
{
    printf("set itemlist {");
}

void
tk_item_entry(vhash *item)
{
    text_item_entry(item);
}

void
tk_item_finish(void)
{
    printf("}\n");
}

/* Task functions */
void
tk_task_start(void)
{
    printf("set tasklist {");
}

void
tk_task_entry(vhash *task)
{
    text_task_entry(task);
}

void
tk_task_finish(void)
{
    text_task_finish();
    printf("}\n");
}

/* Error functions */
void
tk_warning(char *file, int line, char *msg)
{
    if (line > 0) {
        printf("GotoLine %d\n", line);
        printf("Warning {Warning: line %d: %s}\n", line, msg);
    } else {
        printf("Warning {Warning: %s}\n", msg);
    }
}

void
tk_error(char *file, int line, char *msg)
{
    if (line > 0) {
        printf("GotoLine %d\n", line);
        printf("Error {Error: line %d: %s}\n", line, msg);
    } else {
        printf("Error {Error: %s}\n", msg);
    }

    exit(0);
}
