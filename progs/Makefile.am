## Automake template for IFM extra programs.

bin_SCRIPTS = @tkifm@ @ifm2dev@ @scr2ifm@

EXTRA_SCRIPTS = tkifm ifm2dev scr2ifm

EXTRA_DIST = tkifm.tcl scr2ifm.pl

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

CLEANFILES = $(bin_SCRIPTS)

test:; perl ifm2dev.pl -L png -v lgop.ifm
