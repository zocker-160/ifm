## Automake template for IFM documentation.

# Main target.

doc: fig ps html

pdf: ifm.pdf

ps: ifm.ps

fig: map.eps

# General rules.

SUFFIXES = .lyx .ps .tex .aux .pdf .eps .dia

.lyx.ps:;	lyx --export ps $< > $@
.lyx.tex:;	lyx --export latex $< > $@
.ps.gv:;	gv -a4 -magstep -1 -spartan $<
.tex.aux:;	latex $<; latex $<; latex $<
.lyx.pdf:;	tex2pdf $<
.dia.eps:;	dia -e $@ $<

# Stuff for generating HTML.

.PHONY: html

HTML_TITLE = IFM Version $(VERSION)

HTML_ADDRESS = zondo@pillock.freeserve.co.uk

HTML_DIR = ifm

HTML_SPLIT = 5

HTML_LINK = 5

HTML_DISP = -split $(HTML_SPLIT) -link $(HTML_LINK) -show_section_numbers \
-html_version 4.0

HTML_IMAGE = -no_external_images -local_icons -white -image_type gif

HTML_NAV = -next_page_in_navigation

HTML_TEXT = -title "$(HTML_TITLE)" -address "$(HTML_ADDRESS)" -font_size 12pt

HTML_FILE = -dir $(HTML_DIR) -mkdir 

LATEX2HTML = latex2html $(HTML_DISP) $(HTML_IMAGE) $(HTML_NAV) $(HTML_FILE) \
$(HTML_TEXT) $(HTML_LOCAL)

html: ifm.tex ifm.aux
	$(LATEX2HTML) ifm.tex

# Installation stuff.

DOC_DIR = $(pkgdatadir)

install-doc:
	@ if test -d $(srcdir)/$(HTML_DIR); then			\
	   thisdir=`pwd`;						\
	   docdir=`basename $$thisdir`;					\
	   $(mkinstalldirs) $(DOC_DIR);					\
	   cmd="rm -rf $(DOC_DIR)/$$docdir";				\
	   echo $$cmd;							\
	   eval $$cmd;							\
	   cmd="cp -r $(srcdir)/$(HTML_DIR) $(DOC_DIR)/$$docdir";	\
	   echo $$cmd;							\
	   eval $$cmd;							\
	fi

# Distribution stuff.

EXTRA_DIST = ifm.lyx map.dia map.eps

dist-doc: $(EXTRA_DIST)
	if test -d $(srcdir)/$(HTML_DIR); then				\
	   cp -r $(srcdir)/$(HTML_DIR) $(distdir);			\
	fi

# Cleaning stuff.

CLEAN_DOC = *.ps *.eps *.pdf
CLEAN_TEX = ifm.tex *.aux *.dvi *.lof *.lot *.log *.toc *.out

clean-doc: realclean

realclean: htmlclean
	rm -rf $(FILES)

htmlclean:; rm -rf $(HTML_DIR) $(CLEAN_TEX)

# Other stuff.

distclean-local: clean-doc

install-data-hook: install-doc

dist-hook: dist-doc

edit:; lyx ifm.lyx
