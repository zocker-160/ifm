## Automake template for ifm.

AUTOMAKE_OPTIONS	= foreign
SUBDIRS			= @BUILD@
DIST_SUBDIRS		= vars src lib doc tests scr2ifm tkifm
EXTRA_DIST		= README.src README.win32 README.maps

dist-hook:;		cp -rp $(srcdir)/config $(srcdir)/contrib $(distdir)

## Stuff for Win32 distribution.

ZIPDIR			= ../ifm

EXE			= src/ifm.exe

FILES			= README README.win32 README.maps NEWS COPYING

PROGS			= $(EXE) tkifm/tkifm.tcl scr2ifm/scr2ifm.pl

DLLS			= /bin/cygwin.dll

DOCS			= doc/ifm.txt doc/ifm.html tkifm/tkifm.txt \
			  tkifm/tkifm.html scr2ifm/scr2ifm.txt \
			  scr2ifm/scr2ifm.html 

LIBS			= lib/ifm-pro.ps lib/ifm-rgb.txt

ZIPFILES		= $(IFM) $(LIB) $(SCR2IFM) $(TKIFM) $(DOCS) $(CYGDLL)

zip:;			$(MAKE) all zipdir

ziptest:;		$(MAKE) ZIPDIR=zip EXE="" DLLS="" zipdir

zipdir:;		rm -rf $(ZIPDIR)
			mkdir $(ZIPDIR)
			cp $(FILES) $(ZIPDIR)
			for i in README NEWS COPYING; do \
				mv $(ZIPDIR)/$$i $(ZIPDIR)/$$i.txt; \
			done
			mv $(ZIPDIR)/README.win32 $(ZIPDIR)/WIN32.txt
			mv $(ZIPDIR)/README.maps $(ZIPDIR)/MAPS.txt
			mkdir $(ZIPDIR)/progs
			cp $(PROGS) $(DLLS) $(ZIPDIR)/progs
			if test "$(EXE)" != ""; then \
				strip $(ZIPDIR)/progs/$(EXE); \
			fi
			mkdir $(ZIPDIR)/docs
			cp $(DOCS) $(ZIPDIR)/docs
			mkdir $(ZIPDIR)/lib
			cp $(LIBS) $(ZIPDIR)/lib
			chmod -R +w $(ZIPDIR)
