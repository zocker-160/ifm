#! /usr/local/bin/perl

### scr2ifm -- convert game transcript to IFM

use Getopt::Std;

# Compass direction command -> direction mapping.
%cdirmap = ("N" => "n", "NORTH" => "n", "NE" => "ne", "NORTHEAST" => "ne",
	    "E" => "e", "EAST" => "e", "SOUTHEAST" => "se", "SE" => "se",
	    "SOUTH" => "s", "S" => "s", "SOUTHWEST" => "sw", "SW" => "sw",
	    "WEST" => "w", "W" => "w", "NORTHWEST" => "nw", "NW" => "nw");

# Other direction command -> direction mapping.
%odirmap = ("UP" => "up", "U" => "up", "DOWN" => "down", "D" => "down",
	    "IN" => "in", "OUT" => "out");

# Reverse-direction mapping.
%rdirmap = ("n" => "s", "s" => "n", "ne" => "sw", "sw" => "ne", "e" => "w",
	    "w" => "e", "se" => "nw", "nw" => "se", "in" => "out",
	    "out" => "in", "up" => "down", "down" => "up");

# Direction list in order of positioning preference.
@dirlist = ("n", "s", "e", "w", "ne", "se", "sw", "nw");

# List of transcript moves (hash entries).
@moves = ();

# Room tag -> room data mapping.
%roommap = ();

# Linked rooms -> link data mapping.
%linkmap = ();

# List of IFM rooms.
@rooms = ();

# List of IFM links.
@links = ();

# Default room name recognition parameters.
$name_maxwords = 8;
$name_maxuncap = 3;
$name_invalid = '[.!?]';

# Default room description recognition parameters.
$desc_minwords = 20;

# Default command regexps.
$cmd_prompt = '^>\s*';
$cmd_look = '^L(OOK)?$';
$cmd_end = '^UNSCRIPT$';
$cmd_undo = '^UNDO$';
$cmd_invalid = '^RE(START|STORE)$';

### Stage 1 -- parse arguments and read input.

# Parse arguments.
$0 =~ s-.*/--;
&getopts('c:dhlo:t:vw') or die "Type `$0 -h' for help\n";
&usage if $opt_h;

# Read IFM command file if required.
if ($opt_c) {
    open(CMD, $opt_c) or die "Can't open $opt_c: $!\n";

    while (<CMD>) {
	# Skip blanks and comments.
	next if /^\s*#/;
	next if /^\s*$/;

	if (/^\s*\$/) {
	    # Perl variable.
	    eval;
	    &error("%s: %s", $opt_c, $@) if $@;
	} else {
	    # IFM command.
	    push(@ifmcmds, $_);
	}
    }

    close CMD;
}

# Redirect stdout if required.
if ($opt_o) {
    open(STDOUT, "> $opt_o") or die "Can't open $opt_o: $!\n";
}

# Skip input until first prompt.
while (<>) {
    last if /$cmd_prompt/o;
}

# Read command/reply blocks.
&verbose(1, "Reading transcript...");

while (1) {
    # Get command.
    s/$cmd_prompt//o;
    chop($cmd = uc $_);
    $cmd =~ s/\s+$//;
    $line = $.;

    # Check for end of script.
    last if $cmd =~ /$cmd_end/o;

    # Read reply.
    $reply = [];
    while (<>) {
	last if /$cmd_prompt/o;
	chop;
	push(@$reply, $_);
    }

    if ($cmd =~ /$cmd_undo/o) {
	# Undo -- pop previous move (if any).
	pop(@moves) unless $undone++;
    } else {
	# Record move.
	$move = {};
	$move->{CMD} = $cmd;
	$move->{REPLY} = $reply;
	$move->{LINE} = $line;
	push(@moves, $move);
	undef $undone;
    }

    last if eof;
}

### Stage 2 -- scan moves for those which mark or change room.

&verbose(1, "Scanning for movement commands...");

foreach $move (@moves) {
    undef $roomflag;
    undef $descflag;
    undef $desc;

    &error("invalid transcript command: %s", $move->{CMD})
	if $move->{CMD} =~ /$cmd_invalid/o;

    next if $move->{CMD} =~ /$cmd_ignore/o;

    for (@{$move->{REPLY}}) {
	$blank = /^\s*$/;

	# Check for room name.
	if (!$roomflag && !$blank && &roomname($_)) {
	    $roomflag++;
	    $name = $_;
	    next;
	}

	# If got room name, decide if there's a blank line between
	# it and the description.
	$desc_gap = $blank if $roomflag && !defined $desc_gap;

	# If there isn't a blank line, but this line is, then there's
	# no description.
	last if $roomflag && !$desc_gap && $blank;

	# Check for room description.
	if ($roomflag && !$blank) {
	    $desc .= "# " . $_ . "\n";
	    $descflag++;
	    next;
	}

	# Check for end of description.
	last if $descflag && $blank;
    }

    # Store room info (if any).
    if ($roomflag) {
	$move->{ROOM} = $name;
	$move->{DESC} = $desc if $desc;
	$move->{LOOK} = 1 if $move->{CMD} =~ /$cmd_look/o;

	&warning("room `%s' verbose description is missing", $name)
	    if !$desc && !$roomwarn{$name}++;
    }
}

