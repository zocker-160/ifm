## Automake template for ifm documentation.

infodir		= $(prefix)/info
info_DATA	= ifm.info

EXTRA_DIST	= ifm.pod ifm.info ifm.txt ifm.doc ifm.1 ifm.ps ifm.html

TROFF		= groff -man
NROFF		= groff -Tascii -man.nopage

all:		Makefile

PMFLAGS		= -r "Version $(VERSION)" -c "IF Tools"

ifm.1:		ifm.pod
		pod2man $(PMFLAGS) $< > $@

ifm.doc:	ifm.1
		$(NROFF) $< > $@

ifm.txt:	ifm.1
		$(NROFF) -P-fbuo $< > $@

ifm.info:	ifm.pod
		pod2inf $< | infoize -d30 -v -i ifm -o $@

ifm.ps:		ifm.1
		$(TROFF) $< > $@

ifm.html:	ifm.pod
		pod2html $< > $@

install-man:	ifm.1
		cp $< $(mandir)/man1

install-cat:	ifm.doc
		rm -f $(mandir)/cat1/ifm.z
		cp $< $(mandir)/cat1/ifm
		pack -f $(mandir)/cat1/ifm

clean:;		rm -f *cache
