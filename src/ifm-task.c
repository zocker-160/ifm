/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Task building functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ifm.h"

/* Task step list */
static vlist *tasklist = NULL;

/* Scribble buffer */
static char buf[BUFSIZ];

/* Add a new task */
void
add_task(void)
{
    if (curtask == NULL)
        return;

    if (vh_iget(curtask, "NOROOM")) {
        vh_pstore(curtask, "IN", NULL);
    } else if (!vh_exists(curtask, "IN")) {
        if (lastroom == NULL)
            err("no last room");
        vh_pstore(curtask, "IN", lastroom);
    }

    lasttask = curtask;
    vl_ppush(tasks, curtask);
    curtask = NULL;
}

/* Add a task to current task list */
void
add_task_list(char *tag)
{
    if (curtasks == NULL)
        curtasks = vl_create();
    if (tag == NULL) {
        if (lasttask == NULL)
            err("no last task");
        else
            vl_ppush(curtasks, lasttask);
    } else {
        vl_spush(curtasks, tag);
    }
}

/* Build the initial task list */
void
build_tasks(void)
{
    vhash *task, *otask, *get, *after, *item, *tstep, *room, *reach;
    vlist *list, *itasks, *rlist;
    vhash *step;
    vscalar *elt;

    /* Create 'get item' steps, and mention scored objects */
    vl_foreach(elt, items) {
        item = vs_pget(elt);
        step = task_step(T_GET, item);
        vh_pstore(item, "STEP", step);
        if (vh_iget(item, "SCORE") > 0)
            task_pair(step, step);
    }

    /* Create 'goto room' steps, and mention scored rooms */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        step = task_step(T_GOTO, room);
        vh_pstore(room, "STEP", step);
        if (vh_iget(room, "SCORE") > 0)
            task_pair(step, step);
    }

    /* Create user task steps */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        step = task_step(T_USER, task);
        vh_pstore(task, "STEP", step);
        if (vh_pget(task, "GOTO") != NULL)
            task_pair(step, step);
    }

    /* Add required task pairs */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        tstep = vh_pget(task, "STEP");

        /* Must get required items before doing it */
        list = vh_pget(task, "NEED");
        if (list != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                room = vh_pget(item, "ROOM");
                if (room != NULL) {
                    get = vh_pget(item, "STEP");
                    task_pair(get, tstep);
                }

                /* Record tasks for this item */
                itasks = vh_pget(item, "TASKS");
                if (itasks == NULL) {
                    itasks = vl_create();
                    vh_pstore(item, "TASKS", itasks);
                }
                vl_ppush(itasks, tstep);
            }
        }

        /* Must do it before getting supplied items */
        list = vh_pget(task, "GET");
        if (list != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                room = vh_pget(item, "ROOM");
                if (room != NULL) {
                    get = vh_pget(item, "STEP");
                    task_pair(tstep, get);
                }
            }
        }

        /* Must do it after all preceding tasks */
        list = vh_pget(task, "AFTER");
        if (list != NULL) {
            vl_foreach(elt, list) {
                otask = vs_pget(elt);
                after = vh_pget(otask, "STEP");
                task_pair(after, tstep);
            }
        }
    }

    /* Mention items and tasks which are needed for paths */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        rlist = vh_pget(room, "REACH");

        vl_foreach(elt, rlist) {
            reach = vs_pget(elt);

            list = vh_pget(reach, "NEED");
            if (list != NULL) {
                vl_foreach(elt, list) {
                    item = vs_pget(elt);
                    vh_istore(item, "NEEDED", 1);
                    step = vh_pget(item, "STEP");
                    task_pair(step, step);
                    vh_istore(step, "OPENPATH", 1);
                }
            }

            list = vh_pget(reach, "AFTER");
            if (list != NULL) {
                vl_foreach(elt, list) {
                    task = vs_pget(elt);
                    step = vh_pget(task, "STEP");
                    task_pair(step, step);
                    vh_istore(step, "OPENPATH", 1);
                }
            }
        }
    }
}

