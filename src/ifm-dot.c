/* Graphviz output driver */

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
#include "ifm-dot.h"

/* Task function list */
taskfuncs dot_taskfuncs = {
    dot_task_start,
    NULL,
    dot_task_finish,
};

/* Control variables */
static int show_rooms = 0;
static int show_orphans = 0;
static char *graph_attr = "";
static char *node_attr = "";
static char *link_attr = "";

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static void print_label(char *string);

/* Task functions */
void
dot_task_start(void)
{
    double width, height;
    char *title;

    /* Get control variables */
    set_map_vars();
    show_rooms = var_int("task_graph_rooms");
    show_orphans = var_int("task_graph_orphans");
    graph_attr = var_string("task_graph_attr");
    node_attr = var_string("task_graph_node");
    link_attr = var_string("task_graph_link");

    /* Get title */
    if (vh_exists(map, "TITLE"))
        title = vh_sgetref(map, "TITLE");
    else
        title = "Interactive Fiction game";

    /* Get page size */
    width = (page_width - page_margin) / 2.54;
    height = (page_height - page_margin) / 2.54;

    /* Write graph header */
    printf("digraph \"%s\" {\n", title);

    printf("    graph [size = \"%g,%g\", ratio = fill, %s];\n",
           height, width, graph_attr);

    printf("    rankdir = LR;\n");
    printf("    rotate = 90;\n");
    printf("    concentrate = true;\n");
}

void
dot_task_finish(void)
{
    vlist *list, *tolist, *nodes;
    vhash *step, *room, *rooms;
    char *node, *name;
    int cluster = 0;
    vscalar *elt;
    vgraph *g;

    /* Build directed graph */
    g = task_graph();

    /* Group tasks by room */
    rooms = vh_create();
    nodes = vg_node_list(g);

    vl_foreach(elt, nodes) {
        node = vs_sgetref(elt);
        if (!show_orphans && vg_node_links(g, node, NULL, NULL) == 0)
            continue;

        step = vg_node_pget(g, node);
        if (vh_iget(step, "IGNORE"))
            continue;

        room = vh_pget(step, "ROOM");
        name = room ? vh_sgetref(room, "DESC") : "";

        if ((list = vh_pget(rooms, name)) == NULL) {
            list = vl_create();
            vh_pstore(rooms, name, list);
        }

        vl_spush(list, node);
    }

    vl_destroy(nodes);

    /* Write nodes */
    printf("    node [%s];\n", node_attr);

    vh_foreach(name, elt, rooms) {
        list = vs_pget(elt);

        if (show_rooms) {
            if (strlen(name) > 0) {
                printf("    subgraph cluster_%d {\n", ++cluster);
                printf("        ");
                print_label(name);
                printf(";\n");
            } else {
                printf("    subgraph anywhere {\n");
            }
        }

        vl_foreach(elt, list) {
            node = vs_sgetref(elt);            
            step = vg_node_pget(g, node);
            printf("    ");

            if (show_rooms)
                printf("    ");

            printf("%s [", node);

            if (show_rooms || strlen(name) == 0)
                strcpy(buf, vh_sgetref(step, "DESC"));
            else
                sprintf(buf, "%s\\n[%s]", vh_sgetref(step, "DESC"), name);

            print_label(buf);
            printf("];\n");
        }

        if (show_rooms)
            printf("    }\n");
    }

    /* Write links */
    printf("    edge [%s];\n", link_attr);

    vh_foreach(name, elt, rooms) {
        list = vs_pget(elt);

        vl_foreach(elt, list) {
            node = vs_sgetref(elt);
            tolist = vg_node_to(g, node);
            vl_foreach(elt, tolist)
                printf("    %s -> %s;\n", node, vs_sgetref(elt));
        }
    }

    /* Write graph footer */
    printf("}\n");

    /* Clean up */
    v_destroy(rooms);
    vg_destroy(g);
}

/* Print a label, escaping doublequotes */
static void
print_label(char *string)
{
    printf("label = \"");

    while (*string != '\0') {
        if (*string == '"')
            putchar('\\');
        putchar(*string);
        string++;
    }

    putchar('"');
}
