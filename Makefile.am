## Automake template for ifm.

AUTOMAKE_OPTIONS	= foreign
SUBDIRS			= @BUILD@
DIST_SUBDIRS		= vars src lib doc tests scr2ifm tkifm
EXTRA_DIST		= README.unix README.win32 README.maps

dist-hook:;		cp -rp $(srcdir)/config $(srcdir)/contrib $(distdir)
			rm -f $(distdir)/config/config.h
			rm -f $(distdir)/config/stamp-h

## Stuff for Win32 distribution.

.PHONY:			ziptest

ZIPDIR			= ../ifm

EXE			= ifm.exe

FILES			= README README.win32 README.maps NEWS COPYING

PROGS			= src/$(EXE) tkifm/tkifm.tcl scr2ifm/scr2ifm.pl

DLL			= $(bindir)/cygwin1.dll

DOCS			= doc/ifm.txt doc/ifm.html tkifm/tkifm.txt \
			  tkifm/tkifm.html scr2ifm/scr2ifm.txt \
			  scr2ifm/scr2ifm.html 

LIBS			= lib/*.ifm lib/ifm-pro.ps lib/ifm-rgb.txt

ZIPFILES		= $(IFM) $(LIB) $(SCR2IFM) $(TKIFM) $(DOCS) $(CYGDLL)

zip:;			$(MAKE) all zipdir

ziptest:;		$(MAKE) ZIPDIR=ziptest EXE=ifm DLL="" zipdir

zipdir:;		rm -rf $(ZIPDIR)
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
