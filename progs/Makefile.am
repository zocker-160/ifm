## Automake template for IFM extra programs.

bin_SCRIPTS = @tkifm@ @scr2ifm@

EXTRA_SCRIPTS = tkifm scr2ifm

infodir = $(prefix)/info

info_DATA = tkifm.info scr2ifm.info

EXTRA_DIST = tkifm.tcl tkifm.txt tkifm.html tkifm.info scr2ifm.pl	\
scr2ifm.txt scr2ifm.html scr2ifm.info

#ETAGS_ARGS = scr2ifm.pl
#ETAGS_ARGS = -l none -r '/proc[ \t]+\([^ \t]+\)/\1/' tkifm.tcl

#TAGS_DEPENDENCIES = tkifm.tcl scr2ifm.pl

tkifm: tkifm.tcl
	echo '#! $(WISH) -f' > $@
	cat $< >> $@
	chmod +x $@

scr2ifm: scr2ifm.pl
	echo '#! $(PERL)' > $@
	cat $< >> $@
	chmod +x $@

CLEANFILES = tkifm scr2ifm

@common_rules@
