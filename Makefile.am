## Automake template for IFM.

AUTOMAKE_OPTIONS = foreign

SUBDIRS = @BUILD@

DIST_SUBDIRS = vars src lib doc tests tkifm scr2ifm

EXTRA_DIST = README.unix README.win32 README.maps

dist-hook: dist-config dist-contrib dist-header dist-cleanup

dist-config:
	cp -rp $(srcdir)/config $(distdir)
	rm -rf $(distdir)/config/RCS
	rm -f $(distdir)/config/config.h
	rm -f $(distdir)/config/stamp-h
	rm -f $(distdir)/config/*header*

dist-contrib:
	cp -rp $(srcdir)/contrib $(distdir)

dist-header:
	for dir in src lib tkifm scr2ifm; do \
	   $(srcdir)/config/add-header $(srcdir)/config $(distdir)/$$dir; \
	done

dist-cleanup:
	find $(distdir) -name ChangeLog -exec rm {} \;

## Stuff for Win32 distribution.
.PHONY: ziptest

ZIPDIR = ../ifm

EXE = ifm.exe

FILES = README README.win32 README.maps NEWS COPYING

PROGS = src/$(EXE) tkifm/tkifm.tcl scr2ifm/scr2ifm.pl

DLL = $(bindir)/cygwin1.dll

DOCS = doc/ifm.txt doc/ifm.html tkifm/tkifm.txt tkifm/tkifm.html	\
scr2ifm/scr2ifm.txt scr2ifm/scr2ifm.html

LIBS = lib/*.ifm lib/ifm-pro.ps lib/ifm-rgb.txt

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
	cp $(DOCS) $(ZIPDIR)/docs
	mkdir $(ZIPDIR)/lib
	cp $(LIBS) $(ZIPDIR)/lib
	chmod -R +w $(ZIPDIR)
