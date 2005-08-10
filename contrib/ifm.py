# IFM module for python.

# TODO:

# Variable settings.
# Rest of syntax.
# Styles.

import os
import sys

class IFMError(RuntimeError): pass

class Map:
    "An IFM map."

    _types = (SECT, ROOM, ITEM, LINK, JOIN, TASK) = range(6)

    def __init__(self, title = None):
        if title:
            self._title = title.replace('"', r'\"')
        else:
            self._title = None

        self._objects = {}
        for type in Map._types:
            self._objects[type] = []

    def section(self, name):
        s = Section(name)
        self._add(SECT, s)
        return s

    def room(self, name):
        r = Room(name)
        self._add(Map.ROOM, r)
        return r

    def link(self, room1, room2):
        l = Link(room1, room2)
        self._add(Map.LINK, l)
        return l

    def join(self, room1, room2):
        j = Join(room1, room2)
        self._add(Map.JOIN, j)
        return j

    def item(self, name):
        i = Item(name)
        self._add(Map.ITEM, i)
        return i

    def task(self, name):
        t = Task(name)
        self._add(Map.TASK, t)
        return t

    def _add(self, type, obj):
        self._objects[type].append(obj)
        obj._map = self

        if type in (Map.ROOM, Map.ITEM, Map.TASK):
            obj._section = self.last(Map.SECT)

        if type in (Map.ITEM, Map.TASK):
            obj._room = self.last(Map.ROOM)

    def last(self, type):
        olist = self._objects[type]

        if len(olist) > 0:
            return olist[-1]

        return None

    def edit(self, prog = "tkifm"):
        "Edit IFM map."

        tmp = self._tmpfile()

        fp = file(tmp, "w")
        self.write(fp)
        fp.close()

        os.system("%s %s" % (prog, tmp))
        os.unlink(tmp)

    def show(self, prog = "gv"):
        "Show PostScript IFM map."

        tmp = self._tmpfile()

        fp = os.popen("ifm -m -o %s" % tmp, "w")
        fp.write("page_rotate = 0;\n")
        self.write(fp)
        fp.close()

        os.system("%s %s" % (prog, tmp))
        os.unlink(tmp)

    def write(self, fp = sys.stdout):
        "Write IFM map to specified stream."

        # Write title.
        fp.write("# IFM map created by IFM python module.\n");

        if self._title:
            fp.write("\ntitle \"%s\";\n" % self._title)

        # Write non-room items and tasks.
        for type in (Map.ITEM, Map.TASK):
            count = 0
            for obj in self._objects[type]:
                if obj._room is not None:
                    continue

                if count == 0:
                    fp.write("\n")

                obj.write(fp)
                count += 1

        # Write each map section.
        for section in self._objects[Map.SECT]:
            self._write_section(section, fp)

        self._write_section(None, fp)

        # Write explicit links and joins.
        for type in (Map.LINK, Map.JOIN):
            for obj in self._objects[type]:
                obj.write(fp)

    def _write_section(self, section, fp):
        # Write a map section.
        if section:
            section.write(fp)

        for room in self._objects[Map.ROOM]:
            if room._section is section:
                room.write(fp)
            else:
                continue

            for type in (Map.ITEM, Map.TASK):
                for obj in self._objects[type]:
                    if obj._room is room:
                        obj.write(fp)

    def _tmpfile(self):
        import tempfile
        (fd, name) = tempfile.mkstemp()
        os.close(fd)
        return name

class MapObject:
    "An object which is drawn on the map."

    def __init__(self):
        self._from = None
        self._dirs = []
        self._go = None
        self._oneway = 0

    def dir(self, *dirs):
        "Add one or more directions."
        self._dirs.extend(dirs)
        return self

    def from_(self, room):
        "Set the 'from' room."
        self._from = room
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
        if self._dirs:
            dirs = [str(x) for x in self._dirs]
            fp.write(" dir " + " ".join(dirs))
            if self._from:
                fp.write(" from " + self._from._tag)

        if self._go:
            fp.write(" go " + str(self._go))

        if self._oneway:
            fp.write(" oneway")

class TaskObject:
    "An object having task attributes."

    def __init__(self):
        self._before = []
        self._after = []
        self._need = []

    def before(self, *tasks):
        self._before.extend(tasks)

    def after(self, *tasks):
        self._after.extend(tasks)

    def need(self, *items):
        self._need.extend(items)

    def write(self, fp):
        if self._before:
            fp.write(" before")
            for task in self._before:
                fp.write(" " + task._tag)

        if self._after:
            fp.write(" after")
            for task in self._after:
                fp.write(" " + task._tag)

        if self._need:
            fp.write(" need")
            for item in self._need:
                fp.write(" " + item._tag)

