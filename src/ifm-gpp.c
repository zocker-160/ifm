/* GPP interface functions */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vars.h>

#include "ifm-gpp.h"

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
    "-n",
    "-U \"" U1 AND U2 AND U3 AND U4 AND U5 AND U6 AND U7 AND U8 AND U9 "\"",
    "-M \"" M1 AND M2 AND M3 AND M4 AND M5 AND M6 AND M7 "\"",
    "+c \"" C11 AND C12 "\"",
    "+c \"" C21 AND C22 "\"",
    "+s \"" S1 AND S2 AND S3 "\"",
    "-includemarker \"#line % \\\"%\\\" %\"",
    NULL
};

/* The command buffer */
static char gpp_cmd[BUFSIZ];

/* Scribble buffer */
static char buf[BUFSIZ];

/* Close GPP */
void
gpp_close(FILE *fp)
{
    pclose(fp);
}

/* Define a GPP token */
void
gpp_define(char *var, char *val)
{
    if (val == NULL) {
        gpp_option("-D", var);
    } else {
        sprintf(buf, "%s=%s", var, val);
        gpp_option("-D", buf);
    }
}

/* Set GPP include paths */
void
gpp_include(char *paths)
{
    char *path;

    strcpy(buf, paths);
    path = strtok(buf, ":");

    while (path != NULL) {
	gpp_option("-I", path);
	path = strtok(NULL, ":");
    }
}

/* Initialise GPP */
int
gpp_init(void)
{
    int i;

    strcpy(gpp_cmd, "gpp");

    for (i = 0; gpp_args[i] != NULL; i++) {
        strcat(gpp_cmd, " ");
        strcat(gpp_cmd, gpp_args[i]);
    }

#ifdef GPP_DEBUG
    fprintf(stderr, "%s\n", gpp_cmd);
#endif

    return 1;
}

/* Open GPP */
FILE *
gpp_open(char *file)
{
    static char buf[BUFSIZ];

    if (file != NULL)
        sprintf(buf, "%s %s", gpp_cmd, file);
    else
        strcpy(buf, gpp_cmd);

    return popen(buf, "r");
}

/* Set a GPP option */
void
gpp_option(char *opt, char *arg)
{
    strcat(gpp_cmd, " ");
    strcat(gpp_cmd, opt);
    if (arg != NULL)
	strcat(gpp_cmd, arg);
}
