/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Task building functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vars.h>

#include "ifm-main.h"
#include "ifm-map.h"
#include "ifm-path.h"
#include "ifm-task.h"
#include "ifm-util.h"

/* Verbose flag */
extern int ifm_verbose;

/* Task step list */
vlist *tasklist = NULL;

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static void do_task(vhash *task);
static void leave_item(vhash *item, vhash *room);
static void moveto_room(vhash *task, vhash *from, vhash *to);
static void task_pair(vhash *before, vhash *after);
static int task_possible(vhash *room, vhash *step);
static vhash *task_step(int type, vhash *data);

/* Flag a task as done */
static void
do_task(vhash *task)
{
    int print = 1, score = 1;
    vscalar *elt;
    vhash *item;
    vlist *list;

    /* Do the task */
    switch (vh_iget(task, "TYPE")) {
    case T_GET:
        item = vh_pget(task, "DATA");
        if (vh_exists(item, "TAKEN"))
            score = 0;
        vh_istore(item, "TAKEN", 1);
        if (vh_iget(item, "GIVEN"))
            print = 0;
        break;
    case T_DROP:
        item = vh_pget(task, "DATA");
        vh_istore(item, "TAKEN", 0);
        vh_istore(item, "DROPPED", 1);
        if (vh_iget(item, "LOST"))
            print = 0;
        break;
    case T_GOTO:
        print = 0;
        break;
    }

    if (!score)
        vh_delete(task, "SCORE");

    if (print) {
        vl_ppush(taskorder, task);

        if (ifm_verbose) {
            indent(2);
            printf("do task: %s\n", vh_sgetref(task, "DESC"));
        }
    }

    /* Lose any items involved */
    if ((list = vh_pget(task, "LOSE")) != NULL) {
        vl_foreach(elt, list) {
            item = vs_pget(elt);
            vh_istore(item, "TAKEN", 0);
            vh_istore(item, "DROPPED", 1);
            if (ifm_verbose) {
                indent(2);
                printf("lose: %s\n", vh_sgetref(item, "DESC"));
            }
        }
    }

    /* Flag path modification if required */
    if (vh_iget(task, "MODPATH"))
        modify_path();

    /* Flag it as done */
    vh_istore(task, "DONE", 1);
}

/* Leave an item in a room and get it later */
static void
leave_item(vhash *item, vhash *room)
{
    vhash *tstep, *step;
    vscalar *elt;
    vlist *list;
    int opt = 1;

    /* Do nothing if not carrying it */
    if (!vh_iget(item, "TAKEN"))
        return;

    /* Drop the item */
    vh_pstore(item, "ROOM", room);
    step = task_step(T_DROP, item);
    do_task(step);

    /* Create new task step to get it back */
    step = task_step(T_GET, item);
    task_pair(step, step);

    /* Add new task dependencies */
    if ((list = vh_pget(item, "TASKS")) != NULL) {
        vl_foreach(elt, list) {
            tstep = vs_pget(elt);
            task_pair(step, tstep);
            opt = 0;
        }
    }

    /* Flag retrieval as optional if no other tasks need it */
    if (opt)
        vh_istore(step, "OPTIONAL", 1);
}

/* Move to a new room */
static void
moveto_room(vhash *task, vhash *from, vhash *to)
{
    vhash *item, *reach, *room, *mtask, *last;
    vlist *path, *list;
    vscalar *elt;
    char *cmd;

    /* Add movement tasks */
    if (vh_iget(task, "BLOCK"))
        path = vh_pget(task, "PATH");
    else
        path = get_path(to);

    last = from;

    vl_foreach(elt, path) {
        reach = vs_pget(elt);
        room = vh_pget(reach, "TO");

        /* Leave items behind if required */
        if ((list = vh_pget(reach, "LEAVE")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                leave_item(item, last);
            }
        }

        if ((list = vh_pget(room, "LEAVE")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                leave_item(item, last);
            }
        }

        /* Move to the next room */
        mtask = task_step(T_MOVE, room);
        cmd = vh_sgetref(reach, "CMD");
        vh_sstore(mtask, "CMD", cmd);
        vl_ppush(taskorder, mtask);

        if (vh_exists(room, "VISITED"))
            vh_delete(mtask, "SCORE");
        vh_istore(room, "VISITED", 1);

        if (ifm_verbose) {
            indent(2);
            printf("move to: %s\n", vh_sgetref(room, "DESC"));
        }

        last = room;
    }
}

