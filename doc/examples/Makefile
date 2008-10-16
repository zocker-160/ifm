# Makefile for ruins demo.

all: ruins.scr

ruins.scr: ruins.z5 ruins.rec
	rec2scr -o $@ -r ruins.rec ruins.z5

ruins.rec: ruins.ifm
	ifm -t -f rec -o $@ $<
