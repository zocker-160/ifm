# Makefile for building Win32 distribution.

bindir = /bin

TOPDIR = ..
SRCDIR = $(TOPDIR)/src
LIBDIR = $(TOPDIR)/lib
DOCDIR = $(TOPDIR)/doc
GPPDIR = $(TOPDIR)/gpp
MAPDIR = $(TOPDIR)/demos
PROGDIR = $(TOPDIR)/progs

ZIPDIR = ifm

IFM = ifm.exe
GPP = gpp.exe
DLL = $(bindir)/cygwin1.dll

FILES = $(TOPDIR)/README $(TOPDIR)/NEWS $(TOPDIR)/COPYING
PROGS = $(SRCDIR)/$(IFM) $(GPPDIR)/$(GPP) $(PROGDIR)/*.pl
DOCS  = $(DOCDIR)/ifm.pdf $(DOCDIR)/ifm
LIBS  = $(LIBDIR)/*.ifm $(LIBDIR)/ifm-pro.ps $(LIBDIR)/ifm-rgb.txt
MAPS  = $(MAPDIR)/*.ifm $(MAPDIR)/README

CTEXT = $(PROGDIR)/ctext/ctext.tcl
TKIFM = $(PROGDIR)/tkifm.tcl

all: test

test:; $(MAKE) IFM=ifm GPP=gpp DLL="" zip

zip: init files progs tkifm docs lib demos final

init:;	rm -rf $(ZIPDIR)
	mkdir $(ZIPDIR)

files:;	cp $(FILES) $(ZIPDIR)
	- for i in README NEWS COPYING; do				\
	   mv $(ZIPDIR)/$$i $(ZIPDIR)/$$i.txt;				\
	done
	cp README.win32 $(ZIPDIR)/WIN32.txt

progs:; cp $(PROGS) $(DLL) $(ZIPDIR)
	strip $(ZIPDIR)/$(IFM)
	strip $(ZIPDIR)/$(GPP)

tkifm:; cat $(CTEXT) $(TKIFM) > $(ZIPDIR)/tkifm.tcl

docs:;	- mkdir $(ZIPDIR)/docs
	- cp -r $(DOCS) $(ZIPDIR)/docs

lib:;	cp $(LIBS) $(ZIPDIR)

demos:;	- mkdir $(ZIPDIR)/demos
	cp $(MAPS) $(ZIPDIR)/demos
	- mv $(ZIPDIR)/demos/README $(ZIPDIR)/demos/README.txt

final:;	chmod -R a+w $(ZIPDIR)

clean:; rm -rf $(ZIPDIR)

include ../etc/Makefile.common
