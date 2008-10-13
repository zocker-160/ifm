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

PROGS = $(PROGDIR)/*.pl
DOCS  = $(DOCDIR)/html
LIBS  = $(LIBDIR)/*.ifm $(LIBDIR)/ifm-pro.ps $(LIBDIR)/ifm-rgb.txt
MAPS  = $(MAPDIR)/*.ifm $(MAPDIR)/README

CTEXT = $(PROGDIR)/ctext/ctext.tcl
TKIFM = $(PROGDIR)/tkifm.tcl

all: test

test:; $(MAKE) IFM=ifm DLL="" zip

zip: init readme progs docs lib demos final

init:;	rm -rf $(ZIPDIR)
	mkdir $(ZIPDIR)

readme:
	echo See docs/index.html for IFM documentation > $(ZIPDIR)/README.txt

progs:; cp $(SRCDIR)/$(IFM) $(DLL) $(ZIPDIR)
	strip $(ZIPDIR)/$(IFM)
	- mkdir $(ZIPDIR)/progs
	cp $(PROGS) $(ZIPDIR)/progs
	cat $(CTEXT) $(TKIFM) > $(ZIPDIR)/progs/tkifm.tcl

docs:;	- mkdir $(ZIPDIR)/docs
	- cp -r $(DOCS)/* $(ZIPDIR)/docs

lib:;	cp $(LIBS) $(ZIPDIR)

demos:;	- mkdir $(ZIPDIR)/demos
	cp $(MAPS) $(ZIPDIR)/demos
	- mv $(ZIPDIR)/demos/README $(ZIPDIR)/demos/README.txt

final:;	chmod -R a+w $(ZIPDIR)

clean:; rm -rf $(ZIPDIR)

include ../etc/Makefile.common
