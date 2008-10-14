============================
 Getting and installing IFM
============================

Installing on Linux
===================

See the file :file:`INSTALL` for installation details.  But it basically
boils down to::

    ./configure
    make
    su -c 'make install'

Installing on Windows
=====================

The Win32 version of IFM comes in a ZIP file, and is built using Cygnus
:program:`gcc`, which requires the library file :file:`CYGWIN1.DLL`
(included in the ZIP distribution).  This should be in your DLL search
path.  The subdirectories in the ZIP file are:

``progs``
    The programs, and DLL

``docs``
    Documentation in HTML format

``demos``
    Example maps

Setup
-----

When running, IFM looks for certain files that are contained in the current
directory (e.g., the :file:`ifm-pro.ps` file for PostScript).  IFM searches
for these files using a standard search path, which you can see by invoking
the :keyword:`-show path` option.  But you can change the search path by
setting the :envvar:`IFMPATH` environment variable.  It should be a
colon-separated list of directories to search.

IFM looks for an initialization file called :file:`ifm.ini` in your home
directory (the one pointed at by the :envvar:`HOME` environment variable).
If that exists, it is read.  You can set various defaults there.

Graphical interface
-------------------

IFM is *not* a graphical Windows program; you won't get any nice friendly
windowy menu-y stuff.  You must run it from the console.  However, there's
a very simple graphical interface to IFM included, called :ref:`tkifm
<tkifm>`.  To use it, you need to have `Tcl/Tk`_ installed (probably v8.0 or
greater).

.. _`Tcl/Tk`: ftp://ftp.sunlabs.com/pub/tcl

Assuming you have Tcl/Tk installed, you can arrange for :program:`tkifm` to
run when you double-click an IFM file.  Just create a new file type, with
suffix ``.ifm``, and set the Open command to be::

     <pathname of wish> -f <pathname of tkifm.tcl> "%1%"

If you want a nice window interface for making maps *and* a mouse-clicky
way of drawing them too, you might want to check out :ref:`IFMapper
<mapping-programs>` instead.

Alternatively, you can write a graphical front end which builds an IFM
source file automatically---but don't forget to send me a copy so I can
include it in the next IFM distribution. ``:-)``
