/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Path building functions */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vars.h>

#include "ifm-main.h"
#include "ifm-map.h"
#include "ifm-path.h"
#include "ifm-task.h"
#include "ifm-util.h"

#define NODE(room)           vh_sgetref(room, "NODE")

#define PATH_LIST(r1, r2)    vg_path_list(graph, NODE(r1), NODE(r2))
#define PATH_INFO(r1, r2)    vg_path_info(graph, NODE(r1), NODE(r2))
#define PATH_LENGTH(r1, r2)  ((int) vg_path_length(graph, NODE(r1), NODE(r2)))

#define BIG 1000

/* Graph structure */
static vgraph *graph = NULL;

/* Modified-path flag */
static int path_modify = 0;

/* Path cache room */
static vhash *path_room = NULL;

/* Path task */
static vhash *path_task = NULL;

/* Find-path start room */
static vhash *start_room = NULL;

/* Internal functions */
static double link_size(char *fnode, char *tnode, vscalar *s);
static int sort_tasks(vscalar **v1, vscalar **v2);
static int use_link(char *fnode, char *tnode, vscalar *s);
static int use_node(char *node, vscalar *s, double dist);

/* Connect rooms as a directed graph */
void
connect_rooms(void)
{
    vhash *room, *link, *join, *reach, *from, *to;
    int oneway, len, goflag, dir, num = 0;
    char *cmd, id[10], *fnode, *tnode;
    vlist *cmdfrom, *cmdto, *list;
    vscalar *elt;

    DEBUG0(0, "Task debugging information\n");
    DEBUG0(0, "Connecting rooms...");

    /* Initialise */
    graph = vg_create();

    vg_use_node_function(graph, use_node);
    vg_use_link_function(graph, use_link);
    vg_link_size_function(graph, link_size);

    /* Create room nodes */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        sprintf(id, "R%d", ++num);
        vh_sstore(room, "NODE", id);
        vg_node_pstore(graph, id, room);
    }

    /* Build link connections */
    vl_foreach(elt, links) {
        link = vs_pget(elt);
        if (vh_iget(link, "NOLINK"))
            continue;

        oneway = vh_iget(link, "ONEWAY");
        len = vh_iget(link, "LEN");

        from = vh_pget(link, "FROM");
        to = vh_pget(link, "TO");

        fnode = vh_sgetref(from, "NODE");
        tnode = vh_sgetref(to, "NODE");

        /* From -> to */
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

        vg_link_oneway_pstore(graph, fnode, tnode, reach);

        if (ifm_debug) {
            indent(1);
            list = vh_pget(reach, "CMD");
            printf("link `%s' to `%s' (%s)",
                   vh_sgetref(from, "DESC"),
                   vh_sgetref(to, "DESC"),
                   vl_join(list, ". "));
            if (len > 1)
                printf(" (dist %d)", len);
            printf("\n");
        }

        /* To -> from if not one-way */
        if (!oneway) {
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

            vg_link_oneway_pstore(graph, tnode, fnode, reach);

            if (ifm_debug) {
                indent(1);
                list = vh_pget(reach, "CMD");
                printf("link `%s' to `%s' (%s)",
                       vh_sgetref(to, "DESC"),
                       vh_sgetref(from, "DESC"),
                       vl_join(list, ". "));
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

        fnode = vh_sgetref(from, "NODE");
        tnode = vh_sgetref(to, "NODE");

        /* From -> to */
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

        vg_link_oneway_pstore(graph, fnode, tnode, reach);

        if (ifm_debug) {
            indent(1);
            list = vh_pget(reach, "CMD");
            printf("join `%s' to `%s' (%s)",
                   vh_sgetref(from, "DESC"),
                   vh_sgetref(to, "DESC"),
                   vl_join(list, ". "));
            if (len > 1)
                printf(" (dist %d)", len);
            printf("\n");
        }

        /* To -> from if not one-way */
        if (!oneway) {
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

            vg_link_oneway_pstore(graph, tnode, fnode, reach);

            if (ifm_debug) {
                indent(1);
                list = vh_pget(reach, "CMD");
                printf("join `%s' to `%s' (%s)",
                       vh_sgetref(to, "DESC"),
                       vh_sgetref(from, "DESC"),
                       vl_join(list, ". "));
                if (len > 1)
                    printf(" (dist %d)", len);
                printf("\n");
            }
        }
    }
}

/* Return length of a path between two rooms */
int
find_path(vhash *step, vhash *from, vhash *to)
{
    vlist *path;
    int len;

    /* Check trivial case */
    if (from == to)
        return 0;

    start_room = from;

    if (ifm_debug) {
        indent(3);
        printf("find path: `%s' to `%s'",
               vh_sgetref(from, "DESC"),
               vh_sgetref(to, "DESC"));
    }

    if (step != NULL && vh_iget(step, "BLOCK")) {
        if (ifm_debug)
            printf("\n");

        path_task = step;
        if ((path = vh_pget(step, "PATH")) != NULL)
            vl_destroy(path);
        vh_delete(step, "PATH");

        vg_use_cache(graph, 0);
        if ((path = PATH_INFO(from, to)) == NULL)
            return NOPATH;

        len = vl_dshift(path);
        vh_pstore(step, "PATH", path);
    } else {
        path_task = NULL;
        vg_use_cache(graph, 1);

        if (ifm_debug && path_room != from)
            printf("\n");

        len = PATH_LENGTH(from, to);

        if (ifm_debug && path_room == from) {
            if (len < 0)
                printf(" (cached: no path)\n");
            else
                printf(" (cached: dist %d)\n", len);
        }
    }

    return (len < 0 ? NOPATH : len);
}

/* Return path twixt path start room and a given room */
vlist *
get_path(vhash *step, vhash *room)
{
    static vlist *path = NULL;
    char *node, *next;
    vhash *reach;
    vlist *list;
    int i, len;

    /* Build path */
    list = vh_pget(step, "PATH");
    vh_delete(step, "PATH");

    if (list == NULL)
        list = PATH_LIST(path_room, room);

    if (list == NULL)
        return NULL;

    /* Convert node names to link data */
    if (path == NULL)
        path = vl_create();
    else
        vl_empty(path);

    len = vl_length(list);
    node = vl_sgetref(list, 0);

    for (i = 1; i < len; i++) {
        next = vl_sgetref(list, i);
        reach = vg_link_pget(graph, node, next);
        vl_ppush(path, reach);
        node = next;
    }

    vl_destroy(list);
    return path;
}

/* Initialise path searches */
void
init_path(vhash *room)
{
    vhash *step, *item, *taskroom;
    int len, blockable, offset;
    extern vlist *tasklist;
    vscalar *elt;
    vlist *list;
    double dist;

    /* Only need update if room changed, or path modified */
    if (room == path_room && !path_modify)
        return;

    path_room = room;
    path_modify = 0;

    /* Deal with tasks that need droppable items */
    vl_foreach(elt, tasklist) {
        step = vs_pget(elt);
        if (vh_iget(step, "DONE"))
            continue;

        if ((list = vh_pget(step, "NEED")) == NULL)
            continue;

        if ((taskroom = vh_pget(step, "ROOM")) == NULL)
            continue;

        blockable = 0;
        vl_foreach(elt, list) {
            item = vs_pget(elt);
            if (!vh_iget(item, "TAKEN"))
                continue;
            if (!vh_iget(item, "LEAVE"))
                continue;

            vh_pstore(item, "BLOCK", step);
            blockable = 1;
        }

        if (blockable) {
            /* Find path to task room */
            vh_istore(step, "BLOCK", 1);

            if (ifm_debug) {
                indent(2);
                printf("update path: %s\n", vh_sgetref(step, "DESC"));
                indent(2);
                printf("possible block: %s may need dropping\n",
                       vh_sgetref(item, "DESC"));
            }

            if ((len = find_path(step, room, taskroom)) != NOPATH)
                vh_istore(step, "SORT", len);
            else
                vh_istore(step, "SORT", BIG);
        }
    }

    /* Cache paths from this room */
    dist = vg_path_cache(graph, NODE(room));

    if (ifm_debug) {
        indent(2);
        printf("updated path cache (max dist %g)\n", dist);
    }

    /* Record distance of each task */
    vl_foreach(elt, tasklist) {
        step = vs_pget(elt);

        if (vh_iget(step, "BLOCK"))
            len = vh_iget(step, "SORT");
        else if ((taskroom = vh_pget(step, "ROOM")) == NULL)
            len = 0;
        else if ((len = PATH_LENGTH(room, taskroom)) < 0)
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

            if ((len = vh_iget(step, "DIST")) == BIG)
                continue;

            if (require_task(step) != NULL)
                continue;

            indent(3);
            printf("dist %d: %s\n", len, vh_sgetref(step, "DESC"));
        }
    }
}

