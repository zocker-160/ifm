/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Path building functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ifm.h"

/* Verbose flag */
extern int ifm_verbose;

/* Connect rooms as a directed graph */
void
connect_rooms(void)
{
    vhash *room, *link, *join, *reach, *from, *to, *task;
    int oneway, len;
    vlist *rlist;
    vscalar *elt;

    if (ifm_verbose)
        printf("\nConnecting rooms...\n");

    /* Create lists of reachable rooms from each room */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        vh_pstore(room, "REACH", vl_create());
    }

    /* Build link connections */
    vl_foreach(elt, links) {
        link = vs_pget(elt);
        from = vh_pget(link, "FROM");
        to = vh_pget(link, "TO");
        oneway = vh_iget(link, "ONEWAY");
        len = vh_iget(link, "LEN");

        if (ifm_verbose) {
            indent(1);
            printf("link `%s' to `%s'",
                   vh_sgetref(from, "DESC"),
                   vh_sgetref(to, "DESC"));
            if (len > 1)
                printf(" (distance %d)", len);
            if (oneway)
                printf(" (oneway)");
            printf("\n");
        }

        /* From -> to */
        rlist = vh_pget(from, "REACH");
        reach = vh_create();

        vh_pstore(reach, "ROOM", to);
        vh_pstore(reach, "NEED", vh_pget(link, "NEED"));
        vh_pstore(reach, "BEFORE", vh_pget(link, "BEFORE"));
        vh_pstore(reach, "AFTER", vh_pget(link, "AFTER"));
        vh_istore(reach, "LEN", V_MAX(len, 1));

        vl_ppush(rlist, reach);

        /* To -> from if not one-way */
        if (!oneway) {
            rlist = vh_pget(to, "REACH");
            reach = vh_create();

            vh_pstore(reach, "ROOM", from);
            vh_pstore(reach, "NEED", vh_pget(link, "NEED"));
            vh_pstore(reach, "BEFORE", vh_pget(link, "BEFORE"));
            vh_pstore(reach, "AFTER", vh_pget(link, "AFTER"));
            vh_istore(reach, "LEN", V_MAX(len, 1));

            vl_ppush(rlist, reach);
        }
    }

    /* Build join connections */
    vl_foreach(elt, joins) {
        join = vs_pget(elt);
        from = vh_pget(join, "FROM");
        to = vh_pget(join, "TO");
        oneway = vh_iget(join, "ONEWAY");
        len = vh_iget(join, "LEN");

        if (ifm_verbose) {
            indent(1);
            printf("join `%s' to `%s'",
                   vh_sgetref(from, "DESC"),
                   vh_sgetref(to, "DESC"));
            if (len > 1)
                printf(" (distance %d)", len);
            if (oneway)
                printf(" (oneway)");
            printf("\n");
        }

        /* From -> to */
        rlist = vh_pget(from, "REACH");
        reach = vh_create();

        vh_pstore(reach, "ROOM", to);
        vh_pstore(reach, "NEED", vh_pget(join, "NEED"));
        vh_pstore(reach, "BEFORE", vh_pget(join, "BEFORE"));
        vh_pstore(reach, "AFTER", vh_pget(join, "AFTER"));
        vh_istore(reach, "LEN", V_MAX(len, 1));

        vl_ppush(rlist, reach);

        /* To -> from if not one-way */
        if (!oneway) {
            rlist = vh_pget(to, "REACH");
            reach = vh_create();

            vh_pstore(reach, "ROOM", from);
            vh_pstore(reach, "NEED", vh_pget(join, "NEED"));
            vh_pstore(reach, "BEFORE", vh_pget(join, "BEFORE"));
            vh_pstore(reach, "AFTER", vh_pget(join, "AFTER"));
            vh_istore(reach, "LEN", V_MAX(len, 1));

            vl_ppush(rlist, reach);
        }
    }
}

