/* GPP interface functions */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vars.h>

#include "ifm-gpp.h"
#include "ifm-main.h"
#include "ifm-util.h"

/* GPP program */
#ifdef CYGWIN
#define GPP "gpp.exe"
#else
#define GPP "gpp"
#endif

/* Standard GPP arguments */
#define U1 ""
#define U2 ""
#define U3 "("
#define U4 ","
#define U5 ")"
#define U6 "("
#define U7 ")"
#define U8 "%"
#define U9 ""

#define M1 "\\n%\\w"
#define M2 "\\n"
#define M3 " "
#define M4 " "
#define M5 "\\n"
#define M6 ""
#define M7 ""

#define C11 "#"
#define C12 "\\n"

#define C21 "\\\\\\n"
#define C22 ""

#define S1 "\\\""
#define S2 "\\\""
#define S3 "\\\\"

#define AND "\" \""

static char *gpp_args[] = {
    "-U \"" U1 AND U2 AND U3 AND U4 AND U5 AND U6 AND U7 AND U8 AND U9 "\"",
    "-M \"" M1 AND M2 AND M3 AND M4 AND M5 AND M6 AND M7 "\"",
    "+c \"" C11 AND C12 "\"", "+c \"" C21 AND C22 "\"",
    "+s \"" S1 AND S2 AND S3 "\"",
    "-n", "-nostdinc", "-includemarker \"#line % \\\"%\\\" %\"",
    NULL
};

/* The command buffer */
V_NBUF_DECL(gbuf);

/* Close GPP */
void
gpp_close(FILE *fp)
{
    pclose(fp);
}

/* Return the current GPP command */
char *
gpp_command(void)
{
    return V_NBUF_VAL(gbuf);
}

/* Define a GPP token */
void
gpp_define(char *var, char *val)
{
    V_BUF_DECL;

    if (val == NULL) {
        gpp_option("-D", var);
    } else {
        V_BUF_SET2("%s=%s", var, val);
        gpp_option("-D", V_BUF_VAL);
    }
}

/* Set GPP include paths */
void
gpp_include(char *paths)
{
    char *path;
    V_BUF_DECL;

    paths = V_BUF_SET(paths);
    path = strtok(paths, PATHSEP);

    while (path != NULL) {
	gpp_option("-I", path);
	path = strtok(NULL, PATHSEP);
    }
}

/* Initialise GPP */
int
gpp_init(void)
{
    char *path;
    int i;

    if ((path = find_file(GPP)) != NULL) {
        V_NBUF_SET(gbuf, path);
    } else {
        err("can't find '%s' in search path", GPP);
        return 0;
    }

    for (i = 0; gpp_args[i] != NULL; i++)
        gpp_option(gpp_args[i], NULL);

    return 1;
}

/* Open GPP */
FILE *
gpp_open(char *file)
{
    V_BUF_DECL;
    char *cmd;

    cmd = V_NBUF_VAL(gbuf);
    V_BUF_SET(cmd);

    if (file != NULL)
        V_BUF_ADD1(" '%s'", file);

    return popen(V_BUF_VAL, "r");
}

/* Set a GPP option */
void
gpp_option(char *opt, char *arg)
{
    V_NBUF_ADD1(gbuf, " %s", opt);

    if (arg != NULL)
        V_NBUF_ADD(gbuf, arg);
}
