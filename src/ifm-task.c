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

/* Task step list */
vlist *tasklist = NULL;

/* Current location */
static vhash *location = NULL;

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static void add_task(vhash *task);
static int do_task(vhash *task, int print);
static void drop_item(vhash *item, vhash *room, vlist *until, int print);
static void goto_room(vhash *task);
static vhash *new_task(int type, vhash *data);
static void order_tasks(vhash *before, vhash *after);
static int task_possible(vhash *room, vhash *step);

/* Add a task to the task list */
static void
add_task(vhash *task)
{
    if (vh_exists(task, "DEPEND"))
        return;

    if (tasklist == NULL)
        tasklist = vl_create();

    vl_ppush(tasklist, task);
    vh_pstore(task, "DEPEND", vl_create());
}

/* Perform a task */
static int
do_task(vhash *task, int print)
{
    vhash *item, *room, *step;
    int scoretask = 1, score;
    vlist *list, *until;
    vscalar *elt;

    /* Do the task */
    switch (vh_iget(task, "TYPE")) {
    case T_GET:
        item = vh_pget(task, "DATA");
        if (vh_exists(item, "TAKEN"))
            scoretask = 0;

        vh_istore(item, "TAKEN", 1);
        if (vh_iget(item, "GIVEN"))
            print = 0;

        if (vh_iget(item, "FINISH"))
            add_note(task, "Finishes the game");
        else if (!vh_iget(item, "USED"))
            add_note(task, "Not used for anything yet");

        break;
    case T_DROP:
        item = vh_pget(task, "DATA");
        vh_istore(item, "TAKEN", 0);
        if (vh_iget(item, "LOST"))
            print = 0;

        break;
    case T_USER:
        if ((list = vh_pget(task, "GIVE")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                add_note(task, "Gives %s", vh_sgetref(item, "DESC"));
            }
        }

        if ((room = vh_pget(task, "GOTO")) != NULL)
            add_note(task, "Moves you to %s",
                     vh_sgetref(room, "DESC"));

        if (vh_iget(task, "FINISH"))
            add_note(task, "Finishes the game");

        break;
    case T_GOTO:
        print = 0;
        break;
    }

    if (!scoretask)
        vh_delete(task, "SCORE");

    if (print) {
        vl_ppush(taskorder, task);

        if (ifm_debug) {
            indent(2);
            printf("do task: %s\n", vh_sgetref(task, "DESC"));
        }
    }

    /* Flag it as done */
    vh_istore(task, "DONE", 1);

    /* Get any given items */
    if ((list = vh_pget(task, "GIVE")) != NULL) {
        vl_foreach(elt, list) {
            item = vs_pget(elt);

            if (!vh_exists(item, "TAKEN")) {
                score = vh_iget(task, "SCORE") + vh_iget(item, "SCORE");
                vh_istore(task, "SCORE", score);
            }

            vh_istore(item, "TAKEN", 1);

            if (ifm_debug) {
                indent(2);
                printf("give: %s\n", vh_sgetref(item, "DESC"));
            }
        }

        /* Flag get-item tasks for carried items as done */
        vl_foreach(elt, tasklist) {
            step = vs_pget(elt);
            if (vh_iget(step, "TYPE") != T_GET)
                continue;

            item = vh_pget(step, "DATA");
            if (vh_iget(item, "TAKEN"))
                vh_istore(step, "DONE", 1);
        }
    }

    /* Lose any lost items */
    if ((list = vh_pget(task, "LOSE")) != NULL) {
        vl_foreach(elt, list) {
            item = vs_pget(elt);
            vh_istore(item, "TAKEN", 0);

            if (ifm_debug) {
                indent(2);
                printf("lose: %s\n", vh_sgetref(item, "DESC"));
            }
        }
    }

    /* Drop any dropped items */
    if ((list = vh_pget(task, "DROP")) != NULL) {
        if ((room = vh_pget(task, "DROPROOM")) == NULL)
            room = location;

        until = vh_pget(task, "DROPUNTIL");

        vl_foreach(elt, list) {
            item = vs_pget(elt);
            drop_item(item, room, until, 0);

            if (ifm_debug) {
                indent(2);
                printf("drop: %s\n", vh_sgetref(item, "DESC"));
            }
        }
    }

    /* Teleport to new location if required */
    if ((room = vh_pget(task, "GOTO")) != NULL)
        location = room;

    /* Flag path modification if required */
    if (vh_iget(task, "MODPATH"))
        modify_path();

    /* Return whether to try more tasks */
    if (vh_iget(task, "FINISH"))
        return 0;

    if (vh_iget(location, "FINISH"))
        return 0;

    return 1;
}

