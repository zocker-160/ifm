## Automake template for ifm documentation.

infodir		= $(prefix)/info
info_DATA	= ifm.info

EXTRA_DIST	= ifm.pod ifm.info ifm.txt ifm.1

all:		Makefile

PMFLAGS		= -r "Version $(VERSION)" -c "Unix Programmer's Guide"

pod:;		podpp -o ifm.pod ifm-doc.pod

ifm.1:		ifm.pod
		pod2man $(PMFLAGS) $< > $@

ifm.txt:	ifm.1
		gnroff -man.nopage $< > $@

ifm.info:	ifm.pod
		pod2inf -w $< | infoize -d25 -v -i ifm -o $@

ifm.ps:		ifm.1
		groff -man $< > $@

install-man:	ifm.1
		cp $< $(mandir)/man1

install-cat:	ifm.txt
		rm -f $(mandir)/cat1/ifm.z
		cp $< $(mandir)/cat1/ifm
		pack -f $(mandir)/cat1/ifm
