## Automake template for IFM documentation.

docdir = $(prefix)/doc
ifmdocdir = $(docdir)/ifm

MAN_TITLE = Interactive Fiction Mapper

man_MANS = ifm.1

# Documenation sources.

DOCFILES = diagnostics.rst index.rst intro.rst language.rst maps.rst	\
programs.rst solving.rst usage.rst

# Programs.

IFM      = $(top_srcdir)/src/ifm -s version="$(VERSION)"
IFMCMD   = $(IFM) -I $(top_srcdir)/lib
HELP2MAN = $(top_srcdir)/etc/missing --run help2man -N -n "$(MAN_TITLE)"

# Main targets.

all: guide manpage

# User guide.

.PHONY: html latex

HTMLDIR  = html
LATEXDIR = latex

guide: html

force:; @ rm -rf $(HTMLDIR); $(MAKE) all

SPHINX = sphinx-build -N
SPHINXOPTS = 

setup:;	@ mkdir -p $(HTMLDIR)/.doctrees $(HTMLDIR)/.linkcheck

html: setup conf.py logo.png
	$(SPHINX) -b $@ $(SPHINXOPTS) . $(HTMLDIR)

latex: conf.py
	@ mkdir -p $(LATEXDIR)
	$(SPHINX) -b $@ $(SPHINXOPTS) . $(LATEXDIR)

linkcheck: setup conf.py
	$(SPHINX) -b $@ $(SPHINXOPTS) . $(HTMLDIR)/.linkcheck

logo.png: logo.ifm ifm2web
	./ifm2web $< $@
#	$(IFMCMD) -m -f fig -o logo.fig $<
#	fig2dev -L png -m 0.3 logo.fig > $@
#	rm -f logo.fig

# Man page.

manpage: ifm.1

ifm.1: ifm.man
	cp ifm.man ifm.tmp
	echo "[SEE ALSO]" >> ifm.tmp
	echo ".IP $(ifmdocdir)" >> ifm.tmp
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
	@ if test -d $(srcdir)/html; then				\
	   set -x;							\
	   rm -rf $(ifmdocdir);						\
	   mkdir -p $(ifmdocdir);					\
	   cp -rf $(srcdir)/html/* $(ifmdocdir);			\
	fi

$(ifmdocdir):
	- chmod u+w $(prefix)
	$(mkinstalldirs) $(docdir)
	- chmod u+w $(docdir)
	$(mkinstalldirs) $(ifmdocdir)

# Distribution stuff.

EXTRA_DIST = $(DOCFILES) ifm.1 ifm.man examples templates

dist-doc: $(EXTRA_DIST)
	if test -d $(srcdir)/html; then					\
	   cp -rf $(srcdir)/html $(distdir);				\
	fi

# Other stuff.

distclean-local: clean-doc

install-data-hook: install-doc

uninstall-hook:
	- chmod -R u+w $(ifmdocdir)
	rm -rf $(ifmdocdir)

dist-hook: dist-doc

include $(top_srcdir)/etc/Makefile.common
