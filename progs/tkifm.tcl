# Tkifm version 1.0, Copyright (C) 1997 G. Hutchings
# TkIfm comes with ABSOLUTELY NO WARRANTY.
# This is free software, and you are welcome to redistribute it
# under certain conditions; see the file COPYING for details.

# Global variables.
set ifm(mapcmd)  {ifm -map   -format tk}
set ifm(itemcmd) {ifm -items -format text}
set ifm(taskcmd) {ifm -tasks -format text}

set ifm(editwidth) 80
set ifm(editheight) 24
set ifm(editfont) {Courier 12 bold}

set ifm(textwidth) 50
set ifm(textheight) 20
set ifm(textfont) {Times 12 bold}

set ifm(file) "untitled.ifm"
set ifm(path) "untitled.ifm"
set ifm(filetypes) {{"IFM files" {.ifm}} {"All files" *}}
set ifm(compiled) ""

# Set up the main window.
proc MainWindow {file} {
    global ifm sects

    wm protocol . WM_DELETE_WINDOW Quit

    set m .menu
    menu $m

    # File options.
    set c $m.file
    menu $c
    $m add cascade -label "File" -menu $c -underline 0
    $c add command -label "Open..."    -command Open   -underline 0
    $c add command -label "Save"       -command Save   -underline 0
    $c add command -label "Save As..." -command SaveAs -underline 5
    $c add separator
    $c add command -label "Redraw"     -command Redraw -underline 0
    $c add separator
    $c add command -label "Quit"       -command Quit   -underline 0

    # Map options.
    set c $m.sect
    menu $c
    $m add cascade -label "Map" -menu $c -underline 0
    set ifm(mapmenu) $m.sect

    # Item options.
    set c $m.items
    menu $c
    $m add cascade -label "Items" -menu $c -underline 0
    $c add command -label "Item list" -command ShowItems -underline 0

    # Task options.
    set c $m.tasks
    menu $c
    $m add cascade -label "Tasks" -menu $c -underline 0
    $c add command -label "Task list" -command ShowTasks -underline 0

    # Configure menu.
    . configure -menu $m

    # Set up editing box.
    frame .edit
    pack .edit -expand yes -fill both
    set t .edit.text
    set s .edit.scroll

    text $t -yscrollcommand "$s set" -setgrid true \
	    -width $ifm(editwidth) -height $ifm(editheight) \
	    -wrap word -font $ifm(editfont)

    scrollbar $s -command "$t yview"
    pack $s -side right -fill y
    pack $t -expand yes -fill both
    set ifm(text) $t

    # Read input.
    if {$file != ""} {
	Input $file
	Compile $file
    }

    focus .
}

