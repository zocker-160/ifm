/* GPP interface function header */

#ifndef IFM_GPP_H
#define IFM_GPP_H

#include <stdio.h>

extern void gpp_close(FILE *fp);
extern char *gpp_command(void);
extern void gpp_define(char *var, char *val);
extern void gpp_include(char *paths);
extern int gpp_init(void);
extern FILE *gpp_open(char *file);
extern void gpp_option(char *opt, char *arg);

#endif
