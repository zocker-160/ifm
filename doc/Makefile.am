## Automake template for IFM documentation.

SRCS = ifm-top.pod ifm-desc.pod ifm-oper.pod ifm-map.pod ifm-task.pod	\
ifm-out.pod ifm-lang.pod ifm-diag.pod ifm-bot.pod

infodir = $(prefix)/info

info_DATA = ifm.info

EXTRA_DIST = ifm.info ifm.txt ifm.doc ifm.1 ifm.html

all: ifm.info

@common_rules@

doc: $(SRCS)
	@ rm -f ifm.pod
	@ for i in $(SRCS); do \
		echo Adding $$i; \
		echo >> ifm.pod; \
		$(CONFIG) $$i | podpp >> ifm.pod; \
	done

ETAGS_ARGS = -l none -r '/^=head.[ \t]+\(.+\)/\1/' $(SRCS)

TAGS_DEPENDENCIES = $(SRCS)

CLEANFILES = *cache
