## Automake template for ifm.

AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = ifm 

ifm_SOURCES = ifm-driver.h ifm-groff.c ifm-groff.h ifm-main.c ifm-main.h    \
	      ifm-map.c ifm-map.h ifm-parse.y ifm-parse.h ifm-path.c	    \
	      ifm-path.h ifm-ps.c ifm-ps.h ifm-raw.c ifm-raw.h ifm-scan.l   \
	      ifm-task.c ifm-task.h ifm-text.c ifm-text.h ifm-tk.c ifm-tk.h \
	      ifm-util.c ifm-util.h

ifm_LDADD	= -lvars

SYS_INIT	= ifm-init.ifm

PS_PROLOG	= ifm-pro.ps

LIBFILES	= $(PS_PROLOG)

pkgdata_DATA	= $(LIBFILES)

EXTRA_DIST 	= $(LIBFILES)

IFMLIB		= ../lib

INCLUDES	= -I$(IFMLIB) \
		  -DVERSION=\"$(VERSION)\" \
		  -DIFMPATH=\".:$(pkgdatadir)\" \
		  -DPS_PROLOG=\"$(PS_PROLOG)\" \
		  -DSYSINIT=\"$(pkgdatadir)/$(SYS_INIT)\" \
		  -DPS -DTEXT -DTK -DRAW -DGROFF

YFLAGS		= -d

LDFLAGS		= -L$(IFMLIB)

ifm-parse.h:	ifm-parse.c

lint:;		lint -habx $(INCLUDES) *.c
