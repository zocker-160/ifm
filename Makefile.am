## Automake template for IFM.

AUTOMAKE_OPTIONS = foreign check-news

SUBDIRS = vars src lib doc maps progs tests

EXTRA_DIST = README.unix README.win32 README.maps README.vars

dist-hook: dist-config dist-header dist-extra dist-touch dist-cleanup

dist-config:
	cp -rp $(top_srcdir)/etc $(distdir)
	rm -rf $(distdir)/etc/CVS
	rm -f $(distdir)/etc/*header*

dist-extra:
	cp -rp $(top_srcdir)/contrib $(distdir)
	rm -rf $(distdir)/contrib/CVS

dist-header:
	addheader=$(top_srcdir)/etc/add-header; \
	for dir in src lib progs; do \
	   if test -f $$addheader; then \
	      $$addheader $(top_srcdir)/etc $(distdir)/$$dir; \
	   fi; \
	done

dist-touch:
	for file in src/ifm-scan.c src/ifm-parse.c src/ifm-parse.h; do \
	   touch $(distdir)/$$file; \
	done

dist-cleanup:
	rm -f $(distdir)/etc/config.h
	rm -f $(distdir)/etc/stamp-h

## Stuff for Win32 distribution.
.PHONY: ziptest

ZIPDIR = ../ifm

EXE = ifm.exe

FILES = README README.win32 README.maps NEWS COPYING

PROGS = src/$(EXE) progs/tkifm.tcl progs/scr2ifm.pl

DLL = $(bindir)/cygwin1.dll

DOCS = progs/tkifm.txt progs/tkifm.html progs/scr2ifm.txt	\
progs/scr2ifm.html

LIBS = lib/*.ifm lib/ifm-pro.ps lib/ifm-rgb.txt

MAPS = maps/*.ifm maps/README

ZIPFILES = $(IFM) $(LIB) $(SCR2IFM) $(TKIFM) $(DOCS) $(CYGDLL)

zip:; $(MAKE) all zipdir

ziptest:; $(MAKE) ZIPDIR=ziptest EXE=ifm DLL="" zipdir

zipdir:
	rm -rf $(ZIPDIR)
	mkdir $(ZIPDIR)
	cp $(FILES) $(ZIPDIR)
	for i in README NEWS COPYING; do \
		mv $(ZIPDIR)/$$i $(ZIPDIR)/$$i.txt; \
	done
	mv $(ZIPDIR)/README.win32 $(ZIPDIR)/WIN32.txt
	mv $(ZIPDIR)/README.maps $(ZIPDIR)/MAPS.txt
	mkdir $(ZIPDIR)/progs
	cp $(PROGS) $(DLL) $(ZIPDIR)/progs
	strip $(ZIPDIR)/progs/$(EXE)
	mkdir $(ZIPDIR)/docs
	cp -r doc/html $(ZIPDIR)/docs
	cp $(DOCS) $(ZIPDIR)/docs
	mkdir $(ZIPDIR)/lib
	cp $(LIBS) $(ZIPDIR)/lib
	mkdir $(ZIPDIR)/maps
	cp $(MAPS) $(ZIPDIR)/maps
	mv $(ZIPDIR)/maps/README $(ZIPDIR)/maps/README.txt
	chmod -R +w $(ZIPDIR)