/* Flag a task as done */
void
do_task(vhash *task, vhash *from, vhash *to)
{
    vlist *path, *invent;
    vscalar *elt;
    vhash *item;

#ifdef DEBUG
    debug("Done: %s\n", vh_sgetref(task, "DESC"));
#endif

    /* Record path if required */
    path = vl_create();
    vh_pstore(task, "PATH", path);
    if (from != NULL && to != NULL)
        find_path(path, from, to);

    /* Do the task */
    switch (vh_iget(task, "TYPE")) {
    case T_GET:
        item = vh_pget(task, "DATA");
        vh_istore(item, "TAKEN", 1);
        if (!vh_iget(item, "GIVEN"))
            vl_ppush(taskorder, task);
        break;
    case T_DROP:
        item = vh_pget(task, "DATA");
        vh_istore(item, "DROPPED", 1);
        if (!vh_iget(item, "LOST"))
            vl_ppush(taskorder, task);
        break;
    default:
        vl_ppush(taskorder, task);
        break;
    }

    /* Record items currently carried */
    invent = vl_create();
    vh_pstore(task, "INVENT", invent);
    vl_foreach(elt, items) {
        item = vs_pget(elt);
        if (vh_iget(item, "TAKEN") && !vh_iget(item, "DROPPED"))
            vl_ppush(invent, item);
    }

    /* Flag it as done */
    vh_istore(task, "DONE", 1);
}

/* Create the ordered task list */
void
order_tasks(void)
{
    vhash *nextroom, *gotoroom, *room, *step, *trystep, *item, *task, *dstep;
    int drop, pri, priority, tasksleft;
    vlist *itasks, *dtasks = NULL;
    vscalar *elt;

    /* Don't bother if no tasks */
    if (vl_length(tasks) == 0)
        return;

    /* Build initial inventory */
    vl_foreach(elt, items) {
        item = vs_pget(elt);
        if (vh_pget(item, "ROOM") == NULL)
            vh_istore(item, "TAKEN", 1);
    }

    /* Process task list */
    room = startroom;
    while (1) {
        /* Check for dropping unneeded items */
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

            drop = 1;
            itasks = vh_pget(item, "TASKS");
            if (itasks != NULL) {
                vl_foreach(elt, itasks) {
                    task = vs_pget(elt);
                    if (!vh_iget(task, "DONE"))
                        drop = 0;
                }
            }

            if (drop) {
                dstep = task_step(T_DROP, item);
                if (dtasks == NULL)
                    dtasks = vl_create();
                vl_ppush(dtasks, dstep);
            }
        }

        if (dtasks != NULL) {
            vl_foreach(elt, dtasks) {
                dstep = vs_pget(elt);
                do_task(dstep, room, NULL);
            }

            vl_destroy(dtasks);
            dtasks = NULL;
        }

        /* Search for next task */
        step = NULL;
        tasksleft = 0;
        vl_foreach(elt, tasklist) {
            trystep = vs_pget(elt);

            if (vh_iget(trystep, "DONE"))
                continue;

            tasksleft = 1;
            if ((pri = task_priority(room, trystep)) == 0)
                continue;

#ifdef DEBUG
            debug("Try: %s (priority %d)", vh_sgetref(trystep, "DESC"), pri);
#endif

            if (step == NULL || pri > priority) {
                step = trystep;
                priority = pri;
            }
        }

        if (step != NULL) {
            /* Do the task */
            nextroom = vh_pget(step, "ROOM");
            gotoroom = vh_pget(step, "GOTO");
            do_task(step, room, nextroom);
            if (nextroom != NULL)
                room = nextroom;
            if (gotoroom != NULL)
                room = gotoroom;
        } else if (tasksleft) {
            /* Hmm... we seem to be stuck */
            vlist *tmp = vl_create();
            char *sep = "\n\t ";

            vl_foreach(elt, tasklist) {
                step = vs_pget(elt);
                if (!vh_iget(step, "DONE"))
                    vl_spush(tmp, vh_sgetref(step, "DESC"));
            }

            warning("can't solve game (%d tasks not done)%s%s",
                    vl_length(tmp), sep, vl_join(tmp, sep));

            vl_destroy(tmp);
            break;
        } else {
            break;
        }
    }
}

