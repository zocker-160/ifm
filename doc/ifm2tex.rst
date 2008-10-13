.. _ifm2tex:

``ifm2tex``: convert IFM maps to LaTeX
======================================

``ifm2tex`` is a program for creating a summary file in LaTeX format,
suitable for converting to PostScript and printing. It uses ``ifm2dev`` to
create the maps. The command format is::

    ifm2tex [-m] [-i] [-t] [-- ifm-options] file

The options indicate which combinations of things you want output (maps,
items or tasks). Several files are written, whose names depend on the
prefix of the input file (i.e., minus its ``.ifm`` suffix):

``prefix.tex``
       The main LaTeX input file, which includes all the others.

``prefix-maps.tex``
       The maps, which include the EPS figures.

``prefix-items.tex``
       The table of items.

``prefix-tasks.tex``
       The table of tasks.

``prefix-map-N.eps``
       An EPS figure for each map section.

At the moment, the program is very basic and doesn't have any options to
control anything. But you can sort of customize things by using your own
main LaTeX file and doing your own including of the other files.
