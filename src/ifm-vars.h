/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Variable function header */

#ifndef IFM_VARS_H
#define IFM_VARS_H

#define VAR_DEF(var)  (var_get(var) != NULL)

/* Advertised functions */
extern char *var_colour(char *id);
extern vscalar *var_get(char *id);
extern int var_int(char *id);
extern double var_real(char *id);
extern void var_set(char *driver, char *id, vscalar *val);
extern char *var_string(char *id);
extern char *var_subst(char *string);

#endif
