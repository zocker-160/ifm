# Automake template for IFM tests.

TESTS_ENVIRONMENT = SRCDIR=$(top_srcdir) BUILDDIR=$(top_builddir)

SRCS = map-exit.ifm map-join1.ifm map-join2.ifm map-link1.ifm map-link2.ifm \
map-nolink.ifm task-attr1.ifm task-attr2.ifm task-attr3.ifm		    \
task-before1.ifm task-before2.ifm task-cmd.ifm task-do1.ifm task-do2.ifm    \
task-drop1.ifm task-drop2.ifm task-drop3.ifm task-drop4.ifm task-finish.ifm \
task-follow1.ifm task-follow2.ifm task-follow3.ifm task-give1.ifm	    \
task-give2.ifm task-keep1.ifm task-keep2.ifm task-nocmd.ifm task-leave1.ifm \
task-leave2.ifm task-lose.ifm task-nolink.ifm task-nopath.ifm task-note.ifm \
task-path.ifm task-simple.ifm task-unsafe.ifm

IFM		= $(top_srcdir)/src/ifm -I$(top_srcdir)/lib

TKIFM		= wish -f $(top_srcdir)/progs/tkifm.tcl

TESTS		= $(SRCS:.ifm=.test)

EXP		= $(SRCS:.ifm=.exp)

EXTRA_DIST	= README $(TESTS) $(EXP)

SUFFIXES	= .ifm .test .task .prof .tk .ps .rec

.ifm.prof:;	time $(IFM) -tasks $<

.ifm.task:;	$(IFM) -tasks -debug $<

.ifm.tk:;	$(TKIFM) $<

.ifm.ps:;	$(IFM) -map -format ps $< > $@

.ifm.rec:;	$(IFM) -tasks -format rec $< > $@

tests:		$(SRCS)
		perl Maketests "$(IFM)" $(SRCS)

CLEANFILES	= *.out

include $(top_srcdir)/etc/Makefile.common
