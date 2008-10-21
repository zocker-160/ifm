==================
 Output variables
==================

General variables
=================

.. list-table::
   :widths: 1 1 1 10 1
   :header-rows: 1
   
   * - Name
     - Type
     - Default
     - Description
     - Outputs

   * - ``colour_file``
     - string
     - "ifm-rgb.txt"
     - File of colour definitions, which contains the RGB values of each
       colour referred to below (and a good many more).  It's just the
       rgb.txt file found on Unix/X11 systems.  See that file for a list of
       available colours.  You can use the same colour names for the Tk
       output, since it uses the standard X colours.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``prolog_file``
     - string
     - "ifm-pro.ps"
     - Prolog file that gets prepended to all the PostScript output.  This
       defines all the procedures for drawing everything.
     - :ref:`ps <ps>`

   * - ``font_scale``
     - float
     - 1
     - Scale factor which is applied to all fonts.  This is a convenience
       variable to make font adjustments easier.
     - :ref:`ps <ps>` :ref:`fig <fig>`

Page variables
==============

.. list-table::
   :widths: 1 1 1 10 1
   :header-rows: 1
   
   * - Name
     - Type
     - Default
     - Description
     - Outputs

   * - ``page_size``
     - string
     - "A4"
     - Default page size.  Available page sizes are: ``A3``, ``A4``, ``A``,
       ``B``, ``C``, ``Legal``, ``Letter``.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``page_width``
     - float
     - undef
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``page_height``
     - float
     - undef
     - If defined, these set a custom page size which overrides the
       ``page_size`` variable.  Units are in cm.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``page_margin``
     - float
     - 2
     - Margin space to be left on each page, in cm.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``page_rotate``
     - int
     - undef
     - Whether to rotate each page to landscape.  If not defined, then
       rotation is decided on a per-page basis in order to get the best
       fit.
     - :ref:`ps <ps>`

   * - ``show_page_title``
     - int
     - true
     - Whether to show the main title on each page.
     - :ref:`ps <ps>`

   * - ``page_title_colour``
     - int
     - "black"
     - Page title colour.
     - :ref:`ps <ps>`

   * - ``page_title_font``
     - int
     - "Times-Bold"
     - Page title font.
     - :ref:`ps <ps>`

   * - ``page_title_fontsize``
     - int
     - 18
     - Page title fontsize.
     - :ref:`ps <ps>`

   * - ``show_page_border``
     - int
     - false
     - Whether to show a border around each page.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``page_border_colour``
     - int
     - "black"
     - Colour of the page border (if drawn).
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``page_background_colour``
     - int
     - "white"
     - Colour of the page background (if border is drawn).
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``fit_page``
     - int
     - false
     - Whether to scale Fig layout to fit on a single page.  Most of the
       time, this doesn't make things look good.
     - :ref:`fig <fig>`

Map section variables
=====================

.. list-table::
   :widths: 1 1 1 10 1
   :header-rows: 1
   
   * - Name
     - Type
     - Default
     - Description
     - Outputs

   * - ``show_map_title``
     - int
     - true
     - Whether to show the map title.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``map_title_colour``
     - int
     - "black"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``map_title_font``
     - int
     - "Times-Bold"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``map_title_fontsize``
     - int
     - 14
     - Appearance of the title printed above each map section.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``show_map_border``
     - int
     - false
     - Whether to show a border around each map section.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``map_border_colour``
     - int
     - "black"
     - Colour of the map border (if drawn).
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``map_background_colour``
     - int
     - "white"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``tk.map_background_colour``
     - int
     - "wheat"
     - Colour of the map background (if border is drawn).
     - :ref:`tk <tk>`

   * - ``map_section_spacing``
     - int
     - 1
     - Minimum space, in rooms, between map sections when packed together.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``map_canvas_height``
     - int
     - 6
     - xxx
     - :ref:`tk <tk>`

   * - ``map_canvas_width``
     - int
     - 8
     - Maximum width and height of the Tk map canvas window, in rooms.
       Sizes bigger than this will cause scrollbars to appear.
     - :ref:`tk <tk>`

Room variables
==============

.. list-table::
   :widths: 1 1 1 10 1
   :header-rows: 1
   
   * - Name
     - Type
     - Default
     - Description
     - Outputs

   * - ``room_size``
     - int
     - 3
     - Space allocated for each room, in cm.  In PostScript and Fig, this
       is the maximum size -- the actual size may be reduced in order to
       fit things on the page.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_width``
     - int
     - 0.8
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_height``
     - int
     - 0.65
     - Proportion of the room space that's taken up by the room dimensions.
       These values should be less than 1 or you'll have no space left for
       link lines.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_colour``
     - int
     - "white"
     - Default background colour of rooms.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_shadow_xoff``
     - int
     - 0.05
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_shadow_yoff``
     - int
     - 0.05
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_shadow_colour``
     - int
     - "grey50"
     - Offset and colour of room 'shadows'.  This is a pseudo-3D effect
       which makes rooms look raised off the page.  The offsets are a
       proportion of the allocated room space.  Note that you can change
       the direction of the room shadow by negating one or both of the
       offsets.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_border_width``
     - int
     - 1
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_border_colour``
     - int
     - "black"
     - Width and colour of the room box lines.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_border_dashed``
     - int
     - 0
     - Whether to draw dashed room borders.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``room_exit_width``
     - int
     - 1
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_exit_colour``
     - int
     - "black"
     - Width and colour of the room exit lines.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_text_colour``
     - int
     - "black"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``room_text_font``
     - int
     - "Times-Bold"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``room_text_fontsize``
     - int
     - 10
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``room_text_fontdef``
     - int
     - "Times 10 bold"
     - Colour, font and fontsize of room description text.
     - :ref:`tk <tk>`

   * - ``show_items``
     - int
     - true
     - Whether to show non-hidden item descriptions in rooms.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``item_text_colour``
     - int
     - "black"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``item_text_font``
     - int
     - "Times-Italic"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``item_text_fontsize``
     - int
     - 6
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``item_text_fontdef``
     - int
     - "Times 8 italic"
     - Colour, font and fontsize of item description text (if shown).
     - :ref:`tk <tk>`

   * - ``show_tags``
     - int
     - false
     - Whether to append room tag names to room descriptions.  If so, they
       are appended in square brackets, like [this].
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

