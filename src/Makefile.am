## Automake template for ifm.

bin_PROGRAMS = ifm

ifm_SOURCES = ifm-driver.h ifm-main.c ifm-main.h ifm-map.c ifm-map.h	  \
ifm-parse.y ifm-parse.h ifm-path.c ifm-path.h ifm-ps.c ifm-ps.h ifm-raw.c \
ifm-raw.h ifm-rec.c ifm-rec.h ifm-scan.l ifm-task.c ifm-task.h ifm-text.c \
ifm-text.h ifm-tk.c ifm-tk.h ifm-util.c ifm-util.h ifm-vars.c ifm-vars.h

VARS = ../vars

ifm_LDADD = -lvars

ifm_LDFLAGS = -L$(VARS)

YFLAGS = -d -v

INCLUDES = -I$(VARS) -DSYSINIT=\"ifm-init.ifm\" -DIFMPATH=\"$(pkgdatadir):.\"

$(bin_PROGRAMS): $(VARS)/libvars.a

ifm-parse.h: ifm-parse.c

lint:; lint -habx $(DEFS) $(INCLUDES) *.c
