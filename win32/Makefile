# Makefile for building Win32 distribution.

TOPDIR = ..
SRCDIR = $(TOPDIR)/src
LIBDIR = $(TOPDIR)/lib
DOCDIR = $(TOPDIR)/doc
MAPDIR = $(TOPDIR)/maps
PROGDIR = $(TOPDIR)/progs

ZIPDIR = ifm

EXE = ifm.exe

DLL = $(bindir)/cygwin1.dll

FILES = $(TOPDIR)/README $(TOPDIR)/README.maps $(TOPDIR)/NEWS	\
$(TOPDIR)/COPYING

PROGS = $(SRCDIR)/$(EXE) $(PROGDIR)/tkifm.tcl $(PROGDIR)/scr2ifm.pl

DOCS = $(DOCDIR)/ifm.pdf $(DOCDIR)/html

LIBS = $(LIBDIR)/*.ifm $(LIBDIR)/ifm-pro.ps $(LIBDIR)/ifm-rgb.txt

MAPS = $(MAPDIR)/*.ifm $(MAPDIR)/README

all: test

test:; $(MAKE) EXE=ifm DLL="" zip

zip:;	rm -rf $(ZIPDIR)
	mkdir $(ZIPDIR)
	cp $(FILES) $(ZIPDIR)
	for i in README NEWS COPYING; do				\
	   mv $(ZIPDIR)/$$i $(ZIPDIR)/$$i.txt;				\
	done
	mv README.win32 $(ZIPDIR)/WIN32.txt
	mv $(ZIPDIR)/README.maps $(ZIPDIR)/MAPS.txt
	mkdir $(ZIPDIR)/progs
	cp $(PROGS) $(DLL) $(ZIPDIR)/progs
	strip $(ZIPDIR)/progs/$(EXE)
	mkdir $(ZIPDIR)/docs
	cp -r $(DOCS) $(ZIPDIR)/docs
	mkdir $(ZIPDIR)/lib
	cp $(LIBS) $(ZIPDIR)/lib
	mkdir $(ZIPDIR)/maps
	cp $(MAPS) $(ZIPDIR)/maps
	mv $(ZIPDIR)/maps/README $(ZIPDIR)/maps/README.txt
	chmod -R +w $(ZIPDIR)

clean:; rm -rf $(ZIPDIR)
