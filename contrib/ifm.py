# IFM module for python, by me.  Needs work.

MAP  = 1
ROOM = 2
ITEM = 3

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

u = up   = Dir("u")
d = down = Dir("d")

in_ = Dir("in")
out = Dir("out")

class Object:
    _objects = {}
    _tags = {}
    _count = {}

    def __init__(self, type, name):
        self.type = type
        self.name = name.replace('"', r'\"')
        self.notes = []

        self.number = Object._count.setdefault(type, 1)
        Object._count[type] += 1

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
        olist = self.objects(type)
        olist.append(self)

    def note(self, *notes):
        for line in notes:
            self.notes.append(line.replace('"', r'\"'))

        return self

    def last(self, type):
        olist = self.objects(type)
        if len(olist) > 0:
            return olist[-1]
        return None

    def objects(self, type):
        return Object._objects.setdefault(type, [])

    def write(self):
        raise NotImplementedError, "not implemented"

class Map(Object):
    def __init__(self, name):
        Object.__init__(self, MAP, name)

    def __str__(self):
        return "map \"%s\"" % self.name

class Room(Object):
    def __init__(self, name):
        Object.__init__(self, ROOM, name)

        self.dirs = []
        self.links = []
        self.godir = None
        self.map = self.last(MAP)
        self.fromroom = self.last(ROOM)
        self.noreturn = 0

    def dir(self, *dirs):
        self.dirs.extend(dirs)
        return self

    def from_(self, room):
        self.fromroom = room
        return self

    def go(self, dir):
        self.godir = dir
        return self

    def oneway(self):
        self.noreturn = 1
        return self

    def link(self, *rooms):
        self.links.extend(rooms)
        return self

class Item(Object):
    def __init__(self, name):
        Object.__init__(self, ITEM, name)
        self.room = self.last(ROOM)

    def room(self, room):
        self.room = room
        return self

if __name__ == "__main__":
    Map("Example Map")

    kitchen = Room("Kitchen")
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
