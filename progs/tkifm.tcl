# Tkifm, copyright (C) 1997-98 G. Hutchings
# TkIfm comes with ABSOLUTELY NO WARRANTY.
# This is free software, and you are welcome to redistribute it
# under certain conditions; see the file COPYING for details.

# Global variables (internal).
set ifm(version) 1.0
set ifm(edit)    1

set ifm(mapcmd)   {ifm -map -format tk}
set ifm(itemcmd)  {ifm -items -format tk}
set ifm(taskcmd)  {ifm -tasks -format tk}
set ifm(debugcmd) {ifm -debug -format tk}
set ifm(printcmd) {ifm -map -format ps}
set ifm(aboutcmd) {ifm -version}

# Global variables (customizable).
set ifm(editwidth)      80
set ifm(editheight)     24
set ifm(editfont)       {Courier 12 bold}
set ifm(editforeground) black
set ifm(editbackground) wheat

set ifm(itemwidth)      50
set ifm(itemheight)     30

set ifm(taskwidth)      50
set ifm(taskheight)     30

set ifm(debugwidth)     80
set ifm(debugheight)    30

set ifm(textfont)       {Times 12 bold}
set ifm(textforeground) black
set ifm(textbackground) wheat

set ifm(roomitemratio) 0.5

set ifm(untitled) "untitled.ifm"
set ifm(ifmfiles) {{"IFM files" {.ifm}} {"All files" *}}
set ifm(psfiles)  {{"PostScript files" {.ps}} {"All files" *}}
set ifm(tearoff)  1

# Set up the main window.
proc MainWindow {} {
    global ifm

    wm protocol . WM_DELETE_WINDOW Quit

    set m .menu
    menu $m

    # File options.
    set c $m.file
    menu $c -tearoff $ifm(tearoff)
    $m add cascade -label "File" -menu $c -underline 0

    if $ifm(edit) {
	$c add command -label "New" -command New -underline 0
    }

    $c add command -label "Open..." -command Open -underline 0

    if $ifm(edit) {
	$c add command -label "Save"       -command Save   -underline 0
	$c add command -label "Save As..." -command SaveAs -underline 5
    }

    $c add command -label "Print..."   -command Print  -underline 0
    $c add separator
    $c add command -label "Redraw"     -command Redraw -underline 0
    $c add separator
    $c add command -label "Quit"       -command Quit   -underline 0

    # Map options.
    set c $m.sect
    menu $c -tearoff $ifm(tearoff)
    $m add cascade -label "Map" -menu $c -underline 0
    set ifm(mapmenu) $m.sect

    # Item options.
    set c $m.items
    menu $c -tearoff $ifm(tearoff)
    $m add cascade -label "Items" -menu $c -underline 0
    $c add command -label "Item list" -command ShowItems -underline 0

    # Task options.
    set c $m.tasks
    menu $c -tearoff $ifm(tearoff)
    $m add cascade -label "Tasks" -menu $c -underline 0
    $c add command -label "Task list" -command ShowTasks -underline 0

    # Debug options.
    set c $m.debug
    menu $c -tearoff $ifm(tearoff)
    $m add cascade -label "Debug" -menu $c -underline 0
    $c add command -label "Debugging output" -command ShowDebug -underline 0

    # Help options.
    set c $m.help
    menu $c -tearoff $ifm(tearoff)
    $m add cascade -label "Help" -menu $c -underline 0
    $c add command -label "About" -command About -underline 0

    # Configure menu.
    . configure -menu $m

    # Set up editing box.
    frame .edit
    set t .edit.text
    set s .edit.scroll
    set ifm(text) $t

    text $t -yscrollcommand "$s set" -setgrid true \
	    -width $ifm(editwidth) -height $ifm(editheight) \
	    -wrap word -font $ifm(editfont) -fg $ifm(editforeground) \
	    -bg $ifm(editbackground) -insertofftime 0 \
	    -insertbackground red

    bind $t <3> "$t scan mark %x %y"
    bind $t <B3-Motion> "$t scan dragto %x %y"

    scrollbar $s -command "$t yview"

    pack .edit -expand yes -fill both
    pack $s -side right -fill y
    pack $t -expand yes -fill both

    if $ifm(edit) {
	focus $ifm(text)
    }
}