/* Leave an item in a room and maybe get it later */
static void
drop_item(vhash *item, vhash *room, vlist *until, int print)
{
    vhash *tstep, *step, *task;
    vscalar *elt;
    vlist *list;

    /* Do nothing if not carrying it */
    if (!vh_iget(item, "TAKEN"))
        return;

    /* Drop the item */
    vh_pstore(item, "ROOM", room);
    step = new_task(T_DROP, item);
    do_task(step, print);

    /* Create new task step to get it back */
    step = new_task(T_GET, item);

    /* Add new task dependencies (if any) */
    if (until != NULL) {
        vl_foreach(elt, until) {
            task = vs_pget(elt);
            tstep = vh_pget(task, "STEP");
            if (!vh_iget(tstep, "DONE"))
                order_tasks(tstep, step);
        }
    }

    if ((list = vh_pget(item, "TASKS")) != NULL) {
        vl_foreach(elt, list) {
            tstep = vs_pget(elt);
            if (!vh_iget(tstep, "DONE"))
                order_tasks(step, tstep);
        }
    }

    /* If item kept or needed for paths, mention it but flag it optional */
    if (vh_iget(item, "NEEDED") || vh_iget(item, "KEEP")) {
        add_task(step);
        vh_istore(step, "OPTIONAL", 1);
    }
}

/* Move to a room to do something */
static void
goto_room(vhash *task)
{
    vhash *item, *reach, *mtask, *last, *room;
    vlist *path, *list;
    vscalar *elt;
    char *cmd;

    /* See if movement is required */
    if ((room = vh_pget(task, "ROOM")) == NULL)
        return;
    if (room == location)
        return;

    /* Add movement tasks */
    if (vh_iget(task, "BLOCK"))
        path = vh_pget(task, "PATH");
    else
        path = get_path(room);

    last = location;

    vl_foreach(elt, path) {
        reach = vs_pget(elt);
        room = vh_pget(reach, "TO");

        /* Leave items behind if required */
        if ((list = vh_pget(reach, "LEAVE")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                drop_item(item, last, NULL, 1);
            }
        }

        if ((list = vh_pget(room, "LEAVE")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                drop_item(item, last, NULL, 1);
            }
        }

        /* Move to the next room */
        mtask = new_task(T_MOVE, room);
        cmd = vh_sgetref(reach, "CMD");
        vh_sstore(mtask, "CMD", cmd);
        vl_ppush(taskorder, mtask);

        if (vh_exists(room, "VISITED")) {
            vh_delete(mtask, "SCORE");
            vh_delete(mtask, "NOTE");
        }

        vh_istore(room, "VISITED", 1);

        if (vh_iget(room, "FINISH"))
            add_note(mtask, "Finishes the game");

        if (ifm_debug) {
            indent(2);
            printf("move to: %s\n", vh_sgetref(room, "DESC"));
        }

        last = room;
    }

    location = room;
}

