/* Text interface to ifm, in -*- C -*- mode */

/* Prototypes */
void text_item_entry(vhash *item);
void text_task_entry(vhash *task);

/* Item function list */
itemfuncs text_itemfuncs = {
    NULL,
    text_item_entry,
    NULL
};

/* Task function list */
taskfuncs text_taskfuncs = {
    NULL,
    text_task_entry,
    NULL
};

/* Item functions */
void
text_item_entry(vhash *item)
{
    vhash *room = vh_pget(item, "ROOM");
    char *idesc = vh_sgetref(item, "DESC");
    char *rdesc = (room == NULL ? "" : vh_sgetref(room, "DESC"));
    char *note = vh_sgetref(item, "NOTE");

    printf("%s\t%s\t%s\n",
           idesc,
           (rdesc == NULL ? "" : rdesc),
           (note == NULL ? "" : note));
}

/* Task functions */
void
text_task_entry(vhash *task)
{
    vhash *room = vh_pget(task, "ROOM");
    int score = vh_iget(task, "SCORE");
    vlist *inv = vh_pget(task, "INVENT");
    char *note = vh_sgetref(task, "NOTE");
    static vhash *last = NULL;
    vlist *carried = vl_create();
    vscalar *elt;

    vl_foreach(elt, inv)
        vl_spush(carried, vh_sgetref(vs_pget(elt), "DESC"));

    printf("%s\t%s\t%s\t%s\t%s\n",
           (room == last || room == NULL ? "" : vh_sgetref(room, "DESC")),
           vh_sgetref(task, "DESC"),
           (note == NULL ? "" : note),
           (score ? vh_sget(task, "SCORE") : ""),
           vl_join(carried, ", "));

    vl_destroy(carried);
    if (room != NULL)
        last = room;
}
