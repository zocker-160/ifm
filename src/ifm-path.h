/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Path function header */

#ifndef IFM_PATH_H
#define IFM_PATH_H

/* Advertised functions */
extern void connect_rooms(void);
extern int find_path(vlist *path, vhash *from, vhash *to, int maxlen,
                     int *dist, int *len);

#endif
