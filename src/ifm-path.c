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

#include "ifm-main.h"
#include "ifm-map.h"
#include "ifm-path.h"
#include "ifm-task.h"
#include "ifm-util.h"

#define BIG 1000

#define INIT_CACHE(room) \
        ap_visit++; ap_room = room

/* Modified-path flag */
static int path_modify = 0;

/* Cached start room */
static vhash *ap_room = NULL;

/* Cached visit flag */
static int ap_visit = 0;

/* Find-path visit flag */
static int fp_visit = 0;

/* Internal functions */
static int sort_tasks(vscalar **v1, vscalar **v2);

/* Connect rooms as a directed graph */
void
connect_rooms(void)
{
    vhash *room, *link, *join, *reach, *from, *to, *item;
    vlist *rlist, *cmdfrom, *cmdto;
    int oneway, len, goflag, dir;
    vscalar *elt;
    char *cmd;

    DEBUG0(0, "Task debugging information\n");
    DEBUG0(0, "Connecting rooms...");

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

        cmd = NULL;
        goflag = vh_iget(link, "GO");
        dir = vh_iget(link, "TO_DIR");
        if ((cmdto = vh_pget(link, "TO_CMD")) != NULL) {
            vh_pstore(reach, "CMD", cmdto);
        } else {
            if (goflag)
                cmd = dirinfo[goflag].sname;
            if (cmd == NULL)
                cmd = dirinfo[dir].sname;
            add_attr(reach, "CMD", cmd);
        }

        vh_pstore(reach, "FROM", from);
        vh_pstore(reach, "TO", to);
        vh_pstore(reach, "NEED", vh_pget(link, "NEED"));
        vh_pstore(reach, "BEFORE", vh_pget(link, "BEFORE"));
        vh_pstore(reach, "AFTER", vh_pget(link, "AFTER"));
        vh_istore(reach, "LEN", V_MAX(len, 1));
        vh_pstore(reach, "LEAVE", vh_pget(link, "LEAVE"));
        vh_istore(reach, "LEAVEALL", vh_iget(link, "LEAVEALL"));

        vl_ppush(rlist, reach);

        if (ifm_debug) {
            indent(1);
            printf("link `%s' to `%s' (%s)",
                   vh_sgetref(from, "DESC"),
                   vh_sgetref(to, "DESC"),
                   cmd);
            if (len > 1)
                printf(" (dist %d)", len);
            printf("\n");
        }

        /* To -> from if not one-way */
        if (!oneway) {
            rlist = vh_pget(to, "REACH");
            reach = vh_create();

            cmd = NULL;
            goflag = dirinfo[goflag].odir;
            dir = vh_iget(link, "FROM_DIR");
            if ((cmdfrom = vh_pget(link, "FROM_CMD")) != NULL) {
                vh_pstore(reach, "CMD", cmdfrom);
            } else if (cmdto != NULL) {
                vh_pstore(reach, "CMD", cmdto);
            } else {
                if (goflag)
                    cmd = dirinfo[goflag].sname;
                if (cmd == NULL)
                    cmd = dirinfo[dir].sname;
                add_attr(reach, "CMD", cmd);
            }

            vh_pstore(reach, "FROM", to);
            vh_pstore(reach, "TO", from);
            vh_pstore(reach, "NEED", vh_pget(link, "NEED"));
            vh_pstore(reach, "BEFORE", vh_pget(link, "BEFORE"));
            vh_pstore(reach, "AFTER", vh_pget(link, "AFTER"));
            vh_pstore(reach, "LEAVE", vh_pget(link, "LEAVE"));
            vh_istore(reach, "LEAVEALL", vh_iget(link, "LEAVEALL"));
            vh_istore(reach, "LEN", V_MAX(len, 1));

            vl_ppush(rlist, reach);

            if (ifm_debug) {
                indent(1);
                printf("link `%s' to `%s' (%s)",
                       vh_sgetref(to, "DESC"),
                       vh_sgetref(from, "DESC"),
                       cmd);
                if (len > 1)
                    printf(" (dist %d)", len);
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

        cmd = NULL;
        goflag = vh_iget(join, "GO");
        if ((cmdto = vh_pget(join, "TO_CMD")) != NULL) {
            vh_pstore(reach, "CMD", cmdto);
        } else {
            if (goflag)
                cmd = dirinfo[goflag].sname;
            if (cmd == NULL)
                cmd = "?";
            add_attr(reach, "CMD", cmd);
        }

        vh_pstore(reach, "FROM", from);
        vh_pstore(reach, "TO", to);
        vh_pstore(reach, "NEED", vh_pget(join, "NEED"));
        vh_pstore(reach, "BEFORE", vh_pget(join, "BEFORE"));
        vh_pstore(reach, "AFTER", vh_pget(join, "AFTER"));
        vh_pstore(reach, "LEAVE", vh_pget(join, "LEAVE"));
        vh_istore(reach, "LEAVEALL", vh_iget(join, "LEAVEALL"));
        vh_istore(reach, "LEN", V_MAX(len, 1));

        vl_ppush(rlist, reach);

        if (ifm_debug) {
            indent(1);
            printf("join `%s' to `%s' (%s)",
                   vh_sgetref(from, "DESC"),
                   vh_sgetref(to, "DESC"),
                   cmd);
            if (len > 1)
                printf(" (dist %d)", len);
            printf("\n");
        }

        /* To -> from if not one-way */
        if (!oneway) {
            rlist = vh_pget(to, "REACH");
            reach = vh_create();

            cmd = NULL;
            goflag = dirinfo[goflag].odir;
            if ((cmdfrom = vh_pget(join, "FROM_CMD")) != NULL) {
                vh_pstore(reach, "CMD", cmdfrom);
            } else if (cmdto != NULL) {
                vh_pstore(reach, "CMD", cmdto);
            } else {
                if (goflag)
                    cmd = dirinfo[goflag].sname;
                if (cmd == NULL)
                    cmd = "?";
                add_attr(reach, "CMD", cmd);
            }

            vh_pstore(reach, "FROM", to);
            vh_pstore(reach, "TO", from);
            vh_pstore(reach, "NEED", vh_pget(join, "NEED"));
            vh_pstore(reach, "BEFORE", vh_pget(join, "BEFORE"));
            vh_pstore(reach, "AFTER", vh_pget(join, "AFTER"));
            vh_pstore(reach, "LEAVE", vh_pget(join, "LEAVE"));
            vh_istore(reach, "LEAVEALL", vh_iget(join, "LEAVEALL"));
            vh_istore(reach, "LEN", V_MAX(len, 1));

            vl_ppush(rlist, reach);

            if (ifm_debug) {
                indent(1);
                printf("join `%s' to `%s' (%s)",
                       vh_sgetref(to, "DESC"),
                       vh_sgetref(from, "DESC"),
                       cmd);
                if (len > 1)
                    printf(" (dist %d)", len);
                printf("\n");
            }
        }
    }
}

/* Find a path between two rooms */
int
find_path(vhash *step, vhash *from, vhash *to)
{
    vhash *node, *reach, *task, *item, *istep, *tstep, *block;
    vlist *need, *after, *before, *rlist, *leave, *path;
    int addnode, len, nlen, blockflag = 0;
    static vqueue *visit = NULL;
    vscalar *elt;

    /* Check trivial case */
    if (from == to)
        return 0;

    if (ifm_debug && to != NULL) {
        indent(3);
        printf("find path: `%s' to `%s'",
               vh_sgetref(from, "DESC"),
               vh_sgetref(to, "DESC"));
    }

    /* Check for cached path */
    if (step != NULL)
        blockflag = vh_iget(step, "BLOCK");

    if (blockflag) {
        /* Task blockable by leaving needed items */
        if (vh_exists(step, "HASPATH")) {
            if (!vh_iget(step, "HASPATH")) {
                if (ifm_debug)
                    printf(" (cached: no path)\n");

                return NOPATH;
            } else if ((path = vh_pget(step, "PATH")) != NULL) {
                len = vl_length(path);

                if (ifm_debug)
                    printf(" (cached: dist %d)\n", len);

                return len;
            }
        }
    } else if (from == ap_room && to != NULL) {
        if (vh_iget(to, "AP_VISIT") == ap_visit) {
            /* Target room has been visited */
            len = vh_iget(to, "AP_LEN");

            if (ifm_debug)
                printf(" (cached: dist %d)\n", len);

            return len;
        } else if (vh_iget(ap_room, "AP_VISIT") == ap_visit) {
            /* Cache exists */
            if (ifm_debug)
                printf(" (cached: no path)\n");

            return NOPATH;
        }
    }

    if (ifm_debug && to != NULL)
        printf("\n");

    /* Initialise search */
    if (visit == NULL)
        visit = vq_create();
    else
        vq_empty(visit);

    vq_pstore(visit, from, 0);
    vh_istore(from, "FP_LEN", 0);
    vh_pstore(from, "FP_LAST", NULL);

    if (from == ap_room) {
        vh_istore(from, "AP_LEN", 0);
        vh_pstore(from, "AP_LAST", NULL);
    }

    fp_visit++;

    while (vq_length(visit) > 0) {
        /* Visit next unvisited node */
        node = vq_pget(visit);
        if (vh_iget(node, "FP_VISIT") == fp_visit)
            continue;

        len = vh_iget(node, "FP_LEN");
        vh_istore(node, "FP_VISIT", fp_visit);

        if (from == ap_room)
            vh_istore(node, "AP_VISIT", ap_visit);

        if (ifm_debug && node != from && to != NULL) {
            indent(4);
            printf("visit: %s (dist %d)\n",
                   vh_sgetref(node, "DESC"), len);
        }

        /* If that's the destination, end */
        if (node == to) {
            if (blockflag) {
                /* Store path for blocked tasks */
                if ((path = vh_pget(step, "PATH")) == NULL) {
                    path = vl_create();
                    vh_pstore(step, "PATH", path);
                } else {
                    vl_empty(path);
                }

                while ((reach = vh_pget(node, "FP_LAST")) != NULL) {
                    vl_punshift(path, reach);
                    node = vh_pget(reach, "FROM");
                }
            }

            if (step != NULL)
                vh_istore(step, "HASPATH", 1);

            return len;
        }

        /* Add reachable nodes to the visit list */
        rlist = vh_pget(node, "REACH");
        vl_foreach(elt, rlist) {
            reach = vs_pget(elt);
            node = vh_pget(reach, "TO");
            if (vh_iget(node, "FP_VISIT") == fp_visit)
                continue;
            addnode = 1;

            /* Check items needed by task don't have to be left */
            if (addnode && step != NULL &&
                (leave = vh_pget(reach, "LEAVE")) != NULL) {
                vl_foreach(elt, leave) {
                    item = vs_pget(elt);
                    block = vh_pget(item, "BLOCK");
                    if (block != NULL && block == step) {
                        addnode = 0;
                        if (ifm_debug && to != NULL) {
                            indent(4);
                            printf("blocked link: %s (must leave %s)\n",
                                   vh_sgetref(node, "DESC"),
                                   vh_sgetref(item, "DESC"));
                        }
                    }
                }
            }

            if (addnode && step != NULL &&
                (leave = vh_pget(node, "LEAVE")) != NULL) {
                vl_foreach(elt, leave) {
                    item = vs_pget(elt);
                    block = vh_pget(item, "BLOCK");
                    if (block != NULL && block == step) {
                        addnode = 0;
                        if (ifm_debug && to != NULL) {
                            indent(4);
                            printf("blocked room: %s (must leave %s)\n",
                                   vh_sgetref(node, "DESC"),
                                   vh_sgetref(item, "DESC"));
                        }
                    }
                }
            }

            /* Check required items have been obtained */
            if (addnode && (need = vh_pget(reach, "NEED")) != NULL) {
                vl_foreach(elt, need) {
                    item = vs_pget(elt);
                    if (!vh_iget(item, "TAKEN")) {
                        addnode = 0;
                        if (ifm_debug && to != NULL) {
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
                    if (!vh_iget(item, "TAKEN")) {
                        addnode = 0;
                        if (ifm_debug && to != NULL) {
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
                    tstep = vh_pget(task, "STEP");
                    if (vh_iget(tstep, "DONE")) {
                        addnode = 0;
                        if (ifm_debug && to != NULL) {
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
                    tstep = vh_pget(task, "STEP");
                    if (!vh_iget(tstep, "DONE")) {
                        addnode = 0;
                        if (ifm_debug && to != NULL) {
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
                    tstep = vh_pget(task, "STEP");
                    if (vh_iget(tstep, "DONE")) {
                        addnode = 0;
                        if (ifm_debug && to != NULL) {
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
                    tstep = vh_pget(task, "STEP");
                    if (!vh_iget(tstep, "DONE")) {
                        addnode = 0;
                        if (ifm_debug && to != NULL) {
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
                nlen = len + vh_iget(reach, "LEN");
                vh_istore(node, "FP_LEN", nlen);
                vh_pstore(node, "FP_LAST", reach);

                if (from == ap_room) {
                    if (node != from)
                        vh_pstore(node, "AP_LAST", reach);
                    vh_istore(node, "AP_LEN", nlen);
                }

                vq_pstore(visit, node, -nlen);
            }
        }
    }

    if (step != NULL)
        vh_istore(step, "HASPATH", 0);

    if (ifm_debug && to != NULL) {
        indent(4);
        printf("failed: no path\n");
    }

    return (to == NULL ? len : NOPATH);
}

/* Return path twixt cache start room and a given room */
vlist *
get_path(vhash *room)
{
    static vlist *path = NULL;
    vhash *reach;

    /* Check room is reachable */
    if (vh_iget(room, "AP_VISIT") != ap_visit)
        return NULL;

    /* Build path */
    if (path == NULL)
        path = vl_create();
    else
        vl_empty(path);

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
    vhash *step, *item, *taskroom;
    static vhash *last = NULL;
    extern vlist *tasklist;
    int len, flag, offset;
    vlist *list, *path;
    vscalar *elt;

    /* If room changed, or path modified, need update */
    if (room == last && !path_modify)
        return;

    last = room;
    path_modify = 0;

    /* Check tasks which need droppable items */
    vl_foreach(elt, tasklist) {
        step = vs_pget(elt);
        if (vh_iget(step, "DONE"))
            continue;

        if ((list = vh_pget(step, "NEED")) == NULL)
            continue;

        if ((taskroom = vh_pget(step, "ROOM")) == NULL)
            continue;

        flag = 0;
        vl_foreach(elt, list) {
            item = vs_pget(elt);
            if (!vh_iget(item, "TAKEN"))
                continue;
            if (!vh_iget(item, "LEAVE"))
                continue;

            vh_pstore(item, "BLOCK", step);
            flag = 1;
        }

        if (!flag)
            continue;

        /* Find path to task room */
        vh_istore(step, "BLOCK", 1);

        if (ifm_debug) {
            indent(2);
            printf("update path: %s\n", vh_sgetref(step, "DESC"));
            indent(2);
            printf("possible block: %s may need dropping\n",
                   vh_sgetref(item, "DESC"));
        }

        INIT_CACHE(room);

        if ((path = vh_pget(step, "PATH")) != NULL)
            vl_destroy(path);
        vh_pstore(step, "PATH", NULL);
        vh_delete(step, "HASPATH");

        if ((len = find_path(step, room, taskroom)) != NOPATH)
            vh_istore(step, "SORT", len);
        else
            vh_istore(step, "SORT", BIG);
    }

    /* Visit all rooms, recording their distances from this one */
    INIT_CACHE(room);
    len = find_path(NULL, room, NULL);

    if (ifm_debug) {
        indent(2);
        printf("updated paths (max dist: %d)\n", len);
    }

    /* Record distance of each task */
    vl_foreach(elt, tasklist) {
        step = vs_pget(elt);

        if (vh_iget(step, "BLOCK"))
            len = vh_iget(step, "SORT");
        else if ((room = vh_pget(step, "ROOM")) == NULL)
            len = 0;
        else if (vh_iget(room, "AP_VISIT") == ap_visit)
            len = vh_iget(room, "AP_LEN");
        else
            len = BIG;

        /* Put 'get-item' tasks a bit further */
        offset = (vh_iget(step, "TYPE") == T_GET);
        vh_istore(step, "SORT", 2 * len + offset);
        vh_istore(step, "DIST", len);
    }

    /* Sort tasks according to distance */
    vl_sort_inplace(tasklist, sort_tasks);

    if (ifm_debug) {
        vl_foreach(elt, tasklist) {
            step = vs_pget(elt);
            if (vh_iget(step, "DONE"))
                continue;
            if (vh_iget(step, "DIST") == BIG)
                continue;

            if (require_task(step) != NULL)
                continue;

            indent(3);
            printf("dist %d: %s\n",
                   vh_iget(step, "DIST"),
                   vh_sgetref(step, "DESC"));
        }
    }
}

/* Flag path modification */
void
modify_path(void)
{
    path_modify = 1;
    DEBUG0(2, "flag path cache update");
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
