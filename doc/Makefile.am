## Automake template for IFM documentation.

docdir = $(prefix)/doc
builddir = $(top_builddir)/doc
ifmdocdir = $(docdir)/ifm
htmldir = $(builddir)/html
latexdir = $(builddir)/latex
sphinxdir = $(builddir)/sphinx

# Documenation sources.

DOCFILES = changes.rst diagnostics.rst ifm2dev.rst ifm2tex.rst index.rst \
intro.rst language.rst license.rst maps.rst programs.rst scr2ifm.rst	 \
solving.rst tkifm.rst usage.rst

# Programs.

IFM      = $(top_srcdir)/src/ifm -s version="$(VERSION)"
IFMCMD   = $(IFM) -I $(top_srcdir)/lib
HELP2MAN = $(top_srcdir)/etc/missing --run help2man -N -n "$(MAN_TITLE)"

# Main targets.

all: guide manpage

# User guide.

.PHONY: html latex

guide: html

force:; @ rm -rf $(htmldir); $(MAKE) all

SPHINX = sphinx-build -N -d $(sphinxdir) $(SPHINXOPTS)

setup:;	@ mkdir -p $(htmldir) $(sphinxdir)

html: setup conf.py logo.png
	$(SPHINX) -b $@ $(srcdir) $(htmldir)

latex: conf.py
	@ mkdir -p $(latexdir)
	$(SPHINX) -b $@ $(srcdir) $(latexdir)

linkcheck: setup conf.py
	$(SPHINX) -b $@ $(srcdir) $(sphinxdir)

# Man page.

MAN_TITLE = Interactive Fiction Mapper

man_MANS = ifm.1

manpage: ifm.1

ifm.1: ifm.man
	cp ifm.man ifm.tmp
	echo "[SEE ALSO]" >> ifm.tmp
	echo ".IP $(ifmdocdir)/index.html" >> ifm.tmp
	echo "Online documentation" >> ifm.tmp
	$(HELP2MAN) -o ifm.1 -i ifm.tmp $(IFM)
	rm -f ifm.tmp

mantest: man
	groff -man -Tps ifm.1 > ifm.ps
	gv -a4 -scale -1 -spartan ifm.ps
	rm -f ifm.ps

# Installation stuff.

install-doc: install-html

install-html: $(ifmdocdir)
	@ if test -d $(htmldir); then					\
	   set -x;							\
	   rm -rf $(ifmdocdir);						\
	   mkdir -p $(ifmdocdir);					\
	   cp -rf $(htmldir)/* $(ifmdocdir);				\
	fi

$(ifmdocdir):
	- chmod u+w $(prefix)
	$(mkinstalldirs) $(docdir)
	- chmod u+w $(docdir)
	$(mkinstalldirs) $(ifmdocdir)

# Distribution stuff.

EXTRA_DIST = $(DOCFILES) ifm.1 ifm.man examples templates logo.png

dist-doc: $(EXTRA_DIST)
	if test -d $(htmldir); then					\
	   cp -rf $(htmldir) $(distdir);				\
	fi

# Other stuff.

distclean-local: clean-doc

install-data-hook: install-doc

uninstall-hook:
	- chmod -R u+w $(ifmdocdir)
	rm -rf $(ifmdocdir)

dist-hook: dist-doc

include $(top_srcdir)/etc/Makefile.common
