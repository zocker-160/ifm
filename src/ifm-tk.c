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
    tk_map_finish
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
    printf("set ifm(pagewidth) %s\n", get_string("page_width", "7i"));
    printf("set ifm(pageheight) %s\n", get_string("page_height", "7i"));

    printf("set ifm(mapwidth) %d\n", get_int("map_width", 8));
    printf("set ifm(mapheight) %d\n", get_int("map_height", 6));

    printf("set ifm(mapcol) %s\n", get_string("map_colour", "Wheat"));

    printf("set ifm(framewidth) %g\n", get_real("box_width", 3.0));
    printf("set ifm(frameheight) %g\n", get_real("box_height", 3.0));

    printf("set ifm(roomwidth) %g\n", get_real("room_width", 0.8));
    printf("set ifm(roomheight) %g\n", get_real("room_height", 0.65));

    printf("set ifm(roomlinewidth) %d\n", get_int("room_linewidth", 2));

    printf("set ifm(roomfont) {%s}\n", get_string("room_font",
                                                  "Times 10 bold"));

    printf("set ifm(puzzlecol) %s\n", get_string("room_puzzle_colour",
                                                 "grey80"));

    printf("set ifm(linklinewidth) %d\n", get_int("link_linewidth", 1));

    printf("set ifm(curvelines) %s\n", (get_int("link_spline", 1) ?
                                        "true" : "false"));

    printf("set ifm(specialcol) %s\n", get_string("link_special_colour",
                                                  "grey60"));

    printf("set ifm(labelfont) {%s}\n", get_string("label_font",
                                                   "Times 8 bold"));

    printf("set ifm(labelcol) %s\n", get_string("label_colour",
                                                "red"));
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
    static int room_num = 0;

    vh_istore(room, "NUM", ++room_num);
    printf("AddRoom {%s} %d %d %d\n",
           vh_sgetref(room, "JDESC"),
           vh_iget(room, "X"),
           vh_iget(room, "Y"),
           vh_iget(room, "PUZZLE"));
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

void
tk_map_finish(void)
{
    vhash *join, *from, *to, *h1, *h2;
    int go, updown, inout;
    vscalar *elt;
    vlist *keys;
    char *key;

    /* Write joins */
    vl_foreach(elt, joins) {
        join = vs_pget(elt);
        from = vh_pget(join, "FROM");
        to = vh_pget(join, "TO");

        go = vh_iget(join, "GO");
        updown = (go == UP || go == DOWN);
        inout = (go == IN || go == OUT);

        printf("AddJoin %d %d %d %d %d\n",
               vh_iget(from, "NUM"),
               vh_iget(to, "NUM"),
               updown, inout,
               vh_iget(join, "ONEWAY"));
    }
}

/* Item functions */
void
tk_item_start(void)
{
    printf("set itemlist {");
    text_item_start();
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
    text_task_start();
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
    if (line > 0)
        printf("Warning {Warning: line %d: %s}\n", line, msg);
    else
        printf("Warning {Warning: %s}\n", msg);
}

void
tk_error(char *file, int line, char *msg)
{
    if (line > 0)
        printf("Error {Error: line %d: %s}\n", line, msg);
    else
        printf("Error {Error: %s}\n", msg);

    exit(0);
}
