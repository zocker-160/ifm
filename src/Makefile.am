## Automake template for ifm.

bin_PROGRAMS = ifm

ifm_SOURCES = ifm-driver.h ifm-main.c ifm-main.h ifm-map.c ifm-map.h	  \
ifm-parse.y ifm-parse.h ifm-path.c ifm-path.h ifm-ps.c ifm-ps.h ifm-raw.c \
ifm-raw.h ifm-rec.c ifm-rec.h ifm-scan.l ifm-task.c ifm-task.h ifm-text.c \
ifm-text.h ifm-tk.c ifm-tk.h ifm-util.c ifm-util.h

ifm_LDADD = -lvars

ifm_LDFLAGS = -L../lib

PS_PROLOG = ifm-pro.ps

LIBFILES = $(PS_PROLOG)

pkgdata_DATA = $(LIBFILES)

EXTRA_DIST = $(LIBFILES)

YFLAGS = -d -v

INCLUDES = -I../lib -DSYSINIT=\"$(pkgdatadir)/ifm-init.ifm\"		\
           -DIFMPATH=\".:$(pkgdatadir)\" -DPS_PROLOG=\"$(PS_PROLOG)\"

$(bin_PROGRAMS): ../lib/libvars.a

ifm-parse.h: ifm-parse.c

lint:; lint -habx $(DEFS) $(INCLUDES) *.c
