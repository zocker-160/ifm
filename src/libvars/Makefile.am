## Automake template for Vars library.

SRCS = vars-buffer.c vars-config.c vars-copy.c vars-debug.c vars-destroy.c \
vars-freeze.c vars-getopt.c vars-graph.c vars-hash.c vars-iterate.c	   \
vars-list.c vars-memory.c vars-print.c vars-queue.c vars-scalar.c	   \
vars-system.c vars-traverse.c vars-type.c vars-utils.c vars-write.c

NOINST_SRCS = vars-freeze-lex.l

HDRS = vars-buffer.h vars-config.h vars-copy.h vars-debug.h vars-destroy.h \
vars-freeze.h vars-getopt.h vars-graph.h vars-hash.h vars-iterate.h	   \
vars-list.h vars-macros.h vars-memory.h vars-print.h vars-queue.h	   \
vars-scalar.h vars-system.h vars-traverse.h vars-type.h vars-utils.h	   \
vars-write.h vars.h

NOINST_HDRS = vars-freeze-lex.h

noinst_HEADERS = $(HDRS)
noinst_LIBRARIES = libvars.a

AM_CFLAGS = $(LOCAL_CFLAGS)

LEX_PREFIX = freeze
LEX_OUTPUT_ROOT = lex.$(LEX_PREFIX)
AM_LFLAGS = -CFa -8 -P$(LEX_PREFIX)
AM_YFLAGS = -v -d

VARS_SRCS = $(SRCS) $(NOINST_SRCS) $(HDRS) $(NOINST_HDRS) vars-config.h

libvars_a_SOURCES  = $(VARS_SRCS)
