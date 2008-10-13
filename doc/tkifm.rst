.. _tkifm:

======================================
 ``tkifm``: create maps interactively
======================================

``tkifm`` is a graphical front end to IFM. It provides a text editing
window in which you can map out your game using IFM commands, and a set of
menus to view things.  The various features are as follows:

Text editing window
       This is the main window, where you type IFM commands. It provides
       all the usual text editing command bindings that come with the
       Tcl/Tk text widget, as well as syntax highlighting.

File menu
       The standard set of file commands: *New*, *Open*, *Save*, *Save-As*,
       *Export* (to PostScript or Fig), *Quit*.  There's also a command
       called *Redraw*, which invokes IFM on the current file
       again. Normally you don't have to use this (it's done whenever you
       open a new file or save the current one), but if you change your
       initialization file (see below) the changes won't be noticed unless
       you do a *Redraw*.

Map menu
       For each map section in your map, a menu entry appears
       here. Selecting it will draw the appropriate map in another window.

Item menu
       This contains a single menu item, which displays a list of items in
       another window.

Task menu
       This contains two menu items: *Task list (brief)*, which displays a
       high-level walkthrough of the game in another window, and *Task list
       (verbose)* which does the same but gives detailed information about
       what the game solver is up to.

Show menu
       This contains two menu items: *Variables*, which shows all the
       currently defined variables and their values, and *Paths*, which
       shows the file search path.

Help menu
       This displays a small info panel about the current IFM version,
       including copying restrictions.

Using Your Own Editor
=====================

If you'd like to use your own editor to edit IFM files, but still view
results with ``tkifm``, you can. ``tkifm`` recognizes when the file it is
visiting gets modified, and rereads it if so. If you like, you can also
disable all tkifm file modification commands by setting the ``ifm(edit)``
variable to zero (see below). This is probably a good idea if using another
editor, or else you might accidentally save from ``tkifm`` and lose all
your changes.

Customization
=============

On startup, ``tkifm`` reads an initialization file in your home directory
(the one pointed at by the ``HOME`` environment variable). On Unix systems
it is called ``.tkifmrc``, and on Win32 systems it is called ``tkifm.ini``.
From there, using Tcl commands, you can set various things that affect the
appearance of the program.  Here's an example file showing the valid
variables, their format and defaults::

    # Example tkifm init file.

    # Whether to allow editing.
    set ifm(edit) 1

    # Edit window dimensions.
    set ifm(editwidth)  80
    set ifm(editheight) 24

    # Editing font.
    set ifm(editfont) {Courier 12 bold}

    # Edit window colours.
    set ifm(editforeground) black
    set ifm(editbackground) wheat

    # Item list window dimensions.
    set ifm(itemwidth)  50
    set ifm(itemheight) 30

    # Task list (brief) window dimensions.
    set ifm(taskwidth)  50
    set ifm(taskheight) 30

    # Task list (verbose) window dimensions.
    set ifm(verbosewidth)  80
    set ifm(verboseheight) 30

    # Variable window dimensions.
    set ifm(varswidth)  50
    set ifm(varsheight) 30

    # Text window font.
    set ifm(textfont) {Times 12 bold}

    # Text window colours.
    set ifm(textforeground) black
    set ifm(textbackground) wheat

    # Whether to allow tearoff menus.
    set ifm(tearoff) 1

    # Syntax highlighting variables.
    set ifm(syntaxcomments)     firebrick
    set ifm(syntaxstrings)      grey40
    set ifm(syntaxstructure)    blue
    set ifm(syntaxdirections)   darkgoldenrod
    set ifm(syntaxspecial)      cadetblue
    set ifm(syntaxbuiltin)      forestgreen
    set ifm(syntaxkeyword)      royalblue
    set ifm(syntaxpreprocessor) purple

Errors and Warnings
===================

Any errors or warnings that occur when invoking IFM will be displayed in a
dialog. The current line of the text window will be changed to point at the
error or warning line (if appropriate).