/* Create and return a new task step */
static vhash *
new_task(int type, vhash *data)
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

        if (vh_exists(data, "TAG"))
            vh_sstore(step, "TAG", vh_sgetref(data, "TAG"));

        if (vh_exists(data, "CMD"))
            vh_sstore(step, "CMD", vh_sgetref(data, "CMD"));

        vh_pstore(step, "NEED", vh_pget(data, "NEED"));
        vh_pstore(step, "GOTO", vh_pget(data, "GOTO"));
        vh_pstore(step, "GIVE", vh_pget(data, "GIVE"));
        vh_pstore(step, "LOSE", vh_pget(data, "LOSE"));
        vh_pstore(step, "DROP", vh_pget(data, "DROP"));
        vh_istore(step, "DROPALL", vh_iget(data, "DROPALL"));
        vh_pstore(step, "DROPROOM", vh_pget(data, "DROPROOM"));
        vh_pstore(step, "DROPUNTIL", vh_pget(data, "DROPUNTIL"));
        break;
    default:
        fatal("internal: unknown task type");
    }

    if (vh_exists(data, "SAFE"))
        vh_istore(step, "SAFE", vh_iget(data, "SAFE"));

    if (vh_exists(data, "FINISH"))
        vh_istore(step, "FINISH", vh_iget(data, "FINISH"));

    if (vh_exists(data, "NOTE") && type != T_DROP)
        vh_pstore(step, "NOTE", vh_pget(data, "NOTE"));

    vh_sstore(step, "DESC", buf);
    vh_pstore(step, "ROOM", room);
    vh_istore(step, "SCORE", score);

    return step;
}

/* Add an ordered task pair to the task list */
static void
order_tasks(vhash *before, vhash *after)
{
    vlist *allow, *depend;
    vhash *start = after;

    add_task(before);
    add_task(after);

    if (before == after)
        return;

    if ((allow = vh_pget(before, "ALLOW")) == NULL) {
        allow = vl_create();
        vh_pstore(before, "ALLOW", allow);
    }

    vl_ppush(allow, after);

    do {
        if (after != before) {
            depend = vh_pget(after, "DEPEND");
            vl_ppush(depend, before);

            if (ifm_debug) {
                indent(2);
                printf("do `%s' before `%s'\n",
                       vh_sgetref(before, "DESC"),
                       vh_sgetref(after, "DESC"));
            }
        }

        after = vh_pget(after, "PREV");
    } while (after != NULL && after != start);
}