# Draw a map section.
proc DrawMap {sect} {
    global ifm rooms links

    InitMap

    # Get attributes.
    set title [Get $sect title]
    set xlen [Get $sect xlen]
    set ylen [Get $sect ylen]

    # Calculate dimensions.
    set width [expr $ifm(framewidth) * $xlen]
    set height [expr $ifm(frameheight) * $ylen]
    set xgap [expr ($ifm(framewidth) * (1 - $ifm(roomwidth))) / 2]
    set ygap [expr ($ifm(frameheight) * (1 - $ifm(roomheight))) / 2]

    set mapwidth [expr $ifm(mapwidth) * $ifm(framewidth)]
    if {$mapwidth > $width} {set mapwidth $width}
    set mapheight [expr $ifm(mapheight) * $ifm(frameheight)]
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
	    -relief sunken \
	    -bg $ifm(mapcol)
    scrollbar $f.xscroll -command "$c xview" -orient horiz
    scrollbar $f.yscroll -command "$c yview"

    bind $c <2> "$c scan mark %x %y"
    bind $c <B2-Motion> "$c scan dragto %x %y"

    grid $c -in $f -row 0 -column 0 \
	    -rowspan 1 -columnspan 1 -sticky nsew
    grid $f.xscroll -in $f -row 1 -column 0 \
	    -rowspan 1 -columnspan 1 -sticky nsew
    grid $f.yscroll -in $f -row 0 -column 1 \
	    -rowspan 1 -columnspan 1 -sticky nsew

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
		set x [expr ($xoff + 0.5) * $ifm(framewidth)]
		set y [expr ($yoff + 0.5) * $ifm(frameheight)]
		lappend cmd ${x}c ${y}c
	    }

	    if {$oneway} {lappend cmd -arrow last}
	    if {$special} {lappend cmd -fill $ifm(specialcol)}

	    lappend cmd -width $ifm(linklinewidth) -smooth $ifm(curvelines)
	    eval $cmd

	    if {$updown || $inout} {
		set xmid [expr ($x + $xlast) / 2]
		set ymid [expr ($y + $ylast) / 2]

		if {$updown} {
		    set text "U/D"
		} else {
		    set text "I/O"
		}

		$c create text ${xmid}c ${ymid}c -text $text \
			-font $ifm(labelfont) -fill $ifm(labelcol)
	    }
	}
    }

    # Draw rooms.
    foreach room $rooms {
	if {[Get $room sect] == $sect} {
	    set desc [Get $room desc]
	    set xoff [Get $room xpos]
	    set yoff [Get $room ypos]
	    set yoff [expr $ylen - 1 - $yoff]
	    set puzzle [Get $room puzzle]

	    set xmin [expr $xoff * $ifm(framewidth) + $xgap]
	    set ymin [expr $yoff * $ifm(frameheight) + $ygap]
	    set xmax [expr $xmin + $ifm(framewidth) * $ifm(roomwidth)]
	    set ymax [expr $ymin + $ifm(frameheight) * $ifm(roomheight)]

	    set fillcol white
	    if {$puzzle} {set fillcol $ifm(puzzlecol)}

	    $c create rectangle ${xmin}c ${ymin}c ${xmax}c ${ymax}c \
		    -width $ifm(roomlinewidth) -fill $fillcol

	    set xc [expr ( $xmin + $xmax ) / 2]
	    set yc [expr ( $ymin + $ymax ) / 2]
	    set wid [expr ( $xmax - $xmin ) * 0.9]

	    $c create text ${xc}c ${yc}c -text $desc \
		    -width ${wid}c -justify center -font $ifm(roomfont)
	}
    }

    focus $w
}

# Show item list.
proc ShowItems {} {
    global ifm

    # Get item data.
    set result [RunProgram $ifm(itemcmd) $ifm(path)]
    if [lindex $result 0] {
	set data [lindex $result 1]
    } else {
	Error [lindex $result 2]
	return
    }

    # Initialise window.
    set w .items
    catch {destroy $w}
    toplevel $w
    wm title $w "Items"

    # Set up text.
    set t $w.text
    set s $w.scroll
    text $t -yscrollcommand "$s set" -setgrid true \
	    -width $ifm(textwidth) -height $ifm(textheight) \
	    -wrap word -font $ifm(textfont)
    scrollbar $s -command "$t yview"
    pack $s -side right -fill y
    pack $t -expand yes -fill both
    $t insert end $data
    $t configure -state disabled

    focus $w
}

# Show task list.
proc ShowTasks {} {
    global ifm

    # Get task data.
    set result [RunProgram $ifm(taskcmd) $ifm(path)]
    if [lindex $result 0] {
	set data [lindex $result 1]
    } else {
	Error [lindex $result 2]
	return
    }

    # Initialise window.
    set w .tasks
    catch {destroy $w}
    toplevel $w
    wm title $w "Tasks"

    # Set up text.
    set t $w.text
    set s $w.scroll
    text $t -yscrollcommand "$s set" -setgrid true \
	    -width $ifm(textwidth) -height $ifm(textheight) \
	    -wrap word -font $ifm(textfont)
    scrollbar $s -command "$t yview"
    pack $s -side right -fill y
    pack $t -expand yes -fill both
    $t insert end $data
    $t configure -state disabled

    focus $w
}

# Initialise the map.
proc InitMap {} {
    global ifm

    if {$ifm(compiled) == ""} {Compile $ifm(path)}
}

# Read IFM source.
proc Input {file} {
    global ifm

    if [catch {set fd [open $file r]}] {
	Error "Can't open $file"
	return
    }

    set ifm(data) [read -nonewline $fd]
    close $fd
	
    set ifm(file) [file tail $file]
    set ifm(path) $file

    $ifm(text) delete 0.0 end
    $ifm(text) insert end $ifm(data)
    append ifm(data) "\n"

    set ifm(compiled) ""

    wm iconname . $ifm(file)
    wm title . $ifm(file)
}

