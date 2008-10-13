## Automake template for IFM man page.

HELP2MAN = $(OPTIONAL) help2man -N -n "$(MAN_TITLE)"
OPTIONAL = $(top_srcdir)/etc/missing --run

MAN_TITLE = Interactive Fiction Mapper

man_MANS = ifm.1

manpage: ifm.1

ifm.1: ifm.man
	cp ifm.man ifm.tmp
	echo "[SEE ALSO]" >> ifm.tmp
	echo ".IP $(ifmdocdir)/index.html" >> ifm.tmp
	echo "Online documentation" >> ifm.tmp
	$(HELP2MAN) -o ifm.1 -i ifm.tmp $(IFM)
	rm -f ifm.tmp

mantest: ifm.1
	groff -man -Tps ifm.1 > ifm.ps
	gv -a4 -scale -1 -spartan ifm.ps
	rm -f ifm.ps

include $(top_srcdir)/etc/Makefile.common
