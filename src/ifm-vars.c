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
        if (nvars == NULL) vars = nvars = vh_create(); \
        if (alias == NULL) alias = vh_create(); \
        if (styles == NULL) styles = vh_create()

#define VAR_GET(id, var) \
        if ((var = var_get(id)) == NULL) \
                fatal("variable `%s' is not defined", id)

#define ALPHA(c) (c == '_' || isalpha(c))
#define ALNUM(c) (c == '_' || isalnum(c))

/* Current variables */
static vhash *vars = NULL;

/* Defined non-style variables */
static vhash *nvars = NULL;

/* Defined aliases */
static vhash *alias = NULL;

/* Defined styles */
static vhash *styles = NULL;

/* Style stack */
static vlist *style_stack = NULL;

/* Scribble buffer */
static char buf[BUFSIZ];

/* Internal functions */
static vhash *read_colour_defs(FILE *fp);
static char *var_encode(char *driver, char *var);

/* Return the current style */
char *
current_style(void)
{
    if (style_stack == NULL || vl_length(style_stack) == 0)
        return NULL;
    return vl_stail(style_stack);
}

/* Push a style onto the style stack */
void
push_style(char *name)
{
    if (style_stack == NULL)
        style_stack = vl_create();
    vl_spush(style_stack, name);
    set_style(name);
}

/* Pop a style from the style stack */
void
pop_style(char *name)
{
    char *sname;

    if (style_stack != NULL && vl_length(style_stack) > 0) {
        sname = vl_spop(style_stack);
        if (name != NULL && !V_STREQ(sname, name))
            warn("unexpected style: %s (expected %s)", name, sname);
        if (vl_length(style_stack) > 0)
            set_style(vl_stail(style_stack));
        else
            set_style(NULL);
    } else {
        warn("no matching style command");
    }
}

/* Set the current style */
void
set_style(char *name)
{
    INIT_VARS;

    if (name != NULL && strlen(name) > 0) {
        if ((vars = vh_pget(styles, name)) == NULL) {
            vars = vh_create();
            vh_pstore(styles, name, vars);
        }
    } else {
        vars = nvars;
    }
}

/* Set a variable alias */
void
var_alias(char *alias_id, char *id)
{
    if (id != NULL)
        vh_sstore(alias, alias_id, id);
    else
        vh_delete(alias, alias_id);
}

/* Return whether a variable has changed since last accessed */
int
var_changed(char *id)
{
    static vhash *values = NULL;
    vscalar *sval, *cval;
    int changed = 1;

    if (values == NULL)
        values = vh_create();

    sval = var_get(id);

    if ((cval = vh_get(values, id)) == NULL && sval == NULL)
        changed = 0;
    else if (cval != NULL && sval != NULL && vs_equal(cval, sval))
        changed = 0;

    if (changed)
        vh_store(values, id, vs_copy(sval));

    return changed;
}

/* Return RGB values from a variable */
char *
var_colour(char *id)
{
    static vhash *defs = NULL;
    double red, green, blue;
    char *name;
    FILE *fp;

    /* Get colour name */
    name = var_string(id);

    /* If colour name looks like RGB values, leave it */
    if (sscanf(name, "%lf %lf %lf", &red, &green, &blue) == 3)
        return name;

    /* Read colour definitions if required */
    if (defs == NULL) {
        fp = open_file(var_string("colour_file"), 1, 1);
        defs = read_colour_defs(fp);
        fclose(fp);
    }

    /* Look up colour name */
    if (!vh_exists(defs, name))
        fatal("colour `%s' is not defined", name);

    return vh_sgetref(defs, name);
}

/* Encode a variable */
static char *
var_encode(char *driver, char *var)
{
    static char encbuf[BUFSIZ];
    sprintf(encbuf, "%s %s", (driver == NULL ? "global" : driver), var);
    return encbuf;
}

/* Return value of a variable */
vscalar *
var_get(char *id)
{
    vscalar *var;
    char *key;

    INIT_VARS;

    /* Check aliases */
    if (vh_exists(alias, id))
        id = vh_sgetref(alias, id);

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

    /* Try non-style variables if required */
    if (vars != nvars) {
        if (ifm_format != NULL) {
            key = var_encode(ifm_format, id);
            if ((var = vh_get(nvars, key)) != NULL)
                return var;
        }
        
        key = var_encode(NULL, id);
        if ((var = vh_get(nvars, key)) != NULL)
            return var;
    }

    return NULL;
}

/* Return an integer variable */
int
var_int(char *id)
{
    vscalar *var;
    VAR_GET(id, var);
    return (var != NULL ? vs_iget(var) : 0);
}

/* List variables to stdout */
void
var_list(void)
{
    vscalar *elt, *val;
    char *name, *sval;
    vlist *names;

    INIT_VARS;

    /* Variables */
    names = vh_sortkeys(vars, NULL);

    printf("# Variables.\n");
    vl_foreach(elt, names) {
        name = vs_sgetref(elt);
        printf("%s = ", name);
        val = vh_get(vars, name);

        switch (vs_type(val)) {
        case V_STRING:
            sval = vs_sgetref(val);
            putchar('"');

            while (*sval != '\0') {
                if (*sval == '\\')
                    putchar('\\');
                putchar(*sval++);
            }

            putchar('"');
            break;
        default:
            printf("%s", vs_sget(val));
            break;
        }

        printf(";\n");
    }

    vl_destroy(names);

    /* Aliases */
    names = vh_sortkeys(alias, NULL);

    if (vl_length(names) > 0) {
        printf("\n# Aliases.\n");

        vl_foreach(elt, names) {
            name = vs_sgetref(elt);
            printf("%s => %s;\n", name, vh_sgetref(alias, name));
        }
    }

    vl_destroy(names);
}

/* Return a real variable */
double
var_real(char *id)
{
    vscalar *var;
    VAR_GET(id, var);
    return (var != NULL ? vs_dget(var) : 0.0);
}

/* Set a scalar variable */
void
var_set(char *driver, char *id, vscalar *val)
{
    char *key;

    INIT_VARS;

    /* Check aliases */
    if (vh_exists(alias, id))
       id = vh_sgetref(alias, id);

    /* Set variable */
    key = var_encode(driver, id);

    if (val != NULL)
        vh_store(vars, key, val);
    else
        vh_delete(vars, key);
}

/* Return a string variable */
char *
var_string(char *id)
{
    vscalar *var;
    VAR_GET(id, var);
    return (var != NULL ? vs_sgetcopy(var) : "");
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
            VAR_GET(var, val);
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
