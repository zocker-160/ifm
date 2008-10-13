.. _ifm2dev:

``ifm2dev``: convert IFM maps to various other formats
======================================================

``ifm2dev`` is a front end to ``fig2dev``, which converts diagrams in Xfig
format to various other formats.  ``ifm2dev`` converts each map section and
writes them to separate files. The command format is::

    ifm2dev [-o template] [fig2dev-options] [-- ifm-options] file

The ``-o`` option sets the file template for the output files. It must
contain an integer format indicator (e.g., ``%d``); this is replaced with
the map section number in filenames. If not set, it defaults to
``prefix-%02d.suffix``, where ``prefix`` is the file prefix of the input
file (with ``.ifm`` removed), and suffix is the suffix appropriate for the
type of output.

All ``fig2dev`` output options are passed through without change. You can
use the ``-L`` option of ``fig2dev`` to set the output format. See the
``fig2dev`` manpage for details.

You can supply options to IFM by first giving the end-of-options indicator
(``--``) and then the options.