class TagObject(TaskObject):
    "An object which has a name."

    # Assigned tags.
    _tags = {}

    def __init__(self, name, tagprefix):
        TaskObject.__init__(self)

        self._name = name.replace('"', r'\"')
        self._notes = []
        self._ignore = 0

        if tagprefix:
            count = 1
            self._tag = tagprefix

            while TagObject._tags.has_key(self._tag):
                count += 1
                self._tag = tagprefix + str(count)

            TagObject._tags[self._tag] = self

    def note(self, *notes):
        "Add one or more notes to the object."
        for note in notes:
            self._notes.append(note.replace('"', r'\"'))

        return self

    def ignore(self):
        self._ignore = 1

    def write(self, fp):
        TaskObject.write(self, fp)
        fp.write(" tag %s" % self._tag)

        if self._ignore:
            fp.write(" ignore");

        # FINISH ME.
        if self._notes:
            pass

class RoomObject(TagObject):
    "An thing that appears in a room."

    def __init__(self, name, longtag = 1):
        prefix = name.replace(" ", "_")
        TagObject.__init__(self, name, prefix)

    def in_(self, room):
        "Set the initial room."
        self._room = room
        return self

class LinkObject(MapObject, TaskObject):
    "An object which links to others on the map."

    def __init__(self, room1, room2, cmd):
        MapObject.__init__(self)
        TaskObject.__init__(self)

        self._cmd = cmd
        self._from = room1
        self._to = room2

    def write(self, fp):
        fp.write("\n%s %s to %s" % (self._cmd, self._from._tag, self._to._tag))
        MapObject.write(self, fp)
        TaskObject.write(self, fp)
        fp.write(";\n")

class Section(TagObject):
    "A map section."

    def __init__(self, name):
        TagObject.__init__(self, name, None)

    def write(self, fp):
        fp.write("\nmap \"%s\";\n" % self._name)

class Room(TagObject, MapObject):
    def __init__(self, name):
        prefix = "".join([w[0] for w in name.split()]).upper()
        TagObject.__init__(self, name, prefix)
        MapObject.__init__(self)

        self._links = []
        self._joins = []
        self._exits = []
        self._nolink = 0
        self._nopath = 0
        self._nodrop = 0
        self._start = 0
        self._finish = 0

    def link(self, *rooms):
        "Link the room to one or more others."
        self._links.extend(rooms)
        return self

    def join(self, *rooms):
        "Join the room to one or more others."
        self._joins.extend(rooms)
        return self

    def exit(self, *dirs):
        "Mark one or more room exits."
        self._exits.extend(dirs)
        return self

    def nolink(self):
        self._nolink = 1

    def nopath(self):
        self._nopath = 1

    def nodrop(self):
        self._nodrop = 1

    def start(self):
        self._start = 1

    def finish(self):
        self._finish = 1

    def write(self, fp):
        fp.write("\nroom \"%s\"" % self._name)
        TagObject.write(self, fp)
        MapObject.write(self, fp)

        if self._links:
            fp.write(" link")
            for link in self._links:
                fp.write(" " + link._tag)

        if self._joins:
            fp.write(" join")
            for join in self._joins:
                fp.write(" " + join._tag)

        if self._exits:
            fp.write(" exit " + " ".join([str(x) for x in self._exits]))

        if self._nolink:
            fp.write(" nolink")

        if self._nopath:
            fp.write(" nopath")

        if self._nodrop:
            fp.write(" nodrop")

        if self._start:
            fp.write(" start")

        if self._finish:
            fp.write(" finish")

        fp.write(";\n")

class Link(LinkObject):
    def __init__(self, room1, room2):
        LinkObject.__init__(self, room1, room2, "link")

class Join(LinkObject):
    def __init__(self, room1, room2):
        LinkObject.__init__(self, room1, room2, "join")

    def dir(self, *dirs):
        raise IFMError, "'dir' not available for joins"

    def from_(self, room):
        raise IFMError, "'from_' not available for joins"

class Item(RoomObject):
    def __init__(self, name):
        RoomObject.__init__(self, name)

    def write(self, fp):
        fp.write("  item \"%s\"" % self._name)
        RoomObject.write(self, fp)
        fp.write(";\n")

class Task(RoomObject):
    def __init__(self, name):
        RoomObject.__init__(self, name)

    def in_any(self):
        self._room = None

class Dir:
    "An IFM direction."

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

if __name__ == "__main__":
    map = Map("Example Map")

    kitchen = map.room("Kitchen").exit(s)
    map.item("spoon").note("Stirs tea")
    map.item("sink")
    map.item("monkey")

    map.room("Garage").dir(s).go(d)
    wrench = map.item("monkey wrench")
    wrench.note("For wrenching monkey out of sink")

    lounge = map.room("Lounge").dir(e).from_(kitchen)
    map.item("TV set")

    diner = map.room("Dining room").dir(s).link(kitchen)
    map.item("table")
    map.item("chair")

    map.room("Study").dir(e, n).oneway()

    map.write()
    #map.show("gs -q -dBATCH -dNOPAUSE -sOutputFile=out.ps -")
