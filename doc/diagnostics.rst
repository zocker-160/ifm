=============
 Diagnostics
=============

This section describes the possible error and warning messages which might
be produced by IFM, and what they mean. Note that individual output formats
may print their own errors and/or warnings. These lists only cover the
standard ones.

Error Messages
==============

Here's the list of error messages. If any errors occur, no output is
produced.

``error: invalid repeat count``
       You've given a repeat count of zero or less for a string or
       direction, which doesn't make much sense.

``error: no last room``
       You've given the very first room a dir clause.

``error: no [type] referred to by 'last'``
       You've said last to refer to the last room, item or task that was
       defined, but none of that type of object have been defined yet.

``error: no [type] referred to by 'it'``
       You've said it to refer to the last room, item or task tag that was
       mentioned in the current command, but no tags of that type of object
       have been mentioned.

``error: [type] tag [name] already defined``
       You've given two similar objects the same tag name.

``error: [type] tag [name] not defined``
       You've referred to a tag name that hasn't been defined anywhere in
       the input.

``error: [type] tag [name] not yet defined``
       You're referring to a tag at a point where it hasn't yet been
       defined, in a situation where it must be (e.g., the room ``from``
       clause, or a command that modifies attributes of a
       previously-defined object).

``error: can't modify [name] attribute``
       You're attempting to modify an attribute of an object which can't be
       changed once it's set (e.g., a tag name). This is because it would
       create inconsistencies between objects.

``error: can't link [name1] and [name2] -- different map sections``
       The rooms you're trying to link are on different sections of the
       map, and have no spatial relation to one another. You might have
       forgotten to link a previous room in the list. Or you meant to use a
       join.

``error: can't link [name] to itself without at least one direction``
       To link a room to itself, you need to specify at least one
       direction. Otherwise, the link goes nowhere.

``error: links between [name1] and [name2] have differing lengths``
       You've defined more than one link or join between the given rooms,
       but given them different values for the ``length`` attribute. This
       isn't allowed.

``error: more than one task needs to follow [task] immediately``
       You've given two or more tasks an identical ``follow`` tag.  Only
       one task can "follow" a given task.

``error: [num] cyclic task dependencies``
       The game isn't solvable because there's one or more chains of tasks
       where each must be done before the next, but the last must be done
       before the first.

``error: variable [name] is not defined``
       A customization variable needed by an output format is not
       defined. You should only see these errors if you have modified or
       overridden the system initialization file. The remedy is to define
       the variable somewhere.

Warning Messages
================

Here's the list of warning messages. If only warnings occur, then output is
still produced.

``warning: attribute [attr] ignored -- no implicit link``
       You've given a room with no ``dir`` clause an attribute that is
       associated with that link (e.g., ``oneway``). Most likely you're
       putting the attribute in the wrong place---if you want, say, a join
       to have one of these attributes, you must define it using the
       standalone ``join`` command instead.

``warning: link from [name1] to [name2] outside grid``
       The destination room for a link is not in a compass direction from
       the last specified position.

``warning: rooms [name1] and [name2] overlap``
       The coordinates of the specified rooms are the same.

``warning: room [name] crossed by link line between [name] and [name]``
       A link line passes through the coordinates of a room.

``warning: room [name] has multiple [dir] links``
       More than one link connects to the specified room in a particular
       direction.

``warning: can't solve game ([num] tasks not done)``
       The game is unsolvable according to the current set of tasks. This
       can be due to part of the map being inaccessible, or IFM stupidly
       choosing the wrong order of doing things.  Hopefully the latter
       shouldn't happen very often.

``warning: can't solve game ([num] tasks ignored)``
       The game is unsolvable because you're explicitly ignoring tasks
       and/or items, using the ``ignore`` attribute.

``warning: no matching style command``
       You've used ``endstyle`` without a matching ``style`. You probably
       have too many ``endstyle`` commands.

``warning: unexpected style: [name] (expected [name])``
       You've used ``endstyle`` with an argument that doesn't match the
       argument of the corresponding ``style``. You might have missed out
       another ``endstyle`` somewhere, or have too many.

``warning: style [name] referenced but not defined``
       An object in your input uses the specified style, but it isn't
       defined anywhere and the style definition file ``name.ifm`` doesn't
       exist in the search path (or if it does, it doesn't define the
       required style).

``warning: [syntax] is obsolete -- use [phrase] instead``
       You've used an obsolete syntax. Consult the documentation and then
       try the suggested alternative instead. Note that multiple uses of
       the same obsolete syntax only result in a single warning.
