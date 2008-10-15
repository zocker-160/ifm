# Makefile for example images.

EXAMPLES = ../examples

IFM = $(wildcard ${EXAMPLES}/*.ifm)
TMP = $(subst ${EXAMPLES}/,,${IFM})
PNG = $(subst .ifm,.png,${TMP})

IFM2WEB = perl ../../progs/ifm2web.pl -S helvetica

LARGE = $(IFM2WEB) -z 3 -s 40
SMALL = $(IFM2WEB) -z 3 -s 15

all: $(PNG)

%.png: $(EXAMPLES)/%.ifm Makefile
	$(LARGE) -o $@ $<

logo.png: $(EXAMPLES)/logo.ifm Makefile
	$(SMALL) -o $@ $<
