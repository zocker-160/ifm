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

#define BIG 1000

/* Verbose flag */
extern int ifm_verbose;

/* Modified-path flag */
static int path_modify = 0;

/* Anchor-path room */
static vhash *ap_room = NULL;

/* Anchor-path visit flag */
static int ap_visit = 0;

/* Find-path visit flag */
static int fp_visit = 0;

/* Internal functions */
static int sort_tasks(vscalar **v1, vscalar **v2);

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
find_path(vhash *from, vhash *to, int *dist, int *len)
{
    vhash *node, *reach, *task, *item, *last, *step;
    int addnode, pdist, plen, ndist, nlen;
    vlist *need, *after, *before, *rlist;
    static vqueue *visit = NULL;
    vscalar *elt;

    /* Initialise visit-room search if required */
    if (to == NULL) {
        ap_room = from;
        ap_visit++;
    }

    if (from == NULL)
        return 0;

    /* Check trivial case */
    if (from == to) {
        *dist = *len = 0;
        return 1;
    }

    if (ifm_verbose && to != NULL) {
        indent(3);
        printf("find path to: %s", vh_sgetref(to, "DESC"));
    }

    /* Check for anchored search */
    if (from == ap_room && to != NULL) {
        /* See if target room has been visited */
        if (vh_iget(to, "AP_VISIT") == ap_visit) {
            *dist = vh_iget(to, "AP_DIST");
            *len = vh_iget(to, "AP_LEN");

            if (ifm_verbose && to != NULL)
                printf(" (cached: distance %d)\n", *len);

            return 1;
        }

        /* If not, but anchor room has, then fail */
        if (vh_iget(from, "AP_VISIT") == ap_visit) {
            if (ifm_verbose && to != NULL)
                printf(" (cached: no path)\n");

            return 0;
        }
    }

    if (ifm_verbose && to != NULL)
        printf("\n");

    /* Initialise search */
    if (visit == NULL)
        visit = vq_create();
    else
        vq_empty(visit);

    vq_pstore(visit, from, 0);

    vh_istore(from, "FP_DIST", 0);
    vh_istore(from, "FP_LEN", 0);
    vh_pstore(from, "FP_LAST", NULL);

    if (from == ap_room) {
        vh_istore(from, "AP_DIST", 0);
        vh_istore(from, "AP_LEN", 0);
    }

    last = from;
    fp_visit++;

    while (vq_length(visit) > 0) {
        /* Visit next unvisited node */
        node = vq_pget(visit);
        if (vh_iget(node, "FP_VISIT") == fp_visit)
            continue;

        plen = vh_iget(node, "FP_LEN");
        pdist = vh_iget(node, "FP_DIST");
        vh_istore(node, "FP_VISIT", fp_visit);
        if (from == ap_room)
            vh_istore(node, "AP_VISIT", ap_visit);
        last = node;

        if (ifm_verbose && node != from && to != NULL) {
            indent(4);
            printf("visit: %s (distance %d)\n",
                   vh_sgetref(node, "DESC"), plen);
        }

        /* If that's the destination, end */
        if (node == to) {
            *len = plen;
            *dist = pdist;
            return 1;
        }

        /* Add reachable nodes to the visit list */
        rlist = vh_pget(node, "REACH");
        vl_foreach(elt, rlist) {
            reach = vs_pget(elt);
            node = vh_pget(reach, "ROOM");
            if (vh_iget(node, "FP_VISIT") == fp_visit)
                continue;
            addnode = 1;

            /* Check required items have been obtained */
            if (addnode && (need = vh_pget(reach, "NEED")) != NULL) {
                vl_foreach(elt, need) {
                    item = vs_pget(elt);
                    step = vh_pget(item, "STEP");
                    if (!vh_iget(step, "DONE")) {
                        addnode = 0;
                        if (ifm_verbose && to != NULL) {
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
                        if (ifm_verbose && to != NULL) {
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
                        if (ifm_verbose && to != NULL) {
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
                        if (ifm_verbose && to != NULL) {
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
                        if (ifm_verbose && to != NULL) {
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
                        if (ifm_verbose && to != NULL) {
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

                ndist = pdist + 1;
                nlen = plen + vh_iget(reach, "LEN");
                vh_istore(node, "FP_DIST", ndist);
                vh_istore(node, "FP_LEN", nlen);

                if (from == ap_room) {
                    vh_istore(node, "AP_DIST", ndist);
                    vh_istore(node, "AP_LEN", nlen);
                }

                vq_pstore(visit, node, -nlen);
            }
        }
    }

    *len = plen;
    *dist = pdist;

    if (ifm_verbose && to != NULL) {
        indent(4);
        printf("failed: no path\n");
    }

    return 0;
}

/* Initialise path searches */
void
init_path(vhash *room)
{
    static vhash *last = NULL;
    extern vlist *tasklist;
    int dist, len;
    vscalar *elt;
    vhash *step;

    /* If same room and path not modified, do nothing */
    if (room == last && !path_modify)
        return;

    last = room;
    path_modify = 0;

    /* Visit all rooms, recording their distances from this one */
    find_path(room, NULL, &dist, &len);

    if (ifm_verbose) {
        indent(2);
        printf("update paths (max distance: %d)\n", len);
    }

    /* Record distance of each task */
    vl_foreach(elt, tasklist) {
        step = vs_pget(elt);
        room = vh_pget(step, "ROOM");

        if (room == NULL)
            len = 0;
        else if (vh_iget(room, "AP_VISIT") == ap_visit)
            len = vh_iget(room, "AP_LEN");
        else
            len = BIG;

        vh_istore(step, "SORT", len);
    }

    /* Sort tasks according to distance */
    vl_sort_inplace(tasklist, sort_tasks);
}

/* Flag path modification */
void
modify_path(void)
{
    path_modify = 1;

    if (ifm_verbose) {
        indent(2);
        printf("flag path update\n");
    }
}

/* Task sorting function */
int
sort_tasks(vscalar **v1, vscalar **v2)
{
    vhash *t1 = vs_pget(*v1);
    vhash *t2 = vs_pget(*v2);
    int s1 = vh_iget(t1, "SORT");
    int s2 = vh_iget(t2, "SORT");

    if (s1 < s2)
        return -1;
    else if (s1 > s2)
        return 1;

    return 0;
}
