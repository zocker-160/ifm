/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Map function header */

#ifndef IFM_MAP_H
#define IFM_MAP_H

/* External vars */
extern vhash *map;
extern vlist *rooms, *links, *joins, *items, *tasks, *sects;
extern vhash *vars;
extern vhash *roomtags, *itemtags, *tasktags;
extern vhash *curroom, *curlink, *curitem, *curjoin, *curtask;
extern vlist *curdirs, *curitems, *curlinks, *curjoins, *curtasks;
extern vhash *startroom, *lastroom, *lastitem, *lasttask;
extern vlist *taskorder, *sectnames;
extern int mapnum;

/* Advertised functions */
extern void init_map(void);
extern void resolve_tags(void);
extern void room_exit(vhash *room, int xoff, int yoff, int flag);
extern void set_tag(char *type, char *tag, vhash *val, vhash *table);
extern void setup_exits(void);
extern void setup_links(void);
extern void setup_rooms(void);
extern void setup_sections(void);

#endif
