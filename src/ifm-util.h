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
extern void add_attr(vhash *obj, char *attr, char *fmt, ...);
extern void add_list(vhash *obj, char *attr, vhash *thing);
extern int get_direction(int xoff, int yoff);
extern int get_papersize(char *pagesize, float *width, float *height);
extern void indent(int num);
extern void obsolete(char *old, char *new);
extern FILE *open_file(char *file, int libflag, int required);
extern int pack_sections(int xmax, int ymax, int border);
extern void put_string(char *fmt, ...);
extern void setup_room_names(int jflag, int tflag);
extern vlist *split_line(char *string, double ratio);
extern void truncate_points(vlist *x, vlist *y, double wid, double ht);

#endif
