.. _usage:

===========
 Using IFM
===========

Running the program
===================

IFM is run from the command line. The general form of the command is::

    ifm [options] [file...]

On startup, IFM does the following. Firstly, the system initialization file
is read. This sets defaults used by everyone. This file is called
:file:`ifm-init.ifm`, and is found by searching a standard set of
directories. You can prepend to this search path by setting the environment
variable :envvar:`IFMPATH` to be a colon-separated list of directories.

Then, if you have a personal initialization file, that is read. This file
is found in the directory specified by your :envvar:`HOME` environment
variable. On Unix-like systems it is called :file:`.ifmrc`, and on Win32
systems it is called :file:`ifm.ini`. You can use this file to customize
the default variable settings for different types of output.

Then input from the file(s) on the command-line is read. If no files were
specified, :keyword:`stdin` is read. A filename equal to :file:`-` also
indicates that :keyword:`stdin` should be read at that point.

If any of the :option:`-map`, :option:`-items`, :option:`-tasks` or
:option:`-show` options was specified, the appropriate output is
produced. If not, only a syntax check of the input is done.

When producing output, the output format specified by the :option:`-format`
option is used. If this was not specified, the first format in the list
which supports this type of output is chosen.

Some of the output formats use additional library files to do their
work. For example, the PostScript output format prepends a standard
"prologue" file to all output.  These files are found using the same search
path as the system initialization file (see above).

Here's a summary of the command-line options (which can be abbreviated),
starting with the output options:

.. cmdoption:: -m, --map [sections]

   Draw a map of the game. You can optionally specify a list of the map
   sections to print.  The list is a comma-separated set of map section
   numbers (starting from 1) and can include ranges. For example, the
   argument ``1,3-5`` would print map sections 1, 3, 4 and 5. If the list
   isn't specified, all sections are printed.

.. cmdoption:: -i, --items

   Print a list of items which appear in the game.

.. cmdoption:: -t, --tasks

   Print a list of tasks required to solve the game.

.. cmdoption:: -f, --format=FORMAT

   Specify the output format.

.. cmdoption:: -o, --output=FILE

   Write to the specified file, instead of stdout.

Next comes the auxiliary options:

.. cmdoption:: -I, --include=DIR

   Prepend the specified directory to the library and include file search
   path. This option may be repeated.

.. cmdoption:: -S, --style=STYLE

   Set a global style. See Customization_ for more details. This option may
   be repeated.

.. cmdoption:: -s, --set VAR=VALUE

   Set a customization variable. This overrides any settings in the input
   files. This option may be repeated.

.. cmdoption:: --noinit

   Don't read your personal init file.

.. cmdoption:: -w, --nowarn

   Don't print warnings.

.. cmdoption:: -e, --errors=NUM

   Print this many errors before aborting (default: 10). If set to zero,
   print all errors.

Finally, here are the information options:

.. cmdoption:: --show=TYPE

   Show one of several types of information, and exit. The ``TYPE``
   argument can be one of:

   ``maps``
	   Show a list of all the map sections defined in the input. This
	   is useful for finding the numbers of the map sections you want
	   to print.

   ``path``
	   Show the directories that are searched for library and include
	   files.

   ``vars``
	   Show a complete list of defined variables, in a format suitable
	   for feeding back into IFM. See `Output variables`_.

.. cmdoption:: -v, --version

   Print the program version.

.. cmdoption:: -h, --help

   Just print some usage information.

Types of output
===============

IFM has three different types of output (a map, a list of items, and a list
of tasks) and several different output formats, which are described in the
following sections. Not all types of output are produced by each output
format. The table below shows what's available for each format.

    ====== ========== === === ==== === === ===
    Output PostScript Fig Tk  Text Rec Dot Raw
    ====== ========== === === ==== === === ===
    Map    Yes        Yes Yes
    Items                     Yes          Yes
    Tasks                     Yes  Yes Yes Yes
    ====== ========== === === ==== === === ===

All the map output formats display map sections in the same way, so that
what you get with one format looks much the same as another. [1]_

PostScript maps (``ps``)
------------------------

This produces a PostScript map suitable for printing.  Several map sections
may be printed per page, and the maps are printed over as many pages as it
takes.  Automatic packing is done to try to get a good fit on the
page. Also, portrait or landscape is chosen depending on whichever gives
the best fit. Fonts of room and item text are scaled to fit them in the
room boxes, if required.

Fig maps (``fig``)
------------------

This produces a map which can be read (and edited) by `Xfig
<http://www.xfig.org>`_, and any other programs which understand Fig
format. The map sections are packed to get a best fit automatically, in a
similar manner to PostScript, but since Fig has no concept of pages, it is
most useful when you're printing each map section individually.  There's a
utility program called :ref:`ifm2dev <ifm2dev>` which automatically does
this.

Fig format is also useful if you want to print poster-sized maps over
several pages. The :option:`-M` option of :program:`fig2dev` (part of the
transfig package) will automatically do this.

Tk drawing commands (``tk``)
----------------------------

This produces map commands for input to :ref:`tkifm <tkifm>`, a simple
graphical interface to IFM. It isn't very useful to produce this output
yourself---:program:`tkifm` does that internally to build its map
pictures. But you can control its display by setting variables in the usual
way.