# Draw a map section.
proc DrawMap {num} {
    global ifm rooms links exits
    global sectnum

    if {[MaybeSave] == 0} return
    if {[MaybeRead] == 0} return

    if {$num > $sectnum} {
	Message "Map section no longer exists!"
	return
    }

    Busy

    # Get attributes.
    set sect sect$num
    set title [Get $sect title]
    set xlen [Get $sect xlen]
    set ylen [Get $sect ylen]

    # Calculate dimensions.
    set width [expr $ifm(roomsize) * $xlen]
    set height [expr $ifm(roomsize) * $ylen]
    set xgap [expr ($ifm(roomsize) * (1 - $ifm(roomwidth))) / 2]
    set ygap [expr ($ifm(roomsize) * (1 - $ifm(roomheight))) / 2]

    set mapwidth [expr $ifm(mapwidth) * $ifm(roomsize)]
    if {$mapwidth > $width} {set mapwidth $width}
    set mapheight [expr $ifm(mapheight) * $ifm(roomsize)]
    if {$mapheight > $height} {set mapheight $height}

    # Initialise window.
    set w .$sect
    catch {destroy $w}
    toplevel $w
    wm title $w $title

    # Set up canvas.
    set f $w.frame
    frame $f
    pack $f -fill both -expand yes

    set c $f.map
    canvas $c -width ${mapwidth}c -height ${mapheight}c \
	    -scrollregion "0 0 ${width}c ${height}c" \
	    -xscrollcommand "$f.xscroll set" \
	    -yscrollcommand "$f.yscroll set" \
	    -relief sunken -bd 2 \
	    -bg $ifm(mapcol)
    scrollbar $f.xscroll -command "$c xview" -orient horiz
    scrollbar $f.yscroll -command "$c yview"

    bind $c <3> "$c scan mark %x %y"
    bind $c <B3-Motion> "$c scan dragto %x %y"

    grid $c -in $f -row 0 -column 0 \
	    -rowspan 1 -columnspan 1 -sticky nsew
    grid $f.xscroll -in $f -row 1 -column 0 \
	    -rowspan 1 -columnspan 1 -sticky nsew
    grid $f.yscroll -in $f -row 0 -column 1 \
	    -rowspan 1 -columnspan 1 -sticky nsew

    grid rowconfig    $f 0 -weight 1 -minsize 0
    grid columnconfig $f 0 -weight 1 -minsize 0

    # Draw rooms.
    foreach room $rooms {
	if {[Get $room sect] == $sect} {
	    set desc [Get $room desc]
	    set xoff [Get $room xpos]
	    set yoff [Get $room ypos]
	    set yoff [expr $ylen - 1 - $yoff]
	    set puzzle [Get $room puzzle]
	    set items [Get $room items]

	    if {$ifm(roomshadow) > 0} {
		set soff [expr $ifm(roomsize) * $ifm(roomshadow)]
		set xmin [expr $xoff * $ifm(roomsize) + $xgap - $soff]
		set ymin [expr $yoff * $ifm(roomsize) + $ygap + $soff]
		set xmax [expr $xmin + $ifm(roomsize) * $ifm(roomwidth)]
		set ymax [expr $ymin + $ifm(roomsize) * $ifm(roomheight)]

		$c create rectangle ${xmin}c ${ymin}c ${xmax}c ${ymax}c \
			-width $ifm(roomlinewidth) -outline $ifm(shadowcol) \
			-fill $ifm(shadowcol)
	    }

	    set xmin [expr $xoff * $ifm(roomsize) + $xgap]
	    set ymin [expr $yoff * $ifm(roomsize) + $ygap]
	    set xmax [expr $xmin + $ifm(roomsize) * $ifm(roomwidth)]
	    set ymax [expr $ymin + $ifm(roomsize) * $ifm(roomheight)]

	    set fillcol $ifm(roomcol)
	    if {$puzzle} {set fillcol $ifm(puzzlecol)}

	    $c create rectangle ${xmin}c ${ymin}c ${xmax}c ${ymax}c \
		    -width $ifm(roomlinewidth) -outline $ifm(bordercol) \
		    -fill $fillcol

	    set xc [expr ($xmin + $xmax) / 2]
	    set yc [expr ($ymin + $ymax) / 2]
	    set wid [expr ($xmax - $xmin) * 0.9]

	    if {$ifm(showitems) && $items != ""} {
		set fac $ifm(roomitemratio)

		set yo [expr $ifm(roomsize) * $ifm(roomheight) * $fac / 2]
		$c create text ${xc}c [expr $yc - $yo]c -text $desc \
			-width ${wid}c -justify center -font $ifm(roomfont) \
			-fill $ifm(roomtextcol)

		set yo [expr $ifm(roomsize) * $ifm(roomheight) * (1 - $fac) / 2]
		$c create text ${xc}c [expr $yc + $yo]c -text $items \
			-width ${wid}c -justify center -font $ifm(itemfont) \
			-fill $ifm(itemcol)
	    } else {
		$c create text ${xc}c ${yc}c -text $desc \
			-width ${wid}c -justify center -font $ifm(roomfont) \
			-fill $ifm(roomtextcol)
	    }
	}
    }

    # Draw room exits.
    foreach exit $exits {
	if {[Get $exit sect] == $sect} {
	    set coords [Truncate $exit $ifm(roomwidth) $ifm(roomheight)]
	    set xlist [lindex $coords 0]
	    set ylist [lindex $coords 1]

	    set x1 [lindex $xlist 0]
	    set y1 [lindex $ylist 0]
	    set y1 [expr $ylen - 1 - $y1]

	    set x3 [lindex $xlist 1]
	    set y3 [lindex $ylist 1]
	    set y3 [expr $ylen - 1 - $y3]

	    set fac 0.35
	    set x2 [expr $x1 + ($x3 - $x1) * $fac]
	    set y2 [expr $y1 + ($y3 - $y1) * $fac]

	    set cmd "$c create line"

	    set x1 [expr ($x1 + 0.5) * $ifm(roomsize)]
	    set y1 [expr ($y1 + 0.5) * $ifm(roomsize)]
	    lappend cmd ${x1}c ${y1}c

	    set x2 [expr ($x2 + 0.5) * $ifm(roomsize)]
	    set y2 [expr ($y2 + 0.5) * $ifm(roomsize)]
	    lappend cmd ${x2}c ${y2}c

	    lappend cmd -width $ifm(exitwidth) -fill $ifm(exitcol)
	    eval $cmd
	}
    }

    # Draw links.
    foreach link $links {
	if {[Get $link sect] == $sect} {
	    set coords [Truncate $link $ifm(roomwidth) $ifm(roomheight)]
	    set xlist [lindex $coords 0]
	    set ylist [lindex $coords 1]

	    set updown [Get $link updown]
	    set inout [Get $link inout]
	    set oneway [Get $link oneway]
	    set special [Get $link special]

	    set cmd "$c create line"
	    for {set i 0} {$i < [llength $xlist]} {incr i} {
		if {$i > 0} {
		    set xlast $x
		    set ylast $y
		}

		set xoff [lindex $xlist $i]
		set yoff [lindex $ylist $i]
		set yoff [expr $ylen - 1 - $yoff]
		set x [expr ($xoff + 0.5) * $ifm(roomsize)]
		set y [expr ($yoff + 0.5) * $ifm(roomsize)]
		lappend cmd ${x}c ${y}c
	    }

	    if {$oneway} {lappend cmd -arrow last}

	    if {$special} {
		lappend cmd -fill $ifm(linkspecialcol)
	    } else {
		lappend cmd -fill $ifm(linkcol)
	    }

	    lappend cmd -width $ifm(linkwidth) -smooth $ifm(linkspline)
	    eval $cmd

	    if {$updown || $inout} {
		set xmid [expr ($x + $xlast) / 2]
		set ymid [expr ($y + $ylast) / 2]

		if {$updown} {
		    set text $ifm(linkupdown)
		} else {
		    set text $ifm(linkinout)
		}

		$c create text ${xmid}c ${ymid}c -text $text \
			-font $ifm(linkfont) -fill $ifm(linktextcol)
	    }
	}
    }

    # Add 'dismiss' button.
    set b $w.bye
    button $b -text "Dismiss" -command "destroy $w"
    pack $b -fill x

    Unbusy
}

