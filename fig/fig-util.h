/* Utility function header */

#ifndef FIG_UTIL_H
#define FIG_UTIL_H

#include <vars.h>

#define fig_value(exp)                                                  \
        fig_debug(#exp ": %g", exp)

#define fig_get_ival(object, attr)                                      \
        vs_iget(fig_get_attr(object, attr))

#define fig_get_fval(object, attr)                                      \
        vs_fget(fig_get_attr(object, attr))

#define fig_get_sval(object, attr)                                      \
        vs_sget(fig_get_attr(object, attr))

extern int fig_calc_bbox(vhash *object);
extern void fig_debug(char *fmt, ...);
extern void fig_fatal(char *fmt, ...);
extern vscalar *fig_get_attr(vhash *object, char *attr);
extern vhash *fig_get_figure(vhash *object);

#endif
