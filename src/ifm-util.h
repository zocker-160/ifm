/*
 *  Ifm version 1.0, Copyright (C) 1997 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Utility function header */

#ifndef IFM_UTIL_H
#define IFM_UTIL_H

/* Advertised functions */
extern int get_int(char *id, int def);
extern double get_real(char *id, double def);
extern char *get_string(char *id, char *def);
extern vscalar *get_var(char *id);
extern void set_var(char *table1, char *table2, char *var,
                    vscalar *val);
extern vlist *split_line(char *string, double ratio);
extern void truncate_link(vhash *link, double wid, double ht);

#endif