### Stage 3 -- Build IFM room and link lists.

&verbose(1, "Building rooms and links...");

foreach $move (@moves) {
    $name = $move->{ROOM};
    $desc = $move->{DESC};
    $line = $move->{LINE};

    # Skip it if no room is listed.
    next unless $name;

    # If it's a LOOK command, or we don't know where we are yet,
    # set current room.
    if ($move->{LOOK} || !$here) {
	$here = &newroom($line, $name, $desc) unless $here;
	next;
    }

    # Otherwise, assume we moved in some way.  Try to find the new room.
    $there = &findroom($name, $desc);

    # If the new room looks like this one, do nothing.
    next if $there eq $here;

    # Get the movement direction.
    $cmd = $move->{CMD};

    if      ($cdirmap{$cmd}) {
	# Standard compass direction.
	$dir = $cdirmap{$cmd};
	undef $go;
	undef $cmd;
    } elsif ($odirmap{$cmd}) {
	# Other direction.
	$dir = &choosedir($here);
	$go = $odirmap{$cmd};
	undef $cmd;
    } else {
	# Weird direction.
	$dir = &choosedir($here);
	undef $go;
    }

    if (!$there) {
	# Unvisited -- new room.
	$here = &newroom($line, $name, $desc, $dir, $here, $go, $cmd);
    } else {
	# Visited before -- new link.
	&newlink($line, $here, $there, $dir, $go, $cmd);
	$here = $there;
    }
}

### Stage 4 -- Write IFM output.

&verbose(1, "Writing output...");

print "## IFM map created from a transcript by $0\n";

print "\ntitle \"$opt_t\";\n" if $opt_t;

print "\n## Rooms generated by transcript.\n";

foreach $room (@rooms) {
    $name = $room->{NAME};
    $desc = $room->{DESC};
    $line = $room->{LINE};
    $tag = $room->{TAG};
    $dir = $room->{DIR};
    $from = $room->{FROM};
    $go = $room->{GO};
    $cmd = $room->{CMD};

    print "room \"$name\" tag $tag";

    print " dir $dir" if $dir;
    print " from $from" if $from;
    print " go $go" if $go;
    print " cmd \"$cmd\"" if $cmd;

    print ";";
    print " # Line $line" if $opt_l;
    print "\n";

    print $desc if $opt_d && $desc;
}

print "\n## Extra links generated by transcript.\n" if @links > 0;

foreach $link (@links) {
    $from = $link->{FROM};
    $to = $link->{TO};
    $tag = $link->{TAG};
    $line = $link->{LINE};
    $dir = $link->{DIR};
    $go = $link->{GO};
    $cmd = $link->{CMD};

    print "link $from to $to";
    print " tag $tag" if $tag;
    print " dir $dir" if $dir;
    print " go $go" if $go;
    print " cmd \"$cmd\"" if $cmd;

    print ";";
    print " # Line $line" if $opt_l;
    print "\n";
}

if (@ifmcmds > 0) {
    print "\n## Customization commands.\n";
    print @ifmcmds;
}

# Return whether a text line looks like a room name.
sub roomname {
    my $line = shift;

    # Quick check for invalid format.
    return 0 if $line =~ /$name_invalid/o;

    # Check word count.
    my @words = split(' ', $line);
    return 0 if @words > $name_maxwords;

    # Check uncapitalized words.
    for (@words) {
	return 0 if /^[a-z]/ && length() > $name_maxuncap;
    }

    return 1;
}

# Add a new room to the room list.
sub newroom {
    my ($line, $name, $desc, $dir, $from, $go, $cmd) = @_;
    my $tag = &maketag($name);

    my $room = {};
    push(@rooms, $room);

    $room->{NAME} = $name;
    $room->{DESC} = $desc;
    $room->{LINE} = $line;
    $room->{WORDS} = [ split(' ', $desc) ];
    $room->{TAG} = $tag;

    $room->{DIR} = $dir if $dir;
    $room->{FROM} = $from if $from;
    $room->{GO} = $go if $go;
    $room->{CMD} = $cmd if $cmd;

    $roommap{$tag} = $room;

    if ($from && $dir) {
	&moveroom($from, $dir);
	$roommap{$from}{$dir} = $tag;
	$linkmap{$from}{$tag} = $room;
    }

    return $tag;
}