/* Build the initial task list */
void
setup_tasks(void)
{
    vhash *task, *otask, *get, *after, *item, *tstep, *room, *reach;
    vlist *list, *itasks, *rlist;
    vhash *step, *istep, *oitem;
    vscalar *elt;

    if (ifm_verbose)
        printf("\nSetting up tasks...\n");

    /* Create 'goto room' steps, and mention scored rooms */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        step = task_step(T_GOTO, room);
        vh_pstore(room, "STEP", step);
        if (vh_iget(room, "SCORE") > 0)
            task_pair(step, step);
    }

    /* Create 'get item' steps, and mention scored items */
    vl_foreach(elt, items) {
        item = vs_pget(elt);
        step = task_step(T_GET, item);
        vh_pstore(item, "STEP", step);
        if (vh_iget(item, "SCORE") > 0)
            task_pair(step, step);
    }

    /* Create user task steps */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        step = task_step(T_USER, task);
        vh_pstore(task, "STEP", step);
        task_pair(step, step);
    }

    /* Process tasks (1st pass) */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        tstep = vh_pget(task, "STEP");

        /* Deal with 'follow' tasks */
        if ((otask = vh_pget(task, "FOLLOW")) != NULL) {
            step = vh_pget(otask, "STEP");
            if (vh_exists(step, "NEXT")
                && vh_pget(step, "NEXT") != tstep)
                err("more than one task needs to follow `%s' immediately",
                    vh_sgetref(otask, "DESC"));
            vh_pstore(step, "NEXT", tstep);
            vh_pstore(tstep, "PREV", step);
            task_pair(step, tstep);
        }
    }

    /* Process rooms and map connections */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        rlist = vh_pget(room, "REACH");

        /* Flag 'before' tasks for this room as unsafe */
        if ((list = vh_pget(room, "BEFORE")) != NULL) {
            vl_foreach(elt, list) {
                task = vs_pget(elt);
                step = vh_pget(task, "STEP");
                vh_istore(step, "MODPATH", 1);
                vh_istore(step, "UNSAFE", 1);
            }
        }

        /* Flag items which might have to be left before entering room */
        if ((list = vh_pget(room, "LEAVE")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                vh_istore(item, "LEAVE", 1);
                step = vh_pget(item, "STEP");
                vh_istore(step, "MODPATH", 1);
            }
        }

        /* Must get required items before visiting this room */
        if ((list = vh_pget(room, "NEED")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                vh_istore(item, "USED", 1);
                vh_istore(item, "NEEDED", 1);

                room = vh_pget(item, "ROOM");
                if (room != NULL) {
                    step = vh_pget(item, "STEP");
                    vh_istore(step, "MODPATH", 1);
                    task_pair(step, step);
                }
            }
        }

        vl_foreach(elt, rlist) {
            reach = vs_pget(elt);

            /* Flag items which might have to be left before using link */
            if ((list = vh_pget(reach, "LEAVE")) != NULL) {
                vl_foreach(elt, list) {
                    item = vs_pget(elt);
                    vh_istore(item, "LEAVE", 1);
                    step = vh_pget(item, "STEP");
                    vh_istore(step, "MODPATH", 1);
                }
            }

            /* Flag 'before' tasks for this connection as unsafe */
            if ((list = vh_pget(reach, "BEFORE")) != NULL) {
                vl_foreach(elt, list) {
                    task = vs_pget(elt);
                    step = vh_pget(task, "STEP");
                    vh_istore(step, "MODPATH", 1);
                    vh_istore(step, "UNSAFE", 1);
                }
            }

            /* Mention 'after' tasks for this connection */
            if ((list = vh_pget(reach, "AFTER")) != NULL) {
                vl_foreach(elt, list) {
                    task = vs_pget(elt);
                    step = vh_pget(task, "STEP");
                    vh_istore(step, "MODPATH", 1);
                    task_pair(step, step);
                }
            }

            /* Flag items which are needed for paths */
            if ((list = vh_pget(reach, "NEED")) != NULL) {
                vl_foreach(elt, list) {
                    item = vs_pget(elt);
                    vh_istore(item, "USED", 1);
                    vh_istore(item, "NEEDED", 1);
                    step = vh_pget(item, "STEP");
                    vh_istore(step, "MODPATH", 1);
                    task_pair(step, step);
                }
            }
        }
    }

    /* Process items */
    vl_foreach(elt, items) {
        item = vs_pget(elt);
        istep = vh_pget(item, "STEP");

        /* Must get required items before getting this item */
        if ((list = vh_pget(item, "NEED")) != NULL) {
            vl_foreach(elt, list) {
                oitem = vs_pget(elt);
                vh_istore(oitem, "USED", 1);

                room = vh_pget(oitem, "ROOM");
                if (room != NULL) {
                    get = vh_pget(oitem, "STEP");
                    task_pair(get, istep);
                }

                /* Record dependent tasks for this item */
                itasks = vh_pget(oitem, "TASKS");
                if (itasks == NULL) {
                    itasks = vl_create();
                    vh_pstore(oitem, "TASKS", itasks);
                }
                vl_ppush(itasks, istep);
            }
        }

        /* Deal with 'after' tasks */
        if ((list = vh_pget(item, "AFTER")) != NULL) {
            vl_foreach(elt, list) {
                task = vs_pget(elt);
                step = vh_pget(task, "STEP");
                task_pair(step, istep);
            }
        }

        /* Deal with 'before' tasks */
        if ((list = vh_pget(item, "BEFORE")) != NULL) {
            vl_foreach(elt, list) {
                task = vs_pget(elt);
                step = vh_pget(task, "STEP");
                task_pair(istep, step);
            }
        }
    }

    /* Process tasks (2nd pass) */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        tstep = vh_pget(task, "STEP");

        /* Must get required items before doing this task */
        if ((list = vh_pget(task, "NEED")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                vh_istore(item, "USED", 1);

                room = vh_pget(item, "ROOM");
                if (room != NULL) {
                    get = vh_pget(item, "STEP");
                    task_pair(get, tstep);
                }

                /* Record dependent tasks for this item */
                itasks = vh_pget(item, "TASKS");
                if (itasks == NULL) {
                    itasks = vl_create();
                    vh_pstore(item, "TASKS", itasks);
                }
                vl_ppush(itasks, tstep);
            }
        }

        /* Must do this task before getting supplied items */
        if ((list = vh_pget(task, "GET")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                room = vh_pget(item, "ROOM");
                if (room != NULL) {
                    get = vh_pget(item, "STEP");
                    task_pair(tstep, get);
                }
            }
        }

        /* Must do this task after all preceding tasks */
        if ((list = vh_pget(task, "AFTER")) != NULL) {
            vl_foreach(elt, list) {
                otask = vs_pget(elt);
                after = vh_pget(otask, "STEP");
                task_pair(after, tstep);
            }
        }
    }

    /* Process tasks (3rd pass) */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        tstep = vh_pget(task, "STEP");

        /* Add dependencies for tasks which lose items */
        if ((list = vh_pget(tstep, "LOSE")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);

                /* If item is needed for paths, mark task unsafe */
                if (vh_exists(item, "NEEDED"))
                    vh_istore(tstep, "UNSAFE", 1);

                if ((itasks = vh_pget(item, "TASKS")) != NULL) {
                    vl_foreach(elt, itasks) {
                        step = vs_pget(elt);
                        task_pair(step, tstep);
                    }
                }
            }
        }
    }
}