# Compile IFM source.
proc Compile {file} {
    global sectnum roomnum linknum joinnum itemnum tasknum
    global sects rooms links joins tasks
    global ifm

    # Get map data.
    set result [RunProgram $ifm(mapcmd) $file]
    if [lindex $result 0] {
	set ifm(compiled) [lindex $result 1]
    } else {
	Error [lindex $result 2]
	return
    }

    # Remove old windows.
    if [info exists sects] {
	foreach sect $sects {
	    catch {destroy .$sect}
	}
    }

    catch {destroy .items}
    catch {destroy .tasks}

    # Set up new maps.
    set sects {}
    set rooms {}
    set links {}
    set joins {}
    set tasks {}

    set sectnum 0
    set roomnum 0
    set linknum 0
    set joinnum 0
    set itemnum 0
    set tasknum 0

    eval $ifm(compiled)

    # Reconfigure map menu.
    set c $ifm(mapmenu)
    $c delete 0 end

    foreach sect $sects {
	$c add command -label [Get $sect title] -command "DrawMap $sect"
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
proc AddRoom {desc xpos ypos puzzle} {
    global rooms roomnum sectnum
    incr roomnum
    set var room$roomnum
    lappend rooms $var

    Set $var num $roomnum
    Set $var desc $desc
    Set $var xpos $xpos
    Set $var ypos $ypos
    Set $var puzzle $puzzle

    Set $var items {}
    Set $var tasks {}

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

# Add a join.
proc AddJoin {from to updown inout oneway} {
    global joins joinnum
    incr joinnum
    set var join$joinnum
    lappend joins $var

    Set $var num $joinnum
    Set $var from room$from
    Set $var to room$to
    Set $var updown $updown
    Set $var inout $inout
    Set $var oneway $oneway
}

# Add an item.
proc AddItem {desc note roomnum hidden} {
    global items itemnum
    incr itemnum
    set var item$itemnum
    lappend items $var

    if {$roomnum > 0} {
	set room room$roomnum
	Set $var room $room
	set list [Get $room items]
	lappend list $var
	Set $room items $list
    } else {
	Set $var room ""
    }

    Set $var num $itemnum
    Set $var desc $desc
    Set $var note $note
    Set $var hidden $hidden
}

# Add a task.
proc AddTask {desc note roomnum score} {
    global tasks tasknum
    incr tasknum
    set var task$tasknum
    lappend tasks $var

    if {$roomnum > 0} {
	set room room$roomnum
	Set $var room $room
	set list [Get $room tasks]
	lappend list $var
	Set $room tasks $list
    } else {
	Set $var room ""
    }

    Set $var num $tasknum
    Set $var desc $desc
    Set $var note $note
    Set $var score $score
}

# Open a file and parse it.
proc Open {} {
    global ifm

    if {[MaybeSave] == 0} return
    set file [tk_getOpenFile -filetypes $ifm(filetypes)]

    if [string length $file] {
	Input $file
	Compile $file
    }
}

# Save the current file.
proc Save {} {
    global ifm

    if [catch {set fd [open $ifm(path) w]}] {
	Error "Can't save $file"
	return
    }

    set ifm(data) [$ifm(text) get 0.0 end]
    puts -nonewline $fd $ifm(data)
    close $fd
}

# Save current file under another name.
proc SaveAs {} {
    global ifm

    set file [tk_getSaveFile -initialfile $ifm(path) \
	    -filetypes $ifm(filetypes)]

    if [string length $file] {
	set ifm(path) $file
	Save
    }
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

# Redraw the map.
proc Redraw {} {
    global ifm

    MaybeSave
    Compile $ifm(path)
}

# Quit.
proc Quit {} {
    global ifm

    if {[MaybeSave] == 0} return
    destroy .
}

# Run a program and return its results.
proc RunProgram {prog args} {
    set result {}
    set msg {}
    set err [catch {set result [eval exec $prog $args]} errmsg]
    set ok [expr !$err]

    return [list $ok $result $errmsg]
}

# Return whether source has been modified.
proc Modified {} {
    global ifm
    set curdata [$ifm(text) get 0.0 end]
    if {$ifm(data) != $curdata} {return 1}
    return 0
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
set rcfile [file join $env(HOME) .tkifm]
if [file readable $rcfile] {source $rcfile}

# Parse arguments.
if {$argc == 1} {
    set file [lindex $argv 0]
} else {
    set file ""
}

# Boot up.
MainWindow $file