# Show item list.
proc ShowItems {} {
    global ifm

    if [file exists $ifm(path)] {
	if {[MaybeSave] == 0} return
	if {[MaybeRead] == 0} return
    } else {
	Message "You must save the current file first."
	return
    }

    # Get item data.
    Busy
    set result [RunProgram $ifm(itemcmd) $ifm(path)]
    if [lindex $result 0] {
	set data [lindex $result 1]
    } else {
	Unbusy
	Error [lindex $result 2]
	return
    }

    # Display results.
    eval $data
    if {$itemlist != ""} {
	TextWindow "Items" .items $itemlist $ifm(itemwidth) $ifm(itemheight)
    } else {
	Message "No items found"
    }

    Unbusy
}

# Show task list.
proc ShowTasks {} {
    global ifm

    if [file exists $ifm(path)] {
	if {[MaybeSave] == 0} return
	if {[MaybeRead] == 0} return
    } else {
	Message "You must save the current file first."
	return
    }

    # Get task data.
    Busy

    set result [RunProgram $ifm(taskcmd) $ifm(path)]
    if [lindex $result 0] {
	set data [lindex $result 1]
    } else {
	Unbusy
	Error [lindex $result 2]
	return
    }

    # Display results.
    eval $data
    if {$tasklist != ""} {
	TextWindow "Tasks" .tasks $tasklist $ifm(taskwidth) $ifm(taskheight)
    } else {
	Message "No tasks found"
    }

    Unbusy
}