/* Solve the game by ordering the task list */
void
solve_game(void)
{
    vhash *nextroom, *gotoroom, *room, *step, *trystep, *item, *task, *next;
    int drop, safeflag, tasksleft;
    vlist *itasks;
    vscalar *elt;

    /* Don't bother if no tasks */
    if (tasklist == NULL || vl_length(tasklist) == 0)
        return;

    /* Build initial inventory */
    vl_foreach(elt, items) {
        item = vs_pget(elt);
        if (vh_pget(item, "ROOM") == NULL)
            vh_istore(item, "TAKEN", 1);
    }

    /* Process task list */
    room = startroom;
    next = NULL;

    if (ifm_verbose)
        printf("\nSolving game...\n");

    do {
        if (ifm_verbose) {
            indent(1);
            printf("room: %s\n", vh_sgetref(room, "DESC"));
        }

        /* Initialise path searches from this room */
        init_path(room);

        /* Check for dropping unneeded items */
        if (next == NULL) {
            vl_foreach(elt, items) {
                item = vs_pget(elt);

                if (!vh_iget(item, "TAKEN"))
                    continue;
                if (vh_iget(item, "DROPPED"))
                    continue;
                if (vh_iget(item, "NEEDED"))
                    continue;
                if (vh_iget(item, "KEEP"))
                    continue;
                if (!vh_iget(item, "USED"))
                    continue;

                drop = 1;
                itasks = vh_pget(item, "TASKS");
                if (itasks != NULL) {
                    vl_foreach(elt, itasks) {
                        if (!drop)
                            continue;
                        task = vs_pget(elt);
                        if (!vh_iget(task, "DONE"))
                            drop = 0;
                    }
                }

                if (drop) {
                    step = task_step(T_DROP, item);
                    do_task(step);
                }
            }
        }

        /* Search for next task */
        step = NULL;
        safeflag = 0;
        tasksleft = 0;

        vl_foreach(elt, tasklist) {
            trystep = vs_pget(elt);

            /* If task is done, skip it */
            if (vh_iget(trystep, "DONE"))
                continue;

            /* If not optional, flag at least one task still to do */
            if (!vh_iget(trystep, "OPTIONAL"))
                tasksleft = 1;

            /* If there's a forced next task but this isn't it, skip it */
            if (next != NULL && trystep != next)
                continue;

            /* If we have a safe task, skip the rest */
            if (safeflag)
                continue;

            /* Check task is possible */
            if (!task_possible(room, trystep))
                continue;

            if (!safeflag && vh_iget(trystep, "SAFEFLAG")) {
                safeflag = 1;
                step = trystep;
            } else if (step == NULL) {
                step = trystep;
            }
        }

        if (step != NULL) {
            /* Do the task */
            nextroom = vh_pget(step, "ROOM");
            gotoroom = vh_pget(step, "GOTO");
            if (nextroom != NULL && room != nextroom)
                moveto_room(step, room, nextroom);
            do_task(step);
            if (nextroom != NULL)
                room = nextroom;
            if (gotoroom != NULL)
                room = gotoroom;
            next = vh_pget(step, "NEXT");
        } else if (tasksleft) {
            /* Hmm... we seem to be stuck */
            vlist *tmp = vl_create();
            char *sep = "\n    ";

            vl_foreach(elt, tasklist) {
                step = vs_pget(elt);
                if (!vh_iget(step, "DONE"))
                    vl_spush(tmp, vh_sgetref(step, "DESC"));
            }

            warn("can't solve game (%d tasks not done)%s%s",
                 vl_length(tmp), sep, vl_join(tmp, sep));

            vl_destroy(tmp);
            break;
        } else if (ifm_verbose) {
            indent(2);
            printf("no more tasks\n\n");
        }
    } while (tasksleft);
}

