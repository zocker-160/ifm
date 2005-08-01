# IFM module for python, by me.  Needs work.

import sys

(MAP, ROOM, ITEM, LINK, TASK) = range(5)

class IFMError(RuntimeError): pass

class Dir:
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return self.name

n = north = Dir("n")
e = east  = Dir("e")
s = south = Dir("s")
w = west  = Dir("w")

ne = northeast = Dir("ne")
se = southeast = Dir("se")
sw = southwest = Dir("sw")
nw = northwest = Dir("nw")

u = up   = Dir("up")
d = down = Dir("down")

in_ = Dir("in")
out = Dir("out")

class Object:
    _objects = {}
    _tags = {}

    def __init__(self, type, name = None):
        self.type = type

        if name:
            self.name = name.replace('"', r'\"')

        # Add to object list if required.
        olist = Object.objects(type)
        if self not in olist:
            olist.append(self)

        # Assign number.
        self.number = self.count(type)

    @staticmethod
    def objects(type):
        "Return a list of objects of a given type."
        return Object._objects.setdefault(type, [])

    @staticmethod
    def count(type):
        "Return the number of objects of a given type."
        return len(Object.objects(type))

    @staticmethod
    def last(type):
        "Return the last object created of a given type."
        olist = Object.objects(type)

        if len(olist) > 0:
            return olist[-1]

        return None

class Map(Object):
    def __init__(self, name):
        Object.__init__(self, MAP, name)

    def write(self, fp):
        fp.write("\nmap \"%s\";\n" % self.name)

class MapObject(Object):
    "An object which is drawn on the map."

    def __init__(self, type):
        Object.__init__(self, type)

        self.section = Object.last(MAP)
        self.fromroom = None
        self.dirs = []
        self._go = None
        self._oneway = 0

        if not self.section:
            raise IFMError, "no Map defined"

    def dir(self, *dirs):
        "Add one or more directions."
        self.dirs.extend(dirs)
        return self

    def from_(self, room):
        "Set the 'from' room."
        self.fromroom = room
        return self

    def go(self, dir):
        "Set the actual direction travelled (up/down/in/out)."
        self._go = dir
        return self

    def oneway(self):
        "Set the direction to be oneway."
        self._oneway = 1
        return self

    def write(self, fp):
        if self.dirs:
            dirs = map(str, self.dirs)
            fp.write(" dir " + " ".join(dirs))
            if self.fromroom:
                fp.write(" from " + self.fromroom.tag)

        if self._go:
            fp.write(" go " + str(self._go))

class NamedObject(Object):
    "An object which has a name."

    def __init__(self, type, name):
        Object.__init__(self, type, name)
        self.notes = []

        # Create object tag.
        if type is ITEM:
            prefix = name.replace(" ", "_")
        else:
            prefix = "".join([w[0] for w in name.split()]).upper()

        count = 1
        self.tag = prefix
        while Object._tags.has_key(self.tag):
            count += 1
            self.tag = prefix + str(count)

        Object._tags[self.tag] = self

    def note(self, *notes):
        "Add one or more notes to the object."
        for note in notes:
            self.notes.append(note.replace('"', r'\"'))

        return self

    def write(self, fp):
        fp.write(" tag %s" % self.tag)

class RoomObject(NamedObject):
    "An object that appears in a room."

    def __init__(self, type, name):
        NamedObject.__init__(self, type, name)
        self._room = Object.last(ROOM)

    def room(self, room):
        "Set the initial room."
        self._room = room
        return self

class Room(MapObject, NamedObject):
    def __init__(self, name):
        NamedObject.__init__(self, ROOM, name)
        MapObject.__init__(self, ROOM)
        self.links = []
        self.exits = []

    def link(self, *rooms):
        "Link the room to one or more others."
        self.links.extend(rooms)
        return self

    def exit(self, *dirs):
        "Mark one or more room exits."
        self.exits.extend(dirs)
        return self

    def write(self, fp):
        fp.write("\nroom \"%s\"" % self.name)
        NamedObject.write(self, fp)
        MapObject.write(self, fp)

        if self.links:
            fp.write(" link")
            for link in self.links:
                fp.write(" " + link.tag)

        if self.exits:
            fp.write(" exit " + " ".join(map(str, self.exits)))

        fp.write(";\n")

class Link(MapObject):
    def __init__(self, room1, room2):
        MapObject.__init__(self, LINK)
        self._from = room1
        self._to = room2

    def write(self, fp):
        fp.write("\nlink %s to %s" % (self._from.tag, self._to.tag))
        MapObject.write(self, fp)
        fp.write(";\n")

class Item(RoomObject):
    def __init__(self, name):
        RoomObject.__init__(self, ITEM, name)

    def write(self, fp):
        fp.write("  item \"%s\"" % self.name)
        NamedObject.write(self, fp)
        fp.write(";\n")

class Task(RoomObject):
    def __init__(self, name):
        RoomObject.__init__(self, TASK, name)

def ifm_write(fp = sys.stdout, title = None):
    "Write IFM map to specified stream."

    # Write title.
    fp.write("# IFM map created by IFM python module.\n");

    if title:
        fp.write("\ntitle \"%s\";\n" % title.replace('"', r'\"'))

    # Write non-room items and tasks.
    for type in (ITEM, TASK):
        for obj in Object.objects(type):
            if obj._room is None:
                obj.write(fp)

    # Write each map section.
    for section in Object.objects(MAP):
        section.write(fp)
        for room in Object.objects(ROOM):
            if room.section is section:
                room.write(fp)
                for type in (ITEM, TASK):
                    for obj in Object.objects(type):
                        if obj._room is room:
                            obj.write(fp)

        for obj in Object.objects(LINK):
            obj.write(fp)

if __name__ == "__main__":
    Map("Example Map")

    Item("tongs")

    kitchen = Room("Kitchen").exit(s)
    Item("spoon").note("Stirs tea")
    Item("sink")
    Item("monkey")

    Room("Garage").dir(s).go(d)
    wrench = Item("monkey wrench")
    wrench.note("For wrenching monkey out of sink")

    lounge = Room("Lounge").dir(e).from_(kitchen)
    Item("TV set")

    diner = Room("Dining Room").dir(s).link(kitchen)
    Item("table")
    Item("chair")

    Room("Study").dir(e, n).from_(lounge).oneway()

    ifm_write()