/* Find a path between two rooms */
int
find_path(vlist *path, vhash *from, vhash *to, int maxlen,
          int *dist, int *len)
{
    vhash *node, *reach, *task, *item, *last, *step;
    vlist *need, *after, *before, *rlist;
    int found = 0, addnode, pdist, plen;
    static vqueue *visit = NULL;
    static int visit_id = 0;
    vscalar *elt;

    if (from == to) {
        *dist = *len = 0;
        return 1;
    }

    /* Initialise */
    if (visit == NULL)
        visit = vq_create();
    else
        vq_empty(visit);

    vq_pstore(visit, from, 0);

    vh_istore(from, "DIST", 0);
    vh_istore(from, "LEN", 0);
    vh_pstore(from, "FP_LAST", NULL);

    last = from;
    visit_id++;

    if (ifm_verbose) {
        indent(3);
        printf("find path: `%s' to `%s'\n",
               vh_sgetref(from, "DESC"),
               vh_sgetref(to, "DESC"));
    }

    while (vq_length(visit) > 0) {
        /* Visit next unvisited node */
        node = vq_pget(visit);
        if (vh_iget(node, "FP_VISIT") == visit_id)
            continue;

        plen = vh_iget(node, "LEN");
        pdist = vh_iget(node, "DIST");
        vh_istore(node, "FP_VISIT", visit_id);
        last = node;

        if (ifm_verbose && node != from) {
            indent(4);
            printf("visit: %s (distance %d)\n",
                   vh_sgetref(node, "DESC"), plen);
        }

        /* If that's the destination, end */
        if (node == to) {
            found = 1;
            break;
        }

        /* If path is too long, end */
        if (plen >= maxlen)
            break;

        /* Add reachable nodes to the visit list */
        rlist = vh_pget(node, "REACH");
        vl_foreach(elt, rlist) {
            reach = vs_pget(elt);
            node = vh_pget(reach, "ROOM");
            if (vh_iget(node, "FP_VISIT") == visit_id)
                continue;
            addnode = 1;

            /* Check required items have been obtained */
            if (addnode && (need = vh_pget(reach, "NEED")) != NULL) {
                vl_foreach(elt, need) {
                    item = vs_pget(elt);
                    step = vh_pget(item, "STEP");
                    if (!vh_iget(step, "DONE")) {
                        addnode = 0;
                        if (ifm_verbose) {
                            indent(4);
                            printf("blocked link: %s (need %s)\n",
                                   vh_sgetref(node, "DESC"),
                                   vh_sgetref(item, "DESC"));
                        }
                    }
                }
            }

            if (addnode && (need = vh_pget(node, "NEED")) != NULL) {
                vl_foreach(elt, need) {
                    item = vs_pget(elt);
                    step = vh_pget(item, "STEP");
                    if (!vh_iget(step, "DONE")) {
                        addnode = 0;
                        if (ifm_verbose) {
                            indent(4);
                            printf("blocked room: %s (need %s)\n",
                                   vh_sgetref(node, "DESC"),
                                   vh_sgetref(item, "DESC"));
                        }
                    }
                }
            }

            /* Check status of required tasks */
            if (addnode && (before = vh_pget(reach, "BEFORE")) != NULL) {
                vl_foreach(elt, before) {
                    task = vs_pget(elt);
                    step = vh_pget(task, "STEP");
                    if (vh_iget(step, "DONE")) {
                        addnode = 0;
                        if (ifm_verbose) {
                            indent(4);
                            printf("blocked link: %s (done `%s')\n",
                                   vh_sgetref(node, "DESC"),
                                   vh_sgetref(task, "DESC"));
                        }
                    }
                }
            }

            if (addnode && (after = vh_pget(reach, "AFTER")) != NULL) {
                vl_foreach(elt, after) {
                    task = vs_pget(elt);
                    step = vh_pget(task, "STEP");
                    if (!vh_iget(step, "DONE")) {
                        addnode = 0;
                        if (ifm_verbose) {
                            indent(4);
                            printf("blocked link: %s (not done `%s')\n",
                                   vh_sgetref(node, "DESC"),
                                   vh_sgetref(task, "DESC"));
                        }
                    }
                }
            }

            /* Check room can be visited */
            if (addnode && (before = vh_pget(node, "BEFORE")) != NULL) {
                vl_foreach(elt, before) {
                    task = vs_pget(elt);
                    step = vh_pget(task, "STEP");
                    if (vh_iget(step, "DONE")) {
                        addnode = 0;
                        if (ifm_verbose) {
                            indent(4);
                            printf("blocked room: %s (done `%s')\n",
                                   vh_sgetref(node, "DESC"),
                                   vh_sgetref(task, "DESC"));
                        }
                    }
                }
            }

            if (addnode && (after = vh_pget(node, "AFTER")) != NULL) {
                vl_foreach(elt, after) {
                    task = vs_pget(elt);
                    step = vh_pget(task, "STEP");
                    if (!vh_iget(step, "DONE")) {
                        addnode = 0;
                        if (ifm_verbose) {
                            indent(4);
                            printf("blocked room: %s (not done `%s')\n",
                                   vh_sgetref(node, "DESC"),
                                   vh_sgetref(task, "DESC"));
                        }
                    }
                }
            }

            /* Add node to visit list if reachable */
            if (addnode) {
                if (node != from)
                    vh_pstore(node, "FP_LAST", last);

                vh_istore(node, "DIST", pdist + 1);
                vh_istore(node, "LEN", plen + vh_iget(reach, "LEN"));

                vq_pstore(visit, node, -vh_iget(node, "LEN"));
            }
        }
    }

    /* Do nothing if no path */
    if (!found) {
        if (ifm_verbose) {
            indent(4);
            printf("failed: %s\n",
                   (plen >= maxlen ? "too far away" : "no path"));
        }

        return 0;
    }

    /* Build the node list if required */
    if (path != NULL) {
        vl_empty(path);
        node = to;
        while (node != NULL) {
            vl_punshift(path, node);
            node = vh_pget(node, "FP_LAST");
        }
    }

    *len = plen;
    *dist = pdist;

    return 1;
}
