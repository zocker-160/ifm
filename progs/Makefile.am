## Automake template for IFM extra programs.

bin_SCRIPTS = @tkifm@ @scr2ifm@

EXTRA_SCRIPTS = tkifm scr2ifm

EXTRA_DIST = tkifm.tcl scr2ifm.pl

tkifm: tkifm.tcl
	echo '#! $(WISH) -f' > $@
	cat $< >> $@
	chmod +x $@

scr2ifm: scr2ifm.pl
	echo '#! $(PERL)' > $@
	cat $< >> $@
	chmod +x $@

CLEANFILES = tkifm scr2ifm
