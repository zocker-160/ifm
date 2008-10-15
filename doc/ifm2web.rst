.. _ifm2web:

====================================================
 :program:`ifm2web` -- convert IFM map to Web image
====================================================

:program:`ifm2web` converts an IFM map to an image file suitable for
display on the Interweb (i.e., with transparency).  It does this by
running a pipeline from IFM through :program:`fig2dev` and
:program:`convert`, both of which must be present on the system.

These are the command-line options:

.. cmdoption:: -o file

   Write to the specified file.  If not given, the filename is built from
   the input file prefix and the image format.

.. cmdoption:: -f format

   Set the image format.  Default: ``png``.

.. cmdoption:: -m map-spec

   Only process the maps specified.  Format is the same as the IFM ``-m``
   option (see :ref:`usage`).

.. cmdoption:: -t

   Include map section titles.

.. cmdoption:: -S style

   Use the specified IFM style.

.. cmdoption:: -z zoom

   Set the :program:`fig2dev` magnification (zoom) factor.  Default: 1.

.. cmdoption:: -s scale

   Set the :program:`convert` scale factor, as a percentage.  Default: 100.

.. cmdoption:: -n

   Don't actually run anything; just print what would be done.

.. cmdoption:: -h

   Print a short usage message and exit.