/* Build the initial task list */
void
setup_tasks(void)
{
    vhash *task, *otask, *get, *after, *item, *tstep, *room, *reach;
    vlist *list, *itasks, *rlist, *newlist;
    vhash *step, *istep, *oitem;
    int num = 0, leaveall;
    vscalar *elt;

    if (ifm_debug)
        printf("\nSetting up tasks...\n");

    /* Create 'goto room' steps */
    vl_foreach(elt, rooms) {
        room = vs_pget(elt);
        step = new_task(T_GOTO, room);
        vh_pstore(room, "STEP", step);
        if (vh_iget(room, "SCORE") > 0 || vh_iget(room, "FINISH"))
            add_task(step);
    }

    /* Create 'get item' steps */
    vl_foreach(elt, items) {
        item = vs_pget(elt);
        step = new_task(T_GET, item);
        vh_pstore(item, "STEP", step);
        if (vh_iget(item, "SCORE") > 0 || vh_iget(item, "FINISH"))
            add_task(step);
    }

    /* Create user task steps */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        step = new_task(T_USER, task);
        vh_pstore(task, "STEP", step);
        add_task(step);
    }

    /* Process tasks (1st pass) */
    if (ifm_debug) {
        indent(1);
        printf("Adding dependencies for task 'follow' entries\n");
    }

    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        tstep = vh_pget(task, "STEP");

        /* Deal with 'follow' tasks */
        if ((otask = vh_pget(task, "FOLLOW")) != NULL) {
            step = vh_pget(otask, "STEP");
            if (vh_exists(step, "NEXT") && vh_pget(step, "NEXT") != tstep)
                err("more than one task needs to follow `%s' immediately",
                    vh_sgetref(otask, "DESC"));
            order_tasks(step, tstep);
            vh_pstore(step, "NEXT", tstep);
            vh_pstore(tstep, "PREV", step);
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
                vh_sstore(step, "UNSAFE", "closes off room");
            }
        }

        /* Invert room 'leave' list if leaving all */
        list = vh_pget(room, "LEAVE");
        if (vh_iget(room, "LEAVEALL")) {
            num++;
            newlist = NULL;

            if (list != NULL) {
                vl_foreach(elt, list) {
                    item = vs_pget(elt);
                    vh_istore(item, "NOLEAVE", num);
                }
            }

            vl_foreach(elt, items) {
                item = vs_pget(elt);
                if (vh_iget(item, "NOLEAVE") == num)
                    continue;
                if (newlist == NULL)
                    newlist = vl_create();
                vl_ppush(newlist, item);
            }

            vh_pstore(room, "LEAVE", newlist);
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
                    add_task(step);
                }
            }
        }

        vl_foreach(elt, rlist) {
            reach = vs_pget(elt);

            /* Invert reach 'leave' list if leaving all */
            list = vh_pget(reach, "LEAVE");
            if (vh_iget(reach, "LEAVEALL")) {
                num++;
                newlist = NULL;

                if (list != NULL) {
                    vl_foreach(elt, list) {
                        item = vs_pget(elt);
                        vh_istore(item, "NOLEAVE", num);
                    }
                }

                vl_foreach(elt, items) {
                    item = vs_pget(elt);
                    if (vh_iget(item, "NOLEAVE") == num)
                        continue;
                    if (newlist == NULL)
                        newlist = vl_create();
                    vl_ppush(newlist, item);
                }

                vh_pstore(reach, "LEAVE", newlist);
            }

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
                    vh_sstore(step, "UNSAFE", "closes off link");
                }
            }

            /* Mention 'after' tasks for this connection */
            if ((list = vh_pget(reach, "AFTER")) != NULL) {
                vl_foreach(elt, list) {
                    task = vs_pget(elt);
                    step = vh_pget(task, "STEP");
                    vh_istore(step, "MODPATH", 1);
                    add_task(step);
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
                    add_task(step);
                }
            }
        }
    }

    /* Process items */
    if (ifm_debug) {
        indent(1);
        printf("Adding dependencies for item 'before/after' lists\n");
    }

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
                    order_tasks(get, istep);
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
                order_tasks(step, istep);
            }
        }

        /* Deal with 'before' tasks */
        if ((list = vh_pget(item, "BEFORE")) != NULL) {
            vl_foreach(elt, list) {
                task = vs_pget(elt);
                step = vh_pget(task, "STEP");
                order_tasks(istep, step);
            }
        }
    }

    if (ifm_debug) {
        indent(1);
        printf("Adding dependencies for task 'need/get/give/after' lists\n");
    }

    /* Process tasks (2nd pass) */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        tstep = vh_pget(task, "STEP");

        /* Invert task 'drop' list if dropping all */
        list = vh_pget(task, "DROP");
        if (vh_iget(task, "DROPALL")) {
            num++;
            newlist = NULL;

            if (list != NULL) {
                vl_foreach(elt, list) {
                    item = vs_pget(elt);
                    vh_istore(item, "NODROP", num);
                }
            }

            vl_foreach(elt, items) {
                item = vs_pget(elt);
                if (vh_iget(item, "NODROP") == num)
                    continue;
                if (newlist == NULL)
                    newlist = vl_create();
                vl_ppush(newlist, item);
            }

            vh_pstore(task, "DROP", newlist);
        }

        /* Must get required items before doing this task */
        if ((list = vh_pget(task, "NEED")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                vh_istore(item, "USED", 1);

                room = vh_pget(item, "ROOM");
                if (room != NULL) {
                    get = vh_pget(item, "STEP");
                    order_tasks(get, tstep);
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

        /* Must do this task before giving or getting supplied items */
        if ((list = vh_pget(task, "GET")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                room = vh_pget(item, "ROOM");
                if (room != NULL) {
                    get = vh_pget(item, "STEP");
                    order_tasks(tstep, get);
                }
            }
        }

        if ((list = vh_pget(task, "GIVE")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);
                room = vh_pget(item, "ROOM");
                if (room != NULL) {
                    get = vh_pget(item, "STEP");
                    order_tasks(tstep, get);
                }
            }
        }

        /* Must do this task after all preceding tasks */
        if ((list = vh_pget(task, "AFTER")) != NULL) {
            vl_foreach(elt, list) {
                otask = vs_pget(elt);
                after = vh_pget(otask, "STEP");
                order_tasks(after, tstep);
            }
        }
    }

    if (ifm_debug) {
        indent(1);
        printf("Adding dependencies for task 'lose' lists\n");
    }

    /* Process tasks (3rd pass) */
    vl_foreach(elt, tasks) {
        task = vs_pget(elt);
        tstep = vh_pget(task, "STEP");

        /* Add dependencies for tasks which lose items */
        if ((list = vh_pget(tstep, "LOSE")) != NULL) {
            vl_foreach(elt, list) {
                item = vs_pget(elt);

                if ((itasks = vh_pget(item, "TASKS")) != NULL) {
                    vl_foreach(elt, itasks) {
                        step = vs_pget(elt);
                        order_tasks(step, tstep);
                    }
                }

                /* If item is needed for paths, mark task unsafe */
                if (vh_exists(item, "NEEDED"))
                    vh_sstore(tstep, "UNSAFE", "loses item needed for paths");
            }
        }
    }
}

