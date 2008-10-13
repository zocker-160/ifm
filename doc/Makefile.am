## Automake template for IFM documentation.

docdir = $(prefix)/doc
builddir = $(top_builddir)/doc
ifmdocdir = $(docdir)/ifm
htmldir = $(builddir)/html
latexdir = $(builddir)/latex
sphinxdir = $(builddir)/sphinx

# Documentation sources.

DOCFILES = changes.rst diagnostics.rst ifm2dev.rst ifm2tex.rst index.rst \
intro.rst language.rst license.rst maps.rst programs.rst scr2ifm.rst	 \
solving.rst tkifm.rst usage.rst

# Programs.

IFM      = $(top_srcdir)/src/ifm -s version="$(VERSION)"
IFMCMD   = $(IFM) -I $(top_srcdir)/lib
HELP2MAN = $(OPTIONAL) help2man -N -n "$(MAN_TITLE)"
SPHINX   = $(OPTIONAL) sphinx-build -N -d $(sphinxdir) $(SPHINXOPTS)
OPTIONAL = $(top_srcdir)/etc/missing --run

# User guide.

.PHONY: html latex

guide: html

force:; @ rm -rf $(htmldir); $(MAKE) all

html: setup
	$(SPHINX) -b $@ $(srcdir) $(htmldir)

latex: setup
	$(SPHINX) -b $@ $(srcdir) $(latexdir)

linkcheck: setup
	$(SPHINX) -b $@ $(srcdir) $(sphinxdir)

setup:;	@ mkdir -p $(htmldir) $(latexdir) $(sphinxdir)
	@ for file in conf.py logo.png; do				\
	    path=$(builddir)/$$file;					\
	    test -f $$path || ln -s $(srcdir)/$$file $$path;		\
	done

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

install-data-hook: install-doc

uninstall-hook:
	- chmod -R u+w $(ifmdocdir)
	rm -rf $(ifmdocdir)

dist-hook: dist-doc

include $(top_srcdir)/etc/Makefile.common
