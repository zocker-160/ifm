## Automake template for IFM demo maps.

EXTRA_DIST = example.ifm ruins.ifm

IFM = $(top_srcdir)/src/ifm -I $(top_srcdir)/lib -S helvetica

SET = -s task_graph_rooms=1

ps fig: maptest.ifm
	$(IFM) -f $@ -m -o maptest.$@ $<

dot: ruins.ifm
	$(IFM) $(SET) -f dot -t -o ruins.dot $<
	dot -Tps ruins.dot > ruins.ps

CLEANFILES = *.ps *.fig *.dot