/* Return length of a link */
static double
link_size(char *fnode, char *tnode, vscalar *s)
{
    vhash *reach = vs_pget(s);
    return vh_iget(reach, "LEN");
}

/* Flag path modification */
void
modify_path(void)
{
    path_modify = 1;
    DEBUG0(2, "flag path cache update");
}

/* Return list of reachable rooms from a given room */
vlist *
reachable_rooms(vhash *room)
{
    static vlist *list = NULL;
    char *node, *next;
    vscalar *elt;
    vhash *reach;

    if (list != NULL)
        vl_destroy(list);

    node = NODE(room);
    list = vg_node_to(graph, node);

    vl_foreach(elt, list) {
        next = vs_sgetref(elt);
        reach = vg_link_pget(graph, node, next);
        vs_pstore(elt, reach);
    }

    return list;
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

/* Is link usable? */
static int
use_link(char *fnode, char *tnode, vscalar *s)
{
    vhash *reach, *item, *task, *tstep, *block, *room;
    vscalar *elt;
    vlist *list;

    reach = vs_pget(s);

    /* Check items needed by task don't have to be left */
    if (path_task != NULL && (list = vh_pget(reach, "LEAVE")) != NULL) {
        vl_foreach(elt, list) {
            item = vs_pget(elt);
            block = vh_pget(item, "BLOCK");
            if (block != NULL && block == path_task) {
                if (ifm_debug && !vg_caching()) {
                    indent(4);
                    room = vg_node_pget(graph, tnode);
                    printf("blocked link: %s (must leave %s)\n",
                           vh_sgetref(room, "DESC"),
                           vh_sgetref(item, "DESC"));
                }

                vl_break(list);
                return 0;
            }
        }
    }

    /* Check required items have been obtained */
    if ((list = vh_pget(reach, "NEED")) != NULL) {
        vl_foreach(elt, list) {
            item = vs_pget(elt);
            if (!vh_iget(item, "TAKEN")) {
                if (ifm_debug && !vg_caching()) {
                    indent(4);
                    room = vg_node_pget(graph, tnode);
                    printf("blocked link: %s (need %s)\n",
                           vh_sgetref(room, "DESC"),
                           vh_sgetref(item, "DESC"));
                }

                vl_break(list);
                return 0;
            }
        }
    }

    /* Check status of required tasks */
    if ((list = vh_pget(reach, "BEFORE")) != NULL) {
        vl_foreach(elt, list) {
            task = vs_pget(elt);
            tstep = vh_pget(task, "STEP");
            if (vh_iget(tstep, "DONE")) {
                if (ifm_debug && !vg_caching()) {
                    indent(4);
                    room = vg_node_pget(graph, tnode);
                    printf("blocked link: %s (done `%s')\n",
                           vh_sgetref(room, "DESC"),
                           vh_sgetref(task, "DESC"));
                }

                vl_break(list);
                return 0;
            }
        }
    }

    if ((list = vh_pget(reach, "AFTER")) != NULL) {
        vl_foreach(elt, list) {
            task = vs_pget(elt);
            tstep = vh_pget(task, "STEP");
            if (!vh_iget(tstep, "DONE")) {
                if (ifm_debug && !vg_caching()) {
                    indent(4);
                    room = vg_node_pget(graph, tnode);
                    printf("blocked link: %s (not done `%s')\n",
                           vh_sgetref(room, "DESC"),
                           vh_sgetref(task, "DESC"));
                }

                vl_break(list);
                return 0;
            }
        }
    }

    return 1;
}

/* Is room visitable? */
static int
use_node(char *node, vscalar *s, double dist)
{
    vhash *room, *item, *task, *tstep, *block;
    vscalar *elt;
    vlist *list;

    room = vs_pget(s);

    /* Check items needed by task don't have to be left */
    if (path_task != NULL && (list = vh_pget(room, "LEAVE")) != NULL) {
        vl_foreach(elt, list) {
            item = vs_pget(elt);
            block = vh_pget(item, "BLOCK");
            if (block != NULL && block == path_task) {
                if (ifm_debug && !vg_caching()) {
                    indent(4);
                    printf("blocked room: %s (must leave %s)\n",
                           vh_sgetref(room, "DESC"),
                           vh_sgetref(item, "DESC"));
                }

                vl_break(list);
                return 0;
            }
        }
    }

    /* Check for required items */
    if ((list = vh_pget(room, "NEED")) != NULL) {
        vl_foreach(elt, list) {
            item = vs_pget(elt);
            if (!vh_iget(item, "TAKEN")) {
                if (ifm_debug && !vg_caching()) {
                    indent(4);
                    printf("blocked room: %s (need %s)\n",
                           vh_sgetref(room, "DESC"),
                           vh_sgetref(item, "DESC"));
                }

                vl_break(list);
                return 0;
            }
        }
    }

    /* Check status of required tasks */
    if ((list = vh_pget(room, "BEFORE")) != NULL) {
        vl_foreach(elt, list) {
            task = vs_pget(elt);
            tstep = vh_pget(task, "STEP");
            if (vh_iget(tstep, "DONE")) {
                if (ifm_debug && !vg_caching()) {
                    indent(4);
                    printf("blocked room: %s (done `%s')\n",
                           vh_sgetref(room, "DESC"),
                           vh_sgetref(task, "DESC"));
                }

                vl_break(list);
                return 0;
            }
        }
    }

    if ((list = vh_pget(room, "AFTER")) != NULL) {
        vl_foreach(elt, list) {
            task = vs_pget(elt);
            tstep = vh_pget(task, "STEP");
            if (!vh_iget(tstep, "DONE")) {
                if (ifm_debug && !vg_caching()) {
                    indent(4);
                    printf("blocked room: %s (not done `%s')\n",
                           vh_sgetref(room, "DESC"),
                           vh_sgetref(task, "DESC"));
                }

                vl_break(list);
                return 0;
            }
        }
    }

    if (ifm_debug && room != start_room && !vg_caching()) {
        indent(4);
        printf("visit: %s (dist %g)\n",
               vh_sgetref(room, "DESC"), dist);
    }

    return 1;
}
