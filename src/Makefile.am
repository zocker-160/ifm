## Automake template for ifm.

bin_PROGRAMS = ifm

SRCS = ifm-dot.c ifm-driver.c ifm-fig.c ifm-gpp.c ifm-main.c ifm-map.c	\
ifm-path.c ifm-ps.c ifm-raw.c ifm-rec.c ifm-task.c ifm-text.c ifm-tk.c	\
ifm-util.c ifm-vars.c

NOLINT_SRCS = ifm-parse.y ifm-scan.l

HDRS = ifm-dot.h ifm-driver.h ifm-fig.h ifm-gpp.h ifm-main.h ifm-map.h	  \
ifm-parse.h ifm-path.h ifm-ps.h ifm-raw.h ifm-rec.h ifm-task.h ifm-text.h \
ifm-tk.h ifm-util.h ifm-vars.h

ifm_SOURCES = $(SRCS) $(NOLINT_SRCS) $(HDRS)

EXTRA_DIST = ifm-parse.c ifm-scan.c

FIG_SRC = $(top_srcdir)/fig
FIG_BIN = $(top_builddir)/fig

VARS_SRC = $(top_srcdir)/vars/src
VARS_BIN = $(top_builddir)/vars/src

ifm_LDADD = -lfig -lvars -lm

ifm_LDFLAGS = -L$(FIG_BIN) -L$(VARS_BIN)

YFLAGS = -d -v

SYSDEF = -DSYSINIT=\"ifm-init.ifm\"

PATHDEF = -DIFMPATH=\"$(pkgdatadir)\"

GPPDEF = -DGPPPATH=\"$(pkglibdir)/gpp\"

INCLUDES = -I$(FIG_SRC) -I$(VARS_SRC) $(SYSDEF) $(PATHDEF) $(GPPDEF)

$(bin_PROGRAMS): $(FIG_BIN)/libfig.a $(VARS_BIN)/libvars.a

ifm-parse.h: ifm-parse.c

# Add lint support.

SUFFIXES = .lint

LINT = splint

LINTARGS = +quiet -weak +show-scan -badflag

LINTGLOBAL = -fixed-formal-array +posix-lib +export-header +ignore-signs  \
-zero-ptr +eval-order +noret +unreachable +noeffect +warn-lint-comments	  \
-null-deref +export-header-var +case-break -unrecog -buffer-overflow-high \
-ret-val-other +match-any-integral +relax-types

LINTDEFS = -I. $(CPPFLAGS) $(DEFS) $(INCLUDES)

LINTCMD = $(LINT) $(LINTARGS) $(LINTLOCAL) $(LINTGLOBAL) $(LINTFLAGS)	\
$(LINTDEFS)

.c.lint:; @ $(LINTCMD) $<

lint:; $(LINTCMD) $(DEFS) $(INCLUDES) $(SRCS)
