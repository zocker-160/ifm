## Automake template for fig library.

noinst_LIBRARIES = libfig.a

SRCS = fig-attr.c fig-file.c fig-object.c

HDRS = fig-attr.h fig-file.h fig-object.h fig.h

libfig_a_SOURCES = $(SRCS) $(HDRS)

EXTRA_PROGRAMS = testfig

testfig_SOURCES = testfig.c
testfig_LDADD = libfig.a $(top_srcdir)/vars/src/libvars.a -lm

test: testfig
	./testfig | tee test.fig

CLEANFILES = test.fig testfig