/* Add an ordered task pair to the task list */
static void
task_pair(vhash *before, vhash *after)
{
    vhash *start = after;
    vlist *depend;

    if (tasklist == NULL)
        tasklist = vl_create();

    do {
        if (!vh_iget(before, "SEEN")) {
            vh_istore(before, "SEEN", 1);
            vl_ppush(tasklist, before);
            vh_pstore(before, "DEPEND", vl_create());
        }

        if (!vh_iget(after, "SEEN")) {
            vh_istore(after, "SEEN", 1);
            vl_ppush(tasklist, after);
            vh_pstore(after, "DEPEND", vl_create());
        }

        if (before != after) {
            depend = vh_pget(after, "DEPEND");
            vl_ppush(depend, before);
        }

        if (ifm_verbose && before != after) {
            indent(1);
            printf("do `%s' before `%s'\n",
                   vh_sgetref(before, "DESC"),
                   vh_sgetref(after, "DESC"));
        }

        after = vh_pget(after, "PREV");
    } while (after != NULL && after != start);
}

/* Return whether a task is possible */
static int
task_possible(vhash *room, vhash *step)
{
    vhash *before, *taskroom, *gotoroom;
    int len = 0, safe;
    vlist *depend;
    vscalar *elt;

    /* All dependent tasks must be done */
    if ((depend = vh_pget(step, "DEPEND")) != NULL) {
        vl_foreach(elt, depend) {
            before = vs_pget(elt);
            if (!vh_iget(before, "DONE")) {
                vl_break(depend);
                return 0;
            }
        }
    }

    taskroom = vh_pget(step, "ROOM");
    gotoroom = vh_pget(step, "GOTO");

    if (ifm_verbose) {
        indent(2);
        printf("consider: %s\n", vh_sgetref(step, "DESC"));
    }

    if (taskroom == NULL || taskroom == room) {
        /*
         * Task can be done anywhere, or in current room -- if it's a
         * goto-room task, you must be able to get there.
         */
        if (vh_iget(step, "TYPE") == T_GOTO)
            len = find_path(step, room, gotoroom);
    } else {
        /*
         * Task must be done elsewhere -- there must be a path from
         * here to the task room.
         */
        len = find_path(step, room, taskroom);
    }

    /* Abort if no path */
    if (len == NOPATH)
        return 0;

    /* See whether task is safe */
    if (vh_exists(step, "SAFE")) {
        /* User says it's safe, and they know best */
        safe = 1;
    } else if (vh_exists(step, "UNSAFE")) {
        /* It's been flagged unsafe already */
        safe = 0;
    } else {
        /* If no return path, mark it as unsafe */
        safe = 1;
        if (gotoroom != NULL)
            taskroom = gotoroom;
        if (taskroom != NULL && find_path(NULL, taskroom, room) == NOPATH)
            safe = 0;
    }

    /* Record safe flag */
    vh_istore(step, "SAFEFLAG", safe);

    if (ifm_verbose) {
        indent(2);
        printf("possible: %s", vh_sgetref(step, "DESC"));
        if (len > 0)
            printf(" (distance %d)", len);
        if (!safe)
            printf(" (unsafe)");
        printf("\n");
    }

    return 1;
}

