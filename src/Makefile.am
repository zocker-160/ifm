## Automake template for ifm.

bin_PROGRAMS = ifm 

ifm_SOURCES = ifm-build.c ifm-build.h ifm-driver.h ifm-groff.c ifm-groff.h  \
	      ifm-item.c ifm-item.h ifm-join.c ifm-join.h ifm-link.c	    \
	      ifm-link.h ifm-main.c ifm-main.h ifm-parse.y ifm-parse.h	    \
	      ifm-path.c ifm-path.h ifm-ps.c ifm-ps.h ifm-raw.c ifm-raw.h   \
	      ifm-room.c ifm-room.h ifm-scan.l ifm-task.c ifm-task.h	    \
	      ifm-text.c ifm-text.h ifm-tk.c ifm-tk.h ifm-util.c ifm-util.h \
	      ifm.h

SYS_INIT	= ifm-init.ifm

PS_PROLOG	= ifm-pro.ps

LIBFILES	= $(PS_PROLOG)

pkgdata_DATA	= $(LIBFILES)

EXTRA_DIST 	= $(LIBFILES)

INCLUDES	= -DVERSION=\"$(VERSION)\" \
		  -DIFMPATH=\".:$(pkgdatadir)\" \
		  -DPS_PROLOG=\"$(PS_PROLOG)\" \
		  -DSYSINIT=\"$(pkgdatadir)/$(SYS_INIT)\" \
		  -DPS -DTEXT -DTK -DRAW -DGROFF

LDFLAGS		= -Wl,-rpath -Wl,$(libdir)
