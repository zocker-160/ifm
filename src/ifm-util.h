/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Utility function header */

#ifndef IFM_UTIL_H
#define IFM_UTIL_H

/* Various useful macros */
#define STREQ(s1, s2)           !strcmp(s1, s2)
#define ABS(x)                  ((x) > 0 ? (x) : -(x))
#define MIN(x, y)               ((x) < (y) ? (x) : (y))
#define MAX(x, y)               ((x) > (y) ? (x) : (y))

/* Direction stuff */
struct d_info {
    char *sname, *lname;
    int dir, odir;
    int xoff, yoff;
};

enum {
    D_NONE, D_NORTH, D_SOUTH, D_EAST, D_WEST, D_NORTHEAST, D_SOUTHWEST,
    D_NORTHWEST, D_SOUTHEAST, D_UP, D_DOWN, D_IN, D_OUT
};

extern struct d_info dirinfo[];

/* Advertised functions */
extern int get_direction(int xoff, int yoff);
extern int get_int(char *id, int def);
extern double get_real(char *id, double def);
extern char *get_string(char *id, char *def);
extern vscalar *get_var(char *id);
extern void indent(int num);
extern FILE *open_libfile(char *name);
extern int pack_sections(int xmax, int ymax, int border);
extern vlist *search_path(void);
extern void set_var(char *driver, char *type, char *var, vscalar *val);
extern void setup_room_names(int jflag, int tflag);
extern vlist *split_line(char *string, double ratio);
extern void truncate_points(vlist *x, vlist *y, double wid, double ht);

#endif
