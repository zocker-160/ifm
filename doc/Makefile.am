## Automake template for IFM documentation.

docdir = $(prefix)/doc
ifmdocdir = $(docdir)/ifm

PDF_TITLE  = IFM Version $(VERSION)
PDF_AUTHOR = Glenn Hutchings

# Main targets.

doc: fig pdf html

pdf: ifm.pdf

ps: ifm.ps

fig: cover.eps example.eps advent.eps

# General rules.

SUFFIXES = .lyx .ps .tex .aux .pdf .eps .fig .ifm .png .tex

IFM = $(top_srcdir)/src/ifm -I $(top_srcdir)/lib

.lyx.ps:;	lyx --export ps $< > $@
.lyx.tex:;	lyx --export latex $< > $@
.ps.gv:;	gv -a4 -scale -1 -spartan $<
.tex.aux:;	latex $<; latex $<; latex $<
.lyx.pdf:;	tex2pdf -t "$(PDF_TITLE)" -a "$(PDF_AUTHOR)" $<
.ifm.fig:;	$(IFM) -m -f fig -o $@ $<
.fig.eps:;	fig2dev -L eps $< > $@
.fig.png:;	fig2dev -L png $< > $@
.fig.tex:;	fig2dev -L latex $< > $@

html: fig ifm.lyx
	lyx2html ifm.lyx

# Installation stuff.

install-doc: install-html install-pdf

install-html: $(ifmdocdir)
	@ if test -d $(srcdir)/ifm; then				\
	   set -x;							\
	   rm -rf $(ifmdocdir)/html;					\
	   cp -rf $(srcdir)/ifm $(ifmdocdir)/html;			\
	fi

install-pdf: $(ifmdocdir)
	@ if test -f $(srcdir)/ifm.pdf; then				\
	   set -x;							\
	   $(INSTALL_DATA) $(srcdir)/ifm.pdf $(ifmdocdir);		\
	fi

$(ifmdocdir):
	- chmod u+w $(prefix)
	$(mkinstalldirs) $(docdir)
	- chmod u+w $(docdir)
	$(mkinstalldirs) $(ifmdocdir)

# Distribution stuff.

EXTRA_DIST = ifm.lyx gfdl.lyx advent.cmd advent.ifm advent1.scr advent2.scr \
advent3.scr advent4.scr advent5.scr advent6.scr advent7.scr example.ifm	    \
cover.ifm tkifm.txt macros.tex

dist-doc: $(EXTRA_DIST)
	if test -d $(srcdir)/ifm; then					\
	   cp -rf $(srcdir)/ifm $(distdir);				\
	fi
	if test -f $(srcdir)/ifm.pdf; then				\
	   cp -r $(srcdir)/ifm.pdf $(distdir);				\
	fi

# Cleaning stuff.

CLEAN_DOC = *.ps *.eps *.pdf
CLEAN_TEX = ifm.tex *.aux *.dvi *.lof *.lot *.log *.toc *.out

clean-doc: realclean

realclean: htmlclean
	rm -rf $(CLEAN_DOC)

htmlclean:; rm -rf ifm $(CLEAN_TEX)

# Other stuff.

test:; opera `pwd`/ifm/index.htm

distclean-local: clean-doc

install-data-hook: install-doc

uninstall-hook:
	- chmod -R u+w $(ifmdocdir)
	rm -rf $(ifmdocdir)

dist-hook: dist-doc

edit:; lyx ifm.lyx

include $(top_srcdir)/etc/Makefile.common