/* Set list of following tasks */
void
set_task_after(void)
{
    if (curtask == NULL)
	curtask = vh_create();
    vh_pstore(curtask, "AFTER", curtasks);
    curtasks = NULL;
}

/* Set a task attribute */
void
set_task_attr(char *attr, char *val)
{
    if (curtask == NULL)
	curtask = vh_create();
    vh_sstore(curtask, attr, val);
}

/* Set a task item list */
void
set_task_items(char *attr)
{
    if (curtask == NULL)
	curtask = vh_create();
    vh_pstore(curtask, attr, curitems);
    curitems = NULL;
}

/* Set a task tag name */
void
set_task_tag(char *str)
{
    if (curtask == NULL)
        curtask = vh_create();
    set_tag("task", str, curtask, tasktags);
}

/* Add an ordered task pair to the task list */
void
task_pair(vhash *before, vhash *after)
{
    vlist *prev;

    if (tasklist == NULL)
        tasklist = vl_create();

    if (!vh_iget(before, "SEEN")) {
        vh_istore(before, "SEEN", 1);
        vl_ppush(tasklist, before);
        vh_pstore(before, "PREV", vl_create());
    }

    if (!vh_iget(after, "SEEN")) {
        vh_istore(after, "SEEN", 1);
        vl_ppush(tasklist, after);
        vh_pstore(after, "PREV", vl_create());
    }

    if (before != after) {
        prev = vh_pget(after, "PREV");
        vl_ppush(prev, before);
    }
}

/* Return priority of a task, or 0 if it's not possible */
int
task_priority(vhash *room, vhash *step)
{
    vhash *before, *taskroom, *gotoroom;
    int priority = 1000, dist;
    vscalar *elt;
    vlist *prev;

    /* All previous tasks must be done */
    prev = vh_pget(step, "PREV");
    if (prev != NULL) {
        vl_foreach(elt, prev) {
            before = vs_pget(elt);
            if (!vh_iget(before, "DONE")) {
                vl_break(prev);
                return 0;
            }
        }
    }

    /* If already in task room, or task can be done anywhere, give
       it high priority */
    taskroom = vh_pget(step, "ROOM");
    if (taskroom == NULL || taskroom == room)
        return priority;

    /* There must be a path from here to the task room */
    if ((dist = find_path(NULL, room, taskroom)) > 0)
        priority -= dist;
    else
        return 0;

    /* If task doesn't open up new paths, lower the priority */
    if (!vh_iget(step, "OPENPATH"))
        priority -= 100;

    /* If no return path, lower the priority */
    gotoroom = vh_pget(step, "GOTO");
    if (gotoroom != NULL)
        taskroom = gotoroom;
    if (!find_path(NULL, taskroom, room))
        priority -= 200;

    return priority;
}

/* Create and return a new task step */
vhash *
task_step(int type, vhash *data)
{
    vhash *step = vh_create();
    vhash *room = vh_pget(data, "ROOM");
    char *desc = vh_sgetref(data, "DESC");
    int score = vh_iget(data, "SCORE");

    vh_istore(step, "TYPE", type);
    if (data != NULL)
        vh_pstore(step, "DATA", data);

    switch (type) {
    case T_GET:
        sprintf(buf, "Get %s", desc);
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
        strcpy(buf, desc);
        vh_pstore(step, "GOTO", vh_pget(data, "GOTO"));
        vh_sstore(step, "NOTE", vh_sgetref(data, "NOTE"));
        vh_sstore(step, "TAG", vh_sgetref(data, "TAG"));
        break;
    default:
        fatal("internal: unknown task type");
    }

    vh_sstore(step, "DESC", buf);
    vh_pstore(step, "ROOM", room);
    vh_istore(step, "SCORE", score);

    return step;
}