/* Create and return a new task step */
static vhash *
task_step(int type, vhash *data)
{
    char *desc = vh_sgetref(data, "DESC");
    int score = vh_iget(data, "SCORE");
    vhash *room, *step;

    step = vh_create();
    vh_istore(step, "TYPE", type);
    if (data != NULL)
        vh_pstore(step, "DATA", data);

    switch (type) {
    case T_MOVE:
        sprintf(buf, "Move to %s", desc);
        room = data;
        break;
    case T_GET:
        sprintf(buf, "Get %s", desc);
        room = vh_pget(data, "ROOM");
        break;
    case T_DROP:
        sprintf(buf, "Drop %s", desc);
        room = NULL;
        score = 0;
        break;
    case T_GOTO:
        sprintf(buf, "Go to %s", desc);
        room = data;
        break;
    case T_USER:
        room = vh_pget(data, "ROOM");
        strcpy(buf, desc);
        vh_pstore(step, "NEED", vh_pget(data, "NEED"));
        vh_pstore(step, "GOTO", vh_pget(data, "GOTO"));
        vh_pstore(step, "LOSE", vh_pget(data, "LOSE"));
        vh_sstore(step, "NOTE", vh_sgetref(data, "NOTE"));
        vh_sstore(step, "TAG", vh_sgetref(data, "TAG"));
        break;
    default:
        fatal("internal: unknown task type");
    }

    if (vh_exists(data, "SAFE"))
        vh_istore(step, "SAFE", vh_iget(data, "SAFE"));

    vh_sstore(step, "DESC", buf);
    vh_pstore(step, "ROOM", room);
    vh_istore(step, "SCORE", score);

    return step;
}
