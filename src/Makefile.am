## Automake template for ifm.

bin_PROGRAMS = ifm

SRCS = ifm-dot.c ifm-main.c ifm-map.c ifm-parse.y ifm-path.c ifm-ps.c	 \
ifm-raw.c ifm-rec.c ifm-scan.l ifm-task.c ifm-text.c ifm-tk.c ifm-util.c \
ifm-vars.c

HDRS = ifm-dot.h ifm-driver.h ifm-main.h ifm-map.h ifm-parse.h ifm-path.h \
ifm-ps.h ifm-raw.h ifm-rec.h ifm-task.h ifm-text.h ifm-tk.h ifm-util.h	  \
ifm-vars.h

ifm_SOURCES = $(SRCS) $(HDRS)

EXTRA_DIST = ifm-parse.c ifm-scan.c

VARS = ../vars/src

ifm_LDADD = -lvars-local

ifm_LDFLAGS = -L$(VARS)

YFLAGS = -d -v

INCLUDES = -I$(VARS) -DSYSINIT=\"ifm-init.ifm\" -DIFMPATH=\"$(pkgdatadir):.\"

$(bin_PROGRAMS): $(VARS)/libvars-local.a

ifm-parse.h: ifm-parse.c

lint:; lint -habx $(DEFS) $(INCLUDES) *.c
