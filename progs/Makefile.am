## Automake template for scr2ifm.

infodir = $(prefix)/info

info_DATA = scr2ifm.info

bin_SCRIPTS = scr2ifm

EXTRA_DIST = scr2ifm.pl scr2ifm.txt scr2ifm.html scr2ifm.info

ETAGS_ARGS = scr2ifm.pl

TAGS_DEPENDENCIES = scr2ifm.pl

all: scr2ifm

scr2ifm: scr2ifm.pl
	echo '#! $(PERL)' > $@
	cat $< >> $@
	chmod +x $@

CLEANFILES = scr2ifm

@common_rules@
