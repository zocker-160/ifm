## Automake template for IFM documentation.

docdir = $(prefix)/doc/ifm

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

# Stuff for generating PDF.

PDF_TITLE  = IFM Version $(VERSION)
PDF_AUTHOR = Glenn Hutchings

# Stuff for generating HTML.

.PHONY: html

HTML_TITLE = IFM Version $(VERSION)
HTML_ADDR  = zondo@pillock.freeserve.co.uk
HTML_DIR   = html
HTML_DISP  = -split 5 -link 5 -show_section_numbers -html_version 4.0
HTML_IMAGE = -no_external_images -local_icons -white -image_type png
HTML_NAV   = -next_page_in_navigation
HTML_TEXT  = -title "$(HTML_TITLE)" -address "$(HTML_ADDR)" -font_size 12pt
HTML_FILE  = -dir $(HTML_DIR) -mkdir 
HTML_EXTRA = -short_extn

LATEX2HTML = latex2html $(HTML_DISP) $(HTML_IMAGE) $(HTML_NAV) $(HTML_FILE) \
$(HTML_TEXT) $(HTML_EXTRA)

html: fig ifm.tex ifm.aux
	$(LATEX2HTML) ifm.tex

# Installation stuff.

install-doc: install-html install-pdf

install-html:
	@ if test -d $(srcdir)/$(HTML_DIR); then			\
	   set -x;							\
	   $(mkinstalldirs) $(docdir);					\
	   rm -rf $(docdir)/$(HTML_DIR);				\
	   cp -r $(srcdir)/$(HTML_DIR) $(docdir);			\
	fi

install-pdf:
	@ if test -f $(srcdir)/ifm.pdf; then				\
	   set -x;							\
	   $(mkinstalldirs) $(docdir);					\
	   $(INSTALL_DATA) $(srcdir)/ifm.pdf $(docdir);			\
	fi

# Distribution stuff.

EXTRA_DIST = ifm.lyx gfdl.lyx advent.cmd advent.ifm advent1.scr advent2.scr \
advent3.scr advent4.scr advent5.scr advent6.scr advent7.scr example.ifm	    \
cover.ifm tkifm.txt macros.tex

dist-doc: $(EXTRA_DIST)
	if test -d $(srcdir)/$(HTML_DIR); then				\
	   cp -r $(srcdir)/$(HTML_DIR) $(distdir);			\
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

htmlclean:; rm -rf $(HTML_DIR) $(CLEAN_TEX)

# Other stuff.

distclean-local: clean-doc

install-data-hook: install-doc

dist-hook: dist-doc

edit:; lyx ifm.lyx

include $(top_srcdir)/etc/Makefile.common
