/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Build function header */

#ifndef IFM_BUILD_H
#define IFM_BUILD_H

/* External vars */
extern vhash *map;
extern vlist *rooms, *links, *joins, *items, *tasks, *sects;
extern vhash *rpos, *vars;
extern vhash *roomtags, *itemtags, *tasktags;
extern vhash *curroom, *curlink, *curitem, *curjoin, *curtask;
extern vlist *curdirs, *curitems, *curlinks, *curjoins, *curtasks;
extern vhash *startroom, *lastroom, *lastitem, *lasttask;
extern vlist *taskorder, *sectnames;
extern int mapnum;

/* Advertised functions */
extern void add_dir(int dir);
extern void get_offset(int dir, int *xoff, int *yoff);
extern void init_map(void);
extern void resolve_tag(char *type, vscalar *elt, vhash *table);
extern void resolve_tag_list(char *type, vlist *list, vhash *table);
extern void resolve_tags(void);
extern void set_tag(char *type, char *tag, vhash *val, vhash *table);
extern void setup_sections(void);

#endif
