## Automake template for fig library.

noinst_LIBRARIES = libfig.a

SRCS = fig-attr.c fig-file.c fig-object.c fig-util.c

HDRS = fig-attr.h fig-file.h fig-object.h fig-util.h fig.h

libfig_a_SOURCES = $(SRCS) $(HDRS)

EXTRA_DIST = fig-format.txt

EXTRA_PROGRAMS = testfig

VARS = $(top_srcdir)/vars/src

INCLUDES = -I$(VARS)

testfig_SOURCES = testfig.c
testfig_LDFLAGS = -L$(VARS)
testfig_LDADD = libfig.a -lvars -lm

test: testfig
	./testfig | tee test.fig

CLEANFILES = test.fig* testfig
