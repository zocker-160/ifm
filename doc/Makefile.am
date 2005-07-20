## Automake template for IFM documentation.

docdir = $(prefix)/doc
ifmdocdir = $(docdir)/ifm

PDF_TITLE  = IFM Version $(VERSION)
PDF_AUTHOR = Glenn Hutchings

MAN_TITLE = Interactive Fiction Mapper

man_MANS = ifm.1

# Programs.

IFM      = $(top_srcdir)/src/ifm -s version="$(VERSION)"
IFMCMD   = $(IFM) -I $(top_srcdir)/lib
HELP2MAN = help2man -N -n "$(MAN_TITLE)"

# Main targets.

doc: fig pdf html man

pdf: ifm.pdf

rtf: ifm.rtf

fig: cover.eps example.eps advent.eps

man: ifm.1

ifm.1: ifm.man
	cp ifm.man ifm.tmp
	echo "[SEE ALSO]" >> ifm.tmp
	echo ".IP $(ifmdocdir)/html" >> ifm.tmp
	echo "Online documentation" >> ifm.tmp
	echo ".IP $(ifmdocdir)/ifm.pdf" >> ifm.tmp
	echo "Documentation suitable for printing" >> ifm.tmp
	$(HELP2MAN) -o ifm.1 -i ifm.tmp $(IFM)
	rm -f ifm.tmp

mantest: man
	groff -man -Tps ifm.1 > ifm.ps
	gv -a4 -scale -1 -spartan ifm.ps
	rm -f ifm.ps

# General rules.

SUFFIXES = .lyx .ps .tex .aux .pdf .eps .fig .ifm .png .tex .rtf

.lyx.ps:;	lyx --export ps $< > $@
.lyx.tex:;	lyx --export latex $< > $@
.lyx.pdf:;	tex2pdf -t "$(PDF_TITLE)" -a "$(PDF_AUTHOR)" $<
.lyx.rtf:;	lyx2rtf -d2 $<
.ps.gv:;	gv -a4 -scale -1 -spartan $<
.tex.aux:;	latex $<; latex $<; latex $<
.ifm.fig:;	$(IFMCMD) -m -f fig -o $@ $<
.fig.eps:;	fig2dev -L eps $< > $@
.fig.png:;	fig2dev -L png $< > $@
.fig.tex:;	fig2dev -L latex $< > $@

html: fig ifm.lyx
	lyx2html -title IFM ifm.lyx

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

EXTRA_DIST = ifm.1 ifm.man ifm.lyx gfdl.lyx advent.cmd advent.ifm	\
advent1.scr advent2.scr advent3.scr advent4.scr advent5.scr advent6.scr	\
advent7.scr example.ifm cover.ifm tkifm.txt macros.tex

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
