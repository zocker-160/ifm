## Automake template for IFM.

AUTOMAKE_OPTIONS = check-news

ACLOCAL_AMFLAGS = -I etc

SUBDIRS = fig src lib doc progs demos tests

EXTRA_DIST = ANNOUNCE

EXTRA_DIRS = etc contrib win32

dist-hook: dist-prepare dist-extra dist-config dist-header dist-touch \
	   dist-cleanup

dist-prepare:
	cd $(top_srcdir)/win32; $(MAKE) clean

dist-config:
	rm -f $(distdir)/etc/*header*

dist-extra:
	for dir in $(EXTRA_DIRS); do					\
	   cp -frp $(top_srcdir)/$$dir $(distdir);			\
	done

dist-header:
	addheader=$(top_srcdir)/etc/add-header;				\
	for dir in src lib progs; do					\
	   if test -f $$addheader; then					\
	      $$addheader $(top_srcdir)/etc $(distdir)/$$dir;		\
	   fi;								\
	done

dist-touch:
	for file in src/ifm-scan.c src/ifm-parse.c src/ifm-parse.h; do	\
	   touch $(distdir)/$$file;					\
	done

dist-cleanup:
	find $(distdir) -type d -name CVS | xargs rm -rf
	find $(distdir) -type f -name '*~' | xargs rm -f
	find $(distdir) -type f -name .cvsignore | xargs rm -f
	rm -f $(distdir)/etc/config.h
	rm -f $(distdir)/etc/stamp-h*

include $(top_srcdir)/etc/Makefile.common
