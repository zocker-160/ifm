/* Utility function header */

#ifndef FIG_UTIL_H
#define FIG_UTIL_H

#include <vars.h>

extern int fig_calc_bbox(vhash *object);
extern void fig_fatal(char *fmt, ...);
extern vhash *fig_get_figure(vhash *object);

#endif