ASCII text (``text``)
---------------------

This produces human-readable output for items and tasks. The output should
be fairly self-explanatory.

.. _recording:

Recording commands (``rec``)
----------------------------

This output produces a list of commands suitable for feeding to IF
interpreters in playback mode. All the commands in the output are converted
to uppercase.

In order for this to work properly, you have to give commands that the game
will understand. The cmd attribute of rooms, links, joins and tasks can
help with this. Currently there's no item :keyword:`cmd` attribute, so you
have to make sure that the item description is recognized by the game (for
:keyword:`get` and :keyword:`drop` commands).  Also, if a task is
implicitly done in the game without you having to type any commands (e.g.,
visiting a room), you can indicate this by using :keyword:`cmd none`.

Of course, a recording will only play back properly in an interpreter if it
provides correct game commands.  Random events can't be dealt with by IFM,
and will probably cause playback to fail. But you can work around this with
an interpreter that is able to fix the random seed at startup (e.g.,
:program:`frotz`). This should eliminate most (but not all) of the problems
of randomness.

Task dependencies (``dot``)
---------------------------

This produces a graph of the dependencies of tasks on each other, in
Graphviz (dot) format. You'll need to have `Graphviz
<http://www.graphviz.org>`_ installed in order to display the graph.

.. _raw:

Raw data (``raw``)
------------------

This produces raw data for all output formats, intended for use by other
programs (and the IFM regression test suite). Each entry consists of a
number of data lines, and is separated from other entries by a blank line.
Each data line consists of an attribute, a colon, and its value. The
attributes should be self-explanatory. [2]_

Customization
=============

You can change the appearance of many output features according to your
taste. You do this by setting the values of the variables that control
those features.  This section tells you how to use variables---for a
complete list of the customization variables available, see `Output
variables`_.

As a first example, the background colour of rooms is determined by the
variable :keyword:`room_colour`. Its default value is ``white``. It can be
changed like this::

    room_colour = "beige";

Setting a variable like this will affect all output formats. But in some
cases you don't want to do that. A good example is the one above---if you
don't have a colour printer, you may not want to have beige rooms printed
(they'll come out greyish). To get around that, you can set variables that
are specific to a particular output format::

    tk.room_colour = "beige";

This says to set the variable to ``beige`` only if producing Tk output. The
default for all other formats is still ``white``.

You can also customize the appearance of individual rooms and links on the
map, by using different display styles. A display style is just a group of
variable settings with a given name. For example, suppose you're making a
map of *Colossal Cave* and want to mark rooms where you can refill your water
bottle. You can define a style called, say, ``Water``, like this::

    style Water;
    room_colour = "light blue";
    endstyle;

The values of variables that are set between the :keyword:`style` and
:keyword:`endstyle` clauses only apply to things drawn in that style. Now,
if you declare rooms like this::

    room "At End Of Road";

    room "Inside Building" dir e go in style Water;

then the room "Inside Building" will be drawn with a light blue
background. You can customize individual links in a similar manner.

An alternative way to define a variable in a particular style is to use the
in style clause, like this::

   room_colour = "light blue" in style Water;

If a style only changes a single variable, this may be more convenient.

If you assign a style (say, called ``newstyle``) to an object, but don't
define it anywhere in your input, then IFM will look for a file called
:file:`newstyle.ifm` using the standard search path. If the file exists, it
is expected to define style ``newstyle``. For example, you could put the
``Water`` style definition above into a file called :file:`Water.ifm`
somewhere on the IFM search path, and it would be read automatically. This
is useful if, for example, you want to use the same style in several
different maps.

You can define global styles using the :option:`--style` command-line
option; these apply to all IFM objects.  Global styles are most useful when
setting variables that affect the overall appearance of the output, in
conjunction with the file search method described above (e.g., a file
containing general colour and font definitions).

.. _variables:

Output variables
================

There are many variables available for customizing output. Most of them are
for customizing map output.  Their names, descriptions and default values
are all contained in the IFM initialization file. You can change this file
to set global defaults for everybody, or alternatively set your own
preferences in your personal init file.

Here's the original initialization file that came bundled with IFM:

.. literalinclude:: ../lib/ifm-init.ifm

Predefined styles
=================

IFM comes with a few predefined style files, as shown in the table below:

    ========== ====== ====================================
    Style      Scope  Description
    ========== ====== ====================================
    helvetica  global Use Helvetica fonts everywhere in maps
    puzzle     room   Mark room as containing a puzzle
    special    link   Mark link as being special in some way
    reckless   global Treat all tasks as safe when solving the game
    verbose    global Print verbose solver messages
    ========== ====== ====================================

If you create any generally useful or nice-looking styles, you might want
to send me a copy so I can include them with the next version of IFM.  The
"scope" field indicates which type of IFM object it applies to. Styles that
have global scope can meaningfully be used by the :option:`-style`
command-line option.

.. rubric:: Footnotes

.. [1] Well, that's the goal anyway. But there are still some very minor
       differences.

.. [2] Programmer-speak for "I couldn't be bothered to document it."
