/*
 *  Ifm, copyright (C) 1997, 1998 G. Hutchings
 *  Ifm comes with ABSOLUTELY NO WARRANTY.
 *  This is free software, and you are welcome to redistribute it
 *  under certain conditions; see the file COPYING for details.
 */

/* Variable functions */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vars.h>

#include "ifm-main.h"
#include "ifm-util.h"
#include "ifm-vars.h"

#define INIT_VARS \
        if (vars == NULL) vars = vh_create()

#define ALPHA(c) (c == '_' || isalpha(c))
#define ALNUM(c) (c == '_' || isalnum(c))

/* Defined variables */
static vhash *vars = NULL;

/* Scribble buffer */
static char buf[BUFSIZ];

/* Variable encoding buffer */
static char encbuf[BUFSIZ];

/* Internal functions */
static vhash *read_colour_defs(FILE *fp);
static vlist *var_decode(char *code);
static char *var_encode(char *driver, char *var);

/* Read and return colour definitions from a stream */
static vhash *
read_colour_defs(FILE *fp)
{
    int red, green, blue, pos;
    char val[20];
    vhash *defs;

    defs = vh_create();

    while (fgets(buf, BUFSIZ, fp) != NULL) {
        /* Get RGB values */
        if (sscanf(buf, "%d %d %d", &red, &green, &blue) != 3)
            continue;

        /* Get offset of colour name */
        if ((pos = strspn(buf, "0123456789 \t\n")) == 0)
            continue;

        /* Scale RGB values */
        sprintf(val, "%.3g %.3g %.3g",
                red / 255.0, green / 255.0, blue / 255.0);

        /* Add colour */
        v_chop(buf);
        vh_sstore(defs, &buf[pos], val);
    }

    return defs;
}

/* Return RGB values from a variable */
char *
var_colour(char *id)
{
    static vhash *defs = NULL;
    double red, green, blue;
    char *name;
    FILE *fp;

    /* Read colour definitions if required */
    if (defs == NULL) {
        fp = open_file(var_string("colour_file"), 1, 1);
        defs = read_colour_defs(fp);
        fclose(fp);
    }

    /* Get colour name */
    name = var_string(id);

    /* If colour name looks like RGB values, leave it */
    if (sscanf(name, "%lf %lf %lf", &red, &green, &blue) == 3)
        return name;

    /* Otherwise, look up colour name */
    if (!vh_exists(defs, name))
        fatal("colour `%s' is not defined", name);

    return vh_sgetref(defs, name);
}

/* Decode an encoded variable */
static vlist *
var_decode(char *code)
{
    static vlist *list = NULL;
    vscalar *val;

    INIT_VARS;

    if (list != NULL)
        vl_destroy(list);
    list = vl_split(code, NULL);

    val = vh_get(vars, code);
    vl_push(list, vs_copy(val));

    return list;
}

/* Encode a variable */
static char *
var_encode(char *driver, char *var)
{
    sprintf(encbuf, "%s %s", (driver == NULL ? "default" : driver), var);
    return encbuf;
}

/* Return value of a variable */
vscalar *
var_get(char *id)
{
    vscalar *var;
    char *key;

    INIT_VARS;

    /* Check current output format first */
    if (ifm_format != NULL) {
        key = var_encode(ifm_format, id);
        if ((var = vh_get(vars, key)) != NULL)
            return var;
    }
        
    /* Check global variables */
    key = var_encode(NULL, id);
    if ((var = vh_get(vars, key)) != NULL)
        return var;

    return NULL;
}

/* Return an integer variable */
int
var_int(char *id)
{
    vscalar *var = var_get(id);

    if (var == NULL)
        fatal("integer variable `%s' is not defined", id);

    return vs_iget(var);
}

/* Return a real variable */
double
var_real(char *id)
{
    vscalar *var = var_get(id);

    if (var == NULL)
        fatal("real variable `%s' is not defined", id);

    return vs_dget(var);
}

/* Set a scalar variable */
void
var_set(char *driver, char *id, vscalar *val)
{
    char *key = var_encode(driver, id);

    INIT_VARS;

    if (val != NULL)
        vh_store(vars, key, val);
    else
        vh_delete(vars, key);
}

/* Return a string variable */
char *
var_string(char *id)
{
    vscalar *var = var_get(id);

    if (var == NULL)
        fatal("string variable `%s' is not defined", id);

    return vs_sgetcopy(var);
}

/* Substitute variable values in a string */
char *
var_subst(char *string)
{
    static vbuffer *b = NULL;
    char *var, *cp, save;
    int braceflag;
    vscalar *val;

    /* Initialise */
    if (b == NULL)
        b = vb_create();
    else
        vb_empty(b);

    /* Scan the string */
    cp = string;
    while (*cp != '\0') {
        /* If not $, just echo */
        if (*cp != '$') {
            vb_putc(b, *cp++);
            continue;
        }

        /* If $$, turn it into $ */
        if (*++cp == '$') {
            vb_putc(b, *cp++);
            continue;
        }

        /* If not start of variable, just echo */
        if (!ALPHA(*cp) && *cp != '{') {
            vb_putc(b, '$');
            vb_putc(b, *cp++);
            continue;
        }

        /* Find end of variable */
        braceflag = (*cp == '{');
        var = cp;
        if (braceflag)
            var++;

        while (*++cp != '\0') {
            if (braceflag && *cp == '}')
                break;
            if (!braceflag && !ALNUM(*cp))
                break;
        }

        if (braceflag && *cp == '\0') {
            /* Unterminated brace */
            vb_puts(b, "${");
            cp = var;
        } else {
            /* Get variable */
            save = *cp;
            *cp = '\0';
            val = var_get(var);
            *cp = save;
            if (braceflag)
                cp++;

            /* Substitute it */
            if (val != NULL)
                vb_puts(b, vs_sget(val));
        }
    }

    return vb_get(b);
}