/* Solve the game by ordering the task list */
void
solve_game(void)
{
    vhash *room, *step, *trystep, *item, *task, *next;
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
    location = startroom;
    next = NULL;

    if (ifm_debug)
        printf("\nSolving game...\n");

    do {
        if (ifm_debug) {
            indent(1);
            printf("Location: %s\n", vh_sgetref(location, "DESC"));
        }

        /* Initialise path searches from this room */
        init_path(location);

        /* Check for dropping unneeded items */
        if (next == NULL) {
            vl_foreach(elt, items) {
                item = vs_pget(elt);

                if (!vh_iget(item, "TAKEN"))
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
                    step = new_task(T_DROP, item);
                    do_task(step, 1);
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
            if (!task_possible(location, trystep))
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
            goto_room(step);
            tasksleft = do_task(step, 1);
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
        } else if (ifm_debug) {
            indent(2);
            printf("no more tasks\n\n");
        }
    } while (tasksleft);
}

/* Return a task required by a given task, if any */
vhash *
require_task(vhash *step)
{
    vhash *before;
    vlist *depend;
    vscalar *elt;

    if ((depend = vh_pget(step, "DEPEND")) != NULL) {
        vl_foreach(elt, depend) {
            before = vs_pget(elt);
            if (!vh_iget(before, "DONE")) {
                vl_break(depend);
                return before;
            }
        }
    }

    return NULL;
}

/* Return whether a task is possible */
static int
task_possible(vhash *room, vhash *step)
{
    vhash *taskroom, *gotoroom, *droproom;
    char *safemsg = NULL;
    int len = 0;

    /* All dependent tasks must be done */
    if (require_task(step) != NULL)
        return 0;

    taskroom = vh_pget(step, "ROOM");
    gotoroom = vh_pget(step, "GOTO");

    if (ifm_debug) {
        indent(2);
        printf("consider: %s\n", vh_sgetref(step, "DESC"));
    }

    /* If task is done elsewhere, make sure you can get there */
    if (taskroom != NULL && taskroom != room) {
        if ((len = find_path(step, room, taskroom)) == NOPATH)
            return 0;
    }

    /* See whether task is safe */
    if (vh_exists(step, "SAFE")) {
        /* User says it's safe, and they know best */
    } else if (vh_exists(step, "UNSAFE")) {
        /* It's been flagged unsafe already */
        safemsg = vh_sgetref(step, "UNSAFE");
    } else {
        /* If no return path, mark it as unsafe */
        if (gotoroom == NULL)
            gotoroom = taskroom;
        if (gotoroom != NULL && find_path(NULL, gotoroom, room) == NOPATH)
            safemsg = "no return path";

        /* If task drops items, check you can get them back */
        if (vh_pget(step, "DROP") != NULL) {
            droproom = vh_pget(step, "DROPROOM");

            if (droproom == NULL)
                droproom = taskroom;
            if (droproom == NULL)
                droproom = location;

            if (find_path(NULL, gotoroom, droproom) == NOPATH)
                safemsg = "no path to dropped items";
        }
    }

    /* Record safe flag */
    vh_istore(step, "SAFEFLAG", safemsg == NULL);

    if (ifm_debug) {
        indent(2);
        printf("possible: %s", vh_sgetref(step, "DESC"));
        if (len > 0)
            printf(" (dist %d)", len);
        if (safemsg != NULL)
            printf(" (unsafe: %s)", safemsg);
        printf("\n");
    }

    return 1;
}
