## Automake template for IFM extra programs.

bin_SCRIPTS = @tkifm@ @ifm2dev@ @ifm2tex@ @scr2ifm@

EXTRA_SCRIPTS = tkifm ifm2dev ifm2tex scr2ifm

EXTRA_DIST = tkifm.tcl ifm2dev.pl ifm2tex.pl scr2ifm.pl

tkifm: tkifm.tcl
	echo '#! $(WISH) -f' > $@
	cat $< >> $@
	chmod +x $@

scr2ifm: scr2ifm.pl
	echo '#! $(PERL)' > $@
	cat $< >> $@
	chmod +x $@

ifm2dev: ifm2dev.pl
	echo '#! $(PERL)' > $@
	cat $< >> $@
	chmod +x $@

ifm2tex: ifm2tex.pl
	echo '#! $(PERL)' > $@
	cat $< >> $@
	chmod +x $@

CLEANFILES = $(bin_SCRIPTS) *.tex *.aux *.dvi *.lo* *.eps *.ps *.toc

test:;	perl ifm2tex.pl -m test.ifm
	for i in 1 2 3; do latex test.tex; done
	dvips -o test.ps test.dvi
	gv test.ps

include $(top_srcdir)/etc/Makefile.common