# Show debugging output.
proc ShowDebug {} {
    global ifm

    if [file exists $ifm(path)] {
	if {[MaybeSave] == 0} return
	if {[MaybeRead] == 0} return
    } else {
	Message "You must save the current file first."
	return
    }

    # Get task data.
    Busy

    set result [RunProgram $ifm(debugcmd) $ifm(path)]
    if [lindex $result 0] {
	set data [lindex $result 1]
    } else {
	Unbusy
	Error [lindex $result 2]
	return
    }

    # Display results.
    TextWindow "Debugging Output" .debug $data \
	    $ifm(debugwidth) $ifm(debugheight)

    Unbusy
}

# Display a text window.
proc TextWindow {title w text width height} {
    global ifm

    # Initialise window.
    catch {destroy $w}
    toplevel $w
    wm title $w $title

    # Set up text.
    set t $w.text
    set s $w.scroll
    text $t -yscrollcommand "$s set" -setgrid true \
	    -width $width -height $height \
	    -wrap word -font $ifm(textfont) -fg $ifm(textforeground) \
	    -bg $ifm(textbackground)
    scrollbar $s -command "$t yview"

    pack $s -side right -fill y
    pack $t -expand yes -fill both

    $t insert end $text
    $t configure -state disabled

    bind $t <3> "$t scan mark %x %y"
    bind $t <B3-Motion> "$t scan dragto %x %y"

    # Add 'dismiss' button.
    set b $w.bye
    button $b -text "Dismiss" -command "destroy $w"
    pack $b -fill x
}

# Build the map.
proc BuildMap {} {
    global sectnum roomnum linknum exitnum
    global sects rooms links exits
    global ifm

    # Get map data.
    set result [RunProgram $ifm(mapcmd) $ifm(path)]
    if [lindex $result 0] {
	set data [lindex $result 1]
    } else {
	Error [lindex $result 2]
	return
    }

    # Remove old windows.
    if [info exists sects] {
	foreach sect $sects {catch {destroy .$sect}}
    }

    catch {destroy .items}
    catch {destroy .tasks}

    # Set up new maps.
    set sects {}
    set rooms {}
    set links {}
    set exits {}

    set sectnum 0
    set roomnum 0
    set linknum 0
    set exitnum 0

    eval $data

    # Reconfigure map menu.
    set c $ifm(mapmenu)
    $c delete 0 end

    for {set i 1} {$i <= $sectnum} {incr i} {
	$c add command -label [Get sect$i title] -command "DrawMap $i"
    }
}

# Read IFM source.
proc ReadFile {file} {
    global ifm
	
    Busy
    SetFile $file

    if [file exists $file] {
	if [catch {set fd [open $file r]}] {
	    Unbusy
	    Error "Can't open $file"
	    return
	}

	set ifm(data) [read -nonewline $fd]
	close $fd

	$ifm(text) configure -state normal
	$ifm(text) delete 0.0 end
	$ifm(text) insert end $ifm(data)

	if !$ifm(edit) {
	    $ifm(text) configure -state disabled
	}

	append ifm(data) "\n"
	set ifm(modtime) [file mtime $file]

	GotoLine 1
	BuildMap
    }

    Unbusy
}

