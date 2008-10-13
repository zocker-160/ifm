==============
 Introduction
==============

About IFM
=========

IFM is a language for keeping track of your progress through an Interactive
Fiction game, and a program for producing various different sorts of output
using it.  You can record each room you visit and its relation to other
rooms, the initial locations of useful items you find, and the tasks you
need to perform in order to solve the game.

The IFM mapping commands are designed so that you can easily add to the map
as you explore the game. You type in the rooms you visit and the directions
you move in to reach other rooms, and IFM calculates the position of each
room in relation to the others. A map can consist of several independent
sections, allowing you to divide up the map however you like. See
:ref:`making-maps` for an example of how to make a map.

The IFM task commands, if used, allow you to specify the order in which
game-solving tasks must be done. The IFM program can then calculate and
print a high-level "walkthrough" of the game. See :ref:`solving` for
examples of how to do this.

Several output formats are available, including PostScript, Fig and ASCII
text---these are described in :ref:`usage`. Some of the output formats have
a set of variables which control the appearance of the output---see
:ref:`variables`.

History of IFM
==============

When I started playing IF games, years ago, I did what many other people
did---made a rough map on paper of where I'd explored, so I could see which
directions I hadn't tried yet. Inevitably, the maps always fell off the
page and turned into a complete mess.

My first attempt at solving this problem was to make use of the tools I had
available to draw the map for me. So I started typing the map network into
a file, and wrote a small Perl script to convert the data into something
that `groff <http://groff.ffii.org>`_ could read and draw a map from. I
also added a way of recording which items I'd found, and whether I'd found
a use for them yet.

As it stood, this worked quite well---it produced nice maps and lists of
items so I could see where I'd got to. The only problem was that it was
just as tedious making maps this way as on paper, since I had to work out
the offset of each room relative to a fixed origin.

Eventually I decided that enough was enough. I wanted to be able to add
stuff to the map as I played the game, without having to worry about
offsets or anything irrelevant like that. Hence the main design criteria
for IFM. The other criteria were easy---an input language, for flexibility
and extendability, and a program for converting files in this language into
different types of output.

Partway through writing the initial version of IFM, I had the idea that it
would be nice to be able to somehow record not only the map and items found
so far, but what's been done to solve the game. The concept of tasks
appeared, which immediately tripled the size of the program and caused all
sorts of headaches.

But eventually it got to the stage where it might be worth releasing, so in
June 1998 the first version appeared in the `IF archive`_. Very soon after
that, I got a lot of feedback from one Dave Chapeskie
(dchapes@ddm.wox.org), who made a lot of great suggestions for improvements
and new features. He also very kindly started up a Web page for IFM maps;
you can find it at http://www.sentex.net/~dchapes/ifm.

And now, finally, it's finished and I can go back to that IF game I was
playing. [1]_

.. _IF archive: http://www.ifarchive.org

.. [1] Oh all right. Maybe *one* more feature...