Link style variables
====================

.. list-table::
   :widths: 1 1 1 10 1
   :header-rows: 1
   
   * - Name
     - Type
     - Default
     - Description
     - Outputs

   * - ``link_line_width``
     - int
     - 1
     - Width of link lines.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``link_colour``
     - int
     - "black"
     - Colour of link lines.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``link_arrow_size``
     - int
     - 0.1
     - Size of oneway link arrows, as a proportion of the allocated room
       space.
     - :ref:`ps <ps>` :ref:`tk <tk>`

   * - ``link_spline``
     - int
     - true
     - Whether to draw link lines as splines.
     - :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``link_dashed``
     - int
     - false
     - Whether to draw dashed link lines.
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``link_text_font``
     - int
     - "Times-Roman"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``link_text_fontsize``
     - int
     - 6
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``link_text_fontdef``
     - int
     - "Times 8 bold"
     - xxx
     - :ref:`tk <tk>`

   * - ``link_text_colour``
     - int
     - "black"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>`

   * - ``tk.link_text_colour``
     - int
     - "red"
     - Appearance of text that's associated with link lines.  The Tk
       default is to colour them differently for readability.
     - :ref:`tk <tk>`

   * - ``link_updown_string``
     - int
     - "U/D"
     - xxx
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``link_inout_string``
     - int
     - "I/O"
     - Text strings indicating up/down/in/out on links.  PostScript is
       currently a special case: the strings either side of the '/' are
       extracted and printed at either ends of the link, near the room they
       come from.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

Join style variables
====================

.. list-table::
   :widths: 1 1 1 10 1
   :header-rows: 1
   
   * - Name
     - Type
     - Default
     - Description
     - Outputs

   * - ``show_joins``
     - int
     - true
     - Whether to indicate joins in the room text.
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

   * - ``join_format``
     - int
     - "number"
     - Join string format (gets put in parentheses in those rooms that join
       to other rooms).  The value should be "number" or "letter".
     - :ref:`ps <ps>` :ref:`fig <fig>` :ref:`tk <tk>`

Game solver variables
=====================

.. list-table::
   :widths: 1 1 1 10 1
   :header-rows: 1
   
   * - Name
     - Type
     - Default
     - Description
     - Outputs

   * - ``keep_unused_items``
     - int
     - true
     - Whether to keep unused items (i.e. those which were obtained via some
       task or other, but currently have no use).
     - :ref:`text <text>` :ref:`rec <rec>`

   * - ``all_tasks_safe``
     - int
     - false
     - Whether to treat all tasks as safe (reckless mode!).
     - :ref:`text <text>` :ref:`rec <rec>`

   * - ``solver_messages``
     - int
     - false
     - Whether to print game solver info messages (helps with figuring out
       what it's up to).
     - :ref:`text <text>` :ref:`rec <rec>`

Task dependency variables
=========================

.. list-table::
   :widths: 1 1 1 10 1
   :header-rows: 1
   
   * - Name
     - Type
     - Default
     - Description
     - Outputs

   * - ``task_graph_rooms``
     - int
     - false
     - Whether to group tasks by the room they're done in.  This can either
       enhance the task structure or make it look a complete mess.
     - :ref:`dot <dot>`

   * - ``task_graph_orphans``
     - int
     - false
     - Whether to show orphan tasks (those with no previous/next
       dependencies).  Useful for completeness, but it clutters things up a
       lot.
     - :ref:`dot <dot>`

   * - ``task_graph_attr``
     - int
     - ""
     - Graph attributes, in Graphviz format.
     - :ref:`dot <dot>`

   * - ``task_graph_node``
     - int
     - "shape=box"
     - Node attributes, in Graphviz format.
     - :ref:`dot <dot>`

   * - ``task_graph_link``
     - int
     - ""
     - Link attributes, in Graphviz format.
     - :ref:`dot <dot>`

   * - ``task_graph_wrap``
     - int
     - 12
     - Word wrapping cutoff.
     - :ref:`dot <dot>`

   * - ``task_graph_font``
     - int
     - "Times-Roman"
     - Font name.
     - :ref:`dot <dot>`