# Set the current input pathname.
proc SetFile {path} {
    global ifm

    regsub {^\./} $path {} path

    set ifm(dir)  [file dirname $path]
    set ifm(file) [file tail $path]
    set ifm(path) $path
    set ifm(data) "\n"

    wm iconname . $ifm(file)

    if $ifm(edit) {
	wm title . $ifm(file)
    } else {
	wm title . "$ifm(file) (read-only)"
    }
}

# Add a section.
proc AddSect {title xlen ylen} {
    global sects sectnum
    incr sectnum
    set var sect$sectnum
    lappend sects $var

    Set $var num $sectnum
    Set $var title $title
    Set $var xlen $xlen
    Set $var ylen $ylen
}

# Add a room.
proc AddRoom {desc items xpos ypos puzzle} {
    global rooms roomnum sectnum
    incr roomnum
    set var room$roomnum
    lappend rooms $var

    Set $var num $roomnum
    Set $var desc $desc
    Set $var items $items
    Set $var xpos $xpos
    Set $var ypos $ypos
    Set $var puzzle $puzzle

    Set $var sect sect$sectnum
}

# Add a link.
proc AddLink {xlist ylist updown inout oneway special} {
    global links linknum sectnum
    incr linknum
    set var link$linknum
    global $var
    lappend links $var

    Set $var num $linknum
    Set $var xlist $xlist
    Set $var ylist $ylist
    Set $var updown $updown
    Set $var inout $inout
    Set $var oneway $oneway
    Set $var special $special

    Set $var sect sect$sectnum
}

# Add a room exit.
proc AddExit {xlist ylist} {
    global exits exitnum sectnum
    incr exitnum
    set var exit$exitnum
    global $var
    lappend exits $var

    Set $var num $exitnum
    Set $var xlist $xlist
    Set $var ylist $ylist

    Set $var sect sect$sectnum
}

# Start a new file.
proc New {} {
    global ifm

    if {[MaybeSave] == 0} return
    SetFile [file join $ifm(dir) $ifm(untitled)]
    $ifm(text) delete 0.0 end
    set ifm(data) ""

    GotoLine 1
}

# Open a file and parse it.
proc Open {} {
    global ifm

    if {[MaybeSave] == 0} return
    set file [tk_getOpenFile -filetypes $ifm(ifmfiles) -initialdir $ifm(dir)]
    if [string length $file] {ReadFile $file}
}

# Save the current file.
proc Save {} {
    global ifm

    if [catch {set fd [open $ifm(path) w]}] {
	Error "Can't save $file"
	return
    }

    Busy
    set ifm(data) [$ifm(text) get 0.0 end]
    puts -nonewline $fd $ifm(data)
    close $fd

    set ifm(modtime) [file mtime $ifm(path)]

    BuildMap
    Unbusy
}

# Save current file under another name.
proc SaveAs {} {
    global ifm

    set file [tk_getSaveFile -initialfile $ifm(path) -initialdir $ifm(dir) \
	    -filetypes $ifm(ifmfiles)]

    if [string length $file] {
	SetFile $file
	Save
    }
}

# Print current file to PostScript.
proc Print {} {
    global ifm

    if [file exists $ifm(path)] {
	if {[MaybeSave] == 0} return
	if {[MaybeRead] == 0} return
    } else {
	Message "You must save the current file first."
	return
    }

    # Get save filename.
    set root [file rootname $ifm(file)]
    set file [tk_getSaveFile -initialfile ${root}.ps -initialdir $ifm(dir) \
	    -filetypes $ifm(psfiles) -title "Save PostScript"]
    if {$file == ""} return

    # Get PostScript data.
    Busy

    set result [RunProgram $ifm(printcmd) $ifm(path)]
    if [lindex $result 0] {
	set data [lindex $result 1]
    } else {
	Unbusy
	Error [lindex $result 2]
	return
    }

    # Write file.
    if [catch {set fd [open $file w]}] {
	Unbusy
	Error "Can't save $file"
	return
    }

    puts $fd $data
    close $fd

    Unbusy
}

# Save current file if required.
proc MaybeSave {} {
    global ifm

    if [Modified] {
	set reply [Yesno "$ifm(path) has been modified.  Save it?" "yes"]
	if {$reply == "cancel"} {return 0}
	if {$reply == "yes"} Save
    }

    return 1
}

