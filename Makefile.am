## Automake template for ifm.

AUTOMAKE_OPTIONS	= foreign
SUBDIRS			= @BUILD@
DIST_SUBDIRS		= lib src doc tests scr2ifm tkifm
EXTRA_DIST		= README.src README.win32 README.maps README.lib

dist-hook:;		cp -rp config contrib $(distdir)

## Stuff for Win32 distribution.

ZIPDIR			= ../ifm
CYGDLL			= /bin/cygwin.dll

IFM			= src/ifm.exe src/ifm-pro.ps doc/ifm.txt doc/ifm.ps \
			  doc/ifm.html $(CYGDLL)

SCR2IFM			= scr2ifm/scr2ifm.pl scr2ifm/scr2ifm.txt \
			  scr2ifm/scr2ifm.ps scr2ifm/scr2ifm.html

TKIFM			= tkifm/tkifm.tcl tkifm/tkifm.txt tkifm/tkifm.ps \
			  tkifm/tkifm.html

DOCS			= README README.win32 README.maps NEWS COPYING

ZIPFILES		= $(IFM) $(SCR2IFM) $(TKIFM) $(DOCS)

zip:;			$(MAKE) all
			rm -rf $(ZIPDIR)
			mkdir $(ZIPDIR)
			cp $(ZIPFILES) $(ZIPDIR)
			for i in README NEWS COPYING; do \
				mv $(ZIPDIR)/$$i $(ZIPDIR)/$$i.txt; \
			done
			mv $(ZIPDIR)/README.win32 $(ZIPDIR)/WIN32.txt
			mv $(ZIPDIR)/README.maps $(ZIPDIR)/MAPS.txt
			strip $(ZIPDIR)/ifm.exe
			chmod +w $(ZIPDIR)/*
