## Automake template for IFM.

AUTOMAKE_OPTIONS = foreign check-news

SUBDIRS = vars fig src lib doc maps progs tests

EXTRA_DIST = README.unix README.maps

EXTRA_DIRS = etc contrib win32

dist-hook: dist-prepare dist-extra dist-config dist-header dist-touch \
	   dist-cleanup

dist-prepare:
	cd $(top_srcdir)/win32; $(MAKE) clean

dist-config:
	rm -f $(distdir)/etc/*header*

dist-extra:
	for dir in $(EXTRA_DIRS); do					\
	   cp -rp $(top_srcdir)/$$dir $(distdir);			\
	   rm -rf $(distdir)/$$dir/CVS;					\
	   rm -f $(distdir)/$$dir/.cvsignore;				\
	done

dist-header:
	addheader=$(top_srcdir)/etc/add-header;				\
	for dir in src lib progs; do					\
	   if test -f $$addheader; then					\
	      $$addheader $(top_srcdir)/etc $(distdir)/$$dir;		\
	   fi; \
	done

dist-touch:
	for file in src/ifm-scan.c src/ifm-parse.c src/ifm-parse.h; do	\
	   touch $(distdir)/$$file;					\
	done

dist-cleanup:
	rm -f $(distdir)/etc/config.h
	rm -f $(distdir)/etc/stamp-h
