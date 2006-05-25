# Makefile for building Win32 distribution.

TOPDIR = ..
SRCDIR = $(TOPDIR)/src
LIBDIR = $(TOPDIR)/lib
DOCDIR = $(TOPDIR)/doc
MAPDIR = $(TOPDIR)/demos
PROGDIR = $(TOPDIR)/progs

ZIPDIR = ifm

IFM = ifm.exe
DLL = /bin/cygwin1.dll

FILES = $(TOPDIR)/README $(TOPDIR)/NEWS $(TOPDIR)/COPYING
PROGS = $(PROGDIR)/*.pl
DOCS  = $(DOCDIR)/ifm.pdf $(DOCDIR)/ifm
LIBS  = $(LIBDIR)/*.ifm $(LIBDIR)/ifm-pro.ps $(LIBDIR)/ifm-rgb.txt
MAPS  = $(MAPDIR)/*.ifm $(MAPDIR)/README

CTEXT = $(PROGDIR)/ctext/ctext.tcl
TKIFM = $(PROGDIR)/tkifm.tcl

all: test

test:; $(MAKE) IFM=ifm DLL="" zip

zip: init files progs docs lib demos final

init:;	rm -rf $(ZIPDIR)
	mkdir $(ZIPDIR)

files:;	cp $(FILES) $(ZIPDIR)
	- for i in README NEWS COPYING; do				\
	   mv $(ZIPDIR)/$$i $(ZIPDIR)/$$i.txt;				\
	done
	cp README.win32 $(ZIPDIR)/WIN32.txt

progs:; cp $(SRCDIR)/$(IFM) $(DLL) $(ZIPDIR)
	strip $(ZIPDIR)/$(IFM)
	- mkdir $(ZIPDIR)/progs
	cp $(PROGS) $(ZIPDIR)/progs
	cat $(CTEXT) $(TKIFM) > $(ZIPDIR)/progs/tkifm.tcl

docs:;	- mkdir $(ZIPDIR)/docs
	- cp -r $(DOCS) $(ZIPDIR)/docs

lib:;	cp $(LIBS) $(ZIPDIR)

demos:;	- mkdir $(ZIPDIR)/demos
	cp $(MAPS) $(ZIPDIR)/demos
	- mv $(ZIPDIR)/demos/README $(ZIPDIR)/demos/README.txt

final:;	chmod -R a+w $(ZIPDIR)

clean:; rm -rf $(ZIPDIR)

include ../etc/Makefile.common
