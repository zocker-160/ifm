/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Path building functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ifm.h"

/* Connect rooms as a directed graph */
void
connect_rooms()
{
    vhash *room, *link, *join, *reach, *from, *to;
    vlist *rlist;
    vscalar *elt;
    int oneway;

    /* Create lists of reachable rooms from each room */
    FOREACH(elt, rooms) {
        room = vs_pval(elt);
        vh_pstore(room, "REACH", vl_create());
    }

    /* Build link connections */
    FOREACH(elt, links) {
        link = vs_pval(elt);
        from = vh_pget(link, "FROM");
        to = vh_pget(link, "TO");
        oneway = vh_iget(link, "ONEWAY");

        rlist = vh_pget(from, "REACH");
        reach = vh_create();
        vh_pstore(reach, "ROOM", to);
        vh_pstore(reach, "NEED", vh_pget(link, "NEED"));
        vh_pstore(reach, "AFTER", vh_pget(link, "AFTER"));
        vl_ppush(rlist, reach);

        if (!oneway) {
            rlist = vh_pget(to, "REACH");
            reach = vh_create();
            vh_pstore(reach, "ROOM", from);
            vh_pstore(reach, "NEED", vh_pget(link, "NEED"));
            vh_pstore(reach, "AFTER", vh_pget(link, "AFTER"));
            vl_ppush(rlist, reach);
        }
    }

    /* Build join connections */
    FOREACH(elt, joins) {
        join = vs_pval(elt);
        from = vh_pget(join, "FROM");
        to = vh_pget(join, "TO");
        oneway = vh_iget(join, "ONEWAY");

        rlist = vh_pget(from, "REACH");
        reach = vh_create();
        vh_pstore(reach, "ROOM", to);
        vh_pstore(reach, "NEED", vh_pget(join, "NEED"));
        vh_pstore(reach, "AFTER", vh_pget(join, "AFTER"));
        vl_ppush(rlist, reach);

        if (!oneway) {
            rlist = vh_pget(to, "REACH");
            reach = vh_create();
            vh_pstore(reach, "ROOM", from);
            vh_pstore(reach, "NEED", vh_pget(join, "NEED"));
            vh_pstore(reach, "AFTER", vh_pget(join, "AFTER"));
            vl_ppush(rlist, reach);
        }
    }
}

/* Find a path between two rooms */
int
find_path(vlist *path, vhash *from, vhash *to)
{
    vhash *node, *reach, *task, *item, *last, *step;
    vlist *visit, *need, *after, *rlist;
    int found = 0, length = 0, addnode;
    static int visit_id = 0;
    vscalar *elt;

    /* Initialise */
    visit = vl_create();
    vl_ppush(visit, from);
    vh_pstore(from, "FP_LAST", NULL);
    last = from;
    visit_id++;

    while (vl_length(visit) > 0) {
        /* Visit next unvisited node */
        node = vl_pshift(visit);
        if (vh_iget(node, "FP_VISIT") == visit_id)
            continue;
        vh_istore(node, "FP_VISIT", visit_id);
        last = node;

        /* If that's the destination, end */
        if (node == to) {
            found = 1;
            break;
        }

        /* Add reachable nodes to the visit list */
        rlist = vh_pget(node, "REACH");
        FOREACH(elt, rlist) {
            reach = vs_pval(elt);
            node = vh_pget(reach, "ROOM");
            if (vh_iget(node, "FP_VISIT") == visit_id)
                continue;
            addnode = 1;

            /* Check items needed */
            need = vh_pget(reach, "NEED");
            if (need != NULL) {
                FOREACH(elt, need) {
                    item = vs_pval(elt);
                    step = vh_pget(item, "STEP");
                    if (!vh_iget(step, "DONE"))
                        addnode = 0;
                }
            }

            /* Check tasks needing to be done first */
            after = vh_pget(reach, "AFTER");
            if (after != NULL) {
                FOREACH(elt, after) {
                    task = vs_pval(elt);
                    step = vh_pget(task, "STEP");
                    if (!vh_iget(step, "DONE"))
                        addnode = 0;
                }
            }

            /* Add node to visit list if reachable */
            if (addnode) {
                if (node != from)
                    vh_pstore(node, "FP_LAST", last);
                vl_ppush(visit, node);
            }
        }
    }

    vl_destroy(visit);

    /* Do nothing if no path */
    if (!found) return 0;

    /* Initialise path */
    if (path != NULL)
        vl_empty(path);

    /* Build the node list if required */
    node = to;
    while (node != NULL) {
        if (path != NULL)
            vl_punshift(path, node);
        node = vh_pget(node, "FP_LAST");
        length++;
    }

    return length;
}
