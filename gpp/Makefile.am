## Automake template for IFM preprocessor.

pkglib_PROGRAMS = gpp

gpp_SOURCES = gpp.c

EXTRA_DIST = gpphelp.pp

all-local: gpp.html

gpp.1: gpp gpphelp.pp
	./gpp -H -Dman $(srcdir)/gpphelp.pp -o gpp.1

gpp.html: gpp gpphelp.pp
	./gpp -H -Dhtml $(srcdir)/gpphelp.pp -o gpp.html

gpp.tex: gpp gpphelp.pp
	./gpp -H -Dlatex $(srcdir)/gpphelp.pp -o gpp.tex

CLEANFILES = gpp.1 gpp.html gpp.tex

include $(top_srcdir)/etc/Makefile.common
