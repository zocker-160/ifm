## Automake template for ifm documentation.

infodir = $(prefix)/info

info_DATA = ifm.info

EXTRA_DIST = ifm.pod ifm.info ifm.txt ifm.doc ifm.1 ifm.html ifm.key

all: ifm.info

@common_rules@

ifm.info: ifm.key

CLEANFILES = *cache
