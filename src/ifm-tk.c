/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Tcl/Tk output driver */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "ifm.h"
#include "ifm-parse.h"
#include "ifm-tk.h"
#include "ifm-text.h"

/* Map function list */
mapfuncs tk_mapfuncs = {
    tk_map_start,
    tk_map_section,
    tk_map_room,
    tk_map_link,
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
    char *title = get_string("title", NULL);

    /* Mark joined rooms */
    mark_joins();

    /* Set variables */
    printf("set ifm(mapwidth) %d\n", get_int("map_width", 8));
    printf("set ifm(mapheight) %d\n", get_int("map_height", 6));
    printf("set ifm(mapcol) %s\n", get_string("map_colour", "wheat"));

    printf("set ifm(roomsize) %g\n", get_real("room_size", 3.0));
    printf("set ifm(roomwidth) %g\n", get_real("room_width", 0.8));
    printf("set ifm(roomheight) %g\n", get_real("room_height", 0.65));
    printf("set ifm(roomlinewidth) %d\n", get_int("room_linewidth", 2));
    printf("set ifm(roomfont) {%s}\n", get_string("room_font",
                                                  "Times 10 bold"));
    printf("set ifm(puzzlecol) %s\n", get_string("room_puzzle_colour",
                                                 "grey80"));

    printf("set ifm(exitlinewidth) %d\n", get_int("exit_linewidth", 2));
    printf("set ifm(exitcol) %s\n", get_string("exit_colour", "red"));

    printf("set ifm(showitems) %d\n", get_int("show_items", 0));
    printf("set ifm(itemfont) {%s}\n", get_string("item_font",
                                                  "Times 8 italic"));

    printf("set ifm(linklinewidth) %d\n", get_int("link_linewidth", 1));
    printf("set ifm(curvelines) %s\n", (get_int("link_spline", 1) ?
                                        "true" : "false"));
    printf("set ifm(specialcol) %s\n", get_string("link_special_colour",
                                                  "blue"));

    printf("set ifm(labelcol) %s\n", get_string("label_colour", "red"));
    printf("set ifm(labelfont) {%s}\n", get_string("label_font",
                                                   "Times 8 bold"));
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
           vh_sgetref(room, "JDESC"),
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
    int updown = (go == UP || go == DOWN);
    int inout = (go == IN || go == OUT);

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