# Add a new link to the link list if required.
sub newlink {
    my ($line, $from, $to, $dir, $go, $cmd) = @_;
    my $link;

    if ($link = $linkmap{$from}{$to}) {
	# Link this way exists already -- do nothing.
    } elsif ($link = $linkmap{$to}{$from}) {
	# Opposite link exists -- see if it needs modifying.
	unless ($link->{MODIFIED}++) {
	    my $odir = $link->{DIR};
	    my $rdir = $rdirmap{$dir};
	    $link->{DIR} .= " " . $rdir
		unless $rdir eq $odir || $link->{GO} || $go;
	    $link->{GO} = $rdirmap{$go} if $go && !$link->{GO};
	    $link->{CMD} = $go if $cmd && !$link->{CMD};
	}
    } else {
	# No link exists -- create new one.
	$link = {};
	push(@links, $link);

	$link->{FROM} = $from;
	$link->{TO} = $to;
	$link->{TAG} = $from . "_" . $to;
	$link->{LINE} = $line;
	$link->{DIR} = $dir if $dir;
	$link->{GO} = $go if $go;
	$link->{CMD} = $cmd if $cmd;

	&moveroom($from, $dir);
	$roommap{$from}{$dir} = $to;
	$linkmap{$from}{$to} = $link;
    }
}

# Find a room and return its tag given a name and description.
sub findroom {
    my ($name, $desc) = @_;
    my ($score, $best, $bestscore);
    my (@words, $match, $room, $i);

    foreach $room (@rooms) {
	undef $score;

	if ($desc) {
	    # We have a description -- try exact match first.
	    $score += 10 if $room->{DESC} eq $desc;

	    # Try substring match.
	    $score += 5 if index($room->{DESC}, $desc) >= 0;

	    # If still no luck, try first N words.
	    unless ($score) {
		$match = 1;
		@words = split(' ', $desc) unless @words;

		foreach $i (1 .. $desc_minwords) {
		    if ($words[$i] ne $room->{WORDS}->[$i]) {
			undef $match;
			last;
		    }
		}

		$score += 2 if $match;
	    }
	} else {
	    # Just the name -- not so good.
	    $score += 1 if $room->{NAME} eq $name;
	}

	next if $score <= $bestscore;
	$bestscore = $score;
	$best = $room->{TAG};
    }

    return $best;
}

# Move an up/down/in/out room if required.
sub moveroom {
    my ($from, $dir) = @_;

    # Check there's a room there.
    my $to = $roommap{$from}{$dir};
    return unless $to;

    # Check it's up/down/in/out.
    my $room = $roommap{$to};
    if ($room->{GO}) {
	# Put room in another direction.
	$dir = &choosedir($from);
	$roommap{$from}{$dir} = $to;
	$room->{DIR} = $dir;
    } else {
	# Warn about identical exits.
	$room = $roommap{$from};
	&warning("room `%s' has multiple exits (%s)",
		 $room->{NAME}, uc $dir);
    }
}

# Choose a direction to represent up/down/in/out.
sub choosedir {
    my $room = shift;
    my ($best, $bestscore, $score, $rdir, $dir);

    foreach $dir (@dirlist) {
	$rdir = $rdirmap{$dir};

	$score = 0;
	$score++ unless $roommap{$room}{$dir};
	$score++ unless $roommap{$room}{$rdir};
	next if defined $bestscore && $score <= $bestscore;

	$bestscore = $score;
	$best = $dir;
    }

    &warning("no up/down/in/out direction left for room `%s'",
	     $room->{NAME}) unless $bestscore;

    return $best;
}

# Make a room tag from its name.
sub maketag {
    my $name = shift;
    my $prefix;

    # Build prefix from initials of capitalized words.
    for (split(' ', $name)) {
	$prefix .= $1 if /^([A-Z])/;
    }

    # Make it unique.
    my $tag = $prefix;
    my $num = 1;
    while ($tagused{$tag}) {
	$tag = $prefix . ++$num;
    }

    $tagused{$tag}++;
    return $tag;
}

# Print a verbose message.
sub verbose {
    return unless $opt_v;

    my $level = shift;
    my $fmt = shift;

    print STDERR "   " x ($level - 1) if $level;
    printf STDERR $fmt, @_;
    print STDERR "\n";
}

# Print a warning.
sub warning {
    return if $opt_w;

    my $fmt = shift;
    print STDERR "$0: warning: ";
    printf STDERR $fmt, @_;
    print STDERR "\n";
}

# Print an error and exit.
sub error {
    my $fmt = shift;
    print STDERR "$0: error: ";
    printf STDERR $fmt, @_;
    print STDERR "\n";
    exit 1;
}

# Print a usage message and exit.
sub usage {
    print "Usage: $0 [options] [file]\n";
    print "   -t title       add a title\n";
    print "   -c file        add ifm commands from file\n";
    print "   -o file        write to given file\n";
    print "   -l             print line number comments\n";
    print "   -d             print room description comments\n";
    print "   -v             be verbose about things\n";
    print "   -w             don't print warnings\n";

    exit 0;
}