# Reread current file if required.
proc MaybeRead {} {
    global ifm

    if [file exists $ifm(path)] {
	if {[file mtime $ifm(path)] > $ifm(modtime)} {
	    ReadFile $ifm(path)
	}
    }

    return 1
}

# Redraw the map.
proc Redraw {} {
    global ifm

    if [file exists $ifm(path)] {
	if {[MaybeSave] == 0} return
	Busy
	BuildMap
	Unbusy
    } else {
	Message "You must save the current file first."
    }
}

# Quit.
proc Quit {} {
    if [MaybeSave] {destroy .}
}

# Display info about program.
proc About {} {
    global ifm

    set result [RunProgram $ifm(aboutcmd)]
    if [lindex $result 0] {
	set text [lindex $result 1]
    } else {
	Error [lindex $result 2]
	return
    }

    Message $text
}

# Run a program and return its results.
proc RunProgram {prog args} {
    global ifm

    set result {}
    set errmsg {}
    set err [catch {set result [eval exec $prog $args]} errmsg]

    return [list [expr !$err] $result $errmsg]
}

# Return whether source has been modified.
proc Modified {} {
    global ifm
    set curdata [$ifm(text) get 0.0 end]
    if {$ifm(data) != $curdata} {return 1}
    return 0
}

# Go to a text line.
proc GotoLine {num} {
    global ifm
    $ifm(text) mark set insert "$num.0"
    $ifm(text) see insert
}

# Truncate links to join on to boxes properly.
proc Truncate {link wid ht} {
    set x [Get $link xlist]
    set y [Get $link ylist]
    set xfac [expr 1 - $wid / 2]
    set yfac [expr 1 - $ht / 2]
    set np [llength $x]

    # Truncate first point.
    set x1 [lindex $x 1]
    set y1 [lindex $y 1]
    set x2 [lindex $x 0]
    set y2 [lindex $y 0]
    set xf [expr $x1 + $xfac * ($x2 - $x1)]
    set yf [expr $y1 + $yfac * ($y2 - $y1)]

    # Truncate last point.
    set x1 [lindex $x [expr $np - 2]]
    set y1 [lindex $y [expr $np - 2]]
    set x2 [lindex $x [expr $np - 1]]
    set y2 [lindex $y [expr $np - 1]]
    set xl [expr $x1 + $xfac * ($x2 - $x1)]
    set yl [expr $y1 + $yfac * ($y2 - $y1)]

    # Replace points.
    set x [lreplace $x 0 0 $xf]
    set x [lreplace $x end end $xl]
    set y [lreplace $y 0 0 $yf]
    set y [lreplace $y end end $yl]

    return [list $x $y]
}

# Set busy state.
proc Busy {} {
    global ifm
    set ifm(oldcursor) [$ifm(text) cget -cursor]
    $ifm(text) configure -cursor watch
    update idletasks
}

# Set unbusy state.
proc Unbusy {} {
    global ifm
    $ifm(text) configure -cursor $ifm(oldcursor)
    update idletasks
}

# Ask a yes/no question.
proc Yesno {question default} {
    tk_messageBox -message $question -type yesnocancel \
	    -default $default -icon question
}

# Print a message.
proc Message {message} {
    tk_messageBox -message $message -type ok \
	    -default ok -icon info
}

# Print a warning.
proc Warning {message} {
    tk_messageBox -message $message -type ok \
	    -default ok -title "Scary!" -icon warning
}

# Print an error.
proc Error {message} {
    bell
    tk_messageBox -message $message -type ok \
	    -default ok -title "Oops!" -icon error
}

# Set a variable reference.
proc Set {var attr val} {
    global $var
    set ${var}($attr) $val
}

# Return value of a variable reference.
proc Get {var attr} {
    global $var
    return [set ${var}($attr)]
}

# Allow customizations.
if {$tcl_platform(platform) == "unix"} {
    set rcname ".tkifmrc"
} else {
    set rcname "tkifm.ini"
}

set rcfile [file join $env(HOME) $rcname]
if [file readable $rcfile] {source $rcfile}

if {$tcl_platform(platform) == "unix"} {
    option add *Dialog.msg.wrapLength 10i
}

# Boot up.
MainWindow

# Parse arguments.
if {$argc == 1} {
    ReadFile [lindex $argv 0]
} else {
    SetFile $ifm(untitled)
}
