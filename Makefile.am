## Automake template for ifm.

AUTOMAKE_OPTIONS	= foreign
SUBDIRS			= lib src doc tkifm tests
EXTRA_DIST		= README.src README.win32 README.maps README.lib

install-tkifm:;		cd tkifm; $(MAKE) $@

ZIPDIR			= ../ifm
CYGDLL			= /bin/cygwin.dll

ZIPFILES		= README README.win32 README.maps NEWS COPYING \
			  src/ifm.exe src/ifm-pro.ps doc/ifm.txt doc/ifm.ps \
			  doc/ifm.html $(CYGDLL) tkifm/tkifm.tcl \
			  tkifm/tkifm.txt tkifm/tkifm.ps tkifm/tkifm.html

dist-hook:;		cp -rp contrib $(distdir)

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
