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
#include <vars.h>

#include "ifm-map.h"
#include "ifm-path.h"
#include "ifm-task.h"
#include "ifm-util.h"

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
    vhash *room, *link, *join, *reach, *from, *to;
    int oneway, len, goflag, dir;
    vlist *rlist;
    vscalar *elt;
    char *cmd;

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

        oneway = vh_iget(link, "ONEWAY");
        len = vh_iget(link, "LEN");

        from = vh_pget(link, "FROM");
        to = vh_pget(link, "TO");

        /* From -> to */
        rlist = vh_pget(from, "REACH");
        reach = vh_create();

        cmd = vh_sgetref(link, "TO_CMD");
        goflag = vh_iget(link, "GO");
        dir = vh_iget(link, "TO_DIR");

        if (cmd == NULL && goflag)
            cmd = dirinfo[goflag].sname;
        if (cmd == NULL)
            cmd = dirinfo[dir].sname;
        vh_sstore(reach, "CMD", cmd);

        vh_pstore(reach, "FROM", from);
        vh_pstore(reach, "TO", to);
        vh_pstore(reach, "NEED", vh_pget(link, "NEED"));
        vh_pstore(reach, "BEFORE", vh_pget(link, "BEFORE"));
        vh_pstore(reach, "AFTER", vh_pget(link, "AFTER"));
        vh_istore(reach, "LEN", V_MAX(len, 1));

        vl_ppush(rlist, reach);

        if (ifm_verbose) {
            indent(1);
            printf("link `%s' to `%s' (%s)",
                   vh_sgetref(from, "DESC"),
                   vh_sgetref(to, "DESC"),
                   cmd);
            if (len > 1)
                printf(" (distance %d)", len);
            printf("\n");
        }

        /* To -> from if not one-way */
        if (!oneway) {
            rlist = vh_pget(to, "REACH");
            reach = vh_create();

            cmd = vh_sgetref(link, "FROM_CMD");
            goflag = dirinfo[goflag].odir;
            dir = vh_iget(link, "FROM_DIR");

            if (cmd == NULL && goflag)
                cmd = dirinfo[goflag].sname;
            if (cmd == NULL)
                cmd = dirinfo[dir].sname;
            vh_sstore(reach, "CMD", cmd);

            vh_pstore(reach, "FROM", to);
            vh_pstore(reach, "TO", from);
            vh_pstore(reach, "NEED", vh_pget(link, "NEED"));
            vh_pstore(reach, "BEFORE", vh_pget(link, "BEFORE"));
            vh_pstore(reach, "AFTER", vh_pget(link, "AFTER"));
            vh_istore(reach, "LEN", V_MAX(len, 1));

            vl_ppush(rlist, reach);

            if (ifm_verbose) {
                indent(1);
                printf("link `%s' to `%s' (%s)",
                       vh_sgetref(to, "DESC"),
                       vh_sgetref(from, "DESC"),
                       cmd);
                if (len > 1)
                    printf(" (distance %d)", len);
                printf("\n");
            }
        }
    }

    /* Build join connections */
    vl_foreach(elt, joins) {
        join = vs_pget(elt);

        oneway = vh_iget(join, "ONEWAY");
        len = vh_iget(join, "LEN");

        from = vh_pget(join, "FROM");
        to = vh_pget(join, "TO");

        /* From -> to */
        rlist = vh_pget(from, "REACH");
        reach = vh_create();

        cmd = vh_sgetref(join, "TO_CMD");
        goflag = vh_iget(join, "GO");

        if (cmd == NULL && goflag)
            cmd = dirinfo[goflag].sname;
        vh_sstore(reach, "CMD", cmd == NULL ? "?" : cmd);

        vh_pstore(reach, "FROM", from);
        vh_pstore(reach, "TO", to);
        vh_pstore(reach, "NEED", vh_pget(join, "NEED"));
        vh_pstore(reach, "BEFORE", vh_pget(join, "BEFORE"));
        vh_pstore(reach, "AFTER", vh_pget(join, "AFTER"));
        vh_istore(reach, "LEN", V_MAX(len, 1));

        vl_ppush(rlist, reach);

        if (ifm_verbose) {
            indent(1);
            printf("join `%s' to `%s' (%s)",
                   vh_sgetref(from, "DESC"),
                   vh_sgetref(to, "DESC"),
                   cmd);
            if (len > 1)
                printf(" (distance %d)", len);
            printf("\n");
        }

        /* To -> from if not one-way */
        if (!oneway) {
            rlist = vh_pget(to, "REACH");
            reach = vh_create();

            cmd = vh_sgetref(join, "FROM_CMD");
            goflag = dirinfo[goflag].odir;

            if (cmd == NULL && goflag)
                cmd = dirinfo[goflag].sname;
            vh_sstore(reach, "CMD", cmd == NULL ? "?" : cmd);

            vh_pstore(reach, "FROM", to);
            vh_pstore(reach, "TO", from);
            vh_pstore(reach, "NEED", vh_pget(join, "NEED"));
            vh_pstore(reach, "BEFORE", vh_pget(join, "BEFORE"));
            vh_pstore(reach, "AFTER", vh_pget(join, "AFTER"));
            vh_istore(reach, "LEN", V_MAX(len, 1));

            vl_ppush(rlist, reach);

            if (ifm_verbose) {
                indent(1);
                printf("join `%s' to `%s' (%s)",
                       vh_sgetref(to, "DESC"),
                       vh_sgetref(from, "DESC"),
                       cmd);
                if (len > 1)
                    printf(" (distance %d)", len);
                printf("\n");
            }
        }
    }
}

/* Find a path between two rooms */
int
find_path(vhash *from, vhash *to, int *dist, int *len)
{
    vhash *node, *reach, *task, *item, *step;
    vlist *need, *after, *before, *rlist;
    static vqueue *visit = NULL;
    int addnode, ndist, nlen;
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

    if (from == ap_room) {
        vh_istore(from, "AP_DIST", 0);
        vh_istore(from, "AP_LEN", 0);
        vh_pstore(from, "AP_LAST", NULL);
    }

    fp_visit++;

    while (vq_length(visit) > 0) {
        /* Visit next unvisited node */
        node = vq_pget(visit);
        if (vh_iget(node, "FP_VISIT") == fp_visit)
            continue;

        *len = vh_iget(node, "FP_LEN");
        *dist = vh_iget(node, "FP_DIST");
        vh_istore(node, "FP_VISIT", fp_visit);

        if (from == ap_room)
            vh_istore(node, "AP_VISIT", ap_visit);

        if (ifm_verbose && node != from && to != NULL) {
            indent(4);
            printf("visit: %s (distance %d)\n",
                   vh_sgetref(node, "DESC"), *len);
        }

        /* If that's the destination, end */
        if (node == to)
            return 1;

        /* Add reachable nodes to the visit list */
        rlist = vh_pget(node, "REACH");
        vl_foreach(elt, rlist) {
            reach = vs_pget(elt);
            node = vh_pget(reach, "TO");
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
                ndist = *dist + 1;
                nlen = *len + vh_iget(reach, "LEN");
                vh_istore(node, "FP_DIST", ndist);
                vh_istore(node, "FP_LEN", nlen);

                if (from == ap_room) {
                    if (node != from)
                        vh_pstore(node, "AP_LAST", reach);
                    vh_istore(node, "AP_DIST", ndist);
                    vh_istore(node, "AP_LEN", nlen);
                }

                vq_pstore(visit, node, -nlen);
            }
        }
    }

    if (ifm_verbose && to != NULL) {
        indent(4);
        printf("failed: no path\n");
    }

    return 0;
}

/* Return path twixt anchor room and a given room */
vlist *
get_path(vhash *room)
{
    vhash *reach;
    vlist *path;

    /* Check room is reachable */
    if (vh_iget(room, "AP_VISIT") != ap_visit)
        return NULL;

    /* Build path */
    path = vl_create();

    while ((reach = vh_pget(room, "AP_LAST")) != NULL) {
        vl_punshift(path, reach);
        room = vh_pget(reach, "FROM");
    }

    return path;
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
        printf("updated paths (max distance: %d)\n", len);
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
